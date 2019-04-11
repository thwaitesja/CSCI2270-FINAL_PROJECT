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
  int x,y;
  while(x!=-1){
    game.showall();
    cout<<"x:";
    cin>>x;
    cout<<"y:";
    cin>>y;
    a.ic=x-1;
    a.ec=x+1;
    a.ir=y-1;
    a.er=y+1;
    game.attack(a);
    game.attack(a);
  }
  return 0;
}
