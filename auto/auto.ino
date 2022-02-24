#include <Servo.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);  // 設定 LCD I2C 位址
Servo motor,motor2,motor3,motor4;
int trigPin = 12;                  //超音波
int echoPin = 11;                  //超音波
int trigPin2 = 4;                  //超音波2
int echoPin2 = 5;                  //超音波2
int button = 13;
int button2 =3;
long duration,cduration,cm,ccm;
int count=0,ccount=0;
void Distance(int);
void LCDcontrol(int);
void setup()
{
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);        
  pinMode(echoPin2, INPUT);
  pinMode(button,INPUT);
  pinMode(button2,INPUT);
  lcd.init();
  motor.attach(10);      // 腳位
  motor.write(160);      // 一開始先置中
  motor2.attach(9);      
  motor2.write(20);       
  motor3.attach(7);      
  motor3.write(0);                  
  motor4.attach(6);      
  motor4.write(180);     
  delay(2000);
}

void loop()
{
  if(digitalRead(button)==0) 
  {
    if(count<3)
    {
      Distance(1);
      if(cm<=8)
      {
        count++;
        Serial.print("count : ");
        Serial.print(count);
        Serial.println();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("bottle1 has been");
        lcd.setCursor(0, 1);
        lcd.print("used: ");
        lcd.print(count);
        lcd.print(" times");
        motor.write(0);                
        motor2.write(180);
        delay(1000);
        motor.write(160);                //伺服馬達置中
        motor2.write(20);                //伺服馬達置中
        delay(500);
      }
    }
    LCDcontrol(1);
  }
  else if (digitalRead(button)==1)                            //button==1
  {
    count=0;
    lcd.init();
    lcd.noBacklight();
   }
   
  if(digitalRead(button2)==0)
  {
    if(ccount<3)
    {
      Distance(2);
      if(ccm<=8)
      {
        ccount++;
        Serial.print("ccount : ");
        Serial.print(ccount);
        Serial.println();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("bottle2 has been");
        lcd.setCursor(0, 1);
        lcd.print("used: ");
        lcd.print(ccount);
        lcd.print(" times");
        motor3.write(180);                //伺服馬達置中
        motor4.write(0);
        delay(1000);
        motor3.write(0);                  //伺服馬達置中
        motor4.write(180);
        delay(500);    
      }
    }
    LCDcontrol(2);
  }
   else if( digitalRead(button2)==1)
   {
    ccount=0;
    lcd.init();
    lcd.noBacklight();
   }
    
}
void  Distance(int n)                //測距離 
{
  if(n==1)                           //酒精
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);             // 讀取 echo 的電位
    duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
    cm = (duration/2) / 29.1;            // 將時間換算成距離 cm   
    Serial.print("Distance : ");  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
  }
  else if(n==2)                        //護手霜
  {
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin2, HIGH);         // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    pinMode(echoPin2, INPUT);             // 讀取 echo 的電位
    cduration = pulseIn(echoPin2, HIGH);  // 收到高電位時的時間
    ccm = (cduration/2) / 29.1;           // 將時間換算成距離 cm   
    Serial.print("cDistance : ");  
    Serial.print(ccm);
    Serial.print("ccm");
    Serial.println();
    delay(100);
  }
}

void LCDcontrol(int n)
{
  if(n==1)
  {
    if(count>=3)
    {
      lcd.begin(16,2);
      lcd.backlight();              //開啟背光
      lcd.print("refill bottle1!");
    }
    else if(count>1)
    {
      lcd.begin(16,2);
      lcd.backlight();              //開啟背光
      lcd.print("bottle1 low fuel"); 
    }
  }
  else if(n==2)
  {
    if(ccount>=3)
    { 
      lcd.begin(16,2);
      lcd.backlight(); 
      lcd.print("refill bottle2!");
    }
    else if(ccount>1)
    {
      lcd.begin(16,2);
      lcd.backlight(); 
      lcd.print("botton2 low fuel"); 
    }
  }
}

 
  
