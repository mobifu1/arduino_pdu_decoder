//decode a pdu format message

//String pdu_text = "C8F71D14969741F977FD07" ;// > How are you?
byte pdu_bytes[] = {0xC8, 0xF7, 0x1D, 0x14, 0x96, 0x97, 0x41, 0xF9, 0x77, 0xFD, 0x07};// > How are you?
String plain_text ;

void setup() {

  Serial.begin(9600);
  pdu_decode();
  Serial.println(plain_text);
}

void loop() {



}

void pdu_decode() {

  byte plain_bytes[256];
  int len = sizeof(pdu_bytes);
  byte high_mask = 128; // byte:10000000;
  byte low_mask;
  byte shift = 0;
  byte high_byte_new = 0;
  byte high_byte_old = 0;
  byte low_byte = 0;
  int count_plain = 0;
  int i;
  int y = 0;

  for ( i = 0; i < len ; i++) {

    low_mask = high_mask ^ 0xFF; //invert
    high_byte_new = pdu_bytes[i] & high_mask;         // 10000000 = 11000111 & 10000000
    low_byte = pdu_bytes[i] & low_mask;               // 01000111 = 11000111 & 01111111

    plain_bytes[y] = low_byte << shift;               // 10001110
    high_byte_old = high_byte_old >> (8 - shift);     // 00000001
    plain_bytes[y] =  plain_bytes[y] + high_byte_old; // 10001111

    if (shift == 6) {
      y++;
      plain_bytes[y] = high_byte_new >> 1;
    }

    high_mask = high_mask >> 1;           // 10000000 > 01000000
    high_mask = high_mask + 128;          // 01000000 > 11000000
    if (high_mask == 255)high_mask = 128; // 11111111 > 10000000
    low_mask = high_mask ^ 0xFF; //invert

    high_byte_old = high_byte_new;
    shift++;
    if (shift == 7)shift = 0;
    y++;
  }
  for ( i = 0; i < y ; i++) {
    plain_text = plain_text  + char(plain_bytes[i]);
  }
}





