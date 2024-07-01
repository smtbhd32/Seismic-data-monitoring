## Earthquake Alert System with ESP32, MPU6050, and ThingSpeak README.md

This repository implements an earthquake alert system utilizing an ESP32 microcontroller, MPU6050 accelerometer, the ThingSpeak cloud platform, and optional Twilio SMS integration.

## Project Overview
This project establishes a fundamental framework for an earthquake alert system. The ESP32 reads data from the MPU6050 accelerometer, analyzes it for vibrations resembling earthquakes, and sends the data to a designated ThingSpeak channel for monitoring and visualization. Optionally, Twilio SMS alerts can be incorporated to notify authorities upon earthquake detection.

## Features
ESP32 code designed for:
Reading MPU6050 accelerometer data along all three axes (X, Y, Z)
Implementing a basic earthquake detection algorithm based on pre-defined acceleration thresholds
Sending formatted data (including timestamps and peak accelerations on each axis) to a ThingSpeak channel
ThingSpeak channel for:
Securely storing earthquake data
Visually presenting data over time using informative graphs
## Optional Features
Twilio SMS integration for sending alerts to designated authorities (requires a separate Twilio account setup)
## Skills Learned
ESP32 programming fundamentals
MPU6050 data analysis techniques
ThingSpeak cloud platform utilization (data storage, visualization)
ThingSpeak APIs (for data transmission)
## Hardware Requirements
ESP32 Development Board
MPU6050 Accelerometer
Breadboard and Jumper Wires
## Software Requirements
Arduino IDE (or a similar IDE compatible with ESP32)
ThingSpeak Account (free tier available)
(Optional) Twilio Account (for SMS alerts)
## Getting Started
Hardware Setup:

Refer to the provided schematics or consult online resources for connecting the ESP32 to the MPU6050. Ensure proper connections between all components.
Software Setup:

Install the Arduino IDE or your preferred IDE compatible with ESP32.
Create a ThingSpeak account and establish a new channel for this project. Take note of the Channel ID and API Keys (accessible within the channel settings).
(Optional) If using Twilio for SMS alerts, create a Twilio account and obtain your API credentials.
Code Configuration:

Open the esp32_earthquake_alert.ino file within the Arduino IDE.
Update the following values in the code:
WiFi SSID and password (for ESP32 Wi-Fi connection)
ThingSpeak Channel ID and Write API Key
(Optional) Twilio Account SID, Auth Token, and recipient phone number (for SMS alerts)
You can adjust the earthquake_threshold variable in the code to modify the sensitivity of the earthquake detection algorithm.
Upload and Run:

Connect your ESP32 board to your computer.
Select the appropriate board and COM port in the Arduino IDE.
Upload the code to your ESP32 board.
Open the ThingSpeak channel in your web browser to view the streamed sensor data.
Note: This is a foundational implementation. The earthquake detection algorithm might necessitate further refinement for enhanced accuracy in real-world scenarios.

## Further Enhancements
Implement MPU6050 calibration to improve data accuracy.
Refine the earthquake detection algorithm to incorporate additional factors such as frequency analysis.
Develop a mobile app using ThingSpeak React to view real-time data and receive alerts on your phone.
