/*---------------------KRENOVATOR---------------------
  Smart Home Security

  Demonstrates to aware of the distance using the
  ultrasonic sensor which can be used as security
  whenever a person is cut the line of ultrasonic.
  Add a PIR sensor, as a real motion sensor detection.
  In the case of movement in that area, sensor will
  triggered. Add on LEDs as a triggered output.

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
int trigPin = 2;    //D4
int echoPin = 0;    //D3

//initialize for LEDs pin
int ledPinR = 15;   //D8
int ledPinY = 13;   //D7
int ledPinG = 12;   //D6

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
  
  pinMode(ledPinR, OUTPUT);   //led red for the result shows
  pinMode(ledPinY, OUTPUT);   //led yellow for the result shows
  pinMode(ledPinG, OUTPUT);   //led green for the result shows
  
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(pirSensor, INPUT_PULLUP);
  // Set pirSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(pirSensor), detectsMovement, RISING);
}

void blinks(){
  digitalWrite(ledPinR, HIGH);
  delay(100);
  digitalWrite(ledPinR, LOW);
  delay(100);
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
  
  /*CONDITION TO BE MET*/
  //less than 10cm to give a warning
  if(distance <= 10){     
    Serial.print("    Warning!");   //warning will pop up
    blinks();                       //led red will blinking up
    digitalWrite(ledPinY, HIGH);    //led will lights up
  }

  //between 10cm and 20cm to give a clear sign
  else if (distance > 10 && distance <=20){   
    Serial.print("    Careful!");   //clear sign pop up
    digitalWrite(ledPinR, LOW);     //led red turns off
    digitalWrite(ledPinY, HIGH);    //led yellow turns ON
  }

  //greater than 20cm to give a clear sign
  else if (distance > 20){    
    Serial.print("    Clear");    //clear sign pop up
    digitalWrite(ledPinR, LOW);     //led red turns off
    digitalWrite(ledPinY, LOW);     //led yellow turns off
    digitalWrite(ledPinG, HIGH);    //led green turns ON
  }
  
  // Current time
  now = millis();
  // After the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("  Motion stopped");
    startTimer = false;
  }
  delay(250);
}
