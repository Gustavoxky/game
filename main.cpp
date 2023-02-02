#include <SFML/Graphics.hpp>
#include <memory>
#include <experimental/random>

int main() {
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "fundamentos");
    window.setFramerateLimit(60);

    auto object = std::make_shared<sf::RectangleShape>();
    object -> setSize(sf::Vector2f(100.f,100.f));
    object -> setFillColor(sf::Color(0,255,0));
    object -> setPosition(sf::Vector2f(10.f, 10.f));

    float x = static_cast <float> (std::experimental::randint(10, (int)(window.getSize().x - object->getSize().x)));
    object->setPosition(x, 10.f);

    sf::Vector2i position_mouse_win;
    sf::Vector2f position_mouse_coord;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            position_mouse_win = sf::Mouse::getPosition(window);
            position_mouse_coord = window.mapPixelToCoords(position_mouse_win);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(object->getGlobalBounds().contains(position_mouse_coord)) {
                 x = static_cast <float> (std::experimental::randint(10, (int)(window.getSize().x - object->getSize().x)));
            object->setPosition(x, 10.f);
            }
        }

        object->move(0.f, 1.9f);
        if(object->getPosition().y > window.getSize().y) {
            x = static_cast <float> (std::experimental::randint(10, (int)(window.getSize().x - object->getSize().x)));
            object->setPosition(x, 10.f);

        }

        window.clear();
        window.draw(*object);
        window.display();
        
    }
    
    return EXIT_SUCCESS;
}
