# Industrial Track System with RFID (I-Track RFID)

## Overview
An academic IoT prototype to monitor industrial asset movement in specifc points. It uses RFID readers (ESP32) distributed as checkpoints that autonomously update a centralized Firebase database, feeding a live web dashboard.

## Architecture
`RFID Tags` ➡️ `ESP32 + RC522` ➡️ `Firebase RTDB` ➡️ `Web Dashboard`
*(The ESP32 also sends physical routing commands to an Arduino Uno).*

## Hardware Components
* **ESP32:** Main controller. Reads RFID, connects to Wi-Fi/Firebase, and sends actuator commands.
* **RC522:** 13.56 MHz RFID reader module.
* **RFID Tags:** Passive tags representing trackable assets.

## Firmware & Database
* **ESP32 Firmware (C++):** Authenticates via Firebase Auth, reads the tag UID, logs the reading with a Firebase server timestamp (generating a unique push ID), updates the asset's current location, and triggers the Arduino.
* **Firebase Realtime Database:**
  * `/rfid/last_tag`: Quick reference for the last read tag.
  * `/tags/{uid}`: Asset details (name, category, destination, current location).
  * `/scans/{push_key}`: Historical log of all checkpoint readings.
  * `/points/'referenced_points'`: All the checkpoints, and the referenced location.
  * `/config/initial_inventory`: The inventory in the start of the day 
* **Security:** ESP32 writing is authenticated; Firebase Security Rules reject invalid checkpoint locations.

## Web Frontend (Planned)
A read-only, build-free dashboard using HTML, Tailwind CSS, Alpine.js, and Firebase JS SDK. It displays a live asset table and a history log of recent readings.

## Demo Limitations
* Single checkpoint simulated (prototype scale).
* Unregistered tags default to the "dispatch" location.

## License
Distributed under the MIT License.
