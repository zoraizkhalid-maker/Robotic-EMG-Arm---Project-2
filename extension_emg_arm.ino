#include <SoftwareSerial.h>
SoftwareSerial BT(3, 2); // RX, TX  (keep same as your original transmitter)

const int emgPin = A0;   // EMG module analog output goes here

// ---- Tuning parameters (you MUST calibrate these) ----
int thresholdHigh = 620;   // EMG "close" threshold (start here, adjust after Serial readings)
int thresholdLow  = 560;   // EMG "open" threshold (lower than high to create hysteresis)

const int samples = 20;    // smoothing window (increase if signal is noisy)
int emgBuf[samples];
long emgSum = 0;
int emgIdx = 0;

int gripState = 0; // 0 = open, 1 = close

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(emgPin, INPUT);

  // init smoothing buffer
  for (int i = 0; i < samples; i++) {
    emgBuf[i] = analogRead(emgPin);
    emgSum += emgBuf[i];
    delay(5);
  }

  Serial.println("EMG transmitter ready. Watch EMG_AVG values and tune thresholds.");
}

void loop() {
  // Read EMG and smooth it (moving average)
  int raw = analogRead(emgPin);

  emgSum -= emgBuf[emgIdx];
  emgBuf[emgIdx] = raw;
  emgSum += emgBuf[emgIdx];
  emgIdx++;
  if (emgIdx >= samples) emgIdx = 0;

  int emgAvg = (int)(emgSum / samples);

  // Hysteresis decision (prevents rapid toggling)
  if (gripState == 0 && emgAvg >= thresholdHigh) {
    gripState = 1; // close
  } else if (gripState == 1 && emgAvg <= thresholdLow) {
    gripState = 0; // open
  }

  // Debug output for calibration
  Serial.print("RAW=");
  Serial.print(raw);
  Serial.print("\tEMG_AVG=");
  Serial.print(emgAvg);
  Serial.print("\tSTATE=");
  Serial.println(gripState);

  // Keep your original protocol style:
  // Receiver can look for "OK" and then read 5 digits.
  // Here we apply the same command to all 5 fingers.
  sendCommand(gripState);

  delay(50);
}

void sendCommand(int state) {
  // state: 0=open, 1=close
  BT.print("OK");
  BT.print(state);
  BT.print(state);
  BT.print(state);
  BT.print(state);
  BT.println(state);
}

