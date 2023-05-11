/*  Author: PLACITECH. DIY and Funny videos!
 *   
 *  Tiktok: @placitech
 *  Instagram: @placitech_
 *  YouTube: PLACITECH
 *   
 *  Use this code to program a circuit that slowly turns up the volume
 *  of your TV whenever someone sits down to watch it! The way
 *  this works is by detecting the distance between the leg of
 *  the person and an ultrasonic sensor. Once it detects the person
 *  is 10 cm or closer, it will wait 60 seconds and then start turning
 *  turning up the volume of the TV via Bluetooth (you must have a smart
 *  TV for this to work). Make sure to pair the device to the TV before 
 *  putting it in position.
 *  
 *  The microcontroller I used for this example is an ESP32.
 *  
*/

// Make sure to have this library installed as well as the
// ESP32 boards in the Arduino IDE
#include <BleKeyboard.h>

// Declare BLE Remote. The device will appear as "Remote" in your Bluetooth devices list 
BleKeyboard prank_remote("Remote", "PLACITECH", 100); 


// Pins & variables
const byte trigger = 27; 
const byte echo = 14;
const byte ind_led = 25;
int duration = 0;
int distance = 0;



void setup(){
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(ind_led, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(ind_led, LOW);
  prank_remote.begin();
}



void loop(){
  // Check if ESP32 is connected to a BLE device every 2 seconds
  while (prank_remote.isConnected()) {
    // Measure distance between sensor and target
    distance = 0;
    for (int i = 0; i < 50; i++){
      digitalWrite(trigger, LOW);
      delayMicroseconds(2);

      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);

      duration = pulseIn(echo, HIGH);
      distance += duration*0.034/2;
    }

    distance /= 50;
    Serial.println("Distance: " + String(distance) + " cm");
    Serial.println();
    delay(250);

    // If distance is less than 10 cm, wait 60 seconds and start turning up volume
    if (distance <= 10){
      Serial.println("Roommie detected.");
      Serial.println("Destroying eardrums >:D");
      digitalWrite(ind_led, HIGH); // Turn on indicator LED. If you don't want to use an
      // indicator LED, you can just delete that line of code
      delay(60000);
      for (int i = 0; i < 10000; i++){
        prank_remote.write(KEY_MEDIA_VOLUME_UP);
        delay(80);
      }
      digitalWrite(ind_led, LOW);
      delay(5000);
    }
  }
  delay(2000);
}
