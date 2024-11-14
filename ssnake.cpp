#include <iostream>  

#include <fstream>   

#include <windows.h>

#include <conio.h>     

#include <ctime>     

 

// Các hang se dùng trong chuong trình

#define MAX 100          // So luong toi da các doan cua ran 

#define LEN 1            // Huong di chuyen lên

#define XUONG 2          // Huong di chuyen xuong

#define TRAI 3           // Huong di chuyen trái

#define PHAI 4           // Huong di chuyen phai

#define TUONG_TREN 1     // Toa do tuong trên

#define TUONG_DUOI 20    // Toa do tuong duoi

#define TUONG_TRAI 3     // Toa do tuong trái

#define TUONG_PHAI 50    // Toa do tuong phai

#define DE 0             // Muc do de

#define TRUNG_BINH 1     // Muc do trung bình

#define KHO 2            // Muc do khó

#define BLACK_COLOR                                   0

#define DARK_BLUE_COLOR                         1

#define DARK_GREEN_COLOR        2

#define DARK_CYAN_COLOR                        3

#define DARK_RED_COLOR              4

#define DARK_PINK_COLOR                          5

#define DARK_YELLOW_COLOR     6

#define DARK_WHITE_COLOR         7

#define GREY_COLOR                                     8

#define BLUE_COLOR                                      9

#define GREEN_COLOR                                  10

#define CYAN_COLOR                                     11

#define RED_COLOR                           12

#define PINK_COLOR                                       13

#define YELLOW_COLOR                  14

#define WHITE_COLOR                                   15

 

#define KEY_UP                       1072

#define KEY_DOWN  1080

#define KEY_LEFT      1075

#define KEY_RIGHT   1077

#define KEY_NONE   -1

 

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

             CONSOLE_SCREEN_BUFFER_INFO             csbiInfo;                  

             HANDLE          hConsoleOut;

             COORD           Home = {0,0};

             DWORD          dummy;

 

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

    int x;       // Toa do x

    int y;       // Toa do y

    int huong;   // Huong di chuyen

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

int sodot;              // So luong doan cua ran

int x = 0, y = 0;       // Toa do x, y khoi tao

int huong = PHAI;       // Huong di chuyen khoi tao cua ran

int diem;               // Ðiem so hien tai

int tocdo;              // Toc do di chuyen cua ran

Toado ran[MAX];         // Mang luu các doan cua ran

Toado dotcuoicu;        // Toa do dot cuoi cùng cua ran

Toado moi;              // Toa do moi

Toado vatcan1;          // Toa do vat can 1

Toado vatcan2;          // Toa do vat can 2

 

// Hàm dieu khien logic chính cua trò choi

void logic(int mode) {

    clrscr();  // Xóa màn hình

    moi = taomoi(ran);  // Tao moi moi

    taokhoi(ran);  // Tao khoi dau cho ran

    vekhung();  // Ve khung trò choi

    gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);

    cout << "DIEM:" << diem;  // Hien the diem

 

    if (mode == KHO) {

        taovatcan(vatcan1);  // Tao vat can 1

        taovatcan(vatcan2);  // Tao vat can 2

    }

 

    while (1) {

        hienkhoi(ran, dotcuoicu);  // Hien the ran trên màn hình

        if (ktraanmoi(moi) == TRUE) {  // Kiem tra neu ran an moi

            diem++;  // Tang diem

            gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);

            cout << "DIEM:" << diem;  // Cap nhat diem trên màn hình

            sodot++;  // Tang so doan cua ran

            moi = taomoi(ran);  // Tao moi moi

        }

        dieukhien(huong);  // Ðieu khien huong di chuyen cua ran

        dotcuoicu = dichuyen(ran, huong);  // Di chuyen ran

        if (mode == KHO) {

            xoavatcan(vatcan1);  // Xóa vat can 1

            doivatcan(vatcan1);  // Ðoi huong vat can 1 neu can

            dcvatcan(vatcan1);  // Di chuyen vat can 1

            taovatcan(vatcan1);  // Ve lai vat can 1

            xoavatcan(vatcan2);  // Xóa vat can 2

            doivatcan(vatcan2);  // Ðoi huong vat can 2 neu can

            dcvatcan(vatcan2);  // Di chuyen vat can 2

            taovatcan(vatcan2);  // Ve lai vat can 2

            if (damvatcan(ran, vatcan1) == TRUE || damvatcan(ran, vatcan2) == TRUE) {

                break;  // Ket thúc trò choi neu ran dâm vào vat can

            }

        }

        if (damcot(ran) == TRUE) {  // Kiem tra neu ran dâm vào tuong

            if (mode == DE) {

                dichchuyen(ran);  // Di chuyen ran theo huong nguoc lai

            } else if (mode == TRUNG_BINH) {

                break;  // Ket thúc trò choi neu ran dâm vào tuong

            } else if (mode == KHO) {

                break;  // Ket thúc trò choi neu ran dâm vào tuong

            }

        }

        if (damdot(ran) == TRUE) break;  // Ket thúc trò choi neu ran dâm vào thân mình

        Sleep(tocdo);  // Ngu trong mot khoang thoi gian de dieu chinh toc do

        noCursorType();  // in con tro

    }

}

 

