const char ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const char DATA[] = { 23, 25, 27, 29, 31, 33, 35, 37 };
#define CLOCK 2
#define RW 3

void setup() {
    for (int n = 0; n < 16; ++n) {
        pinMode(ADDR[n], INPUT);
    }
    for (int n = 0; n < 8; ++n) {
        pinMode(DATA[n], INPUT);
    }
    pinMode(CLOCK, INPUT);
    pinMode(RW, INPUT);

    attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

    Serial.begin(57600);
}

void loop() {}

void onClock() {
    char output[15];
    unsigned int address = 0;
    for (int n = 0; n < 16; ++n) {
        int b = digitalRead(ADDR[n]) ? 1 : 0;
        Serial.print(b);
        address = address + (b << n);
    }
    Serial.print("    ");
    unsigned int data = 0;
    for (int n = 0; n < 8; ++n) {
        int b = digitalRead(DATA[n]) ? 1 : 0;
        Serial.print(b);
        data = data + (b << n);
    }

    sprintf(output, "\t%04x  %c  %02x", address, digitalRead(RW) ? 'r' : 'w', data);
    Serial.println(output);
}
