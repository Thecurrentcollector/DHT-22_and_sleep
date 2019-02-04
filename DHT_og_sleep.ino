#include <LowPower.h>
#include "DHT.h"

#define DHTPIN 2     

#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

int green_led = 4;
int red_led = 5;
int DHT_vcc = 9;

int sleep = 0;

void setup() {
  
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(DHT_vcc, OUTPUT);

  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(DHT_vcc, LOW);
  
  Serial.begin(9600);
 
  dht.begin();
}

void loop() {
  //Counter for sleep cycles.
  sleep += 1;

  //Checks to see we have slept long enough. If not, go back to sleep.
  if (sleep >= 7) {

    //Turn on DHT via 5V output pin, then wait for 1500 ms for whatever initialization the DHT22 needs. Determined through trial and error.
    digitalWrite(DHT_vcc, HIGH);
    delay(1500);

    // Reading temperature and humidity here.
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    //Turning off the DHT22 before sleeping later.
    digitalWrite(DHT_vcc, LOW);
  
    // Check if any reads failed and blink red LED if so. 
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to get readings!");
      for (int i=0; i < 5; i++ ){
        digitalWrite(red_led, HIGH);
        delay(50);  
        digitalWrite(red_led, LOW);
        delay(100);  
      }
    }
    //Prints readings to serial.
    else {
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" 'C ");
      Serial.println();

    //Blinks green to indicate successful readings.
      for (int i=0; i < 5; i++ ){
          digitalWrite(green_led, HIGH);
          delay(20);  
          digitalWrite(green_led, LOW);
          delay(20); 
          }
        }
        
      //clear the sleep variable to start a new sleep/wake period.
      sleep = 0;

    }
//Sleeps for 8 seconds.
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

}

