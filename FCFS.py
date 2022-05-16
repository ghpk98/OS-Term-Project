#!/usr/bin/env python3
#FCFS time

import pandas as pd


result_FCFS = pd.read_table("tc1_FCFS.txt", sep = " ")

arrival_time=list()
with open("tc1.txt","r") as f:
    for line in f.readlines():
        segments=line.split(' ')
        try:
            segments[2]
            arrival_time.append(int(segments[1]))
        except:
            pass


#waiting turnaround respond
FCFS_time={
    "P0":[0,0,0],"P1":[0,0,0],"P2":[0,0,0],"P3":[0,0,0],"P4":[0,0,0],"P5":[0,0,0],"Avg":[0,0,0]
}


sum_w=0
sum_t=0

for line in result_FCFS.iloc():
    key=line[2]
    index=int(line[2].strip('P'))
    
    FCFS_time[key][0]+=(line[0]-arrival_time[index])
    FCFS_time[key][1]+=(line[1]-arrival_time[index])
    FCFS_time[key][2]+=(line[0]-arrival_time[index])
    sum_w+=FCFS_time[key][0]
    sum_t+=FCFS_time[key][1]

FCFS_time["Avg"][0]=sum_w//6
FCFS_time["Avg"][1]=sum_t//6
FCFS_time["Avg"][2]=sum_w//6


FCFStime_Result=pd.DataFrame.from_dict(FCFS_time, orient='index')
print(FCFStime_Result)
