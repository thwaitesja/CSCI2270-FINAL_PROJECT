#include <vector>
#include <queue>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>

struct ships{
  int turnstatus;
  bool bship;
  int size;
  int strength;
};

class Battleship {
  public:
    Battleship(int players){
      srand (time(NULL));
      ship= new ships[2*players];
      board=new ships*[((14)*players)^2];
      bool occupied[((14)*players)^2];
      }
    };
    ~Battleship(){
      delete [] ship;
      delete [] board;
    }

    void printboard(int region[]);
    void addship(ships *boat, int region[]);
    void damage(ships *boat, int damage);
    void removeship(ships *boat);
    bool shipcollide(int region[]);
    int moveship(ships *boat, int iregion[], int oregion[] );
    bool attack(int region[]);
    void peek(int region[]);


  private:
    /* member functions */
    void(int order[], int players){
      for(int i=0; i<players; i++){
        order[i]=-1;
      }
      for(int j=0; j<players; j++){
        while(order[i]==-1){
          order[i]=rand()%players;
          for(int k=0; k<j; k++){
            if(order[i]==order[k]) order[i]=-1;
          }
        }
      }

    }
    PriorityQueue turn;
    ships** board;
    ships** ship;
};//trying comment
