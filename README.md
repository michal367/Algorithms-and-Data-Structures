# Algorithms and Data Structures

## Algorithms
### 1. Numbers
- even and odd
- divisible
- arithmetic sequence
- Euclidean algorithm - GCD
- coprime integers
- least common multiple - LCM
- extended Euclidean algorithm (modular multiplicative inverse)
- prime numbers
	- division check
	- Eratosthenes&#39; sieve
	- linear sieve
	- Atkin-Bernstein sieve
	- prime factors
		- division method
		- Fermat&#39;s method
	- primality test
		- naive
		- Chinese Primality Test
		- Fermat&#39;s little thorem
		- Miller-Rabin test
- pseudo-random number generator
	- LCG - Linear Congruential Generator
	- Park-Miller
	- Mersenne Twister
- generation without repetition
- Fibonacci numbers
- binary Fibonacci system
- integer square root
	- next squares
	- Newton method (Babylonian method)
	- binary digit by digit method
- square root (Babylonian method)
- a*b mod n
- a^b mod n

### 2. Arrays
- search
	- linear
	- linear with sentinel
	- binary
	- interpolation
- counting without and with sentinel
- shuffle
- max and min
- dominant
- majority element
- partitioning
- k-th largest element
- k-th largest element fast (quick select)
- median
- prefix sums

### 3. Strings
- split
- words counting
- longest word
- longest prefix-suffix
- pattern searching
	- naive
	- Morris-Pratt algorithm
	- Knuth-Morris-Pratt algorithm
	- Boyer-Moore algorithm simplified
	- Boyer-Moore algorithm
	- Karp-Rabin algorithm
- LCS - longest common substring
- LCS - longest common subsequence
- SCS - shortest common superstring
- square words
- palindromes
	- naive
	- Manacher&#39;s algorithm
- ciphers
	- substitution
		- Caesar cipher
		- pseudo-random shift
	- transposition
		- neighbour transposition
		- array transposition
		- pseudo-random transposition
	- Enigma cipher
	- RSA
- large numbers
	- adding
	- multiplying
	- exponentiating
	- large Fibonacci numbers
- hashtable
	- open addressing
	- separate chaining

### 4. Sorting
- selection sort
- insert sort
- heapsort


## Data Structures
### 1. List
- singly linked list
- doubly linked list
- singly linked cyclic list
- count doubly linked list (self organizing list - count method)

##### Algorithms
- singly linked list
	- remove duplicates
	- reverse list
	- insert sort
	- merge sort
	- linear search
	- linear search with sentinel
- doubly linked list
	- partition
	- quick sort
	- linear search
	- move-to-front method (MTF) search
	- transpose method search
- singly linked cyclic list
	- linear search
- count doubly linked list
	- count method search

### 2. Stack
- array implementation
- list implementation

### 3. Queue
- array implementation
- list implementation
- cyclic list implementation

### 4. Priority queue
- list implementation
- heap implementation

### 5. Set
- array implementation
- list implementation
- bitmap implementation
- hashtable implementation
- tree (BST) implementation

##### Algorithms
- union
- intersection
- difference
- complement
- is subset

### 6. Disjoint sets
- array implementation
- list implementation
	- doubly linked list
	- doubly linked list with prev=head
- tree implementation
	- with rank
	- without rank

### 7. Matrix
##### Algorithms
- transpose
- determinant
- Gauss elimination
- Gauss-Crout elimination
- LU decomposition
- LU solve
- LU determinant
- LU invert

### 8. Tree
- Tree
- Binary Tree
- BST - Binary Search Tree
- Red-Black Tree
- AVL
- Splay
- Heap
- Expression Tree

### 9. Graph
- adjacency matrix
- adjacency lists
- edge list
- incidence matrix

##### Algorithms
- DFS - depth first search
- BFS - breadth first search
- transpose
- square
- line graph
- DFS path
- BFS path
- is connected
- connected components
	- DFS
	- disjoint sets
- strongly connected components
	- naive
	- Kosaraju&#39;s algorithm
	- Tarjan&#39;s algorithm
- DF spanning tree
- BF spanning tree
- bridges
	- naive
	- Tarjan&#39;s algorithm
- articulation points
	- naive
	- Tarjan&#39;s algorithm
- is bipartite
- detect cycle
- find cycles
	- find cycle basis in undirected graph
	- find all cycles in directed graph - Johnson&#39;s algorithm
- exists Eulerian path and cycle
- Eulerian path and cycle
	- postorder algorithm
	- Fleury&#39;s algorithm
	- Hierholzer&#39;s algorithm - version with finding simple cycles
- Hamiltionian path and cycle
- topological sort
	- DFS
	- Kahn&#39;s algorithm
- vertex coloring
	- brute force
	- greedy
	- greedy - Largest First (LF)
- edge coloring
	- brute force
	- greedy - Largest First (LF)
- find cliques
	- Bron-Kerbosch algorithm
	- Bron-Kerbosch algorithm with pivoting
- maximum bipartite matching (augmenting path algorithm)
- Edmonds&#39; blossom algorithm - maximum matching in graph

### 10. Weighted graph
- adjacency matrix
- adjacency lists
- edge list
- incidence matrix
- multigraph (adjacency lists)

##### Algorithms
- Dijkstra&#39;s algorithm
- Bellman-Ford algorithm
- Floyd-Warshall algorithm
- travelling salesman problem (shortest Hamiltonian cycle)
- shortest Hamiltonian path
- minimum spanning tree (MST)
	- Kruskal&#39;s algorithm
	- Prim&#39;s algorithm
- Hungarian algorithm (max-weight/min-weight max-cardinality bipartite matching)
- chinese postman problem in directed graph (in mulitgraph)

### 11. Flow network
- adjacency matrix
- adjacency lists

##### Algorithms
- maximum flow
	- Edmonds-Karp algorithm
	- Dinic&#39;s algorithm

### 12. STL containers
- vector
- vector with iterator
- vector with iterator and allocator
- list with iterator

### 13. String


## Programs
- number system conversion
- Fibonacci numbers matrix
- math parser - parse and evaluate math expressions using RPN (Reverse Polish Notation)
- master mind - code-breaking game
- prefix-free coding
- Huffman coding
- labyrinth - BFS solver
- max bipartite matching - using max flow algorithm in flow network

