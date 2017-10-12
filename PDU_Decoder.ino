//decode a pdu format message
#include "pdu_decoder.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(1000); //delay a little toavoid triggering a restart
  
  Serial.println(pdu_decode("0CC8F71D14969741F977FD07"));   //0C(decimal 12) followed by How are you?
  Serial.println(pdu_decode("C8F71D14969741F977FD07", 12)); //How are you?
}

void loop() {
}

