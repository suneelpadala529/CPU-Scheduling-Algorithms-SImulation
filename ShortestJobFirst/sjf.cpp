#include<iostream>
#include<string.h>
#include<cstdlib>
#include<ctime>

using namespace std;

struct process{
 int index,burst,arrival,wait,tat,ct,rt;
 char* status;
 struct process* right;
 struct process* left;
};

void create_process(process** P,int index,int b, int a){
 process* newp = new process;
 newp->status = (char*)malloc(sizeof(char));
 newp->index = index;
 newp->burst = b;
 newp->arrival = a;
 newp->wait = 0;
 newp->right = newp;
 newp->left = newp;
 strcpy(newp->status,"ready");

 if((*P)!=NULL){
   newp->right = (*P);
   newp->left = (*P)->left;
   ((*P)->left)->right = newp;
   (*P)->left = newp;
  }
 else{ 
  (*P)=newp;
 }
}

void print_chart(process* P){
 process* endp = P;
 cout<<"Index \t Burst \t Arrival \t Wait \t status \t CT \t TAT \t Response Time"<<endl;
 do{
   if(!strcmp(P->status, "ready"))
    cout<<(P->index)<<" \t "<<P->burst<<" \t "<<P->arrival<<" \t \t"<<P->wait<<" \t "<<P->status<<endl;
   else
    cout<<(P->index)<<" \t "<<P->burst<<" \t "<<P->arrival<<" \t \t"<<P->wait<<" \t "<<P->status<< " \t "<<P->ct<< " \t "<<P->tat<<" \t "<<P->rt<<endl;
   P = P->right;
 }while(P!=endp);
 cout<<endl; 
}

process* select_waiting_process(process* P, int ct){
 process* endp = P;
 process* nextp = NULL;
 int s_burst = 0;
 do{
   if(!strcmp(P->status, "ready")){
     if(P->arrival <= ct){
       s_burst = P->burst;
       nextp = P;
       break;
     }
   }
   P = P->right;
 }while(P!=endp);
 do{
   if(!strcmp(P->status, "ready")){
     if(P->arrival <= ct){
       if(P->burst < s_burst){
       s_burst = P->burst;
       nextp = P;
     }
     }
   }
   P = P->right;
 }while(P!=endp);
 return nextp;
}

process* select_running_process(process* P){
 process* endp = P;
 do{
   if(!strcmp(P->status, "running")){
    return P;
   }
   P = P->right;
 }while(P!=endp);
}

int initial_time(process* P){
 process* endp = P;
 int s_arrival = P->arrival;
 do{
  if(s_arrival > P->arrival){
    s_arrival = P->arrival;
  }
  P = P->right; 
 }while(P!=endp);
 return s_arrival;
}

void schedule_SJF(process** P){
 process* temp = *P;
 bool scheduled=false;
 int ct = initial_time(*P);
 while(!scheduled){

  process* wp = select_waiting_process(*P, ct);
   if(wp!=NULL){
    // if(wp->arrival <= ct){

    process* rp = select_running_process(*P);
    if(rp!=NULL){
      if(wp->arrival < rp->ct){
        wp->wait = rp->ct - wp->arrival;
        wp->tat = wp->wait + wp->burst;
        wp->ct = rp->ct + wp->burst; 
        wp->rt = wp->wait;
        strcpy(wp->status, "running");
        strcpy(rp->status, "terminated");
      }
      else{
        wp->tat = wp->burst;
        wp->ct = wp->arrival + wp->burst;
        wp->rt = wp->arrival;
        strcpy(wp->status, "running");
      }
    }
    else{
      wp->tat = wp->burst;
      wp->ct = wp->arrival + wp->tat;
      wp->rt = wp->arrival;
      strcpy(wp->status, "running");
    }
   ct = wp->ct;
   }
   else{
    scheduled=true;
    process* rp = select_running_process(*P);
    if(rp!=NULL){
      strcpy(rp->status, "terminated");
    }
   }

 }

}

void print_mean_std(process* P){
  process* endp = P;
  float wait_sum = 0;
  float tat_sum = 0;
  float rt_sum = 0;
  int n=0;
  do{
    wait_sum += P->wait;
    tat_sum += P->tat;
    rt_sum += P->rt;
    n++;
    P = P->right;
  }while(P!=endp);
  wait_sum /= n;
  tat_sum /= n;
  rt_sum /= n;
  cout<<"\n";
  cout<<"Avg Wait time: "<<wait_sum<<" | Avg Turnaround time: "<<tat_sum<<" | Avg Response Time: "<<rt_sum<<endl;
}

int main()
{
 srand((unsigned) time(0));

 process* P = NULL;

 for(int i=0;i<(rand()%10); i++)
 {
   create_process(&P,i,(rand()%100),(rand()%20));
 }
 print_chart(P);

 schedule_SJF(&P);

 print_chart(P);
 print_mean_std(P);
 return 0;
}
