#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"
#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
 
rgb_lcd lcd;
DHT dht(DHTPIN, DHTTYPE);

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
 
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
 
void setup() {
  Serial.begin(9600); 
  dht.begin();
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
    
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
 
  lcd.setRGB(81, 255, 0);
 
  // Print a message to the LCD.
  lcd.print("Aucun Problème !");
 
  delay(1000);
}
 
void loop(){

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
 
    delay(100);
    
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
  
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(t) || isnan(h)) 
    {
        lcd.print("Failed to read from DHT");
    }
    else if (h >= 32)
    {
      lcd.clear();
      lcd.print("Humidity: ");
        lcd.print(h);
        lcd.println("%\t");
        lcd.setRGB(255, 0, 0);
        delay(200);
        lcd.setRGB(0, 0, 0);
        delay(200);
        lcd.setRGB(255, 0, 0);
    }
    else 
    {
        // turn LED off:
        lcd.clear();
        lcd.setRGB(81, 255, 0);
        lcd.print("Humidity: ");
        lcd.print(h);
        lcd.println("%\t");
    }
}
