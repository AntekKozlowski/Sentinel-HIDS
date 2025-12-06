# Sentinel HIDS v4.0 (Network Edition) 🛡️

![Status](https://img.shields.io/badge/Status-Stable-brightgreen.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![Network](https://img.shields.io/badge/network-Discord_Webhooks-7289da.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

**Sentinel** is a lightweight, high-performance **Host-based Intrusion Detection System (HIDS)** developed in modern C++. It provides real-time monitoring of system integrity, analyzes logs for suspicious patterns, and **sends instant security alerts via Discord**.

The project demonstrates low-level system programming, cryptographic operations using OpenSSL, REST API communication, and robust resource management.

## 🚀 Key Features

* **File Integrity Monitoring (FIM):** Detects unauthorized modifications to critical files using **SHA-256** hashing (OpenSSL).
* **Log Analysis (SIEM):** Real-time parsing of system logs to detect Brute Force attacks using Regex heuristics.
* **Network Alerting:** Sends real-time notifications to a **Discord Channel** using Webhooks.
* **JSON Configuration:** Fully configurable via `config.json` - change targets or webhooks without recompiling.
* **Portable Architecture:** Runs directly from the build folder with automatic path handling.

## 🛠️ Tech Stack

* **Core Language:** C++17 (STL, `std::filesystem`, `std::vector`)
* **Build System:** CMake
* **Package Manager:** vcpkg
* **Libraries:**
  * `OpenSSL` (Cryptographic functions)
  * `nlohmann/json` (Configuration parsing)
  * `cpr` (C++ Requests - Network communication)

## ⚙️ Configuration (`config.json`)

Sentinel uses a JSON file for configuration. It must be located in the same directory as the executable.

```json
{
  "fim_target": "test.txt",       // Path to the file monitored for integrity
  "log_target": "system.log",     // Path to the log file analyzed for attacks
  "check_interval_ms": 2000,      // Scanning interval in milliseconds
  "discord_webhook": "YOUR_DISCORD_WEBHOOK_URL"
}
````

> **Note:** If `discord_webhook` is empty or missing, Sentinel automatically switches to **Local Mode** (alerts printed to console only).

## 📥 Getting Started

### Prerequisites

  - C++ Compiler (MSVC, GCC, or Clang)
  - CMake (3.10 or higher)
  - [vcpkg](https://github.com/microsoft/vcpkg) package manager

### Installation & Build

1.  **Clone the repository:**

    ```bash
    git clone [https://github.com/AntekKozlowski/Sentinel-HIDS.git](https://github.com/AntekKozlowski/Sentinel-HIDS.git)
    cd Sentinel-HIDS
    ```

2.  **Install dependencies:**

    ```bash
    vcpkg install openssl:x64-windows nlohmann-json:x64-windows cpr:x64-windows
    ```

3.  **Build with CMake:**

    ```bash
    mkdir build
    cd build
    # Note: Adjust the vcpkg path if necessary
    cmake .. -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
    cmake --build .
    ```

4.  **Run Sentinel:**
    Ensure `config.json` is present in the executable directory (CMake handles copying automatically).

    ```bash
    ./Sentinel.exe
    ```

## 🔮 Roadmap

  - [x] **v4.0:** Discord Integration & Network Module.
  - [ ] **v5.0:** Windows Service Mode (Background Daemon).
  - [ ] **v6.0:** Multi-threading optimization for parallel processing.
  - [ ] Syslog Integration for remote logging.

## 👨‍💻 Author

**Antoni Kozłowski**
*Cybersecurity Student & C++ Developer*

-----

*Project created for educational purposes to explore defensive security tools development.*

```
```