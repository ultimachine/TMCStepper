#include "TMCStepper.h"
#include "TMC_MACROS.h"
using namespace TMC2208_n;

TMC2208Stepper::TMC2208Stepper(Stream * SerialPort, float RS) :
	TMCStepper(RS)
	{
		write_only = false;
		HWSerial = SerialPort;
		defaults();
	}

#if SW_CAPABLE_PLATFORM
	TMC2208Stepper::TMC2208Stepper(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS) :
		TMCStepper(RS)
		{
			write_only = SW_RX_pin != SW_TX_pin;
			SoftwareSerial *SWSerialObj = new SoftwareSerial(SW_RX_pin, SW_TX_pin);
			SWSerial = SWSerialObj;
			defaults();
		}

	void TMC2208Stepper::beginSerial(uint32_t baudrate) {
		if (SWSerial != NULL) SWSerial->begin(baudrate);
	}
#endif

void TMC2208Stepper::begin() {
	#if SW_CAPABLE_PLATFORM
		beginSerial(115200);
	#endif
	pdn_disable(true);
	mstep_reg_select(true);

}

void TMC2208Stepper::defaults() {
	GCONF_register.i_scale_analog = 1;
	GCONF_register.internal_rsense = 0; // OTP
	GCONF_register.en_spreadcycle = 0; // OTP
	GCONF_register.multistep_filt = 1; // OTP
	IHOLD_IRUN_register.iholddelay = 1; // OTP
	TPOWERDOWN_register = 20;
	CHOPCONF_register = 0x10000053;
	PWMCONF_register = 0xC10D0024;
  //MSLUT0_register = ???;
  //MSLUT1_register = ???;
  //MSLUT2_register = ???;
  //MSLUT3_register = ???;
  //MSLUT4_register = ???;
  //MSLUT5_register = ???;
  //MSLUT6_register = ???;
  //MSLUT7_register = ???;
  //MSLUTSTART_register.start_sin90 = 247;
  PWMCONF_register = 0x00050480;
}

void TMC2208Stepper::push() {
	GCONF(GCONF_register.sr);
	IHOLD_IRUN(IHOLD_IRUN_register.sr);
	SLAVECONF(SLAVECONF_register.sr);
	TPOWERDOWN(TPOWERDOWN_register.sr);
	TPWMTHRS(TPWMTHRS_register.sr);
	VACTUAL(VACTUAL_register.sr);
	CHOPCONF(CHOPCONF_register.sr);
	PWMCONF(PWMCONF_register.sr);
}

bool TMC2208Stepper::isEnabled() { return !enn() && toff(); }

uint8_t TMC2208Stepper::IFCNT() {
	return read(IFCNT_t::address);
}

void TMC2208Stepper::SLAVECONF(uint16_t input) {
	SLAVECONF_register = input&0xF00;
	write(SLAVECONF_register.address, SLAVECONF_register.sr);
}
uint16_t TMC2208Stepper::SLAVECONF() {
	return SLAVECONF_register.sr;
}
void TMC2208Stepper::senddelay(uint8_t B) 	{ SLAVECONF_register.senddelay = B; write(SLAVECONF_register.address, SLAVECONF_register.sr); }
uint8_t TMC2208Stepper::senddelay() 		{ return SLAVECONF_register.senddelay; }

void TMC2208Stepper::OTP_PROG(uint16_t input) {
	write(OTP_PROG_t::address, input);
}

uint32_t TMC2208Stepper::OTP_READ() {
	return read(OTP_READ_t::address);
}

