#include <vector>
#include <queue>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>

#include "battleship.hpp"



using namespace std;

int main(int argc, char* argv[]){
  int numb;
  cout<< "Enter the number of Players:";
  cin>>numb;
  Battleship game(numb);
  area a;
  int x,y,mode, n;
  bool quit=1, orientation, bship;
  while(quit){
    game.showall();
    cout<<"_________________________________________________"<<endl;
    cout<<"attack:1"<<endl;
    cout<<"move ship:2"<<endl;
    cout<<"quit: 3"<<endl;
    cin>>mode;
    switch(mode){
      case 1:
      cout<<"x:";
      cin>>x;
      cout<<"y:";
      cin>>y;
      a.ic=x;
      a.ec=x;
      a.ir=y;
      a.er=y;
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      game.attack(a);
      break;
      case 2:
      cout<<"ship number";
      cin>>n;
      cout<<"battleship 1, aircraft carrier 0";
      cin>>bship;
      cout<<"top left point x";
      cin>>x;
      cout<<"top left point y";
      cin>>y;
      cout<<"vertical 1, horizontal 0";
      cin>>orientation;
      game.shipRelocation(n, bship,  x, y, orientation);
      break;
      case 3:
      quit=0;
      break;
    }

  }
  return 0;
}
