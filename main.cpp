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

      quit=game.nexturn();

  }
  cout<<"CONGRATULATIONS PLAYER "<< game.topship()->player<<" WINS!!"<<endl;
  return 0;
}
