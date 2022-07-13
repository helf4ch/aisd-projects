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
#include "hitBox.h"
#include "level.h"

namespace Arcanoid {
    class Game {
        private:
            bool running = false;

            bool endGame;

            bool loseCondition;
            bool winCondition;

            bool showTop;

            bool loadingLevel;
            int loadingTimer;

            int score;

            sf::RenderWindow window{{ WINDOW_WIDTH, WINDOW_HEIGHT }, "ARCANOID"};
            sf::RectangleShape frame;
            sf::Font font;
            sf::Clock clock;

            std::vector<GameEvent> gameEvents;

            std::vector<int> leaderBoard;

            std::vector<Level> levels;
            int levelIndex;

            std::vector<Brick> bricks;
            std::vector<Ball> balls;
            std::vector<Paddle> paddles;
            std::vector<HitBox> deathBoxes;

            void nextLevel() {
                if (levels.size() == levelIndex + 1) {
                    GameEvent event;
                    event.type = GameEvent::Win;
                    gameEvents.push_back(event);
                } else {
                    ++levelIndex;
                    loadLevel();
                }
            }

            void loadLevel() {
                bricks = levels[levelIndex].getBricks();
                balls = levels[levelIndex].getBalls();
                paddles = levels[levelIndex].getPaddles();
                deathBoxes = levels[levelIndex].getDeathBoxes();

                loadingLevel = true;
                loadingTimer = 3;
            }

            void newGame() {
                levelIndex = 0;

                endGame = false;

                loseCondition = false;
                winCondition = false;

                showTop = false;

                loadingLevel = false;
                loadingTimer = 0;

                score = 0;

                gameEvents.clear();

                loadLevel();
            }

            void addToLeaderBoard(const int score) {
                leaderBoard.push_back(score);
                std::sort(leaderBoard.begin(), leaderBoard.end(), std::greater<int>());
                if (leaderBoard.size() > 10) {
                    leaderBoard.erase(leaderBoard.begin() + 10, leaderBoard.end());
                }
            }

            void handleGameEvents() {
                for (int i = 0; i < gameEvents.size(); ++i) {
                    switch (gameEvents[i].type) {
                        case GameEvent::ChangeScore:
                            score += gameEvents[i].score.difference;
                            break;
                        
                        case GameEvent::Win:
                            endGame = true;
                            winCondition = true;
                            addToLeaderBoard(score);
                            break;
                        
                        case GameEvent::Lose:
                            endGame = true;
                            loseCondition = true;
                            addToLeaderBoard(score);
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace) && endGame && showTop) 
                    showTop = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && endGame) showTop = true;
            }

            void updatePhase() {
                for (auto &ball : balls) {
                    ball.update();
                    for (auto &deathBox : deathBoxes) {
                        ball.testCollision(gameEvents, deathBox);
                    }
                    for (auto &paddle : paddles) {
                        paddle.update();
                        ball.testCollision(gameEvents, paddle);
                    }
                    for (auto &brick : bricks) {
                        ball.testCollision(gameEvents, brick);
                    }
                }

                bricks.erase(remove_if(begin(bricks), end(bricks),
                            [](const Brick& brick) {
                                    return brick.isDestroyed();
                                }),
                            end(bricks));
                
                if (bricks.size() == 0) {
                    nextLevel();
                }
            }

            void drawPhase() {
                showText("SCORE " + std::to_string(score), WINDOW_WIDTH / 2.f, FIELD_OFFSET_Y / 2.f - 3, 60);
                showText("PRESS ENTER TO RESTART THE GAME", WINDOW_WIDTH / 2.f, 
                         FIELD_OFFSET_Y / 2.f + 101 + FIELD_HEIGHT + FIELD_OFFSET_Y, 16);

                window.draw(frame);

                for (auto &ball : balls) {
                    window.draw(ball.getShape());
                }

                for (auto &deathBox : deathBoxes) {
                    window.draw(deathBox.getShape());
                }

                for (auto &paddle : paddles) {
                    window.draw(paddle.getShape());
                }

                for (auto &brick : bricks) {
                    window.draw(brick.getShape());
                }
            }

