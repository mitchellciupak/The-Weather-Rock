//Mitchell Ciupak
//Project Main

//Includes
#include <GxEPD.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold12pt7b.h>

//Macros
int rainsense= A0; // analog sensor input pin 0
int count= 0; // counter value starting from 0 and goes up by 1 every second
int isMain = 0; // bool main return

//Constructor for AVR Arduino, Defauly from GxEPD_Class
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 9, /*RST=*/ 8);
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7);

//Function Declorations
void drawMain();
void drawRain();

//Init
void setup(){

   //Prep Rain Sensor
   pinMode(rainsense, INPUT);

   //Prep Disp
   display.init();
   display.eraseDisplay();
   display.drawPaged(drawMain);
}

void loop(){
    //Measure Rain Intensity
    int rainSenseReading = analogRead(rainsense); //sensing value from 0 to 1023.
    delay(250);

    //Trigger Rain Statement
    if(count >= 7) { //Trigger after 1 Minute (6-1 * 10_000)

        //Trigger Event
        if(count == 7){
            display.drawPaged(drawRain);
            isMain = 0;
        }
    }
    
    //Update Rain Action
   if(rainSenseReading < 500) {
      count++; 
   }
   else {
       //Not Raining, Update Count
       count = 0;

       if(count == 0 && isMain == 0){
            display.eraseDisplay();
            display.drawPaged(drawMain);
            isMain = 1;
       }

   }

   delay(5000); //TODO 10000
};


void drawRain() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println();
    display.println(" THE ROCK IS");
    display.println("     WET!");
    display.println();
    display.println(" IT'S RAINING!");
}

void drawMain() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println("Grandma,");
    display.println("Welcome to The");
    display.println("Weather Rock!");
    display.println("         Love,");
    display.println("      Mitchell");
    display.println("          2020");
}