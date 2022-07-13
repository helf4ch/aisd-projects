#pragma once

#include <SFML/Graphics.hpp>

namespace Arcanoid {
    const int WINDOW_WIDTH = 900;
    const int WINDOW_HEIGHT = 900;

    const int FIELD_WIDTH = 804;
    const int FIELD_HEIGHT = 604;
    const int FIELD_OFFSET_X = 48;
    const int FIELD_OFFSET_Y = 100;

    const float CELL_WIDTH = 63.f;
    const float CELL_HEIGHT = 23.f;
    const float CELL_OFFSET_X = 24 + FIELD_OFFSET_X;
    const float CELL_OFFSET_Y = 2 + FIELD_OFFSET_Y;

    const float BALL_RADIUS = 10.f;
    const float BALL_VELOCITY = 5.f;

    const float PADDLE_WIDTH = 60.f;
    const float PADDLE_HEIGHT = 20.f;
    const float PADDLE_VELOCITY = 6.f;

    const float BRICK_WIDTH = 60.f;
    const float BRICK_HEIGHT = 20.f;
    const int COUNT_BRICKS_X = 11;
    const int COUNT_BRICKS_Y = 23;
}