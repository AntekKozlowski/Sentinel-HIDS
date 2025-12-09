#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <windows.h> // Required for GetModuleFileName

#include "FileMonitor.h"
#include "LogWatcher.h"
#include "AlertSender.h"
#include "Service.h" 

using json = nlohmann::json;

// --- WORKER THREADS ---

// Thread function for File Integrity Monitoring
void run_fim_thread(std::string target, int interval_ms, AlertSender& alert_sender) {
    // Ensure the target file exists to prevent errors
    if (!std::filesystem::exists(target)) {
        std::ofstream(target) << "Sentinel Test File";
    }

    FileMonitor monitor(target);

    // Loop continues until the service receives a stop signal
    while (service_running) {
        monitor.check(alert_sender);
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

// Thread function for Log Analysis
void run_log_thread(std::string target, int interval_ms, AlertSender& alert_sender) {
    if (!std::filesystem::exists(target)) {
        std::ofstream(target) << "";
    }

    LogWatcher watcher(target);
    while (service_running) {
        watcher.check(alert_sender);
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

// --- MAIN BUSINESS LOGIC ---
// This function is shared between Console Mode and Service Mode
void sentinel_main_logic() {
    // 1. Automatic Working Directory Detection
    // Windows Services default to C:\Windows\System32. We must change this 
    // to the directory where the .exe is located to find config.json correctly.
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::filesystem::path exe_path(buffer);
    std::filesystem::path exe_dir = exe_path.parent_path();

    try {
        std::filesystem::current_path(exe_dir);
    }
    catch (...) {}

    // 2. Load Configuration
    std::string config_filename = "config.json";
    std::ifstream config_file(config_filename);
    json config;

    if (config_file.is_open()) {
        try { config_file >> config; }
        catch (...) {}
    }

    // Parse settings with fallback default values
    std::string fim_target = config.value("fim_target", "test.txt");
    std::string log_target = config.value("log_target", "system.log");
    std::string webhook_url = config.value("discord_webhook", "");
    int interval = config.value("check_interval_ms", 2000);

    AlertSender alert_sender(webhook_url);
    if (!webhook_url.empty()) {
        alert_sender.send("**Sentinel v5.0 Service Started**");
    }

    // 3. Spawn Worker Threads
    // We use std::ref to pass the AlertSender by reference
    std::thread t1(run_fim_thread, fim_target, interval, std::ref(alert_sender));
    std::thread t2(run_log_thread, log_target, interval, std::ref(alert_sender));

    // 4. Wait for shutdown signal
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    if (!webhook_url.empty()) {
        alert_sender.send("**Sentinel Service Stopped**");
    }
}

// --- ENTRY POINT ---
int main(int argc, char** argv) {
    // 1. Attempt to run as a Windows Service
    // If StartServiceCtrlDispatcher succeeds, this call blocks until the service stops.
    if (Service::Run("Sentinel")) {
        return 0;
    }

    // 2. Fallback: Console Mode
    // If we are here, it means we were run manually by the user (not by SCM).
    std::cout << "--- Sentinel v5.0 (Console Mode) ---" << std::endl;
    std::cout << "[INFO] Running locally. Press Ctrl+C to stop." << std::endl;

    // Manually set the flag to true for console execution
    service_running = true;
    sentinel_main_logic();

    return 0;
}