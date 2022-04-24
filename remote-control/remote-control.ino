/*************************************
 *     TIME:2022.4.23
 *     @Bofei CHEN
 *     Email: chenbofeiheu@gmail.com
 * 
 *  **************************************/
#include <IRremote.h>
//Pin for IR
#define IR_PIN 8

// Pin for motors
#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7  


#define carSpeed 130//Set the carSpeed to 160
IRrecv irrecv(IR_PIN);
decode_results results;

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



void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stop();
  delay(100);

  irrecv.enableIRIn();  // Start the IR reeviver
}

void loop() 
{

 if(irrecv.decode(&results)) {
  Serial.println(results.value, HEX);
  irrecv.resume(); // Receive the next value
 }
    
}
