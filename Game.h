//
// Created by Sebastian2 on 1/28/23.
//

#ifndef SNAKE_GAME_GAME_H
#define SNAKE_GAME_GAME_H


#include "Window.h"
#include "World.h"


class Game
{
    public:
        Game();
        ~Game();

        void HandleInput();
        void Update();
        void Render();
        Window* GetWindow();

        sf::Time getElapsedTime();
        void RestartClock();

    private:
        Window m_window;

        sf::Clock m_clock;
        float m_elapsedTime;

        World m_world;
        Snake m_snake;
};


#endif //SNAKE_GAME_GAME_H
