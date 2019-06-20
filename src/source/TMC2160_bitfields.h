#pragma once
#pragma pack(push, 1)

namespace TMC2160_n {

  struct GCONF_t {
    constexpr static uint8_t address = 0x00;
    union {
      uint32_t sr : 18;
      struct {
        bool  recalibrate : 1,
              faststandstill : 1,
              en_pwm_mode : 1,
              multistep_filt : 1,
              shaft : 1,
              diag0_error : 1,
              diag0_otpw : 1,
              diag0_stall : 1,
              diag1_stall : 1,
              diag1_index : 1,
              diag1_onstate : 1,
              diag1_steps_skipped : 1,
              diag0_int_pushpull : 1,
              diag1_pushpull : 1,
              small_hysteresis : 1,
              stop_enable : 1,
              direct_mode : 1;
      };
    };
  };

  using TMC2130_n::GSTAT_t;

  struct IOIN_t {
    constexpr static uint8_t address = 0x04;
    union {
      uint32_t sr;
      struct {
        bool  refl_step : 1,
              refr_dir : 1,
              encb_dcen_cfg4 : 1,
              enca_dcin_cfg5 : 1,
              drv_enn : 1,
              dco_cfg6 : 1,
              : 2;
        uint16_t : 16;
        uint8_t version : 8;
      };
    };
  };

  struct OTP_READ {
    constexpr static uint8_t address = 0x07;
    union {
      uint8_t sr;
      struct {
        uint8_t otp_fclktrim : 5;
        bool otp_s2_level : 1,
             otp_bbm : 1,
             otp_tbl : 1;
      };
    };
  };

  struct SHORT_CONF_t {
    constexpr static uint8_t address = 0x09;
    union {
      uint32_t sr : 19;
      struct {
        uint8_t s2vs_level  : 4,
                            : 4,
                s2g_level   : 4,
                            : 4,
                shortfilter : 2;
        bool shortdelay : 1;
      };
    };
  };

  struct DRV_CONF_t {
    constexpr static uint8_t address = 0x0A;
    union {
      uint32_t sr : 22;
      struct {
        uint8_t bbmtime : 5,
                        : 3,
                bbmclks : 4,
                        : 4,
                otselect : 2,
                drvstrength : 2,
                filt_isense : 2;
      };
    };
  };

  struct GLOBAL_SCALER_t {
    constexpr static uint8_t address = 0x0B;
    uint8_t sr;
  };

  struct OFFSET_READ_t {
    constexpr static uint8_t address = 0x0C;
    union {
      uint16_t sr;
      struct {
        uint8_t b,
                a;
      };
    };
  };

  using TMC2130_n::IHOLD_IRUN_t;
  using TMC2130_n::TPOWERDOWN_t;
  using TMC2130_n::TSTEP_t;
  using TMC2130_n::TPWMTHRS_t;
  using TMC2130_n::TCOOLTHRS_t;
  using TMC2130_n::THIGH_t;
  using TMC2130_n::XDIRECT_t;
  using TMC2130_n::VDCMIN_t;
  using TMC2130_n::CHOPCONF_t;
  using TMC2130_n::COOLCONF_t;
  using TMC2130_n::DCCTRL_t;
  using TMC2130_n::MSLUT0_t;
  using TMC2130_n::MSLUT1_t;
  using TMC2130_n::MSLUT2_t;
  using TMC2130_n::MSLUT3_t;
  using TMC2130_n::MSLUT4_t;
  using TMC2130_n::MSLUT5_t;
  using TMC2130_n::MSLUT6_t;
  using TMC2130_n::MSLUT7_t;
  using TMC2130_n::MSLUTSEL_t;
  using TMC2130_n::MSLUTSTART_t;
  using TMC2130_n::MSCNT_t;
  using TMC2130_n::MSCURACT_t;

  struct DRV_STATUS_t {
    constexpr static uint8_t address = 0x6F;
    union {
      uint32_t sr;
      struct {
        uint16_t sg_result : 10;
        uint8_t            : 2;
        bool s2vsa : 1,
             s2vsb : 1,
             stealth : 1,
             fsactive : 1;
        uint8_t cs_actual : 5,
                          : 3;
        bool  stallGuard : 1,
              ot : 1,
              otpw : 1,
              s2ga : 1,
              s2gb : 1,
              ola : 1,
              olb : 1,
              stst : 1;
      };
    };
  };

  struct PWMCONF_t {
    constexpr static uint8_t address = 0x70;
    union {
      uint32_t sr;
      struct {
        uint8_t pwm_ofs : 8,
                pwm_grad : 8,
                pwm_freq : 2;
        bool pwm_autoscale : 1,
             pwm_autograd : 1;
        uint8_t freewheel : 2,
                          : 2,
                pwm_reg : 4,
                pwm_lim : 4;
      };
    };
  };

  struct PWM_SCALE_t {
    constexpr static uint8_t address = 0x71;
    union {
      uint32_t sr : 25;
      struct {
        uint8_t pwm_scale_sum : 8,
                              : 8;
        uint16_t pwm_scale_auto : 9;
      };
    };
  };

  struct PWM_AUTO_t {
    constexpr static uint8_t address = 0x72;
    union {
      uint32_t sr : 24;
      struct {
        uint8_t pwm_ofs_auto : 8,
                             : 8,
                pwm_grad_auto : 8;
      };
    };
  };

  using TMC2130_n::LOST_STEPS_t;

} // namespace

#pragma pack(pop)
