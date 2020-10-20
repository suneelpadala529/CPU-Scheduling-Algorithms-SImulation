#include "multilevelfeedbackqueuescheduling.h"

multilevelqueuescheduling::multilevelqueuescheduling()
{
    this->cputime=0;
    this->limit=age;
}

void multilevelqueuescheduling::executeageing2(int t)
{

    //int times=(((this->cputime-this->limit)%age)+this->limit)/age;      //denotes no of times priority has to be increased
    queue <PCB> test= this->fcfs1;
    queue <PCB> test2;
    while(1)
    {
        if(test.empty())
        {
            fcfs1= test2;
            break;
        }
        PCB pcb= test.front();
        //cout<<"\n"<<t<<" process1= "<<pcb.pid<<" "<<pcb.waitingtime;
        pcb.waitingtime+=t;
        if(pcb.waitingtime>=age2)
        {
            pcb.waitingtime=0;
            pq.push(pcb);
            test.pop();
        }
        else
        {
            test2.push(pcb);
            test.pop();
        }

    }

}
void multilevelqueuescheduling::executeageing1(int t)
{

    //int times=(((this->cputime-this->limit)%age)+this->limit)/age;      //denotes no of times priority has to be increased
    queue <PCB> test= this->fcfs2;
    queue <PCB> test2;
    while(1)
    {
        if(test.empty())
        {
            fcfs2= test2;
            break;
        }
        PCB pcb= test.front();
        //cout<<"\n"<<t<<" process2= "<<pcb.pid<<" "<<pcb.waitingtime;
        pcb.waitingtime+=t;
        if(pcb.waitingtime>=age)
        {
            pcb.waitingtime=0;
            fcfs1.push(pcb);
            test.pop();
        }
        else
        {
            test2.push(pcb);
            test.pop();
        }

    }

}

void multilevelqueuescheduling::spawnprocess(int bt,int pid,int prio)
{
    PCB p;
    p.bt= p.totbt=bt;
    p.restime=-1;
    p.pid=pid;
    p.arrtime= this->cputime;
    p.waitingtime=0;
    p.tat=0;
    p.priority=prio;
    this->pq.push(p);

}

void multilevelqueuescheduling::printmap()
{
    cout<<"\nID\tARR\tBT\tWT\tTAT\tRT\n";
    cout<<"------------------------------------";
    queue <PCB> pqueue = this->report;
    while (!pqueue.empty())
    {
        cout <<"\n"<<pqueue.front().pid<<"\t"<<pqueue.front().arrtime<<"\t"<<pqueue.front().totbt<<"\t"<<pqueue.front().waitingtime;
        cout<<"\t"<<pqueue.front().tat<<"\t"<<pqueue.front().restime;
        pqueue.pop();
    }
    cout << '\n';
}

void multilevelqueuescheduling::displaycputime()
{
    cout<<"\nCurrent CPU time: "<<this->cputime;
}

