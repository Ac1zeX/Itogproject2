#ifndef TELEMETRY_H
#define TELEMETRY_H

#pragma once
#include <vector>
#include "device.h"

void printDevice(const Device& device);
void printAllDevices(const std::vector<Device>& devices);
void findDeviceById(const std::vector<Device>& devices);
void showCriticalDevices(const std::vector<Device>& devices);
void showOverheatedDevices(const std::vector<Device>& devices);
void sortDevices(std::vector<Device>& devices);

#endif
