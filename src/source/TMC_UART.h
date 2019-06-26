#pragma once

#include <Arduino.h>
#include "TMC_platforms.h"

class TMC_UART : private TMC_constants{
  protected:
    TMC_UART() {}

    void write(uint8_t, uint32_t);
    uint32_t read(uint8_t);
    uint8_t calcCRC(uint8_t datagram[], uint8_t len);

    Stream * HWSerial = NULL;
    #if SW_CAPABLE_PLATFORM
      SoftwareSerial * SWSerial = NULL;
    #endif

    template<typename SERIAL_TYPE>
    uint64_t _sendDatagram(SERIAL_TYPE &, uint8_t [], const uint8_t, uint16_t);

    uint16_t bytesWritten = 0;
    bool CRCerror = false;
    uint8_t slave_address = TMC_SLAVE_ADDR;
    bool write_only;
    static constexpr uint8_t replyDelay = 2;
    static constexpr uint8_t abort_window = 5;
    static constexpr uint8_t max_retries = 2;

    static constexpr uint8_t  TMC_UART_SYNC = 0x05,
                              TMC_SLAVE_ADDR = 0x00;
};
