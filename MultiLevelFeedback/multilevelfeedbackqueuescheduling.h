#include "cqueue.h"

const int age=60;
const int age2=120;
const int timequanta=10;


struct PCB
{
    int pid;  // Process ID
    int bt;   // CPU Burst time required
    int priority; // Priority of this process
    int waitingtime;    //waiting time for the processes
    int tat;            //turn around time of processes
    int arrtime;        //arrival time of processes
    int totbt;          //original burst time
    int restime;        //response time
};


class multilevelqueuescheduling
{
public:
    int cputime;
    int limit;
    queue<PCB> readyqueue;
    queue<PCB> fcfs1;
    priority_queue <PCB> pq;
    queue <PCB> report;
    queue<PCB> fcfs2;
    void spawnprocess(int bt,int pid,int q);
    multilevelqueuescheduling();
    int* gaussiandistribution(int n, int mean, int stdev);
    void display(int j);
    void executeprocess(int t);
    void displaycputime();
    void printmap();
    void statistics();
     void executeageing1(int t);
     void executeageing2(int t);
};
