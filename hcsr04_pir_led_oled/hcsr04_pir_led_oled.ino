/*---------------------KRENOVATOR---------------------
  Smart Home Security

  Demonstrates to aware of the distance using the
  ultrasonic sensor which can be used as security
  whenever a person is cut the line of ultrasonic.
  Add a PIR sensor, as a real motion sensor detection.
  In the case of movement in that area, sensor will
  triggered. Add on LEDs as a triggered output. The
  changes can be observed at OLED Display

  Get the code at github
  https://github.com/MZulsyahmi/smart-home-security.git
  
  by M.Zulsyahmi @krenovator
  September 2018
 */

/*the library for OLED display*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN        //Enable the OLED
Adafruit_SSD1306 display(OLED_RESET); //Use the library

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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(pirSensor, INPUT_PULLUP);
  // Set pirSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(pirSensor), detectsMovement, RISING);

  //clear buffer
  display.clearDisplay();
}

//binking for red LED
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

  //for the display in the OLED
  display.setTextColor(WHITE);
  display.setCursor(0,45);
  display.setTextSize(1);
  display.print(distance);
  display.println("cm");
  
  /*CONDITION TO BE MET*/
  //less than 10cm to give a warning
  if(distance <= 10){     
    display.setTextColor(WHITE);
    display.setCursor(0,25);
    display.setTextSize(2);
    display.println("Warning!");
    
    blinks();
    digitalWrite(ledPinY, HIGH);    //led will lights up
    digitalWrite(ledPinG, HIGH);    //led green turns ON
    }

  //between 10cm and 20cm
  else if (distance > 10 && distance <= 20){   
    display.setTextColor(WHITE);
    display.setCursor(0,25);
    display.setTextSize(2);
    display.println("Careful");

    digitalWrite(ledPinR, LOW);     //led red turns off
    digitalWrite(ledPinY, HIGH);    //led yellow turns off
    digitalWrite(ledPinG, HIGH);    //led green turns ON
  }

  //greater than 20cm
  else if (distance > 20){
    display.setTextColor(WHITE);
    display.setCursor(0,25);
    display.setTextSize(2);
    display.println("Clear");

    digitalWrite(ledPinR, LOW);     //led red turns off
    digitalWrite(ledPinY, LOW);     //led yellow turns off
    digitalWrite(ledPinG, HIGH);    //led green turns ON
  }

  // Current time
  now = millis();
  // After the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    startTimer = false;
  }
  display.display();
  delay(250);
  display.clearDisplay();
}
