#pragma once
#pragma pack(push, 1)

namespace TMC5160_n {

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
            : 2,
            diag0_step : 1,
            diag1_dir : 1,
            : 3,
            diag0_int_pushpull : 1,
            diag1_poscomp_pushpull : 1,
            small_hysteresis : 1,
            stop_enable : 1,
            direct_mode : 1;
    };
    struct { // SD_MODE = 1
      bool : 5,
           diag0_error : 1,
           diag0_otpw : 1,
           diag0_stall : 1,
           diag1_stall : 1,
           diag1_index : 1,
           diag1_onstate : 1,
           diag1_steps_skipped : 1;       
    };
  };
};

using TMC2130_n::GSTAT_t;
using TMC5130_n::IFCNT_t;
using TMC5130_n::SLAVECONF_t;

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
            enc_n_dco_cfg6 : 1,
            sd_mode : 1,
            swcomp_in : 1;
      uint16_t : 16;
      uint8_t version : 8;
    };
  };
};

using TMC5130_n::OUTPUT_t;
using TMC5130_n::X_COMPARE_t;

struct OTP_PROG_t {
  constexpr static uint8_t address = 0x04;
};

struct OTP_READ_t {
  constexpr static uint8_t address = 0x05;
};

struct FACTORY_CONF_t {
  constexpr static uint8_t address = 0x07;
  union {
    uint16_t sr;
    struct {
        uint8_t fclktrim : 5,
                         : 3,
                ottrim : 2;
    };
  };
};

using TMC2160_n::SHORT_CONF_t;
using TMC2160_n::DRV_CONF_t;
using TMC2160_n::GLOBAL_SCALER_t;
using TMC2160_n::OFFSET_READ_t;
using TMC2130_n::IHOLD_IRUN_t;
using TMC2130_n::TPOWERDOWN_t;
using TMC2130_n::TSTEP_t;
using TMC2130_n::TPWMTHRS_t;
using TMC2130_n::TCOOLTHRS_t;
using TMC2130_n::THIGH_t;
using TMC5130_n::RAMPMODE_t;
using TMC5130_n::XACTUAL_t;
using TMC5130_n::VACTUAL_t;
using TMC5130_n::VSTART_t;
using TMC5130_n::A1_t;
using TMC5130_n::V1_t;
using TMC5130_n::AMAX_t;
using TMC5130_n::VMAX_t;
using TMC5130_n::DMAX_t;
using TMC5130_n::VSTOP_t;
using TMC5130_n::TZEROWAIT_t;
using TMC5130_n::XTARGET_t;
using TMC2130_n::VDCMIN_t;
using TMC5130_n::SW_MODE_t;
using TMC5130_n::RAMP_STAT_t;
using TMC5130_n::XLATCH_t;
using TMC5130_n::ENCMODE_t;
using TMC5130_n::X_ENC_t;
using TMC5130_n::ENC_CONST_t;
using TMC5130_n::ENC_STATUS_t;
using TMC5130_n::ENC_LATCH_t;

struct ENC_DEVIATION_t {
  constexpr static uint8_t address = 0x3D;
  uint32_t sr : 20;
};

using TMC5130_n::MSLUT0_t;
using TMC5130_n::MSLUT1_t;
using TMC5130_n::MSLUT2_t;
using TMC5130_n::MSLUT3_t;
using TMC5130_n::MSLUT4_t;
using TMC5130_n::MSLUT5_t;
using TMC5130_n::MSLUT6_t;
using TMC5130_n::MSLUT7_t;
using TMC5130_n::MSLUTSEL_t;
using TMC5130_n::MSLUTSTART_t;
using TMC2130_n::MSCNT_t;
using TMC2130_n::MSCURACT_t;
using TMC2130_n::CHOPCONF_t;
using TMC2130_n::COOLCONF_t;
using TMC2130_n::DCCTRL_t;
using TMC2160_n::DRV_STATUS_t;
using TMC2160_n::PWMCONF_t;
using TMC2160_n::PWM_SCALE_t;
using TMC2160_n::PWM_AUTO_t;
using TMC2130_n::LOST_STEPS_t;
} // namespace

#pragma pack(pop)
