cmake_minimum_required (VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/anton/source/repos/vcpkg/scripts/buildsystems/vcpkg.cmake")

project ("Sentinel")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable (Sentinel "Sentinel/main.cpp" "Sentinel/FileMonitor.h" "Sentinel/FileMonitor.cpp")

target_link_libraries(Sentinel PRIVATE OpenSSL::SSL OpenSSL::Crypto)