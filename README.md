# bonfire-iot-module
Mental health isn’t just about meditation and deep talks—it’s about feeling everything without letting it consume you. That’s where Bonfire steps in. A full-spectrum mental wellness app, Bonfire helps you navigate stress, anxiety, and emotional burnout with science-backed tools, AI-driven insights, and a safe space to just be.

# IoT-Based VR Joystick Module for Bonfire's VR Rage Room

## Overview
This project integrates an IoT-based joystick module with Unity's VR Rage Room experience in Bonfire, a mental wellness application. The module enables users to control their movements within the virtual environment while monitoring their heart rate to assess mood progression. Additionally, an ultrasonic sensor and buzzer system prevent users from colliding with real-world obstacles while immersed in VR.

## Features
1. **IoT Joystick Control**:
   - The joystick module provides real-time movement control in the VR Rage Room.
   - Uses analog readings from VRX (X-axis) and VRY (Y-axis) pins.
   - A switch (SW) is included for additional actions in the VR.

2. **Heart Rate Monitoring**:
   - The MAX30105 sensor continuously tracks the user's heart rate.
   - Data is uploaded to Firebase in real time.
   - Used to analyze mood progression and emotional changes.

3. **Obstacle Avoidance System**:
   - An ultrasonic sensor measures the distance between the user and nearby objects.
   - A buzzer alerts the user if they are too close to an obstacle, preventing physical collisions while using the VR headset.

## Hardware Components
- ESP32 Microcontroller
- Joystick Module (VRX, VRY, SW pins)
- MAX30105 Pulse Oximeter & Heart Rate Sensor
- Ultrasonic Sensor (HC-SR04)
- Buzzer
- OLED Display (Optional for real-time data visualization)
- Firebase Integration for real-time data logging and analysis

## Software Components
- **Arduino IDE** for ESP32 programming
- **FirebaseESP32 Library** for data communication with Firebase
- **MAX30105 Library** for heart rate monitoring
- **Unity VR Engine** for integrating the joystick module with the VR Rage Room

## Working Mechanism
1. **Connectivity**:
   - The ESP32 connects to WiFi and syncs with Firebase.
   - The joystick sends X, Y, and button press values to Firebase, which are then mapped to VR movements in Unity.
   - Heart rate data is logged continuously for emotional analysis.
   
2. **Movement in VR**:
   - The joystick module allows free movement in the VR space.
   - The X and Y values are mapped to the player's in-game position.
   
3. **Heart Rate & Mood Progression**:
   - The MAX30105 sensor tracks the user's heart rate variations.
   - Data is analyzed to determine stress levels and emotional shifts in the VR session.
   - The system provides real-time feedback on mood changes.

4. **Safety Mechanism**:
   - The ultrasonic sensor detects obstacles in the physical environment.
   - If an object is too close, the buzzer alerts the user to prevent collisions.

## Firebase Data Structure
```json
{
  "joystick": {
    "x": 512,
    "y": 512,
    "sw": 0
  },
  "ultrasonic": {
    "distance": 35.4
  },
  "heartRate": 78
}
```

## Installation & Setup
1. **Hardware Setup**:
   - Connect the joystick, MAX30105, ultrasonic sensor, and buzzer to the ESP32 as per circuit diagram.
   - Power up the system and ensure all sensors are functioning correctly.

2. **Software Setup**:
   - Install necessary libraries in Arduino IDE.
   - Upload the provided code to the ESP32.
   - Ensure WiFi credentials and Firebase configuration are correctly set up.

3. **Unity Integration**:
   - Retrieve data from Firebase in Unity.
   - Map joystick inputs to player movement.
   - Use heart rate data for mood-based effects in the VR experience.

## Applications
- Enhancing mental wellness experiences in VR.
- Providing real-time physiological feedback for emotional analysis.
- Ensuring safety while using immersive VR environments.

## Future Improvements
- Implement AI-based emotional response adaptation.
- Improve heart rate variation analysis for detailed mood progression insights.
- Expand the module to support additional physiological sensors for better emotional tracking.


