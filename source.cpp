#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
#define MinDelta 0.00000000000001


struct Point {
	double x, y, z;
	int index;
	int check = 0;
};

int compareX(const void* P1, const void* P2);
int compareVal(Point *P, int N, double val);
ofstream fout,foutVertex;

int xIndex = 0;
double sameX[3000];

int main(void)
{
	
	int N,count=0;
	double Val =0;
	ifstream fin;
	
	string S = "nv4372.txt";
	fin.open(S);
	//fin.open("test.txt");
	//fin.open("nv1003.txt");
	//fin.open("nv4372.txt");
	//fin.open("nv5805.txt");
	//fin.open("nv1059.txt");
	//fin.open("nv1303.txt");
	//fin.open("nv1709.txt");
	//fin.open("nv1815.txt");	
	//fin.open("nv6493.txt");
	fout.open("out_"+S);
	foutVertex.open("vertex_"+S);

	fin >> N;

	Point *P = new Point[N];

	for (int i = 0; i < N; i++)
	{
		P[i].index = i;
		fin >> P[i].x;
		fin >> P[i].y;
		fin >> P[i].z;
	}
	
	cout.setf(ios::showpoint);
	cout.precision(6);
	cout.fixed;

	foutVertex.setf(ios::showpoint);
	foutVertex.precision(8);
	foutVertex.fixed;

	/*
	for (int i = 0; i < N; i++)
	{
		cout << P[i].index << " : " << "X : " << P[i].x << " Y : " << P[i].y << " Z : " << P[i].z  << endl;
	}
	*/

	//X값에 맞춰 P 정렬
	qsort(P, N,sizeof(Point), compareX);
	
	/*
	for (int i = 0; i < N; i++)
	{
		cout << i<< " : " << "X : " << P[i].x << " Y : " << P[i].y << " Z : " << P[i].z << " preIndex = " << P[i].index << endl;
	}
	*/
	
	while (Val >=0)
	{
		for (int i = 0; i < N; i++)
		{
			P[i].check = 0;
		}

		cout << "오차 범위 입력.(음수 입력시 종료) : ";
		cin >> Val;

		compareVal(P, N, Val);
		
	}
		
	delete[] P;
	return 0;
}
int compareX(const void* P1, const void* P2)
{
	Point a = *(Point*)P1;
	Point b = *(Point*)P2;
	if (a.x - b.x > MinDelta)//a.x가 b.x보다 큰 경우
		return 1;
	else if (abs(a.x - b.x) < MinDelta)//a.x와 b.x가 같은지 비교
		return 0;
	else
		return -1;
}
int compareVal(Point *P, int N, double val)
{		
	int count = 0;
	int numCount = 0;
	if (val < 0)
	{
		cout << "종료..." << endl;
		return count;
	}
	fout << "오차한계 : " << val << endl;
	foutVertex << "Val value  : " << val << endl;
	for (int i = 0; i < N - 1; i++)
	{
		//오차범위(val)내 차이값(abs)이 있으면 같다보고 아니면 다르다고봄
		//차이값이 오차범위에 들어간다=같다고본다
		//Double의 정확한 계산을 위해 MinDelta 사용
		if (val - abs(P[i].x - P[i + 1].x) >= -MinDelta)//P[i].x 와 P[i+1].x를  같다고 봄
		{
			for (int j = i + 1; (val - abs(P[j].x - P[i].x) >= -MinDelta); j++)//P[i].x와 같다고 보는 P[j].x들
			{
				if ( (val - abs(P[j].y - P[i].y) >= -MinDelta) && (val - abs(P[j].z - P[i].z) >= -MinDelta))//y,z둘다 같다고 볼때
				{
					if (!P[i].check)
					{
						numCount++;
						P[i].check = 1;
					}
					if (!P[j].check)
					{
						numCount++;
						P[j].check = 1;
					}
						
					count++;
					//cout << count << " : " << "In: " << P[i].index << " (" << P[i].x << ", " << P[i].y << ", " << P[i].z << ")" << " = ";
					//cout << "In: " << P[j].index << " (" << P[j].x << ", " << P[j].y << ", " << P[j].z << ")" << endl;
					//중복값 및 원래 vertex index 화면 출력

					//fout << count << " : " << "In: " << P[i].index << " (" << P[i].x << ", " << P[i].y << ", " << P[i].z << ")" << " = ";
					//fout << "In: " << P[j].index << " (" << P[j].x << ", " << P[j].y << ", " << P[j].z << ")" << endl;
					//중복값 및 원래 vertex index 화면 출력
				}
			}
		}
	}
	cout << "중복 쌍" << count << "개" << endl;
	cout << "중복으로 여기는 vertex 수" << numCount << "개\n" << endl;

	fout << "중복 쌍 " << count << "개" << endl;
	fout << "중복으로 여기는 vertex 수" << numCount << "개\n" << endl;

	foutVertex << "Pair Num    : " << count <<  endl;
	foutVertex << "Vertex Num  : " << numCount << endl;
	foutVertex << "Vertex list : " << endl;
	for (int i = 0; i < N; i++)
	{
		if (P[i].check == 1)
			foutVertex << "in " << P[i].index << " (" << P[i].x << ", " << P[i].y << ", " << P[i].z << ")" << endl;
	}
	foutVertex <<"\n";


	
	return numCount;
}