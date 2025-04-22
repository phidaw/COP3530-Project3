#include "MazeStuff.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Toolbox.h"
#include <SFML/Window.hpp>
#include <string>
using namespace std;



int launch() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.MazeSize = 1;
    while (toolbox.window.isOpen()) {
        gameLoop();
    }
    return 0;
}
void render(){
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.window.clear();
    if (toolbox.OneUpButton->getSprite()) {
        toolbox.window.draw(*toolbox.OneUpButton->getSprite());
    }
    if (toolbox.FiveUpButton->getSprite()) {
        toolbox.window.draw(*toolbox.FiveUpButton->getSprite());
    }
    if (toolbox.TenUpButton->getSprite()) {
        toolbox.window.draw(*toolbox.TenUpButton->getSprite());
    }
    if (toolbox.HundredUpButton->getSprite()) {
        toolbox.window.draw(*toolbox.HundredUpButton->getSprite());
    }

    if (toolbox.OneDownButton->getSprite()) {
        toolbox.window.draw(*toolbox.OneDownButton->getSprite());
    }
    if (toolbox.FiveDownButton->getSprite()) {
        toolbox.window.draw(*toolbox.FiveDownButton->getSprite());
    }
    if (toolbox.TenDownButton->getSprite()) {
        toolbox.window.draw(*toolbox.TenDownButton->getSprite());
    }
    if (toolbox.HundredDownButton->getSprite()) {
        toolbox.window.draw(*toolbox.HundredDownButton->getSprite());
    }

    if (toolbox.MazeSize < 10 && toolbox.MazeSize >= 1) {
        sf::Sprite counter0 = toolbox.mineNumsSprite[toolbox.MazeSize];
        counter0.setPosition(1245, 140);
        toolbox.window.draw(counter0);
    }
    else if (toolbox.MazeSize >= 10 && toolbox.MazeSize < 100) {
        sf::Sprite counter1 = toolbox.mineNumsSprite[toolbox.MazeSize/10];
        sf::Sprite counter2 = toolbox.mineNumsSprite[toolbox.MazeSize%10];
        counter1.setPosition(1245, 140);
        counter2.setPosition(1266, 140);
        toolbox.window.draw(counter1);
        toolbox.window.draw(counter2);
    }
    else if (toolbox.MazeSize >= 100) {
        sf::Sprite counter3 = toolbox.mineNumsSprite[toolbox.MazeSize/100];
        sf::Sprite counter4 = toolbox.mineNumsSprite[(toolbox.MazeSize%100)/10];
        sf::Sprite counter5 = toolbox.mineNumsSprite[toolbox.MazeSize%10];
        counter3.setPosition(1245, 140);
        counter4.setPosition(1266, 140);
        counter5.setPosition(1287, 140);
        toolbox.window.draw(counter3);
        toolbox.window.draw(counter4);
        toolbox.window.draw(counter5);
    } //DO this for the maze but with a few for statements and an if at front to change sprite
    //for scaling

    if (toolbox.DijkstraButton->getSprite()) {
        toolbox.window.draw(*toolbox.DijkstraButton->getSprite());
    }
    if (toolbox.AStarButton->getSprite()) {
        toolbox.window.draw(*toolbox.AStarButton->getSprite());
    }
    if (toolbox.BFSButton->getSprite()) {
        toolbox.window.draw(*toolbox.BFSButton->getSprite());
    }
    if (toolbox.ConfirmButton->getSprite()) {
        toolbox.window.draw(*toolbox.ConfirmButton->getSprite());
    }
    //For maze rendering
    /*
     for (vector i : MazeThing){ MazeThing maybe be vector(vector(sf::sprite))
        for (sf::Sprite k : i){}
     }
     */
    int x = 0;
    int y = 0; // 29 is limit for 32 bit by 32 bit tiles
    int tilesize = 32;
    for (auto& rows : toolbox.mazeTiles) {
        for (auto& sprites : rows) {
            if (toolbox.MazeSize > 29 && toolbox.MazeSize <= 59) {
                tilesize = 16;
                if (sprites.getTexture() != toolbox.MazeTileSprite16.getTexture()) { //Change this later to checking size or something
                    toolbox.setMazeSprites(toolbox.MazeTileSprite16);
                }
            }
            else if (toolbox.MazeSize > 59 && toolbox.MazeSize <= 118) {
                tilesize = 8;
                if (sprites.getTexture() != toolbox.MazeTileSprite8.getTexture()) {
                    toolbox.setMazeSprites(toolbox.MazeTileSprite8);
                }
            }
            else if (toolbox.MazeSize > 118 && toolbox.MazeSize <= 317) {
                tilesize = 3;
                if (sprites.getTexture() != toolbox.MiniMazeTileSprite.getTexture()) {
                    toolbox.setMazeSprites(toolbox.MiniMazeTileSprite);
                }
            }
            sprites.setPosition(x, y);
            toolbox.window.draw(sprites);
            x += tilesize;
        }
        y += tilesize;
        x = 0;
    }

    sf::Font font;
    if (!font.loadFromFile("Fonts/arial.ttf")) {
        cerr <<"Error loading font";
        toolbox.window.close();
    }
    sf::Text Question("Enter dimension of square maze: ", font, 20);
    Question.setPosition(1130, 100);
    toolbox.window.draw(Question);

    toolbox.window.display();
}

