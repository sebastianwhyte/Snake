//
// Created by Sebastian2 on 1/28/23.
//

#include "Game.h"

// Constructor
Game::Game()  : m_window("Snake", sf::Vector2u(800, 600)), m_snake(m_world.GetBlockSize()),
                m_world(sf::Vector2u(800, 600))
{
    RestartClock();
    //srand(time(nullptr));

    m_elapsedTime = 0.0f;
}

// -------------------------------------------------------------------------
// Deconstructor
Game::~Game()
{

}

// -------------------------------------------------------------------------
// Updates the game
void Game::Update()
{
    m_window.Update();

    // Fixed time step
    float timeStep = 1.0f / m_snake.GetSpeed();

    if (m_elapsedTime >= timeStep)
    {
        m_snake.Tick();
        m_world.Update(m_snake);
        m_elapsedTime -= timeStep;

        if (m_snake.HasLost())
        {
            m_snake.Reset();
        }
    }
}

// -------------------------------------------------------------------------
// Handles the user input based on the key they pressed and sets the direction of the snake.
void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDirection() != Direction::Down)
    {
        m_snake.SetDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDirection() != Direction::Up)
    {
        m_snake.SetDirection(Direction::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDirection() != Direction::Right)
    {
        m_snake.SetDirection(Direction::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDirection() != Direction::Left)
    {
        m_snake.SetDirection(Direction::Right);
    }
}

// -------------------------------------------------------------------------
// Draws the elements to the window
void Game::Render()
{
    m_window.BeginDraw();

    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());

    m_window.EndDraw();
}
// -------------------------------------------------------------------------
/* Retrieves the window
 *
 * @return window
 */
Window *Game::GetWindow()
{
    return &m_window;
}

// -------------------------------------------------------------------------
/* Retrieves the elapsed time since the last time the clock was restarted
 *
 * @return elapsed time since clock was restarted
 */
sf::Time Game::getElapsedTime()
{
    return m_clock.getElapsedTime();
}

// -------------------------------------------------------------------------
// Restarts the clock
void Game::RestartClock()
{
    m_elapsedTime += m_clock.restart().asSeconds();
}




