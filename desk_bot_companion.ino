#include <ESP32Servo.h>
#include <M5Core2.h>
#include <driver/i2s.h>
#include <WiFi.h>

#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

#define OUTPUT_GAIN 10
Servo myservo1; 
Servo myservo2;
#define TFT_GREY 0x5AEB
RTC_TimeTypeDef RTCtime;
RTC_TimeTypeDef RTCtime_Now;
uint32_t init_time;
char timeStrbuff[64];
int flag=1;
int p1=0,p2=0;
int servoPin1 = 14; //Right 180->Down  , 0->Up
int servoPin2 = 13; //Left   0->Down   , 180->Down

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  myservo1.setPeriodHertz(50);   
  myservo1.attach(servoPin1, 500, 2400);
  myservo2.setPeriodHertz(50); 
  myservo2.attach(servoPin2, 500, 2400);
  M5.begin();
//  M5.Lcd.setBrightness(10);
  M5.Axp.SetSpkEnable(true);

  WiFi.mode(WIFI_OFF); 
  delay(500);

  delay(500);

//  M5.Lcd.setTextFont(2);
//  M5.Lcd.printf("Sample MP3 playback begins...\n");
  
  file = new AudioFileSourceSD("/sponge.mp3");
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 0); // Output to builtInDAC
  out->SetPinout(12, 0, 2);
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  M5.Lcd.drawJpgFile(SD, "/b.jpg");


//  if (mp3->isRunning()) {
//    if (!mp3->loop()) {
//      mp3->stop();
//    }
//  } else {
//    file = new AudioFileSourceSD("/sponge.mp3");
//    id3 = new AudioFileSourceID3(file);
//    mp3 = new AudioGeneratorMP3();
//    mp3->begin(id3, out);
//  }
}

void loop() {
    time_show();

    M5.Lcd.drawJpgFile(SD, "/a1.jpg");
    dance();
    cheer_up();

    M5.Lcd.drawJpgFile(SD, "/a2.jpg");
    dance();
    cheer_up();
    dance();
    
    M5.Lcd.drawJpgFile(SD, "/a3.jpg");
    cheer_up();
    dance();

    M5.Lcd.drawJpgFile(SD, "/a4.jpg");
    dance();
    cheer_up();
    dance();


  
}
void time_show(){
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  init_time=millis();
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(60,20);
  if(flag==0){
    M5.Lcd.println("Meeting Time");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0,140);
    M5.Lcd.println("Time Left : 03 - 55");
    flag=1;
  }
  if(flag==1){
    M5.Lcd.println("Lunch Time");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0,140);
    M5.Lcd.println("Time Left : 02 - 15");
    flag=2;
  }
  if(flag==2){
    M5.Lcd.println("Go Home Time");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0,140);
    M5.Lcd.println("Time Left : 06 - 15");
    flag=0;
  }
  
//  else{
//    M5.Lcd.println("Lunch Time");
//    flag=1;
//  }
//  M5.Lcd.setTextSize(3);
  

//  while(millis()-init_time<6000){
//  M5.Lcd.setCursor(0,140);
//  M5.Lcd.println("Time Left : 02 - 45");
//M5.Rtc.GetTime(&RTCtime_Now);
//  sprintf(timeStrbuff,"Time: %02d:%02d:%02d",
//         RTCtime_Now.Hours,RTCtime_Now.Minutes,RTCtime_Now.Seconds);
//  M5.Lcd.println(timeStrbuff);
//}

  
  
}
void init_servo(){
    myservo2.write(90); 
    myservo1.write(90); 
    delay(1000);
}
void cheer_up(){
  init_servo();
  for (p1= 90,p2=90; p1<=180; p1+= 1,p2-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p2= 0,p1=180; p2<=90; p2+= 1,p1-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p1= 90,p2=90; p1<=180; p1+= 1,p2-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p2= 0,p1=180; p2<=90; p2+= 1,p1-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
}
void dance(){
  myservo2.write(90); 
  myservo1.write(180); 
  delay(1000);
  for (p1= 180,p2=90; p2>0; p1-= 1,p2-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p2= 0,p1=90; p2<=90; p2+= 1,p1+=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p1= 180,p2=90; p2>0; p1-= 1,p2-=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
  for (p2= 0,p1=90; p2<=90; p2+= 1,p1+=1) { 
    myservo1.write(p1); 
    delay(5);
    myservo2.write(p2); 
    delay(5);             
  }
}
static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
