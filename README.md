Note on README:

The content of this README was written entirely by me (Zoraiz). Grok AI was used solely to refine the language, eliminate grammatical and spelling errors, and enhance readability.

# EMG-Controlled Robotic Hand (Extension)

Direct muscle-based control of the same 3D-printed robotic hand — no glove, no finger sensors.  
Just flex your forearm muscles → robotic hand closes. Relax → hand opens.

## What It Does

- EMG sensor on forearm detects muscle contraction  
- Single analog signal is smoothed and thresholded  
- When muscle tightens (signal > high threshold) → hand closes  
- When muscle relaxes (signal < low threshold) → hand opens  
- Full grip control using only one muscle group (e.g. forearm flexor)  

## Why This Extension?

This is a direct upgrade from the glove-controlled version (previous project).  
Instead of measuring finger bending, we measure **physiological intent** through muscle electrical activity (EMG).  
Keeps the exact same robotic arm, servos, tendons, and receiver logic — only the input method changes.

## Main Features

- Pure EMG-based control (no mechanical sensors on fingers)  
- Hysteresis + moving average smoothing to reduce noise/false triggers  
- Real-time debug output for easy threshold calibration  
- Compatible with previous robotic hand hardware  
- Simple, intuitive: tense muscle = grip, relax = release  

## Hardware Components (New / Changed)

**Transmitter side (EMG input):**
- Arduino Nano (or Uno)  
- EMG sensor module (common 3-electrode type with analog output)  
- HC-05 Bluetooth module (master)  
- 9V battery + 5V regulator  

**Receiver side:**  
Same as previous project  
- Arduino Uno  
- HC-05 Bluetooth module (slave)  
- 5× MG996R servos  
- 3D-printed robotic hand & forearm  
- Fishing wire tendons  

**STL files** for the full robotic hand, forearm, and joints are included in the previous project repository — print, assemble, and use fishing wire as tendons for motion.

## Repository Files


**Note:** Use the same receiver code as the glove project (parses "OK" + 5 identical digits for all fingers).

## How to Upload & Run

**1. EMG Transmitter Arduino** (`extension_emg_arm.ino`)

- Connect:
  - EMG analog output → A0  
  - HC-05 TX → pin 3 (SoftwareSerial RX)  
  - HC-05 RX → pin 2 (SoftwareSerial TX)  
- Open file in Arduino IDE  
- Board → Arduino Nano (or Uno)  
- Select correct COM port  
- Upload  

**2. Robotic Hand Receiver**  
Use the same receiver sketch from the previous glove project  
(Waits for "OK" header + 5 binary digits → sets all servos to same state)

**After upload:**

- Power on EMG transmitter (9V battery)  
- Power on robotic hand (servo supply)  
- Wait for Bluetooth pairing  
- Place EMG electrodes on forearm (over flexor muscles)  
- Tense forearm → hand should close  
- Relax → hand opens  

**Calibration tip:**  
Open Serial Monitor (9600 baud) → watch EMG_AVG values  
- Relaxed muscle → note typical value  
- Strong contraction → note peak value  
- Set `thresholdHigh` slightly below peak, `thresholdLow` above relaxed  

## Important Notes

- EMG signal is very sensitive to electrode placement, skin contact, and sweat  
- Start with default thresholds (620/560) — tune using Serial readings  
- Use fresh batteries — voltage drop affects readings  
- Receiver must be the same as glove project for compatibility  

First step toward muscle-direct control.  
— Zoraiz
