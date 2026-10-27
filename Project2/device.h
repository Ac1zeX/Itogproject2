#ifndef DEVICE_H
#define DEVICE_H

#pragma once
#include <string>

class Device {
private:
    int id;
    std::string name;
    int battery;
    double temperature;
    bool online;

    void clampBattery();

public:
    Device(int id, const std::string& name, int battery, double temperature, bool online);

    int getId() const;
    const std::string& getName() const;
    int getBattery() const;
    double getTemperature() const;
    bool isOnline() const;

    void charge(int amount);
    void cool(double amount);
    void runCycle(int batteryCost, double tempGain);

    bool isCritical(int threshold) const;
    bool isOverheated() const;
};

#endif
