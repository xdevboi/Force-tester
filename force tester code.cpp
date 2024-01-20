int forwardPin = 8; //AIN1
int reversePin = 7; //AIN2
//put standbye pin with pup res to 3.3V
int motorPWMPin = 6; //PWMA  (ranges from analogWrite(motorPWMPin, 0) to analogWrite(motorPWMPin, 255))

int backEndStop = 4; //high when reaches position 0

int frontEndStop = 3; //high when reaches max extention



enum State {
    HOMEING, PUSHING, RESET, END
};

State state;


double motorSpeed = .9; //Ranges from 0 to 1 (configure)


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

void forwardMotor(){
    digitalWrite(reversePin, LOW);
    digitalWrite(forwardPin, HIGH); 
    runMotor();
}

void reverseMotor(){
    digitalWrite(reversePin, HIGH);
    digitalWrite(forwardPin, LOW); 
    runMotor();
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
    //state = 0;
    Serial.print("setup");
    state = HOMEING;



}


void loop() {
  // put your main code here, to run repeatedly:



    if(state == HOMEING){
      //Serial.print("shit ran ong ong");
        reverseMotor();
          
        if(digitalRead(backEndStop) == HIGH){ //back at home position 
            state = PUSHING;
            forwardMotor();
        }


        if(digitalRead(frontEndStop) == HIGH){
            state = END;
            stopMotor();
            Serial.print("Motor polarity is reversed or you need to take the rod off the front limit switch before starting program");
            delay(200);
        }
        
        
        runMotor();
        }


              
      if(state == PUSHING){
        forwardMotor();

          if(digitalRead(frontEndStop) == HIGH){
              reverseMotor();
              state = RESET;
          }
          runMotor();

          //add collecting load cell data
      }
              
          
          
      if(state == RESET){


        reverseMotor();

        if(digitalRead(backEndStop) == HIGH){ //back at home position 
            state = END;
            forwardMotor();
            delay(1500); //gives time to unpress the limit switch
        }
        
        
        runMotor();
        
    }

      if(state == END){
        stopMotor();
        exit(0); //ends code

  }
}
