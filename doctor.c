// AVR HV Fusebit Reset Code for ATmega328P using Arduino Mini
#define HFUSE 0xDF  // Default High Fuse (SPIEN enabled, 1024 words boot)
#define LFUSE 0x62  // Default Low Fuse (Internal 8MHz / 8)
#define EFUSE 0xFF  // Default Extended Fuse

#define 12V_RESET_PIN 8
#define TARGET_VCC    9
#define DATAOUT       11 // MOSI
#define DATAIN        12 // MISO
#define SPICLOCK      13 // SCK

void setup() {
  pinMode(12V_RESET_PIN, OUTPUT);
  pinMode(TARGET_VCC, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(SPICLOCK, OUTPUT);
  pinMode(DATAIN, INPUT);

  digitalWrite(12V_RESET_PIN, LOW); // 12V OFF (Active High control)
  digitalWrite(TARGET_VCC, LOW);
  
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting High Voltage Fuse Reset...");

  resetFuses();
}

void resetFuses() {
  // Step 1: Power cycle and enter High Voltage Programming mode
  digitalWrite(TARGET_VCC, HIGH);
  delayMicroseconds(50);
  digitalWrite(12V_RESET_PIN, HIGH); // Apply 12V to Target RESET
  delayMicroseconds(300);

  // Step 2: Write Factory Default Fuses via HV protocol
  writeFuse(0xAC, 0xA0, 0x00, LFUSE); // Low Fuse Reset
  delay(10);
  writeFuse(0xAC, 0xA8, 0x00, HFUSE); // High Fuse Reset
  delay(10);
  writeFuse(0xAC, 0xA4, 0x00, EFUSE); // Extended Fuse Reset
  delay(10);

  // Step 3: Turn off HV Programming mode
  digitalWrite(12V_RESET_PIN, LOW);
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
