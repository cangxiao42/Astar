#pragma once
#include<iostream>
#include<cmath>
#include"map.h"

using namespace std;

struct OP
{
	OP(int s_x, int s_y, int e_x, int e_y, int r, int c) :S_start_x{ s_x }, S_start_y{ s_y }, 
		S_goal_x{ e_x }, S_goal_y{ e_y }, row{ r }, col{ c }
	{
		map.resize(row, col);
		map.read();
	}
	int S_start_x; //起点x
	int S_start_y; //起点y
	int S_goal_x; //终点x
	int S_goal_y; //终点y
	int row; //地图行数
	int col; //地图列数
	Map map; //地图
};

struct Point;
double cost(const Point& p1, const Point& p2, OP& p);
double cost(int s_x, int s_y, int g_x, int g_y, OP& p);
struct Point
{
	Point() :x{ 0 }, y{ 0 }, g{ 0 }, h{ 0 }, f{ 0 }, pre{nullptr}
	{

	}
	Point(int x, int y, double g, double h, Point* pre) :x{ x }, y{ y }, g{ g }, h{ h }, pre{pre}
	{
		f = g + h;
	}
	Point(int x, int y, double g, OP& p, Point* pre) :x{ x }, y{ y }, g{ g }, pre{pre}
	{
		this->h = cost(x, y, p.S_goal_x, p.S_goal_y, p);
		f = this->g + this->h;
	}
	int x;
	int y;
	double g;
	double h;
	double f;
	Point* pre;
};


struct cmp
{
	bool operator ()(const Point& a, const Point& b)
	{
		return a.g > b.g; //（小顶）（反之大顶）
	}
};

struct flag
{
	bool visited;
	bool open;
	bool close;
	Point* ptr;
	flag() :visited{ false }, open{ false }, close{false}
	{

	}
	void add_in_visited(Point* p)
	{
		visited = true;
		open = true;
		ptr = p;
	}
	void add_in_close()
	{
		open = false;
		close = true;
	}
	bool get_in_visit()
	{
		return visited;
	}
	bool get_in_open()
	{
		return open;
	}
	bool get_in_close()
	{
		return close;
	}
};



