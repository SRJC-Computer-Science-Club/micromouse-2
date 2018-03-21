#include "Utility.h"

bool Utility::isValidDigitalPinValue(const int& pin_value)
{
	return ((pin_value == HIGH) || (pin_value == LOW));
}

bool Utility::isValidPinIndex(const int& pin_index)
{
	return (pin_index >= GPIO_MIN_PIN_INDEX && pin_index <= GPIO_MAX_PIN_INDEX);
}