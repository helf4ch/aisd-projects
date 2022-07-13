#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "constants.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "hitBox.h"

namespace Arcanoid {
    class Level {
        private:
            std::vector<Brick> bricks;
            std::vector<Ball> balls;
            std::vector<Paddle> paddles;
            std::vector<HitBox> deathBoxes;

            void input(std::ifstream &file, std::string &line) {
                if (!std::getline(file, line)) {
                    throw "Input error";
                }
            }

            int getXCords(int relativeX) {
                return (relativeX) * CELL_WIDTH + CELL_OFFSET_X;
            }

            int getYCords(int relativeY) {
                return (relativeY + 1) * CELL_HEIGHT + FIELD_OFFSET_Y;
            }

            void parseDeathBox(const std::string &type) {
                if (type == "bottom") {
                    deathBoxes.emplace_back(getXCords(6), getYCords(25), FIELD_WIDTH, 50);
                } else if (type == "top") {
                    deathBoxes.emplace_back(getXCords(6), getYCords(-1), FIELD_WIDTH, 50);
                } else if (type == "both") {
                    deathBoxes.emplace_back(getXCords(6), getYCords(25), FIELD_WIDTH, 50);
                    deathBoxes.emplace_back(getXCords(6), getYCords(-1), FIELD_WIDTH, 50);
                }
            }

            sf::Color getColor(char color, const sf::Color def) {
                switch (color) {
                case 'w':
                    return sf::Color::White;
                
                case 'r':
                    return sf::Color::Red;
                
                case 'g':
                    return sf::Color::Green;
                
                case 'b':
                    return sf::Color::Blue;
                
                case 'y':
                    return sf::Color::Yellow;
                
                case 'm':
                    return sf::Color::Magenta;

                case 'c':
                    return sf::Color::Cyan;

                default:
                    return def;
                }
            }

            void makeObject(char color, char object, int x, int y) {
                switch (object) {
                    case '*':
                        bricks.emplace_back(getXCords(x), getYCords(y), getColor(color, sf::Color::Yellow));
                        break;
                    
                    case '.':
                        balls.emplace_back(getXCords(x), getYCords(y), getColor(color, sf::Color::Red));
                        break;
                    
                    case '_':
                        paddles.emplace_back(getXCords(x), getYCords(y), getColor(color, sf::Color::Red));
                        break;

                    default:
                        break;
                }
            }

            void readFile(std::ifstream &file) {
                std::string line;
                input(file, line);
                if (line != "Arcanoid") {
                    throw "Level file error: not right type";
                }

                input(file, line);
                std::istringstream parseLine;
                parseLine.str(line);
                std::string dump;
                parseLine >> dump;
                if (dump != "Death") {
                    throw "Level file error: no death parametr";
                }
                parseLine >> dump;
                if (dump != "bottom" && dump != "top" && dump != "both" && dump != "none") {
                    throw "Level file error: invalid death parametr";
                } else {
                    parseDeathBox(dump);
                }

                input(file, line);
                for (int i = 0; i < 23; ++i) {
                    input(file, line);
                    if (line.size() < 35) {
                        throw "Level file error: field is not filled";
                    }
                    int index = 3;
                    while (index < 35) {
                        makeObject(line[index], line[index + 1], index / 3, i + 1);
                        index += 3;
                    }
                }
                input(file, line);
            }
        
        public:
            Level(std::ifstream &file) {
                readFile(file);
            }

            std::vector<Brick> getBricks() const {
                return bricks;
            }

            std::vector<Ball> getBalls() const {
                return balls;
            }

            std::vector<Paddle> getPaddles() const {
                return paddles;
            }

            std::vector<HitBox> getDeathBoxes() const {
                return deathBoxes;
            }
    };
}

    // Level file example
    //               *START*
    // Arcanoid
    // Death bottom
    //     1  2  3  4  5  6  7  8  9 10 11
    //  1  *  *  *  *  *  *  *  *  *  *  * 
    //  2  *  *  *  *  *  *  *  *  *  *  *
    //  3  *  *  *  *  *  *  *  *  *  *  *
    //  4  *  *  *  *  *  *  *  *  *  *  *
    //  5  *  *  *  *  *  *  *  *  *  *  *
    //  6  *  *  *  *  *  *  *  *  *  *  *
    //  7  *  *  *  *  *  *  *  *  *  *  *
    //  8  *  *  *  *  *  *  *  *  *  *  *
    //  9  *  *  *  *  *  *  *  *  *  *  *
    // 10  *  *  *  *  *  *  *  *  *  *  *
    // 11  *  *  *  *  *  *  *  *  *  *  *
    // 12                                 
    // 13                                 
    // 14                                 
    // 15                                 
    // 16                 .               
    // 17                                 
    // 18                                 
    // 19                                 
    // 20                                 
    // 21                                 
    // 22                                 
    // 23                 _               
    //     1  2  3  4  5  6  7  8  9 10 11
    //                *END*
    //
    // Death: bottom; top; both; none;
    //
    // * - Brick (default: Yellow)
    // . - Ball (default: Red)
    // _ - Paddle (default: Red)
    //
    // w - White
    // r - Red
    // g - Green
    // b - Blue
    // y - Yellow
    // m - Magenta
    // c - Cyan
    //
    // Syntax: r* - Red Brick
    //
    // File must be 27 rows.
    // Field must be filled with spaces.
