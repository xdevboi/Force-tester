int forwardPin = 8; //AIN1
int reversePin = 7; //AIN2
//put standbye pin with pup res to 3.3V
int motorPWMPin = 6; //PWMA  (ranges from analogWrite(motorPWMPin, 0) to analogWrite(motorPWMPin, 255))

int backEndStop = 4; //high when reaches position 0

int frontEndStop = 3; //high when reaches max extention

int state = 0; //sets inital state



int motorSpeed = .5; //Ranges from 0 to 1 (configure)


int motorInput = motorSpeed*255;




/*
bool checkEnds() {
    if(digitalRead(backEndStop)==HIGH || digitalRead(frontEndStop)==HIGH){
        return true;
    }
    else{
        return false;
    }
}
*/




void runMotor() {
    analogWrite(motorPWMPin, motorInput);
}

void stopMotor(){
    analogWrite(motorPWMPin, 0);
    digitalWrite(reversePin, LOW);
    digitalWrite(forwardPin, LOW);
}

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
    pinMode(motorPWMPin, OUTPUT);
    pinMode(forwardPin, OUTPUT);
    pinMode(reversePin, OUTPUT);

    pinMode(backEndStop, INPUT);
    pinMode(frontEndStop, INPUT);
    state = 0;
    Serial.print("setup");



}


void loop() {
  // put your main code here, to run repeatedly:



  switch(state){
      case 0: //getting to back position
      Serial.print("shit ran ong ong");
          
          if(digitalRead(backEndStop) == HIGH){
              state = 1;
              stopMotor();
              delay(200);
              Serial.print("shit ran pt 2 ????");
              break;
          }


          if(digitalRead(frontEndStop) == HIGH){
              state = 3;
              stopMotor();
              delay(200);
              Serial.print("Motor polarity is reversed or you need to take the rod off the front limit switch before starting program");
              break;
          }
          
          digitalWrite(forwardPin, LOW);
          digitalWrite(reversePin, HIGH);
          runMotor();


              
      case 1: //pushing the Mouse

          if(digitalRead(frontEndStop) == HIGH){
              stopMotor();
              delay(200);
              state = 2;
              break;
          }

          digitalWrite(forwardPin, HIGH);
          digitalWrite(reversePin, LOW);
          runMotor();

          //add collecting load cell data
              
          
          
      case 2: //reset back to 0 extention position



          if(digitalRead(backEndStop) == HIGH){
              state = 3;
              stopMotor();
              delay(200);
              break;
          }
          
          digitalWrite(forwardPin, LOW);
          digitalWrite(reversePin, HIGH);
          runMotor();

      case 3:
        exit(0); //ends code

  }
}
