#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "FileMonitor.h"
#include "LogWatcher.h"

using namespace std;
using json = nlohmann::json;

int main() {
    cout << "--- Sentinel HIDS v3.0 (Portable Edition) ---" << endl;
    cout << "[INFO] Current Working Directory: " << filesystem::current_path() << endl;

    // 1. Load Configuration
    // We use a relative path to ensure portability (the app looks for the file next to the .exe)
    string config_filename = "config.json";
    ifstream config_file(config_filename);

    if (!config_file.is_open()) {
        cerr << "[CRITICAL ERROR] Could not open '" << config_filename << "'." << endl;
        cerr << "-> Please ensure 'config.json' is in the same directory as the executable." << endl;
        return 1;
    }

    json config;
    try {
        config_file >> config; // Parse JSON file
    }
    catch (const json::parse_error& e) {
        cerr << "[CRITICAL ERROR] JSON syntax error: " << e.what() << endl;
        return 1;
    }

    // 2. Parse Settings safely
    // We retrieve values by key and convert them to C++ types
    string fim_target = config["fim_target"].get<string>();
    string log_target = config["log_target"].get<string>();
    int interval = config["check_interval_ms"].get<int>();

    cout << "[CONFIG] Configuration loaded successfully." << endl;
    cout << " - FIM Target: " << fim_target << endl;
    cout << " - Log Target: " << log_target << endl;
    cout << " - Interval:   " << interval << "ms" << endl;

    // 3. Initialize Security Modules
    vector<FileMonitor> file_monitors;

    // Add the target file to the File Integrity Monitor
    file_monitors.emplace_back(fim_target);

    // Initialize the Log Watcher for the target log file
    LogWatcher log_watcher(log_target);

    cout << "[INIT] System armed. Monitoring active. Press Ctrl+C to exit." << endl;

    // 4. Main Daemon Loop
    while (true) {
        // Step A: Check file integrity
        for (auto& monitor : file_monitors) {
            monitor.check();
        }

        // Step B: Analyze logs for patterns
        log_watcher.check();

        // Step C: Sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(interval));
    }

    return 0;
}