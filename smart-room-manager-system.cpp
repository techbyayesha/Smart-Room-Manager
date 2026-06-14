// ==============================================
// SMART ROOM MANAGER
// ==============================================
// Description: A console-based system to manage smart devices in a room.
// Features: Add devices, toggle ON/OFF, adjust brightness, save/load data.
// Author: Ayesha Ramzan
// ==============================================

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// ==============================================
// CLASS: Device
// ==============================================
// Represents a single smart device (e.g., lamp, fan, light)
// Demonstrates: Encapsulation, constructors, destructor, const functions
// ==============================================

class Device
{
private:
    string name;       // Device name (e.g., "Table Lamp")
    bool isOn;         // Current status: true = ON, false = OFF
    int brightness;    // Brightness level: 0 (off/dim) to 100 (max)

public:
    // ---------- Default Constructor ----------
    // Used when no data is provided
    Device()
    {
        name = "Unknown";
        isOn = false;
        brightness = 50;
    }

    // ---------- Parameterized Constructor ----------
    // Used when user provides device details
    Device(string n, bool status, int b)
    {
        name = n;
        isOn = status;

        // Input validation: brightness must be between 0 and 100
        if (b >= 0 && b <= 100)
            brightness = b;
        else
        {
            cout << "Invalid brightness. Setting to default (50).\n";
            brightness = 50;
        }
    }

    // ---------- Destructor ----------
    // Cleans up memory when device object is destroyed
    ~Device()
    {
        cout << "Device " << name << " is being removed.\n";
    }

    // ---------- Behavior Methods ----------
    void turnOn()
    {
        isOn = true;
    }

    void turnOff()
    {
        isOn = false;
    }

    // Validates brightness again (user might change it later)
    void setBrightness(int b)
    {
        if (b >= 0 && b <= 100)
            brightness = b;
        else
            cout << "Brightness must be between 0 and 100.\n";
    }

    void setName(string n)
    {
        name = n;
    }

    // ---------- Getter Methods (const = won't modify object) ----------
    string getName() const
    {
        return name;
    }

    bool getStatus() const
    {
        return isOn;
    }

    int getBrightness() const
    {
        return brightness;
    }

    // ---------- Display Method ----------
    void showInfo(int number) const
    {
        cout << "----------------------------\n";
        cout << "\nDevice " << number << ":\n";
        cout << "Name: " << name
             << "\nStatus: " << (isOn ? "ON" : "OFF")  // Ternary operator
             << "\nBrightness: " << brightness << "\n";
    }
};

// ==============================================
// CLASS: Room
// ==============================================
// Manages a collection of devices (max 5)
// Demonstrates: Composition (Room HAS-A array of Devices)
// ==============================================

class Room
{
private:
    string roomName;        // Name of the room (e.g., "Living Room")
    Device devices[5];      // Array to store devices (composition)
    int count;              // Number of actual devices added

public:
    // ---------- Constructor ----------
    Room(string name)
    {
        roomName = name;
        count = 0;
    }

    // ---------- Destructor ----------
    ~Room()
    {
        cout << "Room " << roomName << " manager closed.\n";
    }

    // ---------- Add Device ----------
    // '&' avoids making an extra copy (works with original)
    // 'showMessage' parameter controls whether to show success message
    void addDevice(const Device& d, bool showMessage = true)
    {
        if (count < 5)
        {
            devices[count] = d;
            count++;
            if (showMessage)
                cout << "Device added successfully.\n";
        }
        else
        {
            cout << "Room is full! Max 5 devices allowed.\n";
        }
    }

    // ---------- Find Device by Name ----------
    // Returns index if found, -1 if not found
    int findDevice(string name) const
    {
        for (int i = 0; i < count; i++)
        {
            if (devices[i].getName() == name)
                return i;   // Found: return index
        }
        return -1;          // Not found: array index starts from 0, so -1 means failure
    }

    // ---------- Display All Devices ----------
    void showAllDevices() const
    {
        if (count == 0)
        {
            cout << "No devices in room.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            devices[i].showInfo(i + 1);
        }
        cout << "----------------------------\n";
    }

    // ---------- Toggle Device ON/OFF ----------
    void toggleDevice(string name)
    {
        int index = findDevice(name);

        if (index == -1)
        {
            cout << "Device not found! Try again.\n";
            return;
        }

        // Toggle: if ON → turn OFF, if OFF → turn ON
        if (devices[index].getStatus())
            devices[index].turnOff();
        else
            devices[index].turnOn();

        cout << "Device toggled.\n";
    }

