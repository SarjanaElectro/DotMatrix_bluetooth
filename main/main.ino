
#include <SoftwareSerial.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


textEffect_t texteffect[] =
{
  PA_PRINT,
  PA_WIPE_CURSOR,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_SCROLL_RIGHT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP_RIGHT,
  PA_SCROLL_UP,
  PA_SCROLL_DOWN,
  PA_GROW_UP,
  PA_GROW_DOWN,
  PA_DISSOLVE,
  PA_MESH,
  PA_OPENING_CURSOR,
  PA_CLOSING_CURSOR,
  PA_SLICE,
  PA_BLINDS,
  PA_RANDOM,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_SCROLL_DOWN_RIGHT,
  PA_CLOSING,
  PA_OPENING,
};

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10
#define BUF_SIZE 50
char text[BUF_SIZE] = "";
SoftwareSerial Bluetooth(0, 1); // RX, TX
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Bluetooth.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  // myDisplay.setTextAlignment(PA_CENTER);
  // myDisplay.setPause(1000);
  // myDisplay.setSpeed(100);
  myDisplay.displayClear();
}
void loop() {
   readSerial();
  if (myDisplay.displayAnimate()) {
    myDisplay.displayText(text, PA_LEFT, 100, 100, texteffect[3], texteffect[3]);
    myDisplay.displayReset();
  }
}

void readSerial(void)
{
  static uint8_t count = 0;
 while (Bluetooth.available()) 
 {
        text[count] = Bluetooth.read();
        if((text[count] == '\n') || (count >= BUF_SIZE-3))
        {
          text[count++] = ' ';
          text[count] = '\0';
          count = 0;
        }
        else if(text[count]!= '\r')
        count++;
      }
}
