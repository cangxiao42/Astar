#pragma once
#include<iostream>
#include<fstream>
using namespace std;


class Map
{
public:
	Map()
	{
		m_pMat = NULL;
		m_counter = 0;
		m_x = 0;
		m_y = 0;
		m_pMat = nullptr;
	}
	Map(int height, int width)
	{
		m_pMat = NULL;
		m_counter = 0;
		m_x = height;
		m_y = width;
		m_pMat = new double[width * height];
	}

	void resize(int height, int width)
	{
		m_pMat = NULL;
		m_counter = 0;
		m_x = height;
		m_y = width;
		m_pMat = new double[width * height];
	}

	void read()//读二进制
	{
		FILE* file = NULL;
		fopen_s(&file, "C:\\2020\\hight.bin", "rb");
		if (file == NULL)
		{
			printf("读取地图失败\n");
		}
		fseek(file, 0L, SEEK_END);
		int length = ftell(file);
		fseek(file, 0L, SEEK_SET);
		double* tmp = new double[m_x * m_y];
		fread(tmp, sizeof(double), m_x * m_y, file);
		//mat.AddValue(tmp);
		for (int i = 0; i <m_x * m_y; i++)
		{
			this->AddValue(tmp[i]);
		}
		fclose(file);
		delete[] tmp;
	}
	void read_ascii(string str)//读ascii文件
	{
		//int* data = new int[200 * 200];//定义一个1500*2的矩阵，用于存放数据
		ifstream infile;//定义读取文件流，相对于程序来说是in
		infile.open(str);//打开文件
		for (int i = 0; i < m_x * m_y; i++)//定义行循环
		{
			infile >> m_pMat[i];//读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列不断循环进行
		}
	}
public:
	~Map(void)
	{
		if (m_pMat != NULL)
		{
			delete[] m_pMat;
		}

		//m_Mat.clear();
		//vector<double>(m_Mat).swap(m_Mat);
	}

public:
	void AddValue(double point)
	{
		if (m_pMat != NULL)
		{
			m_pMat[m_counter] = point;
			m_counter++;
		}
	}

	double GetPoint(int x, int y)
	{
		int index = y + x * GetMatMaxY();
		return m_pMat[index];
	}

	double SetPoint(int x, int y, double value)
	{
		int index = y + x * GetMatMaxY();
		m_pMat[index] = value;
	}

	int GetMatMaxX()
	{
		return m_x;
	}

	int GetMatMaxY()
	{
		return m_y;
	}

	void SetMatMaxX(int value)
	{
		m_x = value;
	}

	void SetMatMaxY(int value)
	{
		m_y = value;
	}

	int GetMatSize()
	{
		return m_counter;
	}

private:

	double* m_pMat;
	int m_x;
	int m_y;
	unsigned long m_counter;
};