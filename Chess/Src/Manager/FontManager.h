#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Manager/Manager.h"

constexpr const std::string_view fontManagerSectionKey = "fontMap";

using FontManager = Manager<sf::Font, fontManagerSectionKey>;
