#include <iostream>
#include <rpc.h>      
#include <rpcndr.h>      
#include <unknwn.h>  
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#include <tchar.h>
#include <vector>
#pragma comment(lib, "gdiplus.lib")
using namespace std;
using namespace Gdiplus;
const int vert_num = 33;
struct point
{
	int x, y;
};
struct segment
{
	point begin, end;
};
bool OnSegment(point pi, point pj, point pk) //判断点pk是否在线段pi pj上   
{
	if (min(pi.x, pj.x) <= pk.x&&pk.x <= max(pi.x, pj.x))
	{
		if (min(pi.y, pj.y) <= pk.y&&pk.y <= max(pi.y, pj.y))
		{
			return true;
		}
	}
	return false;
}
double Direction(point pi, point pj, point pk) //计算向量pkpi和向量pjpi的叉积   
{
	return (pi.x - pk.x)*(pi.y - pj.y) - (pi.y - pk.y)*(pi.x - pj.x);
}
bool Judge(point p1, point p2, point p3, point p4) //判断线段p1p2和p3p4是否相交   
{
	double d1 = Direction(p3, p4, p1);
	double d2 = Direction(p3, p4, p2);
	double d3 = Direction(p1, p2, p3);
	double d4 = Direction(p1, p2, p4);
	if (d1*d2<0 && d3*d4<0)
		return true;
	/*if (d1 == 0 && OnSegment(p3, p4, p1))
		return true;
	if (d2 == 0 && OnSegment(p3, p4, p2))
		return true;
	if (d3 == 0 && OnSegment(p1, p2, p3))
		return true;
	if (d4 == 0 && OnSegment(p1, p2, p4))
		return true;*/
	return false;
}
bool JudgeAll(point p1, point p2, segment s[]){ // true 有线段相交, false 没有线段相交
	for (int i = 0; i < vert_num; i++)
		if (Judge(p1, p2, s[i].begin, s[i].end) == true) return true;
	return false;
}
INT GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
	UINT  num = 0;          // number of image encoders    
	UINT  size = 0;         // size of the image encoder array in bytes    

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure    

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure    

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success    
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure   
}

// Get the distance of two points
float GetLength(int x1, int y1, int x2, int y2)    
{
	float disx = x1 - x2;
	float disy = y1 - y2;
	float num = (disx * disx) + (disy * disy);
	return sqrt(num);
}

