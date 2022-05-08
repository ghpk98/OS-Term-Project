#include <stdio.h>
#include <stdbool.h> 

//Swap operation to order by first come
int swap(int pid[], int arrival_time[], int burst_time[], int num) {
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
			}
		}
	}
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

int FCFS(int pid[], int arrival_time[], int burst_time[], int num) {
	swap(pid, arrival_time, burst_time, num);
	printf("\nFCFS:\n");
	int waiting_time[num], turnaround_time[num];
	int tot_wait = 0, tot_turnaround = 0;
	waitingtime(pid, arrival_time, burst_time, waiting_time, num);
	turnaroundtime(pid, arrival_time, burst_time, waiting_time, turnaround_time, num);
	printf("Process ID   Burst Time   Waiting Time   Turnaround Time    Response Time \n");
	for (int i = 0; i < num; i++) {
		tot_wait = tot_wait + waiting_time[i];
		tot_turnaround = tot_turnaround + turnaround_time[i];
		printf(" %d\t\t%d\t\t%d\t\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i]);
	}
	printf("Average waiting time = %.2f\n", (float)tot_wait / (float)num);
	printf("Average turnaround time = %.2f\n", (float)tot_turnaround / (float)num);
	printf("Average response time = ");
	return 0;
}


int main() {
	printf("Enter the number of processes: "); //Get the number of total processes
	int num;
	scanf("%d", &num);
	int pid[num], arrival_time[num], burst_time[num], priority[num]; //initialize pid, arrival_time, burst_time, priority array
	int timeallocation;  //initialize timeallocation
	int count = 0;
	//Enter the Process Data
	while (count < num) {
		printf("Enter processor id, arrival time, burst time, priority:");
		scanf("%d %d %d %d", &pid[count], &arrival_time[count], &burst_time[count], &priority[count]);
		count++;
	}
	//Enter Time Allocation
	printf("Enter Time Allocation for RR: ");
	scanf("%d", &timeallocation);
	FCFS(pid, arrival_time, burst_time, num);
	//SJF()
	//SRTF()
	//RR()
	//Priority()
	//PrePriority()
	//PriorityRR()
	return 0;
}
