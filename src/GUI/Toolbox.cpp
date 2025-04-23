#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "MazeStuff.h"
#include "Button.h"
#include <string>
#include "../../Traversal/Agents/AStarAgent.h"
#include "../../Traversal/BFSAgent.h"
#include "../../Traversal/DijkstraAgent.h"

Toolbox* Toolbox::instance = nullptr;

Toolbox::Toolbox() {
    window.create(sf::VideoMode(1520, 951), "Maze Maestro"); //Biggest size that looks ok is 1500 * 900
    MazeSize = 1;
    placeHolder = -1;
    temp = 0;
    OneUpButton = new Button(sf::Vector2f(1325, 140), [this]{oneUp();});
    FiveUpButton = new Button(sf::Vector2f(1365, 140), [this]{fiveUp();});
    TenUpButton = new Button(sf::Vector2f(1405, 140), [this]{tenUp();});
    HundredUpButton = new Button(sf::Vector2f(1445, 140), [this]{hundredUp();});
    OneDownButton = new Button(sf::Vector2f(1200, 140), [this]{oneDown();});
    FiveDownButton = new Button(sf::Vector2f(1160, 140), [this]{fiveDown();});
    TenDownButton = new Button(sf::Vector2f(1120, 140), [this]{tenDown();});
    HundredDownButton = new Button(sf::Vector2f(1080, 140), [this]{hundredDown();});
    DijkstraButton = new Button(sf::Vector2f(1200, 300), [this]{PlaceHolder();});
    AStarButton = new Button(sf::Vector2f(1200, 450), [this]{PlaceHolder();});
    BFSButton = new Button(sf::Vector2f(1200, 600), [this]{PlaceHolder();});
    ConfirmButton = new Button(sf::Vector2f(1260, 180), [this]{confirmation();});
    mazeTiles = std::vector(MazeSize, std::vector<sf::Sprite>(MazeSize, sf::Sprite{}));
    mazeTilesTypes.resize(MazeSize, std::vector<std::string>(MazeSize, std::string()));



    if (!OneUpTexture.loadFromFile("resources/images/1Up.png")) {
        std::cerr << "Failed to load 1Up texture";
    }
    else { //This creates the sprite of the button, and places it in pos^, and assigns the sprite to the appropriate button
        OneUpSprite.setTexture(OneUpTexture);
        OneUpSprite.setPosition(OneUpButton->getPosition());
        OneUpButton->setSprite(&OneUpSprite);
    }
    if (!FiveUpTexture.loadFromFile("resources/images/5Up.png")) {
        std::cerr << "Failed to load 5Up texture";
    }
    else {
        FiveUpSprite.setTexture(FiveUpTexture);
        FiveUpSprite.setPosition(FiveUpButton->getPosition());
        FiveUpButton->setSprite(&FiveUpSprite);
    }
    if (!TenUpTexture.loadFromFile("resources/images/10Up.png")) {
        std::cerr << "Failed to load 10Up texture";
    }
    else {
        TenUpSprite.setTexture(TenUpTexture);
        TenUpSprite.setPosition(TenUpButton->getPosition());
        TenUpButton->setSprite(&TenUpSprite);
    }
    if (!HundredUpTexture.loadFromFile("resources/images/100Up.png")) {
        std::cerr << "Failed to load 100Up texture";
    }
    else {
        HundredUpSprite.setTexture(HundredUpTexture);
        HundredUpSprite.setPosition(HundredUpButton->getPosition());
        HundredUpButton->setSprite(&HundredUpSprite);
    }

    if (!OneDownTexture.loadFromFile("resources/images/1Down.png")) {
        std::cerr << "Failed to load 1Down texture";
    }
    else {
        OneDownSprite.setTexture(OneDownTexture);
        OneDownSprite.setPosition(OneDownButton->getPosition());
        OneDownButton->setSprite(&OneDownSprite);
    }
    if (!FiveDownTexture.loadFromFile("resources/images/5Down.png")) {
        std::cerr << "Failed to load 5Down texture";
    }
    else {
        FiveDownSprite.setTexture(FiveDownTexture);
        FiveDownSprite.setPosition(FiveDownButton->getPosition());
        FiveDownButton->setSprite(&FiveDownSprite);
    }
    if (!TenDownTexture.loadFromFile("resources/images/10Down.png")) {
        std::cerr << "Failed to load 10Down texture";
    }
    else {
        TenDownSprite.setTexture(TenDownTexture);
        TenDownSprite.setPosition(TenDownButton->getPosition());
        TenDownButton->setSprite(&TenDownSprite);
    }
    if (!HundredDownTexture.loadFromFile("resources/images/100Down.png")) {
        std::cerr << "Failed to load 100Down texture";
    }
    else {
        HundredDownSprite.setTexture(HundredDownTexture);
        HundredDownSprite.setPosition(HundredDownButton->getPosition());
        HundredDownButton->setSprite(&HundredDownSprite);
    }
    if(!mineNumsTexture.loadFromFile("resources/images/digits.png")) {
        std::cerr << "Failed to load mineNums texture";
    }
    int digitW = 21;
    int digitH = 32;
    for (int i = 0; i < 11; ++i) {
        sf::IntRect digitRect(i * digitW, 0, digitW, digitH);
        sf::Sprite tempSprite(mineNumsTexture, digitRect);
        mineNumsSprite.push_back(tempSprite);
    }

    if (!DijkstraTexture.loadFromFile("resources/images/DijkstraButton.png")) {
        std::cerr << "Failed to load Dijkstra texture";
    }
    else {
        DijkstraSprite.setTexture(DijkstraTexture);
        DijkstraSprite.setPosition(DijkstraButton->getPosition());
        DijkstraButton->setSprite(&DijkstraSprite);
    }
    if (!AStarTexture.loadFromFile("resources/images/AStarButton.png")) {
        std::cerr << "Failed to load AStar texture";
    }
    else {
        AStarSprite.setTexture(AStarTexture);
        AStarSprite.setPosition(AStarButton->getPosition());
        AStarButton->setSprite(&AStarSprite);
    }
    if (!BFSTexture.loadFromFile("resources/images/BFSButton.png")) {
        std::cerr << "Failed to load BFS texture";
    }
    else {
        BFSSprite.setTexture(BFSTexture);
        BFSSprite.setPosition(BFSButton->getPosition());
        BFSButton->setSprite(&BFSSprite);
    }
    if (!ConfirmTexture.loadFromFile("resources/images/ConfirmButton.png")) {
        std::cerr << "Failed to load Confirm texture";
    }
    else {
        ConfirmSprite.setTexture(ConfirmTexture);
        ConfirmSprite.setPosition(ConfirmButton->getPosition());
        ConfirmButton->setSprite(&ConfirmSprite);
    }
    if (!MazeTileTexture.loadFromFile("resources/images/MazeTile.png")) {
        std::cerr << "Failed to load Maze Tile texture";
    }
    else {
        MazeTileSprite.setTexture(MazeTileTexture);
    }
    if (!MazePathTexture.loadFromFile("resources/images/MazeTilePath.png")) {
        std::cerr << "Failed to load Maze Path texture";
    }
    else {
        MazePathSprite.setTexture(MazePathTexture);
    }
    if (!MazeSnakeBodyTexture.loadFromFile("resources/images/MazeTileSnakeBody.png")) {
        std::cerr << "Failed to load Maze Snake Body texture";
    }
    else {
        MazeSnakeBodySprite.setTexture(MazeSnakeBodyTexture);
    }
    if (!MazeSnakeHeadTexture.loadFromFile("resources/images/MazeTileSnakeHead.png")) {
        std::cerr << "Failed to load Maze Snake Head texture";
    }
    else {
        MazeSnakeHeadSprite.setTexture(MazeSnakeHeadTexture);
    }
    if (!MazeTileTexture16.loadFromFile("resources/images/MazeTile16.png")) {
        std::cerr << "Failed to load Maze Tile 16 bit texture";
    }
    else {
        MazeTileSprite16.setTexture(MazeTileTexture16);
    }
    if (!MazeTileTexture8.loadFromFile("resources/images/MazeTile8.png")) {
        std::cerr << "Failed to load Maze Tile 8 bit texture";
    }
    else {
        MazeTileSprite8.setTexture(MazeTileTexture8);
    }
    if (!MiniMazeTileTexture.loadFromFile("resources/images/MiniMazeTile.png")) {
        std::cerr << "Failed to load Mini Maze Tile texture";
    }
    else {
        MiniMazeTileSprite.setTexture(MiniMazeTileTexture);
    }
    if (!MiniMazePathTexture.loadFromFile("resources/images/MiniMazeTilePath.png")) {
        std::cerr << "Failed to load Mini Maze Path texture";
    }
    else {
        MiniMazePathSprite.setTexture(MiniMazePathTexture);
    }
    if (!MazePathTexture16.loadFromFile("resources/images/MazeTilePath16.png")) {
        std::cerr << "Failed to load Maze Path 16 bit texture";
    }
    else {
        MazePathSprite16.setTexture(MazePathTexture16);
    }
    if (!MazePathTexture8.loadFromFile("resources/images/MazeTilePath8.png")) {
        std::cerr << "Failed to load Maze Path 8 bit texture";
    }
    else {
        MazePathSprite8.setTexture(MazePathTexture8);
    }
    if (!MazeSnakeBodyTexture16.loadFromFile("resources/images/MazeTileSnakeBody16.png")) {
        std::cerr << "Failed to load Maze Snake Body 16 bit texture";
    }
    else {
        MazeSnakeBodySprite16.setTexture(MazeSnakeBodyTexture16);
    }
    if (!MazeSnakeBodyTexture8.loadFromFile("resources/images/MazeTileSnakeBody8.png")) {
        std::cerr << "Failed to load Maze Snake Body 8 bit texture";
    }
    else {
        MazeSnakeBodySprite8.setTexture(MazeSnakeBodyTexture8);
    }
    if (!MiniMazeSnakeTexture.loadFromFile("resources/images/MiniMazeTileSnake.png")) {
        std::cerr << "Failed to load Mini Maze Snake texture";
    }
    else {
        MiniMazeSnakeSprite.setTexture(MiniMazeSnakeTexture);
    }
    if (!MazeSnakeHeadTexture16.loadFromFile("resources/images/MazeTileSnakeHead16.png")) {
        std::cerr << "Failed to load Maze Snake Head 16 bit texture";
    }
    else {
        MazeSnakeHeadSprite16.setTexture(MazeSnakeHeadTexture16);
    }
}
Toolbox &Toolbox::getInstance() {
    if (instance == nullptr) {
        instance = new Toolbox();
    }
    return *instance;
}
void Toolbox::changeMazeSize(int newSize) {
    temp = newSize;
    mazeTiles.resize(newSize);
    for (auto& row : mazeTiles) {
        row.resize(newSize, sf::Sprite{});
    }
}
void Toolbox::setMazeSprites(sf::Sprite newSprite) {
    for (auto& row : mazeTiles) {
        for (auto& sprites : row) {
            sprites = newSprite;
        }
    }
    /*if (MazeSize > 120) {
        mazeTiles[50][100] = MiniMazePathSprite;
        mazeTiles[50][101] = MiniMazePathSprite;
        mazeTiles[50][102] = MiniMazePathSprite;
        mazeTiles[50][103] = MiniMazePathSprite;
        mazeTiles[51][101] = MiniMazePathSprite;
        mazeTiles[52][101] = MiniMazePathSprite;
    }*/
}