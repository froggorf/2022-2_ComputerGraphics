#include<Windows.h>
#include <conio.h>
#include <iostream>
#include <cmath>
void gotoxy(int x, int y);
class myVertex {
public:
	int x = 0, y = 0, z = 0;
	BOOL is_valid = false;
	double length = 0;
	static int count;

	void AddFromHead(int xx, int yy, int zz) {
		if (count == 10) {
			gotoxy(0, 24);
			printf("에러! - 최대 저장치인 10개까지 저장 완료 하였습니다. 삭제 후 입력해주세요.\n");
			system("pause");
		}
		x = xx, y = yy, z = zz;
		is_valid = true;
		length = sqrt(x * x + y * y + z * z);
		++count;
	}
	void AddFromTail(int xx, int yy, int zz);
	void DelFromTail();
	void InitmyVertex() {
		x = 0; y = 0; z = 0;
		is_valid = false;
		length = 0;
		--count;
	}
	myVertex operator=(myVertex other) {
		x = other.x;
		y = other.y;
		z = other.z;
		is_valid = other.is_valid;
		length = other.length;
		return *this;
	}
};
int myVertex::count = 0;

void DrawListFrame(int x, int y, myVertex v[10]);
void PrintMenual(int x, int y);
void PrintMyVertex(myVertex v[10]);

