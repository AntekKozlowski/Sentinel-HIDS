#pragma once
#include <string>

class AlertSender {
public:
    AlertSender(const std::string& webhook_url);
    void send(const std::string& message);

private:
    std::string webhook_url;
};