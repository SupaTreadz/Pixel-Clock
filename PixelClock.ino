#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"
#define PIN 7

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, PIN, NEO_GRB + NEO_KHZ800);
//////////////////////
int left_hour_one[] = {241,242,243,244,245,246};
//////////////////////
int right_hour_zero[] = {206,205,204,203,202,201,214,217,230,229,228,227,226,225,222,209};
int right_hour_one[] = {209,210,211,212,213,214};
int right_hour_two[] = {206,209,222,225,226,227,228,219,212,203,202,201,214,217,230};
int right_hour_three[] = {206,209,205,222,204,225,203,212,202,219,201,228,214,217,230};
int right_hour_four[] = {206,205,204,203,212,202,219,201,228,229,230};
int right_hour_five[] = {206,209,205,222,204,225,203,212,219,228,229,230,217,214,201};
int right_hour_six[] = {206,209,205,222,204,225,203,212,226,219,227,228,229,230,217,214,201};
int right_hour_seven[] = {206,205,204,203,202,201,214,217,230};
int right_hour_eight[] = {206,209,205,222,204,225,203,212,226,219,227,228,229,230,217,214,201,202};
int right_hour_nine[] = {206,205,204,203,212,202,219,201,228,214,229,217,230};
/////////////////////
int left_min_zero[] = {145,146,147,148,149,150,153,166,169,170,171,172,173,174,161,158};
int left_min_one[] = {158,157,156,155,154,153};
int left_min_two[] = {145,158,161,174,173,172,171,164,155,148,149,150,153,166,169};
int left_min_three[] = {174,161,158,145,146,147,148,155,149,164,150,171,153,166,169};
int left_min_four[] = {145,146,147,148,155,149,164,150,171,170,169};
int left_min_five[] = {174,161,158,145,146,147,148,155,164,171,170,169,166,153,150}; //166,153,150};
/////////////////////
int right_min_zero[] = {110,109,108,107,106,105,118,121,134,133,132,131,130,129,126,113};
int right_min_one[] = {126,125,124,123,122,121};
int right_min_two[] = {110,113,126,129,130,131,132,123,116,107,106,105,118,121,134};
int right_min_three[] = {129,126,113,110,109,108,107,116,106,123,105,132,118,121,134};
int right_min_four[] = {110,109,108,107,116,106,123,105,132,133,134};
int right_min_five[] = {129,126,113,110,109,108,107,116,123,132,133,134,121,118,105};
int right_min_six[] = {110,113,109,126,108,129,107,130,116,131,123,132,133,134,121,118,105};
int right_min_seven[] = {110,109,108,107,106,105,118,121,134};
int right_min_eight[] = {110,113,109,126,108,129,107,130,116,131,123,132,133,134,121,118,105,106};
int right_min_nine[] = {110,109,108,107,116,106,123,105,132,118,133,121,134};
/////////////////////
int M[] = {14,13,12,11,10,9,21,27,37,41,42,43,44,45,46}; 
int P[] = {60,59,58,57,70,73,86,85,84,83,76,82,67,81};
int A[] = {62,61,60,59,58,57,70,73,86,85,84,83,76,82,67,81};
///////////////////// 
uint32_t red = strip.Color(255,0,0);
uint32_t orange = strip.Color(255,100,0);
uint32_t yellow = strip.Color(255,255,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);
uint32_t purple = strip.Color(255,0,200);
uint32_t white = strip.Color(255,255,255);
uint32_t blank = strip.Color(0,0,0);
int wipespeed = 5;
int digitspeed = 5;
uint32_t timecolor = white;
uint32_t ampmcolor = green;
boolean am = false;
boolean pm = false;
uint32_t rainbowcolors[] = {red,orange,yellow,green,blue,purple};
uint32_t colorlist[] = {red,orange,yellow,green,blue,purple,white};
//Clock stuff
int hourtime = 0;
int displayhour = 0;
int minutetime = 0;
int firstminute = 0;
int secondminute = 0;
int oldminute = 0;
int oldfirstmin = 0;
int oldsecondmin = 0;
int oldhour = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("begun");
  rtc.begin();
  strip.begin();
  strip.setBrightness(15);
  strip.show();
}

