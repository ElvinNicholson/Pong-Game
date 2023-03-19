
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  //load font
  font.loadFromFile("Data/Fonts/m6x11.ttf");

  //load tittle
  tittle_display_texture.loadFromFile("Data/Images/tittle_spritesheet.png");
  spritesheet_rect.width = 500;
  spritesheet_rect.height = 300;
  tittle_display.setTexture(tittle_display_texture);
  tittle_display.setTextureRect(spritesheet_rect);
  tittle_display.setPosition((window.getSize().x - tittle_display.getGlobalBounds().width)/2, 100);

  //enter_text text
  enter_text.setFont(font);
  enter_text.setString("PRESS ENTER TO PLAY");
  enter_text.setCharacterSize(48);
  enter_text.setPosition((window.getSize().x - enter_text.getGlobalBounds().width)/2, 450);
  enter_text.setFillColor(sf::Color(62, 57, 79));

  //load background
  background_texture.loadFromFile("Data/Images/background.png");
  background.setTexture(background_texture);

  //mode_selection_text text
  mode_selection_text.setFont(font);
  mode_selection_text.setString("CHOOSE GAME MODE");
  mode_selection_text.setCharacterSize(48);
  mode_selection_text.setPosition((window.getSize().x - mode_selection_text.getGlobalBounds().width)/2, 50);
  mode_selection_text.setFillColor(sf::Color(62, 57, 79));

  //load one_player_button
  one_player_button_texture.loadFromFile("Data/Images/one_player.png");
  one_player_button.setTexture(one_player_button_texture);
  one_player_button.setOrigin(one_player_button.getGlobalBounds().width/2, one_player_button.getGlobalBounds().height/2);
  one_player_button.setPosition(window.getSize().x*0.25, 350);
  one_player_button.setScale(1.1, 1.1);

  //load two_player_button
  two_player_button_texture.loadFromFile("Data/Images/two_player.png");
  two_player_button.setTexture(two_player_button_texture);
  two_player_button.setOrigin(two_player_button.getGlobalBounds().width/2, two_player_button.getGlobalBounds().height/2);
  two_player_button.setPosition(window.getSize().x*0.75, 350);
  two_player_button.setColor(sf::Color(128,128,128));

  //scoreboard_blue text
  scoreboard_blue.setFont(font);
  scoreboard_blue.setString(std::to_string(score_blue));
  scoreboard_blue.setCharacterSize(48);
  scoreboard_blue.setPosition(120, 30);
  scoreboard_blue.setFillColor(sf::Color(91, 110, 225));

  //scoreboard_red text
  scoreboard_red.setFont(font);
  scoreboard_red.setString(std::to_string(score_red));
  scoreboard_red.setCharacterSize(48);
  scoreboard_red.setPosition(window.getSize().x - scoreboard_red.getGlobalBounds().width - 120, 30);
  scoreboard_red.setFillColor(sf::Color(172, 50, 50));

  //pause_text text
  pause_text.setFont(font);
  pause_text.setString("GAME PAUSED");
  pause_text.setCharacterSize(48);
  pause_text.setPosition((window.getSize().x - pause_text.getGlobalBounds().width)/2, 100);
  pause_text.setFillColor(sf::Color(62, 57, 79));

  //load exit_button texture
  exit_button_texture.loadFromFile("Data/Images/exit.png");
  exit_button.setTexture(exit_button_texture);
  exit_button.setOrigin(exit_button.getGlobalBounds().width/2, exit_button.getGlobalBounds().height/2);
  exit_button.setPosition(window.getSize().x*0.25, 350);
  exit_button.setScale(1.1, 1.1);

  //load resume_button texture
  resume_button_texture.loadFromFile("Data/Images/resume.png");
  resume_button.setTexture(resume_button_texture);
  resume_button.setOrigin(resume_button.getGlobalBounds().width/2, resume_button.getGlobalBounds().height/2);
  resume_button.setPosition(window.getSize().x*0.75, 350);
  resume_button.setColor(sf::Color(128,128,128));

  //load grey_overlay texture
  grey_overlay_texture.loadFromFile("Data/Images/grey_overlay.png");
  grey_overlay.setTexture(grey_overlay_texture);

  //winner_text text
  winner_text.setFont(font);
  winner_text.setCharacterSize(48);

  //load wall textures
  wall_blue_texture.loadFromFile("Data/Images/wallBlue.png");
  wall_red_texture.loadFromFile("Data/Images/wallRed.png");

  random_num = rand() % (35);

  paddle.init();
  ball.init();

  return true;
}

