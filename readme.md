# Zecko ES  
### Embedded System Built on the Unihiker K10

Zecko ES is a multifunctional embedded system built from scratch using the **Unihiker K10**.  

The goal of this project was to maximize the capabilities of the board and create a fully interactive daily-use device combining hardware control, AI features, sensor monitoring, and multimedia functions — all written in C++.

---

## 🚀 Features

Zecko ES includes:

- 📷 **Camera** – Capture and save photos to SD card  
- 🎵 **Music Player** – Play `.wav` files from SD card  
- 🏋️ **Workout Station** – Chronometer, pedometer, sets & reps counter  
- 🤖 **Zecko AI** – Voice-interactive chatbot  
- 🌤 **Weather Station** – Temperature, humidity, light intensity & noise monitoring  
- 👁 **AI Recognition** – Face detection and analysis  
- 🎮 **Reaction Game** – Reflex-based color game  
- 🎙 **Journal** – Voice recorder with SD card storage  

---

## 🧠 Hardware Overview

The project is built entirely around the:

**Unihiker K10**

Manufactured by **DFRobot**, the board integrates:

- ESP32-S3 MCU (Xtensa LX7)
- 2.8” 240x320 color display
- Wi-Fi (2.4 GHz)
- Bluetooth 5.0 (BLE)
- 2MP Camera
- Microphone & Speaker
- RGB LED
- Temperature & Humidity sensor
- Ambient Light Sensor
- Accelerometer
- SD Card support

No external PCB or breadboard was required — everything is integrated on the board.

---

## 🏗 System Architecture

The system is built around:

- Persistent state counters
- Button-based navigation logic
- Sensor polling in `loop()`
- Mode-based function switching
- AI mode switching (Face / NoMode)
- SD card file interaction

The navigation system relies on internal counters (`pressA`, `pressB`) to switch between modules.

While intentionally simple in structure, the logic demonstrates:

- State management
- Event callbacks
- Hardware abstraction usage
- Sensor integration
- AI module interaction

---

## 🛠 Development Environment

- Language: **C++ (Arduino framework)**
- Platform: PlatformIO
- Board: `unihiker_k10`
- Framework: Arduino

### platformio.ini

```ini
[env:unihiker]
platform = https://github.com/DFRobot/platform-unihiker.git
board = unihiker_k10
framework = arduino
build_flags = 
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DARDUINO_USB_MODE=1
    -DModel=None
```

---

## 📦 Required Libraries

```cpp
#include "unihiker_k10.h"
#include "math.h"
#include <ctime>
#include <Wire.h>
#include "AIRecognition.h"
#include "asr.h"
```

---

## 🎨 3D Enclosure

A custom enclosure was designed to:

- Keep GPIO pins accessible
- Avoid blocking Wi-Fi antenna
- Maintain sensor exposure
- Preserve speaker output
- Allow press-fit assembly

You can download the case files on Printables (link in repository description).

---

## 🧪 Design Philosophy

Zecko ES was built under a personal challenge:

- No heavy AI assistance for coding
- Fast development (under 6 hours)
- Focus on core C++ logic understanding
- Manual state handling
- Minimal abstraction layers

The logic is intentionally raw but functional — the objective was learning and system integration.

---

## ⚠ Known Limitations

- No structured state machine implementation
- No error-handling safeguards
- AI + Wi-Fi cannot run reliably simultaneously (memory constraints)
- Button-counter navigation can fail under unintended usage
- Not optimized for scalability

Future refactoring could include:

- Proper state machine
- Debouncing logic
- Modular class-based architecture
- Memory optimization
- Power management improvements

---

## 📈 Future Improvements

- Refactor `main.cpp`
- Implement structured state handling
- Add OTA updates
- Expand AI interactions
- Add file manager system
- Improve UI transitions

---

## 📜 License

This project is open-source.  
See `LICENSE` file for details.

---

## 🙌 Acknowledgment

Special thanks to DFRobot for providing the Unihiker K10 through their community program.
