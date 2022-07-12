#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "constants.h"
#include "gameEvent.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "HitBox.h"

namespace Arcanoid {
    class Game {
        private:
            bool running = false;

            bool loseCondition;
            bool winCondition;

            int score;

            sf::RenderWindow window{{ WINDOW_WIDTH, WINDOW_HEIGHT }, "ARCANOID"};
            sf::RectangleShape frame;
            sf::Font font;
            sf::Text scoreText;

            std::vector<GameEvent> gameEvents;

            std::vector<Brick> bricks;
            Ball ball{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT / 2 + FIELD_OFFSET_Y};
            Paddle paddle{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT + FIELD_OFFSET_Y - 50};
            HitBox bottomDeathBox{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT + FIELD_OFFSET_Y - 25, 
                                    FIELD_WIDTH, 50};

            void newGame() {
                loseCondition = false;
                winCondition = false;

                score = 0;

                ball = Ball{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT / 2 + FIELD_OFFSET_Y};
                paddle = Paddle{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT + FIELD_OFFSET_Y - 50};
                bottomDeathBox = HitBox{FIELD_WIDTH / 2 + FIELD_OFFSET_X, FIELD_HEIGHT + FIELD_OFFSET_Y - 11, 
                                        FIELD_WIDTH, 22};

                bricks.clear();
                for(int iX = 0; iX < COUNT_BRICKS_X; ++iX)
                    for(int iY = 0; iY < COUNT_BRICKS_Y; ++iY)
                        bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 22 + FIELD_OFFSET_X,
                                            (iY + 2) * (BRICK_HEIGHT + 3) + FIELD_OFFSET_Y);
            }

            void handleGameEvents() {
                for (int i = 0; i < gameEvents.size(); ++i) {
                    switch (gameEvents[i].type) {
                        case GameEvent::ChangeScore:
                            score += gameEvents[i].score.difference;
                            break;
                        
                        case GameEvent::Win:
                            winCondition = true;
                            break;
                        
                        case GameEvent::Lose:
                            loseCondition = true;
                            break;

                        default:
                            break;
                    }

                    gameEvents.erase(gameEvents.begin() + i);
                }
            }

            void inputPhase() {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        running = false;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) running = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) newGame();
            }

            void updatePhase() {
                ball.update();
                paddle.update();

                ball.testCollision(gameEvents, bottomDeathBox);
                ball.testCollision(gameEvents, paddle);

                for (auto& brick : bricks) {
                    ball.testCollision(gameEvents, brick);
                }

                bricks.erase(remove_if(begin(bricks), end(bricks),
                                        [](const Brick& brick)
                                        {
                                            return brick.isDestroyed();
                                        }),
                            end(bricks));
                
                if (bricks.size() == 0) {
                    GameEvent event;
                    event.type = GameEvent::Win;
                    gameEvents.push_back(event);
                }
            }

            void drawPhase() {
                scoreText.setString("SCORE " + std::to_string(score));
                std::string scoreString = scoreText.getString();
                scoreText.setOrigin(((scoreText.getCharacterSize() / 2.f) * scoreString.size()) / 2.f,
                                    scoreText.getCharacterSize() / 1.5f);
                
                showSubInfoText("PRESS ENTER TO RESTART THE GAME");

                window.draw(scoreText);
                window.draw(frame);
                window.draw(ball.getShape());
                window.draw(paddle.getShape());
                window.draw(bottomDeathBox.getShape());
                for (auto& brick : bricks) {
                    window.draw(brick.getShape());
                }
            }

            void showInfoText(const std::string &string) {
                sf::Text text;

                text.setFont(font);
                text.setPosition(WINDOW_WIDTH / 2.f, FIELD_OFFSET_Y * 1.3f + 3 + FIELD_HEIGHT);
                text.setCharacterSize(52);

                text.setString(string);
                std::string textString = text.getString();
                text.setOrigin(((text.getCharacterSize() / 2.f) * textString.size()) / 2.f,
                                text.getCharacterSize() / 1.5f);

                window.draw(text);
            }

            void showSubInfoText(const std::string &string) {
                sf::Text text;

                text.setFont(font);
                text.setPosition(WINDOW_WIDTH / 2.f, FIELD_OFFSET_Y * 1.6f + 3 + FIELD_HEIGHT);
                text.setCharacterSize(20);

                text.setString(string);
                std::string textString = text.getString();
                text.setOrigin(((text.getCharacterSize() / 2.f) * textString.size()) / 2.f,
                                text.getCharacterSize() / 1.5f);

                window.draw(text);
            }

            void handleWinCondition() {
                showInfoText("YOU WIN!");

                inputPhase();
                drawPhase();
            }

            void handleLoseCondition() {
                showInfoText("YOU LOSE!");
                
                inputPhase();
                drawPhase();
            }

        public:
            explicit Game() {
                window.setFramerateLimit(60);

                frame.setPosition(FIELD_OFFSET_X, FIELD_OFFSET_Y);
                frame.setSize({FIELD_WIDTH, FIELD_HEIGHT});
                frame.setOutlineThickness(2.f);
                frame.setOutlineColor(sf::Color::White);
                frame.setFillColor(sf::Color::Transparent);

                if (!font.loadFromFile("font.ttf")) {
                    std::cout << "Error loading font\n";
                    system("pause");
                }

                scoreText.setFont(font);
                scoreText.setPosition(WINDOW_WIDTH / 2.f, FIELD_OFFSET_Y / 2.f - 3);
                scoreText.setCharacterSize(52);

                newGame();
            }

            void run() {
                running = true;

                while (running) {
                    window.clear();

                    if (winCondition) {
                        handleWinCondition();
                    } else if (loseCondition) {
                        handleLoseCondition();
                    } else {
                        handleGameEvents();
                        inputPhase();
                        updatePhase();
                        drawPhase();
                    }

                    window.display();
                }
            }
    };
}
