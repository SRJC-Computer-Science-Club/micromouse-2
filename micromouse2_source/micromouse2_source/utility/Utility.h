#pragma once
#include <wiringPi.h>
#include <stdexcept>

namespace Utility
{
	inline bool isValidDigitalPinvalue(const int& pin_value);
	
	const static std::string INVALID_DIGITAL_PIN_VALUE = "invalid digital pin value";
}
