# Sentinel HIDS 🛡️

![Status](https://img.shields.io/badge/Status-Work_in_Progress-yellow.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![Security](https://img.shields.io/badge/crypto-OpenSSL-red.svg)

**Sentinel** is a lightweight, high-performance **Host-based Intrusion Detection System (HIDS)** developed in modern C++. It is designed to protect system integrity by monitoring critical files for unauthorized modifications in real-time.

The project demonstrates low-level system programming, cryptographic operations using OpenSSL, and robust resource management.

## 🚀 Key Features

* **File Integrity Monitoring (FIM):** Continuously monitors specified critical files (e.g., config files, hosts, system binaries).
* **Cryptographic Verification:** Utilizes **SHA-256** (via OpenSSL) to generate unique fingerprints for file verification.
* **Smart Polling Engine:** optimized detection loop that minimizes CPU usage while maintaining high alert responsiveness.
* **Memory Efficiency:** Implements chunk-based file reading to handle large files without consuming excessive RAM.
* **Modern Architecture:** Written in C++17 using Object-Oriented Programming (OOP) principles.

## 🛠️ Tech Stack

* **Core Language:** C++17 (STL, `std::filesystem`, `std::vector`, `std::thread`)
* **Build System:** CMake
* **Cryptography:** OpenSSL (linked via vcpkg)
* **Version Control:** Git & GitHub

## ⚙️ How It Works

1.  **Baseline Acquisition:** Upon startup, Sentinel scans the target files and calculates their initial SHA-256 hashes. This establishes a "trusted state".
2.  **Monitoring Daemon:** The system enters an infinite monitoring loop (daemon mode).
3.  **Change Detection:** Periodically re-calculates hashes and compares them against the baseline.
4.  **Alerting:** If `Current_Hash != Baseline_Hash`, a security alert is triggered immediately, identifying the compromised file.

## 📥 Getting Started

### Prerequisites

* C++ Compiler (MSVC, GCC, or Clang)
* CMake (3.10 or higher)
* [vcpkg](https://github.com/microsoft/vcpkg) (package manager for OpenSSL)

### Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/AntekKozlowski/Sentinel-HIDS.git](https://github.com/AntekKozlowski/Sentinel-HIDS.git)
    cd Sentinel-HIDS
    ```

2.  **Install OpenSSL dependencies:**
    ```bash
    vcpkg install openssl:x64-windows
    ```

3.  **Build with CMake:**
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
    cmake --build .
    ```

4.  **Run Sentinel:**
    ```bash
    ./Sentinel.exe
    ```

## 🔮 Roadmap

* [ ] Integration with Syslog for remote logging.
* [ ] Log Watcher module (detecting brute-force attacks in `auth.log`).
* [ ] JSON configuration file support.
* [ ] Windows Service / Linux Daemon mode.

## 👨‍💻 Author

**[YOUR NAME]**
*Cybersecurity Student & C++ Developer*

---
*Project created for educational purposes to explore defensive security tools development.*