

    Battleship::Battleship(int players){
      srand (time(NULL));
      playerNum=players;
      int order[players];
      order(order, players);
      ship= new ships[2*players];
      for(int i=0; i<2*players; i++){
        if(i%2==0){
          ship[i].bship=1;
          ship[i].size=8;
          ship[i].player=(i+1)/2;
          ship[i].strength=8;
          ship[i].turnstatus=order[(i+1)/2]*2+1;
        }
        else{
          ship[i].bship=0;
          ship[i].size=10;
          ship[i].player=(i+1)/2;
          ship[i].strength=10;
          ship[i].turnstatus=order[(i+1)/2]*2;
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
      a.or=scale*playerNum;
      a.oc=scale*playerNum;
      printboard(a);
    }
    void Battleship::printboard(area a){
      for(int i=a.ir; i!=a.or+1; (i++)%(scale*playerNum)){
        for(int j=a.ic; j!=a.oc+1; (j++)%(scale*playerNum)){
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
          position=rand()%(2*playerNum)
        }while(taken[position]);
        taken[position]=1;//randomly find each players horizontal position on the board
        height=rand()%(14*playerNum);
        boat.ir=height;
        boat.ic=(position+2)%((14)*playerNum);
        boat.or=((height+1-ship[2*k].size/2))%((14)*playerNum);
        boat.oc=(position+1)%((14)*playerNum);
        setboat(boat, &ship[2*k]);

        boat.ir=height;
        boat.ic=(((14)*playerNum) +position-2)%((14)*playerNum);
        boat.or=((height+1-ship[2*k+1].size/2))%((14)*playerNum);
        boat.oc=(((14)*playerNum) +position-1)%((14)*playerNum);
        setboat(boat, &ship[2*k+1]);
      }
    }
    void Battleship::setboat(area a, ships *boat){
      createboard(a.ic);
      createboard(a.oc);
      for(int i=a.ir; i!=a.or+1; (i++)%((scale)*playerNum)){
          board[a.ic][i]=boat;
          board[a.ic][i]=boat;
      }
    }
    void Battleship::order(int order[]){
      for(int i=0; i<playerNum; i++){
        order[i]=-1;
      }
      for(int j=0; j<playerNum; j++){
        while(order[i]==-1){
          order[i]=rand()%playerNum;
          for(int k=0; k<j; k++){
            if(order[i]==order[k]) order[i]=-1;
          }
        }
      }

    }
    void Battleship::createboard(int segment){
        if(isEmptySegment(segment)){
            board[segment]=new new ships*[((14)*playerNum)];
            for(int i=0; i<((14)*playerNum);i++) board[segment][i]=0;
        }
    }
    bool Battleship::isEmptySegment(int segment){
      return board[segment]==0;
    }
