//stepper test code
//DIC-Inter IIT
// defines pins numbers
const int stepPiny = 60; 
const int dirPiny = 61;   
const int Y_ENABLE_PIN=56;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPiny,OUTPUT); 
  pinMode(dirPiny,OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  
} 
void loop() {
  
  digitalWrite(dirPiny,HIGH);
  digitalWrite(Y_ENABLE_PIN, LOW);

  for(int x = 0; x < 50; x++) {
    digitalWrite(stepPiny,HIGH); 
    delayMicroseconds(1250); 
    digitalWrite(stepPiny,LOW); 
    delayMicroseconds(1250); 
  }
  delay(1000);
  
  
}
