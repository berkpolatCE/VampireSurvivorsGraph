#pragma once
#ifndef IMGUI_SDL_SETUP_H
#define IMGUI_SDL_SETUP_H

#include <SDL.h>
#include <SDL_opengl.h>
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"
#include <iostream>

bool InitImGuiSDL(SDL_Window*& window, SDL_GLContext& gl_context);
void StartImGuiFrame();
void RenderImGuiFrame();
void CleanupImGuiSDL(SDL_Window* window, SDL_GLContext gl_context);

#endif // IMGUI_SDL_SETUP_H