#pragma once
#include "../utility/Utility.h"
#include <wiringPi.h>

namespace Drive
{
	struct State
	{
		int digital_pin_in1_value;
		int digital_pin_in2_value;
		State();
		State(const int& in1, const int& in2);
		friend bool operator==(const State& left, const State& right);
		friend bool operator!=(const State& left, const State& right);
	};
	bool operator==(const State& left, const State& right);
	bool operator!=(const State& left, const State& right);

	/*****************************************************************************
	forward is a Motor::State specified on the toshiba TB6612FNG datasheet.
	A forward event will occur in a single motor state:
		1: IN1: L | IN2: H 
	*****************************************************************************/
	const static State FORWARD{ LOW, HIGH };

	/*****************************************************************************
	backward is a Motor::State specified on the toshiba TB6612FNG datasheet.
	A backward event will occur in a single motor state:
		1: IN1: H | IN2: L 
	*****************************************************************************/
	const static State BACKWARD{ HIGH, LOW };

	/*****************************************************************************
	Short brake is a motor state specified on the toshiba TB6612FNG datasheet.
	A sort brake event will occur in 3 possible motor states:
		1: IN1: H | IN2: H 
		2: IN1: L | IN2: H	//forward "coasting" 
		3: IN1: H | IN2: L	//backward "coasting"
	Note: states 2-3 occur during operation when the pwm signal is low. We 
	consider a short brake event equivalent to "coasting"; a state in which
	braking occurs passively, as the motor decelerates.
	https://electronics.stackexchange.com/questions/267863/what-does-short-brake-mean
	*****************************************************************************/
	const static State SHORT_BRAKE{ HIGH, HIGH };

	/*****************************************************************************
	Stop is a motor state specified on the toshiba TB6612FNG datasheet.
	A stop event will occur in a single motor state (H: High, L: LOW):
		1: IN1: L | IN2: L | PWM: H | STBY: H	
	*****************************************************************************/
	const static State STOP{ LOW, LOW };
}
