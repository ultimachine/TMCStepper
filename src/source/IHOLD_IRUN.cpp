#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) IHOLD_IRUN_register.SETTING = B; write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
#define GET_REG(SETTING) return IHOLD_IRUN_register.SETTING;

// IHOLD_IRUN
template<class T, class SPI_UART>
uint32_t TMCStepper<T, SPI_UART>::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }

template<class T, class SPI_UART>
void TMCStepper<T, SPI_UART>::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register = input;
	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

template<class T, class SPI_UART> void 	TMCStepper<T, SPI_UART>::ihold(uint8_t B) 		{ SET_REG(ihold);		}
template<class T, class SPI_UART> void 	TMCStepper<T, SPI_UART>::irun(uint8_t B)  		{ SET_REG(irun); 		}
template<class T, class SPI_UART> void 	TMCStepper<T, SPI_UART>::iholddelay(uint8_t B)	{ SET_REG(iholddelay); 	}

template<class T, class SPI_UART> uint8_t TMCStepper<T, SPI_UART>::ihold() 				{ GET_REG(ihold);		}
template<class T, class SPI_UART> uint8_t TMCStepper<T, SPI_UART>::irun()  				{ GET_REG(irun); 		}
template<class T, class SPI_UART> uint8_t TMCStepper<T, SPI_UART>::iholddelay()  			{ GET_REG(iholddelay);	}
