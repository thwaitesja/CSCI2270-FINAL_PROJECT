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
  game.showall();
  return 0;
}
