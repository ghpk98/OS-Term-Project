#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Analysis

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1dCDi2FGEo-YG1V_qTulmkE1ZJMzVAkCo
"""
"""
from google.colab import files
uploaded = files.upload()
"""
print("Module importing...")
import os
from warnings import filterwarnings
filterwarnings('ignore')
#import plotly.express as px
from IPython.display import display
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
#import time
from matplotlib.animation import FuncAnimation
#import matplotlib.ticker as mticker
#from PIL import Image
#from tabulate import tabulate
#!apt install imagemagick

"""-를 기준으로 파일을 2개로 나누기
dataframe->간트(result_*), 표(table_*)
"""
#Declare a list of algorithms for file input and naming of various data storage variables
algorithm_list = ["FCFS", "SJF", "SRTF", "RR", "PRIORITY", "PPRIORITY", "PRR"]
filename = input("WANT TESTCASE: ")

read_file=[filename+"/"+"result_"+x+".txt" for x in algorithm_list]
gantt_file = [filename+"/"+filename + "_gantt_" + x + ".txt" for x in algorithm_list]
table_file=[filename+"/"+filename+"_table_"+x+".txt" for x in algorithm_list]

try:
    for i in range(7):
        if not os.path.isfile(table_file[i]):
            raise NotImplementedError
except:
    for i in range(7):
      f=open(read_file[i])
      lines=f.readlines()
      f.close()

      f=open(gantt_file[i],"a")
      for line in lines:
        if (len(line)==2): # -
          f.close()
          f=open(table_file[i], "a")
        else:
          f.write(line)
      f.close()

result_FCFS = pd.read_table(gantt_file[0], sep = " ")
# print(result_FCFS)
result_SJF = pd.read_table(gantt_file[1], sep = " ")
# print(result_SJF)
result_SRTF = pd.read_table(gantt_file[2], sep = " ")
# print(result_SRTF)
result_RR = pd.read_table(gantt_file[3], sep = " ")
# print(result_RR)
result_PRIORITY = pd.read_table(gantt_file[4], sep = " ")
# print(result_PRIORITY)
result_PPRIORITY = pd.read_table(gantt_file[5], sep = " ")
# print(result_PPRIORITY)
result_PRR = pd.read_table(gantt_file[6], sep = " ")
# print(result_PRR)


process = result_FCFS["PROCESS"].unique()
nprocess = len(result_FCFS["PROCESS"].unique())
color = np.random.randint(0, 256, 3 * nprocess).reshape(nprocess, 3)

processcolor = {x: y for x, y in zip(process, color)}
#print(processcolor.get(result_SJF.iloc[0]["PROCESS"]))
#print(result_SJF.iloc[0])

"""간트차트"""
#Adjust the font size according to the x-axis length of the Gantt chart
size = result_FCFS.iloc[len(result_FCFS)-1]["E"]
font_size = 15 if size < 50 else 8
#print(font_size)
#Gantt chart plot screen setting
fig, gnt = plt.subplots()

plt.rcParams['figure.figsize'] = (25,25)
plt.title("Gantt Chart", fontsize= 16, fontweight = 'bold')


gnt.set_xlabel("Time")
gnt.set_ylabel("Algorithm")
plt.xlim([0, result_FCFS.iloc[len(result_FCFS)-1]["E"]])
plt.ylim([0, 5*7])
plt.xticks(range(result_FCFS.iloc[len(result_FCFS)-1]["E"] + 1))
gnt.set_yticklabels(algorithm_list)
plt.box(False)

#Create process list for color selection by process
process = result_FCFS["PROCESS"].unique()
nprocess = len(result_FCFS["PROCESS"].unique())

#Randomly generated and resized to fit RGB Type
color = np.random.randint(0, 256, 3 * nprocess).reshape(nprocess, 3)/255

#Bind colors to assign to the facecolors option
processcolor = {x: y for x, y in zip(process, color)}

#Background grid setting
gnt.grid(True, linestyle='--')
width = 3.5

#Drawing process occupation Gantt chart for each algorithm using broken_barh
"""
Set the x-coordinate using the start and end time of the process cpu burst time of each algorithm result
broke_barh's thickness is fixed to width
"""
gnt.broken_barh([(0, result_FCFS.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_FCFS)):
  #print([(result_FCFS.iloc[i]["S"], result_FCFS.iloc[i]["E"]), result_FCFS.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_FCFS.iloc[i]["S"], result_FCFS.iloc[i]["E"])], (0, width), facecolors = processcolor.get(result_FCFS.iloc[i]["PROCESS"]).tolist())
  #processcolor.get(result_FCFS.iloc[i]["PROCESS"])
  #print(result_FCFS.loc[i])
  #Marking Processes Using Annotate
  gnt.annotate("%s"%(result_FCFS.iloc[i]["PROCESS"]), xy=((result_FCFS.iloc[i]["S"] + result_FCFS.iloc[i]["E"])/2, 0+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  #Error correction of broken_barh
  if i != len(result_FCFS)-1:  
    length = result_FCFS.iloc[i+1]["S"] - result_FCFS.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_FCFS.iloc[i]["E"], result_FCFS.iloc[i]["E"] + length)], (0, width), facecolors = 'white')


gnt.broken_barh([(0, result_SJF.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_SJF)):
  #print([(result_SJF.iloc[i]["S"], result_SJF.iloc[i]["E"]), result_SJF.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_SJF.iloc[i]["S"], result_SJF.iloc[i]["E"])], (5, width), facecolors = processcolor.get(result_SJF.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_SJF.iloc[i]["PROCESS"]), xy=((result_SJF.iloc[i]["S"] + result_SJF.iloc[i]["E"])/2, 5+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  if i != len(result_SJF)-1:  
    length = result_SJF.iloc[i+1]["S"] - result_SJF.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_SJF.iloc[i]["E"], result_SJF.iloc[i]["E"] + length)], (5, width), facecolors = 'white')


gnt.broken_barh([(0, result_SRTF.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_SRTF)):
  #print([(result_SRTF.iloc[i]["S"], result_SRTF.iloc[i]["E"]), result_SRTF.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_SRTF.iloc[i]["S"], result_SRTF.iloc[i]["E"])], (10, width), facecolors = processcolor.get(result_SRTF.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_SRTF.iloc[i]["PROCESS"]), xy=((result_SRTF.iloc[i]["S"] + result_SRTF.iloc[i]["E"])/2, 10+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)
  
  if i != len(result_SRTF)-1:  
    length = result_SRTF.iloc[i+1]["S"] - result_SRTF.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_SRTF.iloc[i]["E"], result_SRTF.iloc[i]["E"] + length)], (10, width), facecolors = 'white')


gnt.broken_barh([(0, result_RR.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_RR)):
  #print([(result_RR.iloc[i]["S"], result_RR.iloc[i]["E"]), result_RR.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_RR.iloc[i]["S"], result_RR.iloc[i]["E"])], (15, width), facecolors = processcolor.get(result_RR.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_RR.iloc[i]["PROCESS"]), xy=((result_RR.iloc[i]["S"] + result_RR.iloc[i]["E"])/2, 15+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  if i != len(result_RR)-1:  
    length = result_RR.iloc[i+1]["S"] - result_RR.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_RR.iloc[i]["E"], result_RR.iloc[i]["E"] + length)], (15, width), facecolors = 'white')


gnt.broken_barh([(0, result_PRIORITY.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_PRIORITY)):
  #print([(result_PRIORITY.iloc[i]["S"], result_PRIORITY.iloc[i]["E"]), result_PRIORITY.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_PRIORITY.iloc[i]["S"], result_PRIORITY.iloc[i]["E"])], (20, width), facecolors = processcolor.get(result_PRIORITY.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_PRIORITY.iloc[i]["PROCESS"]), xy=((result_PRIORITY.iloc[i]["S"] + result_PRIORITY.iloc[i]["E"])/2, 20+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  if i != len(result_PRIORITY)-1:  
    length = result_PRIORITY.iloc[i+1]["S"] - result_PRIORITY.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_PRIORITY.iloc[i]["E"], result_PRIORITY.iloc[i]["E"] + length)], (20, width), facecolors = 'white')


gnt.broken_barh([(0, result_PPRIORITY.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_PPRIORITY)):
  # print([(result_PPRIORITY.iloc[i]["S"], result_PPRIORITY.iloc[i]["E"]), result_PPRIORITY.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_PPRIORITY.iloc[i]["S"], result_PPRIORITY.iloc[i]["E"])], (25, width), facecolors = processcolor.get(result_PPRIORITY.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_PPRIORITY.iloc[i]["PROCESS"]), xy=((result_PPRIORITY.iloc[i]["S"] + result_PPRIORITY.iloc[i]["E"])/2, 25+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  if i != len(result_PPRIORITY)-1:  
    length = result_PPRIORITY.iloc[i+1]["S"] - result_PPRIORITY.iloc[i]["E"]
    #print(i, length)
    if length > 0:
      gnt.broken_barh([(result_PPRIORITY.iloc[i]["E"], result_PPRIORITY.iloc[i]["E"] + length)], (25, width), facecolors = 'white')


gnt.broken_barh([(0, result_PRR.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_PRR)):
  # print([(result_PRR.iloc[i]["S"], result_PRR.iloc[i]["E"]), result_PRR.iloc[i]["PROCESS"]])
  gnt.broken_barh([(result_PRR.iloc[i]["S"], result_PRR.iloc[i]["E"])], (30, width), facecolors = processcolor.get(result_PRR.iloc[i]["PROCESS"]).tolist())
  gnt.annotate("%s"%(result_PRR.iloc[i]["PROCESS"]), xy=((result_PRR.iloc[i]["S"] + result_PRR.iloc[i]["E"])/2, 30+5/2-1), ha='center', va='center', c = 'white', fontsize = font_size)

  if i != len(result_PRR)-1:  
    length = result_PRR.iloc[i+1]["S"] - result_PRR.iloc[i]["E"]
    # print(i, length)
    if length > 0:
      gnt.broken_barh([(result_PRR.iloc[i]["E"], result_PRR.iloc[i]["E"] + length)], (30, width), facecolors = 'white')


"""
gnt.broken_barh([(0, result_FCFS.iloc[0]["S"])], (0, width), facecolors = 'white')
for i in range (0, len(result_FCFS)-1):
  length = result_FCFS.iloc[i+1]["S"] - result_FCFS.iloc[i]["E"]
  print(i, length)
  if length > 0:
    gnt.broken_barh([(result_FCFS.iloc[i]["E"], result_FCFS.iloc[i]["E"] + length)], (0, width), facecolors = 'white')
