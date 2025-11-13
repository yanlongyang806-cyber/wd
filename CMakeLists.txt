cmake_minimum_required(VERSION 3.10)
project(NativeNWLauncher)

set(CMAKE_CXX_STANDARD 17)

# Windows networking
if (WIN32)
    set(WINSOCK_LIBS ws2_32)
endif()

add_executable(NativeNWLauncher
    src/main.cpp
    src/nw_network.cpp
)

target_link_libraries(NativeNWLauncher ${WINSOCK_LIBS})
