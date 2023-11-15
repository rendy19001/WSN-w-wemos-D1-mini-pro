#ifndef ads1232_h
#define ads1232_h

#include "Arduino.h"

enum ERROR_t {
	NoERROR,
	TIMEOUT_HIGH,     // Timeout waiting for HIGH
	TIMEOUT_LOW,      // Timeout waiting for LOW
	WOULD_BLOCK,      // weight not measured, measuring takes too long
	STABLE_TIMEOUT,   // weight not stable within timeout
	DIVIDED_by_ZERO    
};

class ads1232 {
	public:
	
		ads1232();
		void init(byte pin_DOUT, byte pin_SCLK, byte pin_PDWN);
		bool is_ready();
		int32_t read();
		void power_down();
		void power_up();

	private:
		int _pin_DOUT;
		int _pin_SCLK;
		int _pin_PDWN;
		int _pin_SPEED;
};

#endif

