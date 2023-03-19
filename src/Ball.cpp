#include "Ball.h"

bool Ball::init()
{
  //load ball texture
  ball_texture.loadFromFile("Data/Images/ball.png");
  ball.setTexture(ball_texture);

  return true;
}

void Ball::normalise()
{
  float magnitude = sqrt(pow(vectors[0],2) + pow(vectors[1], 2));

  unit_vector[0] = vectors[0]/magnitude;
  unit_vector[1] = vectors[1]/magnitude;
}

void Ball::moveBall(float dt)
{
  checkEdge();
  normalise();
  ball.move(unit_vector[0] * ball_speed * dt, unit_vector[1] * ball_speed * dt);

  ball_x = ball.getPosition().x + (ball.getGlobalBounds().width/2);
  ball_y = ball.getPosition().y + (ball.getGlobalBounds().height/2);
}

int Ball::checkEdge()
{
  //ball reach bottom screen
  if (ball.getPosition().y > (720 - ball.getGlobalBounds().height))
  {
    vectors[1] = vectors[1]*-1;
    ball.setPosition(ball.getPosition().x, 720 - ball.getGlobalBounds().height - 1);
  }
  //ball reach top screen
  else if (ball.getPosition().y < 0)
  {
    vectors[1] = vectors[1]*-1;
    ball.setPosition(ball.getPosition().x, 1);
  }
  //ball reach left screen
  else if (ball.getPosition().x < 0)
  {
    vectors[0] = vectors[0]*-1;
    ball.setPosition(540, 360);

    return 1;
  }
  //ball reach right screen
  else if (ball.getPosition().x > (1080 - ball.getGlobalBounds().width))
  {
    vectors[0] = vectors[0]*-1;
    ball.setPosition(540, 360);

    return 2;
  }
  return 0;
}

void Ball::resetGame()
{
  //reset ball vector and position
  ball.setPosition(540, 360);
  vectors[0] = 5;
  vectors[1] = 5;
}