void Game::playAnimation()
{
  if (animation_timer.getElapsedTime().asSeconds() > 0.15)
  {
    if (spritesheet_rect.left < 8000 && !animation_back)
    {
      spritesheet_rect.left += 500;
    }
    else if (spritesheet_rect.left == 8000 && !animation_back)
    {
      animation_back = true;
    }

    if (spritesheet_rect.left > 0 && animation_back)
    {
      spritesheet_rect.left -= 500;
      if (spritesheet_rect.left == 0 && animation_back)
      {
        animation_back = false;
      }
    }

  tittle_display.setTextureRect(spritesheet_rect);
  animation_timer.restart();
  }
}

void Game::checkScore(int score)
{
  //check if anyone scored
  if (score == 1)
  {
    score_red += 1;
    scoreboard_red.setString(std::to_string(score_red));

    if (current_scene == one_player)
    {
      random_num = rand() % (40 - 15 + 1) + 15;
    }
  }
  else if (score == 2)
  {
    score_blue += 1;
    scoreboard_blue.setString(std::to_string(score_blue));

    if (current_scene == one_player)
    {
      random_num = rand() % (25);
    }
  }

  //check if anyone wins
  if (score_red >= 5 || score_blue >= 5)
  {
    if (score_red >= 5)
    {
      winner_text.setString("RED WON");
      winner_text.setFillColor(sf::Color(172, 50, 50));
    }
    else
    {
      winner_text.setString("BLUE WON");
      winner_text.setFillColor(sf::Color(91, 110, 225));
    }
    winner_text.setPosition((window.getSize().x - winner_text.getGlobalBounds().width)/2, 100);

    //setup exit_button
    exit_button.setPosition(window.getSize().x/2, 350);
    exit_button.setColor(sf::Color(255,255,255));
    exit_button.setScale(1.1, 1.1);

    pause_option_selected = false;
    game_finished = true;
    pause = true;
  }
}

bool Game::collision(sf::Sprite sprite, float ball_x, float ball_y)
{
  if (
    sprite.getPosition().x < ball_x && ball_x < (sprite.getPosition().x + sprite.getGlobalBounds().width))
  {
    //top collision
    if ((sprite.getPosition().y - 5) < ball_y && ball_y < (sprite.getPosition().y+ 5))
    {
      ball.vectors[1] = -5;
      ball.ball.move(0, -5.1);
      return true;
    }
    //bottom collision
    else if ((sprite.getPosition().y + sprite.getGlobalBounds().height - 5) < ball_y && ball_y < (sprite.getPosition().y + sprite.getGlobalBounds().height + 5))
    {
      ball.vectors[1] = 5;
      ball.ball.move(0, 5.1);
      return true;
    }
    //front-top collision
    else if (
      sprite.getPosition().y < ball_y && ball_y < (sprite.getPosition().y + 30))
    {
      ball.vectors[0] = ball.vectors[0]*-1;

      if (ball.vectors[1] < 0)
      {
        ball.vectors[1] = -7.5;
      }
      else
      {
        ball.vectors[1] = 2.5;
      }

      if (ball.vectors[0] < 0)
      {
        ball.ball.move(-5, 0);
      }
      else
      {
        ball.ball.move(5, 0);
      }
      return true;
    }
    //front-mid collision
    else if ((sprite.getPosition().y + 30) < ball_y && ball_y < (sprite.getPosition().y + sprite.getGlobalBounds().height - 30))
    {
      ball.vectors[0] = ball.vectors[0]*-1;

      if (ball.vectors[1] < 0)
      {
        ball.vectors[1] = -5;
      }
      else
      {
        ball.vectors[1] = 5;
      }

      if (ball.vectors[0] < 0)
      {
        ball.ball.move(-5, 0);
      }
      else
      {
        ball.ball.move(5, 0);
      }

      return true;
    }
    //front-bot collision
    else if ((sprite.getPosition().y + sprite.getGlobalBounds().height - 30) < ball_y && ball_y < (sprite.getPosition().y + sprite.getGlobalBounds().height))
    {
      ball.vectors[0] = ball.vectors[0]*-1;

      if (ball.vectors[1] < 0)
      {
        ball.vectors[1] = -2.5;
      }
      else
      {
        ball.vectors[1] = 7.5;
      }

      if (ball.vectors[0] < 0)
      {
        ball.ball.move(-5, 0);
      }
      else
      {
        ball.ball.move(5, 0);
      }

      return true;
    }
    return false;
  }
  return false;
}

void Game::resetGame()
{
  paddle.resetGame();
  ball.resetGame();

  //reset wall
  for (int i = 0; i < 8; i++)
  {
    if (i <= 3)
    {
      wall[i].setTexture(wall_blue_texture);
      wall[i].setPosition(35, 80 + 160 * i);
    }
    else
    {
      wall[i].setTexture(wall_red_texture);
      wall[i].setPosition(window.getSize().x - wall[i].getGlobalBounds().width - 35, 80 + 160 * (i - 4));
    }
  }

  //reset scores
  score_blue = 0;
  scoreboard_blue.setString(std::to_string(score_blue));

  score_red = 0;
  scoreboard_red.setString(std::to_string(score_red));

  //reset pause menu
  pause = false;
  pause_option_selected = false;
  game_finished = false;
  exit_button.setPosition(window.getSize().x*0.25, 350);
  exit_button.setColor(sf::Color(255,255,255));
  exit_button.setScale(1.1, 1.1);
  resume_button.setColor(sf::Color(128,128,128));
  resume_button.setScale(1, 1);
}

