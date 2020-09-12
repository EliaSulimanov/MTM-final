# GCalc - Graph Calculator
Technion Introduction to System Programming (234124) final project.  
Grade: 96.

This readme is under construction.

## Contents
 - [About The Project](#About-The-Project)
 - [Usage](#Usage)
    - [Defining a new variable](#Defining-a-new-variable)
    - [Assigning the result of an expression into another variable](#Assigning-the-result-of-an-expression-into-another-variable)
    - [Runing one of the commands supported by the calculator](#Runing-one-of-the-commands-supported-by-the-calculator)
    - [Notice](#Notice)
 - [Calculator Commands](#Calculator-Commands)
    - [print(G)](#printg)
    - [delete(G)](#deleteg)
    - [who](#who)
    - [reset](#reset)
    - [quit](#quit)
    - [Notice](#Notice-1)
 - [License](#License)

## About The Project
Graph (discrete mathematics) is a structure amounting to a set of objects in which some pairs of the object are in some sense "related". ([Wikipedia](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)))  
Each object represents an element, for example a city, a person, a computer server.  
A graph describes the relationship between the elements, for example a network of users in a social network.  
The people are represented through the vertices and the connections between them through edges.  
![Graph Demo](Readme/graph_demo.PNG)  
This program is a shell graph calcutalor, which lets you unite, intersect, substract, cross and find the complement of a graph.
"Gcalc>" tag will be prompted in the shell.

## Usage
### Defining a new variable
First you declere the graph name, than you use the graph syntax to describe the graph:  
```Gcalc> G1={a,b | <a,b>}```  

You can also assign an existing graph to a new variable:  
```Gcalc> G2=G1 ```

### Assigning the result of an expression into another variable  
```Gcalc> G1 = !G0```  
```Gcalc> G3 = {a,b | <a,b>} + G2```  

### Runing one of the commands supported by the calculator
```Gcalc> print(myGraph)```

#### Notice
* Graph name can only contain alphanumeric characters.
* Variables, vertices, edges and function names are case-sensitive.
* Spaces can separate elements of a phrase or command, but not allowed within names. For example, ```myGraph    = G1+  G2``` allowed, but ```G 1 = !G2``` not.
* If the expression on the right side of the assignment contains an error, then the variable value on the left does not change.
* A graph name that appears for the first time on the right side of a phrase (or as an argument of a command) without being previously defined carries an error.

## Calculator Commands
### print(G)
Print the content of the graph.
```
Gcalc> myGraph={x, y, z | <x,y>, <y,z>, <z,x>}
Gcalc> print(myGraph)
x
y
z
$
x y
y z
z x
```
### delete(G)
Delete the graph named "G".
### who
Displays a list of all variables (graphs) defined.
```
Gcalc> who
G1
G2
```
### reset
Delete all the existing graphs.
### quit
Quit the graph calculator.

#### Notice
Function names are reserved words, they cannot be used as names of variables (graphs).


## License
The Unlicense.  
How many hours did you spend reading the license of libraries you wanted to use?  
How many times have you given up on contributing to an open source project just because its license did not suit your taste for open source?  
The code of my project is dedicated to the public domain, for free use in any form you choose.  
For more details, please read the license file.
