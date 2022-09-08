/*
SIZE 를 통해 크기 조절 가능
STEP 1 -> 단계별로 확인 가
STEP 0 -> 기존 문제 실행코드
		R/r -> 다시 실행
		A/a -> 왼쪽으로 보드 넘기기
		D/d -> 오른쪽으로 보드 넘기기
		Q/q -> 종료
*/
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <random>
#define SIZE 30
#define STEP 1

enum MonsterGo{UP = 1 , DOWN = 2 , LEFT = 3, RIGHT = 4};
class Monster {
public:
	int x = 0, y = 0;
	int count = 1;
	int going_count=0;
	int wherego=0;
	int up_count = 0;
	int down_count = 0;
	int left_count = 0;
	int right_count = 0;

	void InitMonster() {
		x = 0; y = 0;
		count = 1;
		going_count = 0;
		wherego = 0;
		up_count = 0;
		down_count = 0;
		left_count = 0;
		right_count = 0;
	}
};

void ClearBoard(int board[SIZE][SIZE]);
void PrintBoard(int board[SIZE][SIZE],Monster mon);
void GoingAlgorithm(int board[SIZE][SIZE], Monster mob);
void gotoxy(int x, int y);
void MoveBoard(int board[SIZE][SIZE], BOOL right);
int main() {
	int board[SIZE][SIZE];
	ClearBoard(board);
	//PrintBoard(board);
	Monster mob;
	
	GoingAlgorithm(board,mob);
	if (!STEP) {
		while (1) {
			//system("cls");
			gotoxy(0, 0);
			PrintBoard(board, mob);
			switch (_getch()) {
			case 'R':
			case 'r':
				ClearBoard(board);
				mob.InitMonster();
				GoingAlgorithm(board,mob);
				break;
			case 'A':
			case 'a':
				MoveBoard(board, 0);
				break;
			case 'D':
			case 'd':
				MoveBoard(board, 1);
				break;
			case 'Q':
			case 'q':
				exit(0);
				break;
			}
		}
		
	}
}
void ClearBoard(int board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			board[i][j] = 0;
		}
	}
	board[0][0] = 1;
}
void PrintBoard(int board[SIZE][SIZE],Monster mon) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] != 0) {
				if (STEP&&board[i][j] == mon.count) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					std::cout << std::setw(3) << board[i][j] << " ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					std::cout << std::setw(3) << board[i][j] << " ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
			}
			else {
				std::cout << std::setw(3) << board[i][j] << " ";
			}
			
		}
		std::cout << std::endl << std::endl;
	}
}
void GoingAlgorithm(int board[SIZE][SIZE], Monster mon) {
	std::random_device rd;
	while (1) {
		if (STEP) {
			PrintBoard(board, mon);
			system("pause");
			gotoxy(0, 0);
		}
		if (mon.x == SIZE - 1 && mon.y == SIZE - 1) break;
		int left = 0, right = 0, up = 0, down = 0;
		//x축 우선도 설정
		if (mon.x == 0) {
			left = 0;
			right = 10;
		}
		else if (1 <= mon.x && mon.x <= SIZE / 3) {
			left = 1;
			right = 9;
		}
		else if (SIZE / 3 <= mon.x && mon.x <= SIZE / 2) {
			left = 2;
			right = 8;
		}
		else if (SIZE / 2 <= mon.x && mon.x <= SIZE / 3 * 2) {
			left = 3;
			right = 7;
			if (mon.left_count == 0) {
				left = 10;
				right = 0;
			}
		}
		else if (SIZE / 3 * 2 <= mon.x && mon.x <= SIZE - 2) {
			right = 10;
		}
		else if (mon.x == SIZE - 1) {
			right = 0;
			left = 2;
		}

		//y축 우선도 설정
		if (mon.y == 0) {
			up = 0;
			down = 10;
		}
		else if (1 <= mon.y && mon.y <= SIZE / 3) {
			up = 1;
			down = 9;
		}
		else if (SIZE / 3 <= mon.y && mon.y <= SIZE / 2) {
			up = 2;
			down = 8;
		}
		else if (SIZE / 2 <= mon.y && mon.y <= SIZE / 3 * 2) {
			up = 3;
			down = 7;
			if (mon.up_count == 0) {
				up = 10;
				down = 0;
			}
		}
		else if (SIZE / 3 * 2 <= mon.y && mon.y <= SIZE - 2) {
			down = 10;
		}
		else if (mon.y == SIZE - 1) {
			down = 0;
			up = 2;
		}


		std::uniform_int_distribution<int> uid(1, left + right + up + down);
		int checknum = uid(rd);
		if (checknum <= left) {
			//왼쪽으로 가도록 설정
			if ((mon.wherego == LEFT && mon.going_count >= 5) || mon.wherego == RIGHT);
			else {
				mon.x -= 1;
				mon.left_count += 1;
				mon.count += 1;

				if (mon.wherego == LEFT) {
					mon.going_count += 1;
				}
				else {
					mon.wherego = LEFT;
					mon.going_count = 1;
				}
				board[mon.x][mon.y] = mon.count;
			}
		}
		else if (checknum - left <= right) {
			//오른쪽으로 가도록 설정
			if ((mon.wherego == RIGHT && mon.going_count >= 5) || mon.wherego == LEFT);
			else {
				mon.x += 1;
				mon.right_count += 1;
				mon.count += 1;

				if (mon.wherego == RIGHT) {
					mon.going_count += 1;
				}
				else {
					mon.wherego = RIGHT;
					mon.going_count = 1;
				}
				board[mon.x][mon.y] = mon.count;
			}
		}
		else if (checknum - left - right <= up) {
			//위쪽으로 가도록 설정
			if ((mon.wherego == UP && mon.going_count >= 5) || mon.wherego == DOWN);
			else {
				mon.y -= 1;
				mon.up_count += 1;
				mon.count += 1;

				if (mon.wherego == UP) {
					mon.going_count += 1;
				}
				else {
					mon.wherego = UP;
					mon.going_count = 1;
				}
				board[mon.x][mon.y] = mon.count;
			}
		}
		else {
			//밑으로 가도록 설정
			if ((mon.wherego == DOWN && mon.going_count >= 5) || mon.wherego == UP);
			else {
				mon.y += 1;
				mon.down_count += 1;
				mon.count += 1;

				if (mon.wherego == DOWN) {
					mon.going_count += 1;
				}
				else {
					mon.wherego = DOWN;
					mon.going_count = 1;
				}
				board[mon.x][mon.y] = mon.count;
			}
		}

	}
}

void MoveBoard(int board[SIZE][SIZE], BOOL right) {
	int temp_line[SIZE];
	if (right) {//오른쪽으로 옮기기
		for (int i = 0; i < SIZE; ++i) {
			temp_line[i] = board[i][SIZE-1];
		}
		for (int i = SIZE-1; i >-1; --i) {
			for (int j = SIZE-1; j > -1; --j) {
				board[j][i] = board[j][i - 1];
			}
		}
		for (int i = 0; i < SIZE; ++i) {
			board[i][0] = temp_line[i];
		}
	}
	else {//왼쪽으로 옮기기
		for (int i = 0; i < SIZE; ++i) {
			temp_line[i] = board[i][0];
		}
		for (int i = 0; i < SIZE-1; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				board[j][i] = board[j][i + 1];
			}
		}
		for (int i = 0; i < SIZE; ++i) {
			board[i][SIZE - 1] = temp_line[i];
		}
	}

}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}