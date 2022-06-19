# OS-Term-Project
Korea Univ. 2022 Spring COSE341 Operating System_TEAM 3
<br/>
- [OS-Term-Project](#os-term-project)
    + [Development environment](#development-environment)
  * [Specification](#specification)
  * [How to use](#how-to-use)
  * [Results for some test cases](#results-for-some-test-cases)
  * [Function diagram](#function-diagram)
  * [Features](#features)
    + [Main idea](#main-idea)
  * [Main issues discussed](#main-issues-discussed)
    + [Development Technical Documentation](#development-technical-documentation)
    + [Meeting Record](#meeting-record)
  * [Development Timeline](#development-timeline)
  * [Contributor](#contributor)

<br/>

> `Implement First Come First Served, Shortest Job First, Shortest Remaining Task First, Round Robin, Priority, Preemptive Priority, Non-preemptive Priority with Round Robin scheduling algorithm learned in class and derive` **Gantt chart, Waiting time, Response time and Turn around time**.
> 
>   `Based on the results of each algorithm, the understanding of algorithm is improved. Furthermore, based on the output, the scheduling algorithm adopted by modern systems is understood centering on Linux's Complete Fair Scheduler (CFS).`


### Development environment
- [ ] Scheduling algorithm : C
- [ ] Evaluation Module : Python

![image](https://user-images.githubusercontent.com/53131824/174296407-eed044d3-1bc0-4b58-84fe-5fa1ef0dbc85.png)



## Specification
Visualization of scheduling results and Gantt chart for the 7 algorithms below
- First Come First Served
- Shortest Job First 
- Shortest Remaining Time First 
- Round Robin 
- Non-Preemptive Priority 
- Preemptive Priority
- Non-Preemptive Priority with RR 


## How to use
![image](https://user-images.githubusercontent.com/53131824/174461003-5195c44a-cc60-4067-94ce-d41ac274568d.png)
![image](https://user-images.githubusercontent.com/53131824/174460444-3c128857-606f-442e-94b2-ae676e1efed0.png)
1. **Download part1_final.exe and part2_final.exe to the same path.**
2. **Create a subfolder in the path where step 1 was performed, and create test data as a txt file in the created folder.**  
**(The most important thing in step 2 is that the name of the created subfolder and the name of the test data txt file should be the same.)**

## Results for some test cases
### C part_Shell output

![image](https://user-images.githubusercontent.com/53131824/174460316-e732135e-4dd4-4d9b-8f91-7197325e637d.png)
**_NOTE: Results for the 7 scheduling algorithms are output to the shell in the format above._**

### C part_txt data file
![image](https://user-images.githubusercontent.com/53131824/174460370-16174c36-d4ec-47c9-ba83-2b56a3d08d4a.png)
**_NOTE: Results for 7 scheduling algorithms are saved with txt extension for use in Gantt chart visualization, evaluation module._**
**_NOTE: txt data file의 format은 https://github.com/ghpk98/OS-Term-Project/issues/9
에 정리되어 있습니다_**

### Python part_Gantt chart
![image](https://user-images.githubusercontent.com/53131824/174294140-a89e44b5-47de-4087-8518-bd0e4df142f2.png)

![test2_GanttChartAnimation](https://user-images.githubusercontent.com/53131824/174293824-37e81c2f-77af-4a5a-b209-444bacdd12fa.gif)
**_NOTE: Input data_ https://github.com/ghpk98/OS-Term-Project/blob/main/simulator/test2/test2.txt_**

**_NOTE: The executable file, which is the output of this project, provides a Gantt chart of the PNG and GIF extensions._**


## Function diagram
![final function diagram](https://user-images.githubusercontent.com/53131824/169515901-9eedf780-e1f4-440e-839f-6380815709c0.jpg)
**_NOTE: that all input/output data is processed with txt extension._**


## Features
### Main idea 
알고리즘별 스케줄링과 간트 차트 및 알고리즘 비교를 각각 C, Python으로 진행하였습니다. 수업시간에 배운 layering 개념을 활용해보았습니다. Layering은 운영체제의 복잡도를 낮추기 위한 방안 중 하나로 계층을 나누는 것입니다. 각 계층은 인접한 계층과 통신할 수 있습니다. 이를 통해 각 계층 사이의 interface와 semantics만 맞추면 개발과 유지 및 보수가 쉽고 언어에 따라 실행 파일을 분리함으로써 불필요한 자원을 회수할 수 있습니다. 예를 들어 간트 차트를 생성할 때는 스케줄링에 필요한 priority queue와 ready queue가 필요하지 않기 때문에 이러한 자료구조들은 더 이상 유지하지 않아도 됩니다. 즉, 메모리와 CPU 자원 사용 측면에서 유리합니다. 

||Features|
|:--------:|-------|
|1.	개발 진행 용이|알고리즘 구현 계층과 평가 모듈 구현 계층의 입출력 format(face between layer)만 맞춘다면 동시 개발이 가능합니다. 이 덕분에 실제 텀 프로젝트 동안 UI 팀이 알고리즘 팀의 코드를 기다리지 않고 주어진 기간을 십분 활용할 수 있었습니다. 즉, 알고리즘 구현 계층의 출력 형식을 엄격하게 지키면 이를 평가 모듈 구현 계층의 입력으로 사용하는 UI의 동시 개발이 가능합니다|
|2.	유지 보수 용이|계층 간 interface와 semantics만 맞추면 되기 때문에 추가 기능 구현이 용이합니다. 다른 추가적인 평가 모듈 확장을 원할 경우 알고리즘 구현 계층의 내부 동작방식을 모르더라도 출력 양식만 확인하여 개발이 가능합니다.|
|3. 계층별 최적의 프로그래밍 언어 선택|각 계층별 적합한 언어 선택이 가능했습니다. Computation 속도가 상대적으로 좋은 C언어로 알고리즘 계층을 구현하고 다양한 시각화 모듈을 지원하는 python을 평가 모듈 계층에 사용하였습니다.|
|4. 편리한 테스트 데이터 관리|각 테스트 데이터들을 개별 폴더로 관리할 수 있도록 하였습니다. 실행파일을 설치한 경로에 test data(txt file)을 test라는 폴더 내에 포함시키면 알고리즘 구현 계층에서 생성한 알고리즘별 스케줄링 결과(txt file)와 평가 모듈에서 생성한 간트차트(png, gif file)를 해당 폴더에 저장하도록 하였습니다. 사용자는 test data를 포함하는 폴더 이름만 프로그램에 입력하면 모든 기능을 사용할 수 있습니다.|

## Main issues discussed
### Development Technical Documentation
- Corner case : https://github.com/ghpk98/OS-Term-Project/issues/10
- Animation Ideas : https://github.com/ghpk98/OS-Term-Project/issues/12
- Python Part Executable File Excessive Execution Time Problem : https://github.com/ghpk98/OS-Term-Project/issues/14

### Meeting Record
- 2nd BREAKOUT MEETING : https://github.com/ghpk98/OS-Term-Project/issues/2
- 3rd BREAKOUT MEETING : https://github.com/ghpk98/OS-Term-Project/issues/5


## Development Timeline
![image](https://user-images.githubusercontent.com/53131824/174292732-065c58e1-d1c7-4b56-b05e-44ed862e3b93.png)



## Contributor
|Member|Contributions|Contact|
|:-:|-------|-|
|손혜강</br>_(Leader)_|+ Function implementation (Python : Gantt chart image⦁animation and executable file generation)</br>+ Project scheduling and management **[responsibility]**</br>+ GitHub Management</br>+ Structural design and final report creation|oss67820@korea.ac.kr|
|박건호|+ Write Skeleton code and create executable file</br>+ Algorithm implementation (C language : FCFS, SJF, RR, non-preemptive priority, non-preemptive priority with RR)</br>+ GitHub Management **[responsibility]**</br>+ Build testcase and write final report| |
|조혜민|+ Algorithm implementation (C language - SRTF, preemption priority)</br>+ Presentation planning (responsibility)</br>+ Final report preparation **[responsibility]**| |
|홍지선|+ Function implementation (Python – time table function and code collection)</br>+ Test plan management **[responsibility]**</br>+ Meeting management and final report creation| |
