# LibHoltekPIR
Arduino library for Holtek I2C PIR sensors, especially HT7M2126 (see datasheed in doc folder)


# Light Sensor Addon

Potential Light Sensor:
https://www.sparkfun.com/datasheets/Sensors/Imaging/TEMT6000.pdf

Discussion on arduino forum for lux calculation:
https://forum.arduino.cc/index.php?topic=185158.0

Video showing working measurement:
https://www.youtube.com/watch?v=dPouJw615Vk

Sourcecode (untested, verification needed):

```java
#include <LiquidCrystal.h>


#define TEMT6000pin     A1
#define samples         16


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


unsigned int sample[samples];

unsigned char s = 0;
unsigned int avg = 0;
unsigned int luxValue = 0;
unsigned long sum = 0;


void setup()
{
  memset(sample, 0, samples);
  lcd.begin(16, 2);
}



void loop()
{
   sum -= sample[s];
   sample[s] = analogRead(TEMT6000pin);  
   sum += sample[s];
   s += 1;
   
   if(s >= samples) 
   {
      s = 0;      
      avg = (sum >> 4); 
      luxValue = (avg << 1);
      
      lcd.clear(); 
      lcd.setCursor(1, 0);
      lcd.print("Ardu Lux Meter");
      lcd.setCursor(0, 1);
      lcd.print("Lux Value");
   
      lcd.setCursor(11, 1);
      lcd.print(luxValue);
      delay(600);
   }
}
```
