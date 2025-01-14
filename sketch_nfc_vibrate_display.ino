#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

#include <Arduino.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId = "None";
byte nuidPICC[4];

// Define the pin connected to SIG
const int motorPin = 3;

void setup(void) 
{
 Serial.begin(9600);
 while (!Serial) {
  delay(1000);
 }
//  delay(5000);
 nfc.begin();
 Serial.println("System initialized");

 pinMode(motorPin, OUTPUT);

//  paint();
}
 
void loop() 
{
 readNFC();
}
 
bool isVibrating = false;
void readNFC() 
{
 if (nfc.tagPresent())
 {
   NfcTag tag = nfc.read();
   tag.print();
   tagId = tag.getUidString();
   if (!isVibrating) {
    isVibrating = true;
    // vibrate();
   }
   paint();
 }
 delay(5000);
 isVibrating = false;
}

void vibrate() {
  // Turn the motor on
  digitalWrite(motorPin, HIGH);
  delay(1000);  // wait 1 second
  

  // Turn the motor off
  digitalWrite(motorPin, LOW);
  delay(1000);  // wait 1 second
}