            void showText(const std::string &string, const float x, const float y, const int size) {
                sf::Text text;

                text.setFont(font);
                text.setPosition(x, y);
                text.setCharacterSize(size);

                text.setString(string);
                std::string textString = text.getString();
                text.setOrigin(((text.getCharacterSize() / 1.3f) * textString.size()) / 2.f,
                                text.getCharacterSize() / 1.5f);

                window.draw(text);
            }

            void showLeaderBoard() {
                showText("SCORE " + std::to_string(score), WINDOW_WIDTH / 2.f, FIELD_OFFSET_Y / 2.f - 3, 60);
                showText("PRESS BACKSPACE TO EXIT THIS SCREEN", WINDOW_WIDTH / 2.f, 
                         FIELD_OFFSET_Y / 2.f + 57 + FIELD_HEIGHT + FIELD_OFFSET_Y, 26);
                showText("PRESS ENTER TO RESTART THE GAME", WINDOW_WIDTH / 2.f, 
                         FIELD_OFFSET_Y / 2.f + 101 + FIELD_HEIGHT + FIELD_OFFSET_Y, 16);

                window.draw(frame);

                for (int i = 0; i < 10; ++i) {
                    if (i >= leaderBoard.size()) {
                        continue;
                    } else {
                        showText(std::to_string(i + 1) + ". " + std::to_string(leaderBoard[i]), 
                                 WINDOW_WIDTH / 2.f, 52 * (i + 1) + 12 + FIELD_OFFSET_Y, 30);
                    }
                }
            }

        public:
            explicit Game(std::vector<Level> new_levels) {
                if (!new_levels.size()) {
                    throw "Error: no levels";
                }

                window.setFramerateLimit(60);

                frame.setPosition(FIELD_OFFSET_X, FIELD_OFFSET_Y);
                frame.setSize({FIELD_WIDTH, FIELD_HEIGHT});
                frame.setOutlineThickness(2.f);
                frame.setOutlineColor(sf::Color::White);
                frame.setFillColor(sf::Color::Transparent);

                if (!font.loadFromFile("ka1.ttf")) {
                    std::cout << "Error loading font\n";
                    system("pause");
                }

                levels = new_levels;

                newGame();
            }

            void run() {
                running = true;

                while (running) {
                    window.clear();

                    if (loadingLevel) {
                        drawPhase();
                        showText(std::to_string(loadingTimer), WINDOW_WIDTH / 2.f, 
                                 FIELD_OFFSET_Y / 2.f - 3 + FIELD_HEIGHT + FIELD_OFFSET_Y, 46);
                        if (clock.getElapsedTime().asSeconds() > 1.f) {
                            --loadingTimer;
                            clock.restart();
                        }
                        if (!loadingTimer) {
                            loadingLevel = false;
                        }
                        inputPhase();
                    } else if (endGame) {
                        if (winCondition) showText("YOU WIN!", WINDOW_WIDTH / 2.f, 
                                                   FIELD_OFFSET_Y / 2.f - 3 + FIELD_HEIGHT + 
                                                   FIELD_OFFSET_Y / 2.f, 38);
                        else if (loseCondition) showText("YOU LOSE!", WINDOW_WIDTH / 2.f, 
                                                         FIELD_OFFSET_Y / 2.f - 3 + FIELD_HEIGHT + 
                                                         FIELD_OFFSET_Y, 46);
                        if (showTop) {
                            showLeaderBoard();
                        } else {
                            showText("PRESS SPACE TO LOOK AT THE LEADER BOARD", WINDOW_WIDTH / 2.f, 
                                    FIELD_OFFSET_Y / 2.f + 57 + FIELD_HEIGHT + FIELD_OFFSET_Y, 26);
                            drawPhase();
                        }
                        inputPhase();
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
