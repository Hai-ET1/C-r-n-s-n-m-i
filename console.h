if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

// Xóa con tro nháy
void noCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Ðoi màu chu
// Tham s?: Mã màu
void setTextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
using namespace std;     

// Ðinh nghia cau trúc toa do cho ran, moi và vat can
struct Toado {
    int x;       // Toa do x
    int y;       // Toa do y
    int huong;   // Huong di chuyen
};

// Khai báo các hàm su dung trong chuong trình
void taokhoi(Toado ran[]);
void hienkhoi(Toado ran[], Toado dotcuoicu);
Toado dichuyen(Toado ran[], int &huong);
void dieukhien(int &huong);
void vekhung();
bool damcot(Toado ran[]);
void xulythua();
Toado taomoi(Toado ran[]);
bool ktraanmoi(Toado moi);
bool damdot(Toado ran[]);
void khoitao();
void logic(int mode);
void menu();
void chondokho();
void dichchuyen(Toado ran[]);
void xoavatcan(Toado &vatcan);
void taovatcan(Toado &vatcan);
void dcvatcan(Toado &vatcan);
void doivatcan(Toado &vatcan);
bool damvatcan(Toado ran[], Toado vatcan);
int hiendiem(int diem);
void luudiem(int diem);

// Khai báo các bien toàn cuc
int sodot;              // So luong doan cua ran
int x = 0, y = 0;       // Toa do x, y khoi tao
int huong = PHAI;       // Huong di chuyen khoi tao cua ran
int diem;               // Ðiem so hien tai
int tocdo;              // Toc do di chuyen cua ran
Toado ran[MAX];         // Mang luu các doan cua ran
Toado dotcuoicu;        // Toa do dot cuoi cùng cua ran
Toado moi;              // Toa do moi
Toado vatcan1;          // Toa do vat can 1
Toado vatcan2;          // Toa do vat can 2

// Hàm dieu khien logic chính cua trò choi
void logic(int mode) {
    clrscr();  // Xóa màn hình
    moi = taomoi(ran);  // Tao moi moi
    taokhoi(ran);  // Tao khoi dau cho ran
    vekhung();  // Ve khung trò choi
    gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);
    cout << "DIEM:" << diem;  // Hien the diem

    if (mode == KHO) {
        taovatcan(vatcan1);  // Tao vat can 1
        taovatcan(vatcan2);  // Tao vat can 2
    }

    while (1) {
        hienkhoi(ran, dotcuoicu);  // Hien the ran trên màn hình
        if (ktraanmoi(moi) == TRUE) {  // Kiem tra neu ran an moi
            diem++;  // Tang diem
            gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);
            cout << "DIEM:" << diem;  // Cap nhat diem trên màn hình
            sodot++;  // Tang so doan cua ran
            moi = taomoi(ran);  // Tao moi moi
        }
        dieukhien(huong);  // Ðieu khien huong di chuyen cua ran
        dotcuoicu = dichuyen(ran, huong);  // Di chuyen ran
        if (mode == KHO) {
            xoavatcan(vatcan1);  // Xóa vat can 1
            doivatcan(vatcan1);  // Ðoi huong vat can 1 neu can
            dcvatcan(vatcan1);  // Di chuyen vat can 1
