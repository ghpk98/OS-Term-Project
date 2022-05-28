#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#pragma warning(disable :4996)

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
                int t = arrival_time[x + 1];
                while (t > arrival_time[x] + burst_time[x]) {
                    t--;
                    sum++;
                }
                sum += arrival_time[x] + burst_time[x];
            }
            else {
                int t = arrival_time[x + 1];
                while (t > arrival_time[x] + burst_time[x]) {
                    t--;
                    sum++;
                }
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
                int t = arrival_time[x + 1];
                while (t > arrival_time[x] + burst_time[x]) {
                    t--;
                    sum++;
                }
                sum += arrival_time[x] + burst_time[x];
            }
            else {
                int t = arrival_time[x + 1];
                while (t > arrival_time[x] + burst_time[x]) {
                    t--;
                    sum++;
                }
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

//Calculate waitingtime
int waitingtime(int pid[], int arrival_time[], int burst_time[], int waiting_time[], int num) {
    waiting_time[0] = 0;
    for (int i = 1; i < num; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1] + arrival_time[i - 1] - arrival_time[i];
        if (arrival_time[i] > arrival_time[i - 1] + waiting_time[i - 1] + burst_time[i - 1]) {
            waiting_time[i] = 0;
        }
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

int responsetime() {

}

int FCFS(char p[], int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    printf("\n\nFCFS:\n");
    int *waiting_time, *turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    FILE* ptr;
    ptr = fopen("FCFS.txt", "w");
//    fprintf(ptr, "%d \n", num);
    fprintf(ptr, "S E PROCESS \n");
    printf("Start Time   Burst Time   Process ID \n");
    for (int i = 0; i < num; i++) {
        printf("%d\t\t%d\t\t%d\n", arrival_time[i]+waiting_time[i], burst_time[i], pid[i]);
        fprintf(ptr, "%d %d %c%d \n", (arrival_time[i] + waiting_time[i]), burst_time[i], p[i], pid[i]);
    }
    fprintf(ptr, "- \n");
    printf("\n");
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//    fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int SJF(char p[], int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapSJF(pid, arrival_time, burst_time, priority, num);
    printf("\n\nSJF:\n");
    int* waiting_time, * turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    FILE* ptr;
    ptr = fopen("SJF.txt", "w");
//    fprintf(ptr, "%d \n", num);
    fprintf(ptr, "S E PROCESS \n");
    printf("Start Time   Burst Time   Process ID \n");
    for (int i = 0; i < num; i++) {
        printf("%d\t\t%d\t\t%d\n", arrival_time[i] + waiting_time[i], burst_time[i], pid[i]);
        fprintf(ptr, "%d %d %c%d \n", (arrival_time[i] + waiting_time[i]), burst_time[i], p[i], pid[i]);
    }
    fprintf(ptr, "- \n");
    printf("\n");
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//    fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int RR(char p[], int pid[], int arrival_time[], int burst_time[], int priority[], int num, int timeallocation) {
    swap(pid, arrival_time, burst_time, priority, num);
    printf("\n\nRR:\n");
    int RRnum = 0;
    for (int a = 0; a < num; a++) {
        RRnum += (burst_time[a] + timeallocation - 1) / timeallocation;
    }
    int *RRpid, *RRburst_time;
    RRpid = (int*)malloc(sizeof(int) * RRnum);
    RRburst_time = (int*)malloc(sizeof(int) * RRnum);
    int *temp_pid, *temp2_pid, *temp2_arrival_time, *temp_burst_time, *temp2_burst_time;
    temp_pid = (int*)malloc(sizeof(int) * num);
    temp2_pid = (int*)malloc(sizeof(int) * num);
    temp2_arrival_time = (int*)malloc(sizeof(int) * num);
    temp_burst_time = (int*)malloc(sizeof(int) * num);
    temp2_burst_time = (int*)malloc(sizeof(int) * num);
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
    int timecount = 0;
    int wait = 0;
    for (int c = 0; c < RRnum; c++) {
        RRpid[c] = temp_pid[0];
        int sum = 0;
        int idnum = RRpid[c];
        for (int a = 0; a < num; a++) {
            if (pid[a] == RRpid[c]) {
                for (int i = 0; i < c; i++) {
                    sum += RRburst_time[i];
                }
                sum += arrival_time[0];
                while (arrival_time[a] >= sum) {
                    sum++;
                    wait++;
                }
            }
            break;
        }

        if (temp_burst_time[0] > timeallocation) {
            timecount += timeallocation;
            int test = 0;
            for (int z = 0; z < temp_num2; z++) {
                if (temp2_arrival_time[z] <= timecount) {
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
                    test++;
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
            int test = 0;
            timecount += temp_burst_time[0];
            for (int z = 0; z < temp_num2; z++) {
                if (temp2_arrival_time[z] <= timecount) {
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
                    test=1;
                }
            }
            for (int i = 0; i < num; i++) {
                if (temp_pid[1] == pid[i]) {
                    test = 1;
                }
            }
            if (test == 0 && c < RRnum-1) {
                temp_pid[loc] = temp2_pid[0];
                temp_burst_time[loc] = temp2_burst_time[0];
                timecount = temp2_arrival_time[0];
                for (int y = 0; y < temp_num2 - 1; y++) {
                    temp2_pid[y] = temp2_pid[y + 1];
                    temp2_arrival_time[y] = temp2_arrival_time[y + 1];
                    temp2_burst_time[y] = temp2_burst_time[y + 1];
                }
                temp_num2--;
                loc++;
                test++;
            }
            RRburst_time[c] = temp_burst_time[0];
            for (int d = 0; d < temp_num - 1; d++) {
                temp_pid[d] = temp_pid[d + 1];
                temp_burst_time[d] = temp_burst_time[d + 1];
            }
            temp_num--;
            loc--;
        }
    }
    int* waiting_time, * turnaround_time, * response_time, *total;
    int total2[500];
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    response_time = (int*)malloc(sizeof(int) * num);
    total = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
    FILE* ptr;
    ptr = fopen("RR.txt", "w");
//    fprintf(ptr, "%d \n", num);
    fprintf(ptr, "S E PROCESS \n");
    printf("Start Time   Burst Time   Process ID \n");
    total[0] = arrival_time[0];
    for (int i = 0; i < RRnum; i++) {
        int j = 0;
        if (i > 0) {
            total[i] = total[i - 1];
        }
        for (j; j < num; j++) {
            if (RRpid[i] == pid[j]) {
                while (arrival_time[j] > total[i]) {
                    total[i] += 1;
                }
                break;
            }
        }
        fprintf(ptr, "%d %d %c%d \n", total[i], RRburst_time[i], p[0], RRpid[i]);
        printf("%d\t\t%d\t\t%d\n", total[i], RRburst_time[i], RRpid[i]);
        total[i] += RRburst_time[i];
        total2[i] = total[i];
    }
    int* start_time, * run_time, * blank, * start, * end;
    start_time = (int*)malloc(sizeof(int) * num);
    run_time = (int*)malloc(sizeof(int) * num);
    blank = (int*)malloc(sizeof(int) * num);
    start = (int*)malloc(sizeof(int) * num);
    end = (int*)malloc(sizeof(int) * num);
    waiting_time[0] = 0;
    for (int i = 0; i < num; i++) {
        int count = 0;
        start[i] = 0;
        end[i] = 0;
        run_time[i] = burst_time[i];
        int j = -1;
        while (run_time[i] > 0 && j < RRnum - 1) {
            j++;
            if (pid[i] == RRpid[j]) {
                if (count == 0) {
                    start[i] = total2[j] - RRburst_time[j];
                    response_time[i] = start[i] - arrival_time[i];
                    count++;
                }
                run_time[i] -= RRburst_time[j];
            }
        }
        end[i] = total2[j];
        int burst_sum = 0;
        blank[i] = 0;
        for (int a = 0; a < j; a++) {
            burst_sum += RRburst_time[a];
        }
        while (arrival_time[i] > burst_sum) {
            blank[i]++;
            burst_sum++;
        }
    }
    for (int i = 0; i < num; i++) {
        waiting_time[i] = end[i] - burst_time[i] - arrival_time[i];
    }
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("\n");
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    fprintf(ptr, "- \n");
    for (int i = 0; i < num; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i], priority[i]);
    }
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        tot_response = tot_response + response_time[i];
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;
    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//    fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int Priority(char p[], int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapPriority(pid, arrival_time, burst_time, priority, num);
    printf("\n\nPriority:\n");
    int* waiting_time, * turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    FILE* ptr;
    ptr = fopen("Priority.txt", "w");
//    fprintf(ptr, "%d \n", num);
    fprintf(ptr, "S E PROCESS \n");
    printf("Start Time   Burst Time   Process ID \n");
    for (int i = 0; i < num; i++) {
        printf("%d\t\t%d\t\t%d\n", arrival_time[i] + waiting_time[i], burst_time[i], pid[i]);
        fprintf(ptr, "%d %d %c%d \n", (arrival_time[i] + waiting_time[i]), burst_time[i], p[i], pid[i]);
    }
    fprintf(ptr, "- \n");
    printf("\n");
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//   fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int PriorityRR(char p[], int pid[], int arrival_time[], int burst_time[], int priority[], int num, int timeallocation) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapPriority(pid, arrival_time, burst_time, priority, num);
    printf("\n\nPriorityRR:\n");
    int RRnum = 0;
    int* temp_pid,  * temp_burst_time, * temp_arrival_time, * temp_priority;
    temp_pid = (int*)malloc(sizeof(int) * num);
    temp_burst_time = (int*)malloc(sizeof(int) * num);
    temp_arrival_time = (int*)malloc(sizeof(int) * num);
    temp_priority = (int*)malloc(sizeof(int) * num);
    int RRpid[100], RRburst_time[100], temp2_pid[100], temp2_burst_time[100];
    int temp_num = num;
    int temp_num2 = num - 1;
    int total[100];
    //Setup
    for (int a = 0; a < num; a++) {
        temp_pid[a] = pid[a];
        temp_arrival_time[a] = arrival_time[a];
        temp_burst_time[a] = burst_time[a];
        temp_priority[a] = priority[a];
    }
    int x = 0;
    int time = arrival_time[0];
    while(temp_num > 0) {
        int count = 0;
        for (int j = 1; j <= temp_num; j++) {
            if (temp_num != 1) {
                if (temp_priority[0] == temp_priority[j] && temp_arrival_time[j] <= time) {
                    if (count == 0) {
                        time += temp_burst_time[0];
                        temp2_pid[0] = temp_pid[0];
                        temp2_burst_time[0] = temp_burst_time[0];
                    }
                    count++;
                    time += temp_burst_time[j];
                    temp2_pid[count] = temp_pid[j];
                    temp2_burst_time[count] = temp_burst_time[j];
                    for (int d = j; d < temp_num; d++) {
                        temp_pid[d] = temp_pid[d + 1];
                        temp_arrival_time[d] = temp_arrival_time[d + 1];
                        temp_burst_time[d] = temp_burst_time[d + 1];
                        temp_priority[d] = temp_priority[d + 1];
                    }
                    temp_num--;
                }
            }
        }
        if (count == 0) {
            RRpid[x] = temp_pid[0];
            RRburst_time[x] = temp_burst_time[0];
            x++;
            time += temp_burst_time[0];
            for (int d = 0; d < temp_num-1; d++) {
                temp_pid[d] = temp_pid[d + 1];
                temp_arrival_time[d] = temp_arrival_time[d+1];
                temp_burst_time[d] = temp_burst_time[d+1];
                temp_priority[d] = temp_priority[d+1];
            }
            temp_num--;
            RRnum++;
        }
        else {
            int total = 0;
            for (int z = 0; z <= count; z++) {
                total += (temp2_burst_time[z] + timeallocation - 1) / timeallocation;

            }
            for (int y = 0; y < total; y++) {
                RRnum++;
                RRpid[x] = temp2_pid[y];
                if (temp2_burst_time[y] > timeallocation) {

                    RRburst_time[x] = timeallocation;
                    temp2_burst_time[y] -= timeallocation;
                    x++;
                    temp2_pid[y + count+1] = temp2_pid[y];
                    temp2_burst_time[y+count+1] = temp2_burst_time[y];
                }
                else {
                    RRburst_time[x] = temp2_burst_time[y];
                    for (int g = y; g < y + count; g++) {
                        temp2_burst_time[g] = temp2_burst_time[g + 1];
                        temp2_pid[g] = temp2_pid[g + 1];

                    }
                    count--;
                    x++;
                }
            }
            for (int d = 0; d < temp_num - 1; d++) {
                temp_pid[d] = temp_pid[d + 1];
                temp_arrival_time[d] = temp_arrival_time[d + 1];
                temp_burst_time[d] = temp_burst_time[d + 1];
                temp_priority[d] = temp_priority[d + 1];
            }
            temp_num = temp_num - 1;
        }
    }

    int* waiting_time, * turnaround_time, * response_time, * total1;
    int total2[500];
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    response_time = (int*)malloc(sizeof(int) * num);
    total1 = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
    FILE* ptr;
    ptr = fopen("PriorityRR.txt", "w");
//    fprintf(ptr, "%d\n", num);
    fprintf(ptr, "S E PROCESS \n");
    printf("Start Time   Burst Time   Process ID \n");
    total1[0] = arrival_time[0];
    for (int i = 0; i < RRnum; i++) {
        int j = 0;
        if (i > 0) {
            total1[i] = total1[i - 1];
        }
        for (j; j < num; j++) {
            if (RRpid[i] == pid[j]) {
                while (arrival_time[j] > total1[i]) {
                    total1[i] += 1;
                }
                break;
            }
        }
        fprintf(ptr, "%d %d %c%d \n", total1[i], RRburst_time[i], p[0], RRpid[i]);
        printf("%d\t\t%d\t\t%d\n", total1[i], RRburst_time[i], RRpid[i]);
        total1[i] += RRburst_time[i];
        total2[i] = total1[i];
    }
    int* start_time, * run_time, * blank, * start, * end;
    start_time = (int*)malloc(sizeof(int) * num);
    run_time = (int*)malloc(sizeof(int) * num);
    blank = (int*)malloc(sizeof(int) * num);
    start = (int*)malloc(sizeof(int) * num);
    end = (int*)malloc(sizeof(int) * num);
    waiting_time[0] = 0;

    for (int i = 0; i < num; i++) {
        int count = 0;
        start[i] = 0;
        end[i] = 0;
        run_time[i] = burst_time[i];
        int j = -1;
        while (run_time[i] > 0 && j < RRnum - 1) {
            j++;
            if (pid[i] == RRpid[j]) {
                if (count == 0) {
                    start[i] = total2[j] - RRburst_time[j];
                    response_time[i] = start[i] - arrival_time[i];
                    count++;
                }
                run_time[i] -= RRburst_time[j];
            }
        }
        end[i] = total2[j];
        int burst_sum = 0;
        blank[i] = 0;
        for (int a = 0; a < j; a++) {
            burst_sum += RRburst_time[a];
        }
        while (arrival_time[i] > burst_sum) {
            blank[i]++;
            burst_sum++;
        }
    }
    for (int i = 0; i < num; i++) {
        waiting_time[i] = end[i] - burst_time[i] - arrival_time[i];
    }
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    fprintf(ptr, "-\n");
    printf("\n");
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    for (int i = 0; i < num; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i], priority[i]);
    }
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        tot_response = tot_response + response_time[i];
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;

    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f\n", avg_turnaround);
//    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int minvalue_arr(int arr[], int arrival_time[], int complete[], int num, int fin_t) {
    //returns index of minimum value in array
        //arr can be either priority or remaining time
    int i, min;
    int min_idx = -1;
    for (i = 0; i < num; i++) {
        if (complete[i] == 0 && (arrival_time[i] <= fin_t)) {
            min = arr[i];
            min_idx = i;
            break;
        }
    }	//set min_idx to any pid that is incomplete & already arrived before/at fin_t

    for (i = 0; i < num; i++) {
        if ((complete[i] == 0) && (arrival_time[i] <= fin_t)) {
            if (min > arr[i]) {
                min = arr[i];
                min_idx = i;
                //printf("minvalue1: [min_idx] = %d \n", min_idx);
            }
            else if ((min == arr[i]) && (arrival_time[i] < arrival_time[min_idx])) {
                min = arr[i];
                min_idx = i;
            }
        }
    }

    return min_idx;
    //min_idx == -1 when all processes are complete  OR when CPU becomes idle (completed all processes up to given time)
}

