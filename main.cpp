

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 512

#define PI 3.14159
#define RADIANS 0.01745329251

int main(void)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Visualizing Collatz Conjecture", sf::Style::Close, settings);

    /* Activating vertical synchronization will limit the number of frames displayed to the refresh rate of the monitor. */
    window.setVerticalSyncEnabled(true);

    /* Settings */
    float line_length = 5.0f;
    float theta    = 0.0f;

    /* In Degrees */
    float starting_angle = 0.0f;
    float even_angle = 6.0f;
    float odd_angle = 6.0f;

    /* In Radians */
    starting_angle = (float) starting_angle * RADIANS;
    even_angle     = (float) -even_angle * RADIANS;
    odd_angle      = (float) odd_angle * RADIANS;

    float cx = 0.0f;
    float cy = 0.0f;

    std::vector<std::vector<sf::VertexArray>> Lines;
    std::array<sf::Color, 4> color_pallete = {
        sf::Color(255, 246, 126),
        sf::Color(65, 109, 25),
        sf::Color(191, 234, 124),
        sf::Color(155, 207, 83)
    };

    for (int j=5; j<=5000; j++)
    {
        std::vector<int> sequence{};

        int n = j;

        while (n != 1)
        {
            /* code */
            if (n % 2 == 0)
            {
                n = n / 2;
            } else {
                n = (3*n + 1) / 2;
            }
            sequence.push_back(n);
        }
        
        sequence.push_back(n);    // add number 1

        std::reverse(sequence.begin(), sequence.end());

        std::vector<sf::VertexArray> line{};
        sf::Color line_color = color_pallete[j % 4];

        for (size_t i=0; i<std::size(sequence); i++)
        {
            if (sequence[i] == 1)
            {
                cx = WINDOW_WIDTH / 2.0f;
                cy = WINDOW_HEIGHT;
                theta = starting_angle;             // starting angle
            }

            theta = (sequence[i] % 2 == 0) ? theta + even_angle : theta + odd_angle;

            sf::Vector2f start_line_pos(cx, cy);
            sf::Vector2f end_line_pos(cx, cy - line_length);

            float x1 = start_line_pos.x;
            float y1 = start_line_pos.y;
            float x2 = end_line_pos.x;
            float y2 = end_line_pos.y;
            float x3 = cosf(theta) * (x2 - x1) - sinf(theta) * (y2 - y1) + x1;
            float y3 = sinf(theta) * (x2 - x1) + cosf(theta) * (y2 - y1) + y1;

            sf::VertexArray l(sf::Lines, 2);
            l[0].position = sf::Vector2f(x1, y1);
            l[0].color = line_color;
            l[1].position = sf::Vector2f(x3, y3);
            l[1].color = line_color;

            line.push_back(l);

            cx = x3, cy = y3;
        }
        Lines.push_back(line);
    }

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        for (size_t i = 0; i < std::size(Lines); i++)
        {
            /* code */
            for (size_t j = 0; j < std::size(Lines[i]); j++)
            {
                /* code */
                window.draw(Lines[i][j]);              // Draw lines on the screen.
            }
        }
        window.display();
    }

    return 0;
}