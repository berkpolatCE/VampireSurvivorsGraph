#include "ReadMemory.h"
#include "CharacterData.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "ImGuiSDLSetup.h"
#include "implot.h"

const size_t MAX_DATA_POINTS = 1000;

std::string formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;

    return formattedTime.str();
}

int main(int, char**) {
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context = nullptr;

    if (!InitImGuiSDL(window, gl_context)) {
        return -1;
    }

    // Initialize ImPlot
    ImPlot::CreateContext();

    GetProcessData();

    // Data vectors
    std::vector<float> healthData;
    std::vector<float> timeData;
    std::vector<float> experienceData;
    
    // Toggles
    bool infiniteHealth = false;

    // Main loop
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }

        // Start the ImGui frame
        StartImGuiFrame();

        // Collect health and time data
        float currentHealth = GetHealth();
        float currentTime = GetTime();
        float currentExperience = GetExperience();
        
        healthData.push_back(currentHealth);
        timeData.push_back(currentTime);
        experienceData.push_back(currentExperience);

        // ImGui Code Here
        ImGui::Begin("Game Data");

        if (ImPlot::BeginPlot("Health Data")) {
            ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 1), 2.0f);
            ImPlot::PlotLine("Health", timeData.data(), healthData.data(), timeData.size());
            ImPlot::EndPlot();
        }
        if(ImPlot::BeginPlot("Experience Data")) {
            ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 2.0f);
			ImPlot::PlotLine("Experience", timeData.data(), experienceData.data(), timeData.size());
			ImPlot::EndPlot();
		}
        ImGui::Text("Health: %.2f", currentHealth);
        ImGui::Text("Experience: %.2f", currentExperience);
        ImGui::Text("Time: %s", formatTime(static_cast<int>(currentTime)).c_str());
        // Infinite Health
        ImGui::Checkbox("Infinite Health", &infiniteHealth);
        if (infiniteHealth) {
            SetInfiniteHealth();
        }
        // Add 1000 Experience
        if (ImGui::Button("Add 1000 Experience")) {
			Add1000Experience();
		}
        ImGui::End();

        // Rendering
        RenderImGuiFrame();
        SDL_GL_SwapWindow(window);
    }

    // Cleanup ImPlot
    ImPlot::DestroyContext();

    CleanupImGuiSDL(window, gl_context);

    return 0;
}    