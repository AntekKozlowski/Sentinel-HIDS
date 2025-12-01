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
    // Establish a baseline hash upon initialization
    last_hash = calculate_hash();
}

bool FileMonitor::check() {
    // 1. Verify file existence (Defense against deletion attacks)
    if (!filesystem::exists(monitored_path)) {
        cerr << "[ERROR] Monitored file missing: " << monitored_path << endl;
        return false;
    }

    // 2. Calculate current fingerprint
    string current_hash = calculate_hash();

    // 3. Compare against baseline
    if (current_hash != last_hash) {
        cout << "\n[!!! INTEGRITY ALERT !!!] Unauthorized file modification: " << monitored_path << endl;
        cout << "Baseline Hash: " << last_hash << endl;
        cout << "Current Hash:  " << current_hash << endl;

        // Update baseline to prevent alert flooding
        last_hash = current_hash;
        return true;
    }
    return false;
}

string FileMonitor::calculate_hash() {
    // Open file in BINARY mode to ensure consistent hashing across platforms
    ifstream file(monitored_path, ios::binary);
    if (!file.good()) return "";

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // Read file in 4KB chunks to optimize memory usage for large files
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