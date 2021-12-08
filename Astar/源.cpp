#include<iostream>
#include"Astar.h"
#include"map.h"
#include<queue>
#include<list>
#include<fstream>
#include"BinaryHeap.h"
#include<ctime>
using namespace std;
/*
* 本程序基于二进制高程数据进行规划
* 输入为struct OP类型，其中包含起点终点，地图行数和列数
*/
int main()
{
	OP p{ 0,199,199,199,200,200,"C:/2020/map.txt","C:/Users/Lenovo/Desktop/shangu1.txt", {1,3} }; //存放起点终点，和构造好的地图
	

	list<Point*> close; //close表也一样
	stage.resize(p.row, vector<flag>(p.col, p));//状态表

	Point *s = new Point{ p.S_start_x, p.S_start_y, 0, p, nullptr };
	stage[s->x][s->y].add_in_visited(s, p); //在stage里面改变起点的状态

	vector<BinaryHeap> open(p.open_len.size());
	vector<vector<pair<int, int>>> sport(p.open_len.size());
	for (int i = 0; i < p.open_len.size(); i++)
	{
		vector<pair<int, int>> sp{ {p.open_len[i],0}, {-p.open_len[i], 0}, {0,p.open_len[i]}, {0, -p.open_len[i]} };//初始化四个方向
		sport[i] = sp;
	}
	add_open(open, s, p);

	vector<pair<int,int>> path; // 存放输出结果
	clock_t s_time = clock();
	while (open[0].size() > 0)
	{
		for (int i = open.size()-1; i >= 0; i--)
		{
			if (open[i].size() > 0 && open[i].findMin()->f <= 3 * open[0].findMin()->f)
			{
				Point* current = open[i].findMin();
				if (current->x == p.S_goal_x && current->y == p.S_goal_y)
				{
					while (current)
					{
						path.push_back({ current->x, current->y });
						current = current->pre;
					}
					clock_t e = clock();
					cout << (e - s_time) / (double)CLOCKS_PER_SEC << endl;
					return 0;
				}
				close.push_back(current);
				stage[current->x][current->y].add_in_close();
				open[i].deleteMin();
				for (int k = 0; k < sport[i].size(); k++)
				{
					int x = current->x + sport[i][k].first;
					int y = current->y + sport[i][k].second;
					if (x >= 0 && x < p.row && y > 0 && y < p.col)
					{
						if (stage[x][y].get_in_close())
						{
							continue;
						}
						if (stage[x][y].get_in_open_0())
						{
							int c = cost(current->x, current->y, x, y, p);
							if (current->g + c < stage[x][y].ptr->f)
							{
								stage[x][y].ptr->pre = current;
								stage[x][y].ptr->f = current->g + c;
								open_0.percolateUp(stage[x][y].open_0_pos);
							}
						}
						if (stage[x][y].get_in_open_1())
						{
							int c = cost(current->x, current->y, x, y, p);
							if (current->g + c < stage[x][y].ptr->f)
							{
								stage[x][y].ptr->pre = current;
								stage[x][y].ptr->f = current->g + c;
								open_1.percolateUp(stage[x][y].open_1_pos);
							}
						}
						if (!stage[x][y].visited)
						{
							double g = current->g + cost(current->x, current->y, x, y, p);
							Point* nextPoint = new Point{ x,y,g,p,current };
							open_0.push_back(nextPoint);
							open_1.push_back(nextPoint);
							stage[x][y].add_in_visited(nextPoint);
							stage[x][y].add_in_open_1(nextPoint);
						}
					}
				}
				break;
			}
		}
		if (open_1.size()>0 && open_1.findMin()->f<3*open_0.findMin()->f)
		{
			Point* current = open_1.findMin();
			if (current->x == p.S_goal_x && current->y == p.S_goal_y)
			{
				while (current)
				{
					path.push_back({ current->x, current->y });
					current = current->pre;
				}
				clock_t e = clock();
				cout << (e - s_time) / (double)CLOCKS_PER_SEC << endl;
				return 0;
			}
			close.push_back(current);
			stage[current->x][current->y].add_in_close();
			open_1.deleteMin();
			for (int i = 0; i < sport_1.size(); i++)
			{
				int x = current->x + sport_1[i][0];
				int y = current->y + sport_1[i][1];
				if (x >= 0 && x < p.row && y > 0 && y < p.col)
				{
					if (stage[x][y].get_in_close())
					{
						continue;
					}
					if (stage[x][y].get_in_open_0())
					{
						int c = cost(current->x, current->y, x, y, p);
						if (current->g + c < stage[x][y].ptr->f)
						{
							stage[x][y].ptr->pre = current;
							stage[x][y].ptr->f = current->g + c;
							open_0.percolateUp(stage[x][y].open_0_pos);
						}
					}
					if (stage[x][y].get_in_open_1())
					{
						int c = cost(current->x, current->y, x, y, p);
						if (current->g + c < stage[x][y].ptr->f)
						{
							stage[x][y].ptr->pre = current;
							stage[x][y].ptr->f = current->g + c;
							open_1.percolateUp(stage[x][y].open_1_pos);
						}
					}
					if (!stage[x][y].visited)
					{
						double g = current->g + cost(current->x, current->y, x, y, p);
						Point* nextPoint = new Point{ x,y,g,p,current };
						open_0.push_back(nextPoint);
						open_1.push_back(nextPoint);
						stage[x][y].add_in_visited(nextPoint);
						stage[x][y].add_in_open_1(nextPoint);
					}
				}
			}
		}
		else
		{
			Point* current = open_0.findMin();
			if (current->x == p.S_goal_x && current->y == p.S_goal_y)
			{
				while (current)
				{
					path.push_back({ current->x, current->y });
					current = current->pre;
				}
				clock_t e = clock();
				cout << (e - s_time) / (double)CLOCKS_PER_SEC << endl;
				return 0;
			}
			close.push_back(current);
			stage[current->x][current->y].add_in_close();
			//open.erase(min_it);
			open_0.deleteMin();
			for (int i = 0; i < sport_0.size(); i++)
			{
				int x = current->x + sport_0[i][0];
				int y = current->y + sport_0[i][1];
				if (x >= 0 && x < p.row && y > 0 && y < p.col)
				{
					if (stage[x][y].get_in_close())
					{
						continue;
					}
					if (stage[x][y].get_in_open_0())
					{
						int c = cost(current->x, current->y, x, y, p);
						if (current->g + c < stage[x][y].ptr->f)
						{
							stage[x][y].ptr->pre = current;
							stage[x][y].ptr->f = current->g + c;
							open_0.percolateUp(stage[x][y].open_0_pos);
						}
					}
					if (!stage[x][y].visited)
					{
						double g = current->g + cost(current->x, current->y, x, y, p);
						Point* nextPoint = new Point{ x,y,g,p,current };
						open_0.push_back(nextPoint);
						stage[x][y].add_in_visited(nextPoint);
					}
				}
			}
		}
	}
	return 0;
}