#include "LogWatcher.h"
#include <iostream>
#include <filesystem>

using namespace std;

LogWatcher::LogWatcher(const string& filepath) {
    monitored_path = filepath;

    // Define the Attack Pattern (Regex)
    // We look for "failed" AND ("password" OR "login"), ignoring case sensitivity.
    // Examples caught: "Failed password for root", "Login FAILED"
    suspicious_pattern = regex(".*failed.*(password|login).*", regex_constants::icase);

    // On startup, move the cursor to the END of the file.
    // We only want to analyze *new* log entries, not historical data.
    ifstream file(monitored_path, ios::ate); // 'ate' = At The End
    if (file.good()) {
        last_position = file.tellg();
    }
    else {
        last_position = 0;
    }
}

void LogWatcher::check() {
    if (!filesystem::exists(monitored_path)) return;

    ifstream file(monitored_path);
    if (!file.good()) return;

    // 1. Resume reading from the last known position
    file.seekg(last_position);

    string line;
    // 2. Process only new lines
    while (getline(file, line)) {
        // 3. Apply Heuristics / Regex Analysis
        if (regex_match(line, suspicious_pattern)) {
            cout << "\n[!!! LOG ALERT !!!] Suspicious activity detected!" << endl;
            cout << "Source:  " << monitored_path << endl;
            cout << "Payload: " << line << endl;
        }
    }

    // 4. Clear EOF flag and save the new cursor position
    if (file.eof()) {
        file.clear();
    }
    last_position = file.tellg();
}