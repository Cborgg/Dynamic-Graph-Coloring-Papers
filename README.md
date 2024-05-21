# Dynamic-Graph-Coloring-Papers
Contains various references to Dynamic Graph Coloring research papers

1. Effective and Efficient Dynamic Graph Coloring (2017) - http://www.vldb.org/pvldb/vol11/p338-yuan.pdf

The main contributions are as follows:
Global Optimization: The authors propose a new idea for updating graph coloring by considering global optimization, addressing the drawbacks of existing local update algorithms
Efficient Algorithm: They introduce an efficient color-propagation based algorithm with bounded time complexity, which explores a limited number of vertices for updates

 We design a color-propagation based algorithm which only explores the vertices within the 2-hop neighbors of the update-related and color-changed vertices. We then propose a novel color index to maintain some summary color information and, thus, bound the explored vertices within the neighbors of these vertices. Moreover, we derive some effective pruning rules to further reduce the number of propagated vertices.

3. Improved Dynamic Graph Coloring (2020) - https://arxiv.org/pdf/1904.12427

The authors’ two main contributions in this paper are:

New Algorithm for General Graphs: They present a new algorithm that significantly improves upon the trade-off between the number of colors and recolorings per update step in dynamic graph coloring. For any given parameter β > 0, their algorithm achieves a coloring with Oˆ(C/β log^2 n) colors and only O(β) recolorings per update, where C is the number of colors used by a static algorithm and n is the number of vertices.

Deterministic Algorithm for Sparse Graphs: They introduce a deterministic algorithm for uniformly sparse graphs, which utilizes low out-degree orientations and a new data structure to maintain an O(α log^2 n)-coloring in amortized O(1) time for graphs of arboricity α, where α is a measure of the graph’s sparsity.
