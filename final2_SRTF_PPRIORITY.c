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

int preemp(int arrival_time[], int start, int now_running, int num, int remaining_t[], int complete[]){
	int i, processed_t, k=0, min;
	int idx[num];
	for(i = now_running +1; start + remaining_t[now_running] > arrival_time[i]; i++){
			processed_t = arrival_time[i] - start;
			if((i<num) && remaining_t[now_running] - processed_t > remaining_t[i]  && (complete[i]==0) && start < arrival_time[i] ){
				idx[k] = i;
				k++;
			}
		}
	if(k==0)
		return -1;	//no preemptive process
	else if(k==1)
		return idx[0];
	else{	//2 or more possible preemptive processes
		min = idx[0];
		for(i=0; i<k-1; i++){
			if(remaining_t[idx[i+1]] < remaining_t[min] && arrival_time[idx[i+1]]<arrival_time[min] )
				min = idx[i+1];
		}
		return min;
	}
}

int preemp_PrePriority(int arrival_time[], int start, int now_running, int num, int remaining_t[], int priority[], int complete[]){
	int i, k=0, min;
	int idx[num];
	for(i = now_running +1; start + remaining_t[now_running] > arrival_time[i]; i++){
			if((i<num) && priority[now_running]  > priority[i]  && (complete[i]==0) && start < arrival_time[i] ){
				idx[k] = i;
				k++;
			}
		}
	if(k==0)
		return -1;	//no preemptive process
	else if(k==1)
		return idx[0];
	else{	//2 or more possible preemptive processes
		min = idx[0];
		for(i=0; i<k-1; i++){
			if(priority[idx[i+1]] < priority[min] && arrival_time[idx[i+1]]<arrival_time[min] )
				min = idx[i+1];
		}
		return min;
	}
}

int SRTF(char* p, int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);

	int next=0, min=-1;
    int i, j, completed = 0;
    int processed_t;
    int now_running = 0, t = 0;
    int remaining_t[200], complete[200], wait_t[200], wait_start[200], first_processed_start_t[200];
	int start_t[num], fin_t[num];
    for (i = 0; i < num; i++) {
        remaining_t[i] = burst_time[i];
        complete[i] = 0;
        wait_t[i] = 0;
        wait_start[i] = arrival_time[i];
        first_processed_start_t[i] = arrival_time[i];
		start_t[i] = arrival_time[i]; 
		fin_t[i] = arrival_time[i];
    }

    FILE* ptr;
    ptr = fopen("algo_SRTF.txt", "w");
    printf("S E PROCESS \n");
    fprintf(ptr, "S E PROCESS \n");
    printf("\n\nSRTF:\n");

    if(num>1)
    	i = now_running + 1;
    	
	while(completed != num){
		if(start_t[now_running] + remaining_t[now_running] > arrival_time[i]){	//process i arrives before now running process ends
			next = preemp(arrival_time, start_t[now_running], now_running, num, remaining_t, complete);
			if(next !=-1){
				remaining_t[now_running] -= arrival_time[next] - start_t[now_running];
				fin_t[now_running] = arrival_time[next];
				printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], arrival_time[next], p[now_running], pid[now_running]);
				fprintf(ptr, "%d %d %c%d \n", start_t[now_running], arrival_time[next], p[now_running], pid[now_running]);

				now_running = next;
			}

		    else{    //finished processing w/o preemptive switch	next == -1
        		fin_t[now_running] = start_t[now_running] + remaining_t[now_running];
        		remaining_t[now_running] = 0;
        		printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
        		fprintf(ptr, "%d %d %c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);

        		complete[now_running] = 1; 
        		completed++;
        		if(completed==num)
        		    break;
        		
        		next = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t[now_running]);
        		if(next!=-1){
        		    start_t[next] = fin_t[now_running];
        			wait_t[next] += start_t[next]-fin_t[next];
        			if(remaining_t[next] == burst_time[next])
        				first_processed_start_t[next] = start_t[next];
        			now_running = next;
        			i = now_running +1;
        			
        			continue;
        		}
        		else{    //(next == -1 && completed != num){		//finished all processes that arrived before finishing current process
        			for(j=1; j<num; j++){
        				if(complete[j] ==0 && arrival_time[j] > fin_t[now_running]){
        					now_running = j;
        					start_t[now_running] = arrival_time[j];
        					break;
        				}
        			}
        		}
		    }
		}
		else{        //next process arrives after current process ends
		    fin_t[now_running] = start_t[now_running] + remaining_t[now_running];
        	remaining_t[now_running] = 0;
        	printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
        	fprintf(ptr, "%d %d %c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
			
			
        	complete[now_running] = 1; 
        	completed++;
        	if(completed==num)
        	    break;

			
        		next = minvalue_arr(remaining_t, arrival_time, complete, num, fin_t[now_running]);
        		if(next!=-1){
        		    start_t[next] = fin_t[now_running];
        			wait_t[next] += start_t[next]-fin_t[next];
        			if(remaining_t[next] == burst_time[next])
        				first_processed_start_t[next] = start_t[next];
        			now_running = next;
        			i = now_running +1;
        			
        			continue;
        		}
        		else{    //(next == -1 && completed != num){		//finished all processes that arrived before finishing current process
        			for(j=1; j<num; j++){
        				if(complete[j] ==0 && arrival_time[j] > fin_t[now_running]){
        					now_running = j;
        					start_t[now_running] = arrival_time[j];
        					break;
        				}
        			}
        		}
		}
		
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

    fprintf(ptr, "-\n");
    for (i = 0; i < num; i++) {
        fprintf(ptr, "%d %d %d %d %d %d\n", pid[i], burst_time[i], wait_t[i], burst_time[i] + wait_t[i], first_processed_start_t[i] - arrival_time[i], priority[i]);
    }


    fprintf(ptr, "%.2f %.2f %.2f\n", avg_wait, avg_turnaround, avg_response);

    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);

    fclose(ptr);
    return 0;
}

