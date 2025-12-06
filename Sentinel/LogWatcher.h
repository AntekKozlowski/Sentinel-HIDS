#pragma once
#include <string>
#include <fstream>
#include <regex>
#include "AlertSender.h"

using namespace std;

// Log Analysis Module using Regex heuristics
class LogWatcher {
public:
    LogWatcher(const string& filepath);

    // Scans new log entries for suspicious patterns
    void check(AlertSender& sender);

private:
    string monitored_path;
    streampos last_position;
    regex suspicious_pattern;
};