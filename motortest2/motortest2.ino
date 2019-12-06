
#define pwm1 8
#define dir1 9                         //for Right Motor
#define dir2 10

#define dir4 11                       //for Left Motor
#define dir3 12                                    //for motor driver with 2 dir pins
#define pwm2 13                                    //for motor driver with 2 dir pins

#define trigPin2 4
#define echoPin2 5
#define trigPin1 7
#define echoPin1 6
//This will run only one time.
void setup(){
  pinMode(pwm1,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(dir3,OUTPUT);
  pinMode(dir4,OUTPUT);                         //for motor driver with 2 dir pins
  
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
 
  
}


void loop(){
   digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  digitalWrite(dir3,LOW);
  digitalWrite(dir4,HIGH);
     analogWrite(pwm1,100);
    analogWrite(pwm2,150);  

}
