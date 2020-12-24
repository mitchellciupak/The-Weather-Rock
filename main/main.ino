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
unsigned int isMain = 0, state = 0, count = 0, soc = 100;;
const unsigned int BATTERY_CAPACITY = 2500; //mAh

double rotSum = 0, accelSum = 0;

//Constructor for AVR Arduino, Defauly from GxEPD_Class
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 9, /*RST=*/ 8);
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7);


//Function Declorations
void drawInit();
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
   pinMode(A0, INPUT);

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

    //Measure IMU
//    imu::Vector<3> rot = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE); // rad/s
//    imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // m/s^2
//
//    rotSum += rot.x() + rot.y() + rot.z(); //over 10 for 1min
//    accelSum += accel.x() + accel.y() + accel.z(); //over 13 for 1min
//
//    if(rotSum > 70 && isMain == 1){ //over 10 for 1min
//      display.drawPaged(drawWindy);
//      isMain = 0;
//    }
//
//    if(accelSum > 91 && isMain == 1){ //over 13 for 1min
//      display.drawPaged(drawQuake);
//      isMain = 0;      
//    }

    //Measure Rain Intensity
    int rainSenseReading = analogRead(A0); //sensing value from 0 to 1023.
    delay(250);
    
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

    if(rainSenseReading < 500) {
      count++; 
   }
    
    //Update Action (Only change if all elements are not ocurring)
    if(isMain == 0) {
      
//     if(accel.x() + accel.y() + accel.z() < 13){
//      accelSum = 0;
//      state += 1;  
//     }
//
//     if(rot.x() + rot.y() + rot.z() < 10){
//      rotSum = 0;
//      state += 1;  
//     }

     if(rainSenseReading > 500){
      count = 0;
      state += 1; 
     }
     
     if(state == 3){
      display.eraseDisplay();
      display.drawPaged(drawMain);
      isMain = 1;
      state = 0;
     }
     
    }

   delay(5000); //TODO 10000
};

void drawLowBatt() {

    drawInit();
    display.println(" MY BATTERY ");
    display.println("  IS LOW!");
    display.println();
    display.println(" PLEASE CHARGE");
}

void drawWindy() {

    drawInit();
    display.println(" THE ROCK IS");
    display.println("  TILTED!");
    display.println();
    display.println(" IT'S WINDY!  ");
}

void drawRain() {

    drawInit();
    display.println(" THE ROCK IS");
    display.println("     WET!");
    display.println();
    display.println(" IT'S RAINING!");
}

void drawSnow() {

    drawInit();
    display.println(" THE ROCK IS");
    display.println("COLD&WET!");
    display.println();
    display.println(" IT'S SNOWING!");
}

void drawQuake() {
    drawInit();
    display.println(" THE ROCK IS");
    display.println(" BOUNCING");
    display.println();
    display.println(" IT'S A QUAKE!");
}

void drawMain() {
    drawInit();
    display.println("Grandma,");
    display.println("MERRY ROCKMAS ");
    display.println("2020!         ");
    display.println("         Love,");
    display.println("      Mitchell");
    display.println("          2020");
}

void drawInit(){
    const char* name = "FreeMonoBold12pt7b";
    const GFXfont* f = &FreeMonoBold12pt7b;
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(f);
    display.setCursor(0, 0);  
    display.println();
    display.println();
}
