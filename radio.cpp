// radio.cpp : 定义 DLL 的初始化例程。
//
#include "stdafx.h"
#include "radio.h"
#include "opnet.h"
#include "ets_api.h"
#include "prg_geo.h"
#include "math.h"
#include "stdlib.h"
#include "DetailDialog.h"
#include "Dialog3Detail.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Choice.h"
#include "Irregular.h"
#include "IrregularPoint.h"
#include "PointNum.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include <queue>
#include <ema.h>
#include <opnet_emadefs.h>
#include <opnet_constants.h>
#define N 36 //opnet 仿真返回36个点
#define Max 50 //声明数组时，采用的最大个数
const char* FileNameTest = "C:/Users/Administrator/Desktop/test.txt";
const char* FileNameTask = "C:/Users/Administrator/Desktop/task.txt";
const char* FileNameDat = "C:/Users/Administrator/Desktop/opnet.bat";
int array[100][100] = {0};
double Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio;//监测站属性，天线高度，功率，带宽，频率，比特率
//DPoint DPTemp[N+1];//DPoint* GuiHua(DPoint Point),存储点的坐标
DPoint *backto;//执行相关函数的指针
DPoint APTemp[200]={{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};//DPoint* GuiHua(DPoint Point)
//Point *dptransformtop(DPoint dpoint[], double minx, double maxx, double miny, double maxy)
//DPoint *designpoint(double radius, double minx, double maxx, double miny, double maxy)
//保留最后结果的数组,数组有效长度为count+1,最后一位的DPoint.x保留最佳适应度。DPoint.y为0.0。DPoint *dealstaticpoly(DPoint border[], int bordernum, int count)
//DPoint result[200] = { { 0.0, 0.0 } };
#define	 CRTSRC		"radio"
#define  ABSLUT		"absolute"
#define  RLT2SBNT   "relative to subnet-platform"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// CradioApp

BEGIN_MESSAGE_MAP(CradioApp, CWinApp)
END_MESSAGE_MAP()
// CradioApp 构造

CradioApp::CradioApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}
// 唯一的一个 CradioApp 对象

CradioApp theApp;
// CradioApp 初始化

BOOL CradioApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//基站参数初始化
void InitailStatParam(double m_height, double m_power, double m_bound, double m_freq, double m_ratio)
{
	Stat_height=m_height;
	Stat_power=m_power;
	Stat_bound=m_bound;
	Stat_freq=m_freq;
	Stat_ratio=m_ratio;
}

//仿真得到一个点的范围
void FindBoundary(double longitude=73.1611, double y=51.7756, double m_height = 5.0, double m_power = 0.05, double m_bound=10, double m_freq=1000, double m_ratio=250000)
{
   ofstream tofile;
   typedef struct Coordinate
  {
	char coordinate[50];
   } Coordinate;
   tofile.open(FileNameDat);
   tofile<<"op_runsim -net_name terrain_measure-world_baseline "
   <<" -\"top.AP_Node.Animation Enable\" TRUE "
   <<" -\"top.AP_Node.Antenna Height\" "<<m_height
   <<" -\"top.AP_Node.X Position\" "<<longitude
   <<" -\"top.AP_Node.Y Position\" "<<y
   <<" -\"top.AP_Node.wlan_port_rx0.channel [0].data rate\" "<<m_ratio
   <<" -\"top.AP_Node.wlan_port_rx0.channel [0].bandwidth\" "<<m_bound
   <<" -\"top.AP_Node.wlan_port_rx0.channel [0].min frequency\" "<<m_freq
   <<" -\"top.AP_Node.wlan_port_tx0.channel [0].data rate\" "<<m_ratio
   <<" -\"top.AP_Node.wlan_port_tx0.channel [0].bandwidth\" "<<m_bound
   <<" -\"top.AP_Node.wlan_port_tx0.channel [0].min frequency\" "<<m_freq
   <<" -\"top.AP_Node.wlan_port_tx0.channel [0].power\" "<<m_power;
   for(int i=0;i<=N;i++)
   {
      tofile<<" -\"top.Station_"<<i<<".Animation Enable\" TRUE "
		  <<" -\"top.Station_"<<i<<".Antenna Height\" "<<m_height
		  <<" -\"top.Station_"<<i<<".Init Distance\" 500 "
		  <<" -\"top.Station_"<<i<<".Measure Radius\" 0.0"
		  <<" -\"top.Station_"<<i<<".X Position\" "<<longitude
          <<" -\"top.Station_"<<i<<".Y Position\" "<<y
		  <<" -\"top.Station_"<<i<<".wlan_port_rx0.channel [0].data rate\" "<<m_ratio
          <<" -\"top.Station_"<<i<<".wlan_port_rx0.channel [0].bandwidth\" "<<m_bound
          <<" -\"top.Station_"<<i<<".wlan_port_rx0.channel [0].min frequency\" "<<m_freq
          <<" -\"top.Station_"<<i<<".wlan_port_tx0.channel [0].data rate\" "<<m_ratio
          <<" -\"top.Station_"<<i<<".wlan_port_tx0.channel [0].bandwidth\" "<<m_bound
          <<" -\"top.Station_"<<i<<".wlan_port_tx0.channel [0].min frequency\" "<<m_freq
          <<" -\"top.Station_"<<i<<".wlan_port_tx0.channel [0].power\" "<<m_power;
   }
   tofile<<" -duration 40.0\n"<<endl;
   //tofile<<"pause"<<endl;
   tofile.close();
   system(FileNameDat);
   //保留最后一圈的点
	ifstream fromfile;
	Coordinate coor[N + 1];
	fromfile.open(FileNameTest);
	char tempCoordinate[50];
	while (fromfile.getline(tempCoordinate, 50))
	{
		int Num;
		if (tempCoordinate[9] == 58) Num = int(tempCoordinate[8] - 48);
		else Num = int(tempCoordinate[8] - 48) * 10 + int(tempCoordinate[9] - 48);
		memcpy(coor[Num].coordinate, tempCoordinate, 50);
	}
	fromfile.close();
	for(int i=0;i<=N;i++)
	{
	if(coor[i].coordinate[0] != 'S') continue;
	int j=0,k=0;
	while(coor[i].coordinate[j] != ':') j++;
	while(j<50) {coor[i].coordinate[k++] = coor[i].coordinate[++j];}
	}
	tofile.open(FileNameTask);
	for (int i = 0; i <= N; i++)
	{
		tofile << coor[i].coordinate << endl;
	}
	//tofile<<"daa"<<endl;
	tofile.close();
}

////规划，返回N个点的坐标
//DPoint* GuiHua(DPoint Point)
//{
//	FindBoundary(Point.x,Point.y,Stat_height,Stat_power,Stat_bound,Stat_freq,Stat_ratio);
//	GetCoordinate(DPTemp);
//	return DPTemp;
//}

//规划，返回N个点的坐标(包括其他参数)
DPoint* GuiHua(DPoint Point)
{
	FindBoundary(Point.x, Point.y, Point.AntennaHeight, Point.Power, Point.BandWidth, Point.Frequentcy, Point.DataRate);
	GetCoordinate(APTemp);
	return APTemp;
}

//获取坐标,放在数组中
void GetCoordinate(DPoint Coordinate[])//0~8,11~19
{
	ifstream fromfile;
	char CoordinateChar[50]={};
	fromfile.open(FileNameTask);
	for(int i=0;i<=N;i++)
	{
		fromfile.getline(CoordinateChar,50);
		Coordinate[i].x = StringToDouble(CoordinateChar,11,19);
		Coordinate[i].y = StringToDouble(CoordinateChar,0,8);
	}
	fromfile.close();
}
//将字符串转化为double
double StringToDouble(char x[],int Begin,int End)
{
	double Num;
	Num = double(x[Begin]-48)*10.0+double(x[Begin+1]-48)+double(x[Begin+3]-48)/10.0+double(x[Begin+4]-48)/100.0+double(x[Begin+5]-48)/1000.0+double(x[Begin+6]-48)/10000.0+double(x[Begin+7]-48)/100000.0+double(x[Begin+8]-48)/1000000.0;
	return Num;
}

