#include "Utility.h"

const extern std::string Utility::INVALID_DIGITAL_PIN_VALUE = "invalid digital pin value";
const extern std::string Utility::INVALID_PIN_INDEX = "invalid pin index";
const extern int Utility::GPIO_MIN_PIN_INDEX = 0;
const extern int Utility::GPIO_MAX_PIN_INDEX = 40;
const extern int Utility::WIRING_PI_ERROR = -1;

bool Utility::isValidDigitalPinValue(const int& pin_value)
{
	return ((pin_value == HIGH) || (pin_value == LOW));
}

bool Utility::isValidPinIndex(const int& pin_index)
{
	return (pin_index >= GPIO_MIN_PIN_INDEX && pin_index <= GPIO_MAX_PIN_INDEX);
}