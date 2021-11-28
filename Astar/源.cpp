#include<iostream>
#include"Astar.h"
#include"map.h"
#include<queue>
#include<list>
using namespace std;
/*
* ��������ڶ����Ƹ߳����ݽ��й滮
* ����Ϊstruct OP���ͣ����а�������յ㣬��ͼ����������
*/
int main()
{
	OP p{ 0,0,200,200,5679,4464 }; //�������յ㣬�͹���õĵ�ͼ
	//priority_queue<Point, vector<Point>, cmp> open;
	list<Point*> open; //open�����ָ�룬��ʡȥ�˺ܶ�ռ�
	list<Point*> close; //close��Ҳһ��
	vector<vector<flag>> stage(p.row, vector<flag>(p.col)); //�����ά����͵�ͼһ����ÿ��λ�ö����˶�Ӧ���״̬
	Point *s = new Point{ p.S_start_x, p.S_start_y, 0, p, nullptr };
	vector<vector<int>> sport{ { 1,0 }, { -1,0 }, { 0,1 }, { 0,-1 },{1,1},{1,-1},{-1,1},{-1,-1} }; //8���ɶ�
	open.push_back(s); //�������뵽open��
	stage[s->x][s->y].add_in_visited(s); //��stage����ı�����״̬
	vector<pair<int,int>> path; // ���������
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