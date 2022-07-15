#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

#include "constants.h"
#include "gameEvent.h"
#include "object.h"
#include "forms.h"
#include "properties.h"
#include "paddle.h"
#include "brick.h"
#include "hitBox.h"

namespace Arcanoid {
    class Ball : public Object, public CircleForm, public Updatable, 
                 public Collidable<Paddle>, public Collidable<Brick>, 
                 public Collidable<HitBox> {
        private:
            sf::Vector2f velocity{0.f, -BALL_VELOCITY};

        public:
            explicit Ball(const int start_x, const int start_y, const sf::Color color = sf::Color::Red):
                     CircleForm(start_x, start_y, BALL_RADIUS, color) {}

            virtual void update() {
                getShape().move(velocity);

                if (left() < 0) {
                    getShape().setPosition(FIELD_OFFSET_X + BALL_RADIUS, y() + FIELD_OFFSET_Y);
                    velocity.x = -velocity.x;
                } else if (right() > FIELD_WIDTH) {
                    getShape().setPosition(FIELD_OFFSET_X + FIELD_WIDTH - BALL_RADIUS, y() + FIELD_OFFSET_Y);
                    velocity.x = -velocity.x;
                }

                if (top() < 0) {
                    getShape().setPosition(x() + FIELD_OFFSET_X, FIELD_OFFSET_Y + BALL_RADIUS);
                    velocity.y = -velocity.y;
                }
                else if (bottom() > FIELD_HEIGHT) {
                    getShape().setPosition(x() + FIELD_OFFSET_X, FIELD_OFFSET_Y + FIELD_HEIGHT - BALL_RADIUS);
                    velocity.y = -velocity.y;
                }
            }

            virtual void testCollision(std::vector<GameEvent> &gameEvents, Paddle& collideWith) {
                if (!Form::isIntersecting(collideWith, *this)) return;

                float overlapLeft = right() - collideWith.left();
                float overlapRight = collideWith.right() - left();
                float overlapTop = bottom() - collideWith.top();
                float overlapBottom = collideWith.bottom() - top();

                bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
                bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

                float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
                float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

                if (abs(minOverlapX) < abs(minOverlapY)) {
                    float angle;
                    if (ballFromTop) {
                        angle = (y() - collideWith.top()) / (PADDLE_HEIGHT / 2);
                        velocity.y = sin((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    } else {
                        angle = (collideWith.bottom() - y()) / (PADDLE_HEIGHT / 2);
                        velocity.y = -sin((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    }

                    if (ballFromLeft) {
                        velocity.x = -cos((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    } else {
                        velocity.x = cos((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    }
                } else {
                    float angle;
                    if (ballFromLeft) {
                        angle = (x() - collideWith.left()) / (PADDLE_WIDTH / 2);
                        velocity.x = -cos((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    } else {
                        angle = (collideWith.right() - x()) / (PADDLE_WIDTH / 2);
                        velocity.x = cos((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    }

                    if (ballFromTop) {
                        velocity.y = -sin((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    } else {
                        velocity.y = sin((angle * 70 + 20) * PI / 180) * sqrt(2 * BALL_VELOCITY * BALL_VELOCITY);
                    }
                }
            }

            virtual void testCollision(std::vector<GameEvent> &gameEvents, Brick& collideWith) {
                if (!Form::isIntersecting(collideWith, *this)) return;

                collideWith.setDestroyed(true);

                GameEvent event;
                event.type = GameEvent::ChangeScore;
                event.score.difference = 100;

                gameEvents.push_back(event);

                float overlapLeft = right() - collideWith.left();
                float overlapRight = collideWith.right() - left();
                float overlapTop = bottom() - collideWith.top();
                float overlapBottom = collideWith.bottom() - top();

                bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
                bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

                float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
                float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

                if (abs(minOverlapX) < abs(minOverlapY)) {
                    velocity.x = -velocity.x;
                } else {
                    velocity.y = -velocity.y;
                }
            }

            virtual void testCollision(std::vector<GameEvent> &gameEvents, HitBox& collideWith) {
                if (!Form::isIntersecting(collideWith, *this)) return;

                GameEvent event;
                event.type = GameEvent::Lose;
                gameEvents.push_back(event);
            }
    };
}
