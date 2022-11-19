#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>

const static int skin_cell_size = 32;
const static int skin_length = 2;
const static int skin_count = 5;
const static int skin_choice_height = (skin_length + 4) * skin_cell_size;
const static int skin_choice_width = (skin_count + 6) * skin_cell_size;
static int choice = 1;
static int skin = 0;

static int count_of_hearts = 0;

const static int wall_cell_size = 32;
const static int wall_length = 2;
const static int wall_count = 4;
const static int wall_choice_height = (wall_length + 3) * wall_cell_size;
const static int wall_choice_width = (wall_count + 5) * wall_cell_size;
static int choice_wall = 1;
static int wall = 0;

const static int field_color_cell_size = 32;
const static int window_color_height = 256;
const static int window_color_width = 256;
static bool pause = false;
static bool restart = false;
static int color = 1;

static bool color_pause = true;
static bool pause_menu = false;
static bool control_pause = false;
static bool difficulty_pause = false;
static bool game_level_pause = false;
static bool help_pause = false;

constexpr auto FIELD_CELL_TYPE_NONE = 0;
constexpr auto FIELD_CELL_TYPE_APPLE = -1;
constexpr auto FIELD_CELL_TYPE_WALL = -2;
constexpr auto FIELD_CELL_TYPE_GREEN_APPLE = -3;
constexpr auto FIELD_CELL_TYPE_HEART = -4;
constexpr auto FIELD_CELL_TYPE_YELLOW_APPLE = -5;

constexpr auto SNAKE_DIRECTION_UP = 0;
constexpr auto SNAKE_DIRECTION_RIGHT = 1;
constexpr auto SNAKE_DIRECTION_DOWN = 2;
constexpr auto SNAKE_DIRECTION_LEFT = 3;

const static int field_size_x = 40;
const static int field_size_y = 25;

const static int cell_size = 32;
const static int window_width = field_size_x * cell_size;
const static int window_height = field_size_y * cell_size;


const static int main_menu_width = 25 * cell_size;
const static int main_menu_height = 20 * cell_size;

const static int pause_menu_width = 25 * cell_size;
const static int pause_menu_height = 15 * cell_size;

const static int volume_menu_width = 25 * cell_size;
const static int volume_menu_height = 15 * cell_size;

static int type_of_control;

static std::vector <int> snake_direction_queue;
static bool game_over = false;
static bool game_paused = false;
static int count_of_apples = 0;
const static int n = 10;
static bool event_green = false;
static bool event_yellow = false;
static bool invert_control = false;
static bool length_increase = false;
static bool score_decrease = false;
static int count_of_red_apples = 0;
static int x = 157, y = 255, z = 212, r, g, b;
static bool exit_game;
static bool win_game = false;
static bool new_game = true;

static bool op_help = false;
static bool set_op = false;
static bool op_main = false;

struct GameState {
    int field[field_size_y][field_size_x];
    int snake_position_x = field_size_x / 2;
    int snake_position_y = field_size_y / 2;
    int snake_length = 4;
    int snake_direction = SNAKE_DIRECTION_RIGHT;
    int score = 0;
    int last_score = 0;
    int speed = 100;
    int speed_last;
    int count_of_lifes = 0;
};

struct HighGameState {
    int field[field_size_y][field_size_x];
    int snake_position_x = field_size_x / 2;
    int snake_position_y = field_size_y / 2;
    int snake_length = 4;
    int snake_direction = SNAKE_DIRECTION_RIGHT;
    int score = 0;
    int last_score = 0;
    int speed = 100;
    int speed_last;
    int count_of_lifes = 0;
};

static GameState game_state;

static std::vector <GameState> game_last_states;

static bool roll_back = false;

static sf::Font font_menu;

static std::vector <sf::Text> text_menu_items;

static std::vector <std::string> lose_menu_items{"Your score: ", "Restart", "Exit to main menu", "GAME OVER"};

static std::vector<std::string> menu_items = {"Start new game", "Level", "Settings", "Help", "Quit", "SNAKE",
                                              "By Vanyok77797", "Version 4.2.3"};

static std::vector <std::string> settings_menu_items{"Type of control", "Field color", "Snake skin", "Walls",
                                                     "Difficulty level", "Volume", "Back to main menu", "Game settings"};

static std::vector<std::string> control_menu_items = {"Cursors", "W, A, S, D", "Back to settings", "Type of game control"};

static std::vector<std::string> difficulty_menu_items = {"Standard", "Easy", "Medium", "Hard", "Crazy", "Impossible",
                                                         "Back to settings", "Difficulty level"};

static std::vector <std::string> pause_menu_items = {"Score: ", "Resume", "Exit to main menu", "Pause", "Lives: "};

static std::vector <std::string> volume_menu_items = {"Volume: ", "Exit to main menu", "Volume settings"};

static std::vector<std::string> help_menu_items = {"Apples: ", "\t*Green - random trap", "\t*Golden - random bonus",
                                                        "\t*Red - food for snake", "Heart - every 5 gives life,\nremoves bad effect",
                                                        "Space - game pause", "Tab - to turn off the music",
                                                        "X - to turn on the music", "Enter to close help", "Help"};
static std::vector <std::string> level_menu_items = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5",
                                                     "Level 6" , "Level 7", "Back to main menu", "Choose level"};


static int color_menu = 0;
static int menu_type = 0;
static int lose_color = 1;
static int settings_color = 0;
static int color_of_control = 0;
static int difficulty_color = 0;
static int pause_color = 1;
static int volume_color = 1;
static int level_color = 0;
static int lifes_color = 0;

static int game_level = 0;
static int volume_level = 30;
static int music_level = 20;

static sf::Sound apple_sound;
static sf::SoundBuffer apple_buffer;

static sf::Sound game_over_sound;
static sf::SoundBuffer game_over_buffer;

static sf::Sound yellow_apple_sound;
static sf::SoundBuffer yellow_apple_buffer;

static sf::Sound green_apple_sound;
static sf::SoundBuffer green_apple_buffer;

static sf::Sound menu_sound;
static sf::SoundBuffer menu_buffer;

static sf::Sound enter_sound;
static sf::SoundBuffer enter_buffer;

static sf::Sound heart_sound;
static sf::SoundBuffer heart_buffer;

static sf::Sound life_up_sound;
static sf::SoundBuffer life_up_buffer;

static sf::Music game_music;



