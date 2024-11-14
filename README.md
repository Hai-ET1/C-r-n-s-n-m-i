#include <iostream>  
#include <fstream>   
#include <windows.h>
#include <conio.h>     
#include <ctime>     

// Các hang se dùng trong chuong trình
#define MAX 100          // So luong toi da các doan cua ran 
#define LEN 1            // Huong di chuyen lên
#define XUONG 2          // Huong di chuyen xuong
#define TRAI 3           // Huong di chuyen trái
#define PHAI 4           // Huong di chuyen phai
#define TUONG_TREN 1     // Toa do tuong trên
#define TUONG_DUOI 20    // Toa do tuong duoi
#define TUONG_TRAI 3     // Toa do tuong trái
#define TUONG_PHAI 50    // Toa do tuong phai
#define DE 0             // Muc do de
#define TRUNG_BINH 1     // Muc do trung bình
#define KHO 2            // Muc do khó
#define BLACK_COLOR			0
#define DARK_BLUE_COLOR		1
#define DARK_GREEN_COLOR	2
#define DARK_CYAN_COLOR		3
#define DARK_RED_COLOR		4
#define DARK_PINK_COLOR		5
#define DARK_YELLOW_COLOR	6
#define DARK_WHITE_COLOR	7
#define GREY_COLOR			8
#define BLUE_COLOR			9
#define GREEN_COLOR			10
#define CYAN_COLOR			11
#define RED_COLOR			12
#define PINK_COLOR			13
#define YELLOW_COLOR		14
#define WHITE_COLOR			15

#define KEY_UP		1072
#define KEY_DOWN	1080
#define KEY_LEFT	1075
#define KEY_RIGHT	1077
#define KEY_NONE	-1

// Lay nút bàn phím do nguoi dùng bam
// Tro ve: Mã cua phím
int inputKey();

// Xóa màn hình
void clrscr();

// Di chuyen con tro console den vi trí có toa do (x, y)
void gotoXY (int x, int y);

// Lay toa do x hien tai cua con tro console
int whereX();

// Lay toa do y hien tai cua con tro console
int whereY();

// Xóa con tro nháy 
void noCursorType();

// Ðoi màu chu
// Tham so: Mã màu
void setTextColor (int color);
//end----------------------Screen----------------------end
// Lay nút bàn phím do nguoi dùng bam
// Tro ve: Mã cua phím
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}

// Xóa màn hình
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

// Di chuyen con tro console den vi trí có toa do (x, y)
void gotoXY (int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Lay toa do x hien tai cua con tro console
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

// Lay toa do y hien tai cua con tro console
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
