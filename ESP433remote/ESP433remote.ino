/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch receiveSwitch = RCSwitch();
RCSwitch transmitSwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");
  receiveSwitch.enableReceive(2);  // Receiver on interrupt 0 => that is pin D4

  // Transmitter is connected to ESP Pin D2   
  transmitSwitch.enableTransmit(4);

  // Optional set pulse length.
  // receiveSwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // receiveSwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // receiveSwitch.setRepeatTransmit(15);
}

void loop() {
  if (receiveSwitch.available()) {
    
    int value = receiveSwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( receiveSwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( receiveSwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( receiveSwitch.getReceivedProtocol() );
    }

    receiveSwitch.resetAvailable();
  }
  if (Serial.available() > 0) {
    Serial.println("Transmitting");
    transmitSwitch.send(1361, 24);
    delay(1000);  
    transmitSwitch.send(1364, 24);
    delay(1000);
  }
}
