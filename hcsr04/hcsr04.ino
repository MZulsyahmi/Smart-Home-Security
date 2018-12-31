/*---------------------KRENOVATOR---------------------
  Smart Home Security

  Demonstrates to aware of the distance using the
  ultrasonic sensor which can be used as security
  whenever a person is cut the line of ultrasonic.

  Get the code at github
  https://github.com/MZulsyahmi/smart-home-security.git
  
  by M.Zulsyahmi @krenovator
  September 2018
 */

//GPIO for ultrasonic sensor
int trigPin = 2;  //D4
int echoPin = 0;  //D3

long duration;
long distance;
  
void setup() {
  // Serial port for debugging purpose
  pinMode(trigPin, OUTPUT);   //trigger pin as a receiver
  pinMode(echoPin, INPUT);    //echo pin as a transmitter
  
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trigPin, LOW);   //to set the trigger as off
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);  //triggers on
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);   //set back to off

  duration = pulseIn(echoPin, HIGH);  //emits the ultrasonic
  distance = (duration/2)/29.1;       //formula for the distance in ultrasonic in cm

  //for the display in the Serial Monitor
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.print(" cm");
 
  delay(1000);
}
