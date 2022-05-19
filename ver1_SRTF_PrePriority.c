//comments -- process 가 int 아닌 P1 등 문자열로 주어질 수 있어서 char* 로 바꾸면 좋을 것 같다. 

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

int SRTF(int pid[], int arrival_time[], int burst_time[], int priority[], int num);
int minvalue_arr(int arr[], int arrival_time[], int complete[], int num, int fin_t);
int PrePriority(int pid[], int arrival_time[], int burst_time[], int priority[], int num);

int main() {
    FILE* fptr;
    fptr = fopen("text.TXT", "r");
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
	
    //FCFS(pid, arrival_time, burst_time, priority, num);
    //SJF(pid, arrival_time, burst_time, priority, num);
    SRTF(pid, arrival_time, burst_time, priority, num);
    //RR(pid, arrival_time, burst_time, priority, num, timeallocation);
    //Priority(pid, arrival_time, burst_time, priority, num);
    PrePriority(pid, arrival_time, burst_time, priority, num);
    //PriorityRR(pid, arrival_time, burst_time, priority, num, timeallocation)
    fclose(fptr);
    return 0;
}


int SRTF(int pid[], int arrival_time[], int burst_time[], int priority[], int num){
	swap(pid, arrival_time, burst_time, priority, num);
	
	int i, completed=0;
	int processed_t;
	int now_running=0, t=0;
	int remaining_t[num], complete[num], wait_t[num], wait_start[num], first_processed_start_t[num];
	for(i=0; i<num; i++){
		remaining_t[i] = burst_time[i];
		complete[i] = 0;
		wait_t[i] = 0;
		wait_start[i] = arrival_time[i];
		first_processed_start_t[i]=0;
	}
	int start_t = arrival_time[0], fin_t=arrival_time[0];	//when first process starts after 0

	FILE* ptr;
    ptr = fopen("SRTF.txt", "w");
	printf("\n\nSRTF:\n");
	
	//compare current process & new arrivals
	for(i=1; i<num; i++){
		
		if(now_running == i)	//CPU was idle until this process came.
			continue;
		
		if((remaining_t[now_running] > arrival_time[i] - start_t)){	//new arrival before finishing current process			
			processed_t = arrival_time[i] - fin_t;
			remaining_t[now_running] -= processed_t;			
			fin_t += processed_t;
			if(remaining_t[now_running] > remaining_t[i]){	//preemptive switch
				
				wait_start[now_running] = arrival_time[i];	//count wait time from this point in time
				wait_t[i] += fin_t - arrival_time[i];
				
				printf("%d\t\t%d\t\t%d\n", start_t, arrival_time[i], pid[now_running]);
				fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, arrival_time[i], pid[now_running]);
				fin_t = arrival_time[i];	//update finish time
				now_running = i;
				start_t = arrival_time[i];	//start of new process
				first_processed_start_t[now_running] = arrival_time[i];	//to calculate response time
			}
			else	//continue with original process		
				continue;
		}	
		else{		//끝나고 새 process 도착.  또는 새 프로세스 도착 전에 수행 완료
			wait_t[now_running] = 0;
			fin_t += remaining_t[now_running];
			first_processed_start_t[now_running] = arrival_time[now_running];
			
			printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
			fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
			
			remaining_t[now_running] = 0;
			complete[now_running] = 1;	//completed process
			completed++;
			if(completed == num)
				break;
			//find idx of process w/ least remaining time
			now_running = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t);
			
			if(now_running != -1){	//start processing w/o delay
				start_t = fin_t;	//start_t of new process
				wait_t[now_running] += start_t - wait_start[now_running];
				first_processed_start_t[now_running] = start_t;
			}
			else if((now_running == -1) && (i!=num-1)){		//CPU is idle until next process comes
				start_t = arrival_time[i+1];
				now_running = i+1;
			}
		}
	}	
	//all processes have arrived and been evaluated. behaves like SJF from now
		//여기서부턴 SJF 처럼
	
	fin_t += remaining_t[now_running];
	printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
	fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
	
	if(burst_time[now_running] == remaining_t[now_running])
		first_processed_start_t[now_running] = start_t; //	
	
	remaining_t[now_running] = 0;
	complete[now_running] = 1;	//completed process
	completed++;
	
	while(completed != num){
		start_t = fin_t;
		now_running = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t);
		wait_t[now_running] += start_t - wait_start[now_running];
		
		fin_t = start_t + remaining_t[now_running];
		if(burst_time[now_running] == remaining_t[now_running])
			first_processed_start_t[now_running] = start_t;
		remaining_t[now_running] = 0;
		complete[now_running] = 1;	//completed process
		completed++;

		printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
		fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
		
		start_t = fin_t;
	}
	
/*	for(i=0; i<num; i++){	//검산용
		//printf("first_processed_start_t[%d] = %d\n", pid[i], first_processed_start_t[i]);
		printf("response[%d] = %d\n\n", pid[i], first_processed_start_t[i] - arrival_time[i]);
	}*/
	
	//avg waiting time, turnaround time, response time.
	int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
	for(i=0; i<num; i++){
		tot_wait += wait_t[i];
		tot_turnaround += burst_time[i]+wait_t[i];
		tot_response += first_processed_start_t[i] - arrival_time[i];
	}
		//response time: when process was processed by CPU for the first time?
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;
    fprintf(ptr, "%.2f\n", avg_wait);
    fprintf(ptr, "%.2f\n", avg_turnaround);
    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);	

	fclose(ptr);
	return 0;
}

