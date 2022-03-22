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

int LeftObstacle;
int RightObstacle;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(int speed = carSpeed){//forward function
  analogWrite(ENA, speed);//Set the speed of ENA
  analogWrite(ENB, speed);//Set the speed of ENB
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


/*
use ultrasonic to scan one direction and return one average distance
*/
float ultrasonicScan(char dir)
{
  float averageDis = 0.0;
  int steps = 4;
  int dimision = 15;

  float sumDis = 0.0;
  switch (dir)
  {
  case 'r':
    for(int i=0; i<=4; i++)
    {
      ultrasonicServo.write(rightAngle + i*dimision);
      delay(500);
      sumDis += GetDistance();
    }
    break;
  case 'l':
    for(int i=0; i<=4; i++)
    {
      ultrasonicServo.write(leftAngle - i*dimision);
      delay(500);
      sumDis += GetDistance();
    }
    break;
  default:
    break;
  }
  averageDis = sumDis/(steps+1);
  return averageDis;
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

    RightObstacle  =  !digitalRead(A5);//The sensor on the Right
    LeftObstacle =  !digitalRead(A2);//The sensor on the Left
 
    middleDistance = GetDistance();//getDistance();
    
    if(middleDistance <= 18) 
    {
        stop();
        delay(500);

        rightDistance = ultrasonicScan('r');
        delay(500);
        ultrasonicServo.write(middleAngle);
        delay(500);
        leftDistance = ultrasonicScan('l');

        delay(500);
        ultrasonicServo.write(middleAngle);
        delay(500);
     
        if(rightDistance > leftDistance) 
        {
            moveOn('b', 500);
            delay(300);
            moveOn('r', 300); 
            delay(300);
        }
        else if(rightDistance < leftDistance) 
        {
            moveOn('b', 500);
            delay(300);
            moveOn('l', 300); 
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

    if(LeftObstacle && !RightObstacle)
    {
      //slow down first
      forward(80);
      moveOn('r', 200); 
      delay(300);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    }
    else if(RightObstacle && !LeftObstacle)
    {
      //slow down first
      forward(80);
      moveOn('l', 200);
      delay(300); 
    }
    else if(RightObstacle && LeftObstacle)
    {
      //stop first
      stop();
      moveOn('b', 200);
      delay(300); 
    }
    else 
    {
        forward();
    }  
}
