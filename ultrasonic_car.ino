                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 #include<Servo.h> 
#include<Wire.h> //IIC Communication Library File 
#include<LiquidCrystal_I2C.h> //1602 screen IIC communication library file 
LiquidCrystal_I2C lcd(0x27,16,2);//instantiate an LCD class with address 0x27 
Servo myservo;//instantiate a steering gear class 
#define INT_A 4//Define the pin D4 that controls the direction of the left motor 
#define INT_B 2//Define the pin D2 that controls the direction of the right motor 
#define left_A 6//Define the pin D6 that controls the speed(PWM)of the left motor 
#define right_B 5//Define pinD5 to control the speed of the right motor(PWM) 
#define buzzer A2//Define pin A2 to control the buzzer 
#define Echo 13 //Define ultrasonic receive pulse width pin 
#define Trigger 12 //efine ultrasonic trigger pin 
#define distance_minimum 25 
float distance,distance_10,distance_170; 
int Speed_FB=60; 
int Speed_LR=60; 
int randNumber=0; 
void setup() 
{
  Serial.begin(9600); //Set the serial port baud rate to 9600 
  delay(100); //elay 100ms 
  pinMode(INT_A,OUTPUT); //Set the pins of the control motor to the output state 
  pinMode(INT_B,OUTPUT);
  pinMode(left_A,OUTPUT); 
  pinMode(right_B,OUTPUT); 
  pinMode(buzzer,OUTPUT); 
  pinMode(Echo,INPUT); 
  pinMode(Trigger,OUTPUT); 
  myservo.attach(11);//Set pinD11 control servo 
  myservo.write(90);//Initialize the servo to 90//' degrees 
  lcd.init(); //Initialize the 1602LCD screen 
  lcd.backlight(); //Off 1602 LCD screen backlight 
  lcd.setCursor(2,0); //The cursor is set to the 3rd position on the 1st line 
  lcd.print("HI I AM LORBBI"); //Display "HI I AM LORBBI" from the 3rd position on the 1st line 
  lcd.setCursor(0,1); //The cursor is set to the first position on the 2nd line 
  lcd.print("COZMO ROBOTS");//COZMO ROBOTS" is displayed from the 1st position on the 2nd line.
  } 
  ///////////////////////////////////////////////////////// 
  void loop() 
  {
    ultrasonic_distance(); //Serial.println(distance); if(distance>distance_minimum)
    {
      front(); //??????????????????front()??? 
      }
      if(distance<=distance_minimum)
{ 
  Stop(); //stop 
  digitalWrite(buzzer,HIGH); 
  delay(250); 
  digitalWrite(buzzer,LOW); 
  servo_wheel(); 
  if((distance_10<=distance_minimum)&&(distance_170<=distance_minimum)) 
  {back();delay(250);}
  if(distance_10<distance_170) 
  {left();}
  if(distance_10>distance_170) 
  {right();}
  if(distance_10==distance_170) 
  { 
    randNumber=random(1,2);//Generate random numbers 
    if(randNumber==1) 
    {left();}
    if(randNumber==2) 
    {right();}
    }
    delay(250);
    Stop();    //??????}
    } 
  }
  ///////////////////////////////////////////////////////////goforward 
  void front() 
  {
    digitalWrite(INT_A,LOW); //Control left motor forward
    digitalWrite(INT_B,HIGH); //Control right motor forward 
    analogWrite(left_A,Speed_FB); //Set the speed of the left and right motors (PWM=200) 
    analogWrite(right_B,Speed_FB);} ///////////////////////////////////////////////////////////back 
    void back() 
    {
      digitalWrite(INT_A,HIGH); //Control left motor reversal 
      digitalWrite(INT_B,LOW); //Control right motor reversal 
      analogWrite(left_A,Speed_FB); 
      analogWrite(right_B,Speed_FB);
      } 
      ///////////////////////////////////////////////////////////ture left 
      void left() 
      {
        digitalWrite(INT_A,LOW); //Control left motor forward 
        digitalWrite(INT_B,LOW); //Control right motor reversal 
        analogWrite(left_A,Speed_LR); 
        analogWrite(right_B,Speed_LR);
        } 
        ///////////////////////////////////////////////////////////ture right 
        void right() 
        {
          digitalWrite(INT_A,HIGH); //Control left motor reversal 
          digitalWrite(INT_B,HIGH); //Control right motor forward 
          analogWrite(left_A,Speed_LR); //The speed of the left and right motors (PWMis100) 
          analogWrite(right_B,Speed_LR);
    }
    ///////////////////////////////////////////////////////////stop 
    void Stop() 
    {
      digitalWrite(INT_A,LOW); 
      digitalWrite(INT_B,LOW); 
      analogWrite(left_A,0); //The PWM on both the left and the right is 0 
      analogWrite(right_B,0);
      } 
      ///////////////////////////////////////////////////////////Ultrasonic ranging 
      void ultrasonic_distance() 
      {
        delay(100); 
        digitalWrite(Trigger,HIGH); 
        delayMicroseconds(10); 
        digitalWrite(Trigger,LOW); 
        distance=pulseIn(Echo,HIGH)*34/2000.0; 
        if(distance==0) 
        distance=300;
        delay(100);
        } 
        ///////////////////////////////////////////////////////////Steering wheel rotation 
        void servo_wheel() 
        {
          myservo.write(10); 
          delay(150); 
          ultrasonic_distance(); 
          distance_10=distance; 
          delay(150);
          myservo.write(170); 
          delay(150); 
          ultrasonic_distance(); 
          distance_170=distance; 
          delay(150); 
          myservo.write(145); 
          delay(300);
        }
