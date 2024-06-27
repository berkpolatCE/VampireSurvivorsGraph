#include "ReadMemory.h"


// Get the process id of the specified process
DWORD ReadMemory::GetProcessId(const char* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);
        if (Process32First(snapshot, &processEntry)) {
            do {
                if (strcmp(processEntry.szExeFile, processName) == 0) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }
    else {
        std::cout << "Error: " << GetLastError() << std::endl;
        exit(1);
    }
    if (processId == 0) {
        std::cout << "Error: Process not found" << std::endl;
        exit(2);
    }
    return processId;
}
// Get the handle of the specified process
HANDLE ReadMemory::GetProcessHandle(DWORD processId) {
    if (processId == 0) {
        std::cout << "Error: Invalid process id" << std::endl;
        exit(3);
    }
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (processHandle == NULL) {
        std::cout << "Error: " << GetLastError() << std::endl;
        exit(4);
    }
    return processHandle;
}
// Get the base address of the specified module
uintptr_t ReadMemory::GetModuleBaseAddress(DWORD processId, const char* moduleName) {
    uintptr_t moduleBaseAddress = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 moduleEntry;
        moduleEntry.dwSize = sizeof(moduleEntry);
        if (Module32First(snapshot, &moduleEntry)) {
            do {
                if (strcmp(moduleEntry.szModule, moduleName) == 0) {
                    moduleBaseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                    break;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }
        CloseHandle(snapshot);
    }
    else {
        std::cout << "Error: " << GetLastError() << std::endl;
        exit(5);
    }
    return moduleBaseAddress;
}
