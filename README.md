# Sample Output

data = "ABCDEFGGGABS"

```
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
huffman tree: array view

huffman tree array size: 15
huffman tree leaf count: 8

0: (S) : 1
1: (F) : 1
2: (E) : 1
3: (D) : 1
4: (C) : 1
5: 2 - 3 : 2
6: 0 - 1 : 2
7: (B) : 2
8: (A) : 2
9: 4 - 5 : 3
10: (G) : 3
11: 6 - 7 : 4
12: 8 - 9 : 5
13: 10 - 11 : 7
14: 12 - 13 : 12

10878977,9175041,9043969,8912897,8781825,327682,65538,8650754,8519682,589827,9306115,851972,1114117,1376263,1638412,
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
huffman tree: tree view

                        | B - 2 [1111]
                4 [111]
                                | F - 1 [11101]
                        2 [1110]
                                | S - 1 [11100]
        7 [11]
                | G - 3 [110]
12 [1]
                                | D - 1 [10111]
                        2 [1011]
                                | E - 1 [10110]
                3 [101]
                        | C - 1 [1010]
        5 [10]
                | A - 2 [100]
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
huffman code

(A) - 100
(B) - 1111
(C) - 1010
(D) - 10111
(E) - 10110
(F) - 11101
(G) - 110
(S) - 11100
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
compressed data

00111010011101101101101010001111
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
uncompressed data

010000010100001001000011010001000100010101000110010001110100011101000111010000010100001001010011
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
data_size = 12
comp_size = 4
compression ratio = 66.67%
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
```