/*
 * Project Name: DHT11 Arduino Thermostate
 * Author: Immanuel Sterzik
 * License: GPL v3
 */



#include <math.h>
#include <dht11.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht11 DHT11;
#define DHT11PIN 8
unsigned long UpdateDelay = 1000UL;

// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double temperature, double humidity)
{
 double a = 17.271;
 double b = 237.7;
 double temp = (a * temperature) / (b + temperature) + log(humidity*0.01);
 double Td = (b * temp) / (a - temp);
 return Td;
}

void setup()
{
 delay(1000);
 lcd.begin(16, 2);
}

void loop()
{
 DHT11.read(DHT11PIN);

 lcd.setCursor(0, 0);
 lcd.print("T ");
 lcd.print(DHT11.temperature);
 lcd.print("C");
 lcd.setCursor(0, 1);
 lcd.print("H ");
 lcd.print(DHT11.humidity);
 lcd.print("%");
 lcd.setCursor(9, 1);
 lcd.print("DP ");
 lcd.print((double)dewPointFast((double)DHT11.temperature, (double)DHT11.humidity));
 lcd.print("C");

 delay(UpdateDelay);
}