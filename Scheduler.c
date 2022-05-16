#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 

int swap(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = i; j < num; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                int temp = arrival_time[j];
                arrival_time[j] = arrival_time[i];
                arrival_time[i] = temp;
                temp = pid[j];
                pid[j] = pid[i];
                pid[i] = temp;
                temp = burst_time[j];
                burst_time[j] = burst_time[i];
                burst_time[i] = temp;
                temp = priority[j];
                priority[j] = priority[i];
                priority[i] = temp;
            }
        }
    }
}

//swap for SJF
int swapSJF(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = i; j < num; j++) {
            if (arrival_time[i] == arrival_time[j]) {
                if (burst_time[i] > burst_time[j]) {
                    int temp = arrival_time[j];
                    arrival_time[j] = arrival_time[i];
                    arrival_time[i] = temp;
                    temp = pid[j];
                    pid[j] = pid[i];
                    pid[i] = temp;
                    temp = burst_time[j];
                    burst_time[j] = burst_time[i];
                    burst_time[i] = temp;
                    temp = priority[j];
                    priority[j] = priority[i];
                    priority[i] = temp;
                }
            }
        }
    }
    for (int i = 0; i < num - 2; i++) {
        int sum = 0;
        for (int x = 0; x <= i; x++) {
            if (x == 0) {
                sum += arrival_time[x] + burst_time[x];
            }
            else {
                sum += burst_time[x];
            }
        }
        for (int j = i + 1; j < num - 1; j++) {
            for (int k = j + 1; k < num; k++) {
                if ((burst_time[j] > burst_time[k]) && sum >= arrival_time[k]) {
                    int temp = arrival_time[k];
                    arrival_time[k] = arrival_time[j];
                    arrival_time[j] = temp;
                    temp = pid[k];
                    pid[k] = pid[j];
                    pid[j] = temp;
                    temp = burst_time[k];
                    burst_time[k] = burst_time[j];
                    burst_time[j] = temp;
                    temp = priority[k];
                    priority[k] = priority[j];
                    priority[j] = temp;
                }
            }
        }
    }
}

int swapPriority(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = i; j < num; j++) {
            if (arrival_time[i] == arrival_time[j]) {
                if (priority[i] > priority[j]) {
                    int temp = arrival_time[j];
                    arrival_time[j] = arrival_time[i];
                    arrival_time[i] = temp;
                    temp = pid[j];
                    pid[j] = pid[i];
                    pid[i] = temp;
                    temp = burst_time[j];
                    burst_time[j] = burst_time[i];
                    burst_time[i] = temp;
                    temp = priority[j];
                    priority[j] = priority[i];
                    priority[i] = temp;
                }
            }
        }
    }
    for (int i = 0; i < num - 2; i++) {
        int sum = 0;
        for (int x = 0; x <= i; x++) {
            if (x == 0) {
                sum += arrival_time[x] + burst_time[x];
            }
            else {
                sum += burst_time[x];
            }
        }
        for (int j = i + 1; j < num - 1; j++) {
            for (int k = j + 1; k < num; k++) {
                if ((priority[j] > priority[k]) && sum >= arrival_time[k]) {
                    int temp = arrival_time[k];
                    arrival_time[k] = arrival_time[j];
                    arrival_time[j] = temp;
                    temp = pid[k];
                    pid[k] = pid[j];
                    pid[j] = temp;
                    temp = burst_time[k];
                    burst_time[k] = burst_time[j];
                    burst_time[j] = temp;
                    temp = priority[k];
                    priority[k] = priority[j];
                    priority[j] = temp;
                }
            }
        }
    }
}

