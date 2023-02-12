//
// Created by Sebastian2 on 1/31/23.
//

#include "Snake.h"

// Constructor
Snake::Snake(int l_blockSize)
{
    m_size = l_blockSize;
    m_bodyRectangle.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    Reset();    // reset the snake

}

// ------------------------------------------------------------------------
// Deconstructor
Snake::~Snake() {}


// ------------------------------------------------------------------------
// Resets the snake into its starting position
void Snake::Reset()
{
    m_snakeBody.clear();    // clear the vector

    // Create a snake that is 3 squares
    m_snakeBody.push_back(SnakeSegment(5, 7));
    m_snakeBody.push_back(SnakeSegment(5,6));
    m_snakeBody.push_back(SnakeSegment(5,5));

    SetDirection(Direction::None);      // start off still

    m_speed = 15;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
}

// ------------------------------------------------------------------------
// This method is responsible for growing the snake once it touches the apple
void Snake::Extend()
{
    if (m_snakeBody.empty())
    {
        return;
    }

    // The last element of the vector will be the tail/tail head
    SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];

    // If the vector/snake has more than 1 element, it has more than just the head. So make a tail bone
    if (m_snakeBody.size() > 1)
    {
        // Get the second to last element of the vector
        SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];

        if (tail_head.position.x == tail_bone.position.x)
        {
            // If the tail head's y coordinate is greater than tail bone's y coordinate then add 1
            if (tail_head.position.y > tail_bone.position.y)
            {
                m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
            }
            // Else, if the tail head's y coordinate is less than tail bone's y coordinate then subtract 1
            else
            {
                m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
            }
        }
        // Do the same with the y coordinate
        else if (tail_head.position.y == tail_bone.position.y)
        {
            if (tail_head.position.x > tail_bone.position.x)
            {
                m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
            }
            else
            {
                m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
            }
        }
        else
        {
            switch(m_direction)
            {
                case Direction::Up:
                    m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_bone.position.y + 1));
                    break;
                case Direction::Down:
                    m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_bone.position.y - 1));
                    break;
                case Direction::Left:
                    m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_bone.position.y));
                    break;
                case Direction::Right:
                    m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_bone.position.y));
                    break;
            }
        }
    }
}

// ------------------------------------------------------------------------
// Acts as an update method
void Snake::Tick()
{
    if (m_snakeBody.empty() || m_direction == Direction:: None)
    {
        return;
    }

    Move();
    CheckCollision();
}

// ------------------------------------------------------------------------
// Moves the snake based on the direction
void Snake::Move()
{
    // Moves each element of the vector
    for (int i = m_snakeBody.size() - 1; i > 0; i--)
    {
        m_snakeBody[i].position = m_snakeBody[i-1].position;
    }

    switch (m_direction)
    {
        case Direction::Left:
            --m_snakeBody[0].position.x;
            break;
        case Direction::Right:
            ++m_snakeBody[0].position.x;
            break;
        case Direction::Up:
            --m_snakeBody[0].position.y;
            break;
        case Direction::Down:
            ++m_snakeBody[0].position.y;
            break;
    }
}

// ------------------------------------------------------------------------
// Checks if the snake has collided with either the wall or itself.
void Snake::CheckCollision()
{
    // No need to check for collision unless we have over 5 elements
    if (m_snakeBody.size() < 5)
    {
        return;
    }

    SnakeSegment& head = m_snakeBody.front();


    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++)
    {
        if (itr->position == head.position)
        {
            /* Subtract current iterator from last element of the vector. This lets us know how many
             elements to remove from the back of the snake up until the point of intersection */
            int segments = m_snakeBody.end() - itr;

            Cut(segments);

            // Because there can only be one collision at a time, break out of the for loop to not waste any more clock cycles
            break;
        }
    }
}

// ------------------------------------------------------------------------
/* Loops based on the l_segments value and pops the elements from the back of the snake
 *
 * @param the number of elements to cut from the snake
 */
void Snake::Cut(int l_segments)
{
    for (int i = 0; i < l_segments; i++)
    {
        m_snakeBody.pop_back();
    }

    --m_lives;

    // If the player runs out of lives, then call the Lose() method
    if (!m_lives)
    {
        Lose();
        return;
    }
}

// ------------------------------------------------------------------------
/* Renders elements to the window
 *
 * @param window to draw on
 */
void Snake::Render(sf::RenderWindow &l_window)
{
    if (m_snakeBody.empty())
    {
        return;
    }

    auto head = m_snakeBody.begin();

    // Set up the properties of the snake's body
    m_bodyRectangle.setFillColor(sf::Color::Yellow);
    m_bodyRectangle.setPosition(head->position.x * m_size, head->position.y * m_size);

    l_window.draw(m_bodyRectangle);

    m_bodyRectangle.setFillColor(sf::Color::Green);

    // Draw the snake and set its position
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++)
    {
        m_bodyRectangle.setPosition(itr->position.x * m_size, itr->position.y * m_size);

        l_window.draw(m_bodyRectangle);
    }
}

// ------------------------------------------------------------------------
/* Sets the direction of the snake
 *
 * @param direction for snake to move in
 */
void Snake::SetDirection(Direction l_direction)
{
    m_direction = l_direction;
}

// ------------------------------------------------------------------------
/* Returns the current direction that the snake is in
 *
 * @return direction of the snake
 */
Direction Snake::GetDirection()
{
    return m_direction;
}

// ------------------------------------------------------------------------
/* Looks at the snake structure and retrieves the direction its facing
 *
 * @return the snake's physical direction
 */
Direction Snake::GetPhysicalDirection()
{
    if (m_snakeBody.size() <= 1)
    {
        return Direction::None;
    }

    SnakeSegment& head = m_snakeBody[0];
    SnakeSegment& neck = m_snakeBody[1];

    if (head.position.x == neck.position.x)
    {
        return (head.position.y > neck.position.y ? Direction::Down : Direction:: Up);
    }
    else if (head.position.y == neck.position.y)
    {
        return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
    }

    return Direction::None;
}

// ------------------------------------------------------------------------
/* Retrieves and returns the snake's position
 *
 * @return snake's position
 */
sf::Vector2i Snake::GetPosition()
{
    return (m_snakeBody.empty() ? sf::Vector2i(1,1) : m_snakeBody.front().position);
}

// ------------------------------------------------------------------------
/* Returns the snake's speed
 *
 * @return speed of the snake
 */
int Snake::GetSpeed()
{
    return m_speed;
}

// ------------------------------------------------------------------------
/* Returns the number of lives the snake has left
 *
 * @return the amount of lives left
 */
int Snake::GetLives()
{
    return m_lives;
}

// ------------------------------------------------------------------------
/* Returns the current score
 *
 * @return score
 */
int Snake::GetScore()
{
    return m_score;
}

// ------------------------------------------------------------------------
// Increments the score by 10 when the snake eats the apple
void Snake::IncreaseScore()
{
    m_score += 10;
}

// ------------------------------------------------------------------------
/* Returns true/false depending on if the player has run out of lives
 *
 * @return boolean indicating whether the player has lost
 */
bool Snake::HasLost()
{
    return m_lost;
}

// ------------------------------------------------------------------------
void Snake::Lose()
{
    m_lost = true;
}

// ------------------------------------------------------------------------
// Changes the truth value of lost
void Snake::ToggleLost()
{
    m_lost = !m_lost;
}
