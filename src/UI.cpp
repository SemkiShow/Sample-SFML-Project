// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "UI.hpp"
#include "Settings.hpp"
#include <imgui.h>

bool isSettings = false;
int menuOffset = 20;
sf::Vector2i windowSize = {16 * 50 * 2, 9 * 50 * 2};

void DrawSettings(bool* isOpen)
{
    if (!ImGui::Begin("Settings", isOpen))
    {
        ImGui::End();
        return;
    }
    ImGui::Checkbox("vsync", &settings.vsync);
    ImGui::Checkbox("show-fps", &settings.showFPS);
    ImGui::End();
}

void DrawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Settings"))
            {
                isSettings = true;
                DrawSettings(&isSettings);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return;
}
