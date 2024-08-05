#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}


//g++ main.cpp -o test -IC:/msys64/mingw64/include -IC:/SFML/include -LC:/msys64/mingw64/lib -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
//./test
