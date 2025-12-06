cmake_minimum_required (VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/anton/source/repos/vcpkg/scripts/buildsystems/vcpkg.cmake")

project ("Sentinel")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find packages (OpenSSL + JSON)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

add_executable (Sentinel 
    "Sentinel/main.cpp" 
    "Sentinel/FileMonitor.cpp"
    "Sentinel/FileMonitor.h"
    "Sentinel/LogWatcher.cpp"
    "Sentinel/LogWatcher.h"
    "Sentinel/AlertSender.cpp" 
    "Sentinel/AlertSender.h")

# 2. Link libraries
target_link_libraries(Sentinel PRIVATE 
    OpenSSL::SSL 
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    cpr::cpr
)

# 3. Config copy
configure_file("Sentinel/config.json" "config.json" COPYONLY)
configure_file("Sentinel/test.txt" "test.txt" COPYONLY)
