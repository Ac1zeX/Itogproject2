#include "telemetry.h"
#include <iostream>
#include <algorithm>

void printDevice(const Device& device) {
    std::cout << "ID: " << device.getId()
        << "    Name: " << device.getName() 
        << "    Battery: " << device.getBattery() //знак % не работает
        << "    Temp: " << device.getTemperature() << "C"
        << "    Status: " << (device.isOnline() ? "Online" : "Offline") << "\n";
}

void printAllDevices(const std::vector<Device>& devices) {
    if (devices.empty()) {
        std::cout << "No devices\n";
        return;
    }
    for (const auto& device : devices) {
        printDevice(device);
    }
}

void findDeviceById(const std::vector<Device>& devices) {
    std::cout << "Enter ID to find: ";
    int searchId;
    if (!(std::cin >> searchId)) return;

    auto it = std::find_if(devices.begin(), devices.end(), [searchId](const Device& d) {
        return d.getId() == searchId;
        });

    if (it != devices.end()) {
        std::cout << "Device found:\n";
        printDevice(*it);
    }
    else {
        std::cout << "Device with ID " << searchId << " not found.\n";
    }
}

void showCriticalDevices(const std::vector<Device>& devices) {
    std::cout << "Critical battery: ";
    int threshold;
    if (!(std::cin >> threshold)) return;

    bool found = false;
    for (const auto& device : devices) {
        if ([threshold](const Device& d) { return d.isCritical(threshold); }(device)) {
            printDevice(device);
            found = true;
        }
    }
    if (!found) std::cout << "No critical devices found\n";
}

void showOverheatedDevices(const std::vector<Device>& devices) {
    bool found = false;
    for (const auto& device : devices) {
        if (device.isOverheated()) {
            printDevice(device);
            found = true;
        }
    }
    if (!found) std::cout << "No overheated devices found\n";
}

void sortDevices(std::vector<Device>& devices) {
    std::cout << "1. Battery up\n2. Battery down\n3. Name\n4. Temperature\nChoose mode: ";
    int mode;
    if (!(std::cin >> mode)) return;

    switch (mode) {
    case 1:
        std::sort(devices.begin(), devices.end(), [](const Device& a, const Device& b) {
            return a.getBattery() < b.getBattery();
            });
        break;
    case 2:
        std::sort(devices.begin(), devices.end(), [](const Device& a, const Device& b) {
            return a.getBattery() > b.getBattery();
            });
        break;
    case 3:
        std::sort(devices.begin(), devices.end(), [](const Device& a, const Device& b) {
            return a.getName() < b.getName();
            });
        break;
    case 4:
        std::sort(devices.begin(), devices.end(), [](const Device& a, const Device& b) {
            return a.getTemperature() < b.getTemperature();
            });
        break;
    default:
        std::cout << "Invalid mode.\n";
        return;
    }
    std::cout << "Devices sorted.\n";
}
