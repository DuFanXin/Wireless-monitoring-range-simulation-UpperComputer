// radio.h : radio DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CradioApp
// 有关此类实现的信息，请参阅 radio.cpp
//

class CradioApp : public CWinApp
{
public:
	CradioApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
struct Point
{
int x;
int y;
};
struct DPoint
{
    double x;
    double y;	
	double AntennaHeight;
	double Power;
	double Frequentcy;
	double BandWidth;
	double DataRate;
};

////获取坐标,放在有完整参数的数组中
void GetCoordinate(DPoint Coordinate[]);//0~8,11~19
//基站参数初始化
void InitailStatParam(double m_height, double m_power, double m_bound, double m_freq, double m_ratio);
//仿真得到一个点的范围
void FindBoundary(double longitude, double latitude, double m_height, double m_power, double m_bound, double m_freq, double m_ratio);
//获取坐标,放在数组中
void GetCoordinate(DPoint Coordinate[]);
//规划，返回N个点的坐标
DPoint* GuiHua(DPoint Point);
//规划，返回N个点的坐标(包括其他参数)
DPoint* GuiHua(DPoint Point);
//将字符串转化为double
double StringToDouble(char x[], int Begin, int End);//0~8,11~19

//计算数组1的百分比，计算得出适应度
double calc100();
//清除array[][]
void cleararray();
//从中心点填充36个点，将节点入队列，将其四周为0的顶点压入队列。然后依次出队列，再压缩进队列。以此循环
void addsect(Point c);
//计算圆最短半径（修改，改成数组的形式）
double getradius(DPoint point[], DPoint center);
//生成DPoint类型的x随机坐标
double makerandomx(double minx, double singledis);
//生成DPoint类型的y随机坐标
double makerandomy(double miny, double singledis);
//计算数组中的最小值(修改，增加参数长度)
double getmin(double array[], int num);
//四舍五入函数
int round(float x);
//形式转换（当节点越出边界为负值，将其设为0）
Point *dptransformtop(DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//将两个Point点连接，将连线的值设为1。
void linkpoint(Point p1, Point p2);
//根据矩形原理规划方案。自动规划核心函数返回值是4个值：1.x轴的个数 2.y轴的个数 3.返回的类型 0表示主观情况1表示倒置 4.是否有0.5
int* makepointnum(double radius, double minx, double maxx, double miny, double maxy);
//根据返回值计算规划点,注意!!!!:(规划点200个)
DPoint *designpoint(double radius, double minx, double maxx, double miny, double maxy,double a1,double a2,double a3,double a4,double a5);
//同一纬线上那么两点间的距离=经度差*111km* cos纬度

double getcurcleradius(DPoint center, double distance);
//处理圆形外围的1(修改，改成100*100)
void dealround();
//圆形仿真函数*****（修改去掉指针）,返回指向规划数组的指针
DPoint *dealcurcle(DPoint center, double distance,double a1,double a2,double a3,double a4,double a5);
//初始化多边形
void dealpolygone(int number, DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//规划多边形*****
DPoint *dealpolymain(int number, DPoint dpoint[],double a1,double a2,double a3,double a4,double a5);
//矩形仿真函数**** 参数是四个点的数组 左上、右上、右下、左下
DPoint *dealrec(DPoint dpoint[],double a1,double a2,double a3,double a4,double a5);
//计算多边形适应度只能计算50个点的36个值(多加一个参数边界点数量值)
double calshiyingduofpoly(DPoint dpoint[], int bordernum, double minx, double maxx, double miny, double maxy);
//用户指定数量仿真,返回一个最合适的数组（多边形） &&&&&另一个模块了
DPoint *dealstaticpoly(DPoint border[], int bordernum, int count,double a1,double a2,double a3,double a4,double a5);
//计算圆形适应度只能计算50个点的36个值(多加一个参数边界点数量值)
double calshiyingduofcurcle(DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//用户指定数量仿真,返回一个最合适的数组（圆形） &&&&&另一个模块了
DPoint *dealstaticcurcle(double distance, DPoint center, int count,double a1,double a2,double a3,double a4,double a5);
//计算矩形适应度只能计算50个点的36个值(多加一个参数边界点数量值)
double calshiyingduofrec(DPoint dpoint[], double minx, double maxx, double miny, double maxy, int count);
//用户指定数量仿真,返回一个最合适的数组（矩形）
DPoint *dealstaticrec(double minx, double maxx, double miny, double maxy, int count,double a1,double a2,double a3,double a4,double a5);


