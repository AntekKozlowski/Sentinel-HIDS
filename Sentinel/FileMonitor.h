#pragma once
#include <string>
#include <filesystem>
#include "AlertSender.h"

class FileMonitor {
public:
    FileMonitor(const std::string& filepath); // std::string
    bool check(AlertSender& sender);

private:
    std::filesystem::path monitored_path; // std::filesystem
    std::string last_hash;
    std::string calculate_hash();
};