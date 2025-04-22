#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include "MazeStuff.h"
#include "Button.h"

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

    if (!OneUpTexture.loadFromFile("images/1Up.png")) {
        std::cerr << "Failed to load 1Up texture";
    }
    else {
        OneUpSprite.setTexture(OneUpTexture);
        OneUpSprite.setPosition(OneUpButton->getPosition());
        OneUpButton->setSprite(&OneUpSprite);
    }
    if (!FiveUpTexture.loadFromFile("images/5Up.png")) {
        std::cerr << "Failed to load 5Up texture";
    }
    else {
        FiveUpSprite.setTexture(FiveUpTexture);
        FiveUpSprite.setPosition(FiveUpButton->getPosition());
        FiveUpButton->setSprite(&FiveUpSprite);
    }
    if (!TenUpTexture.loadFromFile("images/10Up.png")) {
        std::cerr << "Failed to load 10Up texture";
    }
    else {
        TenUpSprite.setTexture(TenUpTexture);
        TenUpSprite.setPosition(TenUpButton->getPosition());
        TenUpButton->setSprite(&TenUpSprite);
    }
    if (!HundredUpTexture.loadFromFile("images/100Up.png")) {
        std::cerr << "Failed to load 100Up texture";
    }
    else {
        HundredUpSprite.setTexture(HundredUpTexture);
        HundredUpSprite.setPosition(HundredUpButton->getPosition());
        HundredUpButton->setSprite(&HundredUpSprite);
    }

    if (!OneDownTexture.loadFromFile("images/1Down.png")) {
        std::cerr << "Failed to load 1Down texture";
    }
    else {
        OneDownSprite.setTexture(OneDownTexture);
        OneDownSprite.setPosition(OneDownButton->getPosition());
        OneDownButton->setSprite(&OneDownSprite);
    }
    if (!FiveDownTexture.loadFromFile("images/5Down.png")) {
        std::cerr << "Failed to load 5Down texture";
    }
    else {
        FiveDownSprite.setTexture(FiveDownTexture);
        FiveDownSprite.setPosition(FiveDownButton->getPosition());
        FiveDownButton->setSprite(&FiveDownSprite);
    }
    if (!TenDownTexture.loadFromFile("images/10Down.png")) {
        std::cerr << "Failed to load 10Down texture";
    }
    else {
        TenDownSprite.setTexture(TenDownTexture);
        TenDownSprite.setPosition(TenDownButton->getPosition());
        TenDownButton->setSprite(&TenDownSprite);
    }
    if (!HundredDownTexture.loadFromFile("images/100Down.png")) {
        std::cerr << "Failed to load 100Down texture";
    }
    else {
        HundredDownSprite.setTexture(HundredDownTexture);
        HundredDownSprite.setPosition(HundredDownButton->getPosition());
        HundredDownButton->setSprite(&HundredDownSprite);
    }
    if(!mineNumsTexture.loadFromFile("images/digits.png")) {
        std::cerr << "Failed to load mineNums texture";
    }
    int digitW = 21;
    int digitH = 32;
    for (int i = 0; i < 11; ++i) {
        sf::IntRect digitRect(i * digitW, 0, digitW, digitH);
        sf::Sprite tempSprite(mineNumsTexture, digitRect);
        mineNumsSprite.push_back(tempSprite);
    }

    if (!DijkstraTexture.loadFromFile("images/DijkstraButton.png")) {
        std::cerr << "Failed to load Dijkstra texture";
    }
    else {
        DijkstraSprite.setTexture(DijkstraTexture);
        DijkstraSprite.setPosition(DijkstraButton->getPosition());
        DijkstraButton->setSprite(&DijkstraSprite);
    }
    if (!AStarTexture.loadFromFile("images/AStarButton.png")) {
        std::cerr << "Failed to load AStar texture";
    }
    else {
        AStarSprite.setTexture(AStarTexture);
        AStarSprite.setPosition(AStarButton->getPosition());
        AStarButton->setSprite(&AStarSprite);
    }
    if (!BFSTexture.loadFromFile("images/BFSButton.png")) {
        std::cerr << "Failed to load BFS texture";
    }
    else {
        BFSSprite.setTexture(BFSTexture);
        BFSSprite.setPosition(BFSButton->getPosition());
        BFSButton->setSprite(&BFSSprite);
    }
    if (!ConfirmTexture.loadFromFile("images/ConfirmButton.png")) {
        std::cerr << "Failed to load Confirm texture";
    }
    else {
        ConfirmSprite.setTexture(ConfirmTexture);
        ConfirmSprite.setPosition(ConfirmButton->getPosition());
        ConfirmButton->setSprite(&ConfirmSprite);
    }
    if (!MazeTileTexture.loadFromFile("images/MazeTile.png")) {
        std::cerr << "Failed to load Maze Tile texture";
    }
    else {
        MazeTileSprite.setTexture(MazeTileTexture);
    }
    if (!MazePathTexture.loadFromFile("images/MazeTilePath.png")) {
        std::cerr << "Failed to load Maze Path texture";
    }
    else {
        MazePathSprite.setTexture(MazePathTexture);
    }
    if (!MazeSnakeBodyTexture.loadFromFile("images/MazeTileSnakeBody.png")) {
        std::cerr << "Failed to load Maze Snake Body texture";
    }
    else {
        MazeSnakeBodySprite.setTexture(MazeSnakeBodyTexture);
    }
    if (!MazeSnakeHeadTexture.loadFromFile("images/MazeTileSnakeHead.png")) {
        std::cerr << "Failed to load Maze Snake Head texture";
    }
    else {
        MazeSnakeHeadSprite.setTexture(MazeSnakeHeadTexture);
    }
    if (!MazeTileTexture16.loadFromFile("images/MazeTile16.png")) {
        std::cerr << "Failed to load Maze Tile 16 bit texture";
    }
    else {
        MazeTileSprite16.setTexture(MazeTileTexture16);
    }
    if (!MazeTileTexture8.loadFromFile("images/MazeTile8.png")) {
        std::cerr << "Failed to load Maze Tile 8 bit texture";
    }
    else {
        MazeTileSprite8.setTexture(MazeTileTexture8);
    }
    if (!MiniMazeTileTexture.loadFromFile("images/MiniMazeTile.png")) {
        std::cerr << "Failed to load Mini Maze Tile texture";
    }
    else {
        MiniMazeTileSprite.setTexture(MiniMazeTileTexture);
    }
    if (!MiniMazePathTexture.loadFromFile("images/MiniMazeTilePath.png")) {
        std::cerr << "Failed to load Mini Maze Path texture";
    }
    else {
        MiniMazePathSprite.setTexture(MiniMazePathTexture);
    }

    // Call InitializeGame to update button handlers
    InitializeGame();
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
}