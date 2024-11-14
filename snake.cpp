taovatcan(vatcan1);  // Ve lai vat can 1
            xoavatcan(vatcan2);  // Xóa vat can 2
            doivatcan(vatcan2);  // Ðoi huong vat can 2 neu can
            dcvatcan(vatcan2);  // Di chuyen vat can 2
            taovatcan(vatcan2);  // Ve lai vat can 2
            if (damvatcan(ran, vatcan1) == TRUE || damvatcan(ran, vatcan2) == TRUE) {
                break;  // Ket thúc trò choi neu ran dâm vào vat can
            }
        }
        if (damcot(ran) == TRUE) {  // Kiem tra neu ran dâm vào tuong
            if (mode == DE) {
                dichchuyen(ran);  // Di chuyen ran theo huong nguoc lai
            } else if (mode == TRUNG_BINH) {
                break;  // Ket thúc trò choi neu ran dâm vào tuong
            } else if (mode == KHO) {
                break;  // Ket thúc trò choi neu ran dâm vào tuong
            }
        }
        if (damdot(ran) == TRUE) break;  // Ket thúc trò choi neu ran dâm vào thân mình
        Sleep(tocdo);  // Ngu trong mot khoang thoi gian de dieu chinh toc do
        noCursorType();  // in con tro
    }
}

// Hàm khoi tao các giá tri ban dau
void khoitao() {
    vatcan1 = {TUONG_TRAI + 15, TUONG_TREN + 1, XUONG};  // Toa do và huong di chuyen cua vat can 1
    vatcan2 = {TUONG_PHAI - 15, TUONG_DUOI - 1, LEN};    // Toa do và huong di chuyen cua vat can 2
    sodot = 4;  // So doan ban dau cua ran
    diem = 0;   // Ðiem khoi tao
    huong = PHAI;  // Huong di chuyen khoi tao
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
