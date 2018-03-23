#include "Motor.h"
#include "Motor_constants.h"

/*
Default constructs a motor object.
*/
Drive::Motor::Motor() 
{
	digital_pin_in1_ = DEFAULT_PIN;
	digital_pin_in2_ = DEFAULT_PIN;
}


/*
Constructs a motor object using the digital_pin arguments.
*/
Drive::Motor::Motor(const int& gpio_digital_pin_in1, const int& gpio_digital_pin_in2)
{
	setPin(1, gpio_digital_pin_in1);
	setPin(2, gpio_digital_pin_in2);
}

/*
Returns true when both pins are set to the arguments.
*/
bool Drive::Motor::setPins(const int& gpio_digital_pin_in1, const int& gpio_digital_pin_in2)
{
	return setPin(1, gpio_digital_pin_in1) && setPin(2, gpio_digital_pin_in2);
}

/*
Returns true when digital_pin is set to gpio_digital_pin
*/
bool Drive::Motor::setPin(const int& motor_digital_pin_id, const int& gpio_digital_pin)
{
	if (!Utility::isValidPinIndex(gpio_digital_pin))
	{
		throw std::invalid_argument(Utility::INVALID_PIN_INDEX);
	}
	if (motor_digital_pin_id == 1)
	{
		digital_pin_in1_ = gpio_digital_pin;
		return digital_pin_in1_ == gpio_digital_pin ? true : throw std::runtime_error(FAILURE_TO_SET_PIN);
	}
	else if (motor_digital_pin_id == 2)
	{
		digital_pin_in2_ = gpio_digital_pin;
		return digital_pin_in2_ == gpio_digital_pin ? true : throw std::runtime_error(FAILURE_TO_SET_PIN);
	}
	else
	{
		throw std::invalid_argument(INVALID_MOTOR_PIN_ID);
	}
}



/*
Returns true when both digital_pins have a value between 0 and 40, inclusive.
*/
bool Drive::Motor::isValidState() const
{
	return (Utility::isValidPinIndex(digital_pin_in1_) && Utility::isValidPinIndex(digital_pin_in2_));
}

/*
Returns true when state is valid. Otherwise, it throws. Typically, 
validateState() is called at the beginning of a function to verify a 
valid pre-condition.
*/
bool Drive::Motor::validateState() const
{
	return isValidState() ? true : throw std::runtime_error(INVALID_STATE_PIN_NOT_SET);
}

/*
Returns true when this' state is equal to desired_state. Typically,
validateState is called at the end of a function to verify state
is properly set.
*/
bool Drive::Motor::validateState(const State& desired_state) const
{
	return (readState() == desired_state) ? true : throw std::runtime_error(INVALID_STATE_DIFFERENCE);
}

/*
Returns State read on digital_pins.
*/
Drive::State Drive::Motor::readState() const
{
	validateState();
	State read_state;
	try
	{
		read_state.digital_pin_in1_value = digitalRead(digital_pin_in1_);
		read_state.digital_pin_in2_value = digitalRead(digital_pin_in2_);
	}
	catch (...)
	{
		throw std::runtime_error(FAILURE_TO_READ_STATE);
	}
	return read_state;
}

/*
Writes State on digital_pins. Note: no verification of the written state! 
*/
void Drive::Motor::writeState(const State& new_state) const
{
	validateState();
	digitalWrite(digital_pin_in1_, new_state.digital_pin_in1_value);
	digitalWrite(digital_pin_in2_, new_state.digital_pin_in2_value);
}

/*
Rotates motor forward at it's current speed for an indefinite duration.
Returns true if state is FORWARD. 
*/
bool Drive::Motor::forward() const
{
	return rotate(ROTATE_FORWARD_CCW, SPEED_CONSTANT, DURATION_INDEFINITE);
}

/*
Rotates the motor forward at a set speed for an indefinite duration.
Returns true if state is FORWARD.
*/
bool Drive::Motor::forward(const int& speed) const
{
	return rotate(ROTATE_FORWARD_CCW, speed, DURATION_INDEFINITE);
}

