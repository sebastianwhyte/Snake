//
// Created by Sebastian2 on 2/4/23.
//

#ifndef SNAKE_GAME_WORLD_H
#define SNAKE_GAME_WORLD_H


#include <SFML/System/Vector2.hpp>
#include "Snake.h"

class World
{
    public:
        explicit World(sf::Vector2u l_windowSize);
        ~World();

        // Methods
        int GetBlockSize();

        void RespawnApple();
        void Update(Snake& l_player);
        void Render(sf::RenderWindow& l_window);


    private:
        sf::Vector2u m_windowSize;
        sf::Vector2i m_item;
        int m_blockSize;

        sf::CircleShape m_appleShape;
        sf::RectangleShape m_bounds[4];
};


#endif //SNAKE_GAME_WORLD_H