void multilevelqueuescheduling::executeprocess(int t)
{
    while(t>0)
    {
        if(!this->pq.empty())
        {
            while(t>=8&&!this->pq.empty())
            {
                if(pq.top().bt<=8)
                {
                    //this->limit=pq.top().bt;
                    PCB pcb= pq.top();
                    pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
                    pcb.tat= pcb.waitingtime+ pcb.totbt;
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=pcb.bt;
                    t-=pcb.bt;
                    int k= pcb.bt;
                    pcb.bt=0;
                    cout<<"\n1) Process ID: "<<pcb.pid<<", Priority: "<<pcb.priority<<", Original burst time: "<<pcb.totbt<<", Burst time left: "<<pcb.bt;
                    this->report.push(pcb);
                    pq.pop();
                    this->executeageing1(k);
                    this->executeageing2(k);

                }
                else
                {
                    //this->limit=t;
                    PCB pcb= pq.top();
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=8;
                    pcb.bt-=8;
                    t-=8;
                    //pcb.waitingtime=this->cputime;
                    this->executeageing2(8);
                    fcfs1.push(pcb);
                    cout<<"\n1) Process ID: "<<pcb.pid<<", Priority: "<<pcb.priority<<", original burst time: "<<pq.top().totbt<<", Burst time left: "<<pcb.bt;
                    pq.pop();
                    this->executeageing1(8);


                }
            }
            while(t>0&&!this->pq.empty())
            {
                if(pq.top().bt<=t)
                {
                    PCB pcb= pq.top();
                    pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
                    pcb.tat= pcb.waitingtime+ pcb.totbt;
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=pcb.bt;
                    t-=pcb.bt;
                    int k= pcb.bt;
                    pcb.bt=0;
                    cout<<"\n1) Process ID: "<<pcb.pid<<", Priority: "<<pcb.priority<<", Original burst time: "<<pcb.totbt<<", Burst time left: "<<pcb.bt;
                    this->report.push(pcb);
                    pq.pop();
                    this->executeageing1(k);
                    this->executeageing2(k);
                }
                else
                {
                    //this->limit=t;
                    PCB pcb= pq.top();
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=t;
                    pcb.bt-=t;
                    int k=t;
                    t=0;
                    cout<<"\n1) Process ID: "<<pcb.pid<<", Priority: "<<pcb.priority<<", original burst time: "<<pq.top().totbt<<", Burst time left: "<<pcb.bt;
                    this->executeageing1(k);
                    this->executeageing2(k);
                }
            }



        }
        else if(!this->fcfs1.empty())
        {
            while(t>=16&&!fcfs1.empty())
            {
                if(fcfs1.front().bt<=16)
                {

                    PCB pcb= fcfs1.front();
                    pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
                    pcb.tat= pcb.waitingtime+ pcb.totbt;
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=pcb.bt;
                    t-=pcb.bt;
                    int k=pcb.bt;
                    pcb.bt=0;
                    cout<<"\n2) Process ID: "<<fcfs1.front().pid<<", original burst time: "<<fcfs1.front().totbt<<", burst time left: "<<pcb.bt;
                    this->report.push(pcb);
                    fcfs1.pop();
                    this->executeageing2(k);
                    this->executeageing1(k);
                }
                else
                {
                    if(fcfs1.front().restime<0)
                        fcfs1.front().restime=this->cputime;
                    this->cputime+=16;
                    fcfs1.front().bt-=16;
                    PCB pcb= fcfs1.front();
                    t-=16;
                    cout<<"\n2) Process ID: "<<fcfs1.front().pid<<", original burst time: "<<fcfs1.front().totbt<<", burst time left: "<<pcb.bt;
                    pcb.waitingtime=0;
                    fcfs1.pop();
                    this->executeageing1(16);
                    fcfs2.push(pcb);
                    this->executeageing2(16);
                }
            }
            while(t>0&&!this->fcfs1.empty())
            {
                if(fcfs1.front().bt<=t)
                {

                    PCB pcb= fcfs1.front();
                    pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
                    pcb.tat= pcb.waitingtime+ pcb.totbt;
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=pcb.bt;
                    t-=pcb.bt;
                    int k=pcb.bt;
                    pcb.bt=0;
                    cout<<"\n2) Process ID: "<<fcfs1.front().pid<<", original burst time: "<<fcfs1.front().totbt<<", burst time left: "<<pcb.bt;
                    this->report.push(pcb);
                    fcfs1.pop();
                    this->executeageing1(k);
                    this->executeageing2(k);
                }
                else
                {
                    if(fcfs1.front().restime<0)
                        fcfs1.front().restime=this->cputime;
                    this->cputime+=t;
                    fcfs1.front().bt-=t;
                    this->executeageing2(t);
                    fcfs1.front().waitingtime=0;
                    PCB pcb= fcfs1.front();
                    int k=t;
                    t=0;
                    cout<<"\n2) Process ID: "<<fcfs1.front().pid<<", original burst time: "<<fcfs1.front().totbt<<", burst time left: "<<pcb.bt;
                    this->executeageing1(k);
                }
            }


        }
        else if(!this->fcfs2.empty())
        {
            while(t>0&&!this->fcfs2.empty())
            {
                if(fcfs2.front().bt<=t)
                {

                    PCB pcb= fcfs2.front();
                    pcb.waitingtime=this->cputime-pcb.arrtime-(pcb.totbt-pcb.bt);
                    pcb.tat= pcb.waitingtime+ pcb.totbt;
                    if(pcb.restime<0)
                        pcb.restime=this->cputime;
                    this->cputime+=pcb.bt;
                    t-=pcb.bt;
                    int k=pcb.bt;
                    pcb.bt=0;
                    cout<<"\n3) Process ID: "<<fcfs2.front().pid<<", original burst time: "<<fcfs2.front().totbt<<", burst time left: "<<pcb.bt;
                    this->report.push(pcb);
                    fcfs2.pop();
                    this->executeageing1(k);
                    this->executeageing2(k);
                }
                else
                {
                    if(fcfs2.front().restime<0)
                        fcfs2.front().restime=this->cputime;
                    this->cputime+=t;
                    fcfs2.front().bt-=t;
                    this->executeageing1(t);
                    this->executeageing2(t);
                    fcfs2.front().waitingtime=0;
                    PCB pcb= fcfs2.front();
                    int k=t;
                    t=0;
                    cout<<"\n3) Process ID: "<<fcfs2.front().pid<<", original burst time: "<<fcfs2.front().totbt<<", burst time left: "<<pcb.bt;

                }
            }


        }
    }

    /*else if(!this->cq.isempty())
    {
        if(t>=timequanta)
        {
            if(cq.returnqueue()[cq.returnfront()].bt>timequanta)
            {
                cq.returnqueue()[cq.returnfront()].bt-=timequanta;
                if(cq.returnqueue()[cq.returnfront()].restime<0)
                    cq.returnqueue()[cq.returnfront()].restime=this->cputime;
                this->cputime+=timequanta;
                t-=timequanta;
                cout<<"\nt in first="<<t;
                PCBQ pcbq= cq.returnqueue()[cq.returnfront()];
                cout<<"\nProcess ID: "<<pcbq.pid<<", original burst time: "<<pcbq.totbt<<", Burst time left: "<<pcbq.bt;
                cq.dequeue();
                cq.enqueue(pcbq);
                executeprocess(t);
            }
            else
            {
                PCBQ pcbq= cq.returnqueue()[cq.returnfront()];
                pcbq.waitingtime=(this->cputime-pcbq.arrtime)-(pcbq.totbt-pcbq.bt);
                pcbq.tat= pcbq.waitingtime+ pcbq.totbt;
                if(cq.returnqueue()[cq.returnfront()].restime<0)
                    cq.returnqueue()[cq.returnfront()].restime=pcbq.restime=this->cputime;
                this->cputime+=pcbq.bt;
                t-=pcbq.bt;
                pcbq.bt=0;
                cout<<"\nt in sec="<<t;
                PCB pcb;
                pcb.pid= pcbq.pid;
                pcb.bt=pcbq.totbt;
                pcb.totbt=pcbq.totbt;
                pcb.arrtime=pcbq.arrtime;
                pcb.tat= pcbq.waitingtime+pcbq.totbt;
                pcb.waitingtime=pcbq.waitingtime;
                pcb.restime=pcbq.restime;
                cout<<"\nProcess ID: "<<pcbq.pid<<", original burst time: "<<pcbq.totbt<<", Burst time left: "<<pcbq.bt;
                this->report.push(pcb);
                cq.dequeue();
                executeprocess(t);
            }

        }
        else    //if t<timequanta
        {
            if(cq.returnqueue()[cq.returnfront()].bt>t)
            {
                cq.returnqueue()[cq.returnfront()].bt-=t;
                PCBQ pcbq= cq.returnqueue()[cq.returnfront()];
                if(cq.returnqueue()[cq.returnfront()].restime<0)
                    cq.returnqueue()[cq.returnfront()].restime=this->cputime;
                this->cputime+=t;
                t=0;
                cout<<"\nt in third="<<t;
                cout<<"\nProcess ID: "<<pcbq.pid<<", original burst time: "<<pcbq.totbt<<", Burst time left: "<<pcbq.bt;
                executeprocess(t);
            }
            else
            {
                PCBQ pcbq= cq.returnqueue()[cq.returnfront()];
                pcbq.waitingtime=(this->cputime-pcbq.arrtime)-(pcbq.totbt-pcbq.bt);
                pcbq.tat= pcbq.waitingtime+ pcbq.totbt;
                if(cq.returnqueue()[cq.returnfront()].restime<0)
                    cq.returnqueue()[cq.returnfront()].restime=pcbq.restime=this->cputime;
                this->cputime+=pcbq.bt;
                t-=pcbq.bt;
                pcbq.bt=0;
                cout<<"\nt in fourth="<<t;
                PCB pcb;
                pcb.pid= pcbq.pid;
                pcb.bt=pcbq.totbt;
                pcb.totbt=pcbq.totbt;
                pcb.arrtime=pcbq.arrtime;
                pcb.tat= pcbq.waitingtime+pcbq.totbt;
                pcb.waitingtime=pcbq.waitingtime;
                pcb.restime=pcbq.restime;
                cout<<"\nProcess ID: "<<pcbq.pid<<", original burst time: "<<pcbq.totbt<<", Burst time left: "<<pcbq.bt;
                this->report.push(pcb);
                cq.dequeue();
                executeprocess(t);
            }
        }

    }*/


}

