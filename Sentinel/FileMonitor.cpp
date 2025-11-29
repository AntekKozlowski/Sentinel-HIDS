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
    // On startup, calculate the initial "Baseline" hash
    last_hash = calculate_hash();
}

bool FileMonitor::check() {
    // 1. Verify file existence
    if (!filesystem::exists(monitored_path)) {
        cerr << "[ERROR] File not found: " << monitored_path << endl;
        return false;
    }

    // 2. Calculate the current file fingerprint
    string current_hash = calculate_hash();

    // 3. Change Detection (Core Logic)
    if (current_hash != last_hash) {
        cout << "\n[!!! SECURITY ALERT !!!] File modification detected: " << monitored_path << endl;
        cout << "Previous Hash: " << last_hash << endl;
        cout << "New Hash:      " << current_hash << endl;

        last_hash = current_hash;
        return true;
    }
    return false;
}

string FileMonitor::calculate_hash() {
    // Opening in BINARY mode is critical
    ifstream file(monitored_path, ios::binary);
    if (!file.good()) return "";

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    const int buffer_size = 4096;
    vector<char> buffer(buffer_size);

    while (file.read(buffer.data(), buffer_size)) {
        SHA256_Update(&sha256, buffer.data(), file.gcount());
    }
    SHA256_Update(&sha256, buffer.data(), file.gcount());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}