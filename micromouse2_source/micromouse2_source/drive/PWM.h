#pragma once
#include <string>

namespace Drive
{
	class PWM
	{
	private:
		int file_descriptor_;
		int address; 

	public:
		PWM();
		PWM(const int& device_id);
		void setup(const int& device_id);
		void setFrequency(const double& frequency) const;
		double getFrequency() const;
		//void setDuty() const;
		//void getDuty() const;
		bool sleep() const;
		void restart() const;
		bool isAsleep() const;

	private:
		

		void setPreScale(const double& frequency) const;
		int getPreScale() const;

		int readRegister8(const int& register_address) const;
		void writeRegister8(const int& register_address, const int& data) const;

		const static char PCA9685_REG_MODE1;
		const static char PCA9685_REG_MODE2;
		const static char PCA9685_REG_SUBADDR1;
		const static char PCA9685_REG_SUBADDR2;
		const static char PCA9685_REG_SUBADDR3;
		const static char PCA9685_REG_ALLCALLADDR;

		const static char PCA9685_REG_LEDX_ON_L;
		const static char PCA9685_REG_LEDX_ON_H;
		const static char PCA9685_REG_LEDX_OFF_L;
		const static char PCA9685_REG_LEDX_OFF_H;

		const static char PCA9685_REG_ALL_LED_ON_L;
		const static char PCA9685_REG_ALL_LED_ON_H;
		const static char PCA9685_REG_ALL_LED_OFF_L;
		const static char PCA9685_REG_ALL_LED_OFF_H;
		const static char PCA9685_REG_PRESCALE;

		const static char PCA9685_SWRST;

		const static char PCA9685_PRESCALE_MIN;
		const static char PCA9685_PRESCALE_MAX;
		const static char PCA9685_FREQ_MIN;
		const static char PCA9685_FREQ_MAX;

		const static char PCA9685_COUNTER_RANGE;
		const static char PCA9685_DEFAULT_PERIOD;
		const static char PCA9685_OSC_CLOCK_MHZ;

		const static char PCA9685_NUMREGS;
		const static char PCA9685_MAXCHAN;

		const static char PCA9685_LED_FULL_ON;
		const static char PCA9685_MODE1_RESTART;
		const static char PCA9685_MODE1_SLEEP;
		const static char PCA9685_MODE2_INVERT;

		const static std::string FAILURE_TO_SETUP_I2C;
		const static std::string FAILURE_TO_READ_REGISTER8;
		const static std::string FAILURE_TO_WRITE_REGISTER8;

		const static std::string INVALID_FREQUENCY;
	};
}