#include<iostream>
#include<fstream>
#include<sstream>
#include<string>



using namespace std;

void swap2(ships* &a, ships* &b){
    ships c=a;
    a=b;
    b=c;
  }


    class PriorityQueue
    {
        public:
        PriorityQueue(int queueSize){
                priorityQueue= new ships*[queueSize];
                maxQueueSize=queueSize;
                currentQueueSize=0;
          }
        ~PriorityQueue(){
            delete [] priorityQueue;
        }
        void enqueue (ships* a){
          if(isFull()){
            cout << "Heap full, cannot enqueue" << endl;
          }
          else{
            swap2(priorityQueue[currentQueueSize],a);
            repairUpward(currentQueueSize);
            currentQueueSize++;
          }
        }
        void dequeue(){
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
        ships* peek(){
            return priorityQueue[0];
        }
        bool isFull(){
          return currentQueueSize == maxQueueSize;
        }
        bool isEmpty(){
          return currentQueueSize == 0;
        }
        private:
        //Purpose: maintain heap properties by swapping node with parent if necessary
        void repairUpward(int nodeIndex){
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
        void repairDownward(int nodeIndex)repairDownward(int nodeIndex){
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

        GroupNode* priorityQueue; //pointer to the array used to implement priority queue
        int currentQueueSize; //number of group currently in the priority queue
        int maxQueueSize; //maximum capacity of priority queue
    };
