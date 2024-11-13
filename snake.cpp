#include <iostream>  
#include <fstream>   
#include "console.h" 
#include "bpp.h"     
#include <ctime>     

// Các hằng số dùng trong chương trình
#define MAX 100          // Số lượng tối đa các đoạn của rắn
#define LEN 1            // Hướng di chuyển lên
#define XUONG 2          // Hướng di chuyển xuống
#define TRAI 3           // Hướng di chuyển trái
#define PHAI 4           // Hướng di chuyển phải
#define TUONG_TREN 1     // Tọa độ tường trên
#define TUONG_DUOI 20    // Tọa độ tường dưới
#define TUONG_TRAI 3     // Tọa độ tường trái
#define TUONG_PHAI 50    // Tọa độ tường phải
#define DE 0             // Mức độ dễ
#define TRUNG_BINH 1     // Mức độ trung bình
#define KHO 2            // Mức độ khó

using namespace std;     

// Định nghĩa cấu trúc tọa độ cho rắn, mồi và vật cản
struct Toado {
    int x;       // Tọa độ x
    int y;       // Tọa độ y
    int huong;   // Hướng di chuyển
};

// Khai báo các hàm sử dụng trong chương trình
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

// Khai báo các biến toàn cục
int sodot;              // Số lượng đoạn của rắn
int x = 0, y = 0;       // Tọa độ x, y khởi tạo
int huong = PHAI;       // Hướng di chuyển khởi tạo của rắn
int diem;               // Điểm số hiện tại
int tocdo;              // Tốc độ di chuyển của rắn
Toado ran[MAX];         // Mảng lưu các đoạn của rắn
Toado dotcuoicu;        // Tọa độ đốt cuối cùng của rắn
Toado moi;              // Tọa độ mồi
Toado vatcan1;          // Tọa độ vật cản 1
Toado vatcan2;          // Tọa độ vật cản 2

// Hàm điều khiển logic chính của trò chơi
void logic(int mode) {
    clrscr();  // Xóa màn hình
    moi = taomoi(ran);  // Tạo mồi mới
    taokhoi(ran);  // Tạo khởi đầu cho rắn
    vekhung();  // Vẽ khung trò chơi
    gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);
    cout << "DIEM:" << diem;  // Hiển thị điểm

    if (mode == KHO) {
        taovatcan(vatcan1);  // Tạo vật cản 1
        taovatcan(vatcan2);  // Tạo vật cản 2
    }

    while (1) {
        hienkhoi(ran, dotcuoicu);  // Hiển thị rắn trên màn hình
        if (ktraanmoi(moi) == TRUE) {  // Kiểm tra nếu rắn ăn mồi
            diem++;  // Tăng điểm
            gotoXY(TUONG_TRAI + 1, TUONG_TREN - 1);
            cout << "DIEM:" << diem;  // Cập nhật điểm trên màn hình
            sodot++;  // Tăng số đoạn của rắn
            moi = taomoi(ran);  // Tạo mồi mới
        }
        dieukhien(huong);  // Điều khiển hướng di chuyển của rắn
        dotcuoicu = dichuyen(ran, huong);  // Di chuyển rắn
        if (mode == KHO) {
            xoavatcan(vatcan1);  // Xóa vật cản 1
            doivatcan(vatcan1);  // Đổi hướng vật cản 1 nếu cần
            dcvatcan(vatcan1);  // Di chuyển vật cản 1
            taovatcan(vatcan1);  // Vẽ lại vật cản 1
            xoavatcan(vatcan2);  // Xóa vật cản 2
            doivatcan(vatcan2);  // Đổi hướng vật cản 2 nếu cần
            dcvatcan(vatcan2);  // Di chuyển vật cản 2
            taovatcan(vatcan2);  // Vẽ lại vật cản 2
            if (damvatcan(ran, vatcan1) == TRUE || damvatcan(ran, vatcan2) == TRUE) {
                break;  // Kết thúc trò chơi nếu rắn đâm vào vật cản
            }
        }
        if (damcot(ran) == TRUE) {  // Kiểm tra nếu rắn đâm vào tường
            if (mode == DE) {
                dichchuyen(ran);  // Di chuyển rắn theo hướng ngược lại
            } else if (mode == TRUNG_BINH) {
                break;  // Kết thúc trò chơi nếu rắn đâm vào tường
            } else if (mode == KHO) {
                break;  // Kết thúc trò chơi nếu rắn đâm vào tường
            }
        }
        if (damdot(ran) == TRUE) break;  // Kết thúc trò chơi nếu rắn đâm vào thân mình
        Sleep(tocdo);  // Ngủ trong một khoảng thời gian để điều chỉnh tốc độ
        noCursorType();  // Ẩn con trỏ
    }
}

