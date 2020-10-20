#include<iostream>
#include <random>
#include<algorithm>
#include<cmath>
#include <queue>
using namespace std;
const int age=20;

struct PCB
{
    int pid;  // Process ID
    int bt;   // CPU Burst time required
    int priority; // Priority of this process
    int waitingtime;    //waiting time for the process
    int tat;            //turnaround time for process
    int arrtime;        //arrival time for process
    int totbt;          //original burst time
    int restime;        //response time
};

class priorityscheduling
{
    private:
    int limit;                  //keeps track of time when ageing has to be applied
    float avgwaitingtime;
    public:
    int cputime;
    priority_queue <PCB> pq;
    queue <PCB> report;
    priorityscheduling();
    int* uniformdistribution(int n, int upper);
    void display();
    void spawnprocess(int burst, int prio, int id);
    void executeprocess(int t);
    void displaycputime();
    //void displaywaitingtime();
    priority_queue <PCB> executeageing();
    //priority_queue <PCB> waitingtime();
    void statistics();
    void printmap();
};

priorityscheduling::priorityscheduling()
{
    this->cputime=0;
    this->limit=age;
}

void priorityscheduling::printmap()
{
    cout<<"\nID\tARR\tBT\tWT\tTAT\tRT\n";
    cout<<"----------------------------------------------";
    queue <PCB> pqueue = this->report;
    while (!pqueue.empty())
    {
        cout <<"\n"<<pqueue.front().pid<<"\t"<<pqueue.front().arrtime<<"\t"<<pqueue.front().totbt<<"\t"<<pqueue.front().waitingtime;
        cout<<"\t"<<pqueue.front().tat<<"\t"<<pqueue.front().restime;
        pqueue.pop();
    }
    cout << '\n';

}

void priorityscheduling::statistics()
{
    queue <PCB> pqueue = this->report;
    int n= pqueue.size();
    PCB pcb;
    float stddevwt=0,stddevtat=0,stddevrt=0,avgwt=0,avgtat=0,avgrt=0;
    while (!pqueue.empty())
    {
        pcb= pqueue.front();
        avgtat+=pcb.tat;
        avgwt+= pcb.waitingtime;
        avgrt+=pcb.restime;
        pqueue.pop();
    }
    cout <<"\nAverage waiting time: "<<avgwt*1.0/n;
    cout<<"\nAverage turnaround time: "<<avgtat*1.0/n;
    cout<<"\nAverage response time: "<<avgrt*1.0/n;

    pqueue = this->report;
    while (!pqueue.empty())
    {
        pcb= pqueue.front();
        stddevwt+=pow((pcb.waitingtime-avgwt*1.0/n),2);
        stddevtat+=pow((pcb.tat-avgtat*1.0/n),2);
        stddevrt+=pow((pcb.restime-avgrt*1.0/n),2);
        pqueue.pop();
    }
    stddevwt= sqrt(stddevwt/n);
    stddevtat= sqrt(stddevtat/n);
    stddevrt= sqrt(stddevrt/n);
    cout<<"\nStandard Deviation of waiting time: "<<stddevwt;
    cout<<"\nStandard Deviation of turnaroud time: "<<stddevtat;
    cout<<"\nStandard Deviation of response time: "<<stddevrt;
}

/*priority_queue <PCB> priorityscheduling::waitingtime()
{
    priority_queue <PCB> test;
    PCB pcb;
    pcb=pq.top();
    int time= pcb.bt;
    pcb.waitingtime=0;
    pcb.tat= pcb.bt;
    pq.pop();
    test.push(pcb);
    while (!this->pq.empty())
    {
        pcb= pq.top();
        pcb.waitingtime=time;
        pcb.tat= pcb.waitingtime+pcb.bt;
        time+= pcb.bt;
        pq.pop();
        test.push(pcb);
    }
    return test;
}*/

priority_queue <PCB> priorityscheduling::executeageing()
{
    priority_queue <PCB> test;
    PCB pcb;
    int times=(((this->cputime-this->limit)%age)+this->limit)/age;      //denotes no of times priority has to be increased
    while (!this->pq.empty())
    {
        pcb= pq.top();
        pq.pop();
        if(this->cputime>=limit)
        {
            pcb.priority+= times;
        }
        test.push(pcb);
    }
    if(this->cputime>=limit)
        limit+=age;
    return test;

}

void priorityscheduling::displaycputime()
{
    cout<<"\nCurrent CPU time: "<<this->cputime;
}

void priorityscheduling::spawnprocess(int burst, int prio, int id)
{
    PCB p;
    p.bt= burst;
    p.pid=id;
    p.priority= prio;
    p.arrtime= this->cputime;
    p.totbt=burst;
    p.restime=-1;
    pq.push(p);
}

