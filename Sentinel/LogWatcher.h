#pragma once
#include <string>
#include <fstream>
#include <regex>
#include "AlertSender.h"

class LogWatcher {
public:
    LogWatcher(const std::string& filepath);
    void check(AlertSender& sender);

private:
    std::string monitored_path;
    std::streampos last_position; // std::streampos
    std::regex suspicious_pattern; // std::regex
};