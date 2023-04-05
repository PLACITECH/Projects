/*   Author: PLACITECH. DIY and Funny videos!
 *   
 *   Tiktok: @placitech
 *   Instagram: @placitech_
 *   YouTube: PLACITECH
 *   
 *  Use this code to build a device that plays a sound once a random object
 *  moves beyond a distance of 10 cm! In order to detect the object's
 *  distance and play the sound, you will use an ultrasonic sensor and 
 *  the DFPlayerMini module, respectively. Also, you will have to store
 *  the audio file you want the device to play in the microSD card you
 *  will insert the in MP3 module.
 *  
 *  The microcontroller I used for this example is an Arduino Nano, but you
 *  can use any Micro that you have, like the Arduino UNO or MEGA.
 *  
*/
// Make sure to have these libraries installed
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 

// Declare the MP3 module
SoftwareSerial mySoftwareSerial(4, 5);
DFRobotDFPlayerMini mp3module;

// Variables and ultrasonic sensor pins
int dist;
int dur;
const byte trig = 10; 
const byte echo = 9;


// Function used to get the distance between the object
// and the sensor
void get_dist(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  dur = pulseIn(echo, HIGH);
  dist = dur*0.034/2;
  Serial.println(dist);
}



void setup(){
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
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
  
  delay(100);
}



void loop(){
  // Get the object's distance
  get_dist();

  // If the object is within 10 cm, keep sensing the distance. You can also
  // change the "10 (cm)" to a distance that better fits your project.
  while (dist < 10){ 
    delay(100);
    get_dist();
  }

  // If object is grabbed, wait 2 seconds and play the sound
  delay(2000);
  mp3module.play(1);  // Play the sound stored in microSD card

  // Wait 30 seconds to start loop again
  delay(30000);
}
