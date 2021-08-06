#include <bits/stdc++.h>
#define int long long int
using namespace std;

struct Process {
    int p; // Process ID
    int bt; // Burst Time
    int at; // Arrival Time
    int rt; // Remaining Burst Time
    int wt; // Waiting Time
    int tat; //Turn Around Time
    int priority; // priority
    int priority2; // for coding purpose
}p[10002], temp, data[10002]; //process array and data array

struct comp{
    char algo[30]; // array for different algorithms
    float avg_wt; // average waiting time
    float avg_tat; // average turnaround time
}algo[30];

void menu();
void input();
void assign();
void comparator();

void rr(int);
void irr(int);
void irr_mean_tq(int);
void amrr(int);
void irr_min_tq(int);
void irrsjf(int);
void irrsjfdtq(int);
void arr(int);
void rr_priority(int);
void irr_mean_tq_priority(int);
void irr_min_tq_priority(int);
void irrsjf_priority(int);
void irrsjfdtq_priority(int);
    

int n;

int32_t main()
    {
        menu();
        return 0;
    }

void menu()
{       
        // take input form user
        int ch;
        printf("\nTable\n1.New Input\n2.Round Robin Algorithm\n3.Improved Round Robin Algorithm\n4.Improved Round Robin MEAN Time Quantum Algorithm\n5.Improved Round Robin Minimum Time Quantum Algorithm\n6.Improved Round Robin Shortest Job First Algorithm\n7.Improved Round Robin Shortest Job First Dynamic Time Quantum Algorithm\n8.Average Max Round Robin Algorithm\n9.Adaptive Round Robin with Shortest Job First with Dynamic Time Quantum Algorithm \n10.Round Robin with Priority \n11. Improved Round Robin MEAN Time Quantum Algorithm with priority \n12. Improved Round Robin Minimum Time Quantum Algorithm with priority \n13. Improved Round Robin Shortest Job First Algorithm \n14. Improved Round Robin Shortest Job First Dynamic Time Quantum Algorithm with priority \n15. Comparison of all \n16.Exit");
        printf("\n\nEnter your choice from the above table : ");
            //scanf("%d",&ch);
            cin>>ch;
            switch(ch)
            {
                case 1:input();break;
                case 2:rr(1);break;
                case 3:irr(1);break;
                case 4:irr_mean_tq(1);break;
                case 5:irr_min_tq(1);break;
                case 6:irrsjf(1);break;
                case 7:irrsjfdtq(1);break;
                case 8:amrr(1);break;
                case 9:arr(1);break;
                case 10:rr_priority(1); break;
                case 11:irr_mean_tq_priority(1); break;
                case 12:irr_min_tq_priority(1); break;
                case 13:irrsjf_priority(1); break;
                case 14:irrsjfdtq_priority(1); break;
                case 15:comparator();break;
                case 16:exit(0);break;
                default: printf("\n\nPlease enter choice from 1 to 15 only\n");menu();
            }
}

void input()
{
        // take input generated from the input file to process array
        fstream my_file;
        my_file.open("inputfile", ios::in);
	    if (!my_file) {
	        cout << "No such file"; // if the file doesn't exist the print NO file exist
	    }
        else {
            int i=0;
            int out=0;
            while(i<5){ // i < 5 because each number in the input file is of length 5, preceding 0's might be there
                char ch;
                my_file >> ch;
                if (my_file.eof())
			        return;
                out = 10 * out + (ch - '0');
                i++;
            }
            n = out;

            for(int i=0;i<n;i++)
            {  
                int j=0;
                int out=0;
                while(j<5){
                    char ch;
                    my_file >> ch;
                    if (my_file.eof())
                        return;
                    out = 10 * out + (ch - '0');
                    j++;
                }
                //cout<<out<<endl;
                data[i].bt = out; // burst time for n processes
                data[i].rt = data[i].bt; // remaining time = burst time initially
            }
            
            for(int i=0; i<n; i++)
            { 
                int j=0;
                int out=0;
                while(j<5){
                    char ch;
                    my_file >> ch;
                    if (my_file.eof())
                        return;
                    out = 10 * out + (ch - '0');
                    j++;
                }
                data[i].at = out; // arrival time for n processes
                data[i].p=i+1; // process id will be from 1 to 10,000
            }

            for(int i=0; i<n; i++)
            {
                int j=0;
                int out=0;
                while(j<5){
                    char ch;
                    my_file >> ch;
                    if (my_file.eof())
                        return;
                    out = 10 * out + (ch - '0');
                    j++;
                }
                data[i].priority = out; // priority of processes (1 to 50)
                data[i].priority2 = out; // for coding purpose
            }
        }
        my_file.close(); // close the file
        menu();
}

