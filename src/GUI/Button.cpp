#include "Button.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>



Button::Button(sf::Vector2f pos, std::function<void()> onClick) {
    position = pos;
    clicky = onClick;
    sprite = nullptr;
}
sf::Vector2f Button::getPosition() {
    return position;
}
sf::Sprite* Button::getSprite() {
    return sprite;
}
void Button::setSprite(sf::Sprite *new_sprite) {
    sprite = new_sprite;
}
void Button::onClick() {
    if (clicky) {
        clicky();
    }
}