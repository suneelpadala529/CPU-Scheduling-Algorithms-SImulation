#include<iostream>
#include <random>
#include<algorithm>
#include<cmath>
#include <queue>
using namespace std;


struct PCBQ
{
    int pid;  // Process ID
    int bt;   // CPU Burst time required
    int waitingtime;    //waiting time for the processes
    int tat;            //turn around time of processes
    int arrtime;        //arrival time of processes
    int totbt;          //original burst time;
    int restime;        //response time
};

class cqueue
{
    private:
        int length;
        PCBQ* cq;
        int frnt;
        int rear;
    public:
        void init(int n);
        void enqueue(PCBQ pcbq);
        void dequeue();
        void display();
        bool isempty();
        int returnfront();
        PCBQ* returnqueue();

};


void cqueue::init(int n)
{
    length= n;
    cq= new PCBQ[n];
    frnt=rear=-1;
}

void cqueue::enqueue(PCBQ pcbq)
{
    if(rear==-1)
    {
        frnt=rear=0;
        cq[rear]=pcbq;
    }
    else if((rear+1)%length==frnt)
    {
        cout<<"\nQueue is full.";
    }
    else
    {
        rear= ++rear % length;
        cq[rear]=pcbq;
    }
}

void cqueue::dequeue()
{
    if(frnt== rear)
    {
        frnt=rear=-1;
    }
    else
    {
        frnt= (++frnt)%length;
    }
}

void cqueue::display()
{
    if(frnt==-1)
    {
        cout<<"\nQueue is empty";
        return;
    }
    int test=frnt;
    do{
        //cout<<"\nfront="<<frnt<<" rear="<<rear<<"test="<<test;
        cout <<"\n("<<cq[test].pid<<","<<cq[test].bt<<")";
        test= ++test%length;
    }while(test!=(rear+1)%length);
}

bool cqueue::isempty()
{
    if(rear==-1)
        return true;
    return false;
}

int cqueue::returnfront()
{
    return frnt;;
}

PCBQ* cqueue::returnqueue()
{
    return cq;
}
