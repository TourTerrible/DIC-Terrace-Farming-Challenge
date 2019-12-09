//Inter IIT - DIC Event
//AutoNavigation, pid, Movement
//Arduino Mega 2560

#define kp 1.50                                            
#define ki 0.00
#define kd 1.00
#define k_dist 3

#define dist_to_wall 40.0
#define error 2.5
#define pwm 100
#define weight 0.5
#define angle_thresh -1.5

float inter_distance = dist_to_wall ; 
int region=1;
int dist1,dist2;

volatile float sensor_val[7];
float error_angle = 0;
float error_dist = 0;
float total_error = 0;
int angle_prev,angle_current;
bool control_movement;

float DISTANCE_PER_SENSORVALUE=.017;
int MAX_SENSOR_READING=4000;
int LARGE_SENSOR_READING=15000;
int CONSTANT_DIST=20;
int THRESH_DIST=5;
int THRESH_VALUE=10;
int MAX_CORREC=15;
int THRESH_ANGLE=1;
int constant_speed=100;
int speed_avg=120;
int calibration=50;



//================================================================================
//                                   Define pins
//================================================================================
//Front Left Motor
#define flm1 22      //Digital
#define flm2 23      //Digital
#define flm_pwm 24   //PWM
//Front Right Motor  
#define frm1 25 
#define frm2 26
#define frm_pwm 27 
//Middle
#define mlm1 28 
#define mlm2 29
#define mlm_pwm 30 
#define mrm1 31 
#define mrm2 32
#define mrm_pwm 33 
//Back
#define blm1 34 
#define blm2 35
#define blm_pwm 36 
#define brm1 37 
#define brm2 38
#define brm_pwm 39 

//Ping Sensor pins

#define trigPin1 2
#define echoPin1 3

#define trigPin2 4
#define echoPin2 5

#define trigPin3 6
#define echoPin3 7

#define trigPin4 8
#define echoPin4 9

#define trigPin5 10
#define echoPin5 11

#define trigPin6 12
#define echoPin6 13

#define trigPin7 52
#define echoPin7 53
    

//Recieve task controls from ESP in data
byte data[7]; 

void StopAll(){
  digitalWrite(flm1,LOW);
  digitalWrite(flm2,LOW);
  digitalWrite(frm1,LOW);
  digitalWrite(frm2,LOW);
  digitalWrite(mlm1,LOW);
  digitalWrite(mlm2,LOW);
  digitalWrite(mrm1,LOW);
  digitalWrite(mrm2,LOW);
  digitalWrite(blm1,LOW);
  digitalWrite(blm2,LOW);
  digitalWrite(brm1,LOW);
  digitalWrite(brm2,LOW);
}

float Read_Sensor(int sensor_number){
float sensor_value, dist ;
switch(sensor_number){
  case 1:
    digitalWrite(trigPin1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1,LOW);
    sensor_value=pulseIn(echoPin1,HIGH);
    break;
  case 2:
    digitalWrite(trigPin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2,LOW);
    sensor_value=pulseIn(echoPin2,HIGH);
    break;
  case 3:
    digitalWrite(trigPin3,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3,LOW);
    sensor_value=pulseIn(echoPin3,HIGH);
    break;
  case 4:
    digitalWrite(trigPin4,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin4,LOW);
    sensor_value=pulseIn(echoPin4,HIGH);
    break;
  case 5:
    digitalWrite(trigPin5,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin5,LOW);
    sensor_value=pulseIn(echoPin5,HIGH);
    break; 
  case 6:
    digitalWrite(trigPin6,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin6,LOW);
    sensor_value=pulseIn(echoPin6,HIGH);
    break; 
  case 7:
    digitalWrite(trigPin7,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin7,LOW);
    sensor_value=pulseIn(echoPin7,HIGH);
    break;        
}

if (sensor_value==0.0||sensor_value>=LARGE_SENSOR_READING){
    sensor_value=MAX_SENSOR_READING;
  }
  dist=sensor_value*DISTANCE_PER_SENSORVALUE;
  return dist;
}

float Dist_From_Wall(float val1, float val2){
    if(min(val1, val2) < max(val1 , val2) * 0.5 )
      return min(val1 , val2);
    return (val1 + val2)/2;
}

int Check_Region(float val1, float val2){
  int dist = Dist_From_Wall(val1 , val2);
  if(abs(dist-CONSTANT_DIST)>THRESH_DIST){
    if(dist>CONSTANT_DIST){
       return 2;
    }
    else{
      return 0;
    }
  }
  else
     return 1;
  
}



