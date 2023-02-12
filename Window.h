//
// Created by Sebastian2 on 1/22/23.
//

#ifndef SNAKE_GAME_WINDOW_H
#define SNAKE_GAME_WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

class Window
{
    public:
        // Constructors & Deconstructor
        Window();
        Window(const std::string& l_title, const sf::Vector2u& l_size);
        ~Window();

        // Methods
        void BeginDraw();       // Clear window
        void EndDraw();         // Display changes
        void Update();
        void ToggleFullScreen();
        void Draw(sf::Drawable& l_drawable);

        bool IsDone();
        bool isFullScreen();

        sf::RenderWindow* GetRenderWindow();
        sf::Vector2u GetWindowSize();


    private:
        // Methods
        void Setup(const std::string& l_title, const sf::Vector2u l_size);
        void Destroy();
        void Create();

        // Variables
        sf::RenderWindow window;
        sf::Vector2u windowSize;
        std::string windowTitle;
        bool isDone;
        bool m_isFullScreen;
};


#endif //SNAKE_GAME_WINDOW_H