int minvalue_arr(int arr[], int arrival_time[], int complete[], int num, int fin_t){
//returns index of minimum value in array
	//arr can be either priority or remaining time
	int i, min; 
	int min_idx = -1;
	for(i=0; i<num; i++){
		if(complete[i]==0 &&(arrival_time[i] <= fin_t)){
			min = arr[i];
			min_idx = i;
			break;
		}
	}	//set min_idx to any pid that is incomplete & already arrived before/at fin_t
	
	for(i=0; i<num; i++){
		if((complete[i]==0) && (arrival_time[i] <= fin_t)){
			if(min > arr[i]){
				min = arr[i];
				min_idx = i;				
			}
			else if((min == arr[i]) && (arrival_time[i]<arrival_time[min_idx])){
				min = arr[i];
				min_idx = i;			
			}
		}
	}
	return min_idx;
	//min_idx == -1 when all processes are complete  OR when CPU becomes idle (completed all processes up to given time)
}

int PrePriority(int pid[], int arrival_time[], int burst_time[], int priority[], int num){
	swap(pid, arrival_time, burst_time, priority, num);
	
	int i, now_running=0, completed=0;
	int processed_t;
	int t=0;
	int remaining_t[num], complete[num], wait_t[num], wait_start[num], first_processed_start_t[num];
	for(i=0; i<num; i++){
		remaining_t[i] = burst_time[i];
		complete[i] = 0;
		wait_t[i] = 0;
		wait_start[i] = arrival_time[i];
		first_processed_start_t[i] =0;
	}
	int start_t = arrival_time[0], fin_t=arrival_time[0];	//when first process starts after 0	
	FILE* ptr;
    ptr = fopen("PrePriority.txt", "w");
	printf("\n\nPrePriority:\n");
	
	for(i=1; i<num; i++){
		if(now_running == i)	//CPU was idle until this process came.
			continue;		
		if((remaining_t[now_running] > arrival_time[i] - start_t)){	//new arrival before finishing current process			
			processed_t = arrival_time[i] - fin_t;
			remaining_t[now_running] -= processed_t;			
			fin_t += processed_t;
			if(priority[now_running] > priority[i]){	//preemptive switch
				wait_start[now_running] = arrival_time[i];	//count wait time from this point in time
				wait_t[i] += fin_t - arrival_time[i];
				
				printf("%d\t\t%d\t\t%d\n", start_t, arrival_time[i], pid[now_running]);
				fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, arrival_time[i], pid[now_running]);
				
				fin_t = arrival_time[i];	//update finish time
				now_running = i;
				start_t = arrival_time[i];	//start of new process
				first_processed_start_t[now_running] = arrival_time[i];	//to calculate response time
			}
			else	//continue with original process		
				continue;
		}	
		else{		//끝나고 새 process 도착.  또는 새 프로세스 도착 전에 수행 완료
			wait_t[now_running] = 0;
			fin_t += remaining_t[now_running];
			first_processed_start_t[now_running] = arrival_time[now_running];
			
			printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
			fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
			
			remaining_t[now_running] = 0;
			complete[now_running] = 1;	//completed process
			completed++;
			if(completed == num)
				break;
			
			//find idx of process w/ highest priority
			now_running = minvalue_arr(priority, arrival_time, complete, num, fin_t);
			
			if(now_running != -1){	//start processing w/o delay
				start_t = fin_t;	//start_t of new process
				wait_t[now_running] += start_t - wait_start[now_running];
				first_processed_start_t[now_running] = start_t;
			}
			else if((now_running == -1) && (i!=num-1)){		//CPU is idle until next process comes
				start_t = arrival_time[i+1];
				now_running = i+1;
			}
		}		
	}
	
	//all processes have arrived & been evaluated. from now on, behaves like (non-preemptive) priority
	fin_t += remaining_t[now_running];
	printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
	fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
	
	if(burst_time[now_running] == remaining_t[now_running])
		first_processed_start_t[now_running] = start_t; //
	remaining_t[now_running] = 0;
	complete[now_running] = 1;	//completed process
	completed++;	
	
	while(completed != num){
		start_t = fin_t;
		now_running = minvalue_arr(priority, arrival_time, complete, num, fin_t);
		wait_t[now_running] += start_t - wait_start[now_running];
		
		fin_t = start_t + remaining_t[now_running];
		if(burst_time[now_running] == remaining_t[now_running])
			first_processed_start_t[now_running] = start_t;
		remaining_t[now_running] = 0;
		complete[now_running] = 1;	//completed process
		completed++;

		printf("%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
		fprintf(ptr, "%d\t\t%d\t\t%d\n", start_t, fin_t, pid[now_running]);
		
		start_t = fin_t;
	}	
	
/*	for(i=0; i<num; i++){	//검산용
		//printf("first_processed_start_t[%d] = %d\n", pid[i], first_processed_start_t[i]);
		printf("response[%d] = %d\n\n", pid[i], first_processed_start_t[i] - arrival_time[i]);
	}*/
	
	//avg waiting time, turnaround time, response time.
	int tot_wait = 0, tot_turnaround = 0, tot_response = 0;
	for(i=0; i<num; i++){
		tot_wait += wait_t[i];
		tot_turnaround += burst_time[i]+wait_t[i];
		tot_response += first_processed_start_t[i] - arrival_time[i];
	}
		//response time: when process was processed by CPU for the first time?
    float avg_wait = (float)tot_wait / (float)num;
    float avg_turnaround = (float)tot_turnaround / (float)num;
    float avg_response = (float)tot_response / (float)num;
    fprintf(ptr, "%.2f\n", avg_wait);
    fprintf(ptr, "%.2f\n", avg_turnaround);
    fprintf(ptr, "%.2f\n", avg_response);
    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);	

	fclose(ptr);
	return 0;	
}
