#pragma once
#ifndef VAMPIRESURVIVORS_CHARACTERDATA_H
#define VAMPIRESURVIVORS_CHARACTERDATA_H

#include "ReadMemory.h"

extern const char* processName;
extern const char* moduleName;

extern DWORD processID;
extern HANDLE processHandle;
extern uintptr_t baseAddress;

void GetProcessData();
float GetHealth();
float GetTime();
float GetExperience();

void SetInfiniteHealth();
void Add1000Experience();

#endif // VAMPIRESURVIVORS_CHARACTERDATA_H