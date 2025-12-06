#include "LogWatcher.h"
#include <iostream>
#include <filesystem>

using namespace std;

LogWatcher::LogWatcher(const string& filepath) {
    monitored_path = filepath;

    // Pattern: Matches "failed" AND ("password" OR "login")
    suspicious_pattern = regex(".*failed.*(password|login).*", regex_constants::icase);

    // Move cursor to END of file to ignore historical logs
    ifstream file(monitored_path, ios::ate);
    if (file.good()) {
        last_position = file.tellg();
    }
    else {
        last_position = 0;
    }
}

void LogWatcher::check(AlertSender& sender) {
    if (!filesystem::exists(monitored_path)) return;

    ifstream file(monitored_path);
    if (!file.good()) return;

    // Resume reading from last known position
    file.seekg(last_position);

    string line;
    while (getline(file, line)) {
        // Apply Regex analysis
        if (regex_match(line, suspicious_pattern)) {
            string msg = "**LOG ALERT**\nSuspicious entry: `" + line + "`";
            cout << "\n[!!! LOG ALERT !!!] " << msg << endl;

            sender.send(msg);
        }
    }

    // Reset EOF flag and save new cursor position
    if (file.eof()) {
        file.clear();
    }
    last_position = file.tellg();
}