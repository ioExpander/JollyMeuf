#include "esphome.h"
#include <SoftwareSerial.h>
SoftwareSerial StoveSerial;

#define ENABLE_RX D2

char stoveRxData[2]; //When the heater is sending data, it sends two bytes: a checksum and the value


class MyCustomComponent : public PollingComponent {
 public:
  void setup() override {
    // This will be called once to set up the component
    // think of it as the setup() call in Arduino
  }
  void loop() override {
    // This will be called very often after setup time.
    // think of it as the loop() call in Arduino
      // You can also log messages
      ESP_LOGD("custom", "The GPIO pin 5 is HIGH!");
    }
};

void checkStoveReply(boolean isRam)
{
    uint8_t rxCount = 0;
    stoveRxData[0] = 0x00;
    stoveRxData[1] = 0x00;
    while (StoveSerial.available()) //It has to be exactly 2 bytes, otherwise it's an error
    {
        stoveRxData[rxCount] = StoveSerial.read();
        rxCount++;
    }
    digitalWrite(ENABLE_RX, HIGH);
    if (rxCount == 2)
    {
        byte val = stoveRxData[1];
        byte checksum = stoveRxData[0];
        const byte readByte = (isRam) ? 0x00 : 0x20;
        byte param = checksum - val - readByte;
        //Serial.printf("Param=%01x value=%d\n ", param, val);
        ESP_LOGD("cpp",",%#04x,%d,%#04x", param, val, val);
    } else {
      ESP_LOGE("cpp", "Error Reading Value");
    }
}

void readStoveRegister(boolean isRam, byte address)
{
    const byte readByte = (isRam) ? 0x00 : 0x20;
    StoveSerial.write(readByte);
    delay(1);
    StoveSerial.write(address);
    digitalWrite(ENABLE_RX, LOW);
    delay(80);
    checkStoveReply(isRam);
}

void setupScan() {
  ESP_LOGD("cpp","Starting scan Setup");
  pinMode(ENABLE_RX, OUTPUT);
  digitalWrite(ENABLE_RX, HIGH); //The led of the optocoupler is off
  StoveSerial.begin(1200, SWSERIAL_8N2, D3, D4, false, 256);
}

void scanRAM() {
  ESP_LOGD("cpp","=== Starting RAM scan ===");
  ESP_LOGD("cpp",",Param,value,hex_value");
  const boolean isRam = true;
  for (int shift = 0; shift < 255; shift++) {
        readStoveRegister(isRam, (byte)shift);
        delay(100);
    }
}

void scanEEPROM() {
  ESP_LOGD("cpp","=== Starting EEPROM scan ===");
  ESP_LOGD("cpp",",Param,value,hex_value");
  const boolean isRam = false;
  for (int shift = 0; shift < 255; shift++) {
        readStoveRegister(isRam, (byte)shift);
        delay(100);
    }
}
