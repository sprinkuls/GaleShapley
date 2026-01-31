# Gale-Shapley

Name: Kaitlyn Tran  
UFID: 79518935  

Name: May Macler  
UFID: 26170596  

## Files
`src/GaleShapley.cpp`: The source code for the Gale-Shapley matching engine (Task A), the verifier (Task B), and the scalability testing suite (Task C).  
`runtimeData/AlgosRuntime.xlsx`:  The graphed data for the runtimes of the matcher and verifier.  
`exampleFiles/example.in`: A sample input file following the assignment specification.  
`exampleFiles/example.out`: The output expected from the matching engine corresponding with example.in.  

There are other example inputs in the `exampleFiles/` directory as well, named after the size 'n' of the input. For example, `exampleFiles/example16.in` is input of size 16 to be passed in, and `exampleFiles/example16.out` is the expected output when this input is passed to the program.

## Match Generation
To compile the matcher, use a C++ compiler (like g++):  
```
g++ -std=c++11 -o test GaleShapley.cpp
```

To run the matcher and manually provide input:  
```
./test
```
Copy and paste input from `example.in`, and then click enter. The program will print out the generated matchings.  

You can also generate a random input of size 'n' by passing an integer as an argument.
Matchings for this input will then be created.  
For example, to generate output for 5 hospitals/students, run:  
```
./test 5
```
and you'll see output for the generated data, something like this:
```
Hospital Rankings:
H1 | 4 1 5 3 2 
H2 | 3 4 1 2 5 
H3 | 1 2 3 4 5 
H4 | 1 4 2 5 3 
H5 | 1 5 2 4 3 
Student Rankings:
S1 | 4 2 5 3 1 
S2 | 5 1 4 2 3 
S3 | 4 2 5 3 1 
S4 | 2 5 3 4 1 
S5 | 1 3 5 4 2 
Matchings:
1 4
2 3
3 2
4 1
5 5
```

## Match Verification
To manually test verifier capabilities, run:  
```
    ./test --verify
```
This will generate a random match and test if the match is stable. It will then force a duplicate match, and use
the verifier to test if the verifier catches that it is invalid.

## Runtime Testing
To test scalability/runtime, run:  
```
./test --test
```
This will return the average time taken for the algorithm to execute for increasing numbers of hospitals/students, and for the verifier to verify the matches.
Graphs are stored in `AlgosRuntime.xlsx`. This contains the data and the corresponding graphs for one run of `./test --test`  

![Graphs of Running Time](runtimes.png)

Both the matching engine and the verifier show a trend of O(n^2). As n increases, the time taken grows at a rate of n^2, which is expected for the G-S algorithm.

The matching engine is more efficient than the verifier at higher values of n. For n = 1024, the engine takes 1266
microseconds while the verifier takes 77653 microseconds.

The steeper curve for the Verifier is due to checking all potential blocking pairs and the O(logn) overhead of the set data structure used for stability checking. Building the hospitalBetter and studentBetter sets requires n^2 insertions, and checking for blocking pairs requires n^2 searches. In a set, these operations are logarithmic,resulting in an effective complexity of O(n^2 logn).

## Assumptions & Constraints
It is assumed that the provided preference lists are valid permutations of the set {1,2,...,n} for both hospitals and students.  
The input must start with an integer n, followed by n lines of hospital preferences and n lines of student preferences.  
Requires a C++11 compatible compiler. No external libraries are needed.  
