// Mitchell Ciupak
//Project Main

//Includes
#include <GxEPD.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

//Macros
int rainsense= A0; // analog sensor input pin 0
int countval= 0; // counter value starting from 0 and goes up by 1 every second

//Constructor for AVR Arduino, copy from GxEPD_Example else
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 9, /*RST=*/ 8); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7); // default selection of (9), 7

//Init
void setup(){
   Serial.begin(9600); //TODO Ddebug
   //Prep Rain Sensor
   pinMode(rainsense, INPUT);

   //Prep Disp
   display.init();
   display.eraseDisplay();
}

void drawHelloWorld()
{
  display.setTextColor(GxEPD_BLACK);
  display.print("Hello World!");
}

void loop(){
   int rainSenseReading = analogRead(rainsense);
   Serial.println(rainSenseReading); // serial monitoring message 
   delay(250);// rain sensing value from 0 to 1023.

   // from heavy rain - no rain.
   if (countval >= 35){ 
      Serial.print("Heavy rain");
      digitalWrite(buzzerout, HIGH);  //raise an alert after x time
      digitalWrite(ledout, HIGH);  // led glow
   }
};

//https://www.youtube.com/watch?v=UBEhod2wxvE