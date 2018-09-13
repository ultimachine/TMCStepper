#include "TMCStepper.h"
#include "TMC_MACROS.h"
using namespace TMC2130_n;

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = (CS+1)/32 * V_fs/(R_sense+0.02ohm) * 1/sqrt(2)
  Solve for CS ->
  CS = 32*sqrt(2)*I_rms*(R_sense+0.02)/V_fs - 1

  Example:
  vsense = 0b0 -> V_fs = 0.325V
  mA = 1640mA = I_rms/1000 = 1.64A
  R_sense = 0.10 Ohm
  ->
  CS = 32*sqrt(2)*1.64*(0.10+0.02)/0.325 - 1 = 26.4
  CS = 26
*/

template<class T>
uint16_t TMCStepper<T>::cs2rms(uint8_t CS) {
  return (float)(CS+1)/32.0 * (vsense() ? 0.180 : 0.325)/(Rsense+0.02) / 1.41421 * 1000;
}

template<class T>
void TMCStepper<T>::rms_current(uint16_t mA) {
  uint8_t CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.325 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  if (CS < 16) {
    vsense(true);
    CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.180 - 1;
  } else { // If CS >= 16, turn off high_sense_r
    vsense(false);
  }
  irun(CS);
  ihold(CS*holdMultiplier);
  //val_mA = mA;
}

template<class T>
void TMCStepper<T>::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  rms_current(mA);
}

template<class T>
uint16_t TMCStepper<T>::rms_current() {
  return cs2rms(irun());
}

template<class T>
uint8_t TMCStepper<T>::test_connection() {
  uint32_t drv_status = DRV_STATUS();
  switch (drv_status) {
      case 0xFFFFFFFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

template<class T> void TMCStepper<T>::hysteresis_end(int8_t value) { hend(value+3); }
template<class T> int8_t TMCStepper<T>::hysteresis_end() { return hend()-3; };

template<class T> void TMCStepper<T>::hysteresis_start(uint8_t value) { hstrt(value-1); }
template<class T> uint8_t TMCStepper<T>::hysteresis_start() { return hstrt()+1; }

template<class T>
void TMCStepper<T>::microsteps(uint16_t ms) {
  switch(ms) {
    case 256: mres(0); break;
    case 128: mres(1); break;
    case  64: mres(2); break;
    case  32: mres(3); break;
    case  16: mres(4); break;
    case   8: mres(5); break;
    case   4: mres(6); break;
    case   2: mres(7); break;
    case   0: mres(8); break;
    default: break;
  }
}

template<class T>
uint16_t TMCStepper<T>::microsteps() {
  switch(mres()) {
    case 0: return 256;
    case 1: return 128;
    case 2: return  64;
    case 3: return  32;
    case 4: return  16;
    case 5: return   8;
    case 6: return   4;
    case 7: return   2;
    case 8: return   0;
  }
  return 0;
}

template<class T>
void TMCStepper<T>::blank_time(uint8_t value) {
  switch (value) {
    case 16: tbl(0b00); break;
    case 24: tbl(0b01); break;
    case 36: tbl(0b10); break;
    case 54: tbl(0b11); break;
  }
}

template<class T>
uint8_t TMCStepper<T>::blank_time() {
  switch (tbl()) {
    case 0b00: return 16;
    case 0b01: return 24;
    case 0b10: return 36;
    case 0b11: return 54;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// R+C: GSTATD
template<class T> uint8_t TMCStepper<T>::GSTAT()       { return read(GSTAT_t::address); }
template<class T> void    TMCStepper<T>::GSTAT(uint8_t){ write(GSTAT_t::address, 0b111); }
template<class T> bool    TMCStepper<T>::reset()       { GSTAT_t r; r = GSTAT(); return r.reset; }
template<class T> bool    TMCStepper<T>::drv_err()     { GSTAT_t r; r = GSTAT(); return r.drv_err; }
template<class T> bool    TMCStepper<T>::uv_cp()       { GSTAT_t r; r = GSTAT(); return r.uv_cp; }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPOWERDOWN
template<class T> uint8_t TMCStepper<T>::TPOWERDOWN() { return TPOWERDOWN_register.sr; }
template<class T> void TMCStepper<T>::TPOWERDOWN(uint8_t input) {
  TPOWERDOWN_register = input;
  write(TPOWERDOWN_register.address, TPOWERDOWN_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: TSTEP
template<class T> uint32_t TMCStepper<T>::TSTEP() { return read(TSTEP_t::address); }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPWMTHRS
template<class T> uint32_t TMCStepper<T>::TPWMTHRS() { return TPWMTHRS_register.sr; }
template<class T> void TMCStepper<T>::TPWMTHRS(uint32_t input) {
  TPWMTHRS_register = input;
  write(TPWMTHRS_register.address, TPWMTHRS_register.sr);
}

template<class T> uint16_t TMCStepper<T>::MSCNT() {
  return read(MSCNT_t::address);
}

template<class T> uint32_t TMCStepper<T>::MSCURACT() { return read(MSCURACT_t::address); }
template<class T> int16_t TMCStepper<T>::cur_a() {
  MSCURACT_t r{0};
  r = MSCURACT();
  int16_t value = r.cur_a;
  if (value > 255) value -= 512;
  return value;
}
template<class T> int16_t TMCStepper<T>::cur_b() {
  MSCURACT_t r{0};
  r = MSCURACT();
  int16_t value = r.cur_b;
  if (value > 255) value -= 512;
  return value;
}
