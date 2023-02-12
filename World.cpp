//
// Created by Sebastian2 on 2/4/23.
//

#include "World.h"

// Constructor
World::World(sf::Vector2u l_windowSize)
{
    m_blockSize = 16;

    m_windowSize = l_windowSize;
    RespawnApple();

    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize / 2);

    // Sets up the red border around the window
    for (int i = 0; i < 4; i++)
    {
        m_bounds[i].setFillColor(sf::Color(150, 0, 0));

        if (!(i + 1) % 2)
        {
            m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
        }
        else
        {
            m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
        }


        if (i < 2)
        {
            m_bounds[i].setPosition(0,0);
        }
        else
        {
            m_bounds[i].setOrigin(m_bounds[i].getSize());

            m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
        }
    }
}

// ------------------------------------------------------------------------
// Deconstructor
World::~World()
{

}

// ------------------------------------------------------------------------
// Respawns the apple randomly around the window
void World::RespawnApple()
{
    /* Determines the boundaries within which the apple can be spawned. Subtract 2 to prevent the
     * apple from spawning within the right or bottom walls.
     */
    int max_X = (m_windowSize.x / m_blockSize) - 2;
    int max_Y = (m_windowSize.y / m_blockSize) - 2;

    // Generate random values for the apple's coordinates
    m_item = sf::Vector2i (rand() % max_X + 1, rand() % max_Y + 1);

    m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

// ------------------------------------------------------------------------
/* Updates the world
 *
 * @param snake
 */
void World::Update(Snake &l_player)
{
    // If the snake touches the apple
    if (l_player.GetPosition() == m_item)
    {
        l_player.Extend();
        l_player.IncreaseScore();
        RespawnApple();
    }

    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;

    // If the player goes outside the designated boundaries, call Lose() method
    if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 ||
        l_player.GetPosition().x >= gridSize_x - 1 || l_player.GetPosition().y >= gridSize_y - 1)
    {
        l_player.Lose();
    }
}

// ------------------------------------------------------------------------
/* Retrieves the block size
 *
 * @return block size
 */
int World::GetBlockSize()
{
    return m_blockSize;
}

// ------------------------------------------------------------------------
/* Draws the elements of the world
 *
 * @param window to draw on
 */
void World::Render(sf::RenderWindow &l_window)
{
    // Draw each of the four walls / boundaries
    for (int i = 0; i < 4; i++)
    {
        l_window.draw(m_bounds[i]);
    }

    l_window.draw(m_appleShape);
}

// ------------------------------------------------------------------------