int Pid_Angle(float val1,float val2)
{
  angle_prev = angle_current;
  angle_current = val1-val2;
  total_error += (angle_current - angle_prev);
  if(angle_current == 0)
    return (0);
  else
         error_angle = kp * angle_current + ki * total_error + kd * (angle_current - angle_prev);        
//         Serial.print("correction: ");
//         Serial.println(error_angle);
         return(error_angle);
  }

float pid_dist(){
  float error_dist = k_dist * ((weight-1) *( Dist_From_Wall(sensor_val[0],sensor_val[1]) - CONSTANT_DIST ));

  return(error_dist);
} 

// int Check_Region(float val1, float val2){
//  int dist =Dist_From_Wall(val1 , val2);
//  if(dist < inter_distance -THRESH_DIST)
//    return 0;
//  if(dist > inter_distance +THRESH_DIST)
//    return 2;
//  else return 1;
//}
//
void Inter_Distance(){
    sensor_val[0] = Read_Sensor(1);
    sensor_val[1] = Read_Sensor(2);
//    inter_distance = weight * Dist_From_Wall(sensor_val[0],sensor_val[1]) + (1-weight) * dist_to_wall; 
////    Serial.print("inter_distance :");
}


//==================================================================================
//                            SETUP
//==================================================================================
void setup() {
  Serial.begin(9600);
  //Set up pins
  pinMode(flm1,OUTPUT);
  pinMode(flm2,OUTPUT);
  pinMode(flm_pwm,OUTPUT);
  pinMode(frm1,OUTPUT);
  pinMode(frm2,OUTPUT);
  pinMode(frm_pwm,OUTPUT);
  pinMode(mlm1,OUTPUT);
  pinMode(mlm2,OUTPUT);
  pinMode(mlm_pwm,OUTPUT);
  pinMode(mrm1,OUTPUT);
  pinMode(mrm2,OUTPUT);
  pinMode(mrm_pwm,OUTPUT);
  pinMode(blm1,OUTPUT);
  pinMode(blm2,OUTPUT);
  pinMode(blm_pwm,OUTPUT);
  pinMode(brm1,OUTPUT);
  pinMode(brm2,OUTPUT);
  pinMode(brm_pwm,OUTPUT);

  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(trigPin3,OUTPUT);
  pinMode(echoPin3,INPUT);
  pinMode(trigPin4,OUTPUT);
  pinMode(echoPin4,INPUT);
  pinMode(trigPin5,OUTPUT);
  pinMode(echoPin5,INPUT);
  pinMode(trigPin6,OUTPUT);
  pinMode(echoPin6,INPUT);
  pinMode(trigPin7,OUTPUT);
  pinMode(echoPin7,INPUT);


  //Initialize motors
  StopAll();
  
}

//======================================================================================
//                                         LOOP
//======================================================================================

void loop() {
  Serial.readBytes(data,7);
  control_movement =(int)data[0];
  
  if(control_movement){
    //Move Parallel to wall
    
      Inter_Distance();
      angle_prev = angle_current;
      angle_current= sensor_val[1] - sensor_val[0];
      region=Check_Region(sensor_val[0], sensor_val[1]);
      Serial.print(region);
      if(region==0 or region==2){
        analogWrite(blm_pwm, (speed_avg +calibration) + Pid_Angle(sensor_val[0],sensor_val[1]) + pid_dist());
        analogWrite(flm_pwm, (speed_avg +calibration) + Pid_Angle(sensor_val[0],sensor_val[1]) + pid_dist());
        
        analogWrite(brm_pwm, speed_avg- Pid_Angle(sensor_val[0],sensor_val[1]) - pid_dist());
        analogWrite(frm_pwm, speed_avg- Pid_Angle(sensor_val[0],sensor_val[1]) - pid_dist());
      }
      else{
        if(abs(angle_current)>THRESH_ANGLE){
        analogWrite(blm_pwm, (speed_avg +calibration) + Pid_Angle(sensor_val[0],sensor_val[1]));
        analogWrite(flm_pwm, (speed_avg +calibration) + Pid_Angle(sensor_val[0],sensor_val[1]));
        
        analogWrite(brm_pwm, speed_avg- Pid_Angle(sensor_val[0],sensor_val[1]) );
        analogWrite(frm_pwm, speed_avg- Pid_Angle(sensor_val[0],sensor_val[1]) );
          }
        else{
          analogWrite(blm_pwm, (speed_avg +calibration));
        analogWrite(flm_pwm, (speed_avg +calibration));
        
        analogWrite(brm_pwm, speed_avg );
        analogWrite(frm_pwm, speed_avg);
      
        }
      }
    
    
  }
  else{
     StopAll(); 
  }
 
  
}