//计算数组1的百分比，计算得出适应度
double calc100()
{
	int count = 0;
	for (int i = 0; i<100; i++)
	{
		for (int j = 0; j<100; j++)
		{
			if (array[i][j] == 1)
				count++;
		}
	}
	return (double)count / (double)10000;
}
//清除array[][]
void cleararray()
{
	for (int i = 0; i<100; i++)
	{
		for (int j = 0; j<100; j++)
		{
			array[i][j] = 0;
		}
	}
}
//从中心点填充36个点，将节点入队列，将其四周为0的顶点压入队列。然后依次出队列，再压缩进队列。以此循环
void addsect(Point c)
{
	queue<Point> myqueue;
	myqueue.push(c);
	array[c.x][c.y] = 1;
	cout << "将节点压入队列" << endl;
	while (!myqueue.empty())
	{
		Point temp = myqueue.front();
		cout << "取得栈顶" << temp.x << endl;

		myqueue.pop();
		if (array[temp.x + 1][temp.y] != -1 && array[temp.x + 1][temp.y] == 0)
		{
			Point newp;
			newp.x = temp.x + 1;
			newp.y = temp.y;
			myqueue.push(newp);
			array[newp.x][newp.y] = 1;
		}
		if (array[temp.x - 1][temp.y] != -1 && array[temp.x - 1][temp.y] == 0)
		{
			Point newp;
			newp.x = temp.x - 1;
			newp.y = temp.y;
			myqueue.push(newp);
			array[newp.x][newp.y] = 1;
		}
		if (array[temp.x][temp.y + 1] != -1 && array[temp.x][temp.y + 1] == 0)
		{
			Point newp;
			newp.x = temp.x;
			newp.y = temp.y + 1;
			myqueue.push(newp);
			array[newp.x][newp.y] = 1;
		}
		if (array[temp.x][temp.y - 1] != -1 && array[temp.x][temp.y - 1] == 0)
		{
			Point newp;
			newp.x = temp.x;
			newp.y = temp.y - 1;
			myqueue.push(newp);
			array[newp.x][newp.y] = 1;
		}

	}
}
//计算圆最短半径（修改，改成数组的形式）
double getradius(DPoint point[], DPoint center)
{
	double min = sqrt((point[0].x - center.x)*(point[0].x - center.x) + (point[0].y - center.y)*(point[0].y - center.y));
	for (int i = 0; i<36; i++)
	{
		double dis = sqrt((point[i].x - center.x)*(point[i].x - center.x) + (point[i].y - center.y)*(point[i].y - center.y));
		if (dis<min)
			min = dis;
	}
	return min;
}
//生成DPoint类型的x随机坐标
double makerandomx(double minx, double singledis)
{
	double randomx = minx + rand() % 100 * singledis;
	return randomx;
}
//生成DPoint类型的y随机坐标
double makerandomy(double miny, double singledis)
{
	double randomy = miny + rand() % 100 * singledis;
	return randomy;
}
//计算数组中的最小值(修改，增加参数长度)
double getmin(double array[], int num)
{
	double min = array[0];
	for (int i = 1; i<num; i++)
	{
		if (min>array[i])
			min = array[i];
	}
	return min;
}
//四舍五入函数
int round(float x)
{
	return (int)(x + 0.5);
}
//形式转换（当节点越出边界为负值，将其设为0）
Point *dptransformtop(DPoint dpoint[], double minx, double maxx, double miny, double maxy)
{
	Point point[200] = {{ 0,0 }};
	//cout<<"进入形式转换"<<endl;
	double disx = maxx - minx;
	//cout<<"disx:"<<disx<<endl;
	double disy = maxy - miny;
	double singledisx = disx / 100;
	double singledisy = disy / 100;
	DPoint dparray[200] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
	for (int i = 0; i<200 && dpoint[i].x != 0.0; i++)
	{

		point[i].x = ((dpoint[i].x - minx) / singledisx) - 1;
		point[i].y = ((dpoint[i].y - miny) / singledisy) - 1;
		//cout<<point[i].x<<"!!!"<<point[i].y<<endl;
		if (point[i].x<0)
		{
			point[i].x = 0;
		}
		if (point[i].y<0)
		{
			point[i].y = 0;
		}
	}
	//cout<<"转化结束point[29]为 "<<point[29].x<<point[29].y<<endl;
	//cout<<"转化结束point[30]为 "<<point[30].x<<point[30].y<<endl;
	//cout<<"转化结束point[31]为 "<<point[31].x<<point[31].y<<endl;
	//cout<<"转化结束point[32]为 "<<point[32].x<<point[32].y<<endl;
	//cout<<"转化结束point[33]为 "<<point[33].x<<point[33].y<<endl;
	//cout<<"转化结束point[34]为 "<<point[34].x<<point[34].y<<endl;
	//cout<<"转化结束point[35]为 "<<point[35].x<<point[35].y<<endl;
	//cout<<"转化结束point[36]为 "<<point[36].x<<point[36].y<<endl;
	return point;
}
//将两个Point点连接，将连线的值设为1。
void linkpoint(Point p1, Point p2)
{
	//cout<<"进入链接"<<endl;
	//处理斜率不存在的情况
	if (p1.x == p2.x)
	{  // cout<<"进入斜率不存在情况"<<endl;
		if (p2.y>p1.y)
		{
			for (int i = 0; i <= p2.y - p1.y; i++)
			{
				array[p1.x][p1.y + i] = 1;
			}
		}
		if (p1.y >= p2.y)
		{
			for (int i = 0; i <= p1.y - p2.y; i++)
			{
				array[p1.x][p2.y + i] = 1;
			}
		}
		return;
	}
	if (p1.y == p2.y)
	{
		//cout<<"进入斜率为0";
		if (p2.x>p1.x)
		{
			for (int i = 0; i <= p2.x - p1.x; i++)
			{
				array[p1.x + i][p1.y] = 1;
			}
		}
		if (p1.x >= p2.x)
		{
			for (int i = 0; i <= p1.x - p2.x; i++)
			{
				array[p2.x + i][p2.y] = 1;
			}
		}

		return;
	}

	int temp1 = p2.x - p1.x;
	//cout<<"temp1:"<<temp1<<endl;
	int temp2 = p2.y - p1.y;
	//cout<<"temp2:"<<temp2<<endl;
	double temp3 = abs(((double)temp2 / (double)temp1));
	//cout<<"temp3:"<<temp3<<endl;
	double temp4 = double((double)temp2 / (double)temp1);
	//cout<<"temp4:"<<temp4<<endl;
	double temp5 = double((double)temp1 / (double)temp2);
	//cout<<"temp5:"<<temp5<<endl;

	//斜率大于1
	if (temp3 > 1 && temp4 > 0)
	{
		//cout<<"进入斜率大于1情况"<<endl;
		for (int i = 0; i <= abs(p2.y - p1.y); i++)
		{
			if (p1.y<p2.y)
			{
				array[round(p1.x + temp5 * i)][p1.y + i] = 1;
			}
			else if (p1.y>p2.y)
			{
				array[round(p2.x + temp5 * i)][p2.y + i] = 1;
			}

		}
	}
	//斜率大于0.小于1
	else if (temp3 > 0 && temp3 <= 1 && temp4 >= 0)
	{
		//cout<<"进入斜率大于0.小于1情况"<<endl;
		for (int i = 0; i <= abs(p2.x - p1.x); i++)
		{
			if (p1.y<p2.y)
			{
				array[p1.x + i][(round(p1.y + temp4 * i))] = 1;
			}
			else if (p1.y>p2.y)
			{
				array[p2.x + i][(round(p2.y + temp4 * i))] = 1;
			}
		}
	}
	//斜率大于-1 小于0
	else if (temp3 > 0 && temp3 <= 1 && temp4 <0)
	{
		//cout<<"斜率大于-1 小于0"<<endl;
		for (int i = 0; i <= abs(p1.x - p2.x); i++)
		{
			if (p1.y<p2.y)
			{
				array[p2.x + i][(round(p2.y + temp4 * i))] = 1;
			}
			else if (p1.y>p2.y)
			{
				array[p1.x + i][(round(p1.y + temp4 * i))] = 1;
			}
		}
	}
	//斜率小于-1
	else if (temp3 > 1 && temp4 <0)
	{
		//cout<<"斜率小于-1"<<endl;
		for (int i = 0; i <= abs(p2.y - p1.y); i++)
		{
			if (p1.y>p2.y)
			{
				array[round(p2.x + temp5*i)][p2.y + i] = 1;
			}
			else if (p1.y<p2.y)
			{
				array[round(p1.x + temp5*i)][p1.y + i] = 1;
			}
		}
	}
}
//根据矩形原理规划方案。自动规划核心函数返回值是4个值：1.x轴的个数 2.y轴的个数 3.返回的类型 0表示主观情况1表示倒置 4.是否有0.5
int* makepointnum(double radius, double minx, double maxx, double miny, double maxy)
{
	int  result[4]={0};
	int xfinal1 = 0;
	int yfinal1 = 0;
	int xfinal2 = 0;
	int yfinal2 = 0;
	double count1 = 0.0;
	double count2 = 0.0;
	bool flag1 = false;
	bool flag2 = false;
	double disx = maxx - minx;
	//cout<<"disx:"<<disx<<endl;
	double disy = maxy - miny;
	//cout<<"disy:"<<disy<<endl;
	double rec_heng = 2 * radius;
	//cout<<"rec_heng:"<<rec_heng<<endl;
	double rec_shu = 2 * 1.732*radius;

	int xnum1 = int(disx / rec_heng);
	int ynum1 = int(disy / rec_shu);
	//cout<<"xnum1  ynum1"<<xnum1<<ynum1<<endl;
	xfinal1 = xnum1 + 1;
	if (ynum1*rec_shu + radius > disy)
	{
		yfinal1 = ynum1;
		//cout<<"执行(ynum1*rec_shu +radius > disy)"<<endl;
	}
	else if (ynum1* rec_shu + radius + 1.732*radius>disy)
	{
		yfinal1 = ynum1;
		flag1 = true;
		//cout<<"执行(ynum1* rec_shu+radius+1.732*radius>disy)"<<endl;
	}
	else{
		yfinal1 = ynum1 + 1;
		//cout<<"else"<<endl;
	}
	int xnum2 = int(disx / rec_shu);
	int ynum2 = int(disy / rec_heng);
	//cout<<"xnum2  ynum2"<<xnum2<<ynum2<<endl;
	yfinal2 = ynum2 + 1;
	if (xnum2*rec_shu + radius > disx)
	{
		xfinal2 = xnum2;
	}
	else if (xnum2* rec_shu + radius + 1.732*radius>disx)
	{
		xfinal2 = xnum2;
		flag2 = true;
	}
	else{
		xfinal2 = xnum2 + 1;
	}
	if (flag1)
	{
		count1 = double(xfinal1)*(yfinal1 + 0.5);
		//cout<<"执行!!!!!"<<endl;
	}
	else
	{
		count1 = double(xfinal1*yfinal1);
	}
	//cout<<"count1   :"<<count1;
	if (flag2)
	{
		count2 = double(yfinal2)*(xfinal2 + 0.5);

	}
	else
	{
		count2 = double(yfinal2*xfinal2);
	}
	//cout<<"count2   :"<<count2;
	if (count1<count2)
	{
		result[0] = xfinal1;
		result[1] = yfinal1;
		result[2] = 0;
		if (flag1)
		{
			result[3] = 1;
		}
		else
			result[3] = 0;

	}
	if (count1 >= count2)
	{
		result[0] = xfinal2;
		result[1] = yfinal2;
		result[2] = 1;
		if (flag2)
		{
			result[3] = 1;
		}
		else
			result[3] = 0;

	}
	//cout<<"result  :"<<result[0]<<"   "<<result[1]<<"   "<<result[2]<<"   "<<result[3]<<endl;
	return result;
}
//根据返回值计算规划点,注意!!!!:(规划点200个)
DPoint *designpoint(double radius, double minx, double maxx, double miny, double maxy,double a1,double a2,double a3,double a4,double a5)
{
	DPoint dpoint[200] = {{0.0,0.0,a1,a2,a3,a4,a5}};
	int count = 0;
	int *p;
	int result[4];
	cout << "dpoint[20].x:" << dpoint[20].x;
	p = makepointnum(radius, minx, maxx, miny, maxy);
	for (int i = 0; i<4; i++)
	{
		result[i] = p[i];
	}
	cout << "在desinpoint里result  :" << result[0] << "   " << result[1] << "   " << result[2] << "   " << result[3] << endl;
	int result0 = result[0];
	cout << result0 << endl;
	int result1 = result[1];
	cout << result1 << endl;
	int result2 = result[2];
	cout << result2 << endl;
	int result3 = result[3];
	cout << result3 << endl;
	if (result2 == 0)
	{
		cout << "执行1";
		//正常放置且没有0.5
		if (result3 == 0)
		{
			//处理左线上的点
			for (int i = 0; i<result[1]; i++, count++)
			{
				//cout<<"count1"<<count<<endl;
				dpoint[count].x = minx;
				dpoint[count].y = miny + 1.732 * 2 * i*radius + 1.732*radius + 0.5*radius;
				//cout<<"dpoint[count].x"<<dpoint[count].x<<endl;
			}
			//处理底线的点
			for (int i = 0; i <= result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count2"<<count<<endl;
					dpoint[count].x = minx + radius + 2 * radius*j;
					dpoint[count].y = miny + 0.5*radius + 2 * 1.732*radius*i;
				}
			}
			//中间层其余线
			for (int i = 0; i<result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count3"<<count<<endl;
					dpoint[count].x = minx + radius + 2 * j;
					dpoint[count].y = miny + 1.732 * 2 * i*radius + 1.732*radius + 0.5*radius;
				}
			}
		}
		//多出0.5，也就是多加了一层节点
		if (result3 == 1)
		{
			//处理左线上的点
			for (int i = 0; i <= result[1]; i++, count++)
			{
				//cout<<"count4"<<count<<endl;
				dpoint[count].x = minx;
				dpoint[count].y = miny + 1.732 * 2 * i*radius + 1.732*radius + 0.5*radius;
			}
			//处理底线的点
			for (int i = 0; i <= result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count5"<<count<<endl;
					dpoint[count].x = minx + radius + 2 * radius*j;
					dpoint[count].y = miny + 0.5*radius + 2 * 1.732*radius*i;
				}
			}
			//中间层其余线
			for (int i = 0; i<result[1]; i++)
			{
				for (int j = 0; j <= result[0]; j++, count++)
				{
					//cout<<"count6"<<count<<endl;
					dpoint[count].x = minx + radius + 2 * j;
					dpoint[count].y = miny + 1.732 * 2 * i*radius + 1.732*radius + 0.5*radius;
				}
			}
		}
	}
	//倒立方式
	else if (result2 == 1)
	{
		//不需要0.5
		if (result3 == 0)
		{
			for (int i = 0; i<result[1]; i++, count++)
			{
				//cout<<"count7"<<count<<endl;
				dpoint[count].x = minx + 0.5*radius;
				dpoint[count].y = miny + radius + 2 * radius*i;
				//cout<<"dpoint[count].x"<<dpoint[count].x<<endl;
			}
			for (int i = 0; i <= result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count8"<<count<<endl;
					dpoint[count].x = minx + 0.5*radius + 1.732*radius + 1.732 * 2 * j*radius;
					dpoint[count].y = miny + 2 * radius*i;
					//cout<<"dpoint[count].x"<<dpoint[count].x<<endl;
				}
			}
			for (int i = 0; i<result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count9"<<count<<endl;
					dpoint[count].x = minx + 0.5*radius + 1.732*radius*j + 1.732 * 2 * radius;
					dpoint[count].y = miny + 2 * radius*i + radius;
					//cout<<"dpoint[count].x"<<dpoint[count].x<<endl;
				}
			}
		}
		//需要0.5
		if (result3 == 1)
		{
			for (int i = 0; i<result[1]; i++, count++)
			{
				//cout<<"count10"<<count<<endl;
				dpoint[count].x = minx + 0.5*radius;
				dpoint[count].y = miny + radius + 2 * radius*i;
			}
			for (int i = 0; i <= result[1]; i++)
			{
				for (int j = 0; j <= result[0]; j++, count++)
				{
					//cout<<"count11"<<count<<endl;
					dpoint[count].x = minx + 0.5*radius + 1.732*radius + 1.732 * 2 * j*radius;
					dpoint[count].y = miny + 2 * radius*i;
				}
			}
			for (int i = 0; i<result[1]; i++)
			{
				for (int j = 0; j<result[0]; j++, count++)
				{
					//cout<<"count12"<<count<<endl;
					dpoint[count].x = minx + 0.5*radius + 1.732*radius*j + 1.732 * 2 * radius;
					dpoint[count].y = miny + 2 * radius*i + radius;
				}
			}

		}
	}
	cout << "COUNT" << count << endl;
	cout << "结束执行" << endl;
	return dpoint;
}
//同一纬线上那么两点间的距离=经度差*111km* cos纬度

