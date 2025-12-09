#pragma once

// --- CRITICAL MACROS ---
// These prevent conflicts between Windows API and standard C++ libraries (like std::byte)
#define WIN32_LEAN_AND_MEAN 
#define NOMINMAX 
// -----------------------

#include <windows.h>
#include <string>
#include <atomic>

// Global flag controlling the main loop.
// When set to false, all worker threads will gracefully terminate.
extern std::atomic<bool> service_running;

class Service {
public:
    /**
     * @brief Attempts to start the program as a Windows Service.
     * * @param service_name The name of the service to register.
     * @return true if the program successfully started as a Service.
     * @return false if the Service Control Manager could not be reached (implies Console Mode).
     */
    static bool Run(const std::string& service_name);

private:
    // Entry point called by Windows Service Manager
    static void WINAPI ServiceMain(DWORD argc, LPTSTR* argv);

    // Handler for control events (Stop, Shutdown)
    static void WINAPI CtrlHandler(DWORD request);

    // Helper to report current status to the OS
    static void UpdateStatus(DWORD state);
};

// Forward declaration of the main business logic function
void sentinel_main_logic();