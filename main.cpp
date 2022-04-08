#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include "Game.hpp"

std::istream& operator>> ( std::istream& in, gameMode& x )
{
  int val;

  if ( in>> val ) {
    switch ( val ) {
    case Static: case FirstPerson:
      x = gameMode(val); break;
    default:
      throw ( "Invalid value for type X" );
    }
  }

  return in;
}

int main()
{
   while(true)
   {
      // Next: Choix taille cible, nb cibles, taille fenêtre, modes de jeu
      Game game;

      std::cout << "Game Mode ?\n 0 = Static\n 1 = First Person" << std::endl;
      std::cin >> game.gm;

      LOG("OK");

      std::cout << "\n\n";

      LOG("Starting game...");
      game.start();

      std::cout << "\nYour performance:\n Total time for " << game.n_circles << " hits : "<< (float)game.performance[0]/1000 << " s" << std::endl;
      std::cout << " Average time between hits: " << game.performance[0]/(1000*game.n_circles) << " s" << std::endl;
      std::cout << " Accuracy: " << 100*(float)game.n_circles/(float)game.clicks << " %" << std::endl;
      std::cout << "\nPress enter to start a new game...";
      std::cin.ignore(1000,'\n');
      std::cin.clear();
      std::cin.get();

      //delete game;
   }

   return(0);
}
