//Xinran Shi-week 9 arduino: switch&feedback
//inspired by the reference: https://create.arduino.cc/projecthub/manivannan/social-distancing-caps-815d3b?ref=tag&ref_id=ultrasonic&offset=26

#include <Servo.h> //get the srrvo's function library

Servo myservo;// create the controlled servo object
const int servo_pin = 2;
const int trig_pin = 3;//trigger pin of ultrasonic sensor
const int echo_pin = 4;// echo pin of ultrasonic sensor
const int inter_time = 200;
int time = 0;

void setup() 
{
  Serial.begin(9600);//starting serial terminal; set the baud rate to 9600 (baud rate: the rate at which a single chip computer or a computer communicates through the serial port, so be sure to keep the baud rate of the communication equipment consistent, or communication will not be possible
  myservo.attach(servo_pin, 500, 2400);// Connection port. The first parameter is pin, the second is min, and the third is max
  myservo.write(90);//the absolute angle of rotation 90 degrees
  pinMode (trig_pin, OUTPUT);//Set pin 3 to output mode
  pinMode (echo_pin, INPUT);//Set pin 4 to input mode
  delay(3000);//Delay for 3 seconds, stay at this position
} 

void loop() //Executes the function, and loops continuously during operation
{
  float duration, distance;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(1000);//Prevent operation from being stuck and delay for one second
  digitalWrite(trig_pin, LOW);//The led light on pin 3 is on, and the low potential is output
  duration = pulseIn (echo_pin, HIGH);
  distance = (duration/2)/29;
  Serial.print(distance);
  Serial.println(" cm");//Output value "cm" to serial port display
  time = time + inter_time;
  delay(inter_time);
  if (distance < 100)
  {
    for(int i = 1500; i >= 1100; i-=25){
      myservo.writeMicroseconds(i);
      Serial.println("2");
      delay(100);
    }
    delay(1000);
    for(int i = 1100; i <= 1500; i+=25){
      myservo.writeMicroseconds(i);
      Serial.println("1");
      delay(100);//interval time between each rotate
    }
  }
}