#pragma once
#include<iostream>
#include<vector>
#include"Astar.h"
using namespace std;

extern vector<vector<flag>> stage;


class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100)
	{
		arr.resize(capacity);
		currentSize = 0;
	}

	bool isEmpty() const
	{
		return !currentSize;
	}
	Point* findMin() const
	{
		return arr[1];
	}
	int size()
	{
		return this->currentSize;
	}

	void push_back(Point* x);
	void deleteMin();
	void percolateUp(int hole);
	//private:
	int currentSize;
	vector<Point*> arr;
	void percolateDown(int hole);
};