void priorityscheduling::executeprocess(int t)
{
    /*cout<<"\nProcess ID: "<<pq.top().pid<<", Priority: "<<pq.top().priority<<", Burst time: "<<pq.top().bt;
    this->limit=pq.top().bt;
    PCB pcb= pq.top();
    pcb.waitingtime=this->cputime-pcb.arrtime;
    pcb.tat= pcb.waitingtime+ pcb.bt;
    this->cputime+=pcb.bt;
    this->report.push(pcb);
    pq.pop();
    this->pq= this->executeageing();*/
    while(t>=pq.top().bt)
    {
        this->limit=pq.top().bt;
        PCB pcb= pq.top();
        if(pcb.restime<0)
            pcb.restime=this->cputime;
        pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
        pcb.tat= pcb.waitingtime+ pcb.totbt;
        this->cputime+=pcb.bt;
        t-=pcb.bt;
        pcb.bt=0;
        this->report.push(pcb);
        cout<<"\nProcess ID: "<<pcb.pid<<", Priority: "<<pcb.priority<<", original burst time: "<<pcb.totbt<<", Burst time left: "<<pcb.bt;
        pq.pop();
        if(!this->pq.empty())
        {
            this->pq= this->executeageing();
        }

    }
    if(t>0)
    {
        this->limit=t;
        PCB pcb= pq.top();
        if(pcb.restime<0)
            pcb.restime=this->cputime;
        pcb.bt-=t;
        this->cputime+=t;
        pq.pop();
        pq.push(pcb);
        cout<<"\nProcess ID: "<<pq.top().pid<<", Priority: "<<pq.top().priority<<", original burst time: "<<pq.top().totbt<<", Burst time left: "<<pq.top().bt;
        this->pq= this->executeageing();
    }

}

bool operator<( PCB p1, PCB p2)
{
    return p1.priority < p2.priority;
}

int* priorityscheduling::uniformdistribution(int n, int upper)
{
     const int range_from  = 1;
    const int range_to    = upper;
    std::random_device  rand_dev;
    std::mt19937    generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

     int* rv= new int[n];
     for(int i=0;i<n;i++)
     {
         rv[i]=distr(generator);
     }
     return rv;
}

void priorityscheduling::display()
{
    priority_queue <PCB> pqueue = this->pq;
    while (!pqueue.empty())
    {
        cout <<"\n("<<pqueue.top().pid<<","<< pqueue.top().priority<<","<<pqueue.top().bt<<")";
        pqueue.pop();
    }
    cout << '\n';
}

/*void priorityscheduling::displaywaitingtime()
{
    priority_queue <PCB> pqueue = this->pq;
    while (!pqueue.empty())
    {
        cout << pqueue.top().waitingtime<< " " ;
        pqueue.pop();
    }
    cout << '\n';
}*/

/*priority_queue <PCB> priorityscheduling::returnqueue()
{
    return this->pq;
}*/


int main()
{
    PCB pcb;
    priorityscheduling PS;
    int n, choice;
    cout<<"\nEnter the number of processes: ";
    cin>>n;

    int* rv= PS.uniformdistribution(n, 40);
    int* py= PS.uniformdistribution(n, 127);

    for(int i=0;i<n;i++)
    {
        pcb.pid=i+1;
        pcb.bt= rv[i];
        pcb.totbt=rv[i];
        pcb.priority= py[i];
        pcb.arrtime=0;
        pcb.restime=-1;
        PS.pq.push(pcb);
    }
    //PS.pq= PS.waitingtime();
    while(choice!=8)
    {
        cout<<"\n\nEnter you choice:\n1. Spawn new process\n2. Execute cpu time\n3. Display log of processes\n4. Display current CPU time\n";
        cout<<"5. Compute statistics\n6. Print map of processes\n7. Exit\n";
        cin>>choice;
        switch(choice)
        {
            case 1: int bt, pid, prio;
                    cout<<"\nEnter burst time, process ID and prioirty of the process to be added\n";
                    cin>>bt>>pid>>prio;
                    PS.spawnprocess(bt,prio,pid);
                    break;
            case 2: int t;
                    cout<<"Enter time value to execute: ";
                    cin>>t;
                    PS.executeprocess(t);
                    break;
            case 3: PS.display();
                    break;
            case 4: PS.displaycputime();
                    break;
            case 5: PS.statistics();
                    break;
            case 6: PS.printmap();
                    break;
            case 7: exit(0);
                    break;
        }
    }



}