void multilevelqueuescheduling::statistics()
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

int* multilevelqueuescheduling::gaussiandistribution(int n, int mean, int stdev)
{

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean,stdev);

    int* p= new int[n];
    int i=0;
    while(1){
        int number = distribution(generator);
        if(number>0&&number<128)
        {
            p[i]=number;
            i++;
            if(i==n)
                return p;
        }

    }

}

void multilevelqueuescheduling::display(int ch)
{
    if(ch==3)
    {
        queue <PCB> q = this->fcfs2;
        while (!q.empty())
        {
            cout <<"\n("<<q.front().pid<<","<<q.front().bt<<")";//<<","<<q.front().waitingtime<<")";
            q.pop();
        }
        cout << '\n';
    }
    else if(ch==2)
    {
        queue <PCB> q = this->fcfs1;
        while (!q.empty())
        {
            cout <<"\n("<<q.front().pid<<","<<q.front().bt<<")";//","<<q.front().waitingtime<<")";
            q.pop();
        }
        cout << '\n';
    }
    else if(ch==1)
    {
        priority_queue <PCB> pqueue = this->pq;
        while (!pqueue.empty())
        {
            cout <<"\n("<<pqueue.top().pid<<","<<pqueue.top().priority<<","<<pqueue.top().bt<<")";
            pqueue.pop();
        }
        cout << '\n';
    }
}

