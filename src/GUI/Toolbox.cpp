#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Button.h"
#include "MazeStuff.h"
#include "../../Maze/Maze.h"
#include "../../Traversal/Agents/AStarAgent.h"
#include "../../Traversal/Agents/BFSAgent.h"
#include "../../Traversal/Agents/DijkstraAgent.h"

Toolbox* Toolbox::instance = nullptr;

Toolbox::Toolbox(AgentManager& manager) : agentManager(manager) {
    window.create(sf::VideoMode(1520, 951), "Maze Maestro");
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
    DijkstraButton = new Button(sf::Vector2f(1200, 300), [this]{addDijkstraAgent();});
    AStarButton = new Button(sf::Vector2f(1200, 450), [this]{addAStarAgent();});
    BFSButton = new Button(sf::Vector2f(1200, 600), [this]{addBFSAgent();});
    ConfirmButton = new Button(sf::Vector2f(1260, 180), [this]{confirmation();});
    ComplicatedConfirmButton = new Button(sf::Vector2f(1240, 800), [this]{PlaceHolder();});
    ComplicateCancelButton = new Button(sf::Vector2f(1280, 800), [this]{PlaceHolder();});
    mazeTiles = std::vector(MazeSize, std::vector<sf::Sprite>(MazeSize, sf::Sprite{}));
    mazeTilesTypes.resize(MazeSize, std::vector<std::string>(MazeSize, std::string()));
    totalAgentPaths = std::map<std::string, std::vector<Cell*>>();
    if (!OneUpTexture.loadFromFile("resources/images/1Up.png")) {
        std::cerr << "Failed to load 1Up texture";
    } else {
        OneUpSprite.setTexture(OneUpTexture);
        OneUpSprite.setPosition(OneUpButton->getPosition());
        OneUpButton->setSprite(&OneUpSprite);
    }
    if (!FiveUpTexture.loadFromFile("resources/images/5Up.png")) {
        std::cerr << "Failed to load 5Up texture";
    } else {
        FiveUpSprite.setTexture(FiveUpTexture);
        FiveUpSprite.setPosition(FiveUpButton->getPosition());
        FiveUpButton->setSprite(&FiveUpSprite);
    }
    if (!TenUpTexture.loadFromFile("resources/images/10Up.png")) {
        std::cerr << "Failed to load 10Up texture";
    } else {
        TenUpSprite.setTexture(TenUpTexture);
        TenUpSprite.setPosition(TenUpButton->getPosition());
        TenUpButton->setSprite(&TenUpSprite);
    }
    if (!HundredUpTexture.loadFromFile("resources/images/100Up.png")) {
        std::cerr << "Failed to load 100Up texture";
    } else {
        HundredUpSprite.setTexture(HundredUpTexture);
        HundredUpSprite.setPosition(HundredUpButton->getPosition());
        HundredUpButton->setSprite(&HundredUpSprite);
    }
    if (!OneDownTexture.loadFromFile("resources/images/1Down.png")) {
        std::cerr << "Failed to load 1Down texture";
    } else {
        OneDownSprite.setTexture(OneDownTexture);
        OneDownSprite.setPosition(OneDownButton->getPosition());
        OneDownButton->setSprite(&OneDownSprite);
    }
    if (!FiveDownTexture.loadFromFile("resources/images/5Down.png")) {
        std::cerr << "Failed to load 5Down texture";
    } else {
        FiveDownSprite.setTexture(FiveDownTexture);
        FiveDownSprite.setPosition(FiveDownButton->getPosition());
        FiveDownButton->setSprite(&FiveDownSprite);
    }
    if (!TenDownTexture.loadFromFile("resources/images/10Down.png")) {
        std::cerr << "Failed to load 10Down texture";
    } else {
        TenDownSprite.setTexture(TenDownTexture);
        TenDownSprite.setPosition(TenDownButton->getPosition());
        TenDownButton->setSprite(&TenDownSprite);
    }
    if (!HundredDownTexture.loadFromFile("resources/images/100Down.png")) {
        std::cerr << "Failed to load 100Down texture";
    } else {
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
    } else {
        DijkstraSprite.setTexture(DijkstraTexture);
        DijkstraSprite.setPosition(DijkstraButton->getPosition());
        DijkstraButton->setSprite(&DijkstraSprite);
    }
    if (!AStarTexture.loadFromFile("resources/images/AStarButton.png")) {
        std::cerr << "Failed to load AStar texture";
    } else {
        AStarSprite.setTexture(AStarTexture);
        AStarSprite.setPosition(AStarButton->getPosition());
        AStarButton->setSprite(&AStarSprite);
    }
    if (!BFSTexture.loadFromFile("resources/images/BFSButton.png")) {
        std::cerr << "Failed to load BFS texture";
    } else {
        BFSSprite.setTexture(BFSTexture);
        BFSSprite.setPosition(BFSButton->getPosition());
        BFSButton->setSprite(&BFSSprite);
    }
    if (!ConfirmTexture.loadFromFile("resources/images/ConfirmButton.png")) {
        std::cerr << "Failed to load Confirm texture";
    } else {
        ConfirmSprite.setTexture(ConfirmTexture);
        ComplicatedConfirmSprite.setTexture(ConfirmTexture);
        ConfirmSprite.setPosition(ConfirmButton->getPosition());
        ComplicatedConfirmSprite.setPosition(ComplicatedConfirmButton->getPosition());
        ConfirmButton->setSprite(&ConfirmSprite);
        ComplicatedConfirmButton->setSprite(&ComplicatedConfirmSprite);
    }
    if (!MazeTileTexture.loadFromFile("resources/images/MazeTile.png")) {
        std::cerr << "Failed to load Maze Tile texture";
    } else {
        MazeTileSprite.setTexture(MazeTileTexture);
    }
    if (!MazePathTexture.loadFromFile("resources/images/MazeTilePath.png")) {
        std::cerr << "Failed to load Maze Path texture";
    } else {
        MazePathSprite.setTexture(MazePathTexture);
    }
    if (!MazeSnakeBodyTexture.loadFromFile("resources/images/MazeTileSnakeBody.png")) {
        std::cerr << "Failed to load Maze Snake Body texture";
    } else {
        MazeSnakeBodySprite.setTexture(MazeSnakeBodyTexture);
    }
    if (!MazeSnakeHeadTexture.loadFromFile("resources/images/MazeTileSnakeHead.png")) {
        std::cerr << "Failed to load Maze Snake Head texture";
    } else {
        MazeSnakeHeadSprite.setTexture(MazeSnakeHeadTexture);
    }
    if (!MazeTileTexture16.loadFromFile("resources/images/MazeTile16.png")) {
        std::cerr << "Failed to load Maze Tile 16 bit texture";
    } else {
        MazeTileSprite16.setTexture(MazeTileTexture16);
    }
    if (!MazeTileTexture8.loadFromFile("resources/images/MazeTile8.png")) {
        std::cerr << "Failed to load Maze Tile 8 bit texture";
    } else {
        MazeTileSprite8.setTexture(MazeTileTexture8);
    }
    if (!MiniMazeTileTexture.loadFromFile("resources/images/MiniMazeTile.png")) {
        std::cerr << "Failed to load Mini Maze Tile texture";
    } else {
        MiniMazeTileSprite.setTexture(MiniMazeTileTexture);
    }
    if (!MiniMazePathTexture.loadFromFile("resources/images/MiniMazeTilePath.png")) {
        std::cerr << "Failed to load Mini Maze Path texture";
    } else {
        MiniMazePathSprite.setTexture(MiniMazePathTexture);
    }
    if (!MazePathTexture16.loadFromFile("resources/images/MazeTilePath16.png")) {
        std::cerr << "Failed to load Maze Path 16 bit texture";
    } else {
        MazePathSprite16.setTexture(MazePathTexture16);
    }
    if (!MazePathTexture8.loadFromFile("resources/images/MazeTilePath8.png")) {
        std::cerr << "Failed to load Maze Path 8 bit texture";
    } else {
        MazePathSprite8.setTexture(MazePathTexture8);
    }
    if (!MazeSnakeBodyTexture16.loadFromFile("resources/images/MazeTileSnakeBody16.png")) {
        std::cerr << "Failed to load Maze Snake Body 16 bit texture";
    } else {
        MazeSnakeBodySprite16.setTexture(MazeSnakeBodyTexture16);
    }
    if (!MazeSnakeBodyTexture8.loadFromFile("resources/images/MazeTileSnakeBody8.png")) {
        std::cerr << "Failed to load Maze Snake Body 8 bit texture";
    } else {
        MazeSnakeBodySprite8.setTexture(MazeSnakeBodyTexture8);
    }
    if (!MiniMazeSnakeTexture.loadFromFile("resources/images/MiniMazeTileSnake.png")) {
        std::cerr << "Failed to load Mini Maze Snake texture";
    } else {
        MiniMazeSnakeSprite.setTexture(MiniMazeSnakeTexture);
    }
    if (!MazeSnakeHeadTexture16.loadFromFile("resources/images/MazeTileSnakeHead16.png")) {
        std::cerr << "Failed to load Maze Snake Head 16 bit texture";
    } else {
        MazeSnakeHeadSprite16.setTexture(MazeSnakeHeadTexture16);
    }
    if (!CancelTexture.loadFromFile("resources/images/CancelButton.png")) {
        std::cerr << "Failed to load Cancel texture";
    }
    else {
        CancelSprite.setTexture(CancelTexture);
        CancelSprite.setPosition(ComplicateCancelButton->getPosition());
        ComplicateCancelButton->setSprite(&CancelSprite);
    }
}

