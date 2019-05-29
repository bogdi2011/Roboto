#include <Servo.h>
#include <NewPing.h>

const int MotorStangaFata = 6;
const int MotorStangaSpate = 7;
const int MotorDreaptaFata = 4;
const int MotorDreaptaSpate = 5;

#define trig_pin A1
#define echo_pin A2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance);
Servo servo_motor;

int distMin = 15;

void setup(){

  pinMode(MotorDreaptaFata, OUTPUT);
  pinMode(MotorStangaFata, OUTPUT);
  pinMode(MotorStangaSpate, OUTPUT);
  pinMode(MotorDreaptaSpate, OUTPUT);
  
  servo_motor.attach(10);

  servo_motor.write(100);
  delay(200);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
  if (distance <= distMin){
    Stop();
    delay(300);
    Spate();
    delay(400);
    Stop();
    delay(300);
    distanceRight = lookD();
    delay(300);
    distanceLeft = lookS();
    delay(300);

    if(distanceRight <= distMin && distanceLeft <= distMin){
      Serial.println("new");
      Spate();
      Stop();
    }
    else if(distanceRight == distanceLeft){
      Serial.println("new");
      Spate();
      Stop();
    }
    else if(distanceRight > distanceLeft){
      Serial.println("new");
      Dreapta();
      Stop();
    }
    else if(distanceRight < distanceLeft){
      Serial.println("new");
      Stanga();
      Stop();
    }
  }
  else{
    Fata(); 
  }
    distance = readPing();
    Serial.println(distanceRight);
    Serial.println(distanceLeft);
    Serial.println(distance);
}

int lookD(){  
  servo_motor.write(25);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookS(){
  servo_motor.write(165);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=200;
  }
  return cm;
}

void Stop(){
  
  digitalWrite(MotorDreaptaFata, LOW);
  digitalWrite(MotorStangaFata, LOW);
  digitalWrite(MotorDreaptaSpate, LOW);
  digitalWrite(MotorStangaSpate, LOW);
}

void Fata(){

  if(!goesForward){
    goesForward=true;
    
    digitalWrite(MotorStangaFata, HIGH);
    digitalWrite(MotorDreaptaFata, HIGH);
  
    digitalWrite(MotorStangaSpate, LOW);
    digitalWrite(MotorDreaptaSpate, LOW); 
  Serial.println("fata");
  }
}

void Spate(){

  goesForward=false;

  digitalWrite(MotorStangaSpate, HIGH);
  digitalWrite(MotorDreaptaSpate, HIGH);
  
  digitalWrite(MotorStangaFata, LOW);
  digitalWrite(MotorDreaptaFata, LOW);
  Serial.println("spate");
  
}

void Dreapta(){

  digitalWrite(MotorStangaFata, HIGH);
  digitalWrite(MotorDreaptaSpate, HIGH);
  
  digitalWrite(MotorStangaSpate, LOW);
  digitalWrite(MotorDreaptaFata, LOW);
  
  delay(500);
  
  digitalWrite(MotorStangaFata, HIGH);
  digitalWrite(MotorDreaptaFata, HIGH);
  
  digitalWrite(MotorStangaSpate, LOW);
  digitalWrite(MotorDreaptaSpate, LOW);

  
  Serial.println("right");
}

void Stanga(){

  digitalWrite(MotorStangaSpate, HIGH);
  digitalWrite(MotorDreaptaFata, HIGH);
  
  digitalWrite(MotorStangaFata, LOW);
  digitalWrite(MotorDreaptaSpate, LOW);

  delay(500);
  
  digitalWrite(MotorStangaFata, HIGH);
  digitalWrite(MotorDreaptaFata, HIGH);
  
  digitalWrite(MotorStangaSpate, LOW);
  digitalWrite(MotorDreaptaSpate, LOW);
  Serial.println("left");
}
