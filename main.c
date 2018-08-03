#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    unsigned long long i;
    unsigned long long j;
} Pair;

#define MatrixSz 300
#define VisitSz 300

char visitedMatrix[MatrixSz][MatrixSz];
Pair toVisit[VisitSz];

unsigned long long power(unsigned long long val, unsigned long long exp)
{
    unsigned long long res = 1;
    unsigned long long i;
    for (i = 0; i < exp; ++i)
        res *= val;

    return res;
}

unsigned long long a3smoothNumber(unsigned long long N)
{
    if (N == 0)
        return 1;

    Pair *pair;
    Pair pairCopy;
    unsigned long long visited = 0;
    unsigned long long res = 1;
    unsigned long long val;
    unsigned long long i, j, I;
    for (i = 0; i < MatrixSz; ++i)
        memset(visitedMatrix + i, 0, MatrixSz);

    visitedMatrix[0][0] = 1;

    toVisit[visited].i = 1;
    toVisit[visited].j = 0;
     ++visited;
    visitedMatrix[1][0] = 1;

    toVisit[visited].i = 0;
    toVisit[visited].j = 1;
     ++visited;
    visitedMatrix[0][1] = 1;

    for (i = 0; i < N; ++i)
    {
        printf("arr[%llu] = %llu\n", i, res);

        I = -1;
        res = -1;
        for (j = 0; j < visited; ++j)
        {
            pair = toVisit + j;
            val = power(2, pair->i) * power(3, pair->j);
            if (res > val)
            {
                res = val;
                I = j;
            }
        }

        pair = toVisit + I;
        pairCopy = toVisit[I];
        visitedMatrix[pairCopy.i][pairCopy.j] = 1;
        if (visitedMatrix[pairCopy.i + 1][pairCopy.j] == 0)
        {
            pair->i = pairCopy.i + 1;
            visitedMatrix[pair->i][pair->j] = 1;
            if (visitedMatrix[pairCopy.i][pairCopy.j + 1] == 0)
            {
                pair = toVisit + visited;
                pair->i = pairCopy.i;
                pair->j = pairCopy.j + 1;
                visitedMatrix[pair->i][pair->j] = 1;
                ++visited;
                assert(visited < VisitSz);
            }
        }
        else if (visitedMatrix[pair->i][pair->j + 1] == 0)
        {
            pair->j = pair->j + 1;
            visitedMatrix[pair->i][pair->j] = 1;
        }
        else
        {
            Pair *last = toVisit + visited - 1;
            pair->i = last->i;
            pair->j = last->j;
            --visited;
            assert(visited > 0);
        }
    }

    return res;
}

int main()
{
    a3smoothNumber(1000);
    return 0;
}
