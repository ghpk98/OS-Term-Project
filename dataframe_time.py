#!/usr/bin/env python3

import pandas as pd

algorithm_list = ["FCFS","SJF","SRTF","RR","PRIORITY","PPRIORITY","PRR"]
read_file = ["tc1_"+ x + ".txt" for x in algorithm_list]

FCFS_time=list()
SJF_time=list()
SRTF_time=list()
RR_time=list()
PRIORITY_time=list()
PPRIOIRITY_time=list()
PRR_time=list()
Time=[FCFS_time,SJF_time,SRTF_time,RR_time,PRIORITY_time,PPRIOIRITY_time,PRR_time]
for i in range(2):
    avg_time=["Avg"]
    with open(read_file[i], 'r') as f:
        
        for line in f.readlines()[1:]:
            Time_set=list()
            segments=line.split(" ")

           # print(segments)
            if len(segments)>1:
                Time_set.append("P"+segments[0])
                Time_set.append(segments[2])
                Time_set.append(segments[3])
                Time_set.append(segments[4])

                Time[i].append(Time_set)
            else:
                avg_time.append(segments[0].rstrip())
    Time[i].append(avg_time)
   # print(Time[i])

FCFS_time_df=pd.DataFrame(FCFS_time,columns=['process','waiting','turnaround','response'])
SJF_time_df=pd.DataFrame(SJF_time,columns=['process','waiting','turnaround','response'])
SRTF_time_df=pd.DataFrame(SRTF_time,columns=['process','waiting','turnaround','response'])
RR_time_df=pd.DataFrame(RR_time,columns=['process','waiting','turnaround','response'])
PRIORITY_time_df=pd.DataFrame(PRIORITY_time,columns=['process','waiting','turnaround','response'])
PPRIROTY_time_df=pd.DataFrame(PPRIOIRITY_time,columns=['process','waiting','turnaround','response'])
PRR_df=pd.DataFrame(PRR_time,columns=['process','waiting','turnaround','response'])

print(FCFS_time_df)
print(SJF_time_df)
print(SRTF_time_df)
print(RR_time_df)
print(PRIORITY_time_df)
print(PPRIROTY_time_df)
print(PRR_df)