int clock1 = 8;
int mem1 = 9;
int data1 = 10;

int clock2 = 5;
int mem2 = 6;
int data2 = 7;

int arrk[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
int arra[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000};

void setup()
{
 pinMode(clock1, OUTPUT);
 pinMode(mem1, OUTPUT);
 pinMode(data1, OUTPUT);
 pinMode(clock2, OUTPUT);
 pinMode(mem2, OUTPUT);
 pinMode(data2, OUTPUT);
 resetPins();
 
 digitalWrite(clock1, LOW);
 shiftOut(data1, clock1, MSBFIRST, 0b00000000);
 digitalWrite(mem1, HIGH);
 delay(200);
 digitalWrite(clock2, LOW);
 shiftOut(data2, clock2, LSBFIRST, 0b10000000);
 digitalWrite(mem2, HIGH);
}

void loop()
{
  rows();
}

void rows()
{
 for(int j = 0; j < 5; j++)
 {
   digitalWrite(clock1, LOW);
   shiftOut(data1, clock1, LSBFIRST, arra[j]);
   digitalWrite(mem1, HIGH);
   
   for(int i = 0; i < 8; i++)
   {
     digitalWrite(clock2, LOW);
     shiftOut(data2, clock2, LSBFIRST, arrk[i]);
     digitalWrite(mem2, HIGH);
     delay(50);
     resetPins();
   }
 } 
}

void resetPins()
{
 digitalWrite(clock1, LOW);
 digitalWrite(mem1, LOW);
 digitalWrite(data1, LOW); 
 digitalWrite(clock2, LOW);
 digitalWrite(mem2, LOW);
 digitalWrite(data2, LOW); 
}
