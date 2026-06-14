# 🏠 Smart Room Manager

A **console-based Smart Room Manager** built with **C++** using **Object-Oriented Programming**. This system manages devices in a room — you can add devices, turn them ON/OFF, adjust brightness, and save/load data using file handling.

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

## 🏗️ Class Structure
Device (Blueprints for individual devices)<br>
├── name (string)<br>
├── isOn (bool)<br>
├── brightness (int)<br>
└── Methods: turnOn(), turnOff(), setBrightness(), showInfo()<br><br>

Room (Manages a collection of devices)<br>
├── roomName (string)<br>
├── devices[5] (array of Device objects) ← Composition<br>
├── count (int)<br>
└── Methods: addDevice(), findDevice(), toggleDevice(), saveToFile(), loadFromFile()<br>


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

## 🚀 How to Run

### 1. Compile the code
```bash
g++ smart_room.cpp -o smart_room
