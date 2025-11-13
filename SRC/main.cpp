#include <iostream>
#include <windows.h>
#include "nw_config.h"
#include "nw_network.h"

void LaunchClient()
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(
        NWConfig::CLIENT_EXE.c_str(),
        NULL,
        NULL, NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si, &pi))
    {
        std::cout << "[!] Failed to start GameClient.exe\n";
        return;
    }
}

int main()
{
    std::cout << "Neverwinter Launcher - Native Edition\n";
    std::cout << "Server: " << NWConfig::SERVER_IP << "\n\n";

    if (!ConnectToServer(NWConfig::SERVER_IP, NWConfig::LOGIN_PORT))
        return 1;
    if (!ConnectToServer(NWConfig::SERVER_IP, NWConfig::ACCOUNT_PORT))
        return 1;
    if (!ConnectToServer(NWConfig::SERVER_IP, NWConfig::GAME_PORT))
        return 1;

    std::cout << "[+] All server ports reachable! Starting client...\n";
    LaunchClient();
    return 0;
}
