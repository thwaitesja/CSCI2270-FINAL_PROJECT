
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
          //ship[i].size=16;
          ship[i].player=(i+2)/2;
          ship[i].strength=16;
          ship[i].turnstatus=playerorder[(i)/2]*2+1;
          ship[i].out=0;
          ship[i].action[0]=0;
          turn->enqueue(&ship[i]);
        }
        else{
          ship[i].bship=0;
          //ship[i].size=20;
          ship[i].player=(i+2)/2;
          ship[i].strength=20;
          ship[i].turnstatus=playerorder[(i)/2]*2;
          ship[i].out=0;
          ship[i].action[0]=0;
          turn->enqueue(&ship[i]);
        }

      }
      setboard();

      }
      //battleship destructor
    Battleship::~Battleship(){
      delete [] ship;
      for(int i=0; i<playerNum*scale; i++){
        if(!isEmptySegment(i)) delete [] board[i];
      }
      delete [] board;
      delete turn;
    }
    //battleship constructor
    ships* Battleship::topship(){
      return turn->peek();
    }
    //returns the top ship from the queue
    bool Battleship::nexturn(){
      ships* p = turn->peek();
      int mode, x, y;
      area a;
      bool orientation, quit=1;
      if(turn->oneplayer()){
        return 0;
      }
      turn->dequeue();


      switch(p->action[0]){
        case 0:
        break;
        case 1:
        a.ic=p->action[1];
        a.ec=(p->action[1]+2)%(playerNum*scale);
        a.ir=p->action[2];
        a.er=(p->action[2]+2)%(playerNum*scale);

        attack(a);
        attack(a);
        attack(a);
        attack(a);
        break;
        case 2:
        shipRelocation(p->player, p->bship,  p->action[1], p->action[2], p->action[3]);
        break;
        case 3:
        quit=0;
        break;
      }
        showall();
        cout<<"_________________________________________________"<<endl;
        cout<<"Player"<<p->player<<"'s ";
        if(p->bship)cout<<"battleship's turn";
        else cout<<"aircraft carrier's turn";
        cout<<endl<<"attack:1"<<endl;
        cout<<"move ship:2"<<endl;
        cout<<"quit: 3"<<endl;
        cin>>mode;
        p->action[0]=mode;
        switch(mode){
          case 0:
          break;
          case 1:
          cout<<"x left:";
          cin>>p->action[1];
          cout<<"y top:";
          cin>>p->action[2];
          p->turnstatus=40;
          break;
          case 2:
          cout<<"top left point x";
          cin>>p->action[1];
          cout<<"top left point y";
          cin>>p->action[2];
          cout<<"vertical 1, horizontal 0";
          cin>>p->action[3];
          p->action[3]=p->action[3]%2;//ensures a 1 or 0
          p->turnstatus=80;
          break;
          case 3:
          quit=0;
          break;
        }
      turn->enqueue(p);
      stepday();
      return quit;
    }
    //iterates through one turn
    void Battleship::showall(){
      cout<<"   ";
      for(int k=0; k<scale*playerNum; k++) cout<<" "<<k/10;
      cout<< endl<<"   ";
      for(int k=0; k<scale*playerNum; k++) cout<<" "<<k%10;
      cout<< endl;
      for(int i=0; i<scale*playerNum; i++){
        cout<<i/10<< i%10<<" ";
        for(int j=0; j<scale*playerNum; j++){
          if(board[j]==0) cout<<"  ";
          else if(board[j][i]==0) cout<<"  ";
          else cout<<" "<<board[j][i]->player;
        }
        cout<< endl;
      }
    }
    //shows the entire board for demo and debugging
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
    //prints the specified area
    void Battleship::removeship(ships *boat){
      boat->out=1;
      unsetboat(boat->location);

    }
    //unsets the ship being pointed to
    bool Battleship::shipcollide(area a){
      bool sum=0;
      ships* h;
      for(int i=a.ir; i<=a.er; i++){
        for(int j=a.ic; j<=a.ec; j++){
          h=lookup(j, i);
          if(h!=0){
            sum=1;
          }
        }
      }
      return sum;
    }
    //states if a ship is in the area specified
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
    //attacks an area and deducts 1 health to every pointer in the area
    void Battleship::stepday(){
      int count=0;
      while(turn->peek()->turnstatus!=0){
          turn->lowerpriority();
          count++;
      }
      cout<<count<<" hours have passed"<< endl;
    }
    //calls priorityQueue.lowerpriority() until the front node is at 0
    ships* Battleship::lookup(int c, int r){
      if(isEmptySegment(c))return 0;
      else return board[c][r];
    }
    //returns the pointer at a specified location on the hash table
    void Battleship::setboard(){
      board=new ships**[(scale*playerNum)];
      for(int i=0; i<(scale*playerNum);i++) board[i]=0;
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
        boat.ic=(position+1)%((scale)*playerNum);
        boat.er=(height+7)%((scale)*playerNum);
        boat.ec=(position+2)%((14)*playerNum);
        setboat(boat, &ship[2*k]);

        boat.ir=height;
        boat.ic=(((scale)*playerNum) +position-2)%((scale)*playerNum);
        boat.er=(height+9)%((scale)*playerNum);
        boat.ec=(((scale)*playerNum) +position-1)%((scale)*playerNum);
        setboat(boat, &ship[2*k+1]);
      }
    }
    //randomly sets up the board
    void Battleship::setboat(area a, ships *boat){

    //  cout<< "hi";


      for(int j=a.ic; j!=(a.ec+1)%((scale)*playerNum); j=(j+1)%((scale)*playerNum)){
        if(isEmptySegment(j))createboard(j);
        for(int i=a.ir; i!=(a.er+1)%((scale)*playerNum); i=(i+1)%((scale)*playerNum)){
            board[j][i]=boat;
        }
      }
      boat->location=a;
    }
    //puts the boat back on the board in an area
    void Battleship::unsetboat(area a){
    for(int i=a.ir; i!=(a.er+1)%((scale)*playerNum); i=(i+1)%((scale)*playerNum)){
      for(int j=a.ic; j!=(a.ec+1)%((scale)*playerNum); j=(j+1)%((scale)*playerNum)){
          board[j][i]=0;
          //cout<<j<<" "<< i<< endl;
        }
      }
    //  cout<<"("<< a.ic<<","<< a.ir<<")"<< "   "<<"("<< a.ec<<","<< a.er<<")";
      for(int k=a.ic; k<=a.ec; k++){
        if(isEmptyArray(k)){
          delete [] board[k];
          board[k]=0;
        }
      }
    }
    //removes boat from specified area
    void Battleship::order(int order[]){
      for(int i=0; i<playerNum; i++){
        order[i]=-1;
      }
      for(int j=0; j<playerNum; j++){
        while(order[j]==-1){
          order[j]=rand()%(playerNum);
          for(int k=0; k<j; k++){
            if(order[j]==order[k]) order[j]=-1;
          }
        }
      }

    }
    //generates random order
    void Battleship::createboard(int segment){
        if(isEmptySegment(segment)){
            board[segment]=new ships*[((14)*playerNum)];
            for(int i=0; i<((14)*playerNum);i++) board[segment][i]=0;
        }
    }
    //called to generate board
    bool Battleship::isEmptySegment(int segment){
      return board[segment]==0;
    }
     //checks if the pointer to an array is null
    bool Battleship::isEmptyArray(int segment){
      bool empty=1;
      for(int i=0; i<playerNum*scale ;i++){
        if(board[segment][i]!=0) empty=0;
      }
      return empty;
    }
    //checks if an array is empty
    void Battleship::shipRelocation(int number, bool bship, int x, int y, bool orientation ){
      area a;
      ships* ship;
      a.ic=x;
      a.ir=y;
      int i=2*(number-1);
      if(orientation){
        if(bship){
          a.ec=(x+1)%((scale)*playerNum);
          a.er=(y+7)%((scale)*playerNum);
        }
        else{
          i++;
          a.ec=(x+1)%((scale)*playerNum);
          a.er=(y+9)%((scale)*playerNum);
        }
      }
      else{
        if(bship){
          a.ec=(x+7)%((scale)*playerNum);
          a.er=(y+1)%((scale)*playerNum);
        }
        else{
          i++;
          a.ec=(x+9)%((scale)*playerNum);
          a.er=(y+1)%((scale)*playerNum);
        }
      }
      ship=getship(i);
      unsetboat(ship->location);
      setboat(a, ship);
    }
    //looks up a ship and moves it based on specifications
//_______________________________________________________________________________________________


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
        while(priorityQueue[0]->out){
          dequeue();
        }
        return priorityQueue[0];
    }
    bool PriorityQueue::oneplayer(){
      if(maxQueueSize==2) return 1; //if only one person is playing
      if(priorityQueue[2]!=0) return 0;//3+ ships left
      else if(priorityQueue[1]==0)return 1;//1 ship left
      else if(priorityQueue[1]->player==priorityQueue[0]->player) return 1;//2 ships of same player
      else return 0;//2 different ships
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
