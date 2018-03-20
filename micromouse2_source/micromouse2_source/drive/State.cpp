#include "State.h"

Drive::State::State() 
{
	digital_pin_in1_value = 0;
	digital_pin_in2_value = 0;
}

Drive::State::State(const int& in1, const int& in2)
{
	if (Utility::isValidDigitalPinvalue(in1) && Utility::isValidDigitalPinvalue(in2))
	{
		digital_pin_in1_value = in1;
		digital_pin_in2_value = in2;
	}
	else
	{
		throw std::invalid_argument(Utility::INVALID_DIGITAL_PIN_VALUE);
	}
}

bool Drive::operator==(const Drive::State& left, const Drive::State& right)
{
	return !(
		(left.digital_pin_in1_value != right.digital_pin_in1_value) ||
		(left.digital_pin_in2_value != right.digital_pin_in2_value)
		);
}

bool Drive::operator!=(const Drive::State& left, const Drive::State& right)
{
	return !(left == right);
}