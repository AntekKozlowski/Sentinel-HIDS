# Sentinel HIDS 🛡️

![Status](https://img.shields.io/badge/Status-Active_Development-brightgreen.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

**Sentinel** is a lightweight, high-performance **Host-based Intrusion Detection System (HIDS)** developed in modern C++. It provides real-time monitoring of system integrity and analyzes logs for suspicious patterns.

The project demonstrates low-level system programming, cryptographic operations using OpenSSL, and robust resource management.

## 🚀 Key Features

* **File Integrity Monitoring (FIM):** Detects unauthorized modifications to critical files using **SHA-256** hashing (OpenSSL).
* **Log Analysis (SIEM):** Real-time parsing of system logs to detect brute-force attacks using Regex heuristics.
* **JSON Configuration:** Fully configurable via `config.json`—no recompilation needed.
* **Portable Architecture:** Runs directly from the build folder; automatically handles relative file paths.
* **Efficient Resource Usage:** Optimized polling loop with configurable intervals and chunk-based file reading.

## 🛠️ Tech Stack

* **Core Language:** C++17
* **Build System:** CMake
* **Libraries:**
  * `OpenSSL` (Cryptographic functions)
  * `nlohmann/json` (Configuration parsing)
* **Package Manager:** vcpkg

## ⚙️ Configuration (`config.json`)

Sentinel uses a JSON file for configuration. It must be located in the same directory as the executable.

```json
{
  "fim_target": "test.txt",       // Path to the file monitored for integrity changes
  "log_target": "system.log",     // Path to the log file analyzed for attacks
  "check_interval_ms": 2000        // Scanning interval in milliseconds
}
```

## 📥 Getting Started

### Prerequisites
- C++ Compiler (MSVC, GCC, or Clang)
- CMake (3.10 or higher)
- vcpkg package manager

### Installation & Build

Clone the repository:

```bash
git clone https://github.com/AntekKozlowski/Sentinel-HIDS.git
cd Sentinel-HIDS
```

Install dependencies:

```bash
vcpkg install openssl:x64-windows nlohmann-json:x64-windows
```

Build with CMake:

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

Run Sentinel (ensure `config.json` is present in the executable directory):

```bash
./Sentinel.exe
```

## 🔮 Roadmap
- [ ] Syslog Integration for remote logging.
- [ ] Windows Service / Linux Daemon mode.
- [ ] Webhook Alerts (Discord/Slack).
- [ ] Multi-threading for parallel FIM & LogWatcher processing.

## 👨‍💻 Author

**Antoni Kozłowski**
*Cybersecurity Student & C++ Developer*

---
*Project created for educational purposes to explore defensive security tools development.*
