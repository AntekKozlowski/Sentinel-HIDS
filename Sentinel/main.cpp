#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "FileMonitor.h"
#include "LogWatcher.h"
#include "AlertSender.h" 

using namespace std;
using json = nlohmann::json;

int main() {
    cout << "--- Sentinel HIDS v4.0 (Network Edition) ---" << endl;
    cout << "[INFO] Working Directory: " << filesystem::current_path() << endl;

    // --- 1. Load Configuration ---
    string config_filename = "config.json";
    ifstream config_file(config_filename);

    if (!config_file.is_open()) {
        cerr << "[CRITICAL] Config file missing: " << config_filename << endl;
        return 1;
    }

    json config;
    try {
        config_file >> config;
    }
    catch (const json::parse_error& e) {
        cerr << "[CRITICAL] JSON syntax error: " << e.what() << endl;
        return 1;
    }

    // Parse settings with safe defaults
    string fim_target = config.value("fim_target", "test.txt");
    string log_target = config.value("log_target", "system.log");
    string webhook_url = config.value("discord_webhook", "");
    int interval = config.value("check_interval_ms", 2000);

    cout << "[CONFIG] Loaded successfully." << endl;

    // --- 2. Initialize Modules ---

    // Setup Network Alerting
    AlertSender alert_sender(webhook_url);
    if (!webhook_url.empty()) {
        cout << "[NETWORK] Integration active." << endl;
        alert_sender.send("**Sentinel Started**");
    }
    else {
        cout << "[INFO] Local Mode (No Webhook configured)." << endl;
    }

    // Setup FIM
    vector<FileMonitor> file_monitors;
    file_monitors.emplace_back(fim_target);

    // Setup Log Analysis
    LogWatcher log_watcher(log_target);

    cout << "[INIT] System armed. Press Ctrl+C to exit." << endl;

    // --- 3. Main Loop ---
    while (true) {
        // Check files
        for (auto& monitor : file_monitors) {
            monitor.check(alert_sender);
        }

        // Check logs
        log_watcher.check(alert_sender);

        // Sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(interval));
    }

    return 0;
}