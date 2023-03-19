
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

  void playAnimation();
  void checkScore (int score);
  bool collision(sf::Sprite sprite, float ball_x, float ball_y);
  void resetGame();

 private:
  sf::RenderWindow& window;
  sf::Font font;

  //scenes
  enum Scenes {tittle, mode_selection, one_player, two_player};
  Scenes current_scene = tittle;


  //----- tittle -----//

  //tittle
  sf::Sprite tittle_display;
  sf::Texture tittle_display_texture;
  sf::IntRect spritesheet_rect;
  sf::Clock animation_timer;
  bool animation_back = false;

  //enter_text
  sf::Text enter_text;

  //background
  sf::Sprite background;
  sf::Texture background_texture;


  //----- mode_selection -----//

  //mode_selection_text
  sf::Text mode_selection_text;

  //one_player
  sf::Sprite one_player_button;
  sf::Texture one_player_button_texture;

  //two_player
  sf::Sprite two_player_button;
  sf::Texture two_player_button_texture;

  bool mode_selected = false;


  //----- one_player and two_player -----//

  Paddle paddle;

  Ball ball;

  bool pause = false;
  bool pause_option_selected = false;
  bool game_finished = false;
  int random_num;

  //scores
  int score_blue = 0;
  sf::Text scoreboard_blue;

  int score_red = 0;
  sf::Text scoreboard_red;

  //pause_text
  sf::Text pause_text;

  //exit_button
  sf::Sprite exit_button;
  sf::Texture exit_button_texture;

  //resume_button
  sf::Sprite resume_button;
  sf::Texture resume_button_texture;

  //grey_overlay
  sf::Sprite grey_overlay;
  sf::Texture grey_overlay_texture;

  //winner_text
  sf::Text winner_text;

  //wall
  sf::Sprite wall[8];
  sf::Texture wall_blue_texture;
  sf::Texture wall_red_texture;
};

#endif // PONG_GAME_H
