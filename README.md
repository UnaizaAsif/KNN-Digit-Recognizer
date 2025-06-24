🤖 KNNProject - Digit Recognition Tool

This project implements a K-Nearest Neighbors (K-NN) based digit recognition tool using C++ with a simple GUI for kids to draw digits and receive spoken feedback.

It supports both the standard MNIST dataset and a custom user-drawn dataset created using a companion tool.

---

📌 Features

- 🧠 K-NN algorithm implementation (from scratch, no external ML libraries)
- 🎨 Drawing interface using SFML (Simple and Fast Multimedia Library)
- 🔊 Voice feedback using eSpeak NG (Text-to-Speech)
- ✍️ Custom digit dataset integration
- 🎯 Real-time digit classification and scoring system for kids

---

🗂️ Project Structure

```
KNNProject/
├── build/                   # (Ignored) Build output directory
├── data/
│   ├── mnist/               # Original MNIST dataset (download separately)
│   ├── custom_dataset/      # Custom dataset created by kids
│   │   ├── images/          # Binary image files (images.bin)
│   │   └── labels/          # Corresponding label files (labels.bin)
├── include/
│   └── knn.h                # Header for KNN implementation
├── src/
│   ├── main.cpp             # Main interactive digit testing tool
│   └── knn.cpp              # Core KNN algorithm implementation
├── External/
│   ├── SFML/                # SFML dependency (not included)
│   └── espeak-ng-master/    # eSpeak NG (TTS engine source files)
├── CMakeLists.txt           # CMake build configuration
```

---

🧩 Dependencies

✅ SFML (Graphics)
- Required for drawing the digit input window
- Download: https://www.sfml-dev.org/download.php

✅ eSpeak NG (Voice Feedback)
- Used to provide spoken responses like "Correct" or "Try Again"
- Download or build: https://github.com/espeak-ng/espeak-ng

Place the relevant headers/binaries in the `External/` directory.

---

🖼️ Custom Dataset Integration

You can use your own hand-drawn digits by generating a dataset using this companion tool:

🔗 [CustomDigitDataset Repository](https://github.com/UnaizaAsif/CustomDigitDataset)

This tool allows you to draw digits using a GUI and saves them in binary format for use in this project.

---

🛠️ Build Instructions

Using CMake:
```bash
mkdir build
cd build
cmake ..
make
```

Ensure SFML and eSpeak NG are properly linked in your environment or set paths in CMake accordingly.

---

▶️ Running the Program

1. Launch the application
2. A digit will be randomly selected
3. You draw the digit using your mouse in the pop-up window
4. The program uses K-NN to classify it
5. It gives you audio feedback and tracks your score

Press `C` to clear the canvas  
Press `Enter` to submit your digit

---

🗃️ Data Setup

- Place MNIST files inside `data/mnist/` (download from [LeCun’s site](http://yann.lecun.com/exdb/mnist/))
- Place your custom dataset (`images.bin` and `labels.bin`) inside `data/custom_dataset/images/` and `labels/`

---

🚫 Ignored Files

- `build/` directory
- Compiled binaries like `.exe`, `.dll`, `.o`

These are excluded using a `.gitignore` file.

---
