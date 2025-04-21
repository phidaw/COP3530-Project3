#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "MazeStuff.h"
#include "Button.h"
#include "Tiles.h"

Toolbox* Toolbox::instance = nullptr;

Toolbox::Toolbox() {
    window.create(sf::VideoMode(1520, 951), "Maze Maestro"); //Biggest size that looks ok is 1500 * 900
    debugButton = new Button(sf::Vector2f(20, 515), [this]{test();});
    if (!debugTexture.loadFromFile("images/MiniMazeTile.png")) { //Replace debug with image name, this also loads the images into the code
        std::cerr << "Failed to load debug texture"; //Replace with proper error message
    }
    else { //This creates the sprite of the button, and places it in pos, and assigns the sprite to the appropriate button
        debugSprite.setTexture(debugTexture);
        debugSprite.setPosition(debugButton->getPosition());
        debugButton->setSprite(&debugSprite);
    }
}
Toolbox &Toolbox::getInstance() {
    if (instance == nullptr) {
        instance = new Toolbox();
    }
    return *instance;
}