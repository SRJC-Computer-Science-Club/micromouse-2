#include "Utility.h"

inline bool Utility::isValidDigitalPinvalue(const int& pin_value)
{
	if (!((pin_value == HIGH) || (pin_value == LOW)))
	{
		throw std::invalid_argument(INVALID_DIGITAL_PIN_VALUE);
	}
}