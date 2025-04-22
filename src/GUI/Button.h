#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>

class Button {

    sf::Sprite* sprite;
    sf::Vector2f position;
    std::function<void(void)> clicky;

public:
    friend class Toolbox;
    friend class MazeStuff;
    Button(sf::Vector2f pos, std::function<void(void)> onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* new_sprite);
    void onClick();
};



#endif //BUTTON_H