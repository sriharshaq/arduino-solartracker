#include "gsmModem.h"
#include "sensors.h"
#include "config.h"
#include "TimerOne.h"
#include "appmsg.h"
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Wire.h>
#include "pcf8591.h"
#include "RTClib.h"

// Globals for Timer Calculation
volatile unsigned int ms = 0;
volatile unsigned int ss = 0;

#define ADJUST_RTC

#ifdef ADJUST_RTC
#define DATE "Feb 03 2014"
#define TIME "22:08:00"
#endif

void timer1Isr(void)          // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  ms++;
  if(ms >= 1000)
  {
    ms = 0;
    ss++;
  }
}

// An instance of a LiquidCrystal class (Object)
LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
// An instance of gsm modem class
gsmModem myModem;
// An instance of Sensors class
Sensors mySensors;
// An instance for stepper motor

// An instance of rtc
RTC_DS1307 rtc;


void setup(void)
{ 
  pinMode(LDR1,INPUT);
  pinMode(LDR2,INPUT);
  pinMode(LDR3,INPUT);
  pinMode(LDR4,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  mySensors.begin();
  Wire.begin();
  rtc.begin();
  
  #ifdef ADJUST_RTC
  rtc.adjust(DateTime(DATE, TIME));
  #endif
  
  lcd.setCursor(0,0);
  
  // Attach stepper motor pin
  ///////////////////////////
  ///////////////////////////
  
  // Timer 1
  Timer1.initialize(Timeus);
  Timer1.attachInterrupt(timer1Isr);
}

void loop(void)
{
float _humi,_ldr1,_ldr2,_ldr3,_ldr4,_temp;
float current;
float Voltage;
int Status;
//unsigned char a1,a2,a3,a4;
//unsigned char buff[5];
DateTime now = rtc.now();

/*while(1)
{
 _humi = mySensors.getHumi();
_temp = mySensors.getTemp(DEGC);
current = mySensors.getCurrent();
now = rtc.now();
Serial.print(_temp);
Serial.write(9);
Serial.print(_humi);
Serial.write(9);
Serial.print(current);
Serial.write(9);
Serial.print(now.minute());
Serial.write(9);
Serial.print(now.second());
Serial.println();
delay(1000);
}*/

// Boot Test
#ifndef DEBUG
bootTest();
#endif

// Infinite loop (It will run continuosly)
while(1)
{
// Read All the datas
_humi = mySensors.getHumi();
_temp = mySensors.getTemp(DEGC);
_ldr1 = mySensors.getLight(1);
_ldr2 = mySensors.getLight(2);
_ldr3 = mySensors.getLight(3);
_ldr4 = mySensors.getLight(4);

// Alert Condition
if(_humi > HUMID_UPPER_LIMIT || _humi < HUMID_LOWER_LIMIT || _temp > TEMPR_UPPER_LIMIT || _temp < TEMPR_LOWER_LIMIT)
{
  #if ALERT_TYPE == 0
  myModem.connectCall(USER_NO);
  ////////////////// Display LCD
  ////////////////// Add here
  
  #elif ALERT_TYPE == 1 || ALERT_TYPE == 2 || ALERT_TYPE == 3
  if(_humi > HUMID_UPPER_LIMIT)
  {
    Status = 0;
  }
  else if(_humi < HUMID_LOWER_LIMIT)
  {
    Status = 1;
  }
  else if(_temp > TEMPR_UPPER_LIMIT )
  {
    Status = 2;
  }
  else if(_temp < TEMPR_LOWER_LIMIT)
  {
    Status = 3;
  }
  else
  {
     Status = 4;
  }
  
   if(Status == 0)
   {
             #if ALERT_TYPE == 1
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG1);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 2
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(DAQ_SERVER_NO,USERMSG1);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 3
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG1);
             myModem.sendSms(DAQ_SERVER_NO,USERMSG1);
             ////////////////// Display LCD
             ////////////////// Add here
             #endif
   }
   else if(Status == 1)
   {
             #if ALERT_TYPE == 1
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG2);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 2
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(DAQ_SERVER_NO,USERMSG2);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 3
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG2);
             myModem.sendSms(DAQ_SERVER_NO,USERMSG2);
             ////////////////// Display LCD
             ////////////////// Add here
             #endif
   }
    else if(Status == 2)
    {
             #if   ALERT_TYPE == 1
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG3);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 2
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(DAQ_SERVER_NO,USERMSG3);
             ////////////////// Display LCD
             ////////////////// Add here 
             #elif ALERT_TYPE == 3
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG1);
             myModem.sendSms(DAQ_SERVER_NO,USERMSG3);
             ////////////////// Display LCD
             ////////////////// Add here
             #endif
    }
    else if(Status == 3)
        {
             #if   ALERT_TYPE == 1
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG4);
             ////////////////// Display LCD
             ////////////////// Add here
             #elif ALERT_TYPE == 2
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(DAQ_SERVER_NO,USERMSG4);
             #elif ALERT_TYPE == 3
             ////////////////// Display LCD
             ////////////////// Add here
             myModem.sendSms(USER_NO,USERMSG4);
             myModem.sendSms(DAQ_SERVER_NO,USERMSG4);
             ////////////////// Display LCD
             ////////////////// Add here
             #endif
        }
    else
    {
      // Its invalid
      // Dummy entry
    }
  
   // Put Invalid entry value for status
   Status = 10;
  
   // Through an error      
   #else
   #error "Invalid 'ALERT_TYPE' macro"  
   
   #endif
}

