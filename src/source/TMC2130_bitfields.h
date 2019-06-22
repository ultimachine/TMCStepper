#pragma once
#pragma pack(push, 1)

namespace TMC2130_n {

struct GCONF_t {
  constexpr static uint8_t address = 0x00;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 18;
    struct {
      bool  i_scale_analog : 1,
            internal_rsense : 1,
            en_pwm_mode : 1,
            enc_commutation : 1,
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

struct IHOLD_IRUN_t {
  constexpr static uint8_t address = 0x10;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 20;
    struct {
      uint8_t ihold : 5,
                    : 3,
              irun : 5,
                   : 3,
              iholddelay : 4;
    };
  };
};

struct GSTAT_t {
  constexpr static uint8_t address = 0x01;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint8_t sr : 3;
    struct {
      bool  reset : 1,
            drv_err : 1,
            uv_cp : 1;
    };
  };
};

struct IOIN_t {
  constexpr static uint8_t address = 0x04;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr;
    struct {
      bool  step : 1,
            dir : 1,
            dcen_cfg4 : 1,
            dcin_cfg5 : 1,
            drv_enn_cfg6 : 1,
            dco : 1,
            : 2;
      uint16_t : 16;
      uint8_t version : 8;
    };
  };
};

struct TPOWERDOWN_t {
  constexpr static uint8_t address = 0x11;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint8_t sr : 8;
};

struct TSTEP_t {
  constexpr static uint8_t address = 0x12;
};

struct TPWMTHRS_t {
  constexpr static uint8_t address = 0x13;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr : 20;
};

struct TCOOLTHRS_t {
  constexpr static uint8_t address = 0x14;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr : 20;
};

struct THIGH_t {
  constexpr static uint8_t address = 0x15;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr : 20;
};

struct XDIRECT_t {
  constexpr static uint8_t address = 0x2D;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 25;
    struct {
      int16_t coil_A : 9;
      int8_t         : 7;
      int16_t coil_B : 9;
    };
  };
};

struct VDCMIN_t {
  constexpr static uint8_t address = 0x33;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr : 23;
};

struct IOINT_t {
  constexpr static uint8_t address = 0x04;
};

struct MSLUT0_t {
  constexpr static uint8_t address = 0x60;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT1_t {
  constexpr static uint8_t address = 0x61;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT2_t {
  constexpr static uint8_t address = 0x62;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT3_t {
  constexpr static uint8_t address = 0x63;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT4_t {
  constexpr static uint8_t address = 0x64;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT5_t {
  constexpr static uint8_t address = 0x65;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT6_t {
  constexpr static uint8_t address = 0x66;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUT7_t {
  constexpr static uint8_t address = 0x67;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  uint32_t sr;
};

struct MSLUTSEL_t {
  constexpr static uint8_t address = 0x68;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr;
    struct {
      uint8_t w0 : 2,
              w1 : 2,
              w2 : 2,
              w3 : 2,
              x1 : 8,
              x2 : 8,
              x3 : 8;
    };
  };
};

struct MSLUTSTART_t {
  constexpr static uint8_t address = 0x69;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 24;
    struct {
      uint8_t start_sin : 8,
                        : 8,
              start_sin90 : 8;
    };
  };
};

struct MSCNT_t {
  constexpr static uint8_t address = 0x6A;
};

struct MSCURACT_t {
  constexpr static uint8_t address = 0x6B;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 25;
    struct {
      int16_t cur_a : 9,
                    : 7,
              cur_b : 9;
    };
  };
};

struct CHOPCONF_t {
  constexpr static uint8_t address = 0x6C;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 32;
    struct {
      uint8_t toff : 4,
              hstrt : 3,
              hend : 4,
                   : 1;
      bool    disfdcc : 1,
              rndtf : 1,
              chm : 1;
      uint8_t tbl : 2;
      bool    vsense : 1,
              vhighfs : 1,
              vhighchm : 1;
      uint8_t sync : 4, // 2130, 5130
              mres : 4;
      bool    intpol : 1,
              dedge : 1,
              diss2g : 1;
    };
    struct { // TMC5160
      uint32_t     : 20;
      uint8_t tpfd : 4; // 5160
      uint16_t     : 7;
      bool diss2vs : 1; // TMC5160 only
    };
  };
};

struct COOLCONF_t {
  constexpr static uint8_t address = 0x6D;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 25;
    struct {
      uint8_t semin : 4,
                    : 1,
              seup : 2,
                    : 1,
              semax : 4,
                    : 1,
              sedn : 2;
      bool    seimin : 1;
      int8_t  sgt : 7,
                  : 1;
      bool    sfilt : 1;
    };
  };
};

struct DCCTRL_t {
	constexpr static uint8_t address = 0x6E;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

	union {
		uint32_t sr : 24;
		struct {
			uint16_t dc_time : 10,
				: 6;
			uint8_t dc_sg : 8;
		};
	};
};

struct DRV_STATUS_t {
  constexpr static uint8_t address = 0x6F;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr;
    struct {
      uint16_t sg_result : 10;
      uint8_t            : 5;
      bool fsactive : 1;
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
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint32_t sr : 22;
    struct {
      uint8_t pwm_ampl : 8,
              pwm_grad : 8,
              pwm_freq : 2;
      bool pwm_autoscale : 1,
           pwm_symmetric : 1;
      uint8_t freewheel : 2;
    };
  };
};

struct PWM_SCALE_t {
  constexpr static uint8_t address = 0x71;
};

struct ENCM_CTRL_t {
  constexpr static uint8_t address = 0x72;
  void operator =(uint32_t input) { sr = input; }
  uint32_t operator ()() { return sr; }

  union {
    uint8_t sr : 2;
    struct {
      bool  inv : 1,
            maxspeed : 1;
    };
  };
};

struct LOST_STEPS_t {
  constexpr static uint8_t address = 0x73;
};

} // namespace

#pragma pack(pop)
