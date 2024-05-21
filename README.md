# Dynamic-Graph-Coloring-Papers
Contains various references to Dynamic Graph Coloring research papers

1. Effective and Efficient Dynamic Graph Coloring (2017) - http://www.vldb.org/pvldb/vol11/p338-yuan.pdf

2. Improved Dynamic Graph Coloring (2020) - https://arxiv.org/pdf/1904.12427

We devise a new algorithm for general graphs that improves significantly upon the first
trade-off in a wide range of parameters: For any β > 0, we get a Oˆ(C/β log^2n)-coloring with O(β) recolorings per update, where the Oˆ notation supresses polyloglog(n) factors. In particular, for β = O(1) we get constant recolorings with polylog(n) colors.
For uniformly sparse graphs, the paper presents an algorithm that uses low out-degree orientations to improve update time rather than just the number of recolorings, leading to an amortized O(1) time for maintaining an O(α log² n)-coloring.
