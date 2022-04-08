#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define LOG(x) std::cout << x << std::endl
#endif

enum gameMode
{
   Static, FirstPerson
};


class Game
{
   public:
      Game();
      virtual ~Game();
      void start();

      std::vector<float> performance;
      int n_circles = 10;
      int R = 15;

      int clicks;

      gameMode gm;

   private:

      sf::RenderWindow _window;

      const int gameWidth = 800;
      const int gameHeight = 500;
      const int FRAMERATE = 120;

      const float cos45 = 0.8;

      const int n_metrics = 2;

      int cnt = 0;

      int current_circle_x;
      int current_circle_y;

      bool clicked_within_circle(int,int);
      void _render();
      void _handleInputs();

      void keep(sf::Vector2i*);

      sf::Event event;
      sf::CircleShape ball;
};

#endif // GAME_HPP