// Hàm khởi tạo các giá trị ban đầu
void khoitao() {
    vatcan1 = {TUONG_TRAI + 15, TUONG_TREN + 1, XUONG};  // Tọa độ và hướng di chuyển của vật cản 1
    vatcan2 = {TUONG_PHAI - 15, TUONG_DUOI - 1, LEN};    // Tọa độ và hướng di chuyển của vật cản 2
    sodot = 4;  // Số đoạn ban đầu của rắn
    diem = 0;   // Điểm khởi tạo
    huong = PHAI;  // Hướng di chuyển khởi tạo
}

// Hàm tạo khởi đầu cho rắn
void taokhoi(Toado ran[]) {
    ran[0].x = TUONG_TRAI + 4;
    ran[1].x = TUONG_TRAI + 3;
    ran[2].x = TUONG_TRAI + 2;
    ran[3].x = TUONG_TRAI + 1;
    ran[0].y = ran[1].y = ran[2].y = ran[3].y = TUONG_TREN + 1;
}

// Hàm hiển thị rắn trên màn hình
void hienkhoi(Toado ran[], Toado dotcuoicu) {
    for (int i = 0; i < sodot; i++) {
        setTextColor(GREEN_COLOR);
        gotoXY(ran[i].x, ran[i].y);
        cout << (char)254;
    }
    gotoXY(dotcuoicu.x, dotcuoicu.y);
    cout << " ";
}

// Hàm di chuyển rắn theo hướng hiện tại
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

// Hàm di chuyển rắn theo hướng ngược lại nếu đâm vào tường (chế độ dễ)
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

// Hàm điều khiển hướng di chuyển của rắn
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

// Hàm vẽ khung trò chơi
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

// Hàm kiểm tra nếu rắn đâm vào tường
bool damcot(Toado ran[]) {
    if ((ran[0].y == TUONG_TREN) || (ran[0].y == TUONG_DUOI) || (ran[0].x == TUONG_TRAI) || (ran[0].x == TUONG_PHAI)) {
        return TRUE;
    }
    return FALSE;
}

// Hàm xử lý khi trò chơi kết thúc
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

// Hàm tạo mồi mới cho rắn
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

// Hàm kiểm tra nếu rắn ăn mồi
bool ktraanmoi(Toado moi) {
    if ((ran[0].x == moi.x) && (ran[0].y == moi.y) || vatcan1.x == moi.x || vatcan2.x == moi.x) {
        return TRUE;
    } else return FALSE;
}

// Hàm kiểm tra nếu rắn đâm vào thân mình
bool damdot(Toado ran[]) {
    for (int i = 1; i < sodot; i++) {
        if ((ran[0].x == ran[i].x) && (ran[0].y == ran[i].y)) {
            return TRUE;
        }
    }
    return FALSE;
}

// Hàm đổi hướng di chuyển của vật cản
void doivatcan(Toado &vatcan) {
    if (vatcan.y == TUONG_TREN + 1) {
        vatcan.huong = XUONG;
    } else if (vatcan.y == TUONG_DUOI - 1) {
        vatcan.huong = LEN;
    }
}

