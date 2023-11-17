#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 95
#define PENRADIUS 3
int oldbus, currentbus;

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);


void screen() {
   display.setHanFont(1);
   display.setEngFont(1);
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.setCursor(0, 0);
   display.print_string("버스 배차 정보");

   display.setHanFont(1);
   display.setEngFont(1);
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.setCursor(BOXSIZE-45, 0);
   display.print_string("62번 버스");

   display.setHanFont(1);
   display.setEngFont(1);
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.setCursor(BOXSIZE+50, 0);
   display.print_string("150번 버스");
}

void setup(void) {
  Serial.begin(9600);
  
  tft.reset();

  tft.begin(identifier);

  tft.fillScreen(BLACK);

  tft.fillRect(0, 0, 50, 320, YELLO); //버스 배차 정보
  tft.fillRect(BOXSIZE-45, 0, BOXSIZE, 320, WHITE); //버스 번호 190
  tft.fillRect(BOXSIZE+50, 0, BOXSIZE, 320, WHITE); //버스 번호 95
 
  pinMode(13, OUTPUT);

  screen();
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000
byte c;

void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    if (p.x > 50) {
       if (p.x < BOXSIZE+50) { 
         tft.drawRect(BOXSIZE-45, 0, BOXSIZE, 320, BLUE); //선택한 버스에 네모 표시
         mySerial.write('g');
         
       } else if (p.x < 240) {
         tft.drawRect(BOXSIZE+50, 0, BOXSIZE, 320, WHITE); //선택한 버스에 네모 표시
       }
    }
  }
}
