#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cmath>
#include "PWM.h"
#include "PWM_constants.h"
#include "../utility/Utility.h"

/*
Default initializes file descriptor handle to an erronous state.
*/
Drive::PWM::PWM()
{
	file_descriptor_= Utility::WIRING_PI_ERROR;
}

/*
Sets file_descriptor_ for default initialized objects.
*/
void Drive::PWM::setup(const int& device_id)
{
	if (file_descriptor_ == Utility::WIRING_PI_ERROR)
	{
		file_descriptor_ = wiringPiI2CSetup(device_id);
	}
}

/*
Initializes file descriptor via wiringPiI2CSetup() from a supplied device id.
wiringPiI2CSetup() returns a linux default file descriptor handle.
*/
Drive::PWM::PWM(const int& device_id)
{
	file_descriptor_ = wiringPiI2CSetup(device_id);
	if (file_descriptor_ == Utility::WIRING_PI_ERROR)
	{
		throw std::runtime_error(FAILURE_TO_SETUP_I2C);
	}
}

/*
Sets operating frequency.
*/
void Drive::PWM::setFrequency(const double& frequency) const
{
	setPreScale(frequency);
}

/*
Gets the operating frequency.
*/
double Drive::PWM::getFrequency() const
{
	return round(static_cast<double>(PCA9685_OSC_CLOCK_MHZ) / 4096 * (getPreScale() + 1));
}

/*
Sets the Pre Scale register to the operating frequency.
*/
void Drive::PWM::setPreScale(const double& frequency) const
{
	if (frequency < PCA9685_FREQ_MIN || frequency > PCA9685_FREQ_MAX)
	{
		throw std::invalid_argument(INVALID_FREQUENCY);
	}
	sleep();
	int prescale_value = static_cast<int>(lround(PCA9685_OSC_CLOCK_MHZ / (4096 * frequency)) - 1);
	writeRegister8(PCA9685_REG_PRESCALE, prescale_value);
	restart();
}

/*
Returns a value read from the prescale register.
*/
int Drive::PWM::getPreScale() const
{
	return readRegister8(PCA9685_REG_PRESCALE);
}

/*
Restarts PCA9685 PWM cycle. Preserves all PWM register contents. 
*/
void Drive::PWM::restart() const
{
	sleep();
	delayMicroseconds(500);	//datasheet spec (section 7.3.1.1)
	writeRegister8(PCA9685_REG_MODE1, readRegister8(PCA9685_REG_MODE1) | PCA9685_MODE1_RESTART);
}


/*
Puts PCA9685 to sleep, via writing a logical 1 to mode 1 register bit 4.
*/
bool Drive::PWM::sleep() const
{
	if (!isAsleep())
	{
		writeRegister8(PCA9685_REG_MODE1, readRegister8(PCA9685_REG_MODE1) | PCA9685_MODE1_SLEEP);
	}
	return isAsleep();
}

/*
Returns true when PCA9685 is asleep.
*/
bool Drive::PWM::isAsleep() const
{
	return readRegister8(PCA9685_REG_MODE1) & PCA9685_MODE1_SLEEP;
}

/*
Reads an 8 bit register. 
*/
int Drive::PWM::readRegister8(const int& register_address) const
{
	int reg_data = wiringPiI2CReadReg8(file_descriptor_, register_address);
	return reg_data == Utility::WIRING_PI_ERROR ? throw std::runtime_error(FAILURE_TO_READ_REGISTER8) : reg_data;
}

/*
Writes 8 bits to a register.
*/
void Drive::PWM::writeRegister8(const int& register_address, const int& data) const
{
	if (wiringPiI2CWriteReg8(file_descriptor_, register_address, data) == Utility::WIRING_PI_ERROR)
	{
		throw std::runtime_error(FAILURE_TO_WRITE_REGISTER8);
	}
}