// Hàm khoi tao các giá tri ban dau

void khoitao() {

    vatcan1 = {TUONG_TRAI + 15, TUONG_TREN + 1, XUONG};  // Toa do và huong di chuyen cua vat can 1

    vatcan2 = {TUONG_PHAI - 15, TUONG_DUOI - 1, LEN};    // Toa do và huong di chuyen cua vat can 2

    sodot = 4;  // So doan ban dau cua ran

    diem = 0;   // Ðiem khoi tao

    huong = PHAI;  // Huong di chuyen khoi tao

}

 

// Hàm tao khoi dau cho ran

void taokhoi(Toado ran[]) {

    ran[0].x = TUONG_TRAI + 4;

    ran[1].x = TUONG_TRAI + 3;

    ran[2].x = TUONG_TRAI + 2;

    ran[3].x = TUONG_TRAI + 1;

    ran[0].y = ran[1].y = ran[2].y = ran[3].y = TUONG_TREN + 1;

}

 

// Hàm hien thi ran trên màn hình

void hienkhoi(Toado ran[], Toado dotcuoicu) {

    for (int i = 0; i < sodot; i++) {

        setTextColor(GREEN_COLOR);

        gotoXY(ran[i].x, ran[i].y);

        cout << (char)254;

    }

    gotoXY(dotcuoicu.x, dotcuoicu.y);

    cout << " ";

}

 

// Hàm di chuyen ran theo huong hien tai

Toado dichuyen(Toado ran[], int &huong) {

    Toado dotcuoicu = ran[sodot - 1];

    for (int i = sodot - 1; i > 0; i--) {

        ran[i].x = ran[i - 1].x;

        ran[i].y = ran[i - 1].y;

    }

    switch (huong) {

    case LEN:

        ran[0].y--;

        break;

    case XUONG:

        ran[0].y++;

        break;

    case TRAI:

        ran[0].x--;

        break;

    case PHAI:

        ran[0].x++;

        break;

    default:

        break;

    }

    return dotcuoicu;

}

 

// Hàm di chuyen ran theo huong nguoc lai neu dâm vào tuong (che do de)

void dichchuyen(Toado ran[]) {

    if (ran[0].x == TUONG_TRAI) {

        ran[0].x = TUONG_PHAI - 1;

    } else if (ran[0].x == TUONG_PHAI) {

        ran[0].x = TUONG_TRAI + 1;

    } else if (ran[0].y == TUONG_TREN) {

        ran[0].y = TUONG_DUOI - 1;

    } else if (ran[0].y == TUONG_DUOI) {

        ran[0].y = TUONG_TREN + 1;

    }

}

 

// Hàm dieu khien huong di chuyen cua ran

void dieukhien(int &huong) {

    int key = inputKey();

    if ((key == 'w') && (huong != XUONG)) {

        huong = LEN;

    } else if ((key == 's') && (huong != LEN)) {

        huong = XUONG;

    } else if ((key == 'a') && (huong != PHAI)) {

        huong = TRAI;

    } else if ((key == 'd') && (huong != TRAI)) {

        huong = PHAI;

    }

}

 

// Hàm ve khung trò choi

void vekhung() {

    setTextColor(BLUE_COLOR);

    for (int i = TUONG_TRAI; i <= TUONG_PHAI; i++) {

        gotoXY(i, TUONG_TREN);

        cout << (char)220;

        gotoXY(i, TUONG_DUOI);

        cout << (char)223;

    }

    for (int j = TUONG_TREN + 1; j <= TUONG_DUOI - 1; j++) {

        gotoXY(TUONG_TRAI, j);

        cout << (char)221;

        gotoXY(TUONG_PHAI, j);

        cout << (char)222;

    }

}

 

// Hàm kiem tra neu ran dâm vào tuong

bool damcot(Toado ran[]) {

    if ((ran[0].y == TUONG_TREN) || (ran[0].y == TUONG_DUOI) || (ran[0].x == TUONG_TRAI) || (ran[0].x == TUONG_PHAI)) {

        return TRUE;

    }

    return FALSE;

}

 

// Hàm xu lý khi trò choi ket thúc

void xulythua() {

    if (hiendiem(diem) < diem) {

        luudiem(diem);

    }

    Sleep(200);

    clrscr();

    setTextColor(RED_COLOR);

    gotoXY(10, 6);

    cout << "Game over" << endl;

    gotoXY(10, 7);

    cout << "Diem cua ban la: " << diem << endl;

    gotoXY(10, 8);

    cout << "Nhan 'e' de thoat.";

    while (inputKey() != 'e') {}

}

 

// Hàm tao moi moi cho ran

