
#include "battleship.hpp"



    Battleship::Battleship(int players){

      srand(time(NULL));
      playerNum=players;
      turn= new PriorityQueue(2*players);
      int playerorder[players];
      order(playerorder);
      ship= new ships[2*players];
      for(int i=0; i<2*players; i++){
        if(i%2==0){
          ship[i].bship=1;
          ship[i].size=16;
          ship[i].player=(i+2)/2;
          ship[i].strength=16;
          ship[i].turnstatus=playerorder[(i+1)/2]*2+1;
          ship[i].out=0;
        }
        else{
          ship[i].bship=0;
          ship[i].size=20;
          ship[i].player=(i+2)/2;
          ship[i].strength=20;
          ship[i].turnstatus=playerorder[(i+1)/2]*2;
          ship[i].out=0;
        }
      }
      setboard();

      }
    Battleship::~Battleship(){
      delete [] ship;
      for(int i=0; i<playerNum*scale; i++){
        if(!isEmptySegment(i)) delete [] board[i];
      }
      delete [] board;
      delete turn;
    }
    void Battleship::showall(){
      for(int i=0; i<scale*playerNum; i++){
        for(int j=0; j<scale*playerNum; j++){
          if(board[j]==0) cout<<" *";
          else if(board[j][i]==0) cout<<" *";
          else cout<<" "<<board[j][i]->player;
        }
        cout<< endl;
      }
    }
    void Battleship::printboard(area a){
      for(int i=a.ir; i!=(a.er+1)%(scale*playerNum); i=(i+1)%((scale)*playerNum)){
        for(int j=a.ic; j!=(a.ec+1)%(scale*playerNum); j=(j+1)%((scale)*playerNum)){
          if(board[j]==0) cout<<"*";
          else if(board[j][i]==0) cout<<"*";
          else cout<<board[j][i]->player;
        }
        cout<< endl;
      }
    }
    //void Battleship::addship(ships *boat, area r){}
    void Battleship::damage(ships *boat, int damage){}
    void Battleship::removeship(ships *boat){
      boat->out=1;
      unsetboat(boat->location);

    }
    bool Battleship::shipcollide(area r){}
    int Battleship::moveship(ships *boat, area iregion, area oregion ){}
    bool Battleship::attack(area a){
      ships* h=0;
      for(int i=a.ir; i<=a.er; i++){
        for(int j=a.ic; j<=a.ec; j++){
          h=lookup(j, i);
          if(h!=0){
            h->strength--;
            cout<<"Player"<<h->player<<"'s ";
            if(h->bship)cout<<"battleship was hit";
            else cout<<"aircraft carrier was hit";
            if(h->strength<=0){
              removeship(h);
              cout<<" sunk!"<<endl;
            }
            else  cout<<" and has "<< h->strength<<" health left"<<endl;
          }
        }
      }
    }
  //  void Battleship::peek(area a){}
    void Battleship::stepday(){
      turn->lowerpriority();
    }
    ships* Battleship::lookup(int c, int r){
      if(isEmptySegment(c))return 0;
      else return board[c][r];
    }
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
        taken[position]=1;
        position=position*7;
        //randomly find each players horizontal position on the board
        height=rand()%((scale)*playerNum);
        boat.ir=height;
        boat.ic=(position+2)%((scale)*playerNum);
        boat.er=(height+7)%((scale)*playerNum);
        boat.ec=(position+1)%((14)*playerNum);
        setboat(boat, &ship[2*k]);

        boat.ir=height;
        boat.ic=(((scale)*playerNum) +position-2)%((scale)*playerNum);
        boat.er=(height+9)%((scale)*playerNum);
        boat.ec=(((scale)*playerNum) +position-1)%((scale)*playerNum);
        setboat(boat, &ship[2*k+1]);
      }
    }
    void Battleship::setboat(area a, ships *boat){
      if(isEmptySegment(a.ic))createboard(a.ic);
      if(isEmptySegment(a.ec))createboard(a.ec);
      for(int i=a.ir; i!=(a.er+1)%((scale)*playerNum); i=(i+1)%((scale)*playerNum)){
          board[a.ic][i]=boat;
          board[a.ec][i]=boat;
      }
      boat->location=a;
    }
    void Battleship::unsetboat(area a){
    for(int i=a.ir; i!=(a.er+1)%((scale)*playerNum); i=(i+1)%((scale)*playerNum)){
      for(int j=a.ic; j!=(a.ec+1)%((scale)*playerNum); j=(j+1)%((scale)*playerNum)){
          board[j][i]=0;

        }
      }
      cout<<board[a.ic][ a.ir];
      for(int k=a.ic; k<=a.ec; k++){
        if(isEmptyArray(k)){
          delete [] board[k];
          board[k]=0;
        }
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
    bool Battleship::isEmptyArray(int segment){
      bool empty=1;
      for(int i=0; i<playerNum*scale ;i++){
        if(board[segment][i]!=0) empty=0;
      }
      return empty;
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
