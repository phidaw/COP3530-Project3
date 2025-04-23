#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "MazeStuff.h"
#include "Button.h"
#include <string>

class Toolbox {


    Toolbox();
    static Toolbox* instance;
    friend class Button;
    friend class MazeStuff;
    friend void render();
    friend void gameLoop();
    sf::Texture OneUpTexture;
    sf::Sprite OneUpSprite;
    sf::Texture FiveUpTexture;
    sf::Sprite FiveUpSprite;
    sf::Texture TenUpTexture;
    sf::Sprite TenUpSprite;
    sf::Texture HundredUpTexture;
    sf::Sprite HundredUpSprite;
    sf::Texture OneDownTexture;
    sf::Sprite OneDownSprite;
    sf::Texture FiveDownTexture;
    sf::Sprite FiveDownSprite;
    sf::Texture TenDownTexture;
    sf::Sprite TenDownSprite;
    sf::Texture HundredDownTexture;
    sf::Sprite HundredDownSprite;
    sf::Texture mineNumsTexture;
    std::pmr::vector<sf::Sprite> mineNumsSprite;
    sf::Texture DijkstraTexture;
    sf::Sprite DijkstraSprite;
    sf::Texture AStarTexture;
    sf::Sprite AStarSprite;
    sf::Texture BFSTexture;
    sf::Sprite BFSSprite;
    sf::Texture ConfirmTexture;
    sf::Sprite ConfirmSprite;
    sf::Texture MazeTileTexture;
    sf::Texture MazeTileTexture16;
    sf::Texture MazeTileTexture8;
    sf::Texture MiniMazeTileTexture;
    sf::Texture MazePathTexture;
    sf::Texture MazePathTexture16;
    sf::Texture MazePathTexture8;
    sf::Texture MiniMazePathTexture;
    sf::Texture MazeSnakeBodyTexture;
    sf::Texture MazeSnakeBodyTexture16;
    sf::Texture MazeSnakeBodyTexture8;
    sf::Texture MiniMazeSnakeTexture;
    sf::Texture MazeSnakeHeadTexture;
    sf::Texture MazeSnakeHeadTexture16;




public:
    sf::RenderWindow window;
    Button* OneUpButton;
    Button* FiveUpButton;
    Button* TenUpButton;
    Button* HundredUpButton;
    Button* OneDownButton;
    Button* FiveDownButton;
    Button* TenDownButton;
    Button* HundredDownButton;
    Button* DijkstraButton;
    Button* AStarButton;
    Button* BFSButton;
    Button* ConfirmButton;
    /*Tiles* MazeTile; //32, 16, 8, 3 bits for sizes? all done!
    Tiles* MazePath;
    Tiles* MazeSnakeBody;
    Tiles* MazeSnakeHead;*/
    int temp;
    static Toolbox &getInstance();
    void changeMazeSize(int newSize);
    void setMazeSprites(sf::Sprite newSprite);
    int MazeSize;
    int placeHolder;
    std::vector<std::vector<sf::Sprite>> mazeTiles;
    std::vector<std::vector<std::string>> mazeTilesTypes;
    sf::Sprite MazeTileSprite;
    sf::Sprite MazeTileSprite16;
    sf::Sprite MazeTileSprite8;
    sf::Sprite MiniMazeTileSprite;
    sf::Sprite MazePathSprite;
    sf::Sprite MazePathSprite16;
    sf::Sprite MazePathSprite8;
    sf::Sprite MiniMazePathSprite;
    sf::Sprite MazeSnakeBodySprite;
    sf::Sprite MazeSnakeBodySprite16;
    sf::Sprite MazeSnakeBodySprite8;
    sf::Sprite MiniMazeSnakeSprite;
    sf::Sprite MazeSnakeHeadSprite;
    sf::Sprite MazeSnakeHeadSprite16;


};



#endif //TOOLBOX_H