    // ---------- Set Device Brightness ----------
    void setDeviceBrightness(string name, int b)
    {
        int index = findDevice(name);
        if (index == -1)
        {
            cout << "Device not found.\n";
            return;
        }
        devices[index].setBrightness(b);
        cout << "Brightness updated.\n";
    }

    // ---------- Save to File ----------
    // Saves all devices to "devices.txt" for future use
    void saveToFile()
    {
        ofstream outFile("devices.txt");
        if (!outFile)
        {
            cout << "Error saving file.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            outFile << devices[i].getName() << endl;
            outFile << devices[i].getStatus() << " "
                    << devices[i].getBrightness() << endl;
        }

        outFile.close();
    }

    // ---------- Load from File ----------
    // Loads previously saved devices when program starts
    void loadFromFile()
    {
        count = 0;  // Reset existing devices
        ifstream inFile("devices.txt");
        if (!inFile)
            return;   // File doesn't exist → nothing to load

        string name;
        int status, brightness;

        while (getline(inFile, name))
        {
            if (name.empty())
                continue;   // Skip empty lines

            if (!(inFile >> status >> brightness))
                break;

            inFile.ignore();   // Clear newline character

            Device d(name, (bool)status, brightness);

            // Only add if space is available
            if (count < 5)
                addDevice(d, false);
        }

        inFile.close();
    }
};

// ==============================================
// MAIN FUNCTION
// ==============================================
// Acts as the controller: connects user with Room
// Menu-driven interface using do-while loop
// ==============================================

int main()
{
    Room myRoom("Living Room");
    myRoom.loadFromFile();   // Load previously saved devices

    int choice;

    do
    {
        // ---------- Display Menu ----------
        cout << "\n=== Smart Room Manager ===\n";
        cout << "1. Add a Device\n";
        cout << "2. Show All Devices\n";
        cout << "3. Turn Device ON/OFF\n";
        cout << "4. Change Brightness\n";
        cout << "5. Exit\n";
        cout << "\nEnter choice: ";

        cin >> choice;
        cin.ignore();   // Clear input buffer

        // ---------- Input Validation ----------
        if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
            continue;
        }

        // ---------- Choice 1: Add Device ----------
        if (choice == 1)
        {
            string name;
            int status;
            int brightness;

            cout << "Enter name: ";
            getline(cin, name);

            // Check for duplicate device name
            if (myRoom.findDevice(name) != -1)
            {
                cout << "Device already exists! Try a different name.\n";
                continue;
            }

            // Get and validate status
            cout << "Enter status (1 ON, 0 OFF): ";
            cin >> status;
            while (status != 0 && status != 1)
            {
                cout << "Invalid! Enter 1 or 0 only: ";
                cin >> status;
            }

            // Get and validate brightness
            cout << "Enter brightness (0-100): ";
            cin >> brightness;
            while (brightness < 0 || brightness > 100)
            {
                cout << "Invalid! Enter brightness between 0-100: ";
                cin >> brightness;
            }

            Device d(name, (bool)status, brightness);
            myRoom.addDevice(d);
        }

        // ---------- Choice 2: Show All Devices ----------
        else if (choice == 2)
        {
            myRoom.showAllDevices();
        }

        // ---------- Choice 3: Toggle Device ----------
        else if (choice == 3)
        {
            string name;
            cout << "Enter device name: ";
            getline(cin, name);
            myRoom.toggleDevice(name);
        }

        // ---------- Choice 4: Change Brightness ----------
        else if (choice == 4)
        {
            string name;
            int brightness;

            // Keep asking until valid device name is entered
            bool found = false;
            do
            {
                cout << "Enter device name: ";
                getline(cin, name);
                found = (myRoom.findDevice(name) != -1);
                if (!found)
                    cout << "Device not found! Try again.\n";
            } while (!found);

            // Get and validate new brightness
            cout << "Enter new brightness: ";
            cin >> brightness;
            while (brightness < 0 || brightness > 100)
            {
                cout << "Invalid! Enter brightness between 0-100: ";
                cin >> brightness;
            }

            myRoom.setDeviceBrightness(name, brightness);
        }

        // ---------- Choice 5: Exit ----------
        else if (choice == 5)
        {
            cout << "\nExiting Smart Room Manager. Goodbye!\n";
            cout << "===================================\n";
        }

    } while (choice != 5);   // Loop until user chooses Exit

    // Save devices before exiting
    myRoom.saveToFile();

    return 0;
}
