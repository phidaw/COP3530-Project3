#ifndef MAZESTUFF_H
#define MAZESTUFF_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Toolbox.h"
#include <SFML/Window.hpp>
#include <string>
using namespace std;


    void render(sf::Text question, sf::Text Answer, string answerAlt);
    void gameLoop();
    int launch();
    void test();




#endif //MAZESTUFF_H