
#include "battleship.hpp"



    Battleship::Battleship(int players){
      srand (time(NULL));
      playerNum=players;
      *turn=PriorityQueue(2*players);
      int playerorder[players];
      order(playerorder);
      ship= new ships[2*players];
      for(int i=0; i<2*players; i++){
        if(i%2==0){
          ship[i].bship=1;
          ship[i].size=8;
          ship[i].player=(i+1)/2;
          ship[i].strength=8;
          ship[i].turnstatus=playerorder[(i+1)/2]*2+1;
        }
        else{
          ship[i].bship=0;
          ship[i].size=10;
          ship[i].player=(i+1)/2;
          ship[i].strength=10;
          ship[i].turnstatus=playerorder[(i+1)/2]*2;
        }
      }
      setboard();

      }
    Battleship::~Battleship(){
      delete [] ship;
      delete [] board;
    }
    void Battleship::showall(){
      area a;
      a.ir=0;
      a.ic=0;
      a.er=scale*playerNum;
      a.ec=scale*playerNum;
      printboard(a);
    }
    void Battleship::printboard(area a){
      for(int i=a.ir; i!=a.er+1; (i++)%(scale*playerNum)){
        for(int j=a.ic; j!=a.ec+1; (j++)%(scale*playerNum)){
          if(board[j]==0) cout<<"*";
          else if(board[j][i]==0) cout<<"*";
          else cout<<board[j][i]->player;
        }
        cout<< endl;
      }
    }
    void Battleship::addship(ships *boat, area r){}
    void Battleship::damage(ships *boat, int damage){}
    void Battleship::removeship(ships *boat){}
    bool Battleship::shipcollide(area r){}
    int Battleship::moveship(ships *boat, area iregion, area oregion ){}
    bool Battleship::attack(area a){}
    void Battleship::peek(area a){}
    ships* Battleship::lookup(){}
    void Battleship::setboard(){
      board=new ships**[((14)*playerNum)];
      for(int i=0; i<((14)*playerNum);i++) board[i]=0;
      int position, height;
      area boat;
      bool taken[((2)*playerNum)];
      for(int j=0; j<2*playerNum; j++) taken[j]=0;
      for(int k=0; k<playerNum; k++){
        do{
          position=rand()%(2*playerNum);
        }while(taken[position]);
        taken[position]=1;//randomly find each players horizontal position on the board
        height=rand()%(14*playerNum);
        boat.ir=height;
        boat.ic=(position+2)%((14)*playerNum);
        boat.er=((height+1-ship[2*k].size/2))%((14)*playerNum);
        boat.ec=(position+1)%((14)*playerNum);
        setboat(boat, &ship[2*k]);

        boat.ir=height;
        boat.ic=(((14)*playerNum) +position-2)%((14)*playerNum);
        boat.er=((height+1-ship[2*k+1].size/2))%((14)*playerNum);
        boat.ec=(((14)*playerNum) +position-1)%((14)*playerNum);
        setboat(boat, &ship[2*k+1]);
      }
    }
    void Battleship::setboat(area a, ships *boat){
      createboard(a.ic);
      createboard(a.ec);
      for(int i=a.ir; i!=a.er+1; (i++)%((scale)*playerNum)){
          board[a.ic][i]=boat;
          board[a.ic][i]=boat;
      }
    }
    void Battleship::order(int order[]){
      for(int i=0; i<playerNum; i++){
        order[i]=-1;
      }
      for(int j=0; j<playerNum; j++){
        while(order[j]==-1){
          order[j]=rand()%playerNum;
          for(int k=0; k<j; k++){
            if(order[j]==order[k]) order[j]=-1;
          }
        }
      }

    }
    void Battleship::createboard(int segment){
        if(isEmptySegment(segment)){
            board[segment]=new ships*[((14)*playerNum)];
            for(int i=0; i<((14)*playerNum);i++) board[segment][i]=0;
        }
    }
    bool Battleship::isEmptySegment(int segment){
      return board[segment]==0;
    }



    PriorityQueue::PriorityQueue(int queueSize){
            priorityQueue= new ships*[queueSize];
            maxQueueSize=queueSize;
            currentQueueSize=0;
      }
    PriorityQueue::~PriorityQueue(){
        delete [] priorityQueue;
    }
    void PriorityQueue::enqueue (ships* a){
      if(isFull()){
        cout << "Heap full, cannot enqueue" << endl;
      }
      else{
        swap2(priorityQueue[currentQueueSize],a);
        repairUpward(currentQueueSize);
        currentQueueSize++;
      }
    }
    void PriorityQueue::dequeue(){
      if(isEmpty()){
        cout << "Heap empty, cannot dequeue" << endl;
      }
      else{
        currentQueueSize--;
        priorityQueue[0]=priorityQueue[currentQueueSize];
        priorityQueue[currentQueueSize]=0;
        repairDownward(0);
      }
    }
    ships* PriorityQueue::peek(){
        return priorityQueue[0];
    }
    bool PriorityQueue::isFull(){
      return currentQueueSize == maxQueueSize;
    }
    bool PriorityQueue::isEmpty(){
      return currentQueueSize == 0;
    }
    void PriorityQueue::lowerpriority(){
        for(int i=0; i<currentQueueSize; i++){
          priorityQueue[i]->turnstatus--;
        }
      }
    void PriorityQueue::swap2(ships* &a, ships* &b){
        ships* c=a;
        a=b;
        b=c;
      }
    void PriorityQueue::repairUpward(int nodeIndex){
      int p=(nodeIndex-1)/2;
      if(p<0 || nodeIndex==0){
        return;
      }
      else{
        if(priorityQueue[nodeIndex]->turnstatus < priorityQueue[p]->turnstatus){
          swap2(priorityQueue[nodeIndex], priorityQueue[p]);
          repairUpward(p);
        }
        else{
          return;
        }
      }
    }
    void PriorityQueue::repairDownward(int nodeIndex){
      int c1=(nodeIndex*2)+1;
      int c2=(nodeIndex*2)+2;
      int sm=nodeIndex;
      if(c1<=currentQueueSize-1){
        if(priorityQueue[c1]->turnstatus < priorityQueue[sm]->turnstatus ){
            sm=c1;
          }
      }
      if(c2<=currentQueueSize-1){
        if(priorityQueue[c2]->turnstatus < priorityQueue[sm]->turnstatus ){
            sm=c2;
          }
      }
      if(nodeIndex!=sm){
        swap2(priorityQueue[nodeIndex], priorityQueue[sm]);
        repairDownward(sm);
      }
    }
