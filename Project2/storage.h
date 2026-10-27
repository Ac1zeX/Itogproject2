#ifndef STORAGE_H
#define STORAGE_H

#pragma once
#include <vector>
#include <string>
#include "device.h"

void saveToFile(const std::vector<Device>& devices, const std::string& filename);
void loadFromFile(std::vector<Device>& devices, const std::string& filename);

#endif
