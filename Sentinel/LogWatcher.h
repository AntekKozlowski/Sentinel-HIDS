#pragma once
#include <string>
#include <fstream>
#include <regex>

using namespace std;

// Module responsible for parsing system logs to detect anomalies
class LogWatcher {
public:
    LogWatcher(const string& filepath);

    void check();

private:
    string monitored_path;
    streampos last_position;

    // Attack pattern (Regex)
    // We are looking for phrases like "Failed password" or "Login failed"
    regex suspicious_pattern;
};