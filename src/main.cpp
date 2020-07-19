#include <Arduino.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <SoftwareSerial.h>

//tempterature Probe
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

//Bluetooth serial
SoftwareSerial BluetoothSerial(10, 11); // RX | TX

#define ledPin LED_BUILTIN 
int readState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  BluetoothSerial.begin(115200);  // HC-05 default speed in AT command more
  sensor.begin();
}

void loop(void)
{
  sensor.requestTemperatures();
  if (BluetoothSerial.available()> 0){
    readState = BluetoothSerial.read();
    Serial.print("Read State: ");
    Serial.println(readState);
  }

  // greater than 0 means device ready to reade
  if(readState > 0){
    
    float temperature = sensor.getTempC();
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.println("Sending Data");
    BluetoothSerial.print(temperature);
    BluetoothSerial.print("!");
  }
}