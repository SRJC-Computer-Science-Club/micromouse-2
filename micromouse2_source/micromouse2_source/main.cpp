#include <wiringPi.h>
#include <stdio.h>
#include "drive/Motor.h"

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
// we have to use BCM numbering when initializing with wiringPiSetupSys
// when choosing a different pin number please use the BCM numbering, also
// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys
#define	LED	17

void motorTest()
{
	Drive::Motor A;
	A.setPin(1, 0);
	A.forward();
	A.stop();
	A.backward();
	A.shortBrake();
	A.stop();
}

int main(void)
{
	
	motorTest();
	
	printf("Let their be light...\n");
	
	wiringPiSetupSys();
	pinMode(LED, OUTPUT);
		
	int pin = 17;
	for (int i = 0; i < 60; i++)
	{
		printf("%i\n", digitalRead(pin));
		digitalWrite(LED, HIGH);
		printf("%i\n", digitalRead(pin));
		digitalWrite(LED, LOW);
	}
	
	

	/*
	for (int i = 0; i < 60; i++)
	{
		digitalWrite(LED, HIGH);  // On
		delay(500); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(500);
		printf("again!\n");
	}

	printf("and darkness!\n");
	*/

	return 0;
}