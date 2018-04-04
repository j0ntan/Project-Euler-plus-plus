/* Lattice paths
 * Starting in the top left corner of a 2×2 grid, and only being
 * able to move to the right and down, there are exactly 6 routes
 * to the bottom right corner.
 *
 * How many such routes are there through a 20×20 grid? */

#include <iostream>
#include <vector>

unsigned countPaths(unsigned);
void moveRight(unsigned, unsigned, const unsigned&, unsigned&);
void moveDown(unsigned, unsigned, const unsigned&, unsigned&);

long long calculatePaths(const unsigned);

int main() {
    //std::cout << countPaths(20u);
    std::cout << calculatePaths(20u);
}

void moveRight(unsigned x, unsigned y, const unsigned& size, unsigned& count) {
    ++x;

    if( x < size )
        moveRight(x,y,size,count);
    if( y < size )
        moveDown(x,y,size,count);
    if( x == size and y == size )
        ++count;
}

void moveDown(unsigned x, unsigned y, const unsigned& size, unsigned& count) {
    ++y;

    if( x < size )
        moveRight(x,y,size,count);
    if( y < size )
        moveDown(x,y,size,count);
    if( x == size and y == size )
        ++count;
}

unsigned countPaths(unsigned size) {
    // this solution takes too long for large grid size
    unsigned pathCount = 0;
    unsigned x = 0, y = 0;

    moveRight(x,y,size,pathCount);
    moveDown(x,y,size,pathCount);

    return pathCount;
}

long long calculatePaths(const unsigned size) {
    // init grid boundaries
    std::vector<std::vector<long long>> grid(size+1, std::vector<long long>(size+1, 1));

    for( int i=size-1; i >= 0; --i)
        for( int j=size-1; j >= 0; --j)
            grid[i][j] = grid[i+1][j] + grid[i][j+1];
    return grid[0][0];
}