void loop() 
{
  Serial.println("test1");
  DateTime now = rtc.now();
  String daything = daysOfTheWeek[now.dayOfTheWeek()];
  String printableday = daything.substring(0,3);
  hourtime = now.hour();
  Serial.println(hourtime);
  displayhour = hourtime;
  minutetime = now.minute();
  firstminute = minutetime/10;
  secondminute = minutetime - (minutetime/10)*10;
  
  if(minutetime != oldminute)
  {
    if(minutetime == 0 && oldminute == 9)
    {
      colorWipeRainbow(wipespeed); 
      clearpixels();
    }
    else
    {
      clearpixels();
    }
    timecolor = colorlist[random(0,8)];
  }
  oldminute = minutetime;
  oldfirstmin = firstminute;
  oldsecondmin = secondminute;
  
  if(hourtime != oldhour)
  {
    rainbowCycle(wipespeed);
    clearpixels();  
  }
  oldhour = hourtime;
  
  if(hourtime >=13)
  {
    ampmcolor = orange;
    displayhour = hourtime - 12;
    pm = true;
    am = false;
    setPM(ampmcolor,digitspeed);
  }
  else
  {
    if(hourtime == 0)
    {
      displayhour = 12;
    }
    ampmcolor = green;
    am = true;
    pm = false;
    setAM(ampmcolor,digitspeed);
  }
 
  if(displayhour >= 10)
  {
    set_left_hour(1,timecolor,digitspeed);
    set_right_hour(displayhour-10,timecolor,digitspeed);
  }
  else
  {
    set_left_hour(0,timecolor,digitspeed);
    set_right_hour(displayhour,timecolor,digitspeed);
  }
  colon(timecolor);
  set_left_min(firstminute,timecolor,digitspeed);
  set_right_min(secondminute,timecolor,digitspeed);
  //delay(3000);
}

void clearpixels()
{
  colorWipe(blank,wipespeed);
}
void set_left_hour(int num, uint32_t c, int wait)
{
  if(num==1)
  {
    for(int i=0; i<sizeof(left_hour_one)/2; i++)
    {
      strip.setPixelColor(left_hour_one[i], c);
      strip.show();
      delay(wait);
    }
  }
}

