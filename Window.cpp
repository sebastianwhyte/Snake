//
// Created by Sebastian2 on 1/22/23.
//

#include "Window.h"

// Constructor
Window::Window()
{
    Setup("Window", sf::Vector2u(640, 480));
}

// --------------------------------------------------------------------

/* Overloaded constructor that initializes the window with the given title and size
 *
 * @param title of window, size of window
 */

Window::Window(const std::string &l_title, const sf::Vector2u &l_size)
{
    Setup(l_title, l_size);
}

// --------------------------------------------------------------------

// Deconstructor
Window::~Window()
{
    Destroy();
}

// --------------------------------------------------------------------
/* Creates a window of the given size with the specified title
 *
 *  @param title of the window, size of the window
 */
void Window::Setup(const std::string &l_title, const sf::Vector2u l_size)
{
    windowTitle = l_title;            // Title of the window ('m' means member variable)
    windowSize = l_size;            // Size of the window
    m_isFullScreen = false;           // Checks if the window is in full screen mode
    isDone = false;                 // Checks if the window is closed

    Create();
}

// --------------------------------------------------------------------

void Window::Create()
{
    auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);

    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
}

// --------------------------------------------------------------------

// Closes the window
void Window::Destroy()
{
    window.close();
}

// --------------------------------------------------------------------
// Checks for user input & updates the window
void Window::Update()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        // Check if user pressed the Esc key
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            isDone = true;
        }
        else if (event.type == sf::Event::Closed)
        {
            isDone = true;
        }
        // Check if user pressed the F5 key
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
        {
            ToggleFullScreen();
        }
    }
}

// -------------------------------------------------------------------------

// Toggles the window to be full screen
void Window::ToggleFullScreen()
{
    m_isFullScreen = !m_isFullScreen;   // keeps track to see if the window is full screen or not
    Destroy();                          // Destroy then re-create the window
    Create();
}

// -------------------------------------------------------------------------

// Prepares the window for drawing
void Window::BeginDraw()
{
    window.clear(sf::Color::Black);
}

// -------------------------------------------------------------------------

// Stops drawing and displays the changes
void Window::EndDraw()
{
    window.display();
}

// -------------------------------------------------------------------------

// Checks if we are done with the window
bool Window::IsDone()
{
    return isDone;
}

// -------------------------------------------------------------------------
// Retrieves the size of the window
sf::Vector2u Window::GetWindowSize()
{
    return windowSize;
}

// -------------------------------------------------------------------------

// Draws to the window
void Window::Draw(sf::Drawable &l_drawable)
{
    window.draw(l_drawable);
}

// -------------------------------------------------------------------------

bool Window::isFullScreen()
{
    return m_isFullScreen;
}

// -------------------------------------------------------------------------
sf::RenderWindow *Window::GetRenderWindow()
{
    return &window;
}