uint32_t TMC2208Stepper::IOIN() {
	return read(IOIN_t::address);
}
bool TMC2208Stepper::enn()			{ IOIN_t r{0}; r = IOIN(); return r.enn;		}
bool TMC2208Stepper::ms1()			{ IOIN_t r{0}; r = IOIN(); return r.ms1;		}
bool TMC2208Stepper::ms2()			{ IOIN_t r{0}; r = IOIN(); return r.ms2;		}
bool TMC2208Stepper::diag()			{ IOIN_t r{0}; r = IOIN(); return r.diag;		}
bool TMC2208Stepper::pdn_uart()		{ IOIN_t r{0}; r = IOIN(); return r.pdn_uart;	}
bool TMC2208Stepper::step()			{ IOIN_t r{0}; r = IOIN(); return r.step;		}
bool TMC2208Stepper::sel_a()		{ IOIN_t r{0}; r = IOIN(); return r.sel_a;	}
bool TMC2208Stepper::dir()			{ IOIN_t r{0}; r = IOIN(); return r.dir;		}
uint8_t TMC2208Stepper::version() 	{ IOIN_t r{0}; r = IOIN(); return r.version;	}

uint32_t TMC2224Stepper::IOIN() {
	return read(TMC2224_n::IOIN_t::address);
}
bool TMC2224Stepper::enn()			{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.enn;		}
bool TMC2224Stepper::ms1()			{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.ms1;		}
bool TMC2224Stepper::ms2()			{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.ms2;		}
bool TMC2224Stepper::pdn_uart()		{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.pdn_uart;	}
bool TMC2224Stepper::spread()		{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.spread;	}
bool TMC2224Stepper::step()			{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.step;		}
bool TMC2224Stepper::sel_a()		{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.sel_a;	}
bool TMC2224Stepper::dir()			{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.dir;		}
uint8_t TMC2224Stepper::version() 	{ TMC2224_n::IOIN_t r{0}; r = IOIN(); return r.version;	}

uint16_t TMC2208Stepper::FACTORY_CONF() {
	if (write_only) return FACTORY_CONF_register.sr;
	FACTORY_CONF_register = read(FACTORY_CONF_register.address);
	return FACTORY_CONF_register.sr;
}
void TMC2208Stepper::FACTORY_CONF(uint16_t input) {
	FACTORY_CONF_register = input;
	write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr);
}
void TMC2208Stepper::fclktrim(uint8_t B){ FACTORY_CONF_register.fclktrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
void TMC2208Stepper::ottrim(uint8_t B)	{ FACTORY_CONF_register.ottrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
uint8_t TMC2208Stepper::fclktrim()		{ read(FACTORY_CONF_register.address); return FACTORY_CONF_register.fclktrim; }
uint8_t TMC2208Stepper::ottrim()		{ read(FACTORY_CONF_register.address); return FACTORY_CONF_register.ottrim; }

void TMC2208Stepper::VACTUAL(uint32_t input) {
	VACTUAL_register = input;
	write(VACTUAL_register.address, VACTUAL_register.sr);
}
uint32_t TMC2208Stepper::VACTUAL() {
	return VACTUAL_register.sr;
}

uint32_t TMC2208Stepper::PWM_SCALE() {
	return read(PWM_SCALE_t::address);
}
uint8_t TMC2208Stepper::pwm_scale_sum() {
	PWM_SCALE_t r{0};
	r = PWM_SCALE();
	return r.pwm_scale_sum;
}

int16_t TMC2208Stepper::pwm_scale_auto() {
	PWM_SCALE_t r{0};
	r = PWM_SCALE();
	return r.pwm_scale_auto;
	// Not two's complement? 9nth bit determines sign
	/*
	uint32_t d = PWM_SCALE();
	int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
	if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
	else return response;
	*/
}

// R: PWM_AUTO
uint32_t TMC2208Stepper::PWM_AUTO() {
	return read(PWM_AUTO_t::address);
}
uint8_t TMC2208Stepper::pwm_ofs_auto()  { PWM_AUTO_t r{0}; r = PWM_AUTO(); return r.pwm_ofs_auto; }
uint8_t TMC2208Stepper::pwm_grad_auto() { PWM_AUTO_t r{0}; r = PWM_AUTO(); return r.pwm_grad_auto; }
