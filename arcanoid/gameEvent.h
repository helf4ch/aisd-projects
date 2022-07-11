#pragma once

#include <SFML/Graphics.hpp>

namespace Arcanoid {
    class GameEvent {
        
        public:
            struct ChangeScoreEvent {
                int difference;
            };
            
            
            enum EventType {
                Win,
                Lose,
                ChangeScore
            };

            EventType type;

            union {
                ChangeScoreEvent score;
            };
    };
}
