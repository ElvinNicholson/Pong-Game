#include "Paddle.h"

bool Paddle::init()
{
  //load paddle_blue texture
  paddle_blue_texture.loadFromFile("Data/Images/paddleBlue.png");
  paddle_blue.setTexture(paddle_blue_texture);

  //load paddle_red texture
  paddle_red_texture.loadFromFile("Data/Images/paddleRed.png");
  paddle_red.setTexture(paddle_red_texture);

  return true;
}
void Paddle::moveBluePaddle(float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle_blue.getPosition().y > 0)
  {
    paddle_blue.move(0, -paddle_speed * dt);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle_blue.getPosition().y < (720 - paddle_blue.getGlobalBounds().height))
  {
    paddle_blue.move(0, paddle_speed * dt);
  }
}

void Paddle::moveRedPaddle(float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle_red.getPosition().y > 0)
  {
    paddle_red.move(0, -paddle_speed * dt);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle_red.getPosition().y < (720 - paddle_red.getGlobalBounds().height))
  {
    paddle_red.move(0, paddle_speed * dt);
  }
}

void Paddle::botRedPaddle(float dt, float ball_x, float ball_y, int random_num)
{
  float paddle_red_y = paddle_red.getPosition().y + (paddle_red.getGlobalBounds().height/2);

  if (ball_x > 1080*0.4 && ((ball_x + 12.5) < paddle_red.getPosition().x))
  {
    if ((ball_y - random_num) < paddle_red_y && paddle_red_y < (ball_y + random_num))
    {
      // do nothing
    }
    else if (ball_y > paddle_red_y && paddle_red.getPosition().y < (720 - paddle_red.getGlobalBounds().height))
    {
      // move paddle_red down
      paddle_red.move(0, paddle_speed * dt);
    }
    else if (ball_y < paddle_red_y && paddle_red.getPosition().y > 0)
    {
      // move paddle_red up
      paddle_red.move(0, -paddle_speed * dt);
    }
  }
}

void Paddle::resetGame()
{
  //reset paddle position
  paddle_blue.setPosition(80, 360);
  paddle_red.setPosition(1080 - paddle_red.getGlobalBounds().width - 80, 360);
}