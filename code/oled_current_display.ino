
#include "INA226.h"
#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN //4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaration for an ina226
INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  
  Wire.begin();
  // 
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(1, 0.11); // With calibration

}

void loop()
{
  Serial.println("\nBUS(V)\tSHUNT(mV)\tCURRENT(mA)\tPOWER(mW)");
  /*for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t\t");
    Serial.print(INA.getShuntVoltage_mV(), 3);
    Serial.print("\t\t");
    Serial.print(INA.getCurrent_mA(), 3);
    Serial.print("\t\t");
    Serial.print(INA.getPower_mW(), 3);
    Serial.println();
  }*/
  
  display.clearDisplay();

  display.cp437(true);
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0,0);
  display.print("Infos ...");

  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,20);
  display.print("V Bus : ");
  display.print(INA.getBusVoltage(), 3);
  display.print(" V");

  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,30);
  display.print("V Shunt : ");
  display.print(INA.getShuntVoltage_mV(), 3);
  display.print(" mV");

  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,40);
  display.print("I : ");
  display.print(INA.getCurrent_mA(), 3);
  display.print(" mA");

  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,50);
  display.print("P : ");
  display.print(INA.getPower_mW(), 3);
  display.print(" mW");

  display.display();

  delay(200);
}
