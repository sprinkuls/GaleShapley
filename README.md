# Gale-Shapley

Name: Kaitlyn Tran
UFID: 79518935

Name: May Macler
UFID: 26170596

GaleShapley.cpp: The source code for the Gale-Shapley matching engine (Task A), the verifier (Task B), and the scalability testing suite (Task C).

exampleFiles/example.in: A sample input file following the assignment specification.
exampleFiles/example.out: The output expected from the matching engine corresponding with example.in.

To compile the matcher, use a C++ compiler (like g++):
    g++ -std=c++11 -o test GaleShapley.cpp

To run the matcher and manually provide input:
    ./test
Copy and paste input from example.in, and then click enter. The program will print out the matched output.

You can also generate a random input of size 'n' by passing an integer as an argument.
For example, to generate output for 5 hospitals/students, run:
```
./test 5
```
and you'll see output for the generated data.

To manually test verifier capabilities, run:
    ./test --verify
This will generate a random match and test if the match is stable. It will then force a duplicate match, and use
the verifier to test if the verifier catches that it is invalid.

To test scalability/runtime, run:
    ./test --test
This will return the average time taken for the algorithm to execute for increasing numbers of hospitals/students, and for the verifier to verify the matches.

Graphs are within:
    AlgosRuntime.xlsx
This contains the data and the corresponding graphs for one run of ./test --test.

Both the matching engine and the verifier show a trend of O(n^2). As n increases, the time taken grows at a rate of n^2, which is expected for the G-S algorithm.

The matching engine is more efficient than the verifier at higher values of n. For n = 1024, the engine takes 1266
microseconds while the verifier takes 77653 microseconds.

The steeper curve for the Verifier is due to checking all potential blocking pairs and the O(logn) overhead of the set data structure used for stability checking. Building the hospitalBetter and studentBetter sets requires n^2 insertions, and checking for blocking pairs requires n^2 searches. In a set, these operations are logarithmic,resulting in an effective complexity of O(n^2 logn).

Assumptions & Constraints
    It is assumed that the provided preference lists are valid permutations of the set {1,2,...,n} for both hospitals and students.

    The input must start with an integer n, followed by n lines of hospital preferences and n lines of student preferences.
    
    Requires a C++11 compatible compiler. No external libraries are needed.
