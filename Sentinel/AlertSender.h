#pragma once
#include <string>

using namespace std;

// Handles network notifications (e.g., Discord Webhooks)
class AlertSender {
public:
    // Initialize with the target Webhook URL
    AlertSender(const string& webhook_url);

    // Send a text message via HTTP POST
    void send(const string& message);

private:
    string webhook_url;
};