int main() {
	myVertex v[10];
	while (1) {
		system("cls");
		DrawListFrame(0, 0, v);
		PrintMyVertex(v);
		PrintMenual(35, 0);
		gotoxy(0, 23);
		printf("                                                                       ");
		gotoxy(0, 23);
		printf("명령어 입력: ");
		char c;
		int x, y, z;
		std::cin >> c;
		switch (c) {
		case '+':
			if (v[0].count == 10) {
				BOOL checkEmpty = false;
				for (int i = 9; i >-1; --i) {
					if (!v[i].is_valid) {
						if (std::cin >> x) {
							if (std::cin >> y) {
								if (std::cin >> z) {
									v[i].x = x;
									v[i].y = y;
									v[i].z = z;
									v[i].length= sqrt(x * x + y * y + z * z);
									v[i].is_valid = true;
									checkEmpty = true;
								}
							}
						}
					}
					if (checkEmpty)break;
				}
				if (checkEmpty) break;
				printf("에러! - 최대 저장치인 10개까지 저장 완료 하였습니다. 삭제 후 입력해주세요.\n");
				system("pause");
				break;
			}
			if (std::cin >> x) {
				if (std::cin >> y) {
					if (std::cin >> z) {
						v[v[0].count].AddFromHead(x, y, z);
					}
				}
			}
			break;
		case '-':
			if (v[0].count == 0) {
				gotoxy(0, 24);
				printf("에러! - 데이터가 한개도 안 담겨있어 삭제를 진행할 수 없습니다. 추가 후 입력해주세요");

				system("pause");
				gotoxy(0, 24);
				printf("                                                                                      ");
				break;
			}
			v[v[0].count - 1].InitmyVertex();
			break;
		case 'E':
		case 'e':
			if (v[0].count == 10) {
				BOOL checkEmpty = false;
				for (int i = 0; i <v[0].count; ++i) {
					if (!v[i].is_valid) {
						if (std::cin >> x) {
							if (std::cin >> y) {
								if (std::cin >> z) {
									v[i].x = x;
									v[i].y = y;
									v[i].z = z;
									v[i].length = sqrt(x * x + y * y + z * z);
									v[i].is_valid = true;
									checkEmpty = true;
								}
							}
						}
					}
					if (checkEmpty)break;
				}
				if (checkEmpty) break;
				gotoxy(0, 24);
				printf("에러! - 최대 저장치인 10개까지 저장 완료 하였습니다. 삭제 후 입력해주세요.\n");
				system("pause");
				break;
			}
			if (std::cin >> x) {
				if (std::cin >> y) {
					if (std::cin >> z) {
						for (int i = v[0].count - 1; i >-1; --i) {
							v[i + 1] = v[i];
						}
						++v[0].count;
						v[0].x = x;
						v[0].y = y;
						v[0].z = z;
						v[0].is_valid = true;
						v[0].length = sqrt(x * x + y * y + z * z);
					}
				}
			}
			break;
		case 'D':
		case 'd':
			if (v[0].count == 0) {
				gotoxy(0, 24);
				printf("에러! - 데이터가 한개도 안 담겨있어 삭제를 진행할 수 없습니다. 추가 후 입력해주세요");
				system("pause");
				break;
			}
			for (int i = 0; i < v[0].count; ++i) {
				if (v[i].is_valid) {
					v[i].is_valid = false;
					break;
				}
			}
			break;
		case 'L':
		case 'l':
			gotoxy(0, 24);
			std::cout << "전체 갯수 : " << v[0].count;
			gotoxy(0, 25);
			{
				int num = v[0].count;
				for (int i = 0; i < v[0].count; ++i) {
					if (!v[i].is_valid) num -= 1;
				}
				std::cout << "d 로 인해 빈칸으로 리스트에 빈칸으로만 있는 데이터를 제외한 수 : " << num << std::endl;
				system("pause");
			}
			break;
		case 'C':
		case 'c':
			for (int i = v[0].count-1; i >-1; --i) {
				if (v[0].count == 0) break;
				v[i].InitmyVertex();
			}
			break;
		case 'M':
		case 'm':
		{
			double max = 0;
			int idx = -1;
			for (int i = 0; i < v[0].count; ++i) {
				if (v[i].is_valid) {
					if (v[i].length > max) {
						max = v[i].length;
						idx = i;
					}
				}
			}
			if (idx == -1 || v[0].count == 0) {
				gotoxy(0, 24);
				printf("현재 리스트가 비워져있어 ( d로인해 빈칸으로만 있는 데이터가 있어 ) 출력되는 점이 없습니다.\n");
				gotoxy(0, 25);
				system("pause");
			}
			else {
				gotoxy(0, 24);
				std::cout << "가장 먼 점: v[" << idx << "] - (" << v[idx].x << ", " << v[idx].y << ", " << v[idx].z << ") , 거리 - " << v[idx].length;
				gotoxy(0, 25);
				system("pause");
			}
		}
			break;
		case 'N':
		case 'n':
		{
			double min = 1000000;
			int idx = -1;
			for (int i = 0; i < v[0].count; ++i) {
				if (v[i].is_valid) {
					if (v[i].length < min) {
						min = v[i].length;
						idx = i;
					}
				}
			}
			if (idx == -1 || v[0].count == 0) {
				gotoxy(0, 24);
				printf("현재 리스트가 비워져있어 ( d로인해 빈칸으로만 있는 데이터가 있어 ) 출력되는 점이 없습니다.\n");
				gotoxy(0, 25);
				system("pause");
			}
			else {
				gotoxy(0, 24);
				std::cout << "가장 가까운 점: v[" << idx << "] - (" << v[idx].x << ", " << v[idx].y << ", " << v[idx].z << ") , 거리 - " << v[idx].length;
				gotoxy(0, 25);
				system("pause");
			}
		}
			break;
		case 'S':
		case 's':
			if (v[0].count == 0) {
				gotoxy(0, 24);
				printf("현재 리스트에 담겨져 있는 자료가 없어 정렬을 진행할 수 없습니다.\n");
				system("pause");
				break;
			}
			{
				myVertex tempv[10];
				double min=100000;
				int idx = -1;
				int temp_count = 0;
				int check_count = v[0].count;
				for (int i = 0; i < v[0].count; ++i) {
					if (!v[i].is_valid) check_count-= 1;
				}
				while (1) {
					if (check_count == 0)break;
					for (int i = 0; i < v[0].count; ++i) {
						if (v[i].is_valid) {
							if (v[i].length < min) {
								min = v[i].length;
								idx = i;
							}
						}

					}
					tempv[temp_count].x = v[idx].x;
					tempv[temp_count].y = v[idx].y;
					tempv[temp_count].z = v[idx].z;
					tempv[temp_count].length = sqrt(v[idx].x * v[idx].x + v[idx].y * v[idx].y + v[idx].z * v[idx].z);
					tempv[temp_count].is_valid = true;
					temp_count++;
					v[idx].is_valid = false;
					v[idx].x = 0; v[idx].y = 0; v[idx].z = 0;
					--check_count;
					min = 100000000;
					idx = -1;
				}
				for (int i = 0; i < temp_count; ++i) {
					v[i] = tempv[i];
				}
				v[0].count = temp_count;
				
			}
			
			
			break;
		case 'Q':
		case 'q':
			exit(0);
			break;
		}
	}
}
void PrintMyVertex(myVertex v[10]) {
	for (int i = 0; i < 10; ++i) {
		gotoxy(3, 3 + 2 * (9 - i));
		printf("              ");
		gotoxy(18, 3 + 2 * (9 - i));
		printf("              ");
	}
	for (int i = 0; i < v[0].count; ++i) {
		if (v[i].is_valid) {
			gotoxy(3, 3 + 2 * (9 - i));
			std::cout << v[i].x << ", " << v[i].y << ", " << v[i].z;
			gotoxy(18, 3 + 2 * (9 - i));
			std::cout << v[i].length;
		}
	}
}
void DrawListFrame(int x, int y, myVertex v[10]) {
	gotoxy(x, y);
	printf("┌─┬──────────────┬──────────────┐");
	gotoxy(x, y + 1);
	printf("│ │    vertex    │    length    │");
	gotoxy(x, y + 2);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 3);
	printf("│9│              │              │");
	gotoxy(x, y + 4);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 5);
	printf("│8│              │              │");
	gotoxy(x, y + 6);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 7);
	printf("│7│              │              │");
	gotoxy(x, y + 8);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 9);
	printf("│6│              │              │");
	gotoxy(x, y + 10);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 11);
	printf("│5│              │              │");
	gotoxy(x, y + 12);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 13);
	printf("│4│              │              │");
	gotoxy(x, y + 14);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 15);
	printf("│3│              │              │");
	gotoxy(x, y + 16);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 17);
	printf("│2│              │              │");
	gotoxy(x, y + 18);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 19);
	printf("│1│              │              │");
	gotoxy(x, y + 20);
	printf("├─┼──────────────┼──────────────┤");
	gotoxy(x, y + 21);
	printf("│0│              │              │");
	gotoxy(x, y + 22);
	printf("└─┴──────────────┼──────────────┘");

}
void PrintMenual(int x, int y) {
	gotoxy(x, y);
	printf("+ x y z : 리스트 맨 위에 입력");
	gotoxy(x, y + 1);
	printf("- : 리스트의 맨 위에서 삭제");
	gotoxy(x, y + 2);
	printf("e x y z : 리스트 맨 아래에 입력");
	gotoxy(x, y + 3);
	printf("d : 리스트 맨 아래 삭제");
	gotoxy(x, y + 4);
	printf("l : 리스트에 저장된 점 개수 출력");
	gotoxy(x, y + 5);
	printf("c : 리스트 초기화");
	gotoxy(x, y + 6);
	printf("m : 원점에서 가장 먼 거리에 있는 점 좌표값 출력");
	gotoxy(x, y + 7);
	printf("n : 원점에서 가장 가까운 거리에 있는 점 좌표값 출력");
	gotoxy(x, y + 8);
	printf("s : 원점과의 거리 오름차순 정렬, 빈칸모두 정렬");
	gotoxy(x, y + 9);
	printf("q : 종료");
}




void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}