"""
#Save as image with png extension
plt.savefig(filename+"/"+filename+"_GanttChart.png")
plt.show()
#animation part
print("Creating animation...")
print("(It may take several tens of seconds depending on the environment)")

#Set the animation execution time to 5 seconds and determine the time slice
timeslice = 5/result_FCFS.iloc[len(result_FCFS)-1]["E"]
fig, gnt = plt.subplots()

plt.rcParams['figure.figsize'] = (10,10)
plt.title("Gantt Chart_Time", fontsize= 16, fontweight = 'bold')

gnt.set_xlabel("Time")
gnt.set_ylabel("Algorithm")
plt.xlim([0, result_FCFS.iloc[len(result_FCFS)-1]["E"]])
plt.ylim([0, 5*7])
plt.xticks(range(result_FCFS.iloc[len(result_FCFS)-1]["E"] + 1))
gnt.set_yticklabels(algorithm_list)
plt.box(False)
gnt.grid(True, linestyle='--')
width = 3.5

x, y = [], []
line, = plt.plot([], [], 'bo')

for i in range (0, len(result_FCFS)):
  gnt.annotate("%s"%(result_FCFS.iloc[i]["PROCESS"]), xy=((result_FCFS.iloc[i]["S"] + result_FCFS.iloc[i]["E"])/2, 0+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_FCFS.iloc[i]["PROCESS"]), xy=((result_FCFS.iloc[i]["S"] + result_FCFS.iloc[i]["E"])/2, 0+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_SJF)):
  gnt.annotate("%s"%(result_SJF.iloc[i]["PROCESS"]), xy=((result_SJF.iloc[i]["S"] + result_SJF.iloc[i]["E"])/2, 5+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_SJF.iloc[i]["PROCESS"]), xy=((result_SJF.iloc[i]["S"] + result_SJF.iloc[i]["E"])/2, 5+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_SRTF)):
  gnt.annotate("%s"%(result_SRTF.iloc[i]["PROCESS"]), xy=((result_SRTF.iloc[i]["S"] + result_SRTF.iloc[i]["E"])/2, 10+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_SRTF.iloc[i]["PROCESS"]), xy=((result_SRTF.iloc[i]["S"] + result_SRTF.iloc[i]["E"])/2, 10+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_RR)):
  gnt.annotate("%s"%(result_RR.iloc[i]["PROCESS"]), xy=((result_RR.iloc[i]["S"] + result_RR.iloc[i]["E"])/2, 15+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_RR.iloc[i]["PROCESS"]), xy=((result_RR.iloc[i]["S"] + result_RR.iloc[i]["E"])/2, 15+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_PRIORITY)):
  gnt.annotate("%s"%(result_PRIORITY.iloc[i]["PROCESS"]), xy=((result_PRIORITY.iloc[i]["S"] + result_PRIORITY.iloc[i]["E"])/2, 20+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_PRIORITY.iloc[i]["PROCESS"]), xy=((result_PRIORITY.iloc[i]["S"] + result_PRIORITY.iloc[i]["E"])/2, 20+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_PPRIORITY)):
  gnt.annotate("%s"%(result_PPRIORITY.iloc[i]["PROCESS"]), xy=((result_PPRIORITY.iloc[i]["S"] + result_PPRIORITY.iloc[i]["E"])/2, 25+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_PPRIORITY.iloc[i]["PROCESS"]), xy=((result_PPRIORITY.iloc[i]["S"] + result_PPRIORITY.iloc[i]["E"])/2, 25+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

for i in range (0, len(result_PRR)):
  gnt.annotate("%s"%(result_PRR.iloc[i]["PROCESS"]), xy=((result_PRR.iloc[i]["S"] + result_PRR.iloc[i]["E"])/2, 30+5/2-1.5), ha='center', va='center', c = 'white', fontsize = font_size-3, fontweight='bold')
  gnt.annotate("%s"%(result_PRR.iloc[i]["PROCESS"]), xy=((result_PRR.iloc[i]["S"] + result_PRR.iloc[i]["E"])/2, 30+5/2-0.5), ha='center', va='center', c = 'black', fontsize = font_size-3, fontweight='bold')

#Set action to be performed per default timeslice
def animate(t):
#["FCFS", "SJF", "SRTF", "RR", "PRIORITY", "PPRIORITY", "PRR"]
  x = t+0.5
  y = 1
  index = 0
  for i in range (0, t):
    if result_FCFS.iloc[index]["E"] == i+1:
      index+=1    
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_FCFS.iloc[index]["PROCESS"]).tolist(),s=500)
  
  if 0 <= t and t < result_FCFS.iloc[0]["S"]:
    #Animating with scatter using the rectangle maker option
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  #Consideration of cpu idle time
  for i in range(0, len(result_FCFS)-1):
    if result_FCFS.iloc[i]["E"] <= t and  t < result_FCFS.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)

  
  x = t+0.5
  y = 6
  index = 0
  for i in range (0, t):
    if result_SJF.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_SJF.iloc[index]["PROCESS"]).tolist(),s=500)
  
  if 0 <= t and t < result_SJF.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_SJF)-1):
    if result_SJF.iloc[i]["E"] <= t and  t < result_SJF.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)


  x = t+0.5
  y = 11
  index = 0
  for i in range (0, t):
    if result_SRTF.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_SRTF.iloc[index]["PROCESS"]).tolist(),s=500)
  
  if 0 <= t and t < result_SRTF.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_SRTF)-1):
    if result_SRTF.iloc[i]["E"] <= t and  t < result_SRTF.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)
  
  x = t+0.5
  y = 16
  index = 0
  for i in range (0, t):
    if result_RR.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_RR.iloc[index]["PROCESS"]).tolist(),s=500)
  
  if 0 <= t and t < result_RR.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_RR)-1):
    if result_RR.iloc[i]["E"] <= t and  t < result_RR.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)

  
  x = t+0.5
  y = 21
  index = 0
  for i in range (0, t):
    if result_PRIORITY.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_PRIORITY.iloc[index]["PROCESS"]).tolist(),s=500)
  if 0 <= t and t < result_PRIORITY.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_PRIORITY)-1):
    if result_PRIORITY.iloc[i]["E"] <= t and  t < result_PRIORITY.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)

  
  x = t+0.5
  y = 26
  index = 0
  for i in range (0, t):
    if result_PPRIORITY.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_PPRIORITY.iloc[index]["PROCESS"]).tolist(),s=500)
  if 0 <= t and t < result_PPRIORITY.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_PPRIORITY)-1):
    if result_PPRIORITY.iloc[i]["E"] <= t and  t < result_PPRIORITY.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)

  
  x = t+0.5
  y = 31
  
  index = 0
  for i in range (0, t):
    if result_PRR.iloc[index]["E"] == i+1:
      index+=1 
  plt.scatter(x,y, marker = 's', color = processcolor.get(result_PRR.iloc[index]["PROCESS"]).tolist(),s=500)
  if 0 <= t and t < result_PRR.iloc[0]["S"]:
    plt.scatter(x,y, marker = 's', color = 'white',s=500)
  for i in range(0, len(result_PRR)-1):
    if result_PRR.iloc[i]["E"] <= t and  t < result_PRR.iloc[i+1]["S"]:
      plt.scatter(x,y, marker = 's', color = 'white',s=500)

  



timeslice = 100/result_FCFS.iloc[len(result_FCFS)-1]["E"]
ani = FuncAnimation(fig=fig, func=animate, frames = np.arange(result_FCFS.iloc[len(result_FCFS)-1]["E"]), interval=timeslice, repeat = False)
animationsave = filename+"/"+filename + "_" + "GanttChartAnimation.gif"
#mpl.rcParams['animation.convert_path'] = 'magick'
#ani.save(animationsave, writer='imagemagick')
ani.save(animationsave, writer='pillow')
#plt.show()


"""표"""

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
    rows=list()
    avg_time=list()
    with open(table_file[i], 'r') as f:
        
        for line in f.readlines():
            Time_set=list()
            segments=line.split(" ")
            if len(segments)>4:
                rows.append("P"+segments[0])
                Time_set.append(segments[2])
                Time_set.append(segments[3])
                Time_set.append(segments[4])

                Time[i].append(Time_set)
            else: #average time
                avg_time.append(segments[0])
                avg_time.append(segments[1])
                avg_time.append(segments[2].rstrip())
    Time[i].append(avg_time)
    rows.append("Avg")
    rows_list.append(rows)
    # print(Time[i])


Time_FCFS = pd.DataFrame(Time[0], columns = ["waiting","turnaround","response"],index=rows_list[0])
# print(tabulate(Time_FCFS, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_SJF = pd.DataFrame(Time[1], columns = ["waiting","turnaround","response"],index=rows_list[1])
# print(tabulate(Time_SJF, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_SRTF = pd.DataFrame(Time[2], columns = ["waiting","turnaround","response"],index=rows_list[2])
# print(tabulate(Time_SRTF, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_RR = pd.DataFrame(Time[3], columns = ["waiting","turnaround","response"],index=rows_list[3])
# print(tabulate(Time_RR, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_PRIORITY = pd.DataFrame(Time[4], columns = ["waiting","turnaround","response"],index=rows_list[4])
# print(tabulate(Time_PRIORITY, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_PPRIORITY = pd.DataFrame(Time[5], columns = ["waiting","turnaround","response"],index=rows_list[5])
# print(tabulate(Time_PPRIORITY, headers='keys', tablefmt='fancy_grid', showindex=False))
Time_PRR = pd.DataFrame(Time[6], columns = ["waiting","turnaround","response"],index=rows_list[6])
# print(tabulate(Time_PRR, headers='keys', tablefmt='fancy_grid', showindex=False))

Time_pd=[Time_FCFS,Time_SJF,Time_SRTF,Time_RR,Time_PRIORITY,Time_PPRIORITY,Time_PRR]




"""percetage 비교"""

def cmp_avg(Time_pd,chart):
  index1=algorithm_list.index(chart[0])
  index2=algorithm_list.index(chart[1])
  avg_list1=Time[index1][-1]
  avg_list2=Time[index2][-1]

  print_table(Time_pd,index1)
  print_table(Time_pd,index2)
  # columns=["Waiting Time","Turnaround Time","Response Time"]
  for i in range(3):
    if float(avg_list1[i])>float(avg_list2[i]):
      print("average %s time of %s is %.2f%% slower than average %s time of %s"%(columns[i],chart[0],(float(avg_list1[i])/float(avg_list2[i])-1)*100,columns[i],chart[1]))
    elif float(avg_list1[i])<float(avg_list2[i]):
      print("average %s time of %s is %.2f%% faster than average %s time of %s"%(columns[i],chart[0],(float(avg_list2[i])/float(avg_list1[i])-1)*100,columns[i],chart[1]))
    else:
      print("average %s time of %s is same with average %s time of %s"%(columns[i],chart[0],columns[i],chart[1]))

"""표 출력

