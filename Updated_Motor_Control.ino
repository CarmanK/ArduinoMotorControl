/*
 *Author:    Kevin Carman
 *Contact:   carmank@etown.edu
 *Last Edit: 2/28/2019
 *
 *Purpose
 *The switch controls power to the board.
 *Turning on the Arduino then pressing the pushbutton activates a countdown to motor activation.
 *After starting, the motor will run for a set amount of time.
 *When this passes the arduino will enter a standby state.
*/
 
int control = 9;              //Pin the control is attached to
int pushButtonPower = 8;      //Pin that powers the push button
int pushButtonOutput = 2;     //Recieves ON/OFF from pushButtonPower (pin 8)
boolean pushButtonRead = LOW; //Stores the state of the push button

int runTime = 10;         //Time (s) the motor will run
int motorPower = 255;     //Power to motor (0-255)
int dutyCycle = 50;       //DO NOT go over 50%, it can and will damage the motor and or battery
int actualPower = 0;      //Adjusted power output

//Setup routine
void setup(){
  pinMode(control, OUTPUT);
  pinMode(pushButtonPower, OUTPUT);
  pinMode(pushButtonOutput, INPUT);
}

//Main loop
void loop(){
  analogWrite(control, 0);                        //Turn the control off and make sure it is 0
  digitalWrite(pushButtonPower, HIGH);            //Power the push button
  pushButtonRead = digitalRead(pushButtonOutput); //Read the state of the push button

  //Read the state of the push button until it is high (pushed)
  while (pushButtonRead == LOW){ 
      pushButtonRead = digitalRead(pushButtonOutput);
      delay(10);        
  }
  digitalWrite(pushButtonPower, LOW);   //Turn power off to the push button until the next loop
  delay(3000);                          //Delay 3 seconds before starting the control

  //This is how the power of the motor can be calculated
  //At 50 dutyCycle and 255 basicPower, this value works out to 127.5, which is the max you should give your motor
  //actualPower = (int)(motorPower * (dutyCycle/ 100.0));

  //Increment the speed of the motor from 100 to 127 so that it does not jerk your car on start
  //Roughly 1.6 seconds until full speed
  for (int x = 100; x < 127; x++){
    analogWrite(control, x);
    delay(60);
  }
  
  delay(runTime * 1000);  //Run for `runtime` seconds at full power
  //Loop back to the top of this function. Loop will only stop when the arduino is powered off
}
