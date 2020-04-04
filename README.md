# LCA_Algorithms
 Implementation & speed test of some LCA (Lowest Common Ancestor) algorithms.

## Algorithms
Implemented alogrithm list:
- [Simple sparse table](LCA/Onlogn_Ologn.h). 
- [Covert to RMQ for constant query time](LCA/Onlogn_O1.h)
- [Farach-Colton and Bender Algorithm, O(n) initiation time](LCA/On_O1.h)

## Requirements: 
- g++ (--std=c++17) 
- python3 (if you want to do the speed test yourself)

## How to use:
If you just want to use the code for competitive programming or stuff, download the header file you need in [LCA](LCA/) and the [edge.h](header/edge.h) file. 

See [Example](example/) for example cpp files.

For doing the speed test:
- Clone this repo
- Just simply run speed_test.py by `python speed_test.py` (or `python3`) and wait, check the result in `resuilt.csv` file (you can open it with Excel)
- If you wanna add your own test set, please see the [Test format](#test-format) section below. I also code a test generator [here](generator/), see guide in [Test generator](#test-generator)

## Speed test
I run a speed test with my random test set. Check the result in [result.csv](result.csv)

## Test format
If you want to use you onw test set, please format those test as follow:
- First line: n (number node of the tree), r (index of root node)
- Next n-1 lines: each line containts 2 number (u, v) present an edge between not u and v (it can be directed or not)
- Next line: q (number of query)
- Next q lines: each line containts 3 number (u, v, lca) which are node u, v and LCA of (u, v)

Save it as a `txt` file and move it to `tests` folder.

## Test generator
First, compile the [generator.cpp](generator/generator.cpp) to an executable file with g++ (emxample: `g++ -O2 -std=c++17 -o generator/generator.cpp generator.exe`)

Then run the excutable file in command line with these paramaters: `generator.exe t n q`
- "t" is type of tree you wanna generate, currently it only accept "line" and "random" tree.
- "n" is number nodes of tree
- "q" is number of LCA queries

Example: `generator.exe random 10 10` will generate a random tree with 10 nodes and have 10 LCA queries

To add test(s) by the generator to the speed test, add its parameters to [test_parrams](generator/test_params.txt) file

## Note
it could cause stack-overflow if tree is deep, please inscrease stacksize if you are testing with large tests. With degenerate tree (line) has 10^6 node, consider to inscrease stacksize upto 60MB.