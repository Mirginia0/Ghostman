#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

const int CoinDurMax = 5000;  // in miliseconds (5 seconds)
const int CoinDurationMin = 1000; // in miliseconds (1 second)

const int maxGameDurationInSeconds = 60;

class CustomSprite : public sf::Sprite
 {
  public:

    void setBounds(int left, int right, int top, int bottom)
     {
      bound_top = top;
      bound_bottom = bottom;
      bound_right = right;
      bound_left = left;
     }


    bool Collision_T(sf::FloatRect wall_bounds, sf::FloatRect ghost_bounds)
     {
      if ((ghost_bounds.top+ghost_bounds.height >= wall_bounds.top-3) && (ghost_bounds.top < wall_bounds.top)
      && (ghost_bounds.left+ghost_bounds.width > wall_bounds.left+3) && (ghost_bounds.left < wall_bounds.left+wall_bounds.width-3))
       {
        return 1;
       }
      else{return 0;}

     }

    // add other collison checking sides here


    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect ghost_bounds) //BOTTOM
    {
        if ((ghost_bounds.top <= wall_bounds.top + wall_bounds.height+3) && (ghost_bounds.top + ghost_bounds.height > wall_bounds.top + wall_bounds.height)
         && (ghost_bounds.left + ghost_bounds.width > wall_bounds.left+3) && (ghost_bounds.left < wall_bounds.left + wall_bounds.width-3))
         {
            return 1;
        }
        else{return 0;}
    }

    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect ghost_bounds) //LEFT
    {
        if ((ghost_bounds.left + ghost_bounds.width >= wall_bounds.left-3) && (ghost_bounds.left < wall_bounds.left)
         && (ghost_bounds.top + ghost_bounds.height > wall_bounds.top+3) && (ghost_bounds.top < wall_bounds.top + wall_bounds.height-3))
         {
            return 1;
        }
        else{return 0;}
    }

    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect ghost_bounds) //RIGHT
    {
        if ((ghost_bounds.left <= wall_bounds.left + wall_bounds.width+3) && (ghost_bounds.left + ghost_bounds.width > wall_bounds.left + wall_bounds.width)
         && (ghost_bounds.top + ghost_bounds.height > wall_bounds.top+3) && (ghost_bounds.top < wall_bounds.top + wall_bounds.height-3))
         {
            return 1;
        }
        else{return 0;}
    }





    void moveInDirection(const sf::Time &elapsed, const std::vector<sf::Sprite> &obstacles)
     {


      bool top=0, left=0, bottom=0, right=0;
      for(auto &obstacle : obstacles)
      {
      sf::FloatRect ghost_bounds = getGlobalBounds();
      sf::FloatRect wall_bounds = obstacle.getGlobalBounds();
       if(Collision_T(wall_bounds, ghost_bounds) == 1){top = 1;}
       if(Collision_L(wall_bounds, ghost_bounds) == 1){left = 1;}
       if(Collision_B(wall_bounds, ghost_bounds) == 1){bottom = 1;}
       if(Collision_R(wall_bounds, ghost_bounds) == 1){right = 1;}
      }


      sf::FloatRect rectangle_bounds = getGlobalBounds();
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rectangle_bounds.top > bound_top && bottom != true)
       {
        move(0, -m_speed_y*elapsed.asSeconds());

       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rectangle_bounds.top + rectangle_bounds.height < bound_bottom && top != true)
       {
        move(0, m_speed_y*elapsed.asSeconds());
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rectangle_bounds.left > bound_left && right != true)
       {
        move(-m_speed_x*elapsed.asSeconds(), 0);
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rectangle_bounds.left + rectangle_bounds.width < bound_right && left != true)
       {
        move(m_speed_x*elapsed.asSeconds(), 0);
       }
     }


  private:
    int m_speed_x = 200;
    int m_speed_y = 200;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
 };

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    sf::Font main_font;
    if (!main_font.loadFromFile("arial.ttf")) {
        return 1;
    }
 
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Clock clock;

    sf::Texture ghost_tex;
    if(!ghost_tex.loadFromFile("ghostdown.png")) { return 1; }

    sf::Texture background_tex;
    if(!background_tex.loadFromFile("background.png")) { return 1; }
    background_tex.setRepeated(true);

    sf::Texture wall_tex;
    if(!wall_tex.loadFromFile("wall.png")) { return 1; }
    wall_tex.setRepeated(true);
 
    sf::Texture coin_tex;
    if(!coin_tex.loadFromFile("coin_01.png")) { return 1; }

    CustomSprite ghost;
    ghost.setTexture(ghost_tex);
    ghost.setPosition(390,290);

    sf::Sprite background;
    background.setTexture(background_tex);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,800,600));

    sf::Sprite coin;
    coin.setTexture(coin_tex);
    coin.setOrigin(45/2, 48/2);
    coin.setScale(0.5, 0.5);
    coin.setPosition(rand() % 800, rand() % 600);

    std::vector<sf::Sprite> walls;

    sf::Sprite wall1;

    bool isKeyPressed = false;
 
    sf::Clock coinTimer;
    int score = 0;

    sf::Clock gameTimer;

    bool isGameOver = false;

    while (window.isOpen())
    {
      sf::Event event;

      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::MouseButtonPressed
            && event.mouseButton.button == sf::Mouse::Left
            && isGameOver) {
            window.close();
        }
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
      }
      
      if (isGameOver) {
          continue;
      }
      
      if (gameTimer.getElapsedTime().asSeconds() > maxGameDurationInSeconds) {
        isGameOver = true;
        sf::Text gameOverText("Game Over!", main_font);
        gameOverText.setPosition(50, 50);
        std::string scoreString = std::string("Final score: ") + to_string(score);
        sf::Text scoreText(scoreString, main_font);
        scoreText.setPosition(100, 100);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.display();
        continue;
      }

      sf::Time elapsed = clock.restart();      

      if (coinTimer.getElapsedTime().asMilliseconds() > CoinDurMax){
          coinTimer.restart();
          coin.setPosition(rand() % 800, rand() % 600);
      }

      if (event.type == sf::Event::KeyPressed){
          if (event.key.code == sf::Keyboard::Up){
              if(!ghost_tex.loadFromFile("ghostup.png")) {
                  ghost.setTexture(ghost_tex);
                  isKeyPressed = true;
              }

          }
          if (event.key.code == sf::Keyboard::Left){
              if(!ghost_tex.loadFromFile("ghostleft.png")) {
                  ghost.setTexture(ghost_tex);
              }

          }
          if (event.key.code == sf::Keyboard::Right){
              if(!ghost_tex.loadFromFile("ghostright.png")) {
                  ghost.setTexture(ghost_tex);
              }

          }
          if (event.key.code == sf::Keyboard::Down){
              if(!ghost_tex.loadFromFile("ghostdown.png")) {
                  ghost.setTexture(ghost_tex);
              }

          }

      }
      if (event.type == sf::Event::KeyReleased) {
          if (event.key.code == sf::Keyboard::Up) {
              if(!ghost_tex.loadFromFile("ghostup.png")) {
                  ghost.setTexture(ghost_tex);
                  isKeyPressed = false;
              }
          }
          if (event.key.code == sf::Keyboard::Left) {
              if(!ghost_tex.loadFromFile("ghostleft.png")) {
                  ghost.setTexture(ghost_tex);
                  isKeyPressed = false;
              }
          }
          if (event.key.code == sf::Keyboard::Right) {
              if(!ghost_tex.loadFromFile("ghostright.png")) {
                  ghost.setTexture(ghost_tex);
                  isKeyPressed = false;
              }
          }
          if (event.key.code == sf::Keyboard::Down) {
              if(!ghost_tex.loadFromFile("ghostdown.png")) {
                  ghost.setTexture(ghost_tex);
                  isKeyPressed = false;
              }
          }
      if (!isKeyPressed) {
          if (!ghost_tex.loadFromFile("ghostdown.png")) {
              ghost.setTexture(ghost_tex);
          }
      }
        }
      if (ghost.getGlobalBounds().intersects(coin.getGlobalBounds())){
          score++;
          coin.setPosition(rand() % 800, rand() % 600);
          coinTimer.restart();
      }

      ghost.setBounds(0, window.getSize().x, 0, window.getSize().y);
      ghost.moveInDirection(elapsed, walls);

      window.clear(sf::Color::Black);
      window.draw(background);
      window.draw(ghost);
      window.draw(coin);

      for (auto &wall : walls){
           window.draw(wall);
      }

      window.display();
     }

    std::cout << "TOTAL COINS EATEN: " << score << std::endl;
 
    return 0;
}
