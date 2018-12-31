/*---------------------KRENOVATOR---------------------
  Smart Home Security

  Demonstrates to aware of the distance using the
  ultrasonic sensor which can be used as security
  whenever a person is cut the line of ultrasonic.
  Add a PIR sensor, as a real motion sensor detection.
  In the case of movement in that area, sensor will
  triggered.

  Get the code at github
  https://github.com/MZulsyahmi/smart-home-security.git
  
  by M.Zulsyahmi @krenovator
  September 2018
 */

//fixed the time delay for 10 secs
#define timeSeconds 10

// Set GPIOs for LED and PIR Motion Sensor
const int pirSensor = 14;      //D5

//GPIO for ultrasonic sensor
int trigPin = 2; //D4
int echoPin = 0; //D3

long duration;
long distance;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

// Checks if motion was detected, starts a timer
void detectsMovement() {
  Serial.println("  MOTION DETECTED!");
  startTimer = true;
  lastTrigger = millis();
}
  
void setup() {
  // Serial port for debugging purpose
  pinMode(trigPin, OUTPUT);   //trigger pin as a receiver
  pinMode(echoPin, INPUT);    //echo pin as a transmitter
  
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(pirSensor, INPUT_PULLUP);
  // Set pirSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(pirSensor), detectsMovement, RISING);
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
  
  // Current time
  now = millis();
  // After the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("  Motion stopped");
    startTimer = false;
  }
  delay(1000);
}
