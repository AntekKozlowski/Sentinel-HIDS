#include "Service.h"

// Windows API global variables required for service management
SERVICE_STATUS        g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

// By default, the service is running. Setting this to false stops the app.
std::atomic<bool> service_running(true);

void WINAPI Service::ServiceMain(DWORD argc, LPTSTR* argv) {
    // 1. Register the handler function for the service
    g_StatusHandle = RegisterServiceCtrlHandler("Sentinel", CtrlHandler);
    if (!g_StatusHandle) return;

    // 2. Report initial status to the Service Control Manager (SCM)
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    UpdateStatus(SERVICE_START_PENDING);

    // 3. Create a stop event to handle termination
    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!g_ServiceStopEvent) {
        UpdateStatus(SERVICE_STOPPED);
        return;
    }

    // 4. Report that the service is now RUNNING
    UpdateStatus(SERVICE_RUNNING);

    // 5. Execute the main application logic
    // This function blocks until the work is done or service is stopped
    sentinel_main_logic();

    // 6. Cleanup after logic finishes
    WaitForSingleObject(g_ServiceStopEvent, INFINITE);
    UpdateStatus(SERVICE_STOPPED);
}

void WINAPI Service::CtrlHandler(DWORD request) {
    // Handle Stop or Shutdown signals from Windows
    if (request == SERVICE_CONTROL_STOP || request == SERVICE_CONTROL_SHUTDOWN) {
        UpdateStatus(SERVICE_STOP_PENDING);
        service_running = false; // Signal threads to stop
        SetEvent(g_ServiceStopEvent);
    }
    else {
        UpdateStatus(g_ServiceStatus.dwCurrentState);
    }
}

void Service::UpdateStatus(DWORD state) {
    g_ServiceStatus.dwCurrentState = state;
    g_ServiceStatus.dwWin32ExitCode = NO_ERROR;
    g_ServiceStatus.dwCheckPoint = 0;
    g_ServiceStatus.dwWaitHint = 0;
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
}

bool Service::Run(const std::string& service_name) {
    char* name_str = const_cast<char*>(service_name.c_str());
    SERVICE_TABLE_ENTRY ServiceTable[] = {
        { name_str, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

    // Attempts to connect the main thread to the Service Control Manager.
    // If this fails, it means the program was run from the console, not as a service.
    return StartServiceCtrlDispatcher(ServiceTable);
}