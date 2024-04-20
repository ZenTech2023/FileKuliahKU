#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

RTC_DS1307 rtc;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI D10
#define OLED_CLK D8
#define OLED_DC D2
#define OLED_CS D3
#define OLED_RESET D1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
/*
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
*/

char intro[] = "Aku sudah pernah merasakan semua kepahitan dalam hidup dan yang paling pahit ialah berharap kepada manusia - Ali bin Abi Thalib";
int x, minX;

void Selamatdatang() {
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("DIY");
  display.setCursor(0, 30);
  display.println("TIME CLOCK");
  display.display();
}


void ClockDisplay() {
  DateTime now = rtc.now();
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print(String(now.hour()) + ":" + String(now.minute()));
  display.setTextSize(2);
  display.setCursor(9, 0);
  display.println(String(now.day()) + "-" + String(now.month()) + "-" + String(now.year()));  //+"-"+String(currentYear)

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(115, 0);
  display.print(String(now.second()));
}

void textScroll() {
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, 55);
  display.print(intro);
  x = x - 1;
  if (x < minX) x = display.width();
  delay(50);
}
void setup() {
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();  // Initialize and clear the display
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);
  //display.dim(100);
  x = display.width();
  minX = -6 * strlen(intro);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    rtc.adjust(DateTime(2024,04,18,15,47,0));
    Serial.flush();
    while (1) delay(10);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  ClockDisplay();
  textScroll();
  display.display();
}
