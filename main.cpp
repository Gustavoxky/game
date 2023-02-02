#include <SFML/Graphics.hpp>
#include <memory>
#include <experimental/random>
#include <iostream>

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

    int point = {};

    std::vector<sf::RectangleShape> objs;
    size_t max_obj = 5;
    float obj_max_vel = 10.f;
    float obj_vel = obj_max_vel;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            position_mouse_win = sf::Mouse::getPosition(window);
            position_mouse_coord = window.mapPixelToCoords(position_mouse_win);

            if(objs.size() < max_obj) {
                if(obj_vel >= obj_max_vel) {
                    x = static_cast <float> (std::experimental::randint(10, (int)(window.getSize().x - object->getSize().x)));
                    object->setPosition(x, 0.f);
                    objs.push_back( *object );
                    obj_vel = 0.f;

                } else {
                    obj_vel += 1.f;
                }
            }
            for(int i{}; i < objs.size(); i++) {
                bool del = false;
                objs[i].move(0.f, 5.f);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(objs[i].getGlobalBounds().contains(position_mouse_coord)) {
                        del = true;
                        point += 10.f;
                    }
                }
                if(object->getPosition().y > window.getSize().y) {
                    del = true;
                }
                if(del) {
                    objs.erase(objs.begin() + i);
                }
            }
        }
        object->move(0.f, 1.9f);
        window.clear();
        for (auto &e : objs) {
            window.draw(e);
        }
        window.display();
        
    }
    
    return EXIT_SUCCESS;
}
