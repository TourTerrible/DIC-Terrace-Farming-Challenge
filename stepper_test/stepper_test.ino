//stepper test code
//DIC-Inter IIT
// defines pins numbers
#define stepper_dir      D0       
#define stepper_en       D1    
#define stepper_step     D2
#define moisture_pin     A0  //Analog In
#define moisture_servo   D8        
#define extra_pin_1      D3  
#define extra_pin_2      D4
#define extra_pin_3      D5
#define extra_pin_4      D6

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepper_dir,OUTPUT); 
  pinMode(stepper_en,OUTPUT);
  pinMode(stepper_step, OUTPUT);
  pinMode(moisture_pin,INPUT); 
  pinMode(moisture_servo,OUTPUT);
 
  
  
} 
void loop() {
  
  digitalWrite(stepper_dir,HIGH);
  digitalWrite(stepper_en, LOW);

  for(int x = 0; x < 50; x++) {
    digitalWrite(stepper_step,HIGH); 
    delayMicroseconds(1250); 
    digitalWrite(stepper_step,LOW); 
    delayMicroseconds(1250); 
  }
  delay(1000);
  
  
}