int SRTF(char* p, int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);

    int i, completed = 0;
    int processed_t;
    int now_running = 0, t = 0;
    int remaining_t[200], complete[200], wait_t[200], wait_start[200], first_processed_start_t[200];
    for (i = 0; i < num; i++) {
        remaining_t[i] = burst_time[i];
        complete[i] = 0;
        wait_t[i] = 0;
        wait_start[i] = arrival_time[i];
        first_processed_start_t[i] = 0;
    }
    int start_t = arrival_time[0], fin_t = arrival_time[0];	//when first process starts after 0
    FILE* ptr;
    ptr = fopen("SRTF.txt", "w");
//    fprintf(ptr, "%d \n", num);
    printf("S E PROCESS \n");
    fprintf(ptr, "S E PROCESS \n");
    printf("\n\nSRTF:\n");

    first_processed_start_t[now_running] = arrival_time[now_running];
    //compare current process & new arrivals
    for (i = 1; i < num; i++) {

        if (now_running == i)	//CPU was idle until this process came.
            continue;

        if ((remaining_t[now_running] > arrival_time[i] - start_t)) {	//new arrival before finishing current process			
            processed_t = arrival_time[i] - fin_t;
            remaining_t[now_running] -= processed_t;
            fin_t += processed_t;
            if (remaining_t[now_running] > remaining_t[i]) {	//preemptive switch

                wait_start[now_running] = arrival_time[i];	//count wait time from this point in time
                wait_t[i] += fin_t - arrival_time[i];

                printf("%d\t\t%d\t\t%c%d \n", start_t, arrival_time[i], p[now_running], pid[now_running]);
                fprintf(ptr, "%d %d %c%d \n", start_t, arrival_time[i], p[now_running], pid[now_running]);
                fin_t = arrival_time[i];	//update finish time
                now_running = i;
                start_t = arrival_time[i];	//start of new process
                first_processed_start_t[now_running] = arrival_time[i];	//to calculate response time
            }
            else	//continue with original process		
                continue;
        }
        else {		//끝나고 새 process 도착.  또는 새 프로세스 도착 전에 수행 완료
            fin_t += remaining_t[now_running];
            first_processed_start_t[now_running] = arrival_time[now_running];

            printf("%d\t\t%d\t\t%d \n", start_t, fin_t, pid[now_running]);
            fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

            remaining_t[now_running] = 0;
            complete[now_running] = 1;	//completed process
            completed++;
            if (completed == num)
                break;
            //find idx of process w/ least remaining time
            if ((fin_t < arrival_time[i]) && (completed == i)) {
                now_running = i;
                fin_t = arrival_time[i];	//idle cpu from end of prev process to arrival of i
            }
            else
                now_running = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t);


            if (now_running != -1) {	//start processing w/o delay
                start_t = fin_t;	//start_t of new process
                wait_t[now_running] += start_t - wait_start[now_running];
                first_processed_start_t[now_running] = start_t;
            }
            else if ((now_running == -1) && (i != num - 1)) {		//CPU is idle until next process comes
                start_t = arrival_time[i + 1];
                now_running = i + 1;
            }
        }
    }
    //all processes have arrived and been evaluated. behaves like SJF from now
        //여기서부턴 SJF 처럼

    fin_t += remaining_t[now_running];
    printf("%d\t\t%d\t\t%d \n", start_t, fin_t, pid[now_running]);
    fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

    if (burst_time[now_running] == remaining_t[now_running])
        first_processed_start_t[now_running] = start_t; //	

    remaining_t[now_running] = 0;
    complete[now_running] = 1;	//completed process
    completed++;

    while (completed != num) {
        start_t = fin_t;
        now_running = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t);
        wait_t[now_running] += start_t - wait_start[now_running];

        fin_t = start_t + remaining_t[now_running];
        if (burst_time[now_running] == remaining_t[now_running])
            first_processed_start_t[now_running] = start_t;
        remaining_t[now_running] = 0;
        complete[now_running] = 1;	//completed process
        completed++;

        printf("%d\t\t%d\t\t%d \n", start_t, fin_t, pid[now_running]);
        fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

        start_t = fin_t;
    }

    //avg waiting time, turnaround time, response time.
    int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
    for (i = 0; i < num; i++) {
        tot_wait += wait_t[i];
        tot_turnaround += burst_time[i] + wait_t[i];
        tot_response += first_processed_start_t[i] - arrival_time[i];
    }
    //response time: when process was processed by CPU for the first time?
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;

    fprintf(ptr, "- \n");
    for (i = 0; i < num; i++) {
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], wait_t[i], burst_time[i] + wait_t[i], first_processed_start_t[i] - arrival_time[i], priority[i]);
    }


    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//    fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);

    fclose(ptr);
    return 0;
}

