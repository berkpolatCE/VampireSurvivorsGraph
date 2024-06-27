#include "CharacterData.h"

const char* processName = "VampireSurvivors.exe";
const char* moduleName = "GameAssembly.dll";

DWORD processID;
HANDLE processHandle;
uintptr_t baseAddress;

void GetProcessData() {
    processID = ReadMemory::GetProcessId(processName);
    processHandle = ReadMemory::GetProcessHandle(processID);
    baseAddress = ReadMemory::GetModuleBaseAddress(processID, moduleName);
}

float GetHealth() {
    float health = 0.0f;
    uintptr_t healthBaseAddress = baseAddress + 0x04706F50;
    std::vector<uintptr_t> offsets = { 0xB8, 0x0, 0x268, 0x188 };
    uintptr_t healthAddress = healthBaseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
        healthAddress = ReadMemory::ReadMemory<uintptr_t>(processHandle, healthAddress);
        healthAddress += offsets[i];
    }
    health = ReadMemory::ReadMemory<float>(processHandle, healthAddress);
    if (health < 0) {
		health = 0;
        std::cout << "Either dead, not in game, or you have to press ESC once in game and try again.\n";
	}
    return health;
}

float GetTime() {
    float time = 0.0f;
    uintptr_t timeBaseAddress = baseAddress + 0x04706F50;
    std::vector<uintptr_t> offsets = { 0xB8, 0x0, 0x300 };
    uintptr_t timeAddress = timeBaseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
		timeAddress = ReadMemory::ReadMemory<uintptr_t>(processHandle, timeAddress);
		timeAddress += offsets[i];
	}
    time = ReadMemory::ReadMemory<float>(processHandle, timeAddress);
    if (time <= 0) {
        std::cout << "Start a game to get the time value.\n";
    }
    return time;
}

float GetExperience() {
    float experience = 0.0f;
    uintptr_t experienceBaseAddress = baseAddress + 0x04706F50;
    std::vector<uintptr_t> offsets = { 0xB8, 0x0, 0x268, 0x19C };
    uintptr_t experienceAddress = experienceBaseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
		experienceAddress = ReadMemory::ReadMemory<uintptr_t>(processHandle, experienceAddress);
		experienceAddress += offsets[i];
	}
    experience = ReadMemory::ReadMemory<float>(processHandle, experienceAddress);
	if (experience < 0) {
		experience = 0;
		std::cout << "Either dead, not in game, or you have to press ESC once in game and try again.\n";
	}
	return experience;
}

void SetInfiniteHealth() {
    uintptr_t healthBaseAddress = baseAddress + 0x04706F50;
    std::vector<uintptr_t> offsets = { 0xB8, 0x0, 0x268, 0x188 };
    uintptr_t healthAddress = healthBaseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
        healthAddress = ReadMemory::ReadMemory<uintptr_t>(processHandle, healthAddress);
        healthAddress += offsets[i];
    }
    ReadMemory::WriteMemory<float>(processHandle, healthAddress, 9999.9f);
}

void Add1000Experience() {
    uintptr_t experienceBaseAddress = baseAddress + 0x04706F50;
    std::vector<uintptr_t> offsets = { 0xB8, 0x0, 0x268, 0x19C };
    uintptr_t experienceAddress = experienceBaseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
        experienceAddress = ReadMemory::ReadMemory<uintptr_t>(processHandle, experienceAddress);
        experienceAddress += offsets[i];
    }
    float currentExperience = ReadMemory::ReadMemory<float>(processHandle, experienceAddress);
    ReadMemory::WriteMemory<float>(processHandle, experienceAddress, currentExperience + 1000.0f);
}