
#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H
#include <SFML/Graphics.hpp>

class Paddle
{
 private:
  float paddle_speed = 300;
  sf::Texture paddle_blue_texture;
  sf::Texture paddle_red_texture;

 public:
  bool init();
  void moveBluePaddle(float dt);
  void moveRedPaddle(float dt);
  void botRedPaddle(float dt, float ball_x, float ball_y, int random_num);
  void resetGame();

  sf::Sprite paddle_blue;
  sf::Sprite paddle_red;
};

#endif // PONG_PADDLE_H
