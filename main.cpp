#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <chrono>

std::string wrapText(const std::string& text, const sf::Font& font, unsigned int characterSize, float maxWidth) {
    std::istringstream words(text);
    std::string wrapped, word;
    float spaceWidth = font.getGlyph(' ', characterSize, false).advance;
    float lineWidth = 0;

    while (words >> word) {
        sf::Text temp(word, font, characterSize);
        float wordWidth = temp.getLocalBounds().width;

        if(lineWidth + wordWidth + spaceWidth > maxWidth) {
            wrapped += '\n';
            lineWidth = 0;
        }

        wrapped += word + ' ';
        lineWidth += wordWidth + spaceWidth;
    }

    return wrapped;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Editor");
    std::string text;
    sf::Font font;
    font.loadFromFile("HomemadeApple-Regular.ttf");

    sf::Text textDisplay("", font, 24);
    textDisplay.setFillColor(sf::Color::White);

    sf::RectangleShape cursor(sf::Vector2f(1, 24));
    cursor.setFillColor(sf::Color::White);
    bool cursorVisible = true;
    auto lastBlinkTime = std::chrono::steady_clock::now();
    const auto blinkInterval = std::chrono::milliseconds(500);

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
                textDisplay.setString(wrapText(text, font, 24, window.getSize().x));
            }
        }
        //cursor magic
        sf::FloatRect textBounds = textDisplay.getGlobalBounds();
        cursor.setPosition(textBounds.left + textBounds.width, textBounds.top + textBounds.height - textDisplay.getCharacterSize());
        auto now = std::chrono::steady_clock::now();
        if (now - lastBlinkTime >= blinkInterval) {
            cursorVisible = !cursorVisible;
            lastBlinkTime = now;
        }

        //https://www.sfml-dev.org/documentation/2.0-fr/classsf_1_1Color.php
        window.clear(sf::Color::Black); 
        if (cursorVisible) {
            window.draw(cursor);
        }
        window.draw(textDisplay);
        window.display();
    }
    return 0;
}


//g++ main.cpp -o test -IC:/msys64/mingw64/include -IC:/SFML/include -LC:/msys64/mingw64/lib -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
//./test
