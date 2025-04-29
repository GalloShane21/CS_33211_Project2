# CS 33211 Operating Systems Project 2: Bankers Algorithm for Deadlock Avoidance
 Bankers Algorithm for Deadlock Avoidance Project

 ## Project Description (Instructions given in class)
Consider a system with 
five processes P0 through P4 and three resources of type A, B, C.
Type A has ten instances 
Type B has 5 instances
Type C has 7 instances

![image](instructionPicture.png)

Implement the Banker's algorithm to answer the following question: Is the system in a safe state? If yes, then what is the safe sequence?


## To Compile and run
Compile and run using these commands in your Linux terminal

```bash
g++ bankers.cpp utils.cpp -o banker
./banker input.txt
```

## Examples
