// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Settings.hpp"
#include "UI.hpp"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp> // IWYU pragma: keep
#include <iostream>

int main()
{
    settings.Load();

    // SFML init
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(windowSize.x),
                                           static_cast<unsigned int>(windowSize.y)}),
                            "Sample-SFML-Project");
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(settings.vsync);

    // imgui SFML init
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "Failed to init imgui-sfml!\n";
        return 1;
    }

    sf::Font font("assets/JetBrainsMonoNerdFont-Medium.ttf");
    sf::Text fpsText(font);
    fpsText.setPosition({0, menuOffset * 1.f});
    fpsText.setString(std::to_string(123));
    fpsText.setFillColor(sf::Color(0, 255, 255));
    fpsText.setCharacterSize(24);

    sf::Clock deltaTimeClock;
    sf::Time deltaTime;
    sf::Clock delayClock;
    bool lastVsync = settings.vsync;

    // Main loop
    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (lastVsync != settings.vsync)
        {
            lastVsync = settings.vsync;
            window.setVerticalSyncEnabled(settings.vsync);
        }

        window.clear();

        DrawMenuBar();
        if (isSettings) DrawSettings(&isSettings);

        if (delayClock.getElapsedTime().asSeconds() >= 0.3)
        {
            delayClock.restart();
            fpsText.setString("FPS: " + std::to_string((int)(1 / deltaTime.asSeconds())));
        }
        if (settings.showFPS) window.draw(fpsText);

        ImGui::SFML::Render(window);
        window.display();
    }

    settings.Save();
    ImGui::SFML::Shutdown();
}