// Data Logging Condition
if(ss >= DATA_LOG_SMS_INTERVAL)
{
  // temporary disable interrupt and stop the timer
/*  Timer1.detachInterrupt();       // stop timer interrupt
  Timer1.stop();*/
  // Clear Counts
/*  ss = 0;
  ms = 0;*/
  
// Add Solar Power Measurement Logic here
/////////////////////////////////////////
/////////////////////////////////////////

  #if DATA_LOG_MODE == 0
  // Send Data to DAQ_NO
  #elif DATA_LOG_MODE == 1
  // Send to User mobile
  #elif DATA_LOG_MODE == 2
  // Send to both
  
  // Through an error
  #else
  #error "Inavlid 'DATA_LOG_MODE' macro"
  
  #endif
}

// Solar panel rotation logic
// Add Logic here
///////////////////////////////////////////////
///////////////////////////////////////////////


// For debugging
#ifdef DEBUG
Serial.print(_humi);
Serial.write(0x09);
Serial.print(_temp);
Serial.write(0x09);
Serial.print(_ldr1);
Serial.write(0x09);
Serial.print(_ldr2);
Serial.write(0x09);
Serial.print(_ldr3);
Serial.write(0x09);
Serial.print(_ldr4);
Serial.write(0x09);
Serial.println();
delay(_DEBUG_UART_PRINT_DELAY_);
#endif
}
}

void bootTest(void)
{
  unsigned char i = 0;
  lcd.setCursor(0,0);
  lcd.print(BOOTMSG1);
  
  
  lcd.setCursor(0,1);
  for(i = 0;i<16;i++)
  {
      lcd.write('.');
      delay(LCD_INITIAL_SLOW_DELAY);
  }
  delay(StartUpDelay);
  lcd.clear();
  
  #ifdef DEBUG
  Serial.println();
  #endif
  
  // GSM Modem test
  // If detected
  if(myModem.detectModem() == 1)         
  {
  lcd.print(BOOTMSG2);
  
  #ifdef DEBUG
  Serial.println(BOOTMSG2);
  #endif
  
  ss = 0;
  #ifdef STARTUP_ALERT_SMS == 1
  myModem.sendSms(DAQ_SERVER_NO,START_UP_ALERT_SMS);
  #elif  STARTUP_ALERT_SMS == 2
  myModem.sendSms(USER_NO,START_UP_ALERT_SMS);
  #elif  STARTUP_ALERT_SMS == 3
  myModem.sendSms(DAQ_SERVER_NO,START_UP_ALERT_SMS);
  myModem.sendSms(USER_NO,START_UP_ALERT_SMS);
  
  // Through an error
  #else
  #error "Invalid value for 'STARTUP_ALERT_SMS' macro"
  
  #endif
  }
  // If not detected
  else
  {
  lcd.print(BOOTMSG3);

  #ifdef DEBUG
  Serial.println(BOOTMSG3);
  #endif  

  lcd.setCursor(0,1);
  lcd.print(BOOTMSG4);
  
  #ifdef DEBUG
  Serial.println(BOOTMSG4);
  #endif
  
  ss = 0;
  Timer1.detachInterrupt();       // stop timer interrupt
  Timer1.stop();
  // Infinite loop
  while(true)
  {
    ;
  } 
  }
  
  delay(StartUpDelay);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(BOOTMSG5);

  #ifdef DEBUG
  Serial.println(BOOTMSG5);
  #endif
  
  lcd.setCursor(0,1);
  lcd.print(BOOTMSG6);

  #ifdef DEBUG
  Serial.println(BOOTMSG6);
  #endif
  
  delay(StartUpDelay);
  lcd.clear();
}
