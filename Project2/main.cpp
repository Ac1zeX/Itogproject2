#include <iostream>
#include <vector>
#include <algorithm>
#include "device.h"
#include "telemetry.h"
#include "storage.h"

int main() {
    // locale не наботает, так что на англ
    std::vector<Device> devices;


    const std::string filename = "devices.txt";

    while (true) {
        std::cout << "\nMenu \n"
            << "1. Add dev\n"
            << "2. Show all\n"
            << "3. Cycle (-Battery  +Temperature)\n"
            << "4. Charge device\n"
            << "5. Cool device\n"
            << "6. Find device\n"
            << "7. Show critical battery\n"
            << "8. Show hot device (> 45C)\n" //градусов тоже нет
            << "9. Sort device\n"
            << "10. Save\n"
            << "11. Load\n"
            << "0. Exit\n"
            << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            int id, battery;
            std::string name;
            double temp;
            bool online;
            std::cout << "Enter ID, Name, Battery, Temperature, Online/Offline (1/0): \n";
            std::cout << "Input example: (1 name 77 50 1)\n";
            std::cin >> id >> name >> battery >> temp >> online;
            devices.emplace_back(id, name, battery, temp, online);
            break;
        }
        case 2:
            printAllDevices(devices);
            break;
        case 3: {
            std::cout << "Enter ID: ";
            int targetId;
            std::cin >> targetId;
            auto it = std::find_if(devices.begin(), devices.end(), [targetId](const Device& d) {
                return d.getId() == targetId;
                });
            if (it != devices.end()) {
                int cost; 
                double gain;
                std::cout << "Enter battery and temperature: ";
                std::cin >> cost >> gain;
                it->runCycle(cost, gain);
            }
            else {
                std::cout << "Device not found\n";
            }
            break;
        }
        case 4: {
            std::cout << "Enter Device ID and charge amount: ";
            int targetId, amount;
            std::cin >> targetId >> amount;
            auto it = std::find_if(devices.begin(), devices.end(), [targetId](const Device& d) {
                return d.getId() == targetId;
                });
            if (it != devices.end()) it->charge(amount);
            else std::cout << "Device not found\n";
            break;
        }
        case 5: {
            std::cout << "Enter Device ID and cool amount: ";
            int targetId; 
            double amount;
            std::cin >> targetId >> amount;
            auto it = std::find_if(devices.begin(), devices.end(), [targetId](const Device& d) {
                return d.getId() == targetId;
                });
            if (it != devices.end()) it->cool(amount);
            else std::cout << "Device not found\n";
            break;
        }
        case 6:
            findDeviceById(devices);
            break;
        case 7:
            showCriticalDevices(devices);
            break;
        case 8:
            showOverheatedDevices(devices);
            break;
        case 9:
            sortDevices(devices);
            break;
        case 10:
            saveToFile(devices, filename);
            break;
        case 11:
            loadFromFile(devices, filename);
            break;
        default:
            std::cout << "Invalid option\n";
        }
    }
    return 0;

}
