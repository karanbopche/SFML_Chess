#pragma once

#include <map>
#include <SFML/Audio.hpp>
#include "Manager/Manager.h"

constexpr const std::string_view soundBufferManagerSectionKey = "soundBufferMap";

using SoundBufferManager = Manager<sf::SoundBuffer, soundBufferManagerSectionKey>;
