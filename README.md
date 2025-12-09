# Sentinel HIDS v5.0 (Service Edition) 🛡️

![Status](https://img.shields.io/badge/Status-Stable-brightgreen.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows_Service-0078D6.svg)
![Network](https://img.shields.io/badge/network-Discord_Webhooks-7289da.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

**Sentinel** is a high-performance **Host-based Intrusion Detection System (HIDS)** designed to run as a native **Windows Service**. It features automatic environment detection, multi-threading, and real-time Discord alerting.

The project demonstrates advanced system programming, utilizing Windows API for service management, `std::thread` for parallel processing, and OpenSSL for cryptographic integrity checks.

## 🚀 New in v5.0

* **Windows Service Support:** Runs natively in the background using the Windows Service API.
* **Auto-Detection:** Automatically detects if it's running as a Service or in Console Mode - no command line flags required.
* **Self-Healing Paths:** Automatically adjusts the working directory to the executable location (fixing common `System32` path errors).
* **Multi-threading:** FIM and Log Analysis run on separate, synchronized threads for maximum performance.

## 🛠️ Key Features

* **File Integrity Monitoring (FIM):** Detects unauthorized modifications to critical files using **SHA-256** hashing.
* **Log Analysis (SIEM):** Real-time parsing of system logs to detect Brute Force attacks using Regex heuristics.
* **Network Alerting:** Sends instant security notifications to a **Discord Channel**.
* **Daemon Mode:** Designed to run 24/7 without user login.
* **Portable:** Can be deployed to any directory; configuration is relative to the executable.

## ⚙️ Configuration (`config.json`)

Ensure `config.json` is located in the same directory as `Sentinel.exe`.

```json
{
  "fim_target": "test.txt",
  "log_target": "system.log",
  "check_interval_ms": 2000,
  "discord_webhook": "YOUR_DISCORD_WEBHOOK_URL"
}
```

> **Note:** If `discord_webhook` is empty or missing, Sentinel automatically switches to **Local Mode** (alerts printed to console only).

## 📥 Build & Deployment

### 1. Prerequisites

* C++ Compiler (MSVC recommended for Windows Services)
* CMake (3.10+)
* vcpkg

### 2. Build Source

```bash
git clone https://github.com/AntekKozlowski/Sentinel-HIDS.git
cd Sentinel-HIDS
mkdir build && cd build

vcpkg install openssl:x64-windows nlohmann-json:x64-windows cpr:x64-windows

cmake .. -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### 3. Deploy as Service (Administrator)

**Prepare Directory:** Create `C:\\Sentinel`.

**Copy Files:**

* `Sentinel.exe`
* `config.json`
* `libcrypto-3-x64.dll`, `libssl-3-x64.dll`, `zlib1.dll`

**Install Service:**

```cmd
sc create Sentinel binPath= "C:\\Sentinel\\Sentinel.exe" start= auto
```

**Start Service:**

```cmd
sc start Sentinel
```

## 🕹️ Control & Usage

**Console Mode:** Run `Sentinel.exe` manually.

**Service Mode:**

```cmd
sc stop Sentinel
sc delete Sentinel
```

## 🔮 Roadmap

* [x] **v4.0:** Discord Integration & Network Module.
* [x] **v5.0:** Windows Service Mode (Background Daemon).
* [ ] **v6.0:** Multi-threading optimization for parallel processing.
* [ ] Syslog Integration for remote logging.

## 👨‍💻 Author

**Antoni Kozłowski**
*Cybersecurity Student & C++ Developer*

---

```
Project created for educational purposes to explore defensive security tools development.
```
