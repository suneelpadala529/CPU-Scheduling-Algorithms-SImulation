#include<iostream>
#include<string.h>
#include<cstdlib>
#include<ctime>

using namespace std;

struct process{
 int index,burst,arrival,wait,tat,ct,rburst,rt;
 char* status;
 struct process* right;
 struct process* left;
};

struct rquee{
  process* headp;
  struct rquee* next=NULL;
};

void create_process(process** P,int index,int b, int a){
 process* newp = new process;
 newp->status = (char*)malloc(sizeof(char));
 newp->index = index;
 newp->burst = b;
 newp->rburst = b;
 newp->arrival = a;
 newp->wait = 0;
 newp->right = newp;
 newp->left = newp;
 strcpy(newp->status,"new");

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

void insert_process(rquee** Q, process** P){
 rquee* newp = new rquee;
 strcpy((*P)->status, "ready");
 newp->headp = (*P);

 rquee* temp = *Q;
 if(temp!= NULL){
    while(temp->next != NULL){
       temp = temp->next;
    }
    temp->next = newp;
 }
 else{
   *Q = newp;
 }
}

void print_chart(process* P){
 process* endp = P;
 cout<<"Index \t Burst \t Arrival \t Wait \t status \t CT \t TAT \t Response Time"<<endl;
 do{
   if(!strcmp(P->status, "new"))
    cout<<(P->index)<<" \t "<<P->burst<<" \t "<<P->arrival<<" \t \t"<<P->wait<<" \t "<<P->status<<endl;
   else
    cout<<(P->index)<<" \t "<<P->burst<<" \t "<<P->arrival<<" \t \t"<<P->wait<<" \t "<<P->status<< " \t "<<P->ct<< " \t "<<P->tat<<" \t "<<P->rt<<endl;
   P = P->right;
 }while(P!=endp);
 cout<<endl; 
}

// process* select_ready_process(process* P){
//  process* endp = P;
//  int s_arr;
//  process* nextp=NULL;
//  do{
//    if(!strcmp(P->status, "ready")){
//       s_arr = P->arrival;
//       nextp = P;
//       break;
//    }
//    P = P->right;
//  }while(P!=endp);
 
//  do{
//    if(!strcmp(P->status, "ready")){
//      if(P->arrival < s_arr){
//        s_arr = P->arrival;
//        nextp = P;
//      }
//    }
//    P = P->right;
//  }while(P!=endp);

//  return nextp;
// }

// void create_quee(rquee** Q, process* P){
//   process* endp = P;
//   process* nextp = select_ready_process(P);
//   while(nextp!=NULL){
//     insert_process(Q, &nextp);
//     nextp = select_ready_process(P);
//   }
// }

process* select_queed_process(rquee** Q){
 process* nextp = NULL;
 if((*Q)!=NULL){
  nextp = (*Q)->headp;
  rquee* temp = (*Q);
  (*Q) = (*Q)->next;
  free(temp); 
 } 
 return nextp;
}

process* select_newly_arrived(process* P,int ct){
 process* endp = P;
 int s_arr;
 process* newp=NULL;
 do{
   if(!strcmp(P->status, "new")){
     if(P->arrival <= ct){
       s_arr = P->arrival;
       newp = P;
       break;  
     }
   }
   P = P->right;
 }while(P!=endp);
 do{
   if(!strcmp(P->status, "new")){
     if( (P->arrival < s_arr) && (P->arrival <= ct) ){   
       s_arr = P->arrival;
       newp = P;  
     }
   }
   P =P->right;
 }while(P!=endp);
  return newp;
}

process* select_initially_arrived(process *P){
 process* endp = P;
 int s_arr;
 process* newp=NULL;
 do{
   if(!strcmp(P->status, "new")){
       s_arr = P->arrival;
       newp = P;
       break;  
   }
   P = P->right;
 }while(P!=endp);
 do{
   if(!strcmp(P->status, "new")){
     if(P->arrival < s_arr){   
       s_arr = P->arrival;
       newp = P;  
     }
   }
   P =P->right;
 }while(P!=endp);
  return newp;
}

bool all_terminated(process* P){
 process* endp = P;
 do{
     if(strcmp(P->status,"terminated")){
         return false;
     }
     P = P->right;
 }while(P!=endp);
 return true;
}

void schedule_RR(process** P, int q){
 rquee* Q = NULL;
 bool scheduled=false;
 int ct = 0;
 process* fp = select_initially_arrived(*P);
 insert_process(&Q, &fp);
 ct = (Q->headp)->arrival;

 while(!scheduled){
   
  process* qp = select_queed_process(&Q);
   if(qp!=NULL){
      strcpy(qp->status, "running");

      if(qp->rburst == qp->burst){
        qp->rt = ct - qp->arrival;
      }
      if(qp->rburst > q){
        qp->rburst = qp->rburst - q;
        ct = ct + q;

        process* rdp = select_newly_arrived(*P, ct);  
        while(rdp!=NULL){
            insert_process(&Q, &rdp);
            rdp = select_newly_arrived(*P, ct);
        } 
        insert_process(&Q, &qp);
      }
      else{
        ct = ct + qp->rburst;
        
        process* rdp = select_newly_arrived(*P, ct);  
        while(rdp!=NULL){
            insert_process(&Q, &rdp);
            rdp = select_newly_arrived(*P, ct);
        }

        qp->rburst = 0;
        qp->ct = ct;
        qp->tat = qp->ct - qp->arrival;
        qp->wait = qp->tat - qp->burst;
        strcpy(qp->status, "terminated");
      }
 
   }
   else{
    if(all_terminated(*P)){
        scheduled=true;
    }
    else{
        process* nextp = select_initially_arrived(*P);
        ct = nextp->arrival;
        insert_process(&Q, &nextp); 
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
 int q =2; // quantum

 for(int i=0;i<(rand()%10 + 1); i++)
 {
   create_process(&P,i,(rand()%20 + 1),(rand()%20));
 }
 
//  create_process(&P,0,1,9);
//  create_process(&P,1,11,12);
//  create_process(&P,2,8,15);

 print_chart(P);

 schedule_RR(&P, q);

 print_chart(P);

 print_mean_std(P);
 return 0;
}
