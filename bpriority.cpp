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
