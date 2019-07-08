#include <SoftwareSerial.h>
#include <PWMServo.h>
#include <VescUart.h>
#include <EEPROM.h>
#include <buffer.h>
#include <crc.h>
#include <datatypes.h>
/* UART 5v nc gnd nc 9-TX 8-RX SoftwareSerial mySerial(6,5);*/

SoftwareSerial mySerial(9,8);

SoftwareSerial vescSerial(5, 6);

//SoftwareSerial vescSerial(1,0);

VescUart UART;

PWMServo myservo; 

int eeData ;  //Variable to store in EEPROM.
int eeAddress = 0;   //Location we want the data to be put.

int polMotor;       //Diameter of the motor pulley
int polRoda;        //Diameter of the wheel pulley

String inString = "";
int conectioncheck = 0;

int x;

unsigned long previousMillis1=0;
unsigned long previousMillis2=0;
 
int interval1 = 5;
int interval2 = 1000;

boolean state1 = false;
boolean state2 = false;


void setup() {
  Serial.begin(9600);
  //while (!Serial);
  mySerial.begin(9600);
  myservo.attach(11);  
  vescSerial.begin(115200);  
  UART.setSerialPort(&vescSerial);
}

void loop() {
  //Serial.println("ROBA");
  //vescValues();
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
        state1 = !state1;
        pwmMotorControl();
        previousMillis1 = currentMillis;
   }
   if ((unsigned long)(currentMillis - previousMillis2) >= interval2) {
        state2 = !state2;
        vescValues();
        previousMillis2 = currentMillis;
   }
}

void pwmMotorControl(){
  mySerial.listen();

  while (mySerial.available() > 0) {
    int inChar = mySerial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;      
    }
    //Recilver pulse to the motor
    if (inChar == 'n') {
      x = inString.toInt();
      //Make motor run
      if (x <= 180){
        myservo.write(x);
        }
      inString = "";
    }    
  }
  while (mySerial.available()== NULL){
      if (conectioncheck == 15000){      
        //Serial.println("desconectado");
        myservo.write(70);
        conectioncheck = 0;
      }
      else {conectioncheck++; }
  }
}

void vescValues(){
  vescSerial.listen();
  UART.getVescValues();
    /* 
    Serial.print(" tachometro: ");
    Serial.print(UART.data.tachometer);
    Serial.println();
    Serial.print(" RPM: ");
    Serial.print(UART.data.rpm);
    Serial.println();*/
    Serial.print(" Voltage: ");
    Serial.print(UART.data.inpVoltage);
    Serial.println();
    vescSerial.end();
}
/*
void btName(){
  //mySerial.print("AT+NAMESKATE-ENRYSON");  
}

int setOdometer() {
  EEPROM.put(eeAddress, eeData);  
}

int getOdometer() {
  
  EEPROM.get( eeAddress, eeData);
}*/
