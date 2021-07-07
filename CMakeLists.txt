cmake_minimum_required(VERSION 3.16.3)
project(kasperskyTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(scan_service
        src/scan_service/main.cpp
        src/scan_service/DirectoryScanner.cpp
        src/scan_service/ScanReport.cpp
        src/scan_service/FileScanner.cpp
        src/Pipe.cpp
        )

add_executable(scan_util
        src/scan_util/main.cpp
        src/Pipe.cpp
        )

target_link_libraries(scan_service pthread)
