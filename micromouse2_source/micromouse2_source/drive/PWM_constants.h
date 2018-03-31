

#pragma once
const char PWM::PCA9685_REG_MODE1 = 0x00;
const char PWM::PCA9685_REG_MODE2 = 0x01;
const char PCA::PCA9685_REG_SUBADDR1 = 0x02;
const char PCA9685_REG_SUBADDR2 = 0x03;
const char PCA9685_REG_SUBADDR3 = 0x04;
const char PCA9685_REG_ALLCALLADDR = 0x05;

const char PCA9685_REG_LEDX_ON_L = 0x06;
const char PCA9685_REG_LEDX_ON_H = 0x07;
const char PCA9685_REG_LEDX_OFF_L = 0x08;
const char PCA9685_REG_LEDX_OFF_H = 0x09;

const char PCA9685_REG_ALL_LED_ON_L = 0xFA;
const char PCA9685_REG_ALL_LED_ON_H = 0xFB;
const char PCA9685_REG_ALL_LED_OFF_L = 0xFC;
const char PCA9685_REG_ALL_LED_OFF_H = 0xFD;
const char PCA9685_REG_PRESCALE = 0xFE;

const char PCA9685_SWRST = 0x06;

const char PCA9685_PRESCALE_MIN = 0x03;
const char PCA9685_PRESCALE_MAX = 0xFF;
const char PCA9685_FREQ_MIN = 24;
const char PCA9685_FREQ_MAX = 1526;

const char PCA9685_COUNTER_RANGE = 4096;
const char PCA9685_DEFAULT_PERIOD = 5000000;	//Default period_ns = 1/200 Hz
const char PCA9685_OSC_CLOCK_MHZ = 25000000;	//Internal oscillator; 25 MHz

const char PCA9685_NUMREGS = 0xFF;
const char PCA9685_MAXCHAN = 0x10;

const char PCA9685_LED_FULL_ON = (1 << 4);	//0000 0001 << 4 = 0001 0000 
const char PCA9685_MODE1_RESTART = (1 << 7);	//0000 0001 << 7 = 1000 0000
const char PCA9685_MODE1_SLEEP = (1 << 4);
const char PCA9685_MODE2_INVERT = (1 << 4);
