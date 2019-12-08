byte data[7]; 

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}
//{start,pump,side,center,seeding,plough,harvest}
void loop() {
  Serial.readBytes(data,7); 
  Serial.print(data[0]);
  Serial.print("  ") ;
  Serial.print(data[1]);
  Serial.print("  "); 
  Serial.print(data[2]);
  Serial.print("  ") ;
  Serial.print(data[3]);
  Serial.print("  ") ;
  Serial.print(data[4]);
  Serial.print("  ") ;
  Serial.print(data[5]); 
  Serial.print("  ") ;
  Serial.println(data[6]);
 
  
}
