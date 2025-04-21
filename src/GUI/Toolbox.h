#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "MazeStuff.h"
#include "Button.h"

class Toolbox {


    Toolbox();
    static Toolbox* instance;
    friend class Button;
    friend class MazeStuff;
    friend void render();
    friend void gameLoop();
    sf::Texture debugTexture;
    sf::Sprite debugSprite;

public:
    sf::RenderWindow window;
    Button* debugButton;
    static Toolbox &getInstance();
};



#endif //TOOLBOX_H