#include <SFML/Graphics.hpp>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Editor");
    std::string text;
    sf::Font font;
    font.loadFromFile("HomemadeApple-Regular.ttf");

    sf::Text textDisplay(text, font, 24);
    textDisplay.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                //Backspace
                if (event.text.unicode == 8 && !text.empty()) {
                    text.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != 8) {
                    text += static_cast<char>(event.text.unicode);
                }
                textDisplay.setString(text);
            }
        }
        //https://www.sfml-dev.org/documentation/2.0-fr/classsf_1_1Color.php
        window.clear(sf::Color::Black); 
        window.draw(textDisplay);
        window.display();
    }
    return 0;
}


//g++ main.cpp -o test -IC:/msys64/mingw64/include -IC:/SFML/include -LC:/msys64/mingw64/lib -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
//./test
