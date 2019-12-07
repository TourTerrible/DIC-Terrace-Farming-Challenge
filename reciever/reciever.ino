byte mystr[2]; 

void setup() {
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.readBytes(mystr,2); 
  Serial.println(mystr[0]); 
  Serial.println(mystr[1]); 
  digitalWrite(7,(int)mystr[0]);
  
  analogWrite(6,(int)mystr[1]);
 
}