void Toolbox::addDijkstraAgent() {
    static int dijkstraCount = 0;
    auto agent = std::make_unique<DijkstraAgent>("Dijkstra" + std::to_string(++dijkstraCount));
    agentManager.AddAgent(std::move(agent));
}

void Toolbox::addAStarAgent() {
    static int aStarCount = 0;
    auto agent = std::make_unique<AStarAgent>("AStar" + std::to_string(++aStarCount));
    agentManager.AddAgent(std::move(agent));
}

void Toolbox::addBFSAgent() {
    static int bfsCount = 0;
    auto agent = std::make_unique<BFSAgent>("BFS" + std::to_string(++bfsCount));
    agentManager.AddAgent(std::move(agent));
}

void Toolbox::oneUp() { temp += 1; }
void Toolbox::fiveUp() { temp += 5; }
void Toolbox::tenUp() { temp += 10; }
void Toolbox::hundredUp() { temp += 100; }
void Toolbox::oneDown() { temp -= 1; }
void Toolbox::fiveDown() { temp -= 5; }
void Toolbox::tenDown() { temp -= 10; }
void Toolbox::hundredDown() { temp -= 100; }
void Toolbox::confirmation() { MazeSize = temp; changeMazeSize(MazeSize); }

Toolbox &Toolbox::getInstance(AgentManager& manager) {
    if (instance == nullptr) {
        instance = new Toolbox(manager);
    }
    return *instance;
}

