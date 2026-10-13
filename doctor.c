// Final AVR HV Fusebit Reset Code for ATmega328P using Arduino Mini
#define HFUSE 0xDF  
#define LFUSE 0x62  
#define EFUSE 0xFF  

#define RESET_12V_PIN 8
#define TARGET_VCC    9
#define DATAOUT       11 // MOSI
#define DATAIN        12 // MISO
#define SPICLOCK      13 // SCK

void setup() {
  pinMode(RESET_12V_PIN, OUTPUT);
  pinMode(TARGET_VCC, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(SPICLOCK, OUTPUT);
  pinMode(DATAIN, INPUT);

  digitalWrite(RESET_12V_PIN, LOW); 
  digitalWrite(TARGET_VCC, LOW);
  
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting High Voltage Fuse Reset...");

  resetFuses();
}

void resetFuses() {
  digitalWrite(TARGET_VCC, HIGH);
  delayMicroseconds(50);
  digitalWrite(RESET_12V_PIN, HIGH); 
  delayMicroseconds(300);

  writeFuse(0xAC, 0xA0, 0x00, LFUSE); 
  delay(10);
  writeFuse(0xAC, 0xA8, 0x00, HFUSE); 
  delay(10);
  writeFuse(0xAC, 0xA4, 0x00, EFUSE); 
  delay(10);

  digitalWrite(RESET_12V_PIN, LOW);
  digitalWrite(TARGET_VCC, LOW);

  Serial.println("Fuses successfully restored to factory defaults!");
}

void writeFuse(byte b1, byte b2, byte b3, byte b4) {
  shiftOut(DATAOUT, SPICLOCK, MSBFIRST, b1);
  shiftOut(DATAOUT, SPICLOCK, MSBFIRST, b2);
  shiftOut(DATAOUT, SPICLOCK, MSBFIRST, b3);
  shiftOut(DATAOUT, SPICLOCK, MSBFIRST, b4);
}

void loop() {
  // Nothing to do
}
