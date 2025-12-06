#pragma once
#include <string>
#include <filesystem>
#include "AlertSender.h"

using namespace std;

// File Integrity Monitor (FIM) using SHA-256 hashing
class FileMonitor {
public:
    // Constructor: sets target file and calculates initial hash
    FileMonitor(const string& filepath);

    // Checks for modifications. Triggers alert if hash mismatch found.
    bool check(AlertSender& sender);

private:
    filesystem::path monitored_path;
    string last_hash; // Baseline fingerprint

    // Helper: Calculates SHA-256 hash of the file
    string calculate_hash();
};