int RRwaitingtime(int pid[], int arrival_time[], int burst_time[], int RRpid[], int RRburst_time[], int waiting_time[], int num, int RRnum, int timeallocation) {
    waiting_time[0] = arrival_time[0];
    int start_time[100];
    int run_time[100];
    for (int a = 0; a < num; a++) {
        start_time[a] = 0;
        run_time[a] = 0;
        for (int b = 0; b < RRnum; b++) {
            if (pid[a] == RRpid[b]) {
                start_time[a] = 0;
                for (int c = 0; c < b; c++) {
                    start_time[a] += RRburst_time[c];
                }
                run_time[a] += RRburst_time[b];
            }
        }
        int addfactor;
        if (burst_time[a] != 0) {
            addfactor = burst_time[a] % timeallocation;
            if (addfactor == 0) {
                addfactor = timeallocation;
            }
        }
        run_time[a] -= addfactor;
        printf("Start TIME: %d\n", start_time[a]);
        printf("Run TIME: %d\n", run_time[a]);
    }
    /*
    for (int i = 0; i < num; i++) {
        int temp = 0;
        int temp2 = 0;
        waiting_time[i] = 0;
        int count = 0;
        for (int j = 1; j < RRnum; j++) {
            if (pid[i] == RRpid[j] && i != j) {
                for (int k = i + 1; k < j; k++) {
                    waiting_time[i] += RRburst_time[k];
                    count++;
                    if (i == 5) {
                        printf("%d %d %d %d\n", pid[i], RRpid[j], i, j);
                    }
                }
                waiting_time[i] -= temp;
                temp = waiting_time[i] + RRburst_time[j] + temp2;
                temp2 += RRburst_time[j];
                printf("%d: %d\n", i, waiting_time[i]);
            }
        }
        if (count == 1) {
            waiting_time[i] = waiting_time[i] - burst_time[i];
        }
        */
    for (int i = 0; i < num; i++) {
        waiting_time[i] = start_time[i] - run_time[i] - arrival_time[i];
        printf("Final%d: %d\n", i, waiting_time[i]);
    }
    return 0;
}
//Calculate waitingtime
int waitingtime(int pid[], int arrival_time[], int burst_time[], int waiting_time[], int num) {
    waiting_time[0] = arrival_time[0];
    for (int i = 1; i < num; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1] + arrival_time[i - 1] - arrival_time[i];
    }
    return 0;
}

//Calculate turnaroundtime
int turnaroundtime(int pid[], int arrival_time[], int burst_time[], int waiting_time[], int turnaround_time[], int num) {
    for (int i = 0; i < num; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
    return 0;
}

int FCFS(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    printf("\n\nFCFS:\n");
    int waiting_time[100], turnaround_time[100];
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time    Priority      Response Time \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], priority[i]);
    }
    printf("Average waiting time = %.2f\n", (float)tot_wait / (float)num);
    printf("Average turnaround time = %.2f\n", (float)tot_turnaround / (float)num);
    printf("Average response time = ");
    return 0;
}

int SJF(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapSJF(pid, arrival_time, burst_time, priority, num);
    printf("\n\nSJF:\n");
    int waiting_time[100], turnaround_time[100];
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time    Priority      Response Time \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], priority[i]);
    }
    printf("Average waiting time = %.2f\n", (float)tot_wait / (float)num);
    printf("Average turnaround time = %.2f\n", (float)tot_turnaround / (float)num);
    printf("Average response time = ");
    return 0;
}

