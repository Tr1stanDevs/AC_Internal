#include "TD_Logging.hpp"
#include "TD_GetPidFromProcName.h"
#include <handleapi.h>
#include <iostream>
#include <ostream>
#include <synchapi.h>
#include <windows.h>
#include <filesystem>

int main() {
    TD_Logging::Init();
    TD_Logging::Settings = 0;
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BOLD | TD_Logging::LoggingLevels::LogLevel_ALL;

    const wchar_t* GameName = L"ac_client.exe";
    std::filesystem::path path = std::filesystem::current_path() / "AC_DLL.dll";

    DWORD PID = 0;

     while (PID == 0) {
        TD_Logging::print("%s\n", TD_Logging::LoggingLevels::LogLevel_WARN, "Looking for ac_client.exe!");
        PID = TD_GetPidFromProcNameW(GameName);
        Sleep(500);
        if (PID != 0) break;
    };

    TD_Logging::print("%s%d\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, "Found ac_client.exe with PID: ", PID);

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    LPVOID remotePath = VirtualAllocEx(hProc, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    

    SIZE_T BytesWrote;
    WriteProcessMemory(hProc, remotePath, path.string().c_str(), strlen(path.string().c_str())+1, &BytesWrote);
    TD_Logging::print("Wrote %d bytes for the Path!\n", TD_Logging::LoggingLevels::LogLevel_INFO, BytesWrote);

    HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, remotePath, 0, NULL);

    WaitForSingleObject(hThread, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeThread(hThread, &exitCode); // exitCode ist das HMODULE der geladenen DLL
    if (exitCode == 0) {
        TD_Logging::print("DLL failed to Load at: %p\n", TD_Logging::LoggingLevels::LogLevel_ERROR, remotePath);
    } else {
        TD_Logging::print("DLL Loaded at: %pn", TD_Logging::LoggingLevels::LogLevel_SUCCESS, remotePath);
    }

    if (hProc) CloseHandle(hThread);
    if (hThread) CloseHandle(hThread);
    

    Sleep(5000);
    return 0;
}