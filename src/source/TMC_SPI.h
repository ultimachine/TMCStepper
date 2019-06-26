#pragma once

#include <Arduino.h>
#include "TMC_platforms.h"

class TMC_SPI : private TMC_constants {
	protected:
		TMC_SPI() {}

		void init();
		void begin() {};
		uint8_t transfer(uint8_t ulVal);
		uint16_t transfer16(uint16_t data);
		void endTransaction() {};
		void setSPISpeed(uint32_t speed);
		void switchCSpin(bool state);
		uint32_t read(uint8_t addressByte);
		void write(uint8_t addressByte, uint32_t config);

		uint8_t status_response;

		static uint32_t spi_speed; // Default 2MHz
		uint16_t cs_pin;
		bool use_sw_spi = false;

		uint16_t mosi_pin,
				 miso_pin,
				 sck_pin;

		#if defined(ARDUINO_ARCH_AVR)
			fastio_bm mosi_bm,
					miso_bm,
					sck_bm;
			fastio_reg mosi_register,
							 miso_register,
							 sck_register;
		#endif
};
