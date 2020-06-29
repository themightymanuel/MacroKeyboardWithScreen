
//Include external libraries

#include <Keypad.h>    //Used to interface with the 4x4 keypad
#include <Keyboard.h>  //Used to emulate a HID device - Keyboad
#include <Mouse.h>     //Used to emulate a HID Device - Mouse
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleRotary.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Pin A, Pin B, Button Pin
SimpleRotary rotary(9, 8, 7);

//Global Constants
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
int Page = 1; //Create a variable to track what page of macros are loaded

// the library will return the character inside this array
// when the appropriate button is pressed.

char keys[ROWS][COLS] = {

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};


byte rowPins[ROWS] = {10, 16, 14, 15}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {18, 19, 20, 21 }; //connect to the column pinouts of the keypad

int pageIndex = 0;
const int pageMax = 2;
const char* pages[] = {
  "Arduino\nIDE",
  "Fusion 360\nSketch",
  "Fusion 360\nConstraint"
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{

  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  Display(pages[pageIndex]);
}

void loop()
{
  Rotation();
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();

  if (key)
  {
    Serial.println(key);
  }
  switch (pageIndex)
  {
    case 0:
      Page0(key);
      break;
    case 1:
      Page1(key);
      break;
    case 2:
      Page2(key);
      break;
  }
}

void Rotation()
{
  byte i;

  // 0 = not turning, 1 = CW, 2 = CCW
  i = rotary.rotate();
  if (i != 0)
  {
    if (i = 1)
    {
      if ( pageIndex == pageMax)
      {
        pageIndex = 0;
      }
      else
      {
        pageIndex++;
      }
    }
    else if (i == 2)
    {

      if ( pageIndex == 0)
      {
        pageIndex = pageMax;
      }
      else
      {
        pageIndex--;
      }
    }
    Display(pages[pageIndex]);
  }
}
void Display(char* message)
{
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.write(message);
  display.display();
}

void Page0(char key)
{
  switch (key)
  {
    case '1':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write('t');
      Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write('r');
      Keyboard.releaseAll();
      break;
    case '3':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write('u');
      Keyboard.releaseAll();
      break;
  }
}
void Page1(char key)
{
  switch (key)
  {
    case '1':
      Keyboard.write('x');
      Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.write('l');
      Keyboard.releaseAll();
      break;
    case '3':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write('p');
      Keyboard.releaseAll();
      break;
    case 'A':
      Keyboard.write('p');
      Keyboard.releaseAll();
      break;
    case '4':
      Keyboard.write('d');
      Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.write('c');
      Keyboard.releaseAll();
      break;
  }
}
void Page2(char key)
{
  switch (key)
  {
    case '1':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('h');
      Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('c');
      Keyboard.releaseAll();
      break;
    case '3':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('t');
      Keyboard.releaseAll();
      break;
    case 'A':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('p');
      Keyboard.releaseAll();
      break;
    case '4':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('e');
      Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write('l');
      Keyboard.releaseAll();
      break;
  }
}
