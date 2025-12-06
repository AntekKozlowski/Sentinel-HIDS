#include "FileMonitor.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <openssl/sha.h> 

using namespace std;

FileMonitor::FileMonitor(const string& filepath) {
    monitored_path = filepath;
    // Establish baseline on startup
    last_hash = calculate_hash();
}

bool FileMonitor::check(AlertSender& sender) {
    if (!filesystem::exists(monitored_path)) return false;

    string current_hash = calculate_hash();

    // Compare current state vs baseline
    if (current_hash != last_hash) {
        string msg = "🚨 **FIM ALERT**\nFile modified: `" + monitored_path.string() + "`";
        cout << "\n[!!! ALERT !!!] " << msg << endl;

        // Trigger remote alert
        sender.send(msg);

        // Update baseline to prevent alert flooding
        last_hash = current_hash;
        return true;
    }
    return false;
}

string FileMonitor::calculate_hash() {
    // Open in binary mode for consistent hashing
    ifstream file(monitored_path, ios::binary);
    if (!file.good()) return "";

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // Read in 4KB chunks for memory efficiency
    const int buffer_size = 4096;
    vector<char> buffer(buffer_size);

    while (file.read(buffer.data(), buffer_size)) {
        SHA256_Update(&sha256, buffer.data(), file.gcount());
    }
    SHA256_Update(&sha256, buffer.data(), file.gcount());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    // Convert raw bytes to Hex String
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}