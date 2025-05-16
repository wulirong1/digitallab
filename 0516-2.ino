int ledPin = 9;      // LED connected to digital pin 9
int analogPin = A0;   // potentiometer connected to analog pin 3 (A3)
int val = 0;         // variable to store the read value

void setup() {
  pinMode(ledPin, OUTPUT);  // sets the pin as output
  Serial.begin(9600); 
}

void loop() {
  
  val = analogRead(analogPin);  // read the input pin
  Serial.println(val);
  if(val<100) val=100;
  if(val>800) val=800;
  int ledd =map(val,100,800,100,280);
  analogWrite(ledPin, ledd); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  delay(1);
}