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

using namespace std;

struct ships{
  int turnstatus;
  bool bship;
  int size;
  int strength;
  int player;

};

struct area{
  int ir;
  int ic;
  int er;
  int ec;
//specifies area on the board by top left and bottom right corners
};


class PriorityQueue{
    public:
    PriorityQueue(int queueSize);
    ~PriorityQueue();
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
    void showall();
    void printboard(area a);
    void addship(ships *boat, area r);
    void damage(ships *boat, int damage);
    void removeship(ships *boat);
    bool shipcollide(area r);
    int moveship(ships *boat, area iregion, area oregion );
    bool attack(area a);
    void peek(area a);
    ships* lookup();

  private:
    /* member functions */
    void setboard();
    void setboat(area a, ships *boat);
    void order(int order[]);
    void createboard(int segment);
    bool isEmptySegment(int segment);

    PriorityQueue* turn;
    ships*** board;
    ships* ship;
    int playerNum;
    const int scale=14;
};



#endif