bool operator<( PCB p1, PCB p2)
{
    return p1.priority < p2.priority;
}

int main()
{
    PCB pcb;
    PCBQ pcbq;
    multilevelqueuescheduling MQ;
    int n, choice;
    cout<<"\nEnter the number of processes: ";
    cin>>n;
    int *rv= MQ.gaussiandistribution(n, 8, 16);
    int* py= MQ.gaussiandistribution(n, 20, 20);


    for(int i=0;i<n;i++)
    {
        pcb.pid=i+1;
        pcb.bt=pcb.totbt= rv[i];
        pcb.priority=py[i];
        pcb.arrtime=0;
        pcb.restime=-1;
        pcb.tat=0;
        pcb.waitingtime=0;
        MQ.pq.push(pcb);
    }
    //MQ.cq.init(n);
    /*for(int i=n/3;i<2*n/3;i++)
    {
        pcbq.pid=i+1;
        pcbq.bt= pcbq.totbt=rv[i];
        pcbq.arrtime=0;
        pcbq.waitingtime=0;
        pcbq.restime=-1;
        pcbq.tat=0;
        MQ.cq.enqueue(pcbq);
    }
    for(int i=2*n/3;i<n;i++)
    {
        pcb.pid=i+1;
        pcb.bt= pcb.totbt=rv[i];
        pcb.arrtime=0;
        pcb.restime=-1;
        pcb.waitingtime=0;
        pcb.tat=0;
        MQ.fcfs.push(pcb);
    }*/

    while(choice!=7)
    {
        cout<<"\n\nEnter you choice:\n1. Spawn new process\n2. Execute a process\n3. Display log of processes\n4. Display current CPU time\n";
        cout<<"5. Compute statistics\n6. Print report\n7. Exit\n";
        cin>>choice;
        switch(choice)
        {
            case 1: int bt, pid, prio;
                    cout<<"\nEnter burst time, process ID and priority of the process to be added\n";
                    cin>>bt>>pid>>prio;
                    MQ.spawnprocess(bt,pid,prio);
                    break;
            case 2: int t;
                    cout<<"Enter time value to execute: ";
                    cin>>t;
                    MQ.executeprocess(t);
                    break;
            case 3: cout<<"\nSelect queue: 1.PQ 2.FCFS1 3.FCFS2\n";
                    int ch;
                    cin>>ch;
                    MQ.display(ch);
                    break;
            case 4: MQ.displaycputime();
                    break;
            case 5: MQ.statistics();
                    break;
            case 6: MQ.printmap();
                    break;
            case 7: exit(0);
                    break;
        }
    }

}
