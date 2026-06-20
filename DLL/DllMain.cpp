// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "TD_Logging.hpp"
#include <TD_GetModuleBaseAddress.h>
#include <synchapi.h>


void WINAPI Hack(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    

    TD_Logging::Init();
    TD_Logging::Settings = 0;
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BOLD | TD_Logging::LoggingLevels::LogLevel_ALL;

    TD_Logging::print("%s\n\n", TD_Logging::LoggingLevels::LogLevel_INFO, "Assault Cube Cheat by 1113_1113");

    uintptr_t PlayerObjOffset =                 0x17E0A8;
    uintptr_t EntityListOffset =                0x18AC04;
    uintptr_t CurrentPlayersOffset =            0x18AC0C;

    uintptr_t healthOffsetUI =                  0x00EC;               
    uintptr_t NameOffset =                      0x0010;
    uintptr_t TotalShotsFiredOffest =           0x0188;                
    uintptr_t SecondaryWeaponAmmoOffset =       0x012C;              
    uintptr_t SecondaryReloadingAmmoOffset =    0x0108;              
    uintptr_t AssaultRifeReloadingAmmoOffset =  0x011C;               
    uintptr_t GrandesOffset =                   0x0144;                
    uintptr_t AssaultRifleAmmoOffset  =         0x0140;                
    uintptr_t AmorOffset =                      0x00F0;               

    uintptr_t RealHealthOffset =                0x0408; //0xD010 //this is the offset to the entity *
    uintptr_t HealthPTRChainOffset =            0xD010; // 0x18B0B8 PlayerObjOffset

    uintptr_t EnemyNameOffset =                 0x0205;

    uintptr_t mod_base = (uintptr_t)GetModuleHandleW(L"ac_client.exe");
    if (mod_base == 0) {
        TD_Logging::print("Cant find ac_client.exe!", TD_Logging::LoggingLevels::LogLevel_ERROR, "");
        return;
    }

        size_t CurrentPlayersInMatch = *(size_t*)(mod_base + CurrentPlayersOffset);
        std::cout << CurrentPlayersInMatch << std::endl;


        size_t* RealPlayerList = (size_t*)*(size_t*)(mod_base + EntityListOffset);
        std::cout << RealPlayerList << std::endl;

        for(size_t i = 1; i <= CurrentPlayersInMatch-1; i++) {
            if ((size_t*)*(RealPlayerList+i) == nullptr) break;
            size_t* target = (size_t*)(RealPlayerList+i); //+1 = index
            

            std::cout << target << std::endl;
            std::cout << "Player is at: " << (size_t*)*target << std::endl;
            uintptr_t TargetPlayer = (uintptr_t)*target;
            TD_Logging::print("Name is: %s\n", TD_Logging::LoggingLevels::LogLevel_ERROR, reinterpret_cast<const char*>((size_t*)(TargetPlayer + EnemyNameOffset)));
            std::cout << "-------------------------------\n";
        }

    TD_Logging::print("Module Base: 0x%p\n\n", TD_Logging::LoggingLevels::LogLevel_INFO, mod_base);
    Sleep(1e3);

    
    uintptr_t LocalPlayer = *(uintptr_t*)(mod_base+PlayerObjOffset);
    uintptr_t Healthaddr = **(uintptr_t**)(mod_base + PlayerObjOffset + HealthPTRChainOffset);


    TD_Logging::print("Player OBJ at: 0x%p\n", TD_Logging::LoggingLevels::LogLevel_INFO, LocalPlayer);
    TD_Logging::print("Current Health at: 0x%p\n", TD_Logging::LoggingLevels::LogLevel_INFO, (Healthaddr + RealHealthOffset) );
    TD_Logging::print("Current Ammo at: 0x%p\n", TD_Logging::LoggingLevels::LogLevel_INFO, (uintptr_t*)(LocalPlayer + AssaultRifleAmmoOffset) );

    TD_Logging::print("Current Health: %lu\n", TD_Logging::LoggingLevels::LogLevel_INFO, *(int*)(Healthaddr + RealHealthOffset) );
    TD_Logging::print("Current Ammo: %lu\n", TD_Logging::LoggingLevels::LogLevel_INFO, *(uintptr_t*)(LocalPlayer + AssaultRifleAmmoOffset));
    


    *(int*)(LocalPlayer + GrandesOffset) = 999;
    *(int*)(LocalPlayer + AmorOffset) = 999;

    *(int*)(LocalPlayer + SecondaryWeaponAmmoOffset) = 999;
    *(int*)(LocalPlayer + SecondaryReloadingAmmoOffset) = 999;

    *(int*)(LocalPlayer + AssaultRifeReloadingAmmoOffset) = 999;
    *(int*)(LocalPlayer + AssaultRifleAmmoOffset) = 999;

    *(int*)(Healthaddr + RealHealthOffset) = 999;
    *(int*)(LocalPlayer + healthOffsetUI) = 999;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Hack, hModule, 0, nullptr));
    }
    return TRUE;
}