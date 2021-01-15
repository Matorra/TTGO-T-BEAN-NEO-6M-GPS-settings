#include <Arduino.h>
#include <axp20x.h>
#include <Wire.h>

HardwareSerial GPS(1);
AXP20X_Class axp;


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)


void setup() {
 Serial.begin(115200);
  while (!Serial);
  Wire.begin(21, 22);

   if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
    Serial.println("AXP192 Begin PASS");
  } else {
    Serial.println("AXP192 Begin FAIL");
  }
  axp.setChgLEDMode(AXP20X_LED_LOW_LEVEL);

  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
  axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);

GPS.begin(9600, SERIAL_8N1, 34, 12);   //new 115k boost mode
}

void loop() {
 
   if (GPS.available()){
     axp.setChgLEDMode(AXP20X_LED_BLINK_1HZ); // 4blink/sec, high rate
                      Serial.print(GPS.readStringUntil('\n'));
                     Serial.print("\n");
          axp.setChgLEDMode(AXP20X_LED_OFF); // LED off
          }
    
      if (Serial.available()){
                         GPS.print(Serial.readStringUntil('\n'));
                         GPS.print("\n"); }      
}