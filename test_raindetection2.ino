// Mitchell Ciupak
// Rain Detection Module

int rainsense= A0; // analog sensor input pin 0
int countval= 0; // counter value starting from 0 and goes up by 1 every second
 
void setup(){
   Serial.begin(9600);
   pinMode(rainsense, INPUT);
}

void loop(){
   int rainSenseReading = analogRead(rainsense);
   Serial.println(rainSenseReading); // serial monitoring message 
   delay(250);// rain sensing value from 0 to 1023.

   // from heavy rain - no rain.
   if (rainSenseReading < 500){ 
    
      Serial.print("IT IS RAINING");
      digitalWrite(buzzerout, HIGH);  //raise an alert after x time

      countval = 0;
   }
   else{
    
      Serial.print("NO RAIN");

      countval = 0;
   }

}