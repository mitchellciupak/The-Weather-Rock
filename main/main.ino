//Mitchell Ciupak
//20201224

//Include
#include <SparkFunBQ27441.h>

#include <GxEPD.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold12pt7b.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

//Macros
int isMain = 0; // bool main return
int rainsense= A0; // analog sensor input pin 0
int count= 0; // counter value starting from 0 and goes up by 1 every second

const unsigned int BATTERY_CAPACITY = 2500; //mAh
unsigned int soc = 100; //batt percentage

double rotSum = 0;
double accelSum = 0;

//Constructor for AVR Arduino, Defauly from GxEPD_Class
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 9, /*RST=*/ 8);
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7);


//Function Declorations
void drawMain();
void drawWindy();
void drawRain();
void drawSnow();
void drawQuake();
void drawLowBatt();


//Init
void setup(){

   //Prep Battery Babysitter
   lipo.begin();
   lipo.setCapacity(BATTERY_CAPACITY);

   //Prep IMU(BNO055)
   bno.begin();

   //Prep Rain Sensor
   pinMode(rainsense, INPUT);

   //Prep Disp
   display.init();
   display.eraseDisplay();
   display.drawPaged(drawMain);
}

void loop(){
  
    //Batt
    if(lipo.soc() < 10) {
      display.drawPaged(drawLowBatt);
      isMain = 0;
    }

    //IMU
    imu::Vector<3> rot = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE); // rad/s
    imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // m/s^2

    rotSum += rot.x() + rot.y() + rot.z(); //over 10 for 1min
    accelSum += accel.x() + accel.y() + accel.z(); //over 13 for 1min
    
    //Measure Rain Intensity
    int rainSenseReading = analogRead(rainsense); //sensing value from 0 to 1023.
    delay(250);

    if(rotSum > 70 && isMain == 1){ //over 10 for 1min
      display.drawPaged(drawWindy);
      isMain = 0;
    }

    if(accelSum > 91 && isMain == 1){ //over 13 for 1min
      display.drawPaged(drawQuake);
      isMain = 0;      
    }

    //Trigger Rain Statement
    if(count >= 7) { //Trigger after 1 Minute (6-1 * 10_000)

        //Trigger Event
        if(count == 7){
          if(bno.getTemp() < 0){
            display.drawPaged(drawSnow);
          } else {
            display.drawPaged(drawRain);
          }
            isMain = 0;
        }
    }
    
    //Update Action
   if(rot.x() + rot.y() + rot.z() < 10 && isMain == 0){
      rotSum = 0;
      display.eraseDisplay();
      display.drawPaged(drawMain);
      isMain = 1;
   }
   if(accel.x() + accel.y() + accel.z() < 13 && isMain == 0){
      accelSum = 0;
      display.eraseDisplay();
      display.drawPaged(drawMain);
      isMain = 1;

   }
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

void drawLowBatt() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println();//
    display.println(" MY BATTERY ");
    display.println("  IS LOW!");
    display.println();
    display.println(" PLEASE CHARGE");
}

void drawWindy() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println();
    display.println(" THE ROCK IS");
    display.println("  TILTED!");
    display.println();
    display.println(" IT'S WINDY!  ");
}

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

void drawSnow() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println();
    display.println(" THE ROCK IS");
    display.println("COLD&WET!");
    display.println();
    display.println(" IT'S SNOWING!");
}

void drawQuake() {

    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);
    display.println();
    display.println();
    display.println(" THE ROCK IS");
    display.println(" BOUNCING");
    display.println();
    display.println(" IT'S A QUAKE!");
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
    display.println("Welcome to The"); //TODO Merry Christmas
    display.println("Weather Rock!");
    display.println("         Love,");
    display.println("      Mitchell");
    display.println("          2020");
}
