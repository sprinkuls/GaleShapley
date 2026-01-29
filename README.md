# Gale-Shapley

Name: Kaitlyn Tran
UFID: 79518935

Name: May Macler
UFID: 26170596

GaleShapley.cpp: The source code for the Gale-Shapley matching engine (Task A)

exampleFiles/example.in: A sample input file following the assignment specification.
exampleFiles/example.out: The output expected from the matching engine.

To compile the matcher, use a C++ compiler (like g++):
    g++ -o test GaleShapley.cpp
Then run:
    ./test
Copy paste input from example.in, and then click enter. The program should print out the matched output.

You can also generate a random input of size 'n' by passing an integer as an argument.
For example, to generate output for 5 hospitals/students, run:
```
./test 5
```
and you'll see output for the generated data.

To test scalability/runtime, run:
    ./test --test
This will return the average time taken for the algorithm to execute for increasing numbers of hospitals/students.

Assumptions & Constraints
    The input must start with an integer n, followed by n lines of hospital preferences and n lines of student preferences.
    Requires a C++11 compatible compiler. No external libraries are needed.
