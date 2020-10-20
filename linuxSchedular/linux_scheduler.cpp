#include<iostream>
#include<vector>
#include "rbt_adt.cpp"

#define YES 1
#define NO 0

typedef struct Process_Attr
{
    int process_id, arr_time, burst_time, nice, virtual_time, t_slice;
    float weight;
    int is_inserted;
}PCB;

int main()
{
    RB_TREE rb;
    int total_processes, completed_processes = 0 , *burst_times;
    int current_time = 0, targetted_latency = 20;
    int bt[total_processes],ct[total_processes];
    int prio_to_weight[40] = {
                                /* -20 */     88761,     71755,     56483,     46273,     36291,
                                /* -15 */     29154,     23254,     18705,     14949,     11916,
                                /* -10 */      9548,      7620,      6100,      4904,      3906,
                                /*  -5 */      3121,      2501,      1991,      1586,      1277,
                                /*   0 */      1024,       820,       655,       526,       423,
                                /*   5 */       335,       272,       215,       172,       137,
                                /*  10 */       110,        87,        70,        56,        45,
                                /*  15 */        36,        29,        23,        18,        15,
                                };
    cout<<"\n Enter total Number of Processes = ";
    cin>>total_processes;
    burst_times = rb.gaussiandistribution(total_processes, 10 , 8);

    PCB *process = new PCB[total_processes];
    for(int i = 0;i<total_processes;i++)
    {
        process[i].process_id = i;
        process[i].arr_time = i;        
        process[i].burst_time = burst_times[i];
        process[i].nice = i;
        if(process[i].nice == i)
            process[i].weight = prio_to_weight[20+i];
        process[i].virtual_time = 0;
        process[i].t_slice = 0;
        process[i].is_inserted = NO;

        bt[i] = burst_times[i];
        ct[i]=0;
    }
    cout<<"\nProcess ID | Arrival Time | Burst Time | Nice Value |  Weight  |  Virtual Time  |  Time slice   | Is Inserted";
    for (int i = 0; i < total_processes; i++)
    {
        cout<<"\n"<<process[i].process_id<<"\t\t"<<process[i].arr_time<<"\t\t"<<process[i].burst_time<<"\t\t"<<process[i].nice;
        cout<<"\t"<<process[i].weight<<"\t\t"<<process[i].virtual_time<<"\t\t"<<process[i].t_slice<<"\t\t"<<process[i].is_inserted;
    }
    cout<<"\n";
    cout<<"\n ================== GANTT CHART ========================== \n\n";
    int count=0;
    while(completed_processes<total_processes)
    {
        count++;
        PCB *avail_process = new PCB[total_processes];
        int j = 0;
        for(int i = 0;i<total_processes;i++)
        {
            if(process[i].arr_time<=current_time)
            {
                if(process[i].is_inserted == NO)
                {
                    avail_process[j] = process[i];
                    process[i].is_inserted = YES;
                    j++;
                }
            }
        }
        //Calculate time slice, virtual run time for all available processes
        int total_weight = 0;
        for(int k=0;k<j;k++)
        {
            total_weight = total_weight+avail_process[k].weight;
        }
        for(int k=0;k<j;k++)
        {
            avail_process[k].t_slice = targetted_latency*(avail_process[k].weight/total_weight);
            if(avail_process[k].t_slice<2)
                avail_process[k].t_slice = 2;
            avail_process[k].virtual_time = avail_process[k].virtual_time + (avail_process[k].t_slice*(prio_to_weight[20]/avail_process[k].weight));
            rb.insert_to_RB(rb.root, avail_process[k].process_id, avail_process[k].virtual_time, avail_process[k].arr_time, avail_process[k].burst_time,avail_process[k].nice,avail_process[k].weight, avail_process[k].t_slice);
                
        }
        RBT_NODE *min;
        min = rb.get_min_vtime_process(rb.root);

        if(min!=NULL)
        {
            if(min->b_time < min->time_slice && min->b_time>0)
            {
                current_time = current_time+min->b_time;
                min->b_time = min->b_time-min->b_time;
            }
            else if(min->b_time >= min->time_slice)
            {
                current_time = current_time+min->time_slice;
                min->b_time = min->b_time-min->time_slice;
            }
            cout<<min->p_id<<"_"<<min->b_time<<"_"<<current_time<<"|";
            if(min->b_time>0)
            {
                int id,arrival,burst,vir,nice,weight,slice;
                vir = min->v_time + min->time_slice*(prio_to_weight[20]/min->weight);
                id = min->p_id;
                arrival = min->a_time;
                burst = min->b_time;
                nice = min->nice_value;
                weight = min->weight;
                slice = min->time_slice;
                rb.insert_to_RB(rb.root, id, vir, arrival, burst,nice,weight,slice);
            }
            else if(min->b_time<=0)
            {
                ct[min->p_id] = current_time;
                completed_processes++;
            }
            free(min);
        }
    }
    cout<<"\n\n ============ CFS Result (Time in milliseconds)================ \n";
    int TAT[total_processes],WT[total_processes], total_tat=0, total_wt = 0;
    for (int i = 0; i < total_processes; i++)
    {
        TAT[i] = ct[i]-process[i].arr_time;
        WT[i] = TAT[i]-bt[i];
        total_tat = total_tat+TAT[i];
        total_wt = total_wt+WT[i];
    }
    cout<<"\n\nP_id\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < total_processes; i++)
    {
        cout<<i<<"\t"<<process[i].arr_time<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<TAT[i]<<"\t"<<WT[i]<<"\n";
    }
    cout<<"\n Avg Turn Around Time = "<<total_tat/total_processes;
    cout<<"\n Avg Waiting Around Time = "<<total_wt/total_processes;
    cout<<"\n\n";
    return 0;
}