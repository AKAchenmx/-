#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;
#define MAX 99999
#define maxsize 200
typedef int Distance[maxsize][maxsize];//最短距离矩阵
typedef int Path[maxsize][maxsize];//最短路程
typedef float Time[maxsize][maxsize];//最短时间矩阵
//建筑编号从1开始，在顶点数组中下标从0开始
typedef struct Node {
	string name;//建筑名称
	int num;//建筑编号
}Node;//顶点结构体
typedef struct Graph{
	Node vexs[maxsize];//顶点数组
	int Darcs[maxsize][maxsize];//路程的邻接矩阵
	float Tarcs[maxsize][maxsize];//时间的邻接矩阵
	int vexCount, arcCount;//当前顶点数和边数
}Graph;//图
void Mune()//菜单函数
{
	cout << "**********************************************" << endl;
	cout << "-------****欢迎使用校园交通咨询系统****-------" << endl;
	cout << "                 || 菜单栏 ||                 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "*     | 1,建筑信息及相应的行进时间和路程 |   *" << endl;
	cout << "*     |        2,添加建筑信息            |   *" << endl;
	cout << "*     |        3,删除建筑信息            |   *" << endl;
	cout << "*     |        4,修改建筑信息            |   *" << endl;
	cout << "*     |    5，查询最短路径和最短时间     |   *" << endl;
	cout << "*     |          0,退出系统              |   *" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "**********************************************" << endl;
}
void Init(Graph& G)//初始化地图
{
	G.vexs[0].name = "图书馆"; G.vexs[1].name = "正门";
	G.vexs[2].name = "航空宇航馆"; G.vexs[3].name = "逸夫馆";
	G.vexs[4].name = "工程训练中心"; G.vexs[5].name = "产教融合大楼";
	G.vexs[6].name = "设计艺术馆"; G.vexs[7].name = "体育馆";
	G.vexs[8].name = "北区体育场"; G.vexs[9].name = "大学生活动中心";
	G.vexs[10].name = "蓝天剧场"; G.vexs[11].name = "教学楼C座";
	G.vexs[12].name = "教学楼B座"; G.vexs[13].name = "教学楼A座";
	G.vexs[14].name = "北区食堂"; G.vexs[15].name = "北区宿舍";
	G.vexs[16].name = "北区排球场"; G.vexs[17].name = "南区足球场";
	G.vexs[18].name = "南区食堂"; G.vexs[19].name = "南门";
	G.vexs[20].name = "南区宿舍";
	G.vexCount = 21; G.arcCount = 29;
	for (int i = 0; i < G.vexCount; i++)
	{
		G.vexs[i].num = i + 1;
	}
	for (int i = 0; i < G.arcCount; i++)
	{
		for (int j = 0; j < G.arcCount; j++)
		{
			if (i == j)
			{
				G.Darcs[i][j] = G.Darcs[j][i] = 0;
				G.Tarcs[i][j] = G.Tarcs[j][i] = 0;
			}
			else
			{
				G.Darcs[i][j] = G.Darcs[j][i] = MAX;
				G.Tarcs[i][j] = G.Tarcs[j][i] = MAX;
			}
		}
	}
	G.Darcs[0][1] = G.Darcs[1][0] = 600; G.Tarcs[0][1] = G.Tarcs[1][0] = 6;
	G.Darcs[0][2] = G.Darcs[2][0] = 180; G.Tarcs[0][2] = G.Tarcs[2][0] = 1.8;
	G.Darcs[0][3] = G.Darcs[3][0] = 390; G.Tarcs[0][2] = G.Tarcs[2][0] = 3.9;
	G.Darcs[0][4] = G.Darcs[4][0] = 250; G.Tarcs[0][4] = G.Tarcs[4][0] = 2.5;
	G.Darcs[0][5] = G.Darcs[5][0] = 300; G.Tarcs[0][5] = G.Tarcs[5][0] = 3;
	G.Darcs[0][6] = G.Darcs[6][0] = 150; G.Tarcs[0][6] = G.Tarcs[6][0] = 1.5;
	G.Darcs[0][7] = G.Darcs[7][0] = 200; G.Tarcs[0][7] = G.Tarcs[7][0] = 2;
	G.Darcs[0][11] = G.Darcs[11][0] = 190; G.Tarcs[0][11] = G.Tarcs[11][0] = 1.9;
	G.Darcs[1][2] = G.Darcs[2][1] = 430; G.Tarcs[1][2] = G.Tarcs[2][1] = 4.3;
	G.Darcs[1][13] = G.Darcs[13][1] = 400; G.Tarcs[1][13] = G.Tarcs[13][1] = 4;
	G.Darcs[2][3] = G.Darcs[3][2] = 290; G.Tarcs[2][3] = G.Tarcs[3][2] = 2.9;
	G.Darcs[3][4] = G.Darcs[4][3] = 160; G.Tarcs[3][4] = G.Tarcs[4][3] = 1.6;
	G.Darcs[4][5] = G.Darcs[5][4] = 80; G.Tarcs[4][5] = G.Tarcs[5][4] = 0.8;
	G.Darcs[5][6] = G.Darcs[6][5] = 280; G.Tarcs[5][6] = G.Tarcs[6][5] = 2.8;
	G.Darcs[6][7] = G.Darcs[7][6] = 70; G.Tarcs[6][7] = G.Tarcs[7][6] = 0.7;
	G.Darcs[7][8] = G.Darcs[8][7] = 150; G.Tarcs[7][8] = G.Tarcs[8][7] = 1.5;
	G.Darcs[8][9] = G.Darcs[9][8] = 150; G.Tarcs[8][9] = G.Tarcs[9][8] = 1.5;
	G.Darcs[9][10] = G.Darcs[10][9] = 70; G.Tarcs[9][10] = G.Tarcs[10][9] = 0.7;
	G.Darcs[10][11] = G.Darcs[11][10] = 300; G.Tarcs[10][11] = G.Tarcs[11][10] = 3;
	G.Darcs[11][12] = G.Darcs[12][11] = 70; G.Tarcs[11][12] = G.Tarcs[12][11] = 0.7;
	G.Darcs[12][13] = G.Darcs[13][12] = 60; G.Tarcs[12][13] = G.Tarcs[13][12] = 0.6;
	G.Darcs[8][14] = G.Darcs[14][8] = 90; G.Tarcs[8][14] = G.Tarcs[14][8] = 0.9;
	G.Darcs[14][15] = G.Darcs[15][14] = 40; G.Tarcs[14][15] = G.Tarcs[15][14] = 0.4;
	G.Darcs[15][16] = G.Darcs[16][15] = 170; G.Tarcs[15][16] = G.Tarcs[16][15] = 1.7;
	G.Darcs[10][18] = G.Darcs[18][10] = 210; G.Tarcs[10][18] = G.Tarcs[18][10] = 2.1;
	G.Darcs[11][17] = G.Darcs[17][11] = 270; G.Tarcs[11][17] = G.Tarcs[17][11] = 2.7;
	G.Darcs[17][18] = G.Darcs[18][17] = 120; G.Tarcs[17][18] = G.Tarcs[18][17] = 1.2;
	G.Darcs[18][19] = G.Darcs[19][18] = 180; G.Tarcs[18][19] = G.Tarcs[19][18] = 1.8;
	G.Darcs[18][20] = G.Darcs[20][18] = 100; G.Tarcs[18][20] = G.Tarcs[20][18] = 1;
}
void Map(Graph& G)//输出地图函数
{
	cout << "*建筑信息及其编号:" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		cout << G.vexs[i].num << "—" << G.vexs[i].name << endl;
	}
	cout << "*它的相关路程的邻接矩阵为：（单位：m）" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			cout << G.Darcs[i][j] << "|";
		}
		cout << endl;
		cout << endl;
	}
	cout << "*它的相关时间的邻接矩阵为：（单位：min）" << endl;
	cout << "*注：时间以人步行的速度为100m/min计算" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			cout << G.Tarcs[i][j] << "|";
		}
		cout << endl;
		cout << endl;
	}
}
void FileMap(Graph& G)
{
	ofstream fout("C:\\Users\\张淑妤\\Desktop\\校园交通咨询系统.txt");
	fout << "*建筑信息及其编号" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		fout << i + 1 << "—" << G.vexs[i].name << endl;
	}
	fout << "*它的相关路程的邻接矩阵为：（单位：m）" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			fout << G.Darcs[i][j] << "|";
		}
		fout << endl;
		fout << endl;
	}
	fout << "*它的相关时间的邻接矩阵为：（单位：min）" << endl;
	fout << "*注：时间以人步行的速度为100m/min计算" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			fout << G.Tarcs[i][j] << "|";
		}
		fout << endl;
		fout << endl;
	}
	fout.close();
}
void ShortDistance(Graph& G, Distance& D, Path& P,Time& T)//弗洛伊德算法求两点间最短路径和时间
{
	int t;//起点建筑编号
	int r;//终点建筑编号
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			D[i][j] = G.Darcs[i][j];
			T[i][j] = G.Tarcs[i][j];
			P[i][j] = j;
		}
	}
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			for (int k = 0; k < G.vexCount; k++)
			{
				if (D[j][k] > D[j][i] + D[i][k])
				{
					D[j][k] = D[j][i] + D[i][k];
					P[j][k] = P[j][i];
				}
				if (T[j][k] > T[j][i] + T[i][k])
				{
					T[j][k] = T[j][i] + T[i][k];
				}
			}
		}
	}
	cout << "*请输入要查询路径的起点建筑标号:" << endl;
	cin >> t;
	cout << "*请输入要查询路径的终点建筑标号:" << endl;
	cin >> r;
	cout << "*"<<G.vexs[t - 1].name << "到" << G.vexs[r - 1].name << "的最短路径长为：" << D[t - 1][r - 1] << " m" << endl;
	cout << "*"<<G.vexs[t - 1].name << "到" << G.vexs[r - 1].name << "的最短时间为：" << T[t - 1][r - 1] << " min" << endl;
	int k = P[t - 1][r - 1];
	cout << "*最短路径为：";
	cout << G.vexs[t - 1].name;
	while (k != (r-1))
	{
		cout << "——>" << G.vexs[k].name;
		k = P[k][r - 1];
	}
	cout << "——>" << G.vexs[r - 1].name << endl;
}
void Add(Graph& G)//增加新建筑和新路线
{
	int a;//新增路线数
	int x;//建筑标号
	int y;//两建筑间的距离
	string str;
	int v = G.vexCount;//现在已有的顶点数
	cout << "*请输入要增加的建筑名为：" << endl;
	cin >> str;
	G.vexs[G.vexCount].name = str;
	G.vexs[G.vexCount].num = G.vexCount + 1;
	cout << "*请输入新增的路线数：" << endl;
	cin >> a;
	G.arcCount += a;
	G.Darcs[v - 1][v - 1] = 0;
	for (int i = 0; i < G.vexCount - 1; i++)
	{
		G.Darcs[i][v - 1] = MAX;
		G.Darcs[v - 1][i] = MAX;
		G.Tarcs[i][v - 1] = MAX;
		G.Tarcs[v - 1][i] = MAX;
	}
	for (int j = 1; j <= a; j++)
	{
		cout << "*请输入第" << j << "个与新建筑有路线的建筑标号："<<endl;
		cin >> x;
		if ((x <= 0) || (x > G.vexCount))
		{
			cout << "建筑标号输入错误！" << endl;
			return;
			break;
		}
		cout << "*请输入新建筑与该建筑之间的距离：" << endl;
		cin >> y;
		G.Darcs[x - 1][v - 1] = y;
		G.Darcs[v - 1][x - 1] = y;
		G.Tarcs[x - 1][v - 1] = y / 100.0;
		G.Tarcs[v - 1][x - 1] = y / 100.0;
	}
	G.vexCount++;
	cout << "新建筑与新路线增加成功！" << endl;
}
void Delet(Graph& G)//删除原有建筑和路线
{
	int b;//要删除的建筑标号
	cout << "*请输入要删除的建筑标号" << endl;
	cin >> b;
	if ((b <= 0) || (b > G.vexCount))
	{
		cout << "建筑标号输入错误！" << endl;
		return;
	}
	string s = G.vexs[b - 1].name;
	for (int i = b - 1; i < G.vexCount; i++)
	{
		G.vexs[i] = G.vexs[i + 1];
	}
	for (int i = b - 1; i < G.vexCount; i++)
	{
		for (int j = b - 1; j < G.vexCount; j++)
		{
			G.Darcs[i][j] = G.Darcs[i + 1][j + 1];
			G.Tarcs[i][j] = G.Tarcs[i + 1][j + 1];
		}
	}
	G.vexCount--;
	for (int j = 0; j < G.vexCount; j++)
	{
		G.vexs[j].num = j + 1;
	}
	cout << "建筑" << s << "已删除" << endl;
}
void Modify(Graph& G)//对现有地图进行修改
{
	int d;//用户选择的修改选项
	int m;//要修改建筑名称的编号
	int x, y;//与要修改路线相连的建筑编号
	int r;//新的路线长度
	string str;//修改后新的建筑名称
	cout << "*请选择要修改的选项*" << endl;
	while (1)
	{
		cout << "********************" << endl;
		cout << "  1，修改建筑名称   " << endl;
		cout << "  2，修改路线长度   " << endl;
		cout << "********************" << endl;
		cin >> d;
		switch (d)
		{
		case 1: 
		{
			cout << "请输入要修改的建筑编号:" << endl;
			cin >> m;
			if ((m <= 0) || (m > G.vexCount))
			{
				cout << "建筑编号输入错误！" << endl;
				break;
			}
			cout << "请输入新的建筑名称：" << endl;
			cin >> str;
			G.vexs[m - 1].name = str;
			cout << "建筑名称修改成功" << endl;
			break;
		}
		case 2:
		{
			cout << "请输入与要修改的路线相连的两个建筑编号:" << endl;
			cin >> x >> y;
			if ((x < 1) || (y < 1) || (x > G.vexCount) || (y > G.vexCount))
			{
				cout << "建筑编号输入错误！" << endl;
				break;
			}
				cout << "请输入新的路线长度：" << endl;
				cin >> r;
				G.Darcs[x - 1][y - 1] = r;
				G.Darcs[y - 1][x - 1] = r;
				G.Tarcs[x - 1][y - 1] = r / 100.0;
				G.Tarcs[y - 1][x - 1] = r / 100.0;
				cout << "新的路线长度修改成功" << endl;
				break;
		}
		}
		break;
	}
}
int main()
{
	Graph G;
	Init(G);
	Distance D;
	Time T;
	Path P;
	int x;//用户选择的操作
	while (1)
	{
		Mune();
		cout << "请输入要选择的操作：" << endl;
		cin >> x;
		switch (x)
		{
		case 1://显示地图信息
		{
			Map(G);
			FileMap(G);
			break;
		}
		case 2://增加新建筑
		{
			Add(G);
			break;
		}
		case 3://删除建筑
		{
			Delet(G);
			break;
		}
		case 4://修改建筑
		{
			Modify(G);
			break;
		}
		case 5://求最短路径
		{
			ShortDistance(G, D, P, T);
			break;
		}
		case 0://退出
		{
			cout << "-----**** 欢迎下次使用! ****-----" << endl;
			return 0;
			break;
		}
		}
	}
}