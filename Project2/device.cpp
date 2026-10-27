#include "device.h"

Device::Device(int id, const std::string& name, int battery, double temperature, bool online)
    : id(id), name(name), battery(battery), temperature(temperature), online(online) {
    clampBattery();
}

void Device::clampBattery() {
    if (battery < 0) battery = 0;
    if (battery > 100) battery = 100;
}

int Device::getId() const { return id; }
const std::string& Device::getName() const { return name; }
int Device::getBattery() const { return battery; }
double Device::getTemperature() const { return temperature; }
bool Device::isOnline() const { return online; }

void Device::charge(int amount) {
    battery += amount;
    clampBattery();
}

void Device::cool(double amount) {
    temperature -= amount;
}

void Device::runCycle(int batteryCost, double tempGain) {
    battery -= batteryCost;
    clampBattery();
    temperature += tempGain;
}

bool Device::isCritical(int threshold) const {
    return battery < threshold;
}

bool Device::isOverheated() const {
    return temperature > 45.0;
}
