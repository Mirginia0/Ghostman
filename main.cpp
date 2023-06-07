#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


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

    CustomSprite ghost;
    ghost.setTexture(ghost_tex);
    ghost.setPosition(390,290);

    sf::Sprite background;
    background.setTexture(background_tex);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,800,600));



    std::vector<sf::Sprite> walls;

    sf::Sprite wall1;

    bool isKeyPressed = false;

    while (window.isOpen())
     {
      sf::Time elapsed = clock.restart();


      sf::Event event;
      while (window.pollEvent(event))
       {
        if (event.type == sf::Event::Closed)
         {
          window.close();
         }
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


      ghost.setBounds(0, window.getSize().x, 0, window.getSize().y);
      ghost.moveInDirection(elapsed, walls);

      window.clear(sf::Color::Black);
      window.draw(background);
      window.draw(ghost);

      for (auto &wall : walls){
           window.draw(wall);
      }

      window.display();
     }

    return 0;
}
