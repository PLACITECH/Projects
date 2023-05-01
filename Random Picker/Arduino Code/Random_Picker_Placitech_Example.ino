/*  Author: PLACITECH. DIY and Funny videos!
 *   
 *  Tiktok: @placitech
 *  Instagram: @placitech_
 *  YouTube: PLACITECH
 *   
 *  Use this code to make a "random" options picker. This is a device I
 *  have used in many funny TikToks. The purpose of this device is to
 *  pretend like it's choosing between several options (Restaurants, Movies,
 *  Gifts, or whatever you can think of) just to pick something else (usually
 *  funny) at the end.
 *  
 *  The microcontroller I used for this example is an Arduino Nano, but you
 *  can use any Micro that you have, like the Arduino UNO or MEGA.
 *  
*/

// Make sure you have these libraries installed
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// Display dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// Assign pins
#define MOSI_PIN 4
#define SCLK_PIN 5
#define CS_PIN   6
#define DC_PIN   7
#define RST_PIN  8

// Color definitions. I assigned a number for each one (0, 1, 2...) so you can
// choose which color to use in the "print_text" function.
#define BLACK           0x0000 // 0
#define WHITE           0xFFFF // 1
#define RED             0xF800 // 2
#define GREEN           0x07E0 // 3
#define CYAN            0x07FF // 4
#define MAGENTA         0xF81F // 5
#define YELLOW          0xFFE0 // 6  
#define BLUE            0x001F // 7


// Declare display
Adafruit_SSD1351 Oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  


// FUNCTION USED TO PRINT TEXT. It accepts 5 parameters. The first one is the color of the text,
// and the last 4 are the words you want to print. Each will be in a different row of the screen
void print_text(byte color, String text1, String text2 = "", String text3 = "", String text4 = ""){
  switch (color){
    case 0:
      Oled.setTextColor(BLACK);
      break;
    case 1:
      Oled.setTextColor(WHITE);
      break;
    case 2:
      Oled.setTextColor(RED);
      break;
    case 3:
      Oled.setTextColor(GREEN);
      break;
    case 4:
      Oled.setTextColor(CYAN);
      break;
    case 5:
      Oled.setTextColor(MAGENTA);
      break;
    case 6:
      Oled.setTextColor(YELLOW);
      break;
    case 7:
      Oled.setTextColor(BLUE);
      break;   
  }

  Oled.setCursor(0, 0);
  Oled.print(text1);
  Oled.setCursor(0, 30);
  Oled.print(text2);
  Oled.setCursor(0, 60);
  Oled.print(text3);
  Oled.setCursor(0, 90);
  Oled.print(text4);
}



const byte but = 2; // The button will be connected to pin 2
int del = 100; // This is the delay between each option, you can change if you want

void setup() {
  Serial.begin(9600);
  pinMode(but, INPUT_PULLUP);

  Oled.begin();
  Oled.setRotation(0); // You can choose any value between 0-3. This will change the text orientation
  Oled.setTextSize(2); // Size 2 is perfect for this specific display
  Oled.fillScreen(BLACK); // Clear display
  Oled.setTextColor(WHITE); // You can set this to any of the colors defined above
}



void loop() {
  // Print title. I assigned the color YELLOW for it, but you can choose
  // whichever color you prefer/ Also, change the "XXX" to whatever category
  // you are choosing from. Ex: Game, Restaurant, etc.
  print_text(6, "RANDOM", "XXX", "PICKER");

  // Wait for button to be pressed
  while(digitalRead(but) == HIGH){
    delay(10);
  }

  while(digitalRead(but) == LOW){
    delay(10);
  }

  // Everytime we delete something we printed, we just "print" it again, but in color BLACK
  print_text(0, "RANDOM", "XXX", "PICKER");

  delay(500);

  // Cicle through the 5 options 3 times
  for (int i = 0; i < 3; i++){
    // You can write anything you want in each of the options.
    // I assigned the color white for them, but you can choose
    // whichever color you prefer
    print_text(1, "FIRST", "ITEM", " ", " ");
    delay(del);
    print_text(0, "FIRST", "ITEM", " ", " ");

    print_text(1, "SECOND", "ITEM", " ", " ");
    delay(del);
    print_text(0, "SECOND", "ITEM", " ", " ");

    print_text(1, "THIRD", "ITEM", " ", " ");
    delay(del);
    print_text(0,"THIRD", "ITEM", " ", " ");

    print_text(1, "FOURTH", "ITEM", " ", " ");
    delay(del);
    print_text(0, "FOURTH", "ITEM", " ", " ");

    print_text(1, "FIFTH", "ITEM", " ", " ");
    delay(del);
    print_text(0, "FIFTH", "ITEM", " ", " ");
  }

  // Print "winning" option. I assigned the color GREEN for it,
  // but you can choose whichever color you prefer
  print_text(3, "WINNING", "ITEM", " ", " ");
  delay(5000);
  print_text(0, "WINNING", "ITEM", " ", " ");
}
