#include <SFML/Graphics.hpp>
#include "vars.h"
#include "Low_graphics_version.h"
#include "High_graphics_version.h"

std::vector<std::string> graphics_menu_items = {"Low graphics", "High graphics", "Quit", "Choose graphics"};

int graphics_color = 0;
bool graphics_pause;

void set_sound(){
    enter_buffer.loadFromFile("sounds/enter.wav");
    enter_sound.setBuffer(enter_buffer);
    menu_buffer.loadFromFile("sounds/menu.wav");
    menu_sound.setBuffer(menu_buffer);
}

void set_graphics_fonts(){
    font_menu.loadFromFile("fonts/BigOldBoldy-dEjR.ttf");
    for (int i = 0; i < control_menu_items.size() - 1; i++) {
        text_menu_items.emplace_back(sf::Text());
        text_menu_items.back().setString(graphics_menu_items.at(i));
        text_menu_items.back().setFont(font_menu);
        text_menu_items.back().setCharacterSize(42);
    }
    text_menu_items.emplace_back(sf::Text());
    text_menu_items.back().setString(graphics_menu_items.at(3));
    text_menu_items.back().setFont(font_menu);
    text_menu_items.back().setCharacterSize(50);
}

void graphics_menu(sf::RenderWindow& window){


    const float menu_width = 554;
    float menu_height = 120;

    const float menu_position_x = (float(main_menu_width) - menu_width) / 2;
    float menu_position_y = (float(main_menu_height) - menu_height) / 2 - 30;

    window.clear(sf::Color(0, 0, 0));
    text_menu_items.at(3).move(menu_position_x - 70, 20);
    text_menu_items.at(3).setFillColor(sf::Color(30, 255,25));
    window.draw(text_menu_items.at(3));
    text_menu_items.at(graphics_color).setFillColor(sf::Color(30, 206, 150));

    for (int i = 0; i < menu_items.size() - 5; i++) {
        text_menu_items.at(i).move(menu_position_x + 25, menu_position_y - 75);
        menu_position_y += 60;
        window.draw(text_menu_items.at(i));
    }
}

void control_graphics_menu(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(graphics_color){
                        case 0:
                            enter_sound.play();
                            text_menu_items.clear();
                            window.close();
                            low_graphics_game();
                            break;
                        case 1:
                            enter_sound.play();
                            text_menu_items.clear();
                            window.close();
                            high_graphics_game();
                            break;
                        case 2:
                            enter_sound.play();
                            text_menu_items.clear();
                            window.close();
                            break;
                    }
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    graphics_color++;
                    if(graphics_color == 3){
                        graphics_color = 0;
                    }
                    graphics_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    graphics_color--;
                    if(graphics_color == -1){
                        graphics_color = 2;
                    }
                    graphics_pause = true;
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
            }
        }
    }

}

int main()
{
    set_sound();
    sf::RenderWindow window(sf::VideoMode(main_menu_width, main_menu_height - 180), "Snake", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    graphics_pause = true;
    while (window.isOpen()) {
        control_graphics_menu(window);
        set_graphics_fonts();
        if(graphics_pause){
            graphics_menu(window);
            text_menu_items.clear();
            graphics_pause = false;
            window.display();
        }
    }

    return 0;
}