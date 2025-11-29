#include <iostream>
#include <vector>       
#include <thread>       
#include <chrono>
#include "FileMonitor.h"

using namespace std;

int main() {
    cout << "--- Sentinel HIDS v1.0 (Host Intrusion Detection System) ---" << endl;
    cout << "--- System started. Press Ctrl+C to exit. ---" << endl;

    // Container storing all monitored objects
    vector<FileMonitor> monitors;

    // Configuration of Targets
    // NOTE: Update these paths to match your local environment for testing
    monitors.emplace_back("C:/Users/anton/source/repos/Sentinel/Sentinel/test.txt");
    monitors.emplace_back("C:/Users/anton/source/repos/Sentinel/Sentinel/config.txt");

    cout << "[INIT] Loaded " << monitors.size() << " files into FIM engine." << endl;

    // Main Daemon Loop
    while (true) {
        for (auto& monitor : monitors) {
            monitor.check();
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}