void gameLoop(){
    Toolbox& toolbox = Toolbox::getInstance();

    string answer = "";
    bool isTyping = true; //Just do buttons instead
    sf::Event event;
    while (toolbox.window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            toolbox.window.close();
            cout << "closing";
        }
        if (event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mouseSpot = sf::Mouse::getPosition(toolbox.window);
            if (toolbox.OneUpButton->getSprite() && toolbox.OneUpButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.OneUpButton->onClick();
            }
            if (toolbox.FiveUpButton->getSprite() && toolbox.FiveUpButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.FiveUpButton->onClick();
            }
            if (toolbox.TenUpButton->getSprite() && toolbox.TenUpButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.TenUpButton->onClick();
            }
            if (toolbox.HundredUpButton->getSprite() && toolbox.HundredUpButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.HundredUpButton->onClick();
            }

            if (toolbox.OneDownButton->getSprite() && toolbox.OneDownButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.OneDownButton->onClick();
            }
            if (toolbox.FiveDownButton->getSprite() && toolbox.FiveDownButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.FiveDownButton->onClick();
            }
            if (toolbox.TenDownButton->getSprite() && toolbox.TenDownButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.TenDownButton->onClick();
            }
            if (toolbox.HundredDownButton->getSprite() && toolbox.HundredDownButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.HundredDownButton->onClick();
            }

            if (toolbox.DijkstraButton->getSprite() && toolbox.DijkstraButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.DijkstraButton->onClick();
            }
            if (toolbox.AStarButton->getSprite() && toolbox.AStarButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.AStarButton->onClick();
            }
            if (toolbox.BFSButton->getSprite() && toolbox.BFSButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.BFSButton->onClick();
            }
            if (toolbox.ConfirmButton->getSprite() && toolbox.ConfirmButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.ConfirmButton->onClick();
            }

        }
    }

    render();

    sf::sleep(sf::milliseconds(10));
}

void confirmation() {
    Toolbox& toolbox = Toolbox::getInstance();
    cout << toolbox.temp << " :before \n";
    toolbox.changeMazeSize(toolbox.MazeSize);
    cout << toolbox.temp << " :after \n";
    toolbox.setMazeSprites(toolbox.MazeTileSprite);
}

void PlaceHolder() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.placeHolder += 1;
    cout << "Button activated";
}

void oneUp() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize + 1 <= 317) {
        toolbox.MazeSize += 1;
    }
    cout << " 1up button works! " << toolbox.MazeSize;
}
void fiveUp() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize + 5 <= 317) {
        toolbox.MazeSize += 5;
    }
    cout << " 5up button works! " << toolbox.MazeSize;
}
void tenUp() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize + 10 <= 317) {
        toolbox.MazeSize += 10;
    }
    cout << " 10up button works! " << toolbox.MazeSize;
}
void hundredUp() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize + 100 <= 317) {
        toolbox.MazeSize += 100;
    }
    cout << " 100up button works! " << toolbox.MazeSize;
}
void oneDown() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize - 1 >= 1) {
        toolbox.MazeSize -= 1;
    }
    cout << " 1down button works! " << toolbox.MazeSize;
}
void fiveDown() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize - 5 >= 1) {
        toolbox.MazeSize -= 5;
    }
    cout << " 5down button works! " << toolbox.MazeSize;
}
void tenDown() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize - 10 >= 1) {
        toolbox.MazeSize -= 10;
    }
    cout << " 10down button works! " << toolbox.MazeSize;
}
void hundredDown() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (toolbox.MazeSize - 100 >= 1) {
        toolbox.MazeSize -= 100;
    }
    cout << " 100down button works! " << toolbox.MazeSize;
}