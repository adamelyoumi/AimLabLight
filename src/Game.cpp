#include "Game.hpp"
#include <iostream>

Game::Game(){}


void Game::start()
{

   _window.create(sf::VideoMode(gameWidth, gameHeight), "Larry's Aim Lab");

   //_window.setMouseCursorVisible(false);

   if(gm == FirstPerson)
   {
      _window.setFramerateLimit(140);
      sf::Vector2i window_pos = _window.getPosition();
      sf::Vector2i window_center((int)(gameWidth/2) + window_pos.x, (int)(gameHeight/2) + window_pos.y); // Actual window center coordinates w.r.t. desktop
      sf::Mouse::setPosition(window_center);
   }

   LOG("Window created");
   _window.clear(sf::Color(0,200,0));

   current_circle_x = rand()%(gameWidth-R);
   current_circle_y = rand()%(gameHeight-R);

   clicks = 0;

   ball.setRadius(R);
   ball.setOutlineThickness(1);
   ball.setOutlineColor(sf::Color::Black);
   ball.setFillColor(sf::Color(200,0,0));
   ball.setPosition(current_circle_x - (int)(0.8*R), current_circle_y - (int)(0.8*R) );

   for(int i = 0; i<n_metrics; i++)
   {
      performance.push_back(0.f);
   }

   sf::Clock clock_global;
   sf::Clock clock_framerate;

   LOG("Set scene");

   while (_window.isOpen() && cnt < n_circles)
   {
      _window.clear(sf::Color(0,200,0));
      _window.draw(ball);
      _window.display();
      _handleInputs();
   }

   _window.close();
   LOG("Exited level");

   sf::Time t1 = clock_global.restart();
   performance[0] = (float)t1.asMilliseconds();
}

void Game::keep(sf::Vector2i* ball_xy)
{
   if(ball_xy->x < 0)
   {
      ball_xy->x = 0;
   }
   if(ball_xy->x > gameWidth)
   {
      ball_xy->x = gameWidth - 2*R;
   }
   if(ball_xy->y < 0)
   {
      ball_xy->y = 0;
   }
   if(ball_xy->y < gameHeight)
   {
      ball_xy->y = gameHeight - 2*R;
   }
}

void Game::_handleInputs()
{
   if(gm == Static)
   {
      LOG("Entering Static Game Mode");
      while (_window.pollEvent(event))
      {// Dealing with non-game related events (esc, pause etc)

         switch (event.type)
         {
            case sf::Event::MouseButtonPressed:
               LOG("Detected mouse press");
               clicks++;
               if(event.mouseButton.button == sf::Mouse::Left)
               {
                  LOG("Circle coords: " << current_circle_x << " " << current_circle_y);
                  LOG("Click coords: " << event.mouseButton.x << " " << event.mouseButton.y);
                  LOG((event.mouseButton.x - current_circle_x)*(event.mouseButton.x - current_circle_x) +
                      (event.mouseButton.y - current_circle_y)*(event.mouseButton.y - current_circle_y));
                  LOG(R*R);

                  if(clicked_within_circle(event.mouseButton.x,event.mouseButton.y))
                  {
                     cnt++;
                     current_circle_x = rand()%(gameWidth-R);
                     current_circle_y = rand()%(gameHeight-R);
                     ball.setPosition(current_circle_x - (int)(0.8*R), current_circle_y - (int)(0.8*R) );
                  }
                     //sf::Time t2 = clock.restart();
                     ////performance[1] = (performance[1]*(cnt-1) + (float)t2.asMilliseconds() )/cnt;
                     // avg_(n+1) = (x_1+...+x_n)/(n+1) + x_(n+1) / (n+1) = (avg_n * n + x_(n+1)) / n+1

               }
               break;
            case sf::Event::Closed:
               _window.close();
               break;
            default:
               break;
         }
      }
   }

   else // First Person
   {
      //LOG("Entering FP Game Mode");

      //sf::Vector2i window_pos = _window.getPosition(); // Window position offset

      //sf::Vector2i window_center((int)(gameWidth/2) + window_pos.x, (int)(gameHeight/2) + window_pos.y); // Actual window center coordinates w.r.t. desktop

      LOG("");
      int dx, dy;

      sf::Vector2i window_pos = _window.getPosition();
      sf::Vector2i window_center((int)(gameWidth/2) + window_pos.x, (int)(gameHeight/2) + window_pos.y); // Actual window center coordinates w.r.t. desktop
      sf::Mouse::setPosition(window_center);

      LOG("Window position: " << window_pos.x << " " << window_pos.y);
      LOG("Window center: " << window_center.x << " " << window_center.y);
      LOG("Ball position: " << ball.getPosition().x << " " << ball.getPosition().y);

      while (_window.pollEvent(event))
      {
         switch (event.type)
         {
         case sf::Event::MouseMoved:
            LOG("Mouse x: " << sf::Mouse::getPosition(_window).x << " ; Mouse y (wrt window): " << sf::Mouse::getPosition(_window).x);
            LOG("Mouse x: " << sf::Mouse::getPosition().x << " ; Mouse y (abs): " << sf::Mouse::getPosition().x);
            dx = sf::Mouse::getPosition().x - window_center.x;
            dy = sf::Mouse::getPosition().y - window_center.y;

            LOG("dx: " << dx << " ; dy: " << dy);

            current_circle_x = current_circle_x - dx;
            current_circle_y = current_circle_y - dy;
            ball.setPosition(current_circle_x, current_circle_y); // Moving the ball in the opposite direction of mouse movement
            sf::Mouse::setPosition(window_center);
            break;

         case sf::Event::MouseButtonPressed:
            LOG("Detected mouse press");
            clicks++;
            if(event.mouseButton.button == sf::Mouse::Left)
            {
               LOG("Circle coords: " << current_circle_x << " " << current_circle_y);
               LOG("Click coords: " << event.mouseButton.x << " " << event.mouseButton.y);
               LOG((event.mouseButton.x - current_circle_x)*(event.mouseButton.x - current_circle_x) +
                   (event.mouseButton.y - current_circle_y)*(event.mouseButton.y - current_circle_y));
               LOG(R*R);

               if(clicked_within_circle(event.mouseButton.x,event.mouseButton.y))
               {
                  cnt++;
                  current_circle_x = rand()%(gameWidth-R);
                  current_circle_y = rand()%(gameHeight-R);
                  ball.setPosition(current_circle_x - (int)(0.8*R), current_circle_y - (int)(0.8*R) );
               }
                  //sf::Time t2 = clock.restart();
                  ////performance[1] = (performance[1]*(cnt-1) + (float)t2.asMilliseconds() )/cnt;
                  // avg_(n+1) = (x_1+...+x_n)/(n+1) + x_(n+1) / (n+1) = (avg_n * n + x_(n+1)) / n+1

            }
            break;
         case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter)
               {_window.close();}
            break;
         case (sf::Event::Closed):
            _window.close();
            break;
         default:
            break;
         }
      }
   }
}

void Game::_render()
{
   //LOG(current_circle_x << " " << current_circle_y);
}

bool Game::clicked_within_circle(int x_clicked, int y_clicked)
{
   LOG("Checking distance to center");
   if((x_clicked - current_circle_x)*(x_clicked - current_circle_x) +
      (y_clicked - current_circle_y)*(y_clicked - current_circle_y) <= R*R)
   {
      LOG("Correct !");
      return(true);
   }
   return(false);
}

Game::~Game(){}
