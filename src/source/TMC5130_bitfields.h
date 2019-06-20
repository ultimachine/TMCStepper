#pragma once
#pragma pack(push, 1)

namespace TMC5130_n {

struct GCONF_t {
  constexpr static uint8_t address = 0x00;
  union {
    uint32_t sr : 18;
    struct {
      bool  i_scale_analog : 1, // 2130, 5130
            internal_rsense : 1, // 2130, 5130
            en_pwm_mode : 1,
            enc_commutation : 1, // 2130, 5130
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

struct IFCNT_t {
  constexpr static uint8_t address = 0x02;
};

struct SLAVECONF_t {
  constexpr static uint8_t address = 0x03;
  union {
    uint16_t sr : 12;
    struct {
      uint8_t slaveaddr : 8;
      uint8_t senddelay : 4;
    };
  };
};

struct IOIN_t {
  constexpr static uint8_t address = 0x04;
  union {
    uint32_t sr;
    struct {
      bool  refl_step : 1,
            refr_dir : 1,
            encb_dcen_cfg4 : 1,
            enca_dcin_cfg5 : 1,
            drv_enn_cfg6 : 1,
            enc_n_dco : 1,
            sd_mode : 1,
            swcomp_in : 1;
      uint16_t : 16;
      uint8_t version : 8;
    };
  };
};

struct OUTPUT_t {
  constexpr static uint8_t address = 0x04;
  bool sr : 1;
};

struct X_COMPARE_t {
  constexpr static uint8_t address = 0x05;
  uint32_t sr;
};

using TMC2130_n::IHOLD_IRUN_t;
using TMC2130_n::TPOWERDOWN_t;
using TMC2130_n::TSTEP_t;
using TMC2130_n::TPWMTHRS_t;
using TMC2130_n::TCOOLTHRS_t;
using TMC2130_n::THIGH_t;

struct RAMPMODE_t {
  constexpr static uint8_t address = 0x20;
  uint8_t sr : 2;
};

struct XACTUAL_t {
  constexpr static uint8_t address = 0x21;
  uint32_t sr;
};

struct VACTUAL_t {
  constexpr static uint8_t address = 0x22;
};

struct VSTART_t {
  constexpr static uint8_t address = 0x23;
  uint32_t sr : 18;
};

struct A1_t {
  constexpr static uint8_t address = 0x24;
  uint16_t sr : 16;
};

struct V1_t {
  constexpr static uint8_t address = 0x25;
  uint32_t sr : 20;
};

struct AMAX_t {
  constexpr static uint8_t address = 0x26;
  uint16_t sr : 16;
};

struct VMAX_t {
  constexpr static uint8_t address = 0x27;
  uint32_t sr : 23;
};

struct DMAX_t {
  constexpr static uint8_t address = 0x28;
  uint16_t sr : 16;
};

struct D1_t {
  constexpr static uint8_t address = 0x2A;
  uint16_t sr : 16;
};

struct VSTOP_t {
  constexpr static uint8_t address = 0x2B;
  uint32_t sr : 18;
};

struct TZEROWAIT_t {
  constexpr static uint8_t address = 0x2C;
  uint16_t sr : 16;
};

struct XTARGET_t  {
  constexpr static uint8_t address = 0x2D;
};

using TMC2130_n::VDCMIN_t;

struct SW_MODE_t {
  constexpr static uint8_t address = 0x34;
  union {
    uint16_t sr : 12;
    struct {
      bool  stop_l_enable : 1,
            stop_r_enable : 1,
            pol_stop_l : 1,
            pol_stop_r : 1,
            swap_lr : 1,
            latch_l_active : 1,
            latch_l_inactive : 1,
            latch_r_active : 1,
            latch_r_inactive : 1,
            en_latch_encoder : 1,
            sg_stop : 1,
            en_softstop : 1;
    };
  };
};

struct RAMP_STAT_t {
  constexpr static uint8_t address = 0x35;
  union {
    uint16_t sr : 14;
    struct {
      bool  status_stop_l : 1,
            status_stop_r : 1,
            status_latch_l : 1,
            status_latch_r : 1,
            event_stop_l : 1,
            event_stop_r : 1,
            event_stop_sg : 1,
            event_pos_reached : 1,
            velocity_reached : 1,
            position_reached : 1,
            vzero : 1,
            t_zerowait_active : 1,
            second_move : 1,
            status_sg : 1;
    };
  };
};

struct XLATCH_t {
  constexpr static uint8_t address = 0x36;
};

struct ENCMODE_t {
  constexpr static uint8_t address = 0x38;
  union {
    uint16_t sr : 11;
    struct {
      bool  pol_a : 1,
            pol_b : 1,
            pol_n : 1,
            ignore_ab : 1,
            clr_cont : 1,
            clr_once : 1,
            pos_edge : 1,
            neg_edge : 1,
            clr_enc_x : 1,
            latch_x_act : 1,
            enc_sel_decimal : 1;
    };
  };
};

struct X_ENC_t {
  constexpr static uint8_t address = 0x39;
};

struct ENC_CONST_t {
  constexpr static uint8_t address = 0x3A;
  int32_t sr;
};

struct ENC_STATUS_t {
  constexpr static uint8_t address = 0x3B;
};

struct ENC_LATCH_t {
  constexpr static uint8_t address = 0x3C;
};

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
using TMC2130_n::CHOPCONF_t;
using TMC2130_n::COOLCONF_t;
using TMC2130_n::DCCTRL_t;
using TMC2130_n::DRV_STATUS_t;
using TMC2160_n::PWMCONF_t;
using TMC2160_n::PWM_SCALE_t;
using TMC2130_n::ENCM_CTRL_t;

} // namespace

#pragma pack(pop)
