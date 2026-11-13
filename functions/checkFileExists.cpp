#include <filesystem>
#include <iostream>
#include <string>

#include "functions/checkFileExists.h"

bool checkFileExists(std::string location) {
  bool fileExists = std::filesystem::exists(location);
  return fileExists;
}