#pragma once

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "object.h"
#include "forms.h"
#include "properties.h"

namespace Arcanoid {
    class Paddle : public Object, public RectangleForm, public Updatable {
        private:
            sf::Vector2f velocity;

        public:
            explicit Paddle(const int start_x, const int start_y, const sf::Color color = sf::Color::Red):
                     RectangleForm(start_x, start_y, PADDLE_WIDTH, PADDLE_HEIGHT, color) {}

            virtual void update() {
                getShape().move(velocity);
                
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) 
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                        && left() > 0) {
                    velocity.x = -PADDLE_VELOCITY;
                } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) 
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                        && right() < FIELD_WIDTH) {
                    velocity.x = PADDLE_VELOCITY;
                } else velocity.x = 0;
            }
    };
}