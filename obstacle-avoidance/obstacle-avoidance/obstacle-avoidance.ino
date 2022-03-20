/*************************************
 *     TIME:2021.6.25
 *     Development Team: Zhiyi Technology Co., Ltd.
 * 
 *  **************************************/
#include <Servo.h>  //servo library
Servo ultrasonicServo;      // create servo object to control servo

int Echo = 13;//Pin to D13
int Trig = 12;//Pin to D12


#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7  


#define carSpeed 130//Set the carSpeed to 160
int Sensor1 = A5;//pin A5
int Sensor2 = A2;//pin A2

const int middleAngle = 80;
const int rightAngle = 0;
const int leftAngle = 170;

int SensorLeft;
int SensorRight;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){//forward function
  analogWrite(ENA, carSpeed);//Set the speed of ENA
  analogWrite(ENB, carSpeed);//Set the speed of ENB
    //The right forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //The left forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Forward");
}

void back() {//back function
  analogWrite(ENA, carSpeed);//Set the speed of ENA
  analogWrite(ENB, carSpeed);//Set the speed of ENB
  //The rihgt back
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //The left back
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Back");
}

void left() {//left function
  analogWrite(ENA, 200);//Set the speed of ENA
  analogWrite(ENB, 200);//Set the speed of ENB
   //The right forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  //The left back
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Left");
}

void right() {//right function
  analogWrite(ENA, 200);//Set the speed of ENA
  analogWrite(ENB, 200);//Set the speed of ENB
  //The rihgt back
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
   //The left forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Right");
}

void stop() {//stop function
  digitalWrite(ENA, LOW);//Set the speed of ENA to low 
  digitalWrite(ENB, LOW);//Set the speed of ENB to low
  Serial.println("Stop!");
}

/*Function to move car continus in one direction(dir) in one time duration(duration)
  f:forward
  b:back
  l:left
  r:right
*/
void moveOn(char dir, int duration) {
  unsigned long currentMillis = millis();
  while (millis() - currentMillis < duration)
  {
    switch (dir)
    {
    case 'f':
      forward();
      break;
    case 'b':
      back();
      break;
    case 'l':
      left();
      break;
    case 'r':
      right();
      break;
    default:
      break;
    }
  }
}

float GetDistance()
{
  float distance;
    // Send a low short pulse to Trig to trigger the ranging
	digitalWrite(Trig, LOW); //Send a low level to Trig
	delayMicroseconds(2);
	digitalWrite(Trig, HIGH); 
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);

  distance = pulseIn(Echo, HIGH) / 58.00;
     
  Serial.print("Distance = ");
  Serial.println(distance);//The serial output distance is converted into cm

	return distance;
}

void setup() {
  ultrasonicServo.attach(A0,700,2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stop();
  ultrasonicServo.write(middleAngle);  //setservo position according to scaled value
  delay(100);
}

void loop() 
{

    SensorRight  =  digitalRead(A5);//The sensor on the left
    SensorLeft =  digitalRead(A2);//The sensor on the Right
 
    middleDistance = GetDistance();//getDistance();
    
    if(middleDistance <= 18) 
    {
        stop();
        delay(500);
        ultrasonicServo.write(rightAngle);
        delay(500);
        rightDistance = GetDistance();//getDistance();

        delay(500);
        ultrasonicServo.write(middleAngle);
        delay(500);
        ultrasonicServo.write(leftAngle);
        delay(500);
        leftDistance = GetDistance();//getDistance();

        delay(500);
        ultrasonicServo.write(middleAngle);
        delay(500);
     
        if(rightDistance > leftDistance) 
        {
            moveOn('b', 500);
            delay(300);
            moveOn('r', 500); 
            delay(300);
        }
        else if(rightDistance < leftDistance) 
        {
            moveOn('b', 500);
            delay(300);
            moveOn('l', 500); 
            delay(300);
        }
        
        // else 
        // {
        //     forward();
        // }
    }
    else 
    {
        forward();
    }

    if(!SensorLeft && SensorRight)
    {
      moveOn('r', 500); 
      delay(300);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    }
    else if(!SensorRight && SensorLeft)
    {
      moveOn('l', 500);
      delay(300); 
    }
    else if(!SensorRight && !SensorLeft)
    {
      moveOn('b', 500);
      delay(300); 
    }
    else 
    {
        forward();
    }  
}