"""

def print_table(Time_pd,index):
  print("The time table of "+algorithm_list[index]+" is :")
  display(Time_pd[index])
  print()

"""gantt 출력"""

# def print_gantt(algorithm):
#   image_file=algorithm+'_GanttChart.png'
#   image_pil = Image.open(image_file)
#   image = np.array(image_pil)
#   fig, ax = plt.subplots()

#   ax.axis('off')

#   plt.imshow(image)
#   plt.show()

"""0. 간트차트 애니메이션
1. 전체 timetable, ganttchart
2. 2개 알고리즘 선택->timetable, ganttchart
3. 2개 알고리즘 선택->percentage 비교, timetable, ganttchart 
"""




while True:
    print("_____________________________________________________________________")
    print("                              "+"<MENU>")  
    print("---------------------------------------------------------------------")
    print("" + "1" + "  "+" for all time table")
    print("" + "2" + "  "+" for selecting one algorithm and displaying the time table")
    print("" + "3" + "  "+" for selecting two algorithms and comparing the average time")
    print("" + "4" + "  "+" for quit")
    print("_____________________________________________________________________")
    print()
    num=int(input("enter the number(1-4) > "))
    print()
    if num==1:
        for algorithm in algorithm_list:
            index=algorithm_list.index(algorithm)
            print_table(Time_pd,index)
    elif num==2:
        try:
            chart_input=input("enter an algorithm(FCFS, SJF, SRTF, RR, PRIORITY, PPRIORITY, PRR) > ")
            print()
            upper_chart=chart_input.upper()
            upper_chart in algorithm_list
            index=algorithm_list.index(upper_chart)
            print_table(Time_pd,index)
        except:
            print("You did enter the wrong algorithm!")
            chart_input=input("enter an algorithms(FCFS, SJF, SRTF, RR, PRIORITY, PPRIORITY, PRR) > ")
            print()
            upper_chart=chart_input.upper()
            index=algorithm_list.index(upper_chart)
            print_table(Time_pd,index)
        
    elif(num==3):
        try:
            chart_input=input("enter two algorithms(FCFS, SJF, SRTF, RR, PRIORITY, PPRIORITY, PRR) > ")
            print()
            upper_chart=chart_input.upper()
            chart=upper_chart.split(" ")
            cmp_avg(Time_pd,chart)
        except:
            print("You did enter the wrong algorithm!")
            chart_input=input("enter two algorithms(FCFS, SJF, SRTF, RR, PRIORITY, PPRIORITY, PRR) > ")
            print()
            upper_chart=chart_input.upper()
            chart=upper_chart.split(" ")
            cmp_avg(Time_pd,chart)
    elif num==4:
        for i in range(7):
            os.remove(table_file[i])
            os.remove(gantt_file[i])
        break
    else:
        print("wrong number.")

