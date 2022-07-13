#pragma once

#include <SFML/Graphics.hpp>

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
            sf::Vector2f velocity{-BALL_VELOCITY, -BALL_VELOCITY};

        public:
            explicit Ball(const int start_x, const int start_y, const sf::Color color = sf::Color::Red):
                     CircleForm(start_x, start_y, BALL_RADIUS, color) {}

            virtual void update() {
                getShape().move(velocity);

                if (left() < 0) velocity.x = BALL_VELOCITY;
                else if (right() > FIELD_WIDTH) velocity.x = -BALL_VELOCITY;

                if (top() < 0) velocity.y = BALL_VELOCITY;
                else if (bottom() > FIELD_HEIGHT) velocity.y = -BALL_VELOCITY;
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

                if (abs(minOverlapX) < abs(minOverlapY))
                    velocity.x = ballFromLeft ? -BALL_VELOCITY : BALL_VELOCITY;
                else
                    velocity.y = ballFromTop ? -BALL_VELOCITY : BALL_VELOCITY;
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

                if (abs(minOverlapX) < abs(minOverlapY))
                    velocity.x = ballFromLeft ? -BALL_VELOCITY : BALL_VELOCITY;
                else
                    velocity.y = ballFromTop ? -BALL_VELOCITY : BALL_VELOCITY;
            }

            virtual void testCollision(std::vector<GameEvent> &gameEvents, HitBox& collideWith) {
                if (!Form::isIntersecting(collideWith, *this)) return;

                GameEvent event;
                event.type = GameEvent::Lose;
                gameEvents.push_back(event);
            }
    };
}
