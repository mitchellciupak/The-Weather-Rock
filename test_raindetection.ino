// Mitchell Ciupak
// Rain Detection Module

//Macros
int rainsense = A0;
int buzzerout = 12;
int countval = 0;


void setup(){
   Serial.begin(9600);
   pinMode(rainsense, INPUT);
   pinMode(buzzerout, OUTPUT);
}

void loop(){
   int rainSenseReading = analogRead(rainsense);
   Serial.println(rainSenseReading); // serial monitoring message 
   delay(250);// rain sensing value from 0 to 1023.

   // from heavy rain - no rain.
   if (countval >= 35){ 
      Serial.print("IT IS RAINING");
      digitalWrite(buzzerout, HIGH);  //raise an alert after x time
   }

   if(rainSenseReading < 500) {
      countval++; 
   }
   else {
      Serial.print("NO RAIN");
      digitalWrite(buzzerout, LOW);
      countval = 0;
   }
   delay(1000);
}