int RR(int pid[], int arrival_time[], int burst_time[], int priority[], int num, int timeallocation) {
    swap(pid, arrival_time, burst_time, priority, num);
    printf("\n\nRR:\n");
    int RRnum = 0;
    for (int a = 0; a < num; a++) {
        RRnum += (burst_time[a] + timeallocation - 1) / timeallocation;
    }
    int RRpid[100], RRburst_time[100];
    int temp_pid[100], temp2_pid[100], temp2_arrival_time[100], temp_burst_time[100], temp2_burst_time[100];
    int temp_num = num;
    int temp_num2 = num - 1;
    //Setup
    for (int b = 1; b < num; b++) {
        temp2_pid[b - 1] = pid[b];
        temp2_arrival_time[b - 1] = arrival_time[b];
        temp2_burst_time[b - 1] = burst_time[b];
    }
    int loc = 1;
    temp_pid[0] = pid[0];
    temp_burst_time[0] = burst_time[0];
    //All cases
    int pid_temp, burst_time_temp;
    for (int c = 0; c < RRnum; c++) {
        RRpid[c] = temp_pid[0];
        if (temp_burst_time[0] > timeallocation) {
            for (int z = 0; z < temp_num2; z++) {
                if (temp2_arrival_time[z] <= (c + 1) * timeallocation) {
                    temp_pid[loc] = temp2_pid[z];
                    temp_burst_time[loc] = temp2_burst_time[z];
                    for (int y = z; y < temp_num2 - 1; y++) {
                        temp2_pid[y] = temp2_pid[y + 1];
                        temp2_arrival_time[y] = temp2_arrival_time[y + 1];
                        temp2_burst_time[y] = temp2_burst_time[y + 1];
                    }
                    temp_num2--;
                    z--;
                    loc++;
                }
            }
            RRburst_time[c] = timeallocation;
            temp_burst_time[0] -= timeallocation;
            pid_temp = temp_pid[0];
            burst_time_temp = temp_burst_time[0];
            for (int d = 0; d < temp_num - 1; d++) {
                temp_pid[d] = temp_pid[d + 1];
                temp_burst_time[d] = temp_burst_time[d + 1];
            }
            temp_pid[temp_num - temp_num2 - 1] = pid_temp;
            temp_burst_time[temp_num - temp_num2 - 1] = burst_time_temp;
        }
        else {
            for (int z = 0; z < temp_num2; z++) {
                if (temp2_arrival_time[z] <= (c + 1) * timeallocation) {
                    temp_pid[loc] = temp2_pid[z];
                    temp_burst_time[loc] = temp2_burst_time[z];
                    for (int y = z; y < temp_num2 - 1; y++) {
                        temp2_pid[y] = temp2_pid[y + 1];
                        temp2_arrival_time[y] = temp2_arrival_time[y + 1];
                        temp2_burst_time[y] = temp2_burst_time[y + 1];
                    }
                    temp_num2--;
                    z--;
                    loc++;
                }
            }
            RRburst_time[c] = temp_burst_time[0];
            for (int d = 0; d < temp_num - 1; d++) {
                temp_pid[d] = temp_pid[d + 1];
                temp_burst_time[d] = temp_burst_time[d + 1];
            }
            temp_num--;
            loc--;
        }
        printf("Loc: %d %d %d %d %d %d %d", loc, temp_pid[0], temp_pid[1], temp_pid[2], temp_pid[3], temp_pid[4], temp_pid[5]);
        printf("\n");
    }

    printf("%d", RRnum);

    int waiting_time[100], turnaround_time[100];
    int tot_wait = 0, tot_turnaround = 0;
    RRwaitingtime(pid, arrival_time, burst_time, RRpid, RRburst_time, waiting_time, num, RRnum, timeallocation);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time\n");
    for (int i = 0; i < RRnum; i++) {
        printf(" %d\t\t%d\t\t\n", RRpid[i], RRburst_time[i]);
    }
    printf("Process ID   Waiting Time   Turnaround Time    Priority      Response Time \n");
    for (int i = 0; i < num; i++) {
        printf(" %d\t\t%d\t\t%d\t\t%d\n", pid[i], waiting_time[i], turnaround_time[i], priority[i]);
    }
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        //tot_turnaround = tot_turnaround + turnaround_time[i];
    }
    printf("Average waiting time = %.2f\n", (float)tot_wait / (float)num);
    printf("Average turnaround time = %.2f\n", (float)tot_turnaround / (float)num);
    printf("Average response time = ");
    return 0;
}


int Priority(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapPriority(pid, arrival_time, burst_time, priority, num);
    printf("\n\nPriority:\n");
    int waiting_time[100], turnaround_time[100];
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time    Priority      Response Time \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], priority[i]);
    }
    printf("Average waiting time = %.2f\n", (float)tot_wait / (float)num);
    printf("Average turnaround time = %.2f\n", (float)tot_turnaround / (float)num);
    printf("Average response time = ");
    return 0;
}

int main() {
    FILE* fptr;
    fptr = fopen("C:\\Users\\Gunho\\source\\repos\\Os Scheduling\\Os Scheduling\\text.txt", "r");
    if (fptr == NULL)
    {
        printf("File Not Found!");
        exit(1);
    }
    int num;
    fscanf(fptr, "%d\n", &num);
    int* pid, * arrival_time, * burst_time, * priority;
    pid = (int*)malloc(sizeof(int) * num);
    arrival_time = (int*)malloc(sizeof(int) * num);
    burst_time = (int*)malloc(sizeof(int) * num);
    priority = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        fscanf(fptr, "%d %d %d %d", &pid[i], &arrival_time[i], &burst_time[i], &priority[i]);
    }
    int timeallocation;
    fscanf(fptr, "%d", &timeallocation);
    FCFS(pid, arrival_time, burst_time, priority, num);
    SJF(pid, arrival_time, burst_time, priority, num);
    //SRTF(pid, arrival_time, burst_time, priority, num);
    RR(pid, arrival_time, burst_time, priority, num, timeallocation);
    Priority(pid, arrival_time, burst_time, priority, num);
    //PrePriority(pid, arrival_time, burst_time, priority, num)
    //PriorityRR(pid, arrival_time, burst_time, priority, num, timeallocation)
    fclose(fptr);
    return 0;
}

