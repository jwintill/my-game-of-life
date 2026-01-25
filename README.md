# My Game of Life
I recently learned about cellular automatas other than Conway's Game of Life, so I've started implementation of my own. 
## How It's Made:

**Tech used:** C++, SDL2

I started with a simple implementation of Conway's Game of Life. I used C++ because although it isn't mean for visuals, it's what I'm doing in school so I wanted to continue use of it. I use a 2D arry to store the cells. I have tried using a 1D array before and although it maybe more optimized, I found it hard to understand and the optimal solution isn't really what my goal is. After Conway's was fully implemented I've now started making it smoother one step at a time, starting with colors then rules. The first new rule set I implemented was almost completely taken from Stephen Rafler's SmoothLife

**Link to Rafler's paper:** https://arxiv.org/pdf/1111.1567

## Optimizations

As stated previously optimizations aren't my main goal but they've still been made throughout development. I started with manually building and running through terminal with g++ and although it worked it greatly slowed devolopment so I've used CMake for the first time and created the CMakeLists.txt file which has made the process of building and running much simpler and faster.

## Lessons Learned:

Although I'm still inexperienced, if something interests me, pursuing it can yield great results! The current state is not only way further than I though I would get, but I understand C++, CMake, and cellular automatas much more.