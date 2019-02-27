#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <buffer.h>
#include <crc.h>
#include <datatypes.h>
#include <VescUart.h>


SoftwareSerial vescSerial(8,9);
SoftwareSerial btSerial(2,3);


int eeData ;  //Variable to store in EEPROM.
int eeAddress = 0;   //Location we want the data to be put.

int polMotor;       //Diameter of the motor pulley
int polRoda;        //Diameter of the wheel pulley

String inString = "";
int conectioncheck = 0;
int x;

VescUart UART;

void setup() {
  btSerial.begin(9600);
  vescSerial.begin(9600);
  Serial.begin(9600);
  
  UART.setSerialPort(&vescSerial);
  
}

void loop() {
  
  
}

void vescValues(){
  
  if ( UART.getVescValues() ) {
    Serial.print(" tachometro: ");
    Serial.print(UART.data.tachometer);
    Serial.println();
    Serial.print(" RPM: ");
    Serial.print(UART.data.rpm);
    Serial.println();
    Serial.print(" Voltage: ");
    Serial.print(UART.data.inpVoltage);
    Serial.println();
  }
  
}

int setOdometer() {
  EEPROM.put(eeAddress, eeData);  
}

int getOdometer() {
  
  EEPROM.get( eeAddress, eeData);
}