void Toolbox::changeMazeSize(int newSize) {
    temp = newSize;
    mazeTiles.resize(newSize);
    for (auto& row : mazeTiles) {
        row.resize(newSize, sf::Sprite{});
    }
    mazeTilesTypes.resize(newSize);
}

void Toolbox::setMazeSprites(sf::Sprite newSprite) {
    for (auto& row : mazeTiles) {
        for (auto& sprites : row) {
            sprites = newSprite;
        }
    }
}

std::string Toolbox::getMazeTilesTypesString() const {
    std::string result;
    for (const auto& row : mazeTilesTypes) {
        for (const auto& tileType : row) {
            result += tileType.empty() ? "empty" : tileType;
            result += " ";
        }
        result += "\n";
    }
    return result;
}

void Toolbox::appendAgentPath(const std::string& agentName, const std::vector<Cell*>& path) {
    auto& totalPath = totalAgentPaths[agentName];
    if (!path.empty()) {
        size_t startIndex = (totalPath.empty() || path[0] != totalPath.back()) ? 0 : 1;
        totalPath.insert(totalPath.end(), path.begin() + startIndex, path.end());
    }
}

const std::vector<Cell*>& Toolbox::getAgentPath(const std::string& agentName) const {
    static const std::vector<Cell*> emptyPath;
    auto it = totalAgentPaths.find(agentName);
    return it != totalAgentPaths.end() ? it->second : emptyPath;
}

void Toolbox::clearAgentPaths() {
    totalAgentPaths.clear();
}
