#pragma once
#include <string>
#include <filesystem> // C++17 filesystem support

// Class responsible for File Integrity Monitoring (FIM)
// It works by comparing cryptographic hashes (SHA-256) of files.
class FileMonitor {
public:
    // Constructor: takes the path to the monitored file
    FileMonitor(const std::string& filepath);

    // Main method to check file status
    // Returns TRUE if an unauthorized modification is detected
    bool check();

private:
    std::filesystem::path monitored_path;
    std::string last_hash; // Stores the "baseline" (last known valid hash)

    // Internal helper: opens the file, reads it in chunks, and calculates the hash
    std::string calculate_hash();
};