
#ifndef PONG_BALL_H
#define PONG_BALL_H
#include <SFML/Graphics.hpp>
#include <cmath>

class Ball
{
 private:
  float ball_speed = 400;
  sf::Texture ball_texture;

 public:
  bool init();
  void normalise();
  void moveBall(float dt);
  int checkEdge();
  void resetGame();

  float vectors[2];
  float unit_vector[2];

  float ball_x;
  float ball_y;

  sf::Sprite ball;
};

#endif // PONG_BALL_H
