#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <random>
#define LEFT 300
#define SPEED 35
std::random_device rd;
std::uniform_int_distribution<int> uid(0, 500);
std::uniform_int_distribution<int> size_uid(100, 300);
class Rect {
public:
	int x1 = uid(rd), y1 = uid(rd);
	int size_x = size_uid(rd);
	int size_y = size_uid(rd);
	
};

void gotoxy(int x, int y);
BOOL MyIntersectRect(Rect rect1, Rect rect2);
int main() {
	Rect rect1, rect2;
	HWND hWnd = GetForegroundWindow();
	HDC hdc = GetDC(hWnd);

	HPEN hPen_R,hPen_B, hPen_W, oldPen;
	hPen_R = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hPen_B = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPen_W = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(12,12,12));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	BOOL check_1p=false, check_2p = false, colide = false;
	while (1) {
		system("cls");
		gotoxy(0, 0);
		printf("1P - WASD / 2P - 방향키");
		gotoxy(0, 2);
		std::cout << "1P - (" << rect1.x1 << ", " << rect1.y1 << ")  (" << rect1.x1+rect1.size_x << ", " << rect1.y1+rect1.size_y << ")" << std::endl;
		std::cout << "2P - (" << rect2.x1 << ", " << rect2.y1 << ")  (" << rect2.x1+ rect2.size_x << ", " << rect2.y1+rect2.size_y << ")" << std::endl;
		{//그림그리기
			oldPen = (HPEN)SelectObject(hdc, hPen_W);
			Rectangle(hdc, LEFT+ 0,0,LEFT+800,800);
			SelectObject(hdc, oldPen);


			oldPen = (HPEN)SelectObject(hdc, hPen_R);
			Rectangle(hdc, LEFT+rect1.x1, rect1.y1, LEFT + rect1.x1+rect1.size_x,rect1.y1+rect1.size_y);
			SelectObject(hdc, oldPen);

			oldPen = (HPEN)SelectObject(hdc, hPen_B);
			Rectangle(hdc, LEFT + rect2.x1, rect2.y1, LEFT + rect2.x1+rect2.size_x, rect2.y1+rect2.size_y);
			SelectObject(hdc, oldPen);
		}
		if (check_1p) {
			gotoxy(0, 10);
			printf("1P 범위 넘어감!!");
			//system("pause");
			check_1p = false;
		}
		if (check_2p) {
			gotoxy(0, 11);
			printf("2P 범위 넘어감!!");
			check_2p = false;
		}
		if (colide) {
			gotoxy(0, 12);
			printf("둘이 충돌함!!");
			colide = false;
		}
		switch (_getch()) {
		case 'W':
		case 'w':
			rect1.y1 -= SPEED;
			if (rect1.y1 < 0) {
				rect1.y1 = 0;
				check_1p = true;
			}
			break;
		case 'A':
		case 'a':
			rect1.x1 -= SPEED;
			if (rect1.x1 < 0) {
				rect1.x1 = 0;
				check_1p = true;
			}
			break;
		case 'S':
		case 's':
			rect1.y1 += SPEED;
			if (rect1.y1+rect1.size_y > 800) {
				rect1.y1 = 800-rect1.size_y;
				check_1p=true;
			}
			break;
		case 'D':
		case 'd':
			rect1.x1 += SPEED;
			if (rect1.x1+rect1.size_x > 800) {
				rect1.x1 = 800 - rect1.size_x;
				check_1p=true;
			}
			break;
		case 72:		//위
			rect2.y1 -= SPEED;
			if (rect2.y1 < 0) {
				rect2.y1 = 0;
				check_2p = true;
			}
			break;
		
			break;
		case 80:		//아래
			rect2.y1 += SPEED;
			if (rect2.y1 + rect2.size_y > 800) {
				rect2.y1 = 800 - rect2.size_y;
				check_2p = true;
			}
			break;
		case 75:		//왼쪽
			rect2.x1 -= SPEED;
			if (rect2.x1 < 0) {
				rect2.x1 = 0;
				check_2p = true;
			}
			break;
		case 77:		//오른쪽
			rect2.x1 += SPEED;
			if (rect2.x1 + rect2.size_x > 800) {
				rect2.x1 = 800 - rect2.size_x;
				check_2p = true;
			}
			break;
		
		}

		colide = MyIntersectRect(rect1, rect2);
	}







	
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
	
	DeleteObject(hPen_R);
	ReleaseDC(hWnd, hdc);


}

void gotoxy(int x, int y){
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

BOOL MyIntersectRect(Rect rect1, Rect rect2) {
	BOOL vertical_colide = false;
	BOOL horizon_colide = false;

	if (rect1.x1<rect2.x1 + rect2.size_x && rect1.x1 + rect1.size_x>rect2.x1) horizon_colide = true;
	if (rect1.y1<rect2.y1 + rect2.size_y && rect1.y1 + rect1.size_y>rect2.y1) vertical_colide = true;

	if (horizon_colide && vertical_colide) return true;
	else return false;
}