double getcurcleradius(DPoint center, double distance)
{
	double hudu = center.x *3.1415 / 180;
	double curcleradius = 0.0;
	curcleradius = distance / (111 * cos(hudu));
	return curcleradius;
}
//处理圆形外围的1(修改，改成100*100)
void dealround()
{
	for (int i = 0; i<100; i++)
	{
		for (int j = 0; j<100; j++)
		{
			if (((i - 50)*(i - 50) + (j - 50)*(j - 50)) > 50 * 50)
				array[i][j] = 1;
		}
	}
}
//圆形仿真函数*****（修改去掉指针）,返回指向规划数组的指针
DPoint *dealcurcle(DPoint center, double distance,double a1,double a2,double a3,double a4,double a5)
{

	DPoint *presultpointofcurcle;
	//（修改为数组）
	DPoint test[8]={{0.0,0.0,a1,a2,a3,a4,a5}};
	//（修改增加指针取值）
	DPoint *ptestresult1;
	DPoint *ptestresult2;
	DPoint *ptestresult3;
	DPoint *ptestresult4;
	DPoint *ptestresult5;
	DPoint *ptestresult6;
	DPoint *ptestresult7;
	DPoint *ptestresult8;
	DPoint testresult1[36]={{0,0}};
	DPoint testresult2[36]={{0,0}};
	DPoint testresult3[36]={{0,0}};
	DPoint testresult4[36]={{0,0}};
	DPoint testresult5[36]={{0,0}};
	DPoint testresult6[36]={{0,0}};
	DPoint testresult7[36]={{0,0}};
	DPoint testresult8[36]={{0,0}};
	double minradius[8] = {0.0};//存储八个test节点的最短半径
	double realradius = 0.0;//真正的半径
	//四个点。代表边框的四个点
	DPoint dp1;
	DPoint dp2;
	DPoint dp3;
	DPoint dp4;
	double hudu = center.x / 3.1415;
	//算出精度差，把精度差作为半径
	double curcleradius = distance / (111 * cos(hudu));
	dp1.x = center.x - curcleradius;
	dp1.y = center.y + curcleradius;
	dp2.x = center.x + curcleradius;
	dp2.y = center.y + curcleradius;
	dp3.x = center.x + curcleradius;
	dp3.y = center.y - curcleradius;
	dp4.x = center.x - curcleradius;
	dp4.y = center.y - curcleradius;
	double minx = dp4.x;
	double maxx = dp2.x;
	double miny = dp4.y;
	double maxy = dp2.y;
	//算出单位格的代表的精度值(修改，半径改为50)；
	double singledis = curcleradius / 50;
	dealround();
	//为8个DPoint点赋随机值
	test[0].x = makerandomx(minx, singledis);
	test[0].y = makerandomy(miny, singledis);
	test[1].x = makerandomx(minx, singledis);
	test[1].y = makerandomy(miny, singledis);
	test[2].x = makerandomx(minx, singledis);
	test[2].y = makerandomy(miny, singledis);
	test[3].x = makerandomx(minx, singledis);
	test[3].y = makerandomy(miny, singledis);
	test[4].x = makerandomx(minx, singledis);
	test[4].y = makerandomy(miny, singledis);
	test[5].x = makerandomx(minx, singledis);
	test[5].y = makerandomy(miny, singledis);
	test[6].x = makerandomx(minx, singledis);
	test[6].y = makerandomy(miny, singledis);
	test[7].x = makerandomx(minx, singledis);
	test[7].y = makerandomy(miny, singledis);
	//将GuiHua站点指针获取
	ptestresult1 = GuiHua(test[0]);
	for (int i = 0; i<36; i++)
	{
		testresult1[i] = ptestresult1[i];
	}
	ptestresult2 = GuiHua(test[1]);
	for (int i = 0; i<36; i++)
	{
		testresult2[i] = ptestresult2[i];
	}
	ptestresult3 = GuiHua(test[2]);
	for (int i = 0; i<36; i++)
	{
		testresult3[i] = ptestresult3[i];
	}
	ptestresult4 = GuiHua(test[3]);
	for (int i = 0; i<36; i++)
	{
		testresult4[i] = ptestresult4[i];
	}
	ptestresult5 = GuiHua(test[4]);
	for (int i = 0; i<36; i++)
	{
		testresult5[i] = ptestresult5[i];
	}
	ptestresult6 = GuiHua(test[5]);
	for (int i = 0; i<36; i++)
	{
		testresult6[i] = ptestresult6[i];
	}
	ptestresult7 = GuiHua(test[6]);
	for (int i = 0; i<36; i++)
	{
		testresult7[i] = ptestresult7[i];
	}
	ptestresult8 = GuiHua(test[7]);
	for (int i = 0; i<36; i++)
	{
		testresult8[i] = ptestresult8[i];
	}
	minradius[0] = getradius(testresult1, test[0]);
	minradius[1] = getradius(testresult2, test[1]);
	minradius[2] = getradius(testresult3, test[2]);
	minradius[3] = getradius(testresult4, test[3]);
	minradius[4] = getradius(testresult5, test[4]);
	minradius[5] = getradius(testresult6, test[5]);
	minradius[6] = getradius(testresult7, test[6]);
	minradius[7] = getradius(testresult8, test[7]);
	realradius = getmin(minradius, 8);//获取半径权值
	presultpointofcurcle = designpoint(realradius, minx, maxx, miny, maxy,a1,a2,a3,a4,a5);//获取最后的仿真节点的数组
	return presultpointofcurcle;
}
//初始化多边形
void dealpolygone(int number, DPoint dpoint[], double minx, double maxx, double miny, double maxy)
{
	cout << "进入初始化多边形" << endl;
	Point *point;
	//将DPoint转换为Point
	point = dptransformtop(dpoint, minx, maxx, miny, maxy);
	//cout<<"point[0].x"<<point[0].x<<"point[0].y"<<point[0].y<<endl;
	//cout<<"point[1].x"<<point[1].x<<"point[1].y"<<point[1].y<<endl;
	//cout<<"point[2].x"<<point[2].x<<"point[2].y"<<point[2].y<<endl;
	//cout<<"point[3].x"<<point[3].x<<"point[3].y"<<point[3].y<<endl;
	//cout<<"point[4].x"<<point[4].x<<"point[4].y"<<point[4].y<<endl;
	//cout<<"point[5].x"<<point[5].x<<"point[5].y"<<point[5].y<<endl;
	//cout<<"point[6].x"<<point[6].x<<"point[6].y"<<point[6].y<<endl;
	Point pt[200] = { { 0, 0 } };
	//将Point数组点连接起来
	for (int i = 0; i<number - 1; i++)
	{
		cout << "将数组连接起来:" << i << "次" << endl;
		linkpoint(point[i], point[i + 1]);
	}
	linkpoint(point[number - 1], point[0]);
	for (int i = 0; i<99; i++)
	{
		array[0][i] = 1;
		array[99][i] = 1;
		array[i][99] = 1;
		array[i][0] = 1;
	}
	Point p1 = { 1, 1 };
	Point p2 = { 1, 98 };
	Point p3 = { 98, 1 };
	Point p4 = { 98, 98 };

	addsect(p1);
	addsect(p2);
	addsect(p3);
	addsect(p4);
}
//规划多边形*****
DPoint *dealpolymain(int number, DPoint dpoint[],double a1,double a2,double a3,double a4,double a5)
{
	DPoint *resultpointofpoly;
	double minx = dpoint[0].x;
	double maxx = dpoint[0].x;
	double miny = dpoint[0].y;
	double maxy = dpoint[0].y;
	DPoint test[8];//存放随机生成节点
	double minradius[8] = { 0.0 };
	double realradius;//真正最小距离 即半径
	//首先获取minx、maxx、miny、maxy
	for (int i = 0; i<number; i++)
	{
		if (dpoint[i].x<minx)
		{
			minx = dpoint[i].x;
		}
		if (dpoint[i].x>minx)
		{
			maxx = dpoint[i].x;
		}
		if (dpoint[i].y<miny)
		{
			miny = dpoint[i].y;
		}
		if (dpoint[i].y>maxy)
		{
			maxy = dpoint[i].y;
		}
	}
	DPoint *ptestresult1;
	DPoint *ptestresult2;
	DPoint *ptestresult3;
	DPoint *ptestresult4;
	DPoint *ptestresult5;
	DPoint *ptestresult6;
	DPoint *ptestresult7;
	DPoint *ptestresult8;
	DPoint testresult1[36];
	DPoint testresult2[36];
	DPoint testresult3[36];
	DPoint testresult4[36];
	DPoint testresult5[36];
	DPoint testresult6[36];
	DPoint testresult7[36];
	DPoint testresult8[36];

	//算出单位格的代表的精度值；
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;

	dealpolygone(number, dpoint, minx, maxx, miny, maxy);
	//为8个DPoint点赋随机值
	test[0].x = makerandomx(minx, singledisx);
	test[0].y = makerandomy(miny, singledisy);
	test[1].x = makerandomx(minx, singledisx);
	test[1].y = makerandomy(miny, singledisy);
	test[2].x = makerandomx(minx, singledisx);
	test[2].y = makerandomy(miny, singledisy);
	test[3].x = makerandomx(minx, singledisx);
	test[3].y = makerandomy(miny, singledisy);
	test[4].x = makerandomx(minx, singledisx);
	test[4].y = makerandomy(miny, singledisy);
	test[5].x = makerandomx(minx, singledisx);
	test[5].y = makerandomy(miny, singledisy);
	test[6].x = makerandomx(minx, singledisx);
	test[6].y = makerandomy(miny, singledisy);
	test[7].x = makerandomx(minx, singledisx);
	test[7].y = makerandomy(miny, singledisy);
	//将GuiHua站点指针获取
	ptestresult1 = GuiHua(test[0]);
	for (int i = 0; i<36; i++)
	{
		testresult1[i] = ptestresult1[i];
	}
	ptestresult2 = GuiHua(test[1]);
	for (int i = 0; i<36; i++)
	{
		testresult2[i] = ptestresult2[i];
	}
	ptestresult3 = GuiHua(test[2]);
	for (int i = 0; i<36; i++)
	{
		testresult3[i] = ptestresult3[i];
	}
	ptestresult4 = GuiHua(test[3]);
	for (int i = 0; i<36; i++)
	{
		testresult4[i] = ptestresult4[i];
	}
	ptestresult5 = GuiHua(test[4]);
	for (int i = 0; i<36; i++)
	{
		testresult5[i] = ptestresult5[i];
	}
	ptestresult6 = GuiHua(test[5]);
	for (int i = 0; i<36; i++)
	{
		testresult6[i] = ptestresult6[i];
	}
	ptestresult7 = GuiHua(test[6]);
	for (int i = 0; i<36; i++)
	{
		testresult7[i] = ptestresult7[i];
	}
	ptestresult8 = GuiHua(test[7]);
	for (int i = 0; i<36; i++)
	{
		testresult8[i] = ptestresult8[i];
	}
	minradius[0] = getradius(testresult1, test[0]);
	minradius[1] = getradius(testresult2, test[1]);
	minradius[2] = getradius(testresult3, test[2]);
	minradius[3] = getradius(testresult4, test[3]);
	minradius[4] = getradius(testresult5, test[4]);
	minradius[5] = getradius(testresult6, test[5]);
	minradius[6] = getradius(testresult7, test[6]);
	minradius[7] = getradius(testresult8, test[7]);
	realradius = getmin(minradius, 8);//获取半径权值
	resultpointofpoly = designpoint(realradius, minx, maxx, miny, maxy,a1,a2,a3,a4,a5);//获取最后的仿真节点的数组
	return resultpointofpoly;
}
//矩形仿真函数**** 参数是四个点的数组 左上、右上、右下、左下
DPoint *dealrec(DPoint dpoint[],double a1,double a2,double a3,double a4,double a5)
{
	for (int i = 0; i<99; i++)
	{
		array[0][i] = 1;
		array[99][i] = 1;
		array[i][99] = 1;
		array[i][0] = 1;
	}
	DPoint *resultpointofrec;
	DPoint test[8];//存放随机生成节点
	double minradius[8];
	double realradius;//真正最小距离 即半径
	double minx = dpoint[0].x;
	double maxx = dpoint[1].x;
	double miny = dpoint[3].y;
	double maxy = dpoint[0].y;
	DPoint *ptestresult1;
	DPoint *ptestresult2;
	DPoint *ptestresult3;
	DPoint *ptestresult4;
	DPoint *ptestresult5;
	DPoint *ptestresult6;
	DPoint *ptestresult7;
	DPoint *ptestresult8;
	DPoint testresult1[36];
	DPoint testresult2[36];
	DPoint testresult3[36];
	DPoint testresult4[36];
	DPoint testresult5[36];
	DPoint testresult6[36];
	DPoint testresult7[36];
	DPoint testresult8[36];

	//算出单位格的代表的精度值；
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	//为8个DPoint点赋随机值
	test[0].x = makerandomx(minx, singledisx);
	test[0].y = makerandomy(miny, singledisy);
	test[1].x = makerandomx(minx, singledisx);
	test[1].y = makerandomy(miny, singledisy);
	test[2].x = makerandomx(minx, singledisx);
	test[2].y = makerandomy(miny, singledisy);
	test[3].x = makerandomx(minx, singledisx);
	test[3].y = makerandomy(miny, singledisy);
	test[4].x = makerandomx(minx, singledisx);
	test[4].y = makerandomy(miny, singledisy);
	test[5].x = makerandomx(minx, singledisx);
	test[5].y = makerandomy(miny, singledisy);
	test[6].x = makerandomx(minx, singledisx);
	test[6].y = makerandomy(miny, singledisy);
	test[7].x = makerandomx(minx, singledisx);
	test[7].y = makerandomy(miny, singledisy);
	//将GuiHua站点指针获取
	ptestresult1 = GuiHua(test[0]);
	for (int i = 0; i<36; i++)
	{
		testresult1[i] = ptestresult1[i];
	}
	ptestresult2 = GuiHua(test[1]);
	for (int i = 0; i<36; i++)
	{
		testresult2[i] = ptestresult2[i];
	}
	ptestresult3 = GuiHua(test[2]);
	for (int i = 0; i<36; i++)
	{
		testresult3[i] = ptestresult3[i];
	}
	ptestresult4 = GuiHua(test[3]);
	for (int i = 0; i<36; i++)
	{
		testresult4[i] = ptestresult4[i];
	}
	ptestresult5 = GuiHua(test[4]);
	for (int i = 0; i<36; i++)
	{
		testresult5[i] = ptestresult5[i];
	}
	ptestresult6 = GuiHua(test[5]);
	for (int i = 0; i<36; i++)
	{
		testresult6[i] = ptestresult6[i];
	}
	ptestresult7 = GuiHua(test[6]);
	for (int i = 0; i<36; i++)
	{
		testresult7[i] = ptestresult7[i];
	}
	ptestresult8 = GuiHua(test[7]);
	for (int i = 0; i<36; i++)
	{
		testresult8[i] = ptestresult8[i];
	}
	minradius[0] = getradius(testresult1, test[0]);
	minradius[1] = getradius(testresult2, test[1]);
	minradius[2] = getradius(testresult3, test[2]);
	minradius[3] = getradius(testresult4, test[3]);
	minradius[4] = getradius(testresult5, test[4]);
	minradius[5] = getradius(testresult6, test[5]);
	minradius[6] = getradius(testresult7, test[6]);
	minradius[7] = getradius(testresult8, test[7]);
	realradius = getmin(minradius, 8);//获取半径权值
	resultpointofrec = designpoint(realradius, minx, maxx, miny, maxy,a1,a2,a3,a4,a5);//获取最后的仿真节点的数组
	return  resultpointofrec;
}
//计算多边形适应度只能计算50个点的36个值(多加一个参数边界点数量值)<-画风突转 换模块->
double calshiyingduofpoly(DPoint dpoint[], int bordernum, double minx, double maxx, double miny, double maxy)
{
	//先将array清零
	cleararray();
	//将边界画满
	for (int i = 0; i<100; i++)
	{
		array[0][i] = 1;
		array[99][i] = 1;
		array[i][0] = 1;
		array[i][99] = 1;
	}
	dealpolygone(bordernum, dpoint, minx, maxx, miny, maxy);
	//cout<<"进入函数"<<endl;
	double shiyingdu = 0.0;
	//指针存储基站点Point类型的指针
	Point jizhan[200] = { { 0, 0 } };
	//p为取得dpoint数组的指针
	DPoint *p;
	//将p指针指向数组
	p = dpoint;
	//cout<<"读取p2的值：  "<<p[2].x<<"   "<<p[2].y<<endl;
	//cout<<"读取p1的值：  "<<p[1].x<<"   "<<p[1].y<<endl;
	//cout<<"读取p3的值：  "<<p[3].x<<"   "<<p[3].y<<endl;
	//   cout<<"读取p4的值：  "<<p[4].x<<"   "<<p[4].y<<endl;
	//cout<<"读取p5的值：  "<<p[5].x<<"   "<<p[5].y<<endl;
	//保留结果数组
	Point result[200] = {{0, 0 }};
	//进行坐标转化，将dpoint[]数组转化成point
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	//cout<<"到达singledisx："<<singledisx<<endl;
	for (int i = 0; i<200 && dpoint[i].x != 0.0; i++)
	{

		jizhan[i].x = ((dpoint[i].x - minx) / singledisx) - 1;
		jizhan[i].y = ((dpoint[i].y - miny) / singledisy) - 1;

		if (jizhan[i].x<0)
		{
			jizhan[i].x = 0;
		}
		if (jizhan[i].y<0)
		{
			jizhan[i].y = 0;
		}
		//cout<<jizhan[i].x<<"!!!"<<jizhan[i].y<<endl;
	}

	//temp 为获取36个点的临时存储数组（不动）
	DPoint temp[200] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
	//pget为获取每个点周围36个点的指针
	DPoint *pget;
	//pgetp为Point型
	Point *pgetp;

	cout << "准备进行规划" << endl;
	for (int i = 0; i<200 && p[i].x != 0.0; i++)
	{
		cout << "youknowsym" << i << "次" << endl;
		//获取36个点的指针
		pget = GuiHua(p[i]);
		for (int j = 0; j<36; j++)
		{	  //用数组存储
			temp[j] = pget[j];
			//cout<<"temp"<<j<<".x:"<<temp[j].x<<endl;
		}
		//将DPoint转换城Point
		pgetp = dptransformtop(temp, minx, maxx, miny, maxy);
		// 一定要将指针取的数据用数组拿出来
	/*	for (int k = 0; k<36; k++)
		{
			result[k].x = pgetp[k].x;
			result[k].y = pgetp[k].y;
		}*/
		/*cout<<"point数组 pgetp29"<<pgetp[29].x<<"   "<<pgetp[29].y<<endl;
		cout<<"point数组 pgetp30"<<pgetp[30].x<<"   "<<pgetp[30].y<<endl;
		cout<<"point数组 pgetp31"<<pgetp[31].x<<"   "<<pgetp[31].y<<endl;
		cout<<"point数组 pgetp32"<<pgetp[32].x<<"   "<<pgetp[32].y<<endl;
		cout<<"point数组 pgetp33"<<pgetp[33].x<<"   "<<pgetp[33].y<<endl;
		cout<<"point数组 pgetp34"<<pgetp[34].x<<"   "<<pgetp[34].y<<endl;*/
		for (int k = 0; k<35; k++)
		{
			/*  cout<<"kzhi: "<<k<<endl;
			cout<<"point数组 pgetp"<<result[k].x<<"   "<<result[k].y<<endl;*/
			linkpoint(result[k], result[k + 1]);
		}
		linkpoint(result[35], result[0]);
		addsect(jizhan[i]);
	}

	shiyingdu = calc100();
	return shiyingdu;

}
//用户指定数量仿真,返回一个最合适的数组（多边形） &&&&&另一个模块了
DPoint *dealstaticpoly(DPoint border[], int bordernum, int count,double a1,double a2,double a3,double a4,double a5)
{
	
	//保存节点
	DPoint psave = {0.0,0.0,a1,a2,a3,a4,a5};
	//标识随机生成次数的
	int num = 0;
	//代表适应度
	double shiyingdu = 0.0;
	//取数组的指针
	DPoint *pborder;
	pborder = border;
	DPoint result[200]={{0.0,0.0,a1,a2,a3,a4,a5}};
	//首先取minx、maxx、miny、maxy
	double minx = pborder[0].x;
	double maxx = pborder[0].x;
	double miny = pborder[0].y;
	double maxy = pborder[0].y;
	for (int i = 0; i<bordernum; i++)
	{
		if (pborder[i].x<minx)
		{
			minx = pborder[i].x;
		}
		if (pborder[i].x>minx)
		{
			maxx = pborder[i].x;
		}
		if (pborder[i].y<miny)
		{
			miny = pborder[i].y;
		}
		if (pborder[i].y>maxy)
		{
			maxy = pborder[i].y;
		}
	}
	cout << " minx: " << minx << " maxx: " << maxx << " miny: " << miny << " maxy: " << maxy;
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	for (int i = 0; i<count; i++)
	{
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		//cout << "输出随机数组" << result[i].x << " " << result[i].y << endl;
	}
	shiyingdu = calshiyingduofpoly(result, bordernum, minx, maxx, miny, maxy);
	cout << "shiyingdu" << shiyingdu << endl;
	for (int i = 0; i<count && num<count * 4; i = (i + 1) % count, num++)
	{
		double tempshiyingdu = 0.0;
		psave.x = result[i].x;
		psave.x = result[i].y;
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		tempshiyingdu = calshiyingduofpoly(result, bordernum, minx, maxx, miny, maxy);
		if (tempshiyingdu >= shiyingdu)
		{
			shiyingdu = tempshiyingdu;
		}
		else
			result[i].x = psave.x;
		result[i].y = psave.y;
		cout << "result[i].x" << result[i].x << endl;
	}
	result[count].x = shiyingdu;
	result[count].y = 0.0;
	cout << "result[4].x" << result[4].x << endl;
	return result;
}
//计算圆形适应度只能计算50个点的36个值(多加一个参数边界点数量值)
double calshiyingduofcurcle(DPoint dpoint[], double minx, double maxx, double miny, double maxy)
{
	cout << "进入求圆的适应度" << endl;
	double shiyingdu = 0.0;
	cleararray();
	dealround();
	//指针存储基站点Point类型的指针
	Point jizhan[200] = { { 0, 0 } };
	//p为取得dpoint数组的指针
	DPoint *p;
	//将p指针指向数组
	p = dpoint;
	//保留结果数组
	Point result[200] = {{0,0}};
	//进行坐标转化，将dpoint[]数组转化成point
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	for (int i = 0; i<200 && dpoint[i].x != 0.0; i++)
	{

		jizhan[i].x = ((dpoint[i].x - minx) / singledisx) - 1;
		jizhan[i].y = ((dpoint[i].y - miny) / singledisy) - 1;

		if (jizhan[i].x<0)
		{
			jizhan[i].x = 0;
		}
		if (jizhan[i].y<0)
		{
			jizhan[i].y = 0;
		}
		cout << "基站" << jizhan[i].x << "!!!" << jizhan[i].y << endl;
	}
	//temp 为获取36个点的临时存储数组（不动）
	DPoint temp[200] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
	//pget为获取每个点周围36个点的指针
	DPoint *pget;
	//pgetp为Point型
	Point *pgetp;

	//cout<<"准备进行规划"<<endl;
	for (int i = 0; i<200 && p[i].x != 0.0; i++)
	{
		cout << "youknowsym" << i << "次" << endl;
		//获取36个点的指针
		pget = GuiHua(p[i]);
		for (int j = 0; j<36; j++)
		{	  //用数组存储
			temp[j] = pget[j];
			//cout<<"temp"<<j<<".x:"<<temp[j].x<<endl;
		}
		//将DPoint转换城Point
		pgetp = dptransformtop(temp, minx, maxx, miny, maxy);
		// 一定要将指针取的数据用数组拿出来
		for (int i = 0; i<36; i++)
		{
			result[i].x = pgetp[i].x;
			result[i].y = pgetp[i].y;
		}
		/*cout<<"point数组 pgetp29"<<pgetp[29].x<<"   "<<pgetp[29].y<<endl;
		cout<<"point数组 pgetp30"<<pgetp[30].x<<"   "<<pgetp[30].y<<endl;
		cout<<"point数组 pgetp31"<<pgetp[31].x<<"   "<<pgetp[31].y<<endl;
		cout<<"point数组 pgetp32"<<pgetp[32].x<<"   "<<pgetp[32].y<<endl;
		cout<<"point数组 pgetp33"<<pgetp[33].x<<"   "<<pgetp[33].y<<endl;
		cout<<"point数组 pgetp34"<<pgetp[34].x<<"   "<<pgetp[34].y<<endl;*/
		for (int k = 0; k<35; k++)
		{
			/*  cout<<"kzhi: "<<k<<endl;
			cout<<"point数组 pgetp"<<result[k].x<<"   "<<result[k].y<<endl;*/
			linkpoint(result[k], result[k + 1]);
		}
		linkpoint(result[35], result[0]);
		//addsect(jizhan[i]);
	}

	shiyingdu = calc100();
	return shiyingdu;
}
//用户指定数量仿真,返回一个最合适的数组（圆形） &&&&&另一个模块了
DPoint *dealstaticcurcle(double distance, DPoint center, int count,double a1,double a2,double a3,double a4,double a5)
{
	//保存节点
	DPoint psave = {0.0, 0.0,a1,a2,a3,a4,a5};
	//标识随机生成次数的
	int num = 0;
	//代表适应度
	double shiyingdu = 0.0;
	//保留最后结果的数组,数组有效长度为count+1,最后一位的DPoint.x保留最佳适应度。DPoint.y为0.0
	DPoint result[200] = {{0.0, 0.0,a1,a2,a3,a4,a5}};
	DPoint dp1;
	DPoint dp2;
	DPoint dp3;
	DPoint dp4;
	double hudu = center.x / 3.1415;
	//算出精度差，把精度差作为半径
	double curcleradius = distance / (111 * cos(hudu));
	dp1.x = center.x - curcleradius;
	dp1.y = center.y + curcleradius;
	dp2.x = center.x + curcleradius;
	dp2.y = center.y + curcleradius;
	dp3.x = center.x + curcleradius;
	dp3.y = center.y - curcleradius;
	dp4.x = center.x - curcleradius;
	dp4.y = center.y - curcleradius;
	double minx = dp4.x;
	double maxx = dp2.x;
	double miny = dp4.y;
	double maxy = dp2.y;
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	for (int i = 0; i<count; i++)
	{
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		cout << "输出随机数组" << result[i].x << " " << result[i].y << endl;
	}
	shiyingdu = calshiyingduofcurcle(result, minx, maxx, miny, maxy);
	cout << "shiyingdu" << shiyingdu << endl;
	for (int i = 0; i<count && num<count * 4; i = (i + 1) % count, num++)
	{
		double tempshiyingdu = 0.0;
		psave.x = result[i].x;
		psave.x = result[i].y;
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		tempshiyingdu = calshiyingduofcurcle(result, minx, maxx, miny, maxy);
		if (tempshiyingdu >= shiyingdu)
		{
			shiyingdu = tempshiyingdu;
		}
		else
			result[i].x = psave.x;
		result[i].y = psave.y;
		cout << "result[i].x" << result[i].x << endl;
		if (tempshiyingdu>0.99)
			break;
	}
	result[count].x = shiyingdu;
	result[count].y = 0.0;
	cout << "result[4].x" << result[4].x << endl;
	return result;
}
//计算矩形适应度只能计算50个点的36个值(多加一个参数边界点数量值)
double calshiyingduofrec(DPoint dpoint[], double minx, double maxx, double miny, double maxy, int count)
{
	//先将array清零
	cleararray();
	//将边界画满
	for (int i = 0; i<100; i++)
	{
		array[0][i] = 1;
		array[99][i] = 1;
		array[i][0] = 1;
		array[i][99] = 1;
	}
	double shiyingdu = 0.0;
	//指针存储基站点Point类型的指针
	Point jizhan[200] = { { 0, 0 } };
	//p为取得dpoint数组的指针
	DPoint *p;
	//将p指针指向数组
	p = dpoint;
	cout << "读取p2的值：  " << p[2].x << "   " << p[2].y << endl;
	cout << "读取p1的值：  " << p[1].x << "   " << p[1].y << endl;
	cout << "读取p3的值：  " << p[3].x << "   " << p[3].y << endl;
	cout << "读取p4的值：  " << p[4].x << "   " << p[4].y << endl;
	cout << "读取p5的值：  " << p[5].x << "   " << p[5].y << endl;
	//保留结果数组
	Point result[200] = {{0,0}};
	//进行坐标转化，将dpoint[]数组转化成point
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	//cout<<"到达singledisx："<<singledisx<<endl;
	for (int i = 0; i<200 && dpoint[i].x != 0.0; i++)
	{

		jizhan[i].x = ((dpoint[i].x - minx) / singledisx) - 1;
		jizhan[i].y = ((dpoint[i].y - miny) / singledisy) - 1;

		if (jizhan[i].x<0)
		{
			jizhan[i].x = 0;
		}
		if (jizhan[i].y<0)
		{
			jizhan[i].y = 0;
		}
		cout << jizhan[i].x << "!!!" << jizhan[i].y << endl;
	}

	//temp 为获取36个点的临时存储数组（不动）
	DPoint temp[200] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
	//pget为获取每个点周围36个点的指针
	DPoint *pget;
	//pgetp为Point型
	Point *pgetp;

	cout << "准备进行规划" << endl;
	for (int i = 0; i<200 && p[i].x != 0.0; i++)
	{
		cout << "youknowsym" << i << "次" << endl;
		//获取36个点的指针
		pget = GuiHua(p[i]);
		for (int j = 0; j<36; j++)
		{	  //用数组存储
			temp[j] = pget[j];
			//cout<<"temp"<<j<<".x:"<<temp[j].x<<endl;
		}
		//将DPoint转换城Point
		pgetp = dptransformtop(temp, minx, maxx, miny, maxy);
		// 一定要将指针取的数据用数组拿出来
		for (int i = 0; i<36; i++)
		{
			result[i].x = pgetp[i].x;
			result[i].y = pgetp[i].y;
		}
		/*cout<<"point数组 pgetp29"<<pgetp[29].x<<"   "<<pgetp[29].y<<endl;
		cout<<"point数组 pgetp30"<<pgetp[30].x<<"   "<<pgetp[30].y<<endl;
		cout<<"point数组 pgetp31"<<pgetp[31].x<<"   "<<pgetp[31].y<<endl;
		cout<<"point数组 pgetp32"<<pgetp[32].x<<"   "<<pgetp[32].y<<endl;
		cout<<"point数组 pgetp33"<<pgetp[33].x<<"   "<<pgetp[33].y<<endl;
		cout<<"point数组 pgetp34"<<pgetp[34].x<<"   "<<pgetp[34].y<<endl;*/
		for (int k = 0; k<35; k++)
		{
			/*  cout<<"kzhi: "<<k<<endl;
			cout<<"point数组 pgetp"<<result[k].x<<"   "<<result[k].y<<endl;*/
			linkpoint(result[k], result[k + 1]);
		}
		linkpoint(result[35], result[0]);
		//addsect(jizhan[i]);
	}

	shiyingdu = calc100();
	return shiyingdu;
}
//用户指定数量仿真,返回一个最合适的数组（矩形）
DPoint *dealstaticrec(double minx, double maxx, double miny, double maxy, int count,double a1,double a2,double a3,double a4,double a5)
{
	
	//保存节点
	DPoint psave = {0.0,0.0,a1,a2,a3,a4,a5};
	//标识随机生成次数的
	int num = 0;
	//代表适应度
	double shiyingdu = 0.0;
	//保留最后结果的数组,数组有效长度为count+1,最后一位的DPoint.x保留最佳适应度。DPoint.y为0.0
	DPoint result[200] = {{0.0,0.0,a1,a2,a3,a4,a5}};
	double singledisx = (maxx - minx) / 100;
	double singledisy = (maxy - miny) / 100;
	for (int i = 0; i<count; i++)
	{
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		cout << "输出随机数组" << result[i].x << " " << result[i].y << endl;
	}
	shiyingdu = calshiyingduofrec(result, minx, maxx, miny, maxy, count);
	for (int i = 0; i<count && num<count * 4; i = (i + 1) % count, num++)
	{
		double tempshiyingdu = 0.0;
		psave.x = result[i].x;
		psave.x = result[i].y;
		result[i].x = makerandomx(minx, singledisx);
		result[i].y = makerandomy(miny, singledisy);
		tempshiyingdu = calshiyingduofrec(result, minx, maxx, miny, maxy, count);
		if (tempshiyingdu >= shiyingdu)
		{
			shiyingdu = tempshiyingdu;
		}
		else
		result[i].x = psave.x;
		result[i].y = psave.y;
		cout << "result[i].x" << result[i].x << endl;
	}
	result[count].x = shiyingdu;
	result[count].y = 0.0;
	cout << "result[4].x" << result[4].x << endl;
	return result;
}
//int main()
//{
//	DPoint *p;
//	double a = 0.0;
//	DPoint dp[200] = { { 0.0, 0.0 } };
//	DPoint result[200] = { { 0.0, 0.0 } };
//	dp[0].x = 2.2;
//	dp[0].y = 66.9;
//	dp[1].x = 66.6;
//	dp[1].y = 70.1;
//	dp[2].x = 77.8;
//	dp[2].y = 2.3;
//	dp[3].x = 1.2;
//	dp[3].y = 1.1;
//	cout << "dp[7].x" << dp[7].x << endl;
//	cout << "dp[8].x" << dp[8].x << endl;
//	cout << "dp[9].x" << dp[9].x << endl;
//
//	p = dealstaticrec(0.1, 50.1, 0.6, 63.1, 4);
//
//
//
//
//	//cout<<"minx  "<<minx<<"maxx  "<<maxx<<"miny  "<<miny<<"maxy  "<<maxy; 
//	for (int i = 99; i >= 0; i--)
//	{
//		for (int j = 0; j<100; j++)
//		{
//			cout << array[j][i];
//		}
//		cout << endl;
//	}
//
//	return 0;
//
//}

