#pragma once
#pragma pack(push, 1)

namespace TMC2208_n {
  struct GCONF_t {
    constexpr static uint8_t address = 0x00;
    union {
      uint16_t sr : 10;
      struct {
        bool  i_scale_analog : 1,
              internal_rsense : 1,
              en_spreadcycle : 1,
              shaft : 1,
              index_otpw : 1,
              index_step : 1,
              pdn_disable : 1,
              mstep_reg_select : 1,
              multistep_filt : 1,
              test_mode : 1;
      };
    };
  };

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
              sel_a : 1,
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

  struct VACTUAL_t {
    constexpr static uint8_t address = 0x22;
    uint32_t sr;
  };

  using TMC2130_n::MSCNT_t;
  using TMC2130_n::MSCURACT_t;

  struct CHOPCONF_t {
    constexpr static uint8_t address = 0x6C;
    union {
      uint32_t sr;
      struct {
        uint8_t toff : 4,
                hstrt : 3,
                hend : 4,
                     : 4,
                tbl : 2;
        bool    vsense : 1;
        uint8_t : 6,
                mres : 4;
        bool    intpol : 1,
                dedge : 1,
                diss2g : 1,
                diss2vs : 1;
      };
    };
  };

  struct DRV_STATUS_t {
    constexpr static uint8_t address = 0x6F;
    union {
      uint32_t sr;
      struct {
        bool otpw : 1,
             ot : 1,
             s2ga : 1,
             s2gb : 1,
             s2vsa : 1,
             s2vsb : 1,
             ola : 1,
             olb : 1,
             t120 : 1,
             t143 : 1,
             t150 : 1,
             t157 : 1;
        uint8_t : 4,
                cs_actual : 5,
                : 3,
                : 6;
        bool stealth : 1,
             stst : 1;
      };
    };
  };

  using TMC2160_n::PWMCONF_t;
  using TMC2160_n::PWM_SCALE_t;
  using TMC2160_n::PWM_AUTO_t;

};

namespace TMC2224_n {
  struct IOIN_t {
    constexpr static uint8_t address = 0x06;
    union {
      uint32_t sr;
      struct {
        bool  : 1,
              pdn_uart : 1,
              spread : 1,
              dir : 1,
              enn : 1,
              step : 1,
              ms1 : 1,
              ms2 : 1,
              sel_a : 1;
        uint16_t : 15;
        uint8_t version : 8;
      };
    };
  };
};

#pragma pack(pop)
