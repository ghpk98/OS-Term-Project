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

int FCFS(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    printf("\n\nFCFS:\n");
    int *waiting_time, *turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    FILE* ptr;
    ptr = fopen("C:\\Users\\Gunho\\Desktop\\FCFS.txt", "w");
    fprintf(ptr, "%d\n", num);
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d %d\n", pid[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f\n", avg_wait);
    fprintf(ptr, "%.2f\n", avg_turnaround);
    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int SJF(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapSJF(pid, arrival_time, burst_time, priority, num);
    printf("\n\nSJF:\n");
    int* waiting_time, * turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    FILE* ptr;
    ptr = fopen("C:\\Users\\Gunho\\Desktop\\SJF.txt", "w");
    fprintf(ptr, "%d\n", num);
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d %d\n", pid[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f\n", avg_wait);
    fprintf(ptr, "%.2f\n", avg_turnaround);
    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int Priority(int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);
    swapPriority(pid, arrival_time, burst_time, priority, num);
    printf("\n\nPriority:\n");
    int* waiting_time, * turnaround_time;
    waiting_time = (int*)malloc(sizeof(int) * num);
    turnaround_time = (int*)malloc(sizeof(int) * num);
    int tot_wait = 0, tot_turnaround = 0;
    waitingtime(pid, arrival_time, burst_time, waiting_time, num);
    turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
    printf("Process ID   Burst Time   Waiting Time   Turnaround Time      Response Time     Priority \n");
    FILE* ptr;
    ptr = fopen("C:\\Users\\Gunho\\Desktop\\Priority.txt", "w");
    fprintf(ptr, "%d\n", num);
    for (int i = 0; i < num; i++) {
        tot_wait = tot_wait + waiting_time[i];
        tot_turnaround = tot_turnaround + turnaround_time[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
        fprintf(ptr, "%d %d %d %d %d %d %d\n", pid[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = avg_wait;
    fprintf(ptr, "%.2f\n", avg_wait);
    fprintf(ptr, "%.2f\n", avg_turnaround);
    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);
    return 0;
}

int main() {
    FILE* fptr;
    fptr = fopen("C:\\Users\\Gunho\\Desktop\\text.txt", "r");
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
    //RR(pid, arrival_time, burst_time, priority, num, timeallocation);
    Priority(pid, arrival_time, burst_time, priority, num);
    //PrePriority(pid, arrival_time, burst_time, priority, num)
    //PriorityRR(pid, arrival_time, burst_time, priority, num, timeallocation)
    fclose(fptr);
    return 0;
}

