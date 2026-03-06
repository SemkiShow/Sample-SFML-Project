// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <SFML/System/Vector2.hpp>

extern bool isSettings;
extern int menuOffset;
extern sf::Vector2i windowSize;

void DrawSettings(bool* isOpen);
void DrawMenuBar();