void sort_arrival_time()
{
    // sort the input data according to the arrival time
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].at>p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void sort_priority()
{
    // sort the input data according to the priority of the processes
    for(int i=0; i<n-1; i++)
    {                                                       
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].priority>p[j+1].priority)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void assign()
{
    // assing each data to the process
    for(int i=0; i<n; i++)
        p[i]=data[i];
}
    
/****************************************** NOTE *****************************************/
// SOME TERMS THAT ARE COMMON IN ALGORITHMS AND THERE PURPOSE
// tot_wt --> total waiting time
// tot_tat --> total turnaround time
// time_quantum --> time quantum for a particular or whole process accordingly
// remain --> number of processes remaining at a particular time
// flag --> for coding purpose
// vector<int> flag1(n,0) for coding purpose
// extra_var --> for coding purpose
// tq[50] --> time quantum array for processes with different priority (1 to 50)
// mean --> used for coding purpose related to mean time quantum algorithms


void rr(int menu_flag) 
{ 
    cout<<"\nRound Robin\n";
    assign();
    int remain=n, time_quantum, tot_wt=0, tot_tat=0, flag=0;
    vector<int> flag1(n,0); 
    sort_arrival_time();
    cout<<"\nEnter Time Quantum : "; 
    cin>>time_quantum;  
    for(int i=0,time=p[0].at; remain!=0;) 
    {   
        if(p[i].rt<=time_quantum && p[i].rt>0) 
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>0) 
        { 
            p[i].rt-=time_quantum; 
            time+=time_quantum; 
        } 
        if(p[i].rt==0 && flag==1) 
        { 
            remain--; 
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tat=time-p[i].at;
            tot_wt+=p[i].wt; 
            tot_tat+=p[i].tat; 
            flag=0; 
            flag1[i] = 1;
        } 
        
        if(i==n-1) 
        {
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
        else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time){
            int j=0; 
            int extra_var = 0; 
            for(; j<=i; j++){
                if(!flag1[j]){
                    extra_var = 1;
                    break;
                } 
            }
            if(extra_var) i=j;
            else time++;
        }
        else if(p[i+1].at<=time) 
        i++; 
        else{
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
    } 
    // output data in a separate file
    fstream fout;
    fout.open("rr.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[1].algo,"rr");
        algo[1].avg_tat=(float)tot_tat/n;
        algo[1].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void rr_priority(int menu_flag) 
{ 
    cout<<"\nRound Robin with Priority\n";
    assign();
    int remain=n, time_quantum, tot_wt=0, tot_tat=0, flag=0; 
    vector<int> flag1(n,0); 
    sort_arrival_time();
    sort_priority();
    int tq[50]; 
    for(int i=0; i<50; i++){
        tq[i] = 50 - i; // tq = 50 for highest priority, and tq = 1 for lowest priority
    }
    for(int i=0,time=p[0].at; remain!=0;) 
    {   
        int time_quantum = tq[(p[i].priority) - 1];
        if(p[i].rt<=time_quantum && p[i].rt>0) 
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>0) 
        { 
            p[i].rt-=time_quantum; 
            time+=time_quantum; 
        } 
        if(p[i].rt==0 && flag==1) 
        { 
            remain--; 
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tat=time-p[i].at;
            tot_wt+=p[i].wt; 
            tot_tat+=p[i].tat; 
            flag=0; 
            flag1[i] = 1;
        }
        else if(p[i].rt != 0 && p[i].at <= time){
            if(p[i].priority != 1) p[i].priority--;
        } 
        
        if(i==n-1) 
        {
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
        else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time){
            int j=0; 
            int extra_var = 0;
            for(; j<=i; j++){
                if(!flag1[j]){
                    extra_var = 1;
                    break;
                } 
            }
            if(extra_var) i=j;
            else time++;
        }
        else if(p[i+1].at<=time) 
        i++; 
        else{
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
    } 
    // output data in a separate file
    fstream fout;
    fout.open("rr_priority.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<","<<"Priority"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<","<<p[i].priority2<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[9].algo,"rr_priority");
        algo[9].avg_tat=(float)tot_tat/n;
        algo[9].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void irr(int menu_flag) 
{ 
    cout<<"\nImproved Round Robin RR.pdf An Additional Improvement Round Robin CPU scheduling algorithm (AAIRR)\n";
    // will exexute again for a process if the remaing time is less than 1 time quantum 
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0; 
    vector<int> flag1(n,0);
    sort_arrival_time();
    cout<<"\nEnter Time Quantum : "; 
    cin>>time_quantum; 
    int time = p[0].at;
    for(int i=0; remain!=0;) 
    { 
        if(p[i].rt<=time_quantum && p[i].rt>0) 
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>0) 
        { 
            p[i].rt-=time_quantum; 
            time+=time_quantum; 
        } 
        if(p[i].rt==0 && flag==1) 
        { 
            remain--; 
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tat=time-p[i].at;
            tot_wt+=p[i].wt; 
            tot_tat+=p[i].tat; 
            flag=0;
            flag1[i] = 1; 
        }

        if(i==n-1) 
        {
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
        else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time){
            int j=0; 
            int extra_var = 0;
            for(; j<=i; j++){
                if(!flag1[j]){
                    extra_var = 1;
                    break;
                } 
            }
            if(extra_var) i=j;
            else time++;
        }
        else if(p[i+1].at<=time) 
        i++; 
        else{
            int j = i;
            for(j=0; j<n; j++){
                if(!flag1[j]) break;
            }
            i = j;
        }
    }

    // output data in a separate file
    fstream fout;
    fout.open("irr.csv", ios::out | ios::trunc); 
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n";
        fout.close(); 
        strcpy(algo[2].algo,"irr");
        algo[2].avg_tat=(float)tot_tat/n;
        algo[2].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void irr_mean_tq(int menu_flag) 
{ 
    
    cout<<"\nImproved Roud Robin with Dynamic Mean Quantum Time DABRR\n";
    // time quantum will be mean of the processes in the ready queue
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0, mean=0, time2; 
    vector<int> flag1(n,0);
    sort_arrival_time();
    for(int i=0,time=p[0].at, time2=p[0].at; remain!=0;) 
    { 
        mean=0;
        int count_prq = 0;
        time2 = time;
        for(int j=0; j<n; j++)
        {
            if(p[j].at <= time && p[j].rt != 0){
                mean+=p[j].rt;
                count_prq++;
            }
        }
        int count_inside = 0;   
        if(count_prq == 0){
            time++;
            continue;
        }
        time_quantum = ((mean)/(count_prq));	
        while(count_inside < count_prq){
            if(p[i].rt<=time_quantum && p[i].rt>0) 
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            } 
            else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            }
            else if(p[i].rt>0) 
            { 
                p[i].rt-=time_quantum; 
                time+=time_quantum; 
                count_inside++;
            } 
            if(p[i].rt==0 && flag==1) 
            { 
                remain--; 
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tat=time-p[i].at;
                tot_wt+=p[i].wt; 
                tot_tat+=p[i].tat; 
                flag=0; 
                flag1[i] = 1;
            }

            if(i==n-1) 
            {
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
            else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time2){
                int j=0; 
                int extra_var = 0;
                for(; j<=i; j++){
                    if(!flag1[j]){
                        extra_var = 1;
                        break;
                    } 
                }
                if(extra_var) i=j;
                else time++;
            }
            else if(p[i+1].at<=time2) 
            i++; 
            else{
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
        }
        
    } 

    // output data in a separate file
    fstream fout;
    fout.open("irr_mean_tq.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
    for(int i=0; i<n; i++)
        fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
    fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
    fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    fout.close();
    strcpy(algo[3].algo,"irr_mean_tq");
    algo[3].avg_tat=(float)tot_tat/n;
    algo[3].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irr_mean_tq_priority(int menu_flag) 
{ 
    cout<<"\nImproved Roud Robin with Dynamic Mean Quantum Time  with priority \n";
    // time quantum will be mean of the processes in the ready queue for particular with same priority
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0, mean=0, time2; 
    vector<int> flag1(n,0);
    sort_priority();  
    sort_arrival_time();                                   
    int tq[50];
    // sum[50] && cnt_prq[50] --> used for coding purpose to calculate time quantum dynamically (mean time quantum)
    int sum[50]; // sum of remaining time of process of particular time in ready queue
    int cnt_prq[50]; // number of process of particular priority in ready queue
    for(int i=0,time=p[0].at; remain!=0;) 
    { 
        memset(sum,0,sizeof(sum));
        memset(cnt_prq,0,sizeof(cnt_prq));
        int count_prq = 0; // for coding purpose
        time2 = time;
        for(int j=0; j<n; j++)
        {
            if(p[j].at <= time && p[j].rt != 0){
                sum[(p[j].priority) - 1]+=p[j].rt;
                count_prq++;
                cnt_prq[(p[j].priority) - 1]++;
            }
        }
        
        int count_inside = 0;    // for coding purpose
        for(int i=0;i<50;i++){
            if(cnt_prq[i] == 0) tq[i] = 0;
            else tq[i]=((sum[i])/cnt_prq[i]);
        }	
        while(count_inside < count_prq){
            time_quantum = tq[p[i].priority - 1];
            if(p[i].rt<=time_quantum && p[i].rt>0) 
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            } 
            else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            }
            else if(p[i].rt>0) 
            { 
                p[i].rt-=time_quantum; 
                time+=time_quantum; 
                count_inside++;
            } 
            if(p[i].rt==0 && flag==1) 
            { 
                remain--; 
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tat=time-p[i].at;
                tot_wt+=p[i].wt; 
                tot_tat+=p[i].tat; 
                flag=0; 
                flag1[i] = 1;
            }
            else if(p[i].rt != 0 && p[i].at <= time2){
                if(p[i].priority != 1){
                    p[i].priority--;
                }
            } 

            if(i==n-1) 
            {
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
            else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time2){
                int j=0; 
                int extra_var = 0;
                for(; j<=i; j++){
                    if(!flag1[j]){
                        extra_var = 1;
                        break;
                    } 
                }
                if(extra_var) i=j;
                else time++;
            }
            else if(p[i+1].at<=time2) 
            i++; 
            else{
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
        }
        
    } 

    // output data in a separate file
    fstream fout;
    fout.open("irr_mean_tq_priority.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<","<<"Priority"<<"\n";
    for(int i=0; i<n; i++)
        fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<","<<p[i].priority2<<"\n";
    fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
    fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    fout.close();
    strcpy(algo[10].algo,"irr_mean_tq_priority");
    algo[10].avg_tat=(float)tot_tat/n;
    algo[10].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void amrr(int menu_flag) 
{ 
    cout<<"\nImproved Roud Robin with Dynamic (Mean + max)/2 TIme Quantum AMRR RR.pdf \n";
    // time quantum will be (mean + maximum remaining time of a processs in ready queue)/2;
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0, mean=0, time2; 
    vector<int> flag1(n,0);
    sort_arrival_time();
    for(int i=0,time=p[0].at; remain!=0;) 
    { 
        mean=0; // for coding purpose
        int count_prq = 0; // for coding purpose
        int max_tq = 0; // for coding purpose
        time2 = time;
        for(int j=0; j<n; j++)
        {
            if(p[j].at <= time && p[j].rt != 0){
                count_prq++;
                mean+=p[j].rt;
                max_tq = max(max_tq, p[j].rt);
            }
        }
        int count_inside = 0;  // for coding purpose
        time_quantum = ((mean/count_prq + max_tq)/2);	
        while(count_inside < count_prq){
            if(p[i].rt<=time_quantum && p[i].rt>0) 
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            } 
            else if(p[i].rt>0) 
            { 
                p[i].rt-=time_quantum; 
                time+=time_quantum; 
                count_inside++;
            } 
            if(p[i].rt==0 && flag==1) 
            { 
                remain--; 
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tat=time-p[i].at;
                tot_wt+=p[i].wt; 
                tot_tat+=p[i].tat; 
                flag=0; 
                flag1[i] = 1;
            } 
            if(i==n-1) 
            {
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
            else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time2){
                int j=0; 
                int extra_var = 0;
                for(; j<=i; j++){
                    if(!flag1[j]){
                        extra_var = 1;
                        break;
                    } 
                }
                if(extra_var) i=j;
                else time++;
            }
            else if(p[i+1].at<=time2) 
            i++; 
            else{
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
        }
        
    } 

    // output data in a separate file
    fstream fout;
    fout.open("amrr.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
    for(int i=0; i<n; i++)
        fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
    fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
    fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    fout.close();
    strcpy(algo[7].algo,"amrr");
    algo[7].avg_tat=(float)tot_tat/n;
    algo[7].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irr_min_tq(int menu_flag) 
{
     
    cout<<"\nImproved ROund Robin with Dynamic Minimum Quantum Time IRRVQ \n";
    // time quantum will be the minimum remaining time quantum of a process in ready queue
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0, time2, mintq=INT_MAX; 
    vector<int> flag1(n,0);
    sort_arrival_time();  
    for(int i=0,time=p[0].at; remain!=0;) 
    {   
        time2 = time; // for coding purpose
        int count_prq = 0; // for coding purpose
        for(int j=0; j<n; j++){
            if(p[j].rt!=0 && p[j].at <= time){
                count_prq++;
                mintq = min( mintq, p[j].rt);
            }
        }
            
        time_quantum = mintq;	
        int count_inside = 0;
        while(count_inside < count_prq && remain != 0){
            if(p[i].rt<=time_quantum && p[i].rt>0) 
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            } 
            else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            }
            else if(p[i].rt>0) 
            { 
                p[i].rt-=time_quantum; 
                time+=time_quantum; 
                count_inside++;
            } 
            if(p[i].rt==0 && flag==1) 
            { 
                remain--; 
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tat=time-p[i].at;
                tot_wt+=p[i].wt; 
                tot_tat+=p[i].tat; 
                flag=0; 
                flag1[i] = 1;
            }  

            if(i==n-1) 
            {
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
            else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time2){
                int j=0; 
                int extra_var = 0;
                for(; j<=i; j++){
                    if(!flag1[j]){
                        extra_var = 1;
                        break;
                    } 
                }
                if(extra_var) i=j;
                else time++;
            } 
            else if(p[i+1].at<=time2) 
            i++; 
            else{
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
        }
        
    } 

    // output data in a separate file
    fstream fout;
    fout.open("irr_min_tq.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
    for(int i=0; i<n; i++)
        fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
    fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
    fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    fout.close();
    strcpy(algo[4].algo,"irr_min_tq");
    algo[4].avg_tat=(float)tot_tat/n;
    algo[4].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irr_min_tq_priority(int menu_flag) 
{
    cout<<"\nImproved ROund Robin with Dynamic Minimum Quantum Time priority \n";
    // time quantum will be the minimum remaining time quantum of a process in ready queue for particualr process with same priority
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0, time2; 
    vector<int> flag1(n,0);
    sort_priority();
    sort_arrival_time();  
    int mintq[50]; // minimum time quantum array for process with different priority
    for(int i=0,time=p[0].at; remain!=0;) 
    {   
        for(int i=0; i<50; i++){
            mintq[i] = 10000; // assign each process with a higher numbber then its burst time initially
        }
        time2 = time; // for coding purpose
        int count_prq = 0;
        for(int j=0; j<n; j++){
            if(p[j].rt!=0 && p[j].at <= time){
                count_prq++;
                mintq[(p[j].priority) - 1] = min( mintq[(p[j].priority)-1] , p[j].rt);
            }
        }
            
        int count_inside = 0; // for coding purpose
        while(count_inside < count_prq && remain != 0){
            time_quantum = mintq[(p[i].priority) - 1];
            if(p[i].rt<=time_quantum && p[i].rt>0) 
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            } 
            else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
            { 
                time+=p[i].rt; 
                p[i].rt=0; 
                flag=1; 
                count_inside++;
            }
            else if(p[i].rt>0) 
            { 
                p[i].rt-=time_quantum; 
                time+=time_quantum; 
                count_inside++;
            } 
            if(p[i].rt==0 && flag==1) 
            { 
                remain--; 
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tat=time-p[i].at;
                tot_wt+=p[i].wt; 
                tot_tat+=p[i].tat; 
                flag=0; 
                flag1[i] = 1;
            }  
            else if(p[i].rt != 0 && p[i].at <= time2){
                if(p[i].priority != 1){
                    p[i].priority--;
                }
            }
            if(i==n-1) 
            {
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
            else if(p[i].rt == 0 && flag == 0 && p[i+1].at > time2){
                int j=0; 
                int extra_var = 0;
                for(; j<=i; j++){
                    if(!flag1[j]){
                        extra_var = 1;
                        break;
                    } 
                }
                if(extra_var) i=j;
                else time++;
            } 
            else if(p[i+1].at<=time2) 
            i++; 
            else{
                int j = i;
                for(j=0; j<n; j++){
                    if(!flag1[j]) break;
                }
                i = j;
            }
        }
        
    } 

    // output data in a separate file
    fstream fout;
    fout.open("irr_min_tq_priority.csv", ios::out | ios::trunc);
    fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<","<<"Priority"<<"\n";
    for(int i=0; i<n; i++)
        fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<","<<p[i].priority2<<"\n";
    fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
    fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    fout.close();
    strcpy(algo[11].algo,"irr_min_tq_priority");
    algo[11].avg_tat=(float)tot_tat/n;
    algo[11].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irrsjf(int menu_flag)
{
        cout<<"\nImporved Roubd Robin Shortest Job First Static Time Quantum  \n";
        // shortest job executed first, dynamicall the arrays are sorted by remainig time
        assign();
        int time_quantum,tot_tat=0, tot_wt=0, time2;
        int remain=n;
        sort_arrival_time();                   
        int time=p[0].at;
        
        cout<<"\nEnter Time Quantum : "; 
        cin>>time_quantum;

        while(remain>0)
        {
            // sort according to the remaining time for each process dynamically
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n-i-1;j++)
                {
                    if(p[j].rt>p[j+1].rt)
                    {
                        temp=p[j+1];
                        p[j+1]=p[j];
                        p[j]=temp;
                    }	
                }
            }
            time2 = time;
            int flag1 = 0;
            for(int i=0;i<n;i++) 
            {

                if(p[i].at<=time2 && p[i].rt!=0)
                {   
                    flag1 = 1;
                    if(p[i].rt<=time_quantum && p[i].rt!=0)
                    {
                        time+=p[i].rt;
                        p[i].rt=0;
                    }
                    else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
                    { 
                        time+=p[i].rt; 
                        p[i].rt=0;  
                    }
                    else
                    {
                        time+=time_quantum;
                        p[i].rt-=time_quantum;
                    }
                    
                    if(p[i].rt==0)
                    {
                        p[i].wt=time-p[i].bt-p[i].at;
                        p[i].tat=time-p[i].at;
                        remain--;
                    }
                }
            }
            if(!flag1) time++;
        }
        for(int i=0; i<n; i++)
        {
            tot_wt += p[i].wt;
            tot_tat += p[i].tat; 
        }

        // output data in a separate file
        fstream fout;
        fout.open("irr_sjf.csv", ios::out | ios::trunc);
        fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[5].algo,"irr_sjf");
        algo[5].avg_tat=(float)tot_tat/n;
        algo[5].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void irrsjf_priority(int menu_flag)
{
        cout<<"\nImporved Roubd Robin Shortest Job First Static Time Quantum with priority \n";
        // shortest job executed first, dynamicall the arrays are sorted by remainig time priority wise
        assign();
        int time_quantum,tot_tat=0, tot_wt=0, time2;
        int remain=n;
        sort_arrival_time();                   
        sort_priority();
        int time=p[0].at;

        int tq[50];
        for(int i=0; i<5; i++){
            tq[i] = 50 - i;
        }

        while(remain>0)
        {
            // sort according to remaining time quantum of each process dynamically
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n-i-1;j++)
                {
                    if(p[j].priority == p[j+1].priority && p[j].rt>p[j+1].rt)
                    {
                        temp=p[j+1];
                        p[j+1]=p[j];
                        p[j]=temp;
                    }	
                }
            }
            time2 = time;
            int flag1 = 0;
            for(int i=0;i<n;i++) 
            {
                int time_quantum = tq[(p[i].priority) - 1];

                if(p[i].at<=time2 && p[i].rt!=0)
                {   
                    flag1 = 1;
                    if(p[i].rt<=time_quantum && p[i].rt!=0)
                    {
                        time+=p[i].rt;
                        p[i].rt=0;
                    }
                    else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
                    { 
                        time+=p[i].rt; 
                        p[i].rt=0;  
                    }
                    else
                    {
                        time+=time_quantum;
                        p[i].rt-=time_quantum;
                    }
                    
                    if(p[i].rt==0)
                    {
                        p[i].wt=time-p[i].bt-p[i].at;
                        p[i].tat=time-p[i].at;
                        remain--;
                    }
                    else if(p[i].rt != 0){
                        if(p[i].priority != 1){
                            p[i].priority--;
                        }
                    }
                }
            }
            if(!flag1) time++;
        }
        for(int i=0; i<n; i++)
        {
            tot_wt += p[i].wt;
            tot_tat += p[i].tat; 
        }

        // output data in a separate file
        fstream fout;
        fout.open("irr_sjf_priority.csv", ios::out | ios::trunc);
        fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<","<<"Priority\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<","<<p[i].priority2<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[12].algo,"irr_sjf_priority");
        algo[12].avg_tat=(float)tot_tat/n;
        algo[12].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void arr(int menu_flag)
{   
        cout<<"\nAdaptive Round Robin with Shortest Job First with Dynamic Quantum Time \n";
        // time quantum 
        // if ready queue size is odd -> tq = remianing time of middle process in ready queue
        // if ready queue size is even -> tq = mean of remaining time of process in readu queue
        assign();
        int time_quantum;
        int tot_tat=0, tot_wt=0;
        int remain=n;
        sort_arrival_time();
        int time=p[0].at;
        int sum_bt,prq; //

        for(int i=0;i<n;i++){
            p[i].rt=p[i].bt;
        }

        while(remain>0)
        {
            // sort according to remaining time quantum of each process dynamically
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n-i-1;j++)
                {
                    if(p[j].rt>p[j+1].rt)
                    {
                        temp=p[j+1];
                        p[j+1]=p[j];
                        p[j]=temp;
                    }
                }	
            }
            int flag1 = 0;
            int time2 = time;
            prq=0;  // number of elements in ready queue
            sum_bt=0; // sum of remaining time of process in ready queue
            for(int j=0;j<n;j++)
            {
                if(p[j].at<=time && p[j].rt!=0)
                {
                    prq++;
                    sum_bt+=p[j].rt;
                }
            }

            if(prq==0 ||  (sum_bt/prq) == 0){
                time++;
                continue;
            }
            if(prq%2==0) // even size
            {
                time_quantum = sum_bt/prq;
            }
            else // odd size
            {
                int i=0;
                int j=0;
                if(prq==1){
                    while(p[i].at<=time && p[i].rt==0)
                        i++;
                    time_quantum = p[i].rt;
                }
                else
                {
                    while(j<(prq)/2 && i<n)
                    {
                        if(p[i].at<=time && p[i].rt!=0){
                            j++;
                        }
                        i++;
                    }
                    time_quantum = p[i].rt;
                }
            }

            for(int i=0;i<n;i++)
            {
                if(p[i].at<=time2 && p[i].rt!=0)
                {   
                    flag1 = 1;
                    if(p[i].rt<time_quantum && p[i].rt!=0)
                    {
                        time+=p[i].rt;
                        p[i].rt=0;
                        //cout<<p[i].p<<endl;
                    }
                    else
                    {
                        time+=time_quantum;
                        p[i].rt-=time_quantum;
                    }
                    
                    if(p[i].rt==0)
                    {
                        p[i].wt=time-p[i].bt-p[i].at;
                        p[i].tat=time-p[i].at;
                        remain--;
                    }
                }
            }
            if(!flag1) time++;
        }

        for(int i=0; i<n; i++)
        {
            tot_wt += p[i].wt;
            tot_tat += p[i].tat; 
        }

        // output data in a separate file
        fstream fout;
        fout.open("arr_sjf_dtq.csv", ios::out | ios::trunc);
        fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[8].algo,"arr_sjf_dtq");
        algo[8].avg_tat=(float)tot_tat/n;
        algo[8].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void irrsjfdtq(int menu_flag)
{
        cout<<"\nImproved Round Robin Shortest Job First with Dynamic Quantum Time \n";
        // time quantum = (mean + maximum remaining time of processes in ready queue)/2
        // process in ready queue sorted according to shortest remaining time first
        assign();
        int time_quantum;
        int tot_tat=0, tot_wt=0;
        int remain=n;
        sort_arrival_time();
        int time=p[0].at;
        // max_bt , sun_bt, prq, to calculate time quantum
        int max_bt;
        int sum_bt,prq; 
        int old_mean=0; //for coding purpose
        
        for(int i=0; i<n; i++)
        {	
            p[i].rt=p[i].bt;
            old_mean+=p[i].bt;
        }
        old_mean/=n;
        while(remain>0)
        {
            // sort according to remaining time quantum of each process dynamically
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n-i-1;j++)
                {
                    if(p[j].rt>p[j+1].rt)
                    {
                        temp=p[j+1];
                        p[j+1]=p[j];
                        p[j]=temp;
                    }
                }	
            }
            int flag1 = 0;
            int time2 = time;
            prq=0;  
            max_bt=0;
            sum_bt=0;
            for(int j=0;j<n;j++)
            {
                if(p[j].at<=time && p[j].rt!=0)
                {
                    prq++;
                    if(p[j].rt>max_bt)
                        max_bt=p[j].rt;
                    sum_bt+=p[j].rt;
                }
            }
            if(prq==0 ||  (sum_bt/prq) == 0){
                time_quantum = old_mean;
                time++;
                continue;
            }
            else
            {
                time_quantum=((sum_bt/prq + max_bt)/2);
                old_mean = time_quantum;
            }

            for(int i=0;i<n;i++)
            {
                if(p[i].at<=time2 && p[i].rt!=0)
                {   
                    flag1 = 1;
                    if(p[i].rt<time_quantum && p[i].rt!=0)
                    {
                        time+=p[i].rt;
                        p[i].rt=0;
                    }
                    else
                    {
                        time+=time_quantum;
                        p[i].rt-=time_quantum;
                    }
                    
                    if(p[i].rt==0)
                    {
                        p[i].wt=time-p[i].bt-p[i].at;
                        p[i].tat=time-p[i].at;
                        remain--;
                    }
                }
            }
            if(!flag1) time++;
        }
        for(int i=0; i<n; i++)
        {
            tot_wt += p[i].wt;
            tot_tat += p[i].tat; 
        }

        // output data in a separate file
        fstream fout;
        fout.open("irr_sjf_dtq.csv", ios::out | ios::trunc);
        fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[6].algo,"irr_sjf_dtq");
        algo[6].avg_tat=(float)tot_tat/n;
        algo[6].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void irrsjfdtq_priority(int menu_flag)
{
        cout<<"\nImproved Round Robin Shortest Job First with Dynamic Quantum Time with priority \n";
        // time quantum = (mean + maximum remaining time of processes in ready queue)/2
        // process in ready queue sorted according to shortest remaining time first and priority also
        assign();
        int time_quantum;
        int tot_tat=0, tot_wt=0;
        int remain=n;
        sort_priority();
        sort_arrival_time();
        int time=p[0].at;
        // all the below arrays are used to calculate time quantum
        int tq[50];
        int sum[50]; 
        int maxm[50];
        int count[50];
        
        for(int i=0; i<n; i++)
        {	
            p[i].rt=p[i].bt;
        }
        while(remain>0)
        {
            // sort according to remaining time quantum of each process dynamically also considering the priority of processes
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n-i-1;j++)
                {
                    if(p[j].priority == p[j+1].priority && p[j].rt>p[j+1].rt) // sort acc to priority and shortest remaining time 
                    {
                        temp=p[j+1];
                        p[j+1]=p[j];
                        p[j]=temp;
                    }
                }	
            }
            int flag1 = 0;
            int time2 = time;
            memset(sum,0,sizeof(sum));
            memset(maxm,0,sizeof(maxm));
            memset(count,0,sizeof(count));
            for(int j=0;j<n;j++)
            {
                if(p[j].at<=time && p[j].rt!=0)
                {
                    count[(p[j].priority)-1]++;
                    maxm[(p[j].priority)-1] = max(maxm[(p[j].priority)-1], p[j].rt);
                    sum[(p[j].priority) - 1] += p[j].rt;
                }
            }
            
                for(int i=0; i<50; i++){
                    if(count[i] == 0){
                        tq[i] = 0;
                    }
                    else{
                        tq[i] = (sum[i]/count[i] + maxm[i])/2;
                    }
                }
            for(int i=0;i<n;i++)
            {
                time_quantum=tq[p[i].priority-1];
                if(p[i].at<=time2 && p[i].rt!=0)
                {   
                    flag1 = 1;
                    if(p[i].rt<time_quantum && p[i].rt!=0)
                    {
                        time+=p[i].rt;
                        p[i].rt=0;
                    }
                    else
                    {
                        time+=time_quantum;
                        p[i].rt-=time_quantum;
                    }
                    
                    if(p[i].rt==0)
                    {
                        p[i].wt=time-p[i].bt-p[i].at;
                        p[i].tat=time-p[i].at;
                        remain--;
                    }
                    else if(p[i].rt != 0 && p[i].at <= time2){
                        if(p[i].priority != 1){
                            p[i].priority--;
                        }
                    }
                }
            }
            if(!flag1) time++;
        }
        for(int i=0; i<n; i++)
        {
            tot_wt += p[i].wt;
            tot_tat += p[i].tat; 
        }

        // output data in a separate file
        fstream fout;
        fout.open("irr_sjf_dtq_priority.csv", ios::out | ios::trunc);
        fout<<"Process"<<","<<"Burst Time"<<","<<"Arrival Time"<<","<<"Waiting Time"<<","<<"Turn Around Time"<<","<<"Priority"<<"\n";
        for(int i=0; i<n; i++)
            fout<<p[i].p<<","<<p[i].bt<<","<<p[i].at<<","<<p[i].wt<<","<<p[i].tat<<","<<p[i].priority2<<"\n";
        fout<<"\nAverage Waiting Time = "<<(float)tot_wt/n<<"\n";
        fout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
        fout.close();
        strcpy(algo[13].algo,"irr_sjf_dtq_priority");
        algo[13].avg_tat=(float)tot_tat/n;
        algo[13].avg_wt=(float)tot_wt/n;
        if(menu_flag)
            menu();
}

void comparator()
{
        // comparison function...compares outputs of all the results of all the functions
        rr(0);
        irr(0);
        irr_mean_tq(0);
        irr_min_tq(0);
        irrsjf(0);
        irrsjfdtq(0);
        amrr(0);
        arr(0);
        rr_priority(0);
        irr_mean_tq_priority(0);
        irr_min_tq_priority(0);
        irrsjf_priority(0);
        irrsjfdtq_priority(0);
        fstream fout;
        fout.open("comparatoroutput.csv", ios::out | ios::trunc);
        fout<<"Algorithm"<<","<<"AVG_wt"<<","<<"AVG_TAT"<<"\n";
        for(int i=1; i<9; i++)
            if(strlen(algo[i].algo)>4)
                fout<<algo[i].algo<<","<<algo[i].avg_wt<<","<<algo[i].avg_tat<<"\n";
            else	
                fout<<algo[i].algo<<","<<algo[i].avg_wt<<","<<algo[i].avg_tat<<"\n";
        fout.close();
        //fstream fout;
        fout.open("comparatoroutput1.csv", ios::out | ios::trunc);
        fout<<"Algorithm"<<","<<"AVG_wt"<<","<<"AVG_TAT"<<"\n";
        for(int i=9; i<14; i++)
            if(strlen(algo[i].algo)>4)
                fout<<algo[i].algo<<","<<algo[i].avg_wt<<","<<algo[i].avg_tat<<"\n";
            else	
                fout<<algo[i].algo<<","<<algo[i].avg_wt<<","<<algo[i].avg_tat<<"\n";
        fout.close();
        menu();
}