BOOLEAN WhetherOnALine(int x1, int y1, int x2, int y2, int x3, int y3){
	if ((x3 - x2)*(y2 - y1) == (y3 - y2)*(x2 - x1)) return true;
	else return false;
}
boolean Mutex(int a, int b){
	if (a == 1 && b == 15) return true;
	if (a == 1 && b == 19) return true;
	if (a == 12 && b == 11) return true;
	if (a == 12 && b == 19) return true;
	if (a == 15 && b == 11) return true;
	if (a == 4 && b == 9) return true;
	if (a == 2 && b == 13) return true;
	if (a == 5 && b == 17) return true;
	if (a == 6 && b == 16) return true;
	if (a == 3 && b == 22) return true;
	if (a == 7 && b == 8) return true;
	if (a == 31 && b == 26) return true;
	if (a == 27 && b == 32) return true;
	if (a == 25 && b == 24) return true;
	if (a == 25 && b == 30) return true;
	if (a == 25 && b == 33) return true;
	if (a == 18 && b == 30) return true;
	if (a == 18 && b == 33) return true;
	if (a == 18 && b == 29) return true;
	if (a == 29 && b == 24) return true;
	if (a == 29 && b == 30) return true;
	if (a == 24 && b == 33) return true;


	if (b == 1 && a == 15) return true;
	if (b == 1 && a == 19) return true;
	if (b == 12 && a == 11) return true;
	if (b == 12 && a == 19) return true;
	if (b == 15 && a == 11) return true;
	if (b == 4 && a == 9) return true;
	if (b == 2 && a == 13) return true;
	if (b == 5 && a == 17) return true;
	if (b == 6 && a == 16) return true;
	if (b == 3 && a == 22) return true;
	if (b == 7 && a == 8) return true;
	if (b == 31 && a == 26) return true;
	if (b == 27 && a == 32) return true;
	if (b == 25 && a == 24) return true;
	if (b == 25 && a == 30) return true;
	if (b == 25 && a == 33) return true;
	if (b == 18 && a == 30) return true;
	if (b == 18 && a == 33) return true;
	if (b == 18 && a == 29) return true;
	if (b == 29 && a == 24) return true;
	if (b == 29 && a == 30) return true;
	if (b == 24 && a == 33) return true;
	return false;
}
int main(){
	ULONG_PTR m_gdiplusToken;
	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	// Original map name
	wstring infilename(L"map.jpg");
	string outfilename("color.txt");
	// Original map
	Bitmap* map = new Bitmap(infilename.c_str());
	Bitmap *bmp = new Bitmap(L"original_map.jpg");
	// Create graphics object for alteration.
	Graphics *g = Graphics::FromImage(bmp);
	Pen* myPen = new Pen(Color::YellowGreen);
	myPen->SetWidth(2);
	UINT height = map->GetHeight();
	UINT width = map->GetWidth();
	int p[600][300];
	memset(p, 0, sizeof(p));
	cout << "width " << width << ", height " << height << endl;
	Color color;
	ofstream fout(outfilename.c_str());
	// Get the vertex.
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++){
		map->GetPixel(x, y, &color);
		if ((int)color.GetRed() >= 150 && (int)color.GetGreen() <= 80 && (int)color.GetBlue() <= 80){
			// Get the vertex positions approximately.
			p[x][y] = 1;
		}
		}

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++){
		if (p[x][y] == 1)
			for (int m = y - 10; m <= y + 10; m++)
				for (int n = x - 10; n <= x + 10; n++)
					if ((m != y) || (n != x)) p[n][m] = 0;
		}
	// List the positions of vertex pixels
	cout << "Here're the positions of vertex pixels:" << endl;
	// 33 vertices at all;

	int _x[50];
	int _y[50];
	memset(_x, 0, sizeof(_x));
	memset(_y, 0, sizeof(_y));
	int k = 0;
	point poi[vert_num];
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++){
		if (p[x][y] == 1){
			_x[k] = x;
			_y[k] = y;
			poi[k].x = x;
			poi[k].y = y;
			k++;
			// Output the positions to a txt file for future use.
			fout << x << "," << y << endl;
		}
		}
	// Output the positions to screen.
	for (k = 0; k < vert_num; k++) cout << poi[k].x << "," << poi[k].y << endl;
	// Define segments.
	segment seg[vert_num];
	seg[1] = { poi[0], poi[11]};
	seg[2] = { poi[0], poi[10] };
	seg[3] = { poi[11], poi[14] };
	seg[4] = { poi[14], poi[18] };
	seg[5] = { poi[10], poi[18] };
	seg[6] = { poi[9], poi[20] };
	seg[7] = { poi[9], poi[19] };
	seg[8] = { poi[19], poi[20] };
	seg[9] = { poi[12], poi[3] };
	seg[10] = { poi[12], poi[8] };
	seg[11] = { poi[3], poi[1] };
	seg[12] = { poi[1], poi[8] };
	seg[13] = { poi[15], poi[4] };
	seg[14] = { poi[15], poi[16] };
	seg[15] = { poi[4], poi[5] };
	seg[16] = { poi[5], poi[16] };
	seg[17] = { poi[2], poi[6] };
	seg[18] = { poi[2], poi[7] };
	seg[19] = { poi[6], poi[21] };
	seg[20] = { poi[7], poi[21] };
	seg[21] = { poi[26], poi[25] };
	seg[22] = { poi[26], poi[30] };
	seg[23] = { poi[30], poi[31] };
	seg[24] = { poi[25], poi[31] };
	seg[25] = { poi[13], poi[22] };
	seg[26] = { poi[13], poi[27] };
	seg[27] = { poi[22], poi[27] };
	seg[28] = { poi[17], poi[24] };
	seg[29] = { poi[17], poi[23] };
	seg[30] = { poi[24], poi[28] };
	seg[31] = { poi[28], poi[32] };
	seg[32] = { poi[32], poi[29] };
	seg[0] = { poi[29], poi[23] };
	

	/*
	// Label each vertice.
	WCHAR buf[16];

	// Create font and brush.
	Font *drawFont = new Font(L"Arial", 16);
	SolidBrush *drawBrush = new SolidBrush(Color::Black);
	for (int x = 1; x <= vert_num; x++){
	wsprintfW(buf, L"%d", x);
	// Create point for upper-left corner of drawing.
	PointF drawPoint = PointF(_x[x], _y[x] - 10);
	// Draw string to map.
	g->DrawString(buf, 2, drawFont, drawPoint, drawBrush);
	}
	*/
	memset(p, 0, sizeof(p));
	// Get the black points in the map.
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++){
			bmp->GetPixel(x, y, &color);
			if ((int)color.GetRed() != 255 && (int)color.GetGreen() !=255 && (int)color.GetBlue() !=255)
				// Set the black points
				p[x][y] = 1;
		}
	cout << "Check the original_map_with_label.jpg" << endl;
	cout << "And input only the label of vertice you want to draw path from!" << endl;
	cin >> k;
	while (k < 1 || k>33){
		cout << "The number should range from 1 to 33, please input again!" << endl;
		cin >> k;
	}
	boolean flag;
	const int dis = 5;
	const float accuracy = 0.01;
	int algorithm = 1;
	cout << "Now there are 3 algorithms, and you can input 1, 2 or 3 to switch:" << endl;
	cout << "1. Check whether the resultant path intersects with the obstacle lines" << endl;
	cout << "2. Check whether there's a black color pixel on the line of two vertices using the sum of pixel's length to vertices" << endl;
	cout << "3. Check whether there's a black color pixel on the line of two vertices using gradient" << endl;
	cin >> algorithm;
	for (int x = 0; x < vert_num; x++){
		if (algorithm == 2 || algorithm == 3){
			flag = true;
			if (x != k){
				for (int m = 0; m < height; m++)
					for (int n = 0; n < width; n++){
					if (p[m][n] == 1)
						if (((abs(m - _x[x]) > dis) || (abs(n - _y[x]) > dis)) && ((abs(m - _x[k]) > dis) || (abs(n - _y[k]) > dis))){
						if (algorithm == 2)
							if ((GetLength(m, n, _x[x], _y[x]) + GetLength(m, n, _x[k], _y[k])) - GetLength(_x[x], _y[x], _x[k], _y[k]) < accuracy) flag = false;
						if (algorithm == 3)
							if (WhetherOnALine(_x[k], _y[k], m, n, _x[x], _y[x]) == true) flag = false;
						}
					}
			}
			if (flag == true) g->DrawLine(myPen, _x[k - 1], _y[k - 1], _x[x], _y[x]);
		}
		if (algorithm == 1){
			if (x != k - 1)
				if ((JudgeAll(poi[k - 1], poi[x], seg) == false) && Mutex(k, x + 1) == false) g->DrawLine(myPen, _x[k - 1], _y[k - 1], _x[x], _y[x]);
		}
	}

	CLSID jpegClsid;
	GetEncoderClsid(L"image/jpeg", &jpegClsid);
	bmp->Save(L"result.jpg", &jpegClsid, NULL);
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return 0;
}
