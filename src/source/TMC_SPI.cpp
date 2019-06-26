#include "TMCStepper.h"

void TMC_SPI::init() {
  pinMode(mosi_pin, OUTPUT);
  pinMode(sck_pin, OUTPUT);
  pinMode(miso_pin, INPUT_PULLUP);
  #ifdef ARDUINO_ARCH_AVR
    mosi_register = portOutputRegister(getPort(mosi_pin));
    miso_register = portInputRegister(getPort(miso_pin));
    sck_register = portOutputRegister(getPort(sck_pin));
    mosi_bm = digitalPinToBitMask(mosi_pin);
    miso_bm = digitalPinToBitMask(miso_pin);
    sck_bm = digitalPinToBitMask(sck_pin);
  #endif
  writeSCK_H;
}

uint8_t TMC_SPI::transfer(uint8_t ulVal) {
  uint8_t value = 0;
  writeSCK_L;

  for (uint8_t i=7 ; i>=1 ; i--) {
    // Write bit
    !!(ulVal & (1 << i)) ? writeMOSI_H : writeMOSI_L;
    // Start clock pulse
    writeSCK_H;
    // Read bit
    value |= ( readMISO ? 1 : 0) << i;
    // Stop clock pulse
    writeSCK_L;
  }

  !!(ulVal & (1 << 0)) ? writeMOSI_H : writeMOSI_L;
  writeSCK_H;
  value |= ( readMISO ? 1 : 0) << 0;

  return value;
}

uint16_t TMC_SPI::transfer16(uint16_t data) {
  uint16_t returnVal = 0x0000;
  returnVal |= transfer((data>>8)&0xFF) << 8;
  returnVal |= transfer(data&0xFF) & 0xFF;
  return returnVal;
}

void TMC_SPI::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

void TMC_SPI::switchCSpin(bool state) {
  digitalWrite(cs_pin, state);
}

uint32_t TMC_SPI::read(uint8_t addressByte) {
  uint32_t out = 0UL;
  if (use_sw_spi) {
    switchCSpin(LOW);
    transfer(addressByte & 0xFF);
    transfer16(0x0000); // Clear SPI
    transfer16(0x0000);

    switchCSpin(HIGH);
    switchCSpin(LOW);

    status_response = transfer(addressByte & 0xFF); // Send the address byte again
    out  = transfer(0x00);
    out <<= 8;
    out |= transfer(0x00);
    out <<= 8;
    out |= transfer(0x00);
    out <<= 8;
    out |= transfer(0x00);

  } else {
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    switchCSpin(LOW);
    SPI.transfer(addressByte & 0xFF);
    SPI.transfer16(0x0000); // Clear SPI
    SPI.transfer16(0x0000);

    switchCSpin(HIGH);
    switchCSpin(LOW);

    status_response = SPI.transfer(addressByte & 0xFF); // Send the address byte again
    out  = SPI.transfer(0x00);
    out <<= 8;
    out |= SPI.transfer(0x00);
    out <<= 8;
    out |= SPI.transfer(0x00);
    out <<= 8;
    out |= SPI.transfer(0x00);

    SPI.endTransaction();
  }
  switchCSpin(HIGH);
  return out;
}

void TMC_SPI::write(uint8_t addressByte, uint32_t config) {
  addressByte |= TMC_WRITE;;
  if (use_sw_spi) {
    switchCSpin(LOW);
    status_response = transfer(addressByte & 0xFF);
    transfer16((config>>16) & 0xFFFF);
    transfer16(config & 0xFFFF);
  } else {
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    switchCSpin(LOW);
    status_response = SPI.transfer(addressByte & 0xFF);
    SPI.transfer16((config>>16) & 0xFFFF);
    SPI.transfer16(config & 0xFFFF);
    SPI.endTransaction();
  }
  switchCSpin(HIGH);
}
