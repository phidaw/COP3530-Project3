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
    while (toolbox.window.isOpen()) {
        gameLoop();
    }
    return 0;
}
void render(sf::Text question, sf::Text Answer, string answerAlt){
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.window.clear();
    if (toolbox.debugButton->getSprite()) {
        toolbox.window.draw(*toolbox.debugButton->getSprite()); //Maybe make it a * in the ()
    }
    toolbox.window.draw(question);
    toolbox.window.draw(Answer);

    toolbox.window.display();
}

void gameLoop(){
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Font font;
    if (!font.loadFromFile("Fonts/arial.ttf")) {
        cerr <<"Error loading font";
        toolbox.window.close();
    }
    sf::Text Question("Enter dimension of square maze: ", font, 30);
    Question.setPosition(200, 100);
    sf::Text Answer("A", font, 30);
    Answer.setPosition(200, 150);
    /*sf::RectangleShape AnswerBorder;
    AnswerBorder.setPosition(Answer.getPosition().x - 5, Answer.getPosition().y - 5);
    AnswerBorder.setSize({Answer.getGlobalBounds().width + 10, Answer.getGlobalBounds().height + 10});
    AnswerBorder.setFillColor(sf::Color::Transparent);
    AnswerBorder.setOutlineColor(sf::Color::White);
    AnswerBorder.setOutlineThickness(10.0f); *///Border does nothing at the moment
    sf::FloatRect textRect = Answer.getGlobalBounds();
    string answer = "";
    bool isTyping = true;
    sf::Event event;
    while (toolbox.window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            toolbox.window.close();
            cout << "closing";
        }
        if (event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mouseSpot = sf::Mouse::getPosition(toolbox.window);
            if (textRect.contains(mouseSpot.x, mouseSpot.y)) {
                isTyping = true;
                //AnswerBorder.setOutlineColor(sf::Color::Blue);
            }
            else {
                isTyping = false;
                //AnswerBorder.setOutlineColor(sf::Color::White);
            }
            if (toolbox.debugButton->getSprite() && toolbox.debugButton->getSprite()->getGlobalBounds().contains(mouseSpot.x, mouseSpot.y)) {
                toolbox.debugButton->onClick();
            }
        }
        if (isTyping) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && answer.size() > 0) {
                    answer.pop_back();
                    Answer.setString(answer);
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    answer += static_cast<char>(event.text.unicode);
                    Answer.setString(answer);
                }
                else if (event.text.unicode == 13 && !answer.empty()) {
                    int dimension = stoi(answer);
                    isTyping = false;
                    //For some reason doesn't parse hitting enter
                }
            }
        }
    }
    toolbox.window.clear();
    if (toolbox.debugButton->getSprite()) {
        toolbox.window.draw(*toolbox.debugButton->getSprite());
    }
    toolbox.window.draw(Question);
    toolbox.window.draw(Answer);

    toolbox.window.display();
    //render(Question, Answer, answer);
    //Typed numbers vanish right after

    sf::sleep(sf::milliseconds(10));
}

void test() {
    cout << "button works!";
}