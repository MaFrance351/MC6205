#define CLOCK 3 //SH_CP
#define DATA 4  //DS
#define LATCH 5  //ST_CP
#define RESET 6
#define ADDR 7
#define STROBE 8

#define STX 0x02
#define ETX 0x03

void setup() {
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(ADDR, OUTPUT);

  digitalWrite(LATCH, HIGH);
  digitalWrite(RESET, HIGH);
  digitalWrite(ADDR, HIGH);
  digitalWrite(STROBE, HIGH);
  displayReset();
  Serial.begin(115200);
}

void sendData(uint8_t data) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, data);
  digitalWrite(LATCH, HIGH);
}

void sendAddr(uint8_t addr) {
  sendData(addr);
  digitalWrite(ADDR, LOW);
  delayMicroseconds(10);
  digitalWrite(ADDR, HIGH);
}

void sendSymbol(uint8_t addr) {
  sendData(~addr);
  digitalWrite(STROBE, LOW);
  delayMicroseconds(10);
  digitalWrite(STROBE, HIGH);
}

void displayReset() {
  digitalWrite(RESET, LOW);
  delay(10);
  digitalWrite(RESET, HIGH);
  for (int i = 0; i < 160; i++) {
    sendAddr(i);
    sendSymbol(' ');
  }
  sendAddr(0);
}


void displayShow(char * str, uint8_t len, uint8_t line) {
  for (int i = 0; i < len; i++) {
    sendAddr(line * 16 + i);
    sendSymbol(str[i]);
  }
}

void newPacket() {
  uint8_t packet[20] = {0};
  uint8_t len = 0;
  while (Serial.available() < 2);;
  Serial.readBytes(&packet[0], 2);
  len = packet[1];
  while (Serial.available() < len);;
  Serial.readBytes(&packet[2], len);
  if (packet[len + 1] != ETX) return;
  else if (packet[2] == 0xFF) displayReset();
  else displayShow(&packet[3], len - 2, packet[2]);
}

void loop() {
  if (Serial.available()) {
    if (Serial.peek() == STX) newPacket();
    else Serial.read();
  }
}
