#include "AlertSender.h"
#include <iostream>
#include <cpr/cpr.h>          // Network library
#include <nlohmann/json.hpp>  // JSON library

using namespace std;
using json = nlohmann::json;

AlertSender::AlertSender(const string& url) {
    webhook_url = url;
}

void AlertSender::send(const string& message) {
    // Skip if running in Local Mode (no URL configured)
    if (webhook_url.empty()) return;

    // Prepare JSON payload for Discord API
    json payload = { {"content", message} };

    // Execute HTTP POST request
    cpr::Response r = cpr::Post(
        cpr::Url{ webhook_url },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ payload.dump() }
    );

    // Check response (204 = No Content, acts as Success for Discord)
    if (r.status_code != 204 && r.status_code != 200) {
        cerr << "[ERROR] Discord API Error: " << r.status_code << endl;
    }
    else {
        cout << "[NETWORK] Alert sent successfully." << endl;
    }
}