#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) IHOLD_IRUN_register.SETTING = B; write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
#define GET_REG(SETTING) return IHOLD_IRUN_register.SETTING;

// IHOLD_IRUN
template<class T>
uint32_t TMCStepper<T>::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }

template<class T>
void TMCStepper<T>::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register = input;
	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

template<class T> void 	TMCStepper<T>::ihold(uint8_t B) 		{ SET_REG(ihold);		}
template<class T> void 	TMCStepper<T>::irun(uint8_t B)  		{ SET_REG(irun); 		}
template<class T> void 	TMCStepper<T>::iholddelay(uint8_t B)	{ SET_REG(iholddelay); 	}

template<class T> uint8_t TMCStepper<T>::ihold() 				{ GET_REG(ihold);		}
template<class T> uint8_t TMCStepper<T>::irun()  				{ GET_REG(irun); 		}
template<class T> uint8_t TMCStepper<T>::iholddelay()  			{ GET_REG(iholddelay);	}
