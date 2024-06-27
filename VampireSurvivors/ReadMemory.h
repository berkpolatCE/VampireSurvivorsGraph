#pragma once
#ifndef VAMPIRESURVIVORS_READMEMORY_H
#define VAMPIRESURVIVORS_READMEMORY_H

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <iostream>

namespace ReadMemory {
    DWORD GetProcessId(const char* processName);
    HANDLE GetProcessHandle(DWORD processId);
    uintptr_t GetModuleBaseAddress(DWORD processId, const char* moduleName);

    // Template function needs to be defined in the header file to avoid linker errors
    template <typename T>
    T ReadMemory(HANDLE processHandle, uintptr_t address) {
        T buffer;
        ReadProcessMemory(processHandle, (LPCVOID)address, &buffer, sizeof(T), nullptr);
        return buffer;
    }
    template <typename T>
    void WriteMemory(HANDLE processHandle, uintptr_t address, const T& value) {
        WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(T), NULL);
    }
}

#endif // VAMPIRESURVIVORS_READMEMORY_H