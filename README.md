This project focuses on the application of graph data structures and the graph coloring problem to tackle a real-world issue in computer science known as Register Allocation.

When a C++ program is compiled, the compiler must decide where variables will be stored. This process of variable assignment, known as Register Allocation, can be inefficient or efficient based on the optimal usage of available registers. The number of available registers is limited and is dependent on the processor architecture, thus it's crucial to make effective use of them.

The project is divided into two primary parts:

Implement a Graph Data Structure: The first task is to build a specific kind of graph called an Interference Graph. Nodes in this graph represent variables, and edges between them symbolize overlapping lifetimes.

Solving Register Allocation via Graph Coloring: The second task involves leveraging the constructed Interference Graph to solve the Register Allocation problem. The objective here is to optimally assign variables to the limited registers available, thus mimicking the Graph Coloring problem.

The Interference Graph will be provided in the form of a CSV file. The project also places a strong emphasis on writing comprehensive unit tests to ensure the correct functionality of the graph data structure and the register allocation algorithm.

In essence, this project is a practical application of data structures, graph theory, and compiler construction to optimize the register allocation process during program compilation.
