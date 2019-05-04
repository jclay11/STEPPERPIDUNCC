//defines pins for motor
const int stepPin = 6;  //PUL -Pulse GREEN
const int dirPin = 7; //DIR -Direction RED
const int enPin = 8;  //ENA -Enable ORANGE, GREY TO GROUND 
//define pins for ultrasonic
int trigPin = 11;
int echoPin = 12;
//initialize
double duration, mm; double currentDistance; double distance; double error;
int cmdDistance = 231; //mm
int kp = 2;
int ki = 7;
int PIDi = 0;
int PIDp = 0;
int PID = 0;

void setup(){
  //Sets the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.print("Rock n roll baby");
}

void loop(){
 if (Serial.available() > 0){
    cmdDistance = Serial.parseInt();
    }
  //Sets trigpin on high state for 10 ms
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds 
  duration = pulseIn(echoPin, HIGH);

  
  // Calculating the distance
  currentDistance = duration*0.34/2;
  Serial.println(currentDistance);

  //Find error
  error = (cmdDistance - currentDistance);
  Serial.println(error);

  //PID Calculations
  PIDp=error*kp;
  
  PIDi += error;
  if (PIDi>160){
  PIDi=160;
  }
  if (PIDi<-160){
  PIDi=-160;
  }
  else{
  PIDi=PIDi;
  }
   //FINAL TOTAL PID VALUE
   PID= 59*((error*kp) + (PIDi*ki));
  Serial.println(PID);

  
    if (PID > 0){
      //Enables the motor direction to move
      digitalWrite(dirPin,LOW);
      //Makes 200 Pulses for making one full cycle rotation
      for(int x = 0; x < PID ; x++){
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(500); 
      }
    }
    if (PID < 0){
      PID = abs(PID);
      //Changes the rotations direction
      digitalWrite(dirPin,HIGH);
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < PID; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }
    }
  //digitalWrite(trigPin, LOW);//Clears trig pin
  //delayMicroseconds(2);
}
