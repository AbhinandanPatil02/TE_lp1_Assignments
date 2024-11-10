#include<iostream>
#include<climits>
using namespace std;


class process{
    public:
    int pid;
    int bt;
    int at;
    int priority;
    int remaining_bt;

};

class algo{
    public:
    process *p;
    algo(process*q){
        this->p=q;
    }
    void fcfs(int n,int ct[],int tat[],int wt[]){
        int wait=0;
        for(int i=0;i<n;i++){
            if(wait<p[i].at){
                wait=p[i].at;
            }
            ct[i]=wait+p[i].bt;
            tat[i]=ct[i]-p[i].at;
            wt[i]=tat[i]-p[i].bt;
            wait=ct[i];
        }
    }


    void sjfpre(int n,int ct[],int tat[],int wt[]){
        int completed=0;
        int current_time=0;
        while(completed<n){
            int min_bt=INT_MAX;
            int min_bt_index=-1;
            for(int i=0;i<n;i++){
                if(p[i].at<=current_time&&p[i].remaining_bt<min_bt&&p[i].remaining_bt>0){
                    min_bt=p[i].remaining_bt;
                    min_bt_index=i;
                }
            }
            if(min_bt_index==-1){
                current_time++;
                continue;
            }
            p[min_bt_index].remaining_bt--;
            current_time++;
            if(p[min_bt_index].remaining_bt==0){
                completed++;
                ct[min_bt_index]=current_time;
                tat[min_bt_index]=ct[min_bt_index]-p[min_bt_index].at;
                wt[min_bt_index]=tat[min_bt_index]-p[min_bt_index].bt;
            }
        }
    }


    void prioritynon(int n,int ct[],int tat[],int wt[]){
        int completed=0;
        int current_time=0;
        // lower the no higher the priority
        while(n>completed){
            int highest_priority=INT_MAX;
            int highest_priority_index=-1;
            for(int i=0;i<n;i++){
                if(p[i].at<=current_time&&p[i].priority<highest_priority&&p[i].remaining_bt>0){
                    highest_priority=p[i].priority;
                    highest_priority_index=i;
                }
            }
            if(highest_priority_index!=-1){
                completed++;
                ct[highest_priority_index]=current_time+p[highest_priority_index].bt;
                tat[highest_priority_index]=ct[highest_priority_index]-p[highest_priority_index].at;
                wt[highest_priority_index]=tat[highest_priority_index]-p[highest_priority_index].bt;
                p[highest_priority_index].remaining_bt=0;
                current_time=ct[highest_priority_index];
            }
            else{
                current_time++;
            }
            
        }

    }


    void rr(int n,int ct[],int tat[],int wt[],int qunt){
        int remaining=n;
        int rem[n];
        int current_time=0;
        for(int i=0;i<n;i++){
            rem[i]=p[i].bt;
        }
        while (remaining>0){
            int done=1;
            for(int i=0;i<n;i++){
                if(p[i].at<=current_time&&rem[i]>0){
                    done=0;
                    if(qunt<rem[i]){
                        current_time+=qunt;
                        rem[i]-=qunt;
                    }
                    else{
                        current_time=rem[i];
                        remaining--;
                        rem[i]=0;
                        ct[i]=current_time;
                        tat[i]=ct[i]-p[i].at;
                        wt[i]=tat[i]-p[i].bt;
                    }

                }
            }
            if(done){
                current_time++;
            }
            
        }
        


    }







// n,ct,tat,wt
    void print(int n,int ct[],int tat[],int wt[]){
        cout<<"p_id\tat\tbt\tct\ttat\twt"<<endl;
        for(int i=0;i<n;i++){
            cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
        }
    }









};









int main(){

    process *p;
    int n;
    cout<<"Ente no  of process : ";
    cin>>n;
    p=new process[n];
    algo a(p);

    int wt[n];
    int tat[n];
    int ct[n];

    for(int i=0;i<n;i++){
        cout<<"Enter p_id : ";
        cin>>p[i].pid;
        cout<<"Enter Arival Time : ";
        cin>>p[i].at;
        cout<<"Enter Brust Time : ";
        cin>>p[i].bt;
        p[i].remaining_bt=p[i].bt;
    }

    for(int i=0;i<n;i++){
        cout<<"Enter Priprity : ";
        cin>>p[i].priority;
    }



    // a.fcfs(n,ct,tat,wt);
    // a.sjfpre(n,ct,tat,wt);
    a.prioritynon(n,ct,tat,wt);

    cout<<endl;
    a.print(n,ct,tat,wt);


    return 0;
}












// 4  1 0 2  2 1 2  3 5 3  4 6 4

// process id       Arival time    Brust time      Completion time TurnAround Time Waiting Time
// 1               0               2               2               2               0
// 2               1               2               4               3               1
// 3               5               3               8               3               0
// 4               6               4               12              6               2


//------------------------------------------------------------------------------------------------

// 4   1 0 5  2 1 3  3 2 4  4 4 1


// process id       Arival time    Brust time      Completion time TurnAround Time Waiting Time
// 1               0               5               9               9               4
// 2               1               3               4               3               0
// 3               2               4               13              11              7
// 4               4               1               5               1               0

//------------------------------------------------------------------------------------------------



// 4   1 0 5  2 1 3  3 2 4  4 4 1
//     5 3 2 1 4
// process id       Arival time    Brust time      Completion time TurnAround Time Waiting Time
// 1               0               5               5               5               0
// 2               1               3               13              12              9
// 3               2               4               10              8               4
// 4               4               1               6               2               1

// -------------------------------------------------------------------------------------------------
// 4   1 0 5  2 1 4  3 2 2  4 4 1             2


// process id       Arival time    Brust time      Completion time TurnAround Time Waiting Time
// 1               0               5               12              12              7
// 2               1               4               11              10              6
// 3               2               2               6               4               2
// 4               4               1               7               3               2