int PPRIORITY(char* p, int pid[], int arrival_time[], int burst_time[], int priority[], int num) {
    swap(pid, arrival_time, burst_time, priority, num);

	int next=0, min=-1;
    int i, j, completed = 0;
    int processed_t;
    int now_running = 0, t = 0;
    int remaining_t[200], complete[200], wait_t[200], wait_start[200], first_processed_start_t[200];
	int start_t[num], fin_t[num];
    for (i = 0; i < num; i++) {
        remaining_t[i] = burst_time[i];
        complete[i] = 0;
        wait_t[i] = 0;
        wait_start[i] = arrival_time[i];
        first_processed_start_t[i] = arrival_time[i];
		start_t[i] = arrival_time[i]; 
		fin_t[i] = arrival_time[i];
    }

    FILE* ptr;
    ptr = fopen("algo_PPRIORITY.txt", "w");
    printf("S E PROCESS \n");
    fprintf(ptr, "S E PROCESS \n");
    printf("\n\nPPRIORITY:\n");

    if(num>1)
    	i = now_running + 1;
    	
	while(completed != num){
		if(start_t[now_running] + remaining_t[now_running] > arrival_time[i]){	//process i arrives before now running process ends
			next = preemp_PrePriority(arrival_time, start_t[now_running], now_running, num, remaining_t, priority, complete);
			if(next !=-1){
				remaining_t[now_running] -= arrival_time[next] - start_t[now_running];
				fin_t[now_running] = arrival_time[next];
				printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], arrival_time[next], p[now_running], pid[now_running]);
				fprintf(ptr, "%d %d %c%d \n", start_t[now_running], arrival_time[next], p[now_running], pid[now_running]);
			
				now_running = next;
			}

		    else{    //finished processing w/o preemptive switch	next == -1
        		fin_t[now_running] = start_t[now_running] + remaining_t[now_running];
        		remaining_t[now_running] = 0;
        		printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
        		fprintf(ptr, "%d %d %c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
				
        		complete[now_running] = 1; 
        		completed++;
        		if(completed==num)
        		    break;
        		
        		next = minvalue_arr(priority, arrival_time, complete, num, fin_t[now_running]);
				//printf("next: %d\n", next);
        		if(next!=-1){
        		    start_t[next] = fin_t[now_running];
        			wait_t[next] += start_t[next]-fin_t[next];
        			if(remaining_t[next] == burst_time[next])
        				first_processed_start_t[next] = start_t[next];
        			now_running = next;
        			i = now_running +1;
        			
        			continue;
        		}
        		else{    //(next == -1 && completed != num){		//finished all processes that arrived before finishing current process
        			for(j=1; j<num; j++){
        				if(complete[j] ==0 && arrival_time[j] > fin_t[now_running]){
        					now_running = j;
        					start_t[now_running] = arrival_time[j];
        					break;
        				}
        			}
        		}
		    }
		}
		else{        //next process arrives after current process ends
		    fin_t[now_running] = start_t[now_running] + remaining_t[now_running];
        	remaining_t[now_running] = 0;
        	printf("%d\t\t%d\t\t%c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
        	fprintf(ptr, "%d %d %c%d \n", start_t[now_running], fin_t[now_running] , p[now_running], pid[now_running]);
			
        	complete[now_running] = 1; 
        	completed++;
        	if(completed==num)
        	    break;
			next = minvalue_arr(priority, arrival_time, complete, num, fin_t[now_running]);
       		if(next!=-1){
       		    start_t[next] = fin_t[now_running];
       			wait_t[next] += start_t[next]-fin_t[next];
       			if(remaining_t[next] == burst_time[next])
       				first_processed_start_t[next] = start_t[next];
       			now_running = next;
       			i = now_running +1;
       			
       			continue;
       		}
       		else{    //(next == -1 && completed != num){		//finished all processes that arrived before finishing current process
       			for(j=1; j<num; j++){
       				if(complete[j] ==0 && arrival_time[j] > fin_t[now_running]){
       					now_running = j;
       					start_t[now_running] = arrival_time[j];
       					break;
       				}
       			}
       		}
	}
		
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

    fprintf(ptr, "-\n");
    for (i = 0; i < num; i++) {
        fprintf(ptr, "%d %d %d %d %d %d\n", pid[i], burst_time[i], wait_t[i], burst_time[i] + wait_t[i], first_processed_start_t[i] - arrival_time[i], priority[i]);
    }


    fprintf(ptr, "%.2f %.2f %.2f\n", avg_wait, avg_turnaround, avg_response);

    printf("Average waiting time = %.2f\n", avg_wait);
    printf("Average turnaround time = %.2f\n", avg_turnaround);
    printf("Average response time = %.2f\n", avg_response);

    fclose(ptr);
    return 0;
}

int main() {
    FILE* fptr;
    fptr = fopen("case5.txt", "r");
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
    //FCFS(p, pid, arrival_time, burst_time, priority, num);
    //SJF(p, pid, arrival_time, burst_time, priority, num);
    //RR(p, pid, arrival_time, burst_time, priority, num, timeallocation);
    //Priority(p, pid, arrival_time, burst_time, priority, num);
	//PriorityRR(p, pid, arrival_time, burst_time, priority, num, timeallocation);
	SRTF(p, pid, arrival_time, burst_time, priority, num);
    PPRIORITY(p, pid, arrival_time, burst_time, priority, num);
    fclose(fptr);
    return 0;
}
