#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "object.h"
#include "gameEvent.h"

namespace Arcanoid {
    class Updatable {
        
        public:
            virtual ~Updatable() {}

            virtual void update() = 0;
    };

    template<class T>
    class Collidable {

        public:
            virtual ~Collidable() {}

            virtual void testCollision(std::vector<GameEvent> &gameEvents, T& collideWith) = 0;
    };

    class Destroyable {
        private:
            bool destroyed = false;

        public:
            virtual ~Destroyable() {}

            bool isDestroyed() const {
                return destroyed;
            }

            void setDestroyed(const bool new_destroyed) {
                destroyed = new_destroyed;
            }
    };
}