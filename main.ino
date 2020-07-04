//Mitchell Ciupak
//Project Main

//Includes
#include <GxEPD.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

//Macros
int rainsense= A0; // analog sensor input pin 0
int count= 0; // counter value starting from 0 and goes up by 1 every second
int isCorrectScreen = 0; //Init Refresh Reduction

//Constructor for AVR Arduino, Defauly from GxEPD_Class
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 9, /*RST=*/ 8);
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7);

//Function Declorations
void drawMain();
void drawRain();

//Init
void setup(){
   Serial.begin(9600); //TODO Debug

   //Prep Rain Sensor
   pinMode(rainsense, INPUT);

   //Prep Disp
   display.init();
   display.eraseDisplay();
   display.drawPaged(drawMain);
}

void loop(){
    //Measure Rain Intensity
    int rainSenseReading = analogRead(rainsense);
    delay(250); // rain sensing value from 0 to 1023.

    Serial.println(rainSenseReading); //TODO Debug

    //Trigger Rain Statement
    if(count >= 6) { //Trigger after 1 Minute (6 * 10_000)
        Serial.print("IT IS RAINING"); //TODO Debug

        //Trigger Refresh
        if(count == 6){
            isCorrectScreen = 0;
        }
        
        //Draw Page
        if(isCorrectScreen == 0){
            display.drawPaged(drawRain);
        }
    }
    
    //Update Rain Action
   if(rainSenseReading < 500) {
      count++; 
   }
   else {

       //No Rain or Not Raining Anymore
       Serial.print("NO RAIN"); //TODO Debug

       if(isCorrectScreen == 0){
            display.eraseDisplay();
            display.drawPaged(drawMain);
       }

       //Update count
       count = 0;
   }

   delay(5000); //TODO 10000
};


void drawRain() {
    isCorrectScreen = 1;
    display.setTextColor(GxEPD_BLACK);
    display.print("THE ROCK IS WET, I THINK IT MAY BE RAINING");
}

void drawMain() {
    isCorrectScreen = 1;
    display.setTextColor(GxEPD_BLACK);
    display.print("Welcome to your own personal Weather Rock, Grandma!");
}