#ifndef BATTLESHIP
#define BATTLESHIP

#include <string>

#include <vector>
#include <queue>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cmath>

using namespace std;

struct area{
  int ir;
  int ic;
  int er;
  int ec;
//specifies area on the board by top left and bottom right corners
};

struct ships{
  int turnstatus;
  bool bship;
  //int size;
  int strength;
  int player;
  area location;
  bool out;
  int action[4];//[type of acion, x coordinate, y coordinate, orientation]

};


class PriorityQueue{
    public:
    PriorityQueue(int queueSize);
    ~PriorityQueue();
    bool oneplayer();
    void enqueue (ships* a);
    void dequeue();
    ships* peek();
    bool isFull();
    bool isEmpty();
    void lowerpriority();
    private:
    //Purpose: maintain heap properties by swapping node with parent if necessary
    void swap2(ships* &a, ships* &b);
    void repairUpward(int nodeIndex);
    void repairDownward(int nodeIndex);

    ships** priorityQueue; //pointer to the array used to implement priority queue
    int currentQueueSize; //number of group currently in the priority queue
    int maxQueueSize; //maximum capacity of priority queue
};




class Battleship {
  public:
    Battleship(int players);
    ~Battleship();
    ships* topship();
    bool nexturn();
    void showall();
    void printboard(area a);
    ships* getship(int i){return &ship[i];}
    void shipRelocation(int number, bool bship, int x, int y, bool orientation );
    void removeship(ships *boat);
    bool shipcollide(area a);
    bool attack(area a);
    void stepday();
    ships* lookup(int c, int r);

  private:
    /* member functions */
    void setboard();
    void setboat(area a, ships *boat);
    void unsetboat(area a);
    void order(int order[]);
    void createboard(int segment);
    bool isEmptySegment(int segment);
    bool isEmptyArray(int segment);

    PriorityQueue* turn;
    ships*** board;
    ships* ship;
    int playerNum;
    const int scale=14;
};



#endif
