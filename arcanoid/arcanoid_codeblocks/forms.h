#pragma once

#include <SFML/Graphics.hpp>

namespace Arcanoid {
    class Form {

        public:
            virtual ~Form() {}

            template <class T1, class T2>
            static bool isIntersecting(const T1& A, const T2& B) {
                return A.right() >= B.left() && A.left() <= B.right() &&
                        A.bottom() >= B.top() && A.top() <= B.bottom();
            }

            virtual sf::Shape& getShape() = 0;

            virtual float x() const = 0;
            virtual float y() const = 0;
            virtual float left() const = 0;
            virtual float right() const = 0;
            virtual float top() const = 0;
            virtual float bottom() const = 0;
    };

    class RectangleForm : public Form {
        private:
            sf::RectangleShape shape;
        
        public:
            explicit RectangleForm(int start_x, int start_y, float width, float height, sf::Color color) {
                shape.setPosition(start_x, start_y);
                shape.setSize({width, height});
                shape.setFillColor(color);
                shape.setOrigin(width / 2.f, height / 2.f);
            }

            sf::Shape& getShape() {
                return shape;
            }

            virtual float x() const { return shape.getPosition().x - FIELD_OFFSET_X; }
            virtual float y() const { return shape.getPosition().y - FIELD_OFFSET_Y; }
            virtual float left() const { return x() - shape.getSize().x / 2.f; }
            virtual float right() const { return x() + shape.getSize().x / 2.f; }
            virtual float top() const { return y() - shape.getSize().y / 2.f; }
            virtual float bottom() const { return y() + shape.getSize().y / 2.f; }
    };

    class CircleForm : public Form {
        private:
            sf::CircleShape shape;
        
        public:
            explicit CircleForm(int start_x, int start_y, int radius, sf::Color color) {
                shape.setPosition(start_x, start_y);
                shape.setRadius(radius);
                shape.setFillColor(color);
                shape.setOrigin(radius, radius);
            }

            sf::Shape& getShape() {
                return shape;
            }

            virtual float x() const { return shape.getPosition().x - FIELD_OFFSET_X; }
            virtual float y() const { return shape.getPosition().y - FIELD_OFFSET_Y; }
            virtual float left() const { return x() - shape.getRadius(); }
            virtual float right() const { return x() + shape.getRadius(); }
            virtual float top() const { return y() - shape.getRadius(); }
            virtual float bottom() const { return y() + shape.getRadius(); }
    };
}