int PrePriority(char* p, int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);

    int i, now_running = 0, completed = 0;
    int processed_t;
    int t = 0;
    int remaining_t[200], complete[200], wait_t[200], wait_start[200], first_processed_start_t[200];
    for (i = 0; i < num; i++) {
        remaining_t[i] = burst_time[i];
        complete[i] = 0;
        wait_t[i] = 0;
        wait_start[i] = arrival_time[i];
        first_processed_start_t[i] = 0;
    }
    int start_t = arrival_time[0], fin_t = arrival_time[0];	//when first process starts after 0

    FILE* ptr;
    ptr = fopen("PrePriority.txt", "w");
    printf("\n\nPrePriority:\n");
//    fprintf(ptr, "%d \n", num);
    printf("S E PROCESS \n");
    fprintf(ptr, "S E PROCESS \n");
    first_processed_start_t[now_running] = arrival_time[now_running];
    for (i = 1; i < num; i++) {
        if (now_running == i)	//CPU was idle until this process came.
            continue;
        if ((remaining_t[now_running] > arrival_time[i] - start_t)) {	//new arrival before finishing current process			
            processed_t = arrival_time[i] - fin_t;
            remaining_t[now_running] -= processed_t;
            fin_t += processed_t;
            if (priority[now_running] > priority[i]) {	//preemptive switch
                wait_start[now_running] = arrival_time[i];	//count wait time from this point in time
                wait_t[i] += fin_t - arrival_time[i];

                printf("%d\t\t%d\t\t%d \n", start_t, arrival_time[i], pid[now_running]);
                fprintf(ptr, "%d %d %c%d \n", start_t, arrival_time[i], p[now_running], pid[now_running]);

                fin_t = arrival_time[i];	//update finish time
                now_running = i;
                start_t = arrival_time[i];	//start of new process
                first_processed_start_t[now_running] = arrival_time[i];	//to calculate response time
            }
            else	//continue with original process		
                continue;
        }
        else {		//끝나고 새 process 도착.  또는 새 프로세스 도착 전에 수행 완료
            fin_t += remaining_t[now_running];
            first_processed_start_t[now_running] = arrival_time[now_running];

            printf("%d\t\t%d\t\t%d \n", start_t, fin_t, pid[now_running]);
            fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

            remaining_t[now_running] = 0;
            complete[now_running] = 1;	//completed process
            completed++;
            if (completed == num)
                break;

            //find idx of process w/ highest priority
            if ((fin_t < arrival_time[i]) && (completed == i)) {
                now_running = i;
                fin_t = arrival_time[i];	//idle cpu from end of prev process to arrival of i
            }
            else
                now_running = minvalue_arr(priority, arrival_time, complete, num, fin_t);

            if (now_running != -1) {	//start processing w/o delay
                start_t = fin_t;	//start_t of new process
                wait_t[now_running] += start_t - wait_start[now_running];
                first_processed_start_t[now_running] = start_t;
            }
            else if ((now_running == -1) && (i != num - 1)) {		//CPU is idle until next process comes
                start_t = arrival_time[i + 1];
                now_running = i + 1;
            }
        }
    }

    //all processes have arrived & been evaluated. from now on, behaves like (non-preemptive) priority
    fin_t += remaining_t[now_running];

    printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
    fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

    if (burst_time[now_running] == remaining_t[now_running])
        first_processed_start_t[now_running] = start_t; //
    remaining_t[now_running] = 0;
    complete[now_running] = 1;	//completed process
    completed++;

    while (completed != num) {
        start_t = fin_t;
        now_running = minvalue_arr(priority, arrival_time, complete, num, fin_t);
        wait_t[now_running] += start_t - wait_start[now_running];

        fin_t = start_t + remaining_t[now_running];
        if (burst_time[now_running] == remaining_t[now_running])
            first_processed_start_t[now_running] = start_t;
        remaining_t[now_running] = 0;
        complete[now_running] = 1;	//completed process
        completed++;

        printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
        fprintf(ptr, "%d %d %c%d \n", start_t, fin_t, p[now_running], pid[now_running]);

        start_t = fin_t;
    }

    //avg waiting time, turnaround time, response time.
    int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
    for (i = 0; i < num; i++) {
        tot_wait += wait_t[i];
        tot_turnaround += burst_time[i] + wait_t[i];
        tot_response += first_processed_start_t[i] - arrival_time[i];
    }
    //response time: when process was processed by CPU for the first time?
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;

    fprintf(ptr, "- \n");
    for (i = 0; i < num; i++) {
        fprintf(ptr, "%d %d %d %d %d %d \n", pid[i], burst_time[i], wait_t[i], burst_time[i] + wait_t[i], first_processed_start_t[i] - arrival_time[i], priority[i]);
    }
    fprintf(ptr, "%.2f %.2f %.2f \n", avg_wait, avg_turnaround, avg_response);
