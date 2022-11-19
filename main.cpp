#include <SFML/Graphics.hpp>
#include "vars.h"
#include "game_mathods.h"

std::vector<std::string> graphics_menu_items = {"Low graphics", "High graphics", "Quit", "Choose graphics"};

int graphics_color = 0;
bool graphics_pause;

void set_sound(){
    enter_buffer.loadFromFile("sounds/enter.wav");
    enter_sound.setBuffer(enter_buffer);
    menu_buffer.loadFromFile("sounds/menu.wav");
    menu_sound.setBuffer(menu_buffer);
}

int main()
{
    set_sound();
    game();



    return 0;
}