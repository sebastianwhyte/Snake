//
// Created by Sebastian2 on 1/31/23.
//
#include <SFML/Graphics.hpp>

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H


enum class Direction
{
    None, Up, Down, Left, Right
};


struct SnakeSegment
{
    SnakeSegment(int x, int y) : position(x,y) {}   // Constructor with initializer list
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;


class Snake
{
    public:
        explicit Snake(int l_blockSize);
        ~Snake();

        // Helper methods
        int GetSpeed();
        int GetLives();
        int GetScore();

        void IncreaseScore();
        void SetDirection(Direction l_direction);

        bool HasLost();

        Direction GetPhysicalDirection();
        Direction GetDirection();
        sf::Vector2i GetPosition();

        void Lose();
        void ToggleLost();

        void Extend();
        void Reset();

        void Move();
        void Tick();
        void Cut(int l_segments);
        void Render(sf::RenderWindow& l_window);


    private:
        void CheckCollision();

        SnakeContainer m_snakeBody;
        int m_size;
        int m_speed;
        int m_lives;
        int m_score;
        bool m_lost;

        Direction m_direction;
        sf::RectangleShape m_bodyRectangle;
};


#endif //SNAKE_GAME_SNAKE_H
