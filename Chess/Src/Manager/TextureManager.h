#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Manager/Manager.h"

constexpr std::string_view textureManagerSectionKey = "textureMap";

using TextureManager = Manager<sf::Texture, textureManagerSectionKey>;
