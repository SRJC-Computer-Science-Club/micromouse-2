#pragma once
#include <wiringPi.h>
#include <stdexcept>

namespace Utility
{
	bool isValidDigitalPinValue(const int& pin_value);
	bool isValidPinIndex(const int& pin_value);
	
	const static std::string INVALID_DIGITAL_PIN_VALUE = "invalid digital pin value";
	const static std::string INVALID_PIN_INDEX = "invalid pin index";
	const static int GPIO_MIN_PIN_INDEX = 0;
	const static int GPIO_MAX_PIN_INDEX = 40;
}
