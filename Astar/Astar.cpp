#include"Astar.h"

double cost(const Point& p1, const Point& p2, OP& p)
{
	return cost(p1.x, p1.y, p2.x, p2.y, p);
}

double cost(int s_x, int s_y, int g_x, int g_y, OP& p)
{
	double c1 = pow(((double)s_x - g_x), 2);
	double c2 = pow(((double)s_y - g_y), 2);
	double c3 = pow(p.map.GetPoint(s_x, s_y) - p.map.GetPoint(g_x, g_y), 2);
	double dist = sqrt(c1 + c2 + c3);
	return dist;
}

