/*
  RGBLedExample
  Example for the RGBLED Library
  Created by Bret Stateham, November 13, 2014
  You can get the latest version from http://github.com/BretStateham/RGBLED
*/
#include <RGBLED.h>

// Declare an RGBLED instanced named rgbLed
// Red, Green and Blue LED legs are connected to PWM pins 11,9 & 6 respectively
// In this example, we have a COMMON_ANODE LED, use COMMON_CATHODE otherwise
unsigned long time=0;


struct lightcolor {
  int red;
  int green;
  int blue;
};

RGBLED rgbLed1(2,3,0,COMMON_CATHODE);//need this block for each LED
lightcolor lcol1={255,150,0};
struct lightcolor *ptlcol1=&lcol1;
unsigned long flatime1 = 0;
unsigned long *ftime1 = &flatime1;


RGBLED rgbLed2(7,6,0,COMMON_CATHODE);
struct lightcolor lcol2 = {255,150,0};
struct lightcolor *ptlcol2 = &lcol2;
unsigned long flatime2 = 0;
unsigned long *ftime2 = &flatime2;


RGBLED rgbLed3(12,10,0,COMMON_CATHODE);
struct lightcolor lcol3 = {255,150,0};
struct lightcolor *ptlcol3 = &lcol3;
unsigned long flatime3 = 0;
unsigned long *ftime3 = &flatime3;


RGBLED rgbLed4(5,4,0,COMMON_CATHODE);//need this block for each LED
lightcolor lcol4={255,150,0};
struct lightcolor *ptlcol4=&lcol4;
unsigned long flatime4 = 0;
unsigned long *ftime4 = &flatime4;


RGBLED rgbLed5(9,8,0,COMMON_CATHODE);
struct lightcolor lcol5 = {255,150,0};
struct lightcolor *ptlcol5 = &lcol5;
unsigned long flatime5 = 0;
unsigned long *ftime5 = &flatime5;


RGBLED rgbLed6(11,13,0,COMMON_CATHODE);
struct lightcolor lcol6 = {255,150,0};
struct lightcolor *ptlcol6 = &lcol6;
unsigned long flatime6 = 0;
unsigned long *ftime6 = &flatime6;


struct lightcolor lcolgreen = {0, 255, 0};
struct lightcolor lcolred = {255, 0, 0};
int buttonState = 0; //make sure signal sent for a second or so, input pin goes to boo box
int buttonPin = 1;
int ms_delay = 5;
unsigned long countdown = 120000; //time for red in milliseconds (multiply by 1000)

//How long to show each color in the example code (in milliseconds);
int delayMs = 1000;

void setup() {
  //Initialize Serial communications
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  //digitalWrite(buttonPin,HIGH);
}

void loop() {

  //The code in the loop shows multiple exampls

  //Set the RGBLED to show RED only
  //printRgbValues() prints various LED values to the Serial port
  //you can monitor the serial port to see the values printed
  //The delay(delayMs) waits for 1 second to be able to see the color shown
  //rgbLed.writeRGB(255,0,0);
  //printRgbValues();
  //Serial.println("Values: " + String(rgbLed.redMappedValue));
  //delay(delayMs);
  time = millis();
  colPicker(ptlcol1,50);
  colPicker(ptlcol2,80);
  colPicker(ptlcol3,20);
  buttonState = digitalRead(buttonPin);
  Serial.println(digitalRead(buttonPin));
  if (buttonState == LOW) {
    while (time+countdown >=millis()){
      rgbLed1.writeRGB(255,0,0);
      rgbLed2.writeRGB(255,0,0);
      rgbLed3.writeRGB(255,0,0);
        for (int i=0; i <= 255; i++){
          rgbLed4.writeRGB(i, 0, 0);
          rgbLed5.writeRGB(i, 0, 0);
          rgbLed6.writeRGB(i, 0, 0);
          delay(ms_delay);
        }
        delay(ms_delay);
        for (int i=255; i >= 0; i--){
          rgbLed4.writeRGB(i, 0, 0);
          rgbLed5.writeRGB(i, 0, 0);
          rgbLed6.writeRGB(i, 0, 0);
          delay(ms_delay);
        }
    }
    digitalWrite(buttonPin,HIGH);
  } else {
    flash(rgbLed1,random(1000),random(3000),lcol1,ftime1);
    flash(rgbLed2,random(20000),random(40000),lcol2,ftime2);
    flash(rgbLed3,random(40000),random(20000),lcol3,ftime3);
    flash(rgbLed4,random(40000),random(4000),lcol4,ftime4);
    flash(rgbLed5,random(4000),random(40000),lcol5,ftime5);
    flash(rgbLed6,random(10000),random(40000),lcol6,ftime6);
  }
}

void flash(RGBLED &led, int on_time, int off_time, struct lightcolor theColor, unsigned long *flashtime)
{
  if(led.redValue + led.greenValue > 0)
  {
    if (time - *flashtime >= on_time)//assess how long it's been
    {
      led.turnOff();
      *flashtime = time;
    }
  }
  else
  {
    if (time - *flashtime >= off_time)//assess how long it's been
    {
     led.writeRGB(theColor.red,theColor.green,theColor.blue);
     *flashtime = time;
    }
  }
}

void colPicker(struct lightcolor *ptcolor, int chanceYel){
  if (chanceYel >= random(100)){
    *ptcolor = {255,25,0};
  } else {
    *ptcolor = {0,255,0};
  }
}

void printRgbValues(RGBLED &rgbLed) {
  Serial.println("Requested RGB Values:");
  Serial.println("(r,g,b)=(" + String(rgbLed.redValue) + "," + String(rgbLed.greenValue) + "," + String(rgbLed.blueValue) + ")");
  Serial.println("Mapped RGB Values based on type (COMMON_ANODE or COMMON_CATHODE):");
    Serial.println("Mapped(r,g,b)=(" + String(rgbLed.redMappedValue) + "," + String(rgbLed.greenMappedValue) + "," + String(rgbLed.blueMappedValue) + ")");
    Serial.println("------------------------------");
}
