//Serial Rx Tx data sender 
//String data
 byte data[]={3,234};

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.write(data,2); //Write the serial data
  delay(1000);
}
