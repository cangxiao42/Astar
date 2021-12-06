#include"BinaryHeap.h"
vector<vector<flag>> stage(0, vector<flag>(0));

void BinaryHeap::push_back(Point* x)
{
    if (currentSize == arr.size() - 1)
        arr.resize(arr.size() * 2);
    int hole = ++currentSize;
    Point* copy = x;
    arr[0] = move(copy);
    for (; x->f < arr[hole / 2]->f; hole /= 2)
    {
        stage[arr[hole/2]->x][arr[hole/2]->y].open_pos = hole;
        arr[hole] = move(arr[hole / 2]);
    }
    arr[hole] = move(arr[0]);
    stage[arr[0]->x][arr[0]->y].open_pos = hole;
}


void BinaryHeap::deleteMin()
{
    arr[1] = move(arr[currentSize--]);
    percolateDown(1);
}

void BinaryHeap::percolateDown(int hole)
{
    int child;
    Point* tmp = move(arr[hole]);
    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && arr[child + 1] < arr[child])
            ++child;
        if (arr[child]->f < tmp->f)
        {
            stage[arr[child]->x][arr[child]->y].open_pos = hole;
            arr[hole] = move(arr[child]);
        }      
        else
            break;
    }
    arr[hole] = move(tmp);
    stage[tmp->x][tmp->y].open_pos = hole;
}


void BinaryHeap::percolateUp(int hole)
{
    int parent;
    Point* tmp = move(arr[hole]);
    for (; hole / 2 >= 1; hole = parent)
    {
        parent = hole / 2;
        if (tmp->f < arr[parent]->f)
        {
            stage[arr[parent]->x][arr[parent]->y].open_pos = hole;
            arr[hole] = move(arr[parent]);
        }  
        else
            break;
    }
    arr[hole] = move(tmp);
    stage[tmp->x][tmp->y].open_pos = hole;
}