void set_right_hour(int num, uint32_t c, int wait)
{
  if(num==0)
  {
    for(int i=0; i<sizeof(right_hour_zero)/2; i++)
    {
      strip.setPixelColor(right_hour_zero[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==1)
  {
    for(int i=0; i<sizeof(right_hour_one)/2; i++)
    {
      strip.setPixelColor(right_hour_one[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==2)
  {
    for(int i=0; i<sizeof(right_hour_two)/2; i++)
    {
      strip.setPixelColor(right_hour_two[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==3)
  {
    for(int i=0; i<sizeof(right_hour_three)/2; i++)
    {
      strip.setPixelColor(right_hour_three[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==4)
  {
    for(int i=0; i<sizeof(right_hour_four)/2; i++)
    {
      strip.setPixelColor(right_hour_four[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==5)
  {
    for(int i=0; i<sizeof(right_hour_five)/2; i++)
    {
      strip.setPixelColor(right_hour_five[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==6)
  {
    for(int i=0; i<sizeof(right_hour_six)/2; i++)
    {
      strip.setPixelColor(right_hour_six[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==7)
  {
    for(int i=0; i<sizeof(right_hour_seven)/2; i++)
    {
      strip.setPixelColor(right_hour_seven[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==8)
  {
    for(int i=0; i<sizeof(right_hour_eight)/2; i++)
    {
      strip.setPixelColor(right_hour_eight[i], c);
      strip.show();
      delay(wait);
    }
  }
  else
  {
    for(int i=0; i<sizeof(right_hour_nine)/2; i++)
    {
      strip.setPixelColor(right_hour_nine[i], c);
      strip.show();
      delay(wait);
    }
  }
}

void colon(uint32_t c)
{
  int setcolon[] = {189,186};
  strip.setPixelColor(189, c);
  strip.setPixelColor(186, c);
  strip.show();    
}

void set_left_min(int num, uint32_t c, int wait)
{
  if(num==0)
  {
    for(int i=0; i<sizeof(left_min_zero)/2; i++)
    {
      strip.setPixelColor(left_min_zero[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==1)
  {
    for(int i=0; i<sizeof(left_min_one)/2; i++)
    {
      strip.setPixelColor(left_min_one[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==2)
  {
    for(int i=0; i<sizeof(left_min_two)/2; i++)
    {
      strip.setPixelColor(left_min_two[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==3)
  {
    for(int i=0; i<sizeof(left_min_three)/2; i++)
    {
      strip.setPixelColor(left_min_three[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==4)
  {
    for(int i=0; i<sizeof(left_min_four)/2; i++)
    {
      //strip.setPixelColor(left_min_four[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==5)
  {
    for(int i=0; i<sizeof(left_min_five)/2; i++)
    {
      //strip.setPixelColor(left_min_five[i], c);
      strip.show();
      delay(wait);
    }
  }
}

void set_right_min(int num, uint32_t c, int wait)
{
  if(num==0)
  {
    for(int i=0; i<sizeof(right_min_zero)/2; i++)
    {
      //strip.setPixelColor(right_min_zero[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==1)
  {
    for(int i=0; i<sizeof(right_min_one)/2; i++)
    {
      //strip.setPixelColor(right_min_one[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==2)
  {
    for(int i=0; i<sizeof(right_min_two)/2; i++)
    {
      //strip.setPixelColor(right_min_two[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==3)
  {
    for(int i=0; i<sizeof(right_min_three)/2; i++)
    {
      //strip.setPixelColor(right_min_three[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==4)
  {
    for(int i=0; i<sizeof(right_min_four)/2; i++)
    {
      //strip.setPixelColor(right_min_four[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==5)
  {
    for(int i=0; i<sizeof(right_min_five)/2; i++)
    {
      //strip.setPixelColor(right_min_five[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==6)
  {
    for(int i=0; i<sizeof(right_min_six)/2; i++)
    {
      //strip.setPixelColor(right_min_six[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==7)
  {
    for(int i=0; i<sizeof(right_min_seven)/2; i++)
    {
      //strip.setPixelColor(right_min_seven[i], c);
      strip.show();
      delay(wait);
    }
  }
  else if(num==8)
  {
    for(int i=0; i<sizeof(right_min_eight)/2; i++)
    {
      //strip.setPixelColor(right_min_eight[i], c);
      strip.show();
      delay(wait);
    }
  }
  else
  {
    for(int i=0; i<sizeof(right_min_nine)/2; i++)
    {
      //strip.setPixelColor(right_min_nine[i], c);
      strip.show();
      delay(wait);
    }
  }
}

void setAM(uint32_t c, int wait)
{
  for(int i=0; i<sizeof(A)/2; i++)
  {
    strip.setPixelColor(A[i], c);
    strip.show();
    delay(wait);
  }
  for(int i=0; i<sizeof(M)/2; i++)
  {
    strip.setPixelColor(M[i], c);
    strip.show();
    delay(wait);
  }
}
void setPM(uint32_t c, int wait)
{
  for(int i=0; i<sizeof(P)/2; i++)
  {
    strip.setPixelColor(P[i], c);
    strip.show();
    delay(wait);
  }
  for(int i=0; i<sizeof(M)/2; i++)
  {
    strip.setPixelColor(M[i], c);
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipeRainbow(uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
      strip.setPixelColor(i, rainbowcolors[i % 6]);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void testMode()
{
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(1,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(1,timecolor,digitspeed);
  set_right_min(1,timecolor,digitspeed);
  setPM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(2,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(2,timecolor,digitspeed);
  set_right_min(2,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(3,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(3,timecolor,digitspeed);
  set_right_min(3,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(4,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(4,timecolor,digitspeed);
  set_right_min(4,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(5,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(5,timecolor,digitspeed);
  set_right_min(5,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(6,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(0,timecolor,digitspeed);
  set_right_min(6,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(7,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(0,timecolor,digitspeed);
  set_right_min(7,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(8,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(0,timecolor,digitspeed);
  set_right_min(8,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(9,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(0,timecolor,digitspeed);
  set_right_min(9,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  clearpixels();
  set_left_hour(1,timecolor,digitspeed);
  set_right_hour(0,timecolor,digitspeed);
  colon(timecolor);
  set_left_min(0,timecolor,digitspeed);
  set_right_min(0,timecolor,digitspeed);
  setAM(ampmcolor,digitspeed);
  delay(1000);
  //rainbowCycle(wipespeed);
  //delay(1000);
}
