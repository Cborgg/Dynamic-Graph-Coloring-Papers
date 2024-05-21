# Dynamic-Graph-Coloring-Papers

**1. Effective and Efficient Dynamic Graph Coloring (2017) (ACM) - http://www.vldb.org/pvldb/vol11/p338-yuan.pdf**

The main contributions are as follows:

Global Optimization: The authors propose a new idea for updating graph coloring by considering global optimization, addressing the drawbacks of existing local update algorithms

Efficient Algorithm: They introduce an efficient color-propagation based algorithm with bounded time complexity, which explores a limited number of vertices for updates

They do so by designing a color-propagation based algorithm which only explores the vertices within the 2-hop neighbors of the update-related and color-changed vertices. They then propose a novel color index to maintain some summary color information and, thus, bound the explored vertices within the neighbors of these vertices. Moreover, they derive some effective pruning rules to further reduce the number of propagated vertices.

**2. Improved Dynamic Graph Coloring (2020) (ACM Transactions on Algorithms (TALG)) - https://arxiv.org/pdf/1904.12427**

The authors’ two main contributions in this paper are:

New Algorithm for General Graphs: They present a new algorithm that significantly improves upon the trade-off between the number of colors and recolorings per update step in dynamic graph coloring. For any given parameter β > 0, their algorithm achieves a coloring with Oˆ(C/β log^2 n) colors and only O(β) recolorings per update, where C is the number of colors used by a static algorithm and n is the number of vertices.

Deterministic Algorithm for Sparse Graphs: They introduce a deterministic algorithm for uniformly sparse graphs, which utilizes low out-degree orientations and a new data structure to maintain an O(α log^2 n)-coloring in amortized O(1) time for graphs of arboricity α, where α is a measure of the graph’s sparsity.

**3. Dynamic Graph Coloring (2017) (Springer) - https://arxiv.org/pdf/1708.09080**

Here are the main findings of this paper:

Dynamic Coloring Algorithms: The paper presents two algorithms for maintaining a proper coloring of a graph during insertions and deletions of vertices and edges, offering different trade-offs between the number of colors used and the number of vertex recolorings required.

Trade-off Balance: For a given parameter (d), the first algorithm maintains an ( O(CdN^{1/d}) )-coloring with at most (O(d)) recolorings per update, while the second algorithm maintains an (O(Cd))-coloring with (O(dN^{1/d})) recolorings per update where C and N are the maximum chromatic number and maximum number of vertices respectively.

Lower Bound: A lower bound is established, demonstrating that any algorithm maintaining a ( c )-coloring of a 2-colorable graph must recolor at least (Omega(N^{2/c(c-1)})) vertices per update for any constant c>=2
