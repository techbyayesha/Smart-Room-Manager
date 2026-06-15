# 🏠 Smart Room Manager

A **console-based Smart Room Manager** built with **C++** using **Object-Oriented Programming**. This system manages devices in a room — you can add devices, turn them ON/OFF, adjust brightness, and save/load data using file handling.

---

## ✨ Technologies

- **C++ 17**
- **OOP (Classes, Encapsulation, Composition)**
- **File Handling** (`<fstream>`)
- **Standard Library** (`<iostream>`, `<string>`)
- **Arrays** (Device collection)

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| ➕ **Add Device** | Add a new device with name, status (ON/OFF), and brightness (0-100) |
| 📋 **Show All Devices** | Display all devices in the room with their details |
| 🔘 **Toggle Device** | Turn a device ON or OFF by name |
| 💡 **Change Brightness** | Adjust brightness level (0 to 100) |
| 💾 **Auto Save** | Devices are automatically saved to `devices.txt` |
| 📂 **Auto Load** | Previously saved devices load when program starts |

---

## 📍 The Process

I wanted to build something that feels like controlling a smart home — simple but satisfying. Started with basic device attributes (name, status, brightness), but realized a room needs to manage multiple devices together. That's where composition came in — the Room class contains an array of Device objects. The toggle feature gives that satisfying flip feeling, while brightness control adds precision. File handling ensures your room setup isn't lost after closing the program. Built the whole thing with clean OOP so each device manages its own state, and the room just coordinates them.

---

## 🎯 Component Architecture

- **Device Class** - Manages name, status, brightness with encapsulation
- **Room Class** - Contains array of devices (composition)
- **addDevice()** - Adds device with duplicate name check
- **findDevice()** - Linear search returns index or -1
- **toggleDevice()** - Flips status between ON/OFF
- **setDeviceBrightness()** - Validates and updates brightness
- **showAllDevices()** - Displays all devices with formatting
- **saveToFile() / loadFromFile()** - Persistent storage using fstream
- **Destructors** - Clean up memory when objects are destroyed

---

## 🛠️ OOP Concepts Used

| Concept | How It's Used |
|---------|----------------|
| **Encapsulation** | Private attributes with public getters/setters |
| **Composition** | Room contains an array of Device objects |
| **Constructor Overloading** | Default and parameterized constructors |
| **Destructor** | Cleans up memory when objects are destroyed |
| **Const Member Functions** | `getStatus() const` — doesn't modify object |
| **Ternary Operator** | `(isOn ? "ON" : "OFF")` for cleaner code |
| **Input Validation** | Brightness range check (0-100) |
| **File Handling** | Save/load devices using `<fstream>` |

---