/*
Rotates the motor forward at a set speed for a set duration (miliseconds).
Returns true if state is SHORT_BRAKE. Note: when a duration is specified
the motor enters a "coasting" state post-duration.
*/
bool Drive::Motor::forward(const int& speed, const int& duration) const
{
	return rotate(ROTATE_FORWARD_CCW, speed, duration);
}

/*
Rotates motor backward at it's current speed for an indefinite duration.
Returns true if state is BACKWARD.
*/
bool Drive::Motor::backward() const
{
	return rotate(ROTATE_BACKWARD_CW, SPEED_CONSTANT, DURATION_INDEFINITE);
}

/*
Rotates the motor backward at a set speed for an indefinite duration.
Returns true if state is BACKWARD.
*/
bool Drive::Motor::backward(const int& speed) const
{
	return rotate(ROTATE_BACKWARD_CW, speed, DURATION_INDEFINITE);
}

/*
Rotates the motor backward at a set speed for a set duration (miliseconds).
Returns true if state is SHORT_BRAKE. Note: when a duration is specified
the motor enters a "coasting" state post-duration.
*/
bool Drive::Motor::backward(const int& speed, const int& duration) const
{
	return rotate(ROTATE_BACKWARD_CW, speed, duration);
}

/*
Short brakes indefinitely. Returns true if state is SHORT_BRAKE.
*/
bool Drive::Motor::shortBrake()
{
	return shortBrake(DURATION_INDEFINITE);
}

/*
Short brakes for a set duration. Returns true if new_state is original_state
when duration is greater than 0. Otherwise, returns true if state is SHORT_BRAKE.
*/
bool Drive::Motor::shortBrake(const int& duration)
{
	validateState();
	if (duration > 0)
	{
		const State original_state = readState();
		writeState(SHORT_BRAKE);
		if (!validateState(SHORT_BRAKE))
		{
			throw std::runtime_error(FAILURE_TO_WRITE_STATE);
		}
		delay(duration);
		writeState(original_state);
		return validateState(original_state) ? true : throw std::runtime_error(INVALID_STATE_DIFFERENCE);
	}
	writeState(SHORT_BRAKE);
	return validateState(SHORT_BRAKE) ? true : throw std::runtime_error(FAILURE_TO_WRITE_STATE);
}

/*
Stop indefinitely. Returns true when state is STOP.
*/
bool Drive::Motor::stop() const
{
	return stop(DURATION_INDEFINITE);
}

/*
Stop for a set duration. Returns true if new_state is original_state
when duration is greater than 0. Otherwise, returns true if state is STOP.
*/
bool Drive::Motor::stop(const int& duration) const
{
	validateState();
	if (duration > 0)
	{
		const State original_state = readState();
		writeState(STOP);
		if (!validateState(STOP))
		{
			throw std::runtime_error(FAILURE_TO_WRITE_STATE);
		}
		delay(duration);
		writeState(original_state);
		return validateState(original_state) ? true : throw std::runtime_error(INVALID_STATE_DIFFERENCE);
	}
	writeState(STOP);
	return validateState(STOP) ? true : throw std::runtime_error(FAILURE_TO_WRITE_STATE);
}


bool Drive::Motor::rotate(const int& direction, const int& speed, const int& duration) const
{
	validateState();
	const State original_state = readState();
	if (speed > 0)
	{
		//set speed
		//validate speed set else throw
	}
	if (direction == ROTATE_FORWARD_CCW)
	{
		writeState(FORWARD);
		if (!validateState(FORWARD))
		{
			throw std::runtime_error(FAILURE_TO_WRITE_STATE);
		}
	}
	else if (direction == ROTATE_BACKWARD_CW)
	{
		writeState(BACKWARD);
		if (!validateState(BACKWARD))
		{
			throw std::runtime_error(FAILURE_TO_WRITE_STATE);
		}
	}
	else
	{
		throw std::invalid_argument(INVALID_ROTATION_DIRECTION);
	}
	if (duration > 0)
	{
		delay(duration);
		writeState(original_state);
		return validateState(original_state) ? true : throw std::runtime_error(INVALID_STATE_DIFFERENCE);
	}
	else
	{
		return !validateState(original_state) ? true : throw std::invalid_argument(INVALID_STATE_DIFFERENCE);
	}
}