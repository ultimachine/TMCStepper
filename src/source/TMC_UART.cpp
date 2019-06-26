#include "TMCStepper.h"

uint8_t TMC_UART::calcCRC(uint8_t datagram[], uint8_t len) {
	uint8_t crc = 0;
	for (uint8_t i = 0; i < len; i++) {
		uint8_t currentByte = datagram[i];
		for (uint8_t j = 0; j < 8; j++) {
			if ((crc >> 7) ^ (currentByte & 0x01)) {
				crc = (crc << 1) ^ 0x07;
			} else {
				crc = (crc << 1);
			}
			crc &= 0xff;
			currentByte = currentByte >> 1;
		}
	}
	return crc;
}

void TMC_UART::write(uint8_t addr, uint32_t regVal) {
	uint8_t len = 7;
	addr |= TMC_WRITE;
	uint8_t datagram[] = {TMC_UART_SYNC, slave_address, addr, (uint8_t)(regVal>>24), (uint8_t)(regVal>>16), (uint8_t)(regVal>>8), (uint8_t)(regVal>>0), 0x00};

	datagram[len] = calcCRC(datagram, len);

	#if SW_CAPABLE_PLATFORM
		if (SWSerial != NULL) {
				for(int i=0; i<=len; i++){
					bytesWritten += SWSerial->write(datagram[i]);
				}
		} else
	#endif
		{
			for(int i=0; i<=len; i++){
				bytesWritten += HWSerial->write(datagram[i]);
		}
	}
	delay(replyDelay);
}

template<typename SERIAL_TYPE>
uint64_t TMC_UART::_sendDatagram(SERIAL_TYPE &serPtr, uint8_t datagram[], const uint8_t len, uint16_t timeout) {
	while (serPtr.available() > 0) serPtr.read(); // Flush
	for(int i=0; i<=len; i++) serPtr.write(datagram[i]);
	delay(TMC_UART::replyDelay);

	// scan for the rx frame and read it
	uint32_t ms = millis();
	uint32_t sync_target = ((uint32_t)datagram[0]<<16) | 0xFF00 | datagram[2];
	uint32_t sync = 0;

	do {
		uint32_t ms2 = millis();
		if (ms2 != ms) {
			// 1ms tick
			ms = ms2;
			timeout--;
		}
		if (!timeout) return 0;

		int16_t res = serPtr.read();
		if (res < 0) continue;

		sync <<= 8;
		sync |= res & 0xFF;
		sync &= 0xFFFFFF;

	} while (sync != sync_target);

	uint64_t out = sync;
	ms = millis();
	timeout = abort_window;

	for(uint8_t i=0; i<5;) {
		uint32_t ms2 = millis();
		if (ms2 != ms) {
			// 1ms tick
			ms = ms2;
			timeout--;
		}
		if (!timeout) return 0;

		int16_t res = serPtr.read();
		if (res < 0) continue;

		out <<= 8;
		out |= res & 0xFF;

		i++;
	}

	while (serPtr.available() > 0) serPtr.read(); // Flush
	return out;
}

uint32_t TMC_UART::read(uint8_t addr) {
	constexpr uint8_t len = 3;
	addr |= TMC_READ;
	uint8_t datagram[] = {TMC_UART_SYNC, slave_address, addr, 0x00};
	datagram[len] = calcCRC(datagram, len);
	uint64_t out = 0x00000000UL;

	for (uint8_t i = 0; i < max_retries; i++) {
		#if SW_CAPABLE_PLATFORM
			if (SWSerial != NULL) {
					SWSerial->listen();
					out = _sendDatagram(*SWSerial, datagram, len, abort_window);
					SWSerial->stopListening();
			} else
		#endif
			{
				out = _sendDatagram(*HWSerial, datagram, len, abort_window);
			}

		delay(replyDelay);

		CRCerror = false;
		uint8_t out_datagram[] = {(uint8_t)(out>>56), (uint8_t)(out>>48), (uint8_t)(out>>40), (uint8_t)(out>>32), (uint8_t)(out>>24), (uint8_t)(out>>16), (uint8_t)(out>>8), (uint8_t)(out>>0)};
		uint8_t crc = calcCRC(out_datagram, 7);
		if ((crc != (uint8_t)out) || crc == 0 ) {
			CRCerror = true;
			out = 0;
		} else {
			break;
		}
	}

	return out>>8;
}