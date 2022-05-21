#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt



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
columns=['waiting','turnaround','response']
rows_list=list()
for i in range(7):
    rows=[]
    avg_time=[]
    with open(read_file[i], 'r') as f:
        
        for line in f.readlines()[1:]:
            Time_set=list()
            segments=line.split(" ")
            if len(segments)>1:
                rows.append("P"+segments[0])
                Time_set.append(segments[2])
                Time_set.append(segments[3])
                Time_set.append(segments[4])

                Time[i].append(Time_set)
            else:
                avg_time.append(segments[0].rstrip())
    Time[i].append(avg_time)
    rows.append("Avg")
    rows_list.append(rows)


print(rows_list)
print(Time)
fig, ax=plt.subplots()
ax.set_axis_off()
for i in range(7):
    the_table=ax.table(cellText=Time[i],
                    colLabels=columns,
                    rowLabels=rows_list[i],
                    loc='center')
    plt.savefig(algorithm_list[i]+'_time.png',
                bbox_inches='tight',
                dpi=240)