// Hàm xóa vật cản khỏi màn hình
void xoavatcan(Toado &vatcan) {
    gotoXY(vatcan.x, vatcan.y);
    cout << " ";
}

// Hàm vẽ vật cản lên màn hình
void taovatcan(Toado &vatcan) {
    setTextColor(RED_COLOR);
    gotoXY(vatcan.x, vatcan.y);
    cout << "$";
}

// Hàm di chuyển vật cản theo hướng hiện tại
void dcvatcan(Toado &vatcan) {
    if (vatcan.huong == XUONG) {
        vatcan.y++;
    } else if (vatcan.huong == LEN) {
        vatcan.y--;
    }
}

// Hàm kiểm tra nếu rắn đâm vào vật cản
bool damvatcan(Toado ran[], Toado vatcan) {
    for (int i = 0; i < sodot; i++) {
        if ((ran[i].x == vatcan.x) && (ran[i].y == vatcan.y)) {
            return TRUE;
        }
    }
    return FALSE;
}

// Hàm chọn độ khó của trò chơi
void chondokho() {
    int choice = 0;
    clrscr();
    while (1) {
        setTextColor(GREEN_COLOR);
        khoitao();
        gotoXY(10, 5);
        cout << "-----Chonchedo------";
        gotoXY(10, 6);
        cout << (choice == 0 ? "> " : "  ") << "1. De"; 
        gotoXY(10, 7);
        cout << (choice == 1 ? "> " : "  ") << "2. Binh Thuong";
        gotoXY(10, 8);
        cout << (choice == 2 ? "> " : "  ") << "3. Kho";
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

// Hàm lưu điểm vào file
void luudiem(int diem) {
    ofstream os("diem.txt");
    os << diem;
    os.close();
}

// Hàm hiển thị điểm cao nhất từ file
int hiendiem(int diem) {
    ifstream is;
    is.open("diem.txt");
    is >> diem;
    is.close();
    return diem;
}

// Hàm menu chính của trò chơi
void menu() {
    int choice = 0;
    clrscr();
    while (1) {
        setTextColor(GREEN_COLOR);
        khoitao();
        gotoXY(10, 5);
        cout << "------Menu------";
        gotoXY(10, 6);
        cout << (choice == 0 ? "> " : "  ") << "1. Choi"; 
        gotoXY(10, 7);
        cout << (choice == 1 ? "> " : "  ") << "2. Thoat";
        gotoXY(10, 8);
        cout << (choice == 2 ? "> " : "  ") << "3. Huong Dan";
        gotoXY(10, 9);
        cout << (choice == 3 ? "> " : "  ") << "4. Xem Diem";
        noCursorType();
        int key = inputKey();
        if ((key == 's') && (choice != 3)) {
            choice += 1;
        } else if ((key == 'w') && (choice != 0)) {
            choice -= 1;
        } else if (key == '\r') {
            if (choice == 0) {
                chondokho();
                xulythua();
                clrscr();
            } else if (choice == 1) {
                clrscr();
                break;
            } else if (choice == 2) {
                Sleep(200);
                clrscr();
                gotoXY(10, 6);
                cout << "Nhan a,s,w,d de di chuyen ran" << endl;
                gotoXY(10, 7);
                cout << "An moi se duoc cong diem" << endl;
                gotoXY(10, 8);
                cout << "Neu dam trung cot, than ran hoac vat can se ket thuc game" << endl;
                gotoXY(10, 9);
                cout << "Nhan e de thoat.";
                while (inputKey() != 'e') {}
                clrscr();
            } else if (choice == 3) {
                clrscr();
                gotoXY(10, 7);
                cout << "Diem cao nhat cua ban la: " << hiendiem(diem);
                gotoXY(10, 8);
                cout << "Nhan e de thoat.";
                while (inputKey() != 'e') {}
                clrscr();
            }
        }
        Sleep(100);
    }
}

// Hàm chính của chương trình
int main() {
    menu();
    return 0;
}



  
