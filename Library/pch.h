// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// add headers that you want to pre-compile here

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <math.h>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>

using Color = sf::Color;
using Point = sf::Vector2f;
using Window = sf::RenderWindow;

const float TIME_SCALING = 1;

#endif //PCH_H
