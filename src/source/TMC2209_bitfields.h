#pragma once
#pragma pack(push, 1)

namespace TMC2209_n {

  using TMC2208_n::GCONF_t;
  using TMC2130_n::GSTAT_t;
  using TMC5130_n::IFCNT_t;
  using TMC5130_n::SLAVECONF_t;
  using TMC5160_n::OTP_PROG_t;
  using TMC5160_n::OTP_READ_t;

  struct IOIN_t {
    constexpr static uint8_t address = 0x06;
    union {
      uint32_t sr;
      struct {
        bool  enn : 1,
                  : 1,
              ms1 : 1,
              ms2 : 1,
              diag : 1,
                   : 1,
              pdn_uart : 1,
              step : 1,
              spread_en : 1,
              dir : 1;
        uint16_t : 14;
        uint8_t version : 8;
      };
    };
  };

  using TMC5160_n::FACTORY_CONF_t;
  using TMC2130_n::IHOLD_IRUN_t;
  using TMC2130_n::TPOWERDOWN_t;
  using TMC2130_n::TSTEP_t;
  using TMC2130_n::TPWMTHRS_t;
  using TMC2208_n::VACTUAL_t;
  using TMC2130_n::MSCNT_t;
  using TMC2130_n::MSCURACT_t;
  using TMC2208_n::CHOPCONF_t;
  using TMC2208_n::DRV_STATUS_t;
  using TMC2160_n::PWMCONF_t;
  using TMC2160_n::PWM_SCALE_t;
  using TMC2160_n::PWM_AUTO_t;
  using TMC2130_n::TCOOLTHRS_t;

  struct SGTHRS_t {
    constexpr static uint8_t address = 0x40;
    uint8_t sr : 8;
  };

  struct SG_RESULT_t {
    constexpr static uint8_t address = 0x41;
    uint16_t sr : 10;
  };

  struct COOLCONF_t {
    constexpr static uint8_t address = 0x42;
    union {
      uint16_t sr;
      struct {
        uint8_t semin : 4,
                      : 1,
                seup : 2,
                      : 1,
                semax : 4,
                      : 1,
                sedn : 2;
        bool    seimin : 1;
      };
    };
  };

} // namespace

#pragma pack(pop)