//    fprintf(ptr, "%.2f \n", avg_turnaround);
//    fprintf(ptr, "%.2f \n", avg_response);
    printf("Average waiting time = %.2f \n", avg_wait);
    printf("Average turnaround time = %.2f \n", avg_turnaround);
    printf("Average response time = %.2f \n", avg_response);

    fclose(ptr);
    return 0;
}

int main() {
    FILE* fptr;
    fptr = fopen("text.txt", "r");
    if (fptr == NULL)
    {
        printf("File Not Found!");
        exit(1);
    }
    int num;
    fscanf(fptr, "%d\n", &num);
    char* p;
    int* pid, * arrival_time, * burst_time, * priority;
    p = (char*)malloc(sizeof(char) * num);
    pid = (int*)malloc(sizeof(int) * num);
    arrival_time = (int*)malloc(sizeof(int) * num);
    burst_time = (int*)malloc(sizeof(int) * num);
    priority = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        fscanf(fptr, "%c%d %d %d %d\n", &p[i], & pid[i], &arrival_time[i], &burst_time[i], &priority[i]);
    }
    int timeallocation;
    fscanf(fptr, "%d", &timeallocation);
    FCFS(p, pid, arrival_time, burst_time, priority, num);
    SJF(p, pid, arrival_time, burst_time, priority, num);
    SRTF(p, pid, arrival_time, burst_time, priority, num);
    RR(p, pid, arrival_time, burst_time, priority, num, timeallocation);
    Priority(p, pid, arrival_time, burst_time, priority, num);
    PrePriority(p, pid, arrival_time, burst_time, priority, num);
    PriorityRR(p, pid, arrival_time, burst_time, priority, num, timeallocation);
    fclose(fptr);
    return 0;
}
