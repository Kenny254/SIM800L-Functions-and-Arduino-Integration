#include <SoftwareSerial.h>

//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 2

//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 3

//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
char Command = 0;
void setup() {
//Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
Serial.begin(9600);
while(!Serial);

//Being serial communication witj Arduino and SIM800
serialSIM800.begin(9600);
delay(1000);

Serial.println("Setup Complete!");
}

void loop() {
//Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
    if (Serial.available() > 0) {    // is a character available?
    Command = Serial.read();
  }
  if (Command == 's'){ //Send SMS
    Serial.write(serialSIM800.read());
    serialSIM800.write("AT+CMGF=1\r"); //sending SMS in text mode
    delay(1000);
    Serial.println("AT+CMGF=1\r");       
    serialSIM800.write("AT+CMGS=\"+639175603150\"\r"); // phone number
    delay(1000);
    Serial.println("AT+CMGS=\"+639175603150\"\r");       
    serialSIM800.write("Hello parang salamat\r"); // message
    delay(1000);
    Serial.println("Hello parang salamat\r"); 
    delay(1000);
    serialSIM800.write(0x1A);
    //send a Ctrl+Z (end of the message)
    delay(1000);
    Serial.println("SMS sent successfully");
  }

  
    if (Command == 'r'){ //Read SMS
    Serial.write(serialSIM800.read());
    serialSIM800.write("AT+CMGF=1\r"); //sending SMS in text mode
    delay(1000);
    Serial.println("AT+CMGF=1\r");       
    serialSIM800.write("AT+CNMI 1,2,0,0,0"); // Read SMS
    delay(1000);
    Serial.println("AT+CNMI 1,2,0,0,0");       
    delay(1000);
    serialSIM800.write("AT+CMGL “REC UNREAD” 0 "); // Read SMS
    Serial.println("AT+CMGL “REC UNREAD” 0 ");   
    delay(1000);
    serialSIM800.write(0x1A);
    //send a Ctrl+Z (end of the message)
    delay(1000);
    Serial.println("SMS read successfully");
  }
}

