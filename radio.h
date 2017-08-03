// radio.h : radio DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CradioApp
// �йش���ʵ�ֵ���Ϣ������� radio.cpp
//

class CradioApp : public CWinApp
{
public:
	CradioApp();

// ��д
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

////��ȡ����,����������������������
void GetCoordinate(DPoint Coordinate[]);//0~8,11~19
//��վ������ʼ��
void InitailStatParam(double m_height, double m_power, double m_bound, double m_freq, double m_ratio);
//����õ�һ����ķ�Χ
void FindBoundary(double longitude, double latitude, double m_height, double m_power, double m_bound, double m_freq, double m_ratio);
//��ȡ����,����������
void GetCoordinate(DPoint Coordinate[]);
//�滮������N���������
DPoint* GuiHua(DPoint Point);
//�滮������N���������(������������)
DPoint* GuiHua(DPoint Point);
//���ַ���ת��Ϊdouble
double StringToDouble(char x[], int Begin, int End);//0~8,11~19

//��������1�İٷֱȣ�����ó���Ӧ��
double calc100();
//���array[][]
void cleararray();
//�����ĵ����36���㣬���ڵ�����У���������Ϊ0�Ķ���ѹ����С�Ȼ�����γ����У���ѹ�������С��Դ�ѭ��
void addsect(Point c);
//����Բ��̰뾶���޸ģ��ĳ��������ʽ��
double getradius(DPoint point[], DPoint center);
//����DPoint���͵�x�������
double makerandomx(double minx, double singledis);
//����DPoint���͵�y�������
double makerandomy(double miny, double singledis);
//���������е���Сֵ(�޸ģ����Ӳ�������)
double getmin(double array[], int num);
//�������뺯��
int round(float x);
//��ʽת�������ڵ�Խ���߽�Ϊ��ֵ��������Ϊ0��
Point *dptransformtop(DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//������Point�����ӣ������ߵ�ֵ��Ϊ1��
void linkpoint(Point p1, Point p2);
//���ݾ���ԭ��滮�������Զ��滮���ĺ�������ֵ��4��ֵ��1.x��ĸ��� 2.y��ĸ��� 3.���ص����� 0��ʾ�������1��ʾ���� 4.�Ƿ���0.5
int* makepointnum(double radius, double minx, double maxx, double miny, double maxy);
//���ݷ���ֵ����滮��,ע��!!!!:(�滮��200��)
DPoint *designpoint(double radius, double minx, double maxx, double miny, double maxy,double a1,double a2,double a3,double a4,double a5);
//ͬһγ������ô�����ľ���=���Ȳ�*111km* cosγ��

double getcurcleradius(DPoint center, double distance);
//����Բ����Χ��1(�޸ģ��ĳ�100*100)
void dealround();
//Բ�η��溯��*****���޸�ȥ��ָ�룩,����ָ��滮�����ָ��
DPoint *dealcurcle(DPoint center, double distance,double a1,double a2,double a3,double a4,double a5);
//��ʼ�������
void dealpolygone(int number, DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//�滮�����*****
DPoint *dealpolymain(int number, DPoint dpoint[],double a1,double a2,double a3,double a4,double a5);
//���η��溯��**** �������ĸ�������� ���ϡ����ϡ����¡�����
DPoint *dealrec(DPoint dpoint[],double a1,double a2,double a3,double a4,double a5);
//����������Ӧ��ֻ�ܼ���50�����36��ֵ(���һ�������߽������ֵ)
double calshiyingduofpoly(DPoint dpoint[], int bordernum, double minx, double maxx, double miny, double maxy);
//�û�ָ����������,����һ������ʵ����飨����Σ� &&&&&��һ��ģ����
DPoint *dealstaticpoly(DPoint border[], int bordernum, int count,double a1,double a2,double a3,double a4,double a5);
//����Բ����Ӧ��ֻ�ܼ���50�����36��ֵ(���һ�������߽������ֵ)
double calshiyingduofcurcle(DPoint dpoint[], double minx, double maxx, double miny, double maxy);
//�û�ָ����������,����һ������ʵ����飨Բ�Σ� &&&&&��һ��ģ����
DPoint *dealstaticcurcle(double distance, DPoint center, int count,double a1,double a2,double a3,double a4,double a5);
//���������Ӧ��ֻ�ܼ���50�����36��ֵ(���һ�������߽������ֵ)
double calshiyingduofrec(DPoint dpoint[], double minx, double maxx, double miny, double maxy, int count);
//�û�ָ����������,����һ������ʵ����飨���Σ�
DPoint *dealstaticrec(double minx, double maxx, double miny, double maxy, int count,double a1,double a2,double a3,double a4,double a5);


