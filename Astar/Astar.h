#pragma once
#include<iostream>
#include<cmath>
#include"map.h"
#include<vector>

using namespace std;
struct OP
{
	OP(int s_x, int s_y, int e_x, int e_y, int r, int c, string map, string valley, int l) :S_start_x{ s_x }, S_start_y{ s_y }, 
		S_goal_x{ e_x }, S_goal_y{ e_y }, row{ r }, col{ c }, open_1_len{ l }
	{
		this->map.resize(row, col);
		this->map.read_ascii(map);
		this->valley.resize(row, col);
		this->valley.read_ascii(valley);
	}
	int S_start_x; //起点x
	int S_start_y; //起点y
	int S_goal_x; //终点x
	int S_goal_y; //终点y
	int row; //地图行数
	int col; //地图列数
	int open_1_len;
	Map map; //地图
	Map valley; //山谷
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
	bool operator<(const Point& p) const
	{
		return this->f < p.f;
	}
	bool operator>(const Point& p) const
	{
		return this->f > p.f;
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
	bool open_0;
	int open_0_pos;
	bool close;
	Point* ptr;
	bool open_1;
	int open_1_pos;
	flag() :visited{ false }, open_0{ false }, close{ false }, open_0_pos{ 0 }, ptr{ nullptr }, open_1{ false }, open_1_pos{0}
	{

	}
	void add_in_visited(Point* p)
	{
		visited = true;
		open_0 = true;
		ptr = p;
	}
	void add_in_close()
	{
		open_0 = false;
		open_1 = false;
		close = true;
	}
	bool get_in_visit()
	{
		return visited;
	}
	bool get_in_open_0()
	{
		return open_0;
	}
	bool get_in_close()
	{
		return close;
	}
	void add_in_open_1(Point* p)
	{
		open_1 = true;
	}
	bool get_in_open_1()
	{
		return open_1;
	}
};