void Game::update(float dt)
{
  switch (current_scene)
  {
    case tittle:
      playAnimation();

      break;

    case mode_selection:

      break;

    case one_player:
      if (!pause)
      {
        collision(paddle.paddle_blue, ball.ball_x, ball.ball_y);
        collision(paddle.paddle_red, ball.ball_x, ball.ball_y);
        for (int i = 0; i < 8; i++)
        {
          if (collision(wall[i], ball.ball_x, ball.ball_y))
          {
            wall[i].setPosition(0, -100);
          }
        }
        ball.moveBall(dt);
        paddle.moveBluePaddle(dt);
        paddle.botRedPaddle(dt, ball.ball_x, ball.ball_y, random_num);
        checkScore(ball.checkEdge());
      }

      break;

    case two_player:
      if (!pause)
      {
        collision(paddle.paddle_blue, ball.ball_x, ball.ball_y);
        collision(paddle.paddle_red, ball.ball_x, ball.ball_y);
        for (int i = 0; i < 8; i++)
        {
          if (collision(wall[i], ball.ball_x, ball.ball_y))
          {
            wall[i].setPosition(0, -100);
          }
        }
        ball.moveBall(dt);
        paddle.moveBluePaddle(dt);
        paddle.moveRedPaddle(dt);
        checkScore(ball.checkEdge());
      }

      break;
  }
}

void Game::render()
{
  window.draw(background);

  switch (current_scene)
  {
    case tittle:
      window.draw(tittle_display);
      window.draw(enter_text);

      break;

    case mode_selection:
      window.draw(mode_selection_text);
      window.draw(one_player_button);
      window.draw(two_player_button);

      break;

    case one_player:
    case two_player:
      window.draw(ball.ball);
      window.draw(paddle.paddle_blue);
      window.draw(paddle.paddle_red);
      window.draw(scoreboard_blue);
      window.draw(scoreboard_red);
      window.draw(wall[0]);
      for (int i = 0; i < 8; i++)
      {
        window.draw(wall[i]);
      }

      //pause menu
      if (pause)
      {
        window.draw(grey_overlay);
        window.draw(exit_button);

        if (game_finished)
        {
          window.draw(winner_text);
        }
        if (!game_finished)
        {
          window.draw(resume_button);
          window.draw(pause_text);
        }
      }

      break;
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  switch (current_scene)
  {
    case tittle:
      if (event.key.code == sf::Keyboard::Enter)
      {
        current_scene = mode_selection;
      }

      break;

    case mode_selection:
      if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
      {
        mode_selected = !mode_selected;
        //one_player_button is selected
        if (!mode_selected)
        {
          one_player_button.setColor(sf::Color(255,255,255));
          one_player_button.setScale(1.1, 1.1);

          two_player_button.setColor(sf::Color(128,128,128));
          two_player_button.setScale(1, 1);
        }
        //two_player_button is selected
        else
        {
          one_player_button.setColor(sf::Color(128,128,128));
          one_player_button.setScale(1, 1);

          two_player_button.setColor(sf::Color(255,255,255));
          two_player_button.setScale(1.1, 1.1);
        }
      }
      if (event.key.code == sf::Keyboard::Enter)
      {
        if (!mode_selected)
        {
          resetGame();
          current_scene = one_player;
        }
        else
        {
          resetGame();
          current_scene = two_player;
        }
      }

      break;

    case one_player:
    case two_player:
      if (event.key.code == sf::Keyboard::Escape && !game_finished)
      {
        pause = !pause;
      }
      if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right && !game_finished)
      {
        pause_option_selected = !pause_option_selected;
        //exit_button is selected
        if (!pause_option_selected)
        {
          exit_button.setColor(sf::Color(255,255,255));
          exit_button.setScale(1.1, 1.1);

          resume_button.setColor(sf::Color(128,128,128));
          resume_button.setScale(1, 1);
        }
        //resume_button is selected
        else
        {
          exit_button.setColor(sf::Color(128,128,128));
          exit_button.setScale(1, 1);

          resume_button.setColor(sf::Color(255,255,255));
          resume_button.setScale(1.1, 1.1);
        }
      }
      if (event.key.code == sf::Keyboard::Enter && pause != 0)
      {
        if (!pause_option_selected)
        {
          current_scene = tittle;
        }
        else
        {
          pause = false;
        }
      }

      break;
  }
}