/*  Author: PLACITECH. DIY and Funny videos!
 *   
 *  Tiktok: @placitech
 *  Instagram: @placitech_
 *  YouTube: PLACITECH
 *   
 *  Use this code to program a circuit for getting your friends WET!
 *  To do this, you'll place this device behind a door and wait for
 *  any of your friends to open it. Once they do that, the device will
 *  start both throwing water and playing a sound!
 *  
 *  The microcontroller I used for this example is an Arduino Nano, 
 *  but you can use any Micro that you have, like the Arduino UNO or MEGA.
 *  
*/

// Make sure to have these libraries installed
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 

#define trigger 4
#define pump 7

// Declare MP3 module
SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini mp3module;


void setup() {
  Serial.begin(9600);
  pinMode(trigger, INPUT_PULLUP);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);

  delay(2000);
  
  mySoftwareSerial.begin(9600);
  
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!mp3module.begin(mySoftwareSerial)) { 
    Serial.println("Unable to connect to module!");
    Serial.println("Check cable connections and");
    Serial.println("make sure SD Card is inserted");
    while(1);
  }
  
  Serial.println("Succesfully connected to DFPlayer Mini");
  
  mp3module.setTimeOut(500); // Set serial communictaion time out to 500 ms
  mp3module.volume(25);  //Set volume value (0-30).
  mp3module.EQ(DFPLAYER_EQ_NORMAL); // Set equalization to normal
  mp3module.outputDevice(DFPLAYER_DEVICE_SD); // Read music from MicroSD card
  delay(1000);
}



void loop() {
  // Wait for cable to be removed
  Serial.println("Waiting to be triggered");
  Serial.println();

  while (digitalRead(trigger) == LOW){
    delay(10);
  }

  // Turn on pump and play sound
  Serial.println("Cable removed. Prank device TRIGGERED!");
  //delay(500);

  digitalWrite(pump, HIGH);
  delay(1000);
  mp3module.play(1);

  delay(2000);

  // Turn off pump after 5 seconds
  digitalWrite(pump, LOW);

  // Reconnect trigger cable for device to reset
  while (digitalRead(trigger) == HIGH){
    delay(10);
  }

  delay(1000);
}