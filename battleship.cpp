
#include "battleship.hpp"



    Battleship::Battleship(int players){
      scale=14*players;
      srand(time(NULL));
      playerNum=players;
      turn= new PriorityQueue(2*players);
      int playerorder[players];
      order(playerorder);
      ship= new ships[2*players];
      for(int i=0; i<2*players; i++){
        if(i%2==0){
          ship[i].bship=1;
          ship[i].player=(i+2)/2;
          ship[i].strength=16;
          ship[i].turnstatus=playerorder[(i)/2]*2+1;
          ship[i].out=0;
          ship[i].action[0]=0;
          turn->enqueue(&ship[i]);
        }
        else{
          ship[i].bship=0;
          ship[i].player=(i+2)/2;
          ship[i].strength=20;
          ship[i].turnstatus=playerorder[(i)/2]*2;
          ship[i].out=0;
          ship[i].action[0]=0;
          turn->enqueue(&ship[i]);
        }

      }
      //initializes the player boats ad order
      setboard();
      //calls the board setup
      }
      //battleship constructor
    Battleship::~Battleship(){
      delete [] ship;
      for(int i=0; i<scale; i++){
        if(!isEmptySegment(i)) delete [] board[i];
      }
      delete [] board;
      delete turn;
      //deletes the data structures
    }
    //battleship destructor
    ships* Battleship::topship(){
      return turn->peek();
    }
    //returns the top ship from the queue
    bool Battleship::nexturn(){
      ships* p = turn->peek();
      int mode, x, y;
      string null;
      area a;
      bool orientation, quit=1;
      for(int i=0; i<50; i++) cout<<endl;//enters for privacy
      cout<<"Player"<<p->player<<"'s ";
      if(p->bship)cout<<"battleship's turn";
      else cout<<"aircraft carrier's turn";
      cout<<endl<<endl<<"press any key and then enter";
      cin>> null;
      //displays the header for the player then waits for any input
      for(int i=0; i<50; i++) cout<<endl;
      switch(p->action[0]){
        case 0:
        break;
        case 1:
          a.ic=(p->action[1]+scale-1)%(scale);
          a.ec=(p->action[1]+1)%(scale);
          a.ir=(p->action[2]+scale-1)%(scale);
          a.er=(p->action[2]+1)%(scale);

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
      //does the action from the previous move
      if(turn->oneplayer()){
          return 0;
      }
      //makes sure there are more than one player playing after the actions
      turn->dequeue();

      //prints the board from the boat's perspective
      printboard(p);
      //  showall();//shows the whole structure
      cout<<"___________________________________________________"<<endl;
      cout<< "O is current ship, o is your 2nd ship, ? is unknown enemy"<< endl;
      cout<<endl<<"attack 3x3 area: Delay = 9*(rows+collumns) press 1"<<endl;
      cout<<"move ship: Delay = size*(rows+collumns) press 2"<<endl;
      cout<<"quit: press 3"<<endl;
      cin>>mode;
      //menu for next turn
      p->action[0]=mode;
      //set next action
      switch(mode){
          case 0:
            //p->turnstatus=10000;//used for debugging makes it so a player no longer has turns
          break;
          case 1:
            cout<< "center point"<<endl;
            cout<<"x:";
            cin>>x;
            p->action[1]=(p->location.ic+scale+x)%scale;
            cout<<"y:";
            cin>>y;
            p->action[2]=(p->location.ir+scale+y)%scale;
            p->turnstatus=(abs(x)+abs(y))*9;
            //sets up the attack and then computes the wait time
          break;
          case 2:
            cout<< "Enter top left x, y coordinate, then the orientation of the ship"<<endl;
            cout<<" If the place of movement is/ becomes blocked, the move won't happen"<<endl;
            cout<<"top left x value: ";
            cin>>x;
            p->action[1]=(p->location.ic+scale+x)%scale;
            cout<<"top left y value: ";
            cin>>y;
            p->action[2]=(p->location.ir+scale+y)%scale;
            cout<<"vertical type 1, horizontal type 0: ";
            cin>>p->action[3];
            p->action[3]=p->action[3]%2;//ensures a 1 or 0
            if(p->bship) p->turnstatus=(abs(x)+abs(y))*16;
            else p->turnstatus=(abs(x)+abs(y))*20;
            //sets up for moving then sets delay
          break;
          case 3:
            quit=0;
          break;
        }
      turn->enqueue(p);
      stepday();
      return quit;
      // puts the ship back on the queue goes to the next boat and returns 1 if game continues
    }
    //iterates through one turn
    void Battleship::showall(){
      cout<<"   ";
      for(int k=0; k<scale; k++) cout<<" "<<k/10;
      cout<< endl<<"   ";
      for(int k=0; k<scale; k++) cout<<" "<<k%10;
      cout<< endl;
      for(int i=0; i<scale; i++){
        cout<<i/10<< i%10<<" ";
        for(int j=0; j<scale; j++){
          if(board[j]==0) cout<<"  ";
          else if(board[j][i]==0) cout<<"  ";
          else cout<<" "<<board[j][i]->player;
        }
        cout<< endl;
      }
    }
    //shows the entire board for demo and debugging
    void Battleship::printboard(ships* boat){
      int x=boat->location.ic;
      int y=boat->location.ir;
      int xstart=(scale/2+x)%scale;
      int ystart=(scale/2+y)%scale;
      //this sets up how much the board will need to be shifted.
      cout<<"    ";
      for(int k=-scale/2; k<scale/2; k++){
        if(k<0)cout<<" -";
        else cout<<"  ";
      }
      cout<< endl<<"    ";
      for(int k=-scale/2; k<scale/2; k++){
        if(k<0)cout<<" "<<-k/10;
        else cout<<" "<<k/10;
      }
      cout<< endl<<"    ";
      for(int k=-scale/2; k<scale/2; k++){
        if(k<0)cout<<" "<< -k%10;
        else cout<<" "<< k%10;
      }
      cout<< endl;
      //above is for printing outer numbers
      //the for loops loop from 0 to scale, but by adding the start variable and moduloing
      //this prints with the active ship in the middle
      for(int i=0; i<scale; i++){//this is printing the y coordinates
        int shiftedi= i-scale/2;
        int newi= (i+ystart)%scale;
        if(shiftedi<0)cout<<"-"<<-shiftedi/10<< -shiftedi%10<<" ";
        else cout<<" "<<shiftedi/10<< shiftedi%10<<" ";
        for(int j=0; j<scale; j++){//this is printing the x coordinates
          int newj= (j+xstart)%scale;
          if(board[newj]==0) cout<<"  ";
          else if(board[newj][newi]==0) cout<<"  ";
          else if(board[newj][newi]==boat) cout<<"O"<<"O";
          else if(board[newj][newi]->player==boat->player) cout<<" "<<"o";
          else cout<<" "<<"?";
        }
        cout<< endl;
      }
    }
    //prints the specified area
    void Battleship::removeship(ships *boat){
      boat->out=1;
      unsetboat(boat->location);
      //flags the boat for the priority queue and calls the unsetting function
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
    //states 1 if a ship is in the area specified
    bool Battleship::attack(area a){
      ships* h=0;
      for(int i=a.ir; i!=(a.er+1)%(scale); i=(i+1)%(scale)){
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
      //looks up ships in the area and each time it removes one health
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
    //returns the pointer at a specified location on the hash table otherwise 0
    void Battleship::setboard(){
      board=new ships**[scale];
      for(int i=0; i<scale;i++) board[i]=0;
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
        height=rand()%(scale);
        boat.ir=height;
        boat.ic=(position+1)%(scale);
        boat.er=(height+7)%(scale);
        boat.ec=(position+2)%(scale);
        setboat(boat, &ship[2*k]);
        //each player's battleship
        boat.ir=height;
        boat.ic=((scale) +position-2)%(scale);
        boat.er=(height+9)%(scale);
        boat.ec=((scale) +position-1)%(scale);
        setboat(boat, &ship[2*k+1]);
        //each players aircraft carrier
      }
    }
    //randomly sets up the board with the boats in a random location
    void Battleship::setboat(area a, ships *boat){
      for(int j=a.ic; j!=(a.ec+1)%(scale); j=(j+1)%(scale)){
        if(isEmptySegment(j))createboard(j);
        for(int i=a.ir; i!=(a.er+1)%(scale); i=(i+1)%(scale)){
            board[j][i]=boat;
        }
      }
      boat->location=a;
    }
    //puts the boat back on the board in the specified area
    void Battleship::unsetboat(area a){
    for(int i=a.ir; i!=(a.er+1)%(scale); i=(i+1)%(scale)){
      for(int j=a.ic; j!=(a.ec+1)%(scale); j=(j+1)%(scale)){
          board[j][i]=0;
        }
      }
      //sets every pointer in the area to 0
      for(int k=a.ic; k<=a.ec; k++){
        if(isEmptyArray(k)){
          delete [] board[k];
          board[k]=0;
        }
      }
      //checks the collumns in the specified area if they are all null, the array is deleted
    }
    //removes boat from specified area
    void Battleship::order(int order[]){
      for(int i=0; i<playerNum; i++){
        order[i]=-1;
      }
      //initializes to -1
      for(int j=0; j<playerNum; j++){
        while(order[j]==-1){
          order[j]=rand()%(playerNum);
          for(int k=0; k<j; k++){
            if(order[j]==order[k]) order[j]=-1;
          }
        }
      }
      //uses a while loop to randomly pick numbers until it finds a unpicked number and puts it in the order
    }
    //generates random order
    void Battleship::createboard(int segment){
        if(isEmptySegment(segment)){
            board[segment]=new ships*[scale];
            for(int i=0; i<(scale);i++) board[segment][i]=0;
        }
    }
    //called to generate board for a collumn if the board is not allready generated
    bool Battleship::isEmptySegment(int segment){
      return board[segment]==0;
    }
     //checks if the pointer to an array is null
    bool Battleship::isEmptyArray(int segment){
      bool empty=1;
      for(int i=0; i<scale ;i++){
        if(board[segment][i]!=0) empty=0;
      }
      return empty;
    }
    //checks if an array is full of 0 pointers
    void Battleship::shipRelocation(int number, bool bship, int x, int y, bool orientation ){
      area a;
      ships* ship;
      a.ic=x;
      a.ir=y;
      int i=2*(number-1);
      if(orientation){
        if(bship){
          a.ec=(x+1)%(scale);
          a.er=(y+7)%(scale);
        }
        else{
          i++;
          a.ec=(x+1)%(scale);
          a.er=(y+9)%(scale);
        }
      }
      else{
        if(bship){
          a.ec=(x+7)%(scale);
          a.er=(y+1)%(scale);
        }
        else{
          i++;
          a.ec=(x+9)%(scale);
          a.er=(y+1)%(scale);
        }
      }
      //generates an area based on the parameters
      ship=getship(i);
      unsetboat(ship->location);
      //takes out the boat
      if(!shipcollide(a)) setboat(a, ship);
      else setboat(ship->location, ship);
      //if the desired location of moving is empty it sets the boat there, otherwise
      //it puts it back on the old location
    }
    //looks up a ship and moves it based on specifications and if there is no collision
//_______________________________________________________________________________________________


    PriorityQueue::PriorityQueue(int queueSize){
            priorityQueue= new ships*[queueSize];

            maxQueueSize=queueSize;
            currentQueueSize=0;
      }
    //standard priorityQueue constructor
    PriorityQueue::~PriorityQueue(){
        delete [] priorityQueue;
    }
    //standard priorityQueue destructor
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
    //standard priorityQueue enqueue
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
    //standard priorityQueue dequeue
    ships* PriorityQueue::peek(){
        while(priorityQueue[0]->out){
          dequeue();
        }
        return priorityQueue[0];
    }
    //standard priorityQueue outputing the top element
    bool PriorityQueue::oneplayer(){
      bool breakit=1;
      ships* a=peek();
      dequeue();
      while(priorityQueue[0]!=0&& breakit){
        if(priorityQueue[0]->out)  dequeue();
        else breakit=0;
      }
      breakit=1;
      if(isEmpty()){
        enqueue(a);
        return 1;
      }
      ships* b=peek();
      dequeue();
      while(priorityQueue[0]!=0&& breakit){
        if(priorityQueue[0]->out)  dequeue();
        else breakit=0;
      }
      if(!isEmpty()){
        enqueue(a);
        enqueue(b);
        return 0;
      }//check to make sure the third+ elements aren't eliminated
      enqueue(a);
      enqueue(b);//puts back in the first two elements
      if(priorityQueue[1]==0)return 1;//1 ship left
      else if(priorityQueue[1]->player==priorityQueue[0]->player) return 1;//2 ships of same player
      else return 0;//2 different ships
    }
    //This function checks to see if there is only one player left by looking
    //at the first 3 elements
    bool PriorityQueue::isFull(){
      return currentQueueSize == maxQueueSize;
    }
    //1 if full
    bool PriorityQueue::isEmpty(){
      return currentQueueSize == 0;
    }
    //1 if empty
    void PriorityQueue::lowerpriority(){
        for(int i=0; i<currentQueueSize; i++){
          priorityQueue[i]->turnstatus--;
        }
      }
    //iterates through the entire queue and lowers the priority by 1
    void PriorityQueue::swap2(ships* &a, ships* &b){
        ships* c=a;
        a=b;
        b=c;
      }
    // swaps 2 elements
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
    //repairs towards the root node
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
    //repairs away from the first node