Toado taomoi(Toado ran[]) {

    setTextColor(RED_COLOR);

    srand(time(NULL));

    int x, y;

    while (1) {

        x = rand() % (TUONG_PHAI - 1 - TUONG_TRAI - 1) + (TUONG_TRAI + 1);

        y = rand() % (TUONG_DUOI - 1 - TUONG_TREN - 1) + (TUONG_TREN + 1);

        bool check = false;

        for (int i = 0; i < sodot; i++) {

            if ((x == ran[i].x) && (y == ran[i].y)) {

                check = true;

                break;

            }

        }

        if (check == false) break;

    }

    gotoXY(x, y);

    cout << "@";

    return {x, y};

}

 

// Hàm kiem tra neu ran an moi

bool ktraanmoi(Toado moi) {

    if ((ran[0].x == moi.x) && (ran[0].y == moi.y) || vatcan1.x == moi.x || vatcan2.x == moi.x) {

        return TRUE;

    } else return FALSE;

}

 

// Hàm kiem tra neu ran dâm vào thân mình

bool damdot(Toado ran[]) {

    for (int i = 1; i < sodot; i++) {

        if ((ran[0].x == ran[i].x) && (ran[0].y == ran[i].y)) {

            return TRUE;

        }

    }

    return FALSE;

}

 

// Hàm doi huong di chuyen cua vat can

void doivatcan(Toado &vatcan) {

    if (vatcan.y == TUONG_TREN + 1) {

        vatcan.huong = XUONG;

    } else if (vatcan.y == TUONG_DUOI - 1) {

        vatcan.huong = LEN;

    }

}

 

// Hàm xóa vat can khoi màn hình

void xoavatcan(Toado &vatcan) {

    gotoXY(vatcan.x, vatcan.y);

    cout << " ";

}

 

// Hàm ve vat can lên màn hình

void taovatcan(Toado &vatcan) {

    setTextColor(RED_COLOR);

    gotoXY(vatcan.x, vatcan.y);

    cout << "$";

}

 

// Hàm di chuyen vat can theo huong hien tai

void dcvatcan(Toado &vatcan) {

    if (vatcan.huong == XUONG) {

        vatcan.y++;

    } else if (vatcan.huong == LEN) {

        vatcan.y--;

    }

}

 

// Hàm kiem tra neu ran dâm vào vat can

bool damvatcan(Toado ran[], Toado vatcan) {

    for (int i = 0; i < sodot; i++) {

        if ((ran[i].x == vatcan.x) && (ran[i].y == vatcan.y)) {

            return TRUE;

        }

    }

    return FALSE;

}

 

// Hàm chon do khó cua trò choi

void chondokho() {

    int choice = 0;

    clrscr();

    while (1) {

        setTextColor(GREEN_COLOR);

        khoitao();

        gotoXY(10, 5);

        cout << "-----Chedochoi------";

        gotoXY(10, 6);

        cout << (choice == 0 ? "> " : "  ") << "1. De"; 

        gotoXY(10, 7);

        cout << (choice == 1 ? "> " : "  ") << "2. Binh Thuong";

        gotoXY(10, 8);

        cout << (choice == 2 ? "> " : "  ") << "3. Kho";

        noCursorType();

        int key = inputKey();

        if ((key == 's') && (choice != 2)) {

            choice += 1;

        } else if ((key == 'w') && (choice != 0)) {

            choice -= 1;

        } else if (key == '\r') {

            if (choice == 0) {

                clrscr();

                tocdo = 200;

                logic(DE);

                break;

            } else if (choice == 1) {

                clrscr();

                tocdo = 100;

                logic(TRUNG_BINH);

                break;

            } else if (choice == 2) {

                clrscr();

                tocdo = 95;

                logic(KHO);

                break;

            }

        }

    }

}

 

// Hàm luu diem vào file

void luudiem(int diem) {

    ofstream os("diem.txt");

    os << diem;

    os.close();

}

 

// Hàm hien thi diem cao nhat tu file

int hiendiem(int diem) {

    ifstream is;

    is.open("diem.txt");

    is >> diem;

    is.close();

    return diem;

}

 

// Hàm menu chính cua trò choi

void menu() {

    int choice = 0;

    clrscr();

    while (1) {

        setTextColor(GREEN_COLOR);

        khoitao();

        gotoXY(10, 5);

        cout << "------Menu------";

        gotoXY(10, 6);

        cout << (choice == 0 ? "> " : "  ") << "1. Choi"; 

        gotoXY(10, 7);

        cout << (choice == 1 ? "> " : "  ") << "2. Thoat";

        gotoXY(10, 8);

        cout << (choice == 2 ? "> " : "  ") << "3. Huong Dan";

        gotoXY(10, 9);

        cout << (choice == 3 ? "> " : "  ") << "4. Xem Diem";

        noCursorType();

        int key = inputKey();

        if ((key == 's') && (choice != 3)) {

            choice += 1;

        } else if ((key == 'w') && (choice != 0)) {

            choice -= 1;

        } else if (key == '\r') {
