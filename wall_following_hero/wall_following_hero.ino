//Wall following with PID implementation
//Guining Pertin
//11-12-19

//MACROS
#define MAX_DIST 100
#define MIN_DIST 1
#define DISTANCE_PER_SENSORVALUE 0.016f

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
  for(int i=0; i<7; i++)  {
    pinMode(trig_pins[i], OUTPUT);
    pinMode(echo_pins[i], INPUT);
  }
}

void loop() {
  //Read ultrasonic sensors
  float *distances = read_ultraonic();

}

//Function to give ultrasonic sensor readings
float* read_ultrasonic() {
  //Initialize distances array
  static float distances[7];
  //Sensor value
  float temp_dist;
  //Take average value(5 readings) for each sensor
  for(int sen_num = 0; sen_num < 7; sen_num++)  {
    for(int read_num = 0; read_num < 5; read_num++) {
      //Ultrasonic reading
      digitalWrite(trig_pins[sen_num],HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_pins[sen_num],LOW);
      temp_dist = pulseIn(echo_pins[sen_num],HIGH) * DISTANCE_PER_SENSORVALUE;
      //Limits
      if (temp_dist > MAX_DIST || temp_dist < MIN_DIST)  {
        temp_dist = 0;
      }
      //Update distance
      distances[sen_num] += temp_dist;
    }
    //Average
    distances[sen_num] = distances[sen_num]/5;
  }
  return distances
}