extern "C" DLLEXPORT void scopesimulation()
{
	FIN (scopesimulation());
	CDetailDialog dlg;
	if (IDOK == dlg.DoModal()){
		//dlg.getValueFromEdit();
		//dlg.FindBoundary(dlg.lo,dlg.la,dlg.h,dlg.p,dlg.b,dlg.f,dlg.r);
		//dlg.FindBoundary(73.1,53.2,5.0,0.05,10,1000,250000);
		//cout<<"123132125"<<endl;
		//cout<<dlg.lo<<dlg.la<<dlg.h<<dlg.p<<dlg.b<<dlg.f<<dlg.r<<endl;
		//system("pause");
	}
FOUT;
}

extern "C" DLLEXPORT void stationplan()
{
	FIN(stationplan());
	CDialog3Detail m_StatParam;//监测站属性
	CRectangle m_Rectangle;//矩形规划形状
	CCircle m_Circle;//圆形规划形状
	CChoice m_Choice;//选择规划范围形状
	CIrregular m_Irregular;//每个监测站坐标
	CPointNum m_PointNum;//监测站数目
	CIrregularPoint m_IrregularPoint[Max];//不规则形状的边界点的坐标
	CIrregularPoint m_JianCeZhan[Max];//不规则记录每个监测站的初始坐标
	int ErrorRecord = 0;//记录界面是否非正常退出,0表示正常,1表示异常
	if (IDOK == m_StatParam.DoModal()) {//DoModal()打开站点参数输入窗口
		//==IDOK是为了确保结束窗口是因为用户点击确定后,而不是取消或其他异常情况。
		//在点确定后才能继续后续窗口；否则必须全部结束
		InitailStatParam(m_StatParam.AntennaHeight, m_StatParam.Power, m_StatParam.BandWidth, m_StatParam.Frequentcy, m_StatParam.DataRate);
		//将监测站参数取出，放入全局变量中，参数如下：
		//double Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio
		//对应监测站属性，天线高度，功率，带宽，频率，比特率
		if (!m_StatParam.StationNum)//如果用户不指定监测站数目
		{
			if (m_Choice.DoModal() == IDOK){//打开选择仿真范围形状的窗口
				CString choice = m_Choice.Choice;
				if (choice == _T("圆形")){//如果用户选择的是圆形
					if (m_Circle.DoModal() == IDOK){//打开圆形参数输入窗口，输入圆心点坐标，半径
						//可用参数：圆心经度double CircLong;圆心纬度double CircLati; 半径double CircRadius;
						//TODO 规划函数接口
						//double Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio
						//监测站属性，天线高度，功率，带宽，频率，比特率
						DPoint Center = { m_Circle.CircLong, m_Circle.CircLati,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio };//记录圆心坐标，生成DPoint类型的圆心点
						backto = dealcurcle(Center, m_Circle.CircRadius,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio );//执行规划的相关函数
					}//if(m_Circle.DoModal()==IDOK)
				}//if(choice == _T("圆形"))
				if (choice == _T("矩形")){//如果用户选择的是矩形
					if (m_Rectangle.DoModal() == IDOK){//打开矩形参数输入窗口，输入四个角参数
						//TODO 规划函数接口
						//矩形左上角经度 double LURectLong;矩形左上角纬度 double UPRectLati;
						//矩形右上角经度 double RURectLong;矩形右上角纬度 double RURectLati;
						//矩形左下角经度 double LDRectLong;矩形左下角纬度 double LDRectLati;
						//矩形右下角经度 double RDRectLong;矩形右下角纬度 double RDRectLati;
						DPoint Center[4]={{0.0,0.0,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio}};
						Center[0].x = m_Rectangle.LURectLong;
						Center[0].y = m_Rectangle.UPRectLati;
						Center[1].x = m_Rectangle.RURectLong;
						Center[1].y = m_Rectangle.RURectLati;
						Center[2].x = m_Rectangle.RDRectLong;
						Center[2].y = m_Rectangle.RDRectLati;
						Center[3].x = m_Rectangle.LDRectLong;
						Center[3].y = m_Rectangle.LDRectLati;
						backto = dealrec(Center,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio);
					}//if(m_Rectangle.DoModal()== IDOK)
				}//if(choice == _T("矩形"))
				if (choice == _T("不规则形状")){
					//m_Irregular.DoModal();
					if (m_PointNum.DoModal() == IDOK){//打开不规则参数输入窗口，记录每个边界点的坐标
						int pointNum = m_PointNum.NumOfPoint;//pointNum为边界点个数
						for (int i = 0; i < pointNum; i++)//记录每个边界点的坐标
						{
							if (m_IrregularPoint[i].DoModal() != IDOK) { ErrorRecord = 1; break; }
						}
						if (ErrorRecord) return;
						DPoint Center[200]={{0.0,0.0,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio}};
						for (int i = 0; i < pointNum; i++)
						{
							Center[i].x = m_IrregularPoint[i].IregPointLong;
							Center[i].y = m_IrregularPoint[i].IregPointLati;
						}
						//TODO 不规则形状规划函数接口
						backto = dealpolymain(pointNum, Center,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio);
						//坐标个数 int NumOfPoints;
						//double IregPointLong 经度;double IregPointLati 纬度
					}//if(m_PointNum.DoModal()== IDOK)
				}//if(choice == _T("不规则形状"))
				//MessageBox(NULL,_T("建站规划程序暂未开发"),_T("无线电监测站覆盖范围仿真规划系统"),MB_OK);
			}//if(m_Choice.DoModal())
		}//if(m_StatParam.StationNum)

		else//用户指定监测站数目
		{
			int StaionNum = m_StatParam.StationNum;
			MessageBox(NULL, _T("请输入每个监测站的初始坐标"), _T("无线电监测站覆盖范围仿真规划系统"), MB_OK);
			for (int i = 0; i < StaionNum; i++) {//记录每个监测站的初始坐标
				if (m_JianCeZhan[i].DoModal() != IDOK) { ErrorRecord = 1; break; } 
				//如果中途退出，标识ErrorRecord置1，供后面的判断退出程序
			}
			if (ErrorRecord) return;//若标识为1，则前面的输入出现问题，退出程序
			//m_Irregular.DoModal();
			DPoint JianCeZhan[200]={0.0,0.0,0.0,0.0,0.0,0.0,0.0};
			for (int i = 0; i < StaionNum; i++) {//对每个监测站的各个参数赋值
				//double Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio
				//监测站属性，天线高度，功率，带宽，频率，比特率
				JianCeZhan[i].x = m_JianCeZhan[i].IregPointLong;
				JianCeZhan[i].y = m_JianCeZhan[i].IregPointLati;
				JianCeZhan[i].AntennaHeight = Stat_height;
				JianCeZhan[i].Power = Stat_power;
				JianCeZhan[i].BandWidth = Stat_bound;
				JianCeZhan[i].Frequentcy = Stat_freq;
				JianCeZhan[i].DataRate = Stat_ratio;
			}//for (int i = 0; i < StaionNum; i++)
			if (m_Choice.DoModal() == IDOK){//打开选择仿真范围形状的窗口
				CString choice = m_Choice.Choice;//choice为用户选定的范围形状
				if (choice == _T("圆形")){//如果用户选择的是圆形
					if (m_Circle.DoModal() == IDOK){//打开圆形参数输入窗口，输入圆心点坐标，半径
						DPoint center ={m_Circle.CircLong,m_Circle.CircLati,0.0,0.0,0.0,0.0,0.0};
						backto=dealstaticcurcle(m_Circle.CircRadius, center, StaionNum, Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio);
						//可用参数：圆心经度double CircLong;圆心纬度double CircLati; 半径double CircRadius;StaionNum用户基站数
						//TODO 圆形规划函数添加处
					}//if (m_Circle.DoModal() == IDOK)
				}//if (choice == _T("圆形"))
				if (choice == _T("矩形")) {//如果用户选择的是矩形
					if (m_Rectangle.DoModal() == IDOK){//打开矩形参数输入窗口，输入四个角参数
						DPoint Center[4]={{0.0,0.0,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio}};
						Center[0].x = m_Rectangle.LURectLong;
						Center[0].y = m_Rectangle.UPRectLati;
						Center[1].x = m_Rectangle.RURectLong;
						Center[1].y = m_Rectangle.RURectLati;
						Center[2].x = m_Rectangle.RDRectLong;
						Center[2].y = m_Rectangle.RDRectLati;
						Center[3].x = m_Rectangle.LDRectLong;
						Center[3].y = m_Rectangle.LDRectLati;
						//根据边框取min、max
						backto=dealstaticrec(Center[0].x, Center[1].x, Center[2].y, Center[0].y ,StaionNum,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio);

						//可用参数：矩形左上角经度 double LURectLong;矩形左上角纬度 double UPRectLati;
						//矩形右上角经度 double RURectLong;矩形右上角纬度 double RURectLati;
						//矩形左下角经度 double LDRectLong;矩形左下角纬度 double LDRectLati;
						//矩形右下角经度 double RDRectLong;矩形右下角纬度 double RDRectLati;
						//TODO 矩形规划函数添加处
					}//if (m_Rectangle.DoModal() == IDOK)
				}//if (choice == _T("矩形"))
				if (choice == _T("不规则形状")){//如果用户选择的是不规则形状
					if (m_PointNum.DoModal() == IDOK){//打开不规则参数输入窗口，记录每个边界点的坐标
						int pointNum = m_PointNum.NumOfPoint;//pointNum为边界点个数
						for (int i = 0; i < pointNum; i++)
						{
							//m_IrregularPoint[i].SetStaticText(i);
							//m_IrregularPoint[i].GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("dasd"));
							if (m_IrregularPoint[i].DoModal() != IDOK) { ErrorRecord = 1; break; }
						}
						if (ErrorRecord) return;
						DPoint Center[200]={{0.0,0.0,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio}};//监测站
						for (int i = 0; i < pointNum; i++)
						{
							Center[i].x = m_IrregularPoint[i].IregPointLong;
							Center[i].y = m_IrregularPoint[i].IregPointLati;
						}

						backto = dealstaticpoly(Center, pointNum, StaionNum,Stat_height,Stat_power,Stat_bound, Stat_freq, Stat_ratio);


						//坐标个数 int NumOfPoints;
						//double IregPointLong 经度;double IregPointLati 纬度
						//TODO 规划函数接口
					}//if (m_PointNum.DoModal() == IDOK)
				}//if (choice == _T("不规则形状"))
			 }//if (m_Choice.DoModal() == IDOK)
			}//else//用户指定监测站数目
		}//if(IDOK==m_StatParam.DoModal())
		FOUT;
}//extern "C" DLLEXPORT void stationplan()

extern "C" DLLEXPORT void ShiYingDu()
{
	FIN(ShiYingDu());
	int BiaoZhi = 0;
	CPointNum m_PointNum;
	CDetailDialog m_StationPara[200];
	if (m_PointNum.DoModal()==IDOK){//输入监测站个数
		int NumOfPoint = m_PointNum.NumOfPoint;
		for (int i = 0; i < NumOfPoint; i++)//依次输入每个监测站的参数
		{
			if (m_StationPara[i].DoModal() != IDOK){ BiaoZhi = 1; break; }
		}
		if (BiaoZhi) return;
		//可用参数：中心站点经度 double m_StationPara[i].Longitude;中心站点纬度.Latitude;
		//天线高度.AntennaHeight;发射机功率.Power;频率.Frequentcy;带宽.BandWidth;比特率.DataRate;
		//TODO 适应度函数接口
	}
	FOUT;
}