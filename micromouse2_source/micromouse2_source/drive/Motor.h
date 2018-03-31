#pragma once
#include "State.h"
#include "../utility/Utility.h"
#include <wiringPi.h>
#include <stdexcept>
#include <string>

namespace Drive
{
	class Motor
	{
	public:
		Motor();
		Motor(const int& gpio_digital_pin_in1, const int& gpio_digital_pin_in2);
		bool setPins(const int& gpio_digital_pin_in1, const int& gpio_digital_pin_in2);
		bool setPin(const int& motor_digital_pin_id, const int& gpio_digital_pin);

		bool forward() const;
		bool forward(const int& speed) const;
		bool forward(const int& speed, const int& duration) const;
		
		bool backward() const;
		bool backward(const int& speed) const;
		bool backward(const int& speed, const int& duration) const;
				
		bool shortBrake();
		bool shortBrake(const int& duration);

		bool stop() const;
		bool stop(const int& duration) const;

	private:
		bool isValidState() const;
		bool validateState() const;
		bool validateState(const State& desired_state) const;

		State readState() const;
		void writeState(const State& new_state) const;

		bool rotate(const int& direction, const int& speed, const int& duration) const;
		
		int digital_pin_in1_;
		int digital_pin_in2_;
	
	private:
		const static int DEFAULT_PIN;
		const static int ROTATE_FORWARD_CCW;
		const static int ROTATE_BACKWARD_CW;
		const static int SPEED_CONSTANT;
		const static int DURATION_INDEFINITE;

		const static std::string INVALID_STATE_PIN_NOT_SET;
		const static std::string INVALID_STATE_DIFFERENCE;
		const static std::string INVALID_ROTATION_DIRECTION;
		const static std::string INVALID_MOTOR_PIN_ID;
		
		const static std::string FAILURE_TO_READ_STATE;
		const static std::string FAILURE_TO_WRITE_STATE;
		const static std::string FAILURE_TO_SET_PIN;

		const static Drive::State FORWARD;
		const static Drive::State BACKWARD;
		const static Drive::State SHORT_BRAKE;
		const static Drive::State STOP;
	};
}