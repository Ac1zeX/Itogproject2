#include "storage.h"
#include <fstream>
#include <sstream>
#include <iostream>


void saveToFile(const std::vector<Device>& devices, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error open file\n";
        return;
    }
    for (const auto& d : devices) {
        file << d.getId() << ","
            << d.getName() << ","
            << d.getBattery() << ","
            << d.getTemperature() << ","
            << (d.isOnline() ? 1 : 0) << "\n";
    }
    std::cout << "Data successfully saved\n";
}

void loadFromFile(std::vector<Device>& devices, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File not found\n";
        return;
    }

    std::vector<Device> tempDevices;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string s_id, name, s_battery, s_temp, s_online;

        if (std::getline(ss, s_id, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, s_battery, ',') &&
            std::getline(ss, s_temp, ',') &&
            std::getline(ss, s_online, ',')) {

            try {
                int id = std::stoi(s_id);
                int battery = std::stoi(s_battery);
                double temp = std::stod(s_temp);
                bool online = (std::stoi(s_online) != 0);

                tempDevices.emplace_back(id, name, battery, temp, online);
            }
            catch (...) {
                continue;
            }
        }
    }
    devices = std::move(tempDevices);
    std::cout << "Data successfully loaded\n";
}
