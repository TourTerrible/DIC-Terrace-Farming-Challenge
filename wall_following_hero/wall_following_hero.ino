//Wall following with PID implementation
//Guining Pertin
//11-12-19

//Sensor pins
//Order - left-back, left-front, front, front-bottom, right-front, right-back, back
const int trig_pins[7] = {21,22,23,24,25,26,27};
const int echo_pins[7] = {31,32,33,34,35,36,37};

//Motor pins
//Main - Left - 2 Motors
const int lmain_dir = 1;
const int lmain_pwm = 2;
const int lmain_brk = 3;
//Main - Right - 2 Motors
const int rmain_dir = 4;
const int rmain_pwm = 5;
const int rmain_brk = 6;
//Subs - Left
const int lsubs_dir = 7;
const int lsubs_pwm = 8;
const int lsubs_brk = 9;
//Subs - Right
const int rsubs_dir = 10;
const int rsubs_pwm = 11;
const int rsubs_brk = 12;

void setup() {
  //Start serial
  Serial.begin(9600);
  //Set pinmodes
  //Motor pins
  pinMode(lmain_dir, OUTPUT); 
  pinMode(lmain_pwm, OUTPUT);
  pinMode(lmain_brk, OUTPUT);
  pinMode(rmain_dir, OUTPUT);
  pinMode(rmain_pwm, OUTPUT);
  pinMode(rmain_brk, OUTPUT);
  pinMode(lsubs_dir, OUTPUT);
  pinMode(lsubs_pwm, OUTPUT);
  pinMode(lsubs_brk, OUTPUT);
  pinMode(rsubs_dir, OUTPUT);
  pinMode(rsubs_pwm, OUTPUT);
  pinMode(rsubs_brk, OUTPUT);
  //Sensor pins
  for(int i=0; i<7; i++){
    pinMode(trig_pins[i], OUTPUT);
    pinMode(echo_pins[i], INPUT);
  }    
}

void loop() {
  

}
