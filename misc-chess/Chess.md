# Chess

## Idea

The basic idea came from [5D Chess With Multiverse Time Travel](https://store.steampowered.com/app/1349230/5D_Chess_With_Multiverse_Time_Travel/).

However, our server is not powerful enough to support a strong AI for 5D chess game(even a good one).

I also found a chess library based on python called python-chess from github. I thought it was strong enough to handle normal chess game, but it turned out that I was so wrong and here are so many bugs due to its implements.

The idea is that players could do "time travel" to make effects to those chessboards in the past with two hidden parameters.

| Step kinds       | From_square | To_square | From_timepoint  | To_timepoint      |
| ---------------- | ----------- | --------- | --------------- | ----------------- |
| Normal step      | from        | to        | (max_timepoint) | (max_timepoint+1) |
| Time travel step | from        | to        | from_t          | to_t              |

Players are supposed to try different steps to get at most two kinds of endings:

1. Normal end: Player win or lose in a normal chess game. 
2. Cheating end: AI cheated(She use time travel steps).
3. Bugs. Sorry for that.



### EXP

```
1 18
18 28 2 0
28 45 0 0
1 18 0 0
18 28 0 0
28 43 0 0
```

This exp could make a double check situation in the chessboard 0. 

Other exps are also accepted.



## Source code

./chess