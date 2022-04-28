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

/*
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
*/
#define carSpeed 130//Set the carSpeed to 160
IRrecv irrecv(IR_PIN);
decode_results results;
unsigned long button_pressed = 0;
unsigned long loopN = 0;
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
  switch(results.value) {
    case 0xFF18E7: //2 foward
      button_pressed = 0xFF18E7;
      forward(); 
      break;
    case 0xFF10EF: //4 left
      button_pressed = 0xFF10EF;
      left();
      break;
    case 0xFF5AA5: //6 right
      button_pressed = 0xFF5AA5;
      right();
      break;
    case 0xFF4AB5: //8 back
      button_pressed = 0xFF4AB5;
      back();
      break;
    case 0xFFFFFFFF: // keep
      break;
    default:
      button_pressed = 0;
      stop();
      break; 
  }
  
  Serial.println(button_pressed, HEX);
  Serial.println(loopN);
  irrecv.resume(); // Receive the next value 
 }

    switch(button_pressed) {
    case 0xFF18E7: //2 foward
      forward(); 
      break;
    case 0xFF10EF: //4 left
      left();
      break;
    case 0xFF5AA5: //6 right
      right();
      break;
    case 0xFF4AB5: //8 back
      back();
      break;
    default:
      stop();
      break; 
  }

}
