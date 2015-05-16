#include <wiringPi.h>
#include <stdio.h>


int main()
{
	
	if(wiringPiSetup() == -1)
		return 1;
		
		
	pinMode(0, OUTPUT);  //wiringPi pin-layout; 0=17, 4=23
	pinMode(4, OUTPUT);
	
	int pin1 = 0;
	int pin2 = 4;
	int del = 1000;
	int dur = 2;
	
	for(int i = 0; i < dur; i++)
	{
		digitalWrite(pin1, 0);
		delay(del);
		digitalWrite(pin1, 1);
		digitalWrite(pin2, 0);
		delay(del);
		digitalWrite(pin2, 1);
	}
	delay(1000);
	
	for(int i = 0; i < dur; i++)
	{
		digitalWrite(pin1, 0);
		digitalWrite(pin2, 0);
		delay(del);
		digitalWrite(pin1, 1);
		digitalWrite(pin2, 1);
		delay(del);
	} 	
	
	digitalWrite(pin1, 1);
	digitalWrite(pin2, 1);
}

void blink(int pin1, int pin2, int dur, int del)
{
	for(int i = 0; i < dur; i++)
	{
		digitalWrite(pin1, 0);
		digitalWrite(pin2, 0);
		delay(del);
		digitalWrite(pin1, 1);
		digitalWrite(pin2, 1);
		delay(del);
	}
}



