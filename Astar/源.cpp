#include<iostream>
#include"Astar.h"
#include"map.h"
#include<queue>
#include<list>
using namespace std;
/*
* 本程序基于二进制高程数据进行规划
* 输入为struct OP类型，其中包含起点终点，地图行数和列数
*/
int main()
{
	OP p{ 0,0,200,200,5679,4464 }; //存放起点终点，和构造好的地图
	//priority_queue<Point, vector<Point>, cmp> open;
	list<Point*> open; //open表，存放指针，就省去了很多空间
	list<Point*> close; //close表也一样
	vector<vector<flag>> stage(p.row, vector<flag>(p.col)); //这个二维矩阵和地图一样大，每个位置都放了对应点的状态
	Point *s = new Point{ p.S_start_x, p.S_start_y, 0, p, nullptr };
	vector<vector<int>> sport{ { 1,0 }, { -1,0 }, { 0,1 }, { 0,-1 },{1,1},{1,-1},{-1,1},{-1,-1} }; //8自由度
	open.push_back(s); //将起点加入到open表
	stage[s->x][s->y].add_in_visited(s); //在stage里面改变起点的状态
	vector<pair<int,int>> path; // 存放输出结果
	while (open.size() > 0)
	{
		list<Point*>::iterator min_it = open.begin();
		for (auto it = open.begin(); it != open.end(); it++)
		{
			if ((**it).f<(**min_it).f)
			{
				min_it = it;
			}
		}
		Point* current = *min_it;
		if (current->x == p.S_goal_x && current->y == p.S_goal_y)
		{
			while (current)
			{
				path.push_back({ current->x, current->y });
				current = current->pre;
			}
			return 0;
		}
		close.push_back(current);
		stage[current->x][current->y].add_in_close();
		open.erase(min_it);
		for (int i = 0; i < sport.size(); i++)
		{
			int x = current->x + sport[i][0];
			int y = current->y + sport[i][1];
			if (x >= 0 && x <= p.row && y >= 0 && y <= p.col)
			{	
				if (stage[x][y].get_in_close())
				{
					continue;
				}
				if (stage[x][y].get_in_open())
				{
					int c = cost(current->x, current->y, x, y, p);
					if (current->g + c < stage[x][y].ptr->f)
					{
						stage[x][y].ptr->pre = current;
						stage[x][y].ptr->f = current->g + c;
					}
				}
				if (!stage[x][y].visited)
				{
					double g = current->g + cost(current->x, current->y, x, y, p);
					Point* nextPoint = new Point{ x,y,g,p,current };
					open.push_back(nextPoint);
					stage[x][y].add_in_visited(nextPoint);
				}	
			}	
		}
	}
	return 0;
}