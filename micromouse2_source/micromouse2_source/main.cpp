#include <wiringPi.h>
#include <stdio.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
// we have to use BCM numbering when initializing with wiringPiSetupSys
// when choosing a different pin number please use the BCM numbering, also
// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys
#define	LED	17

int main(void)
{
	printf("Let their be light...\n");
	
	wiringPiSetupSys();
	pinMode(LED, OUTPUT);
		
	for (int i = 0; i < 60; i++)
	{
		digitalWrite(LED, HIGH);  // On
		delay(500); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(500);
		printf("again!\n");
	}

	printf("and darkness!\n");
	
	return 0;
}