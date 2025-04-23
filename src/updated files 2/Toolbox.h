#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "Button.h"
#include "MazeStuff.h"
#include "../../Maze/Maze.h"

class AgentManager; // Forward declaration for AgentManager

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
    int temp;
    static Toolbox &getInstance();
    void changeMazeSize(int newSize);
    void setMazeSprites(sf::Sprite newSprite);
    void addDijkstraAgent();
    void addAStarAgent();
    void addBFSAgent();
    void oneUp();
    void fiveUp();
    void tenUp();
    void hundredUp();
    void oneDown();
    void fiveDown();
    void tenDown();
    void hundredDown();
    void confirmation();
    int MazeSize;
    int placeHolder;
    std::vector<std::vector<sf::Sprite>> mazeTiles;
    std::vector<std::vector<std::string>> mazeTilesTypes;
    std::map<std::string, std::vector<Cell*>> totalAgentPaths;
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
    std::string getMazeTilesTypesString() const;
    void appendAgentPath(const std::string& agentName, const std::vector<Cell*>& path);
    const std::vector<Cell*>& getAgentPath(const std::string& agentName) const;
    void clearAgentPaths();

private:
    AgentManager& agentManager; // Reference to AgentManager
};

#endif //TOOLBOX_H