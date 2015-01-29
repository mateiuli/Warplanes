#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sstream>

template <typename T>
std::string toString(const T& value);
std::string toString(sf::Keyboard::Key key);
float toRadian(float degree);
float toDegree(float radian);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text&		text);

/* Vector operations */
sf::Vector2f unitVector(sf::Vector2f vector);

#include "Utility.inl"

#endif
