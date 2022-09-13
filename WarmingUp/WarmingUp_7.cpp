#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <random>

#define ComboScoreRate 1.3
#define FailScore -10
#define BaseScore 100
void gotoxy(int x, int y);

enum GameLevel { EASY = 1, NORMAL = 2, HARD = 3, HELL = 4, INFORM = 5 };
enum KeyBoard { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13 };

class Game {
public:



};
std::random_device rd;
std::uniform_int_distribution<int> uid(1, 12);
class Board {
public:
	char card[4][6];
	int select_x = 0, select_y = 0;
	int click_x[2] = { -1,-1 }, click_y[2] = { -1,-1 };

	int level = 0;
	int combo = 0;
	int fail = 0;

	int score = 0;
	int life = 0;
	int sleepTime = 2000;

	void InitBoard(int level) {
		score = 0;
		this->level = level;
		switch (level) {
		case EASY:
			card[0][0] = card[0][1] = 'a';
			card[1][0] = card[1][1] = 'b';
			card[2][0] = card[2][1] = 'c';
			card[3][0] = card[3][1] = 'd';
			life = 50;
			sleepTime = 1000;
			break;
		case NORMAL:
		case HARD:
			card[0][0] = card[0][1] = 'a'; card[0][2] = card[0][3] = 'e';
			card[1][0] = card[1][1] = 'b'; card[1][2] = card[1][3] = 'f';
			card[2][0] = card[2][1] = 'c'; card[2][2] = card[2][3] = 'g';
			card[3][0] = card[3][1] = 'd'; card[3][2] = card[3][3] = 'h';
			life = 30;
			sleepTime = 700;
			break;
		case HELL:
			card[0][0] = card[0][1] = 'a'; card[0][2] = card[0][3] = 'e'; card[0][4] = card[0][5] = 'i';
			card[1][0] = card[1][1] = 'b'; card[1][2] = card[1][3] = 'f'; card[1][4] = card[1][5] = 'j';
			card[2][0] = card[2][1] = 'c'; card[2][2] = card[2][3] = 'g'; card[2][4] = card[2][5] = 'k';
			card[3][0] = card[3][1] = 'd'; card[3][2] = card[3][3] = 'h'; card[3][4] = card[3][5] = 'l';
			life = 30;
			sleepTime = 400;
			break;
		}
		select_x = 0; select_y = 0;
		click_x[0] = -1, click_x[1] = -1, click_y[0] = -1, click_y[1] = -1;
		combo = fail = 0;
	}
	void ShuffleCard() {
		switch (level) {
		case EASY:
			for (int i = 0; i < 50; ++i) {
				int randx1 = uid(rd) % 4, randy1 = uid(rd) % 2;
				int randx2 = uid(rd) % 4, randy2 = uid(rd) % 2;
				char temp = card[randx1][randy1];
				card[randx1][randy1] = card[randx2][randy2];
				card[randx2][randy2] = temp;
			}
			break;
		case NORMAL:
		case HARD:
			for (int i = 0; i < 100; ++i) {
				int randx1 = uid(rd) % 4, randy1 = uid(rd) % 4;
				int randx2 = uid(rd) % 4, randy2 = uid(rd) % 4;
				char temp = card[randx1][randy1];
				card[randx1][randy1] = card[randx2][randy2];
				card[randx2][randy2] = temp;
			}
			break;
		case HELL:
			for (int i = 0; i < 100; ++i) {
				int randx1 = uid(rd) % 4, randy1 = uid(rd) % 6;
				int randx2 = uid(rd) % 4, randy2 = uid(rd) % 6;
				char temp = card[randx1][randy1];
				card[randx1][randy1] = card[randx2][randy2];
				card[randx2][randy2] = temp;
			}
			break;

		}
	}
	void DrawCard() {
		switch (level) {
		case EASY:
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 2; ++j) {
					gotoxy(1 + 4 * j, 1 + 2 * i);
					if ('a' <= card[i][j] && card[i][j] <= 'z')
						std::cout << " * ";
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), card[i][j] - 'A' + 1);
						std::cout << " " << card[i][j] << " ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

				}
			}
			if (click_x[0] != -1 && click_y[0] != -1) {
				gotoxy(1 + 4 * click_x[0], 1 + 2 * click_y[0]);
				if ('a' <= card[click_y[0]][click_x[0]] && card[click_y[0]][click_x[0]] <= 'z')
					std::cout << " " << (char)(card[click_y[0]][click_x[0]] - ('z' - 'Z')) << " ";
				else
					std::cout << " " << card[click_y[0]][click_x[0]] << " ";
			}
			if (click_x[1] != -1 && click_y[1] != -1) {
				gotoxy(1 + 4 * click_x[1], 1 + 2 * click_y[1]);
				if ('a' <= card[click_y[1]][click_x[1]] && card[click_y[1]][click_x[1]] <= 'z')
					std::cout << " " << (char)(card[click_y[1]][click_x[1]] - ('z' - 'Z')) << " ";
				else std::cout << " " << card[click_y[1]][click_x[1]] << " ";
			}
			gotoxy(1 + 4 * select_x, 1 + 2 * select_y);
			std::cout << "[";
			gotoxy(1 + 4 * select_x + 2, 1 + 2 * select_y);
			std::cout << "]";
			break;
		case NORMAL:
		case HARD:
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					gotoxy(1 + 4 * j, 1 + 2 * i);
					if ('a' <= card[i][j] && card[i][j] <= 'z')
						std::cout << " * ";
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), card[i][j] - 'A' + 1);
						std::cout << " " << card[i][j] << " ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
				}
			}
			if (click_x[0] != -1 && click_y[0] != -1) {
				gotoxy(1 + 4 * click_x[0], 1 + 2 * click_y[0]);
				if ('a' <= card[click_y[0]][click_x[0]] && card[click_y[0]][click_x[0]] <= 'z')
					std::cout << " " << (char)(card[click_y[0]][click_x[0]] - ('z' - 'Z')) << " ";
				else
					std::cout << " " << card[click_y[0]][click_x[0]] << " ";
			}
			if (click_x[1] != -1 && click_y[1] != -1) {
				gotoxy(1 + 4 * click_x[1], 1 + 2 * click_y[1]);
				if ('a' <= card[click_y[1]][click_x[1]] && card[click_y[1]][click_x[1]] <= 'z')
					std::cout << " " << (char)(card[click_y[1]][click_x[1]] - ('z' - 'Z')) << " ";
				else std::cout << " " << card[click_y[1]][click_x[1]] << " ";
			}
			gotoxy(1 + 4 * select_x, 1 + 2 * select_y);
			std::cout << "[";
			gotoxy(1 + 4 * select_x + 2, 1 + 2 * select_y);
			std::cout << "]";
			break;
		case HELL:
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 6; ++j) {
					gotoxy(1 + 4 * j, 1 + 2 * i);
					if ('a' <= card[i][j] && card[i][j] <= 'z')
						std::cout << " * ";
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), card[i][j] - 'A' + 1);
						std::cout << " " << card[i][j] << " ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
				}
			}
			if (click_x[0] != -1 && click_y[0] != -1) {
				gotoxy(1 + 4 * click_x[0], 1 + 2 * click_y[0]);
				if ('a' <= card[click_y[0]][click_x[0]] && card[click_y[0]][click_x[0]] <= 'z')
					std::cout << " " << (char)(card[click_y[0]][click_x[0]] - ('z' - 'Z')) << " ";
				else
					std::cout << " " << card[click_y[0]][click_x[0]] << " ";
			}
			if (click_x[1] != -1 && click_y[1] != -1) {
				gotoxy(1 + 4 * click_x[1], 1 + 2 * click_y[1]);
				if ('a' <= card[click_y[1]][click_x[1]] && card[click_y[1]][click_x[1]] <= 'z')
					std::cout << " " << (char)(card[click_y[1]][click_x[1]] - ('z' - 'Z')) << " ";
				else std::cout << " " << card[click_y[1]][click_x[1]] << " ";
			}
			gotoxy(1 + 4 * select_x, 1 + 2 * select_y);
			std::cout << "[";
			gotoxy(1 + 4 * select_x + 2, 1 + 2 * select_y);
			std::cout << "]";
			break;
		}
	}
	void PressEnter() {
		if (!('a' <= card[select_y][select_x] && card[select_y][select_x] <= 'z'))return;
		if ((click_x[0] == -1 || click_y[0] == -1)) {//첫 번째 선택
			click_x[0] = select_x;
			click_y[0] = select_y;
		}
		else {//두 번째 선택
			if (select_x == click_x[0] && select_y == click_y[0]);//만약 같은 카드를 선택할 경우
			else {
				if (card[select_y][select_x] == card[click_y[0]][click_x[0]]) {//카드가 맞을 경우
					card[select_y][select_x] -= ('z' - 'Z');
					card[click_y[0]][click_x[0]] -= ('z' - 'Z');

					double rate = 1;
					for (int i = 0; i < combo; ++i) {
						rate *= 1.3;
					}
					score += (BaseScore * rate);

					if (fail == 0) ++combo;
					else combo = 1;
					fail = 0;

				}
				else {//카드가 틀릴 경우
					combo = 0;
					fail += 1;
					score += FailScore;
					life -= 1;

				}
				click_x[1] = select_x, click_y[1] = select_y;

				if (fail >= 5) {
					//어려움과 헬난이도에서 fail 5번 이상일경우 돌려버리도록 설정
					if (level == HARD || level == HELL) {
						fail = 0;
						ShuffleCard();
						click_x[0] = -1, click_y[0] = -1;
						click_x[1] = -1, click_y[1] = -1;
					}
				}

				DrawCard();
				for (int i = 0; i < 20; ++i) {
					if (level == EASY) gotoxy(9, 7);
					else if (level == NORMAL || level == HARD) gotoxy(17, 7);
					else gotoxy(25, 7);
					printf("■■■■■■■■■■■■■■■■■■■■");
					for (int j = i; j > -1; --j) {
						if (level == EASY) gotoxy(9 + 19 - j, 7);
						else if (level == NORMAL || level == HARD) gotoxy(17 + 19 - j, 7);
						else gotoxy(25 + 19 - j, 7);
						printf(" ");
					}
					Sleep(sleepTime / 20);
				}
				click_x[0] = -1, click_y[0] = -1;
				click_x[1] = -1, click_y[1] = -1;
			}

		}
	}
	void PressArrow(int presskey) {
		switch (presskey) {
		case UP:
			select_y -= 1;
			if (select_y < 0) select_y = 0;
			break;
		case DOWN:
			select_y += 1;
			if (select_y > 3) select_y = 3;
			break;
		case LEFT:
			select_x -= 1;
			if (select_x < 0) select_x = 0;
			break;
		case RIGHT:
			select_x += 1;
			switch (level) {
			case EASY:
				if (select_x > 1) select_x = 1;
				break;
			case NORMAL:
			case HARD:
				if (select_x > 3) select_x = 3;
				break;
			case HELL:
				if (select_x > 5) select_x = 5;
				break;
			}
			break;
		}
	}
	BOOL CheckClear() {
		int max;
		switch (level) {
		case EASY:
			max = 2;
			break;
		case NORMAL:
		case HARD:
			max = 4;
			break;
		case HELL:
			max = 6;
			break;
		}
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < max; ++j) {
				if ('a' <= card[i][j] && card[i][j] <= 'z') return false;
			}
		}
		return true;
	}
};


void GameMenu(int&, Game&, Board& board);
void DrawBoard(int x, int y, int levelselect);
void DrawStatus(int x, int y, int levelselect, Board& board);
void DrawFrame(int levelselect, Board& board);
BOOL gamestart = false;
int main() {
	Board board;
	Game game;

	BOOL flag_answer = false;
	int levelselect = EASY;

	while (1) {
		if (!gamestart) { //게임 시작 전 메뉴
			GameMenu(levelselect, game, board);

		}
		else {			 //게임 시작 후
			if (board.CheckClear()) {
				gotoxy(0, 15);
				printf("축하드립니다! 게임 클리어!\n");
				printf("r - 메인메뉴 // Q, q - 게임 종료");
				switch (_getch()) {
				case 'R':
				case 'r':
					gamestart = false;
					levelselect = EASY;
					system("cls");
					break;
				case 'Q':
				case 'q':
					_exit(0);
					break;
				}
				continue;
			}

			if (board.life <= 0) {
				gotoxy(0, 15);
				printf("게임 오버! 다시 도전해주세요.\n");
				printf("r - 메인메뉴 // Q, q - 게임 종료");
				switch (_getch()) {
				case 'R':
				case 'r':
					gamestart = false;
					levelselect = EASY;
					system("cls");
					break;
				case 'Q':
				case 'q':
					_exit(0);
					break;
				}
				continue;
			}

			DrawFrame(levelselect, board);
			board.DrawCard();
			if (flag_answer) {
				gotoxy(0, 10);
				int max = 0;
				switch (board.level) {
				case EASY: max = 2; break;
				case NORMAL: case HARD: max = 4; break;
				case HELL: max = 6; break;
				}
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < max; ++j) {
						if ('a' <= board.card[i][j] && board.card[i][j] <= 'z')
							std::cout << " " << (char)(board.card[i][j] - ('z' - 'Z')) << " ";
						else
							std::cout << " " << board.card[i][j] << " ";
					}
					std::cout << std::endl;
				}
			}
			gotoxy(0, 9);
			printf("    ");
			gotoxy(0, 9);
			if (board.click_x[0] == -1 && board.click_y[0] == -1) printf("첫 번째 카드 선택");
			else printf("두 번째 카드 선택");

			switch (_getch()) {
			case 'Q':
			case 'q':
				exit(0);
				break;
			case 'R':
			case 'r':
				gamestart = false;
				levelselect = EASY;
				system("cls");
				break;
			case UP:	//위 방향키
				board.PressArrow(UP);
				break;
			case DOWN:	//아래 방향키
				board.PressArrow(DOWN);
				break;
			case LEFT:	//왼쪽 방향키
				board.PressArrow(LEFT);
				break;
			case RIGHT:	//오른쪽 방향키
				board.PressArrow(RIGHT);
				break;
			case ENTER:	//엔터
				board.PressEnter();
				break;
			case '1':
				flag_answer = 1 - flag_answer;
				gotoxy(0, 10);
				printf("                             \n");
				printf("                             \n");
				printf("                             \n");
				printf("                             \n");
				break;

			case '-':
				board.life -= 1;
			}
		}
	}
}

void GameMenu(int& levelselect, Game& game, Board& board) {
	gotoxy(0, 0);
	printf("카드 짝 찾기 게임 - 2019180031 이윤석\n");
	printf("**난이도를 선택해주세요** // 방향키 조정 - 엔터 누르기 // Q/q - 종료\n");
	printf("   쉬움\n");
	printf("   보통\n");
	printf("   어려움\n");
	printf("   헬\n");
	printf("   난이도 설명문\n");
	gotoxy(0, 1 + levelselect);
	printf("->");

	switch (_getch()) {
	case 'Q':
	case 'q':
		exit(0);
		break;
	case UP:	//위
		gotoxy(0, 1 + levelselect);
		printf("   ");
		levelselect -= 1;
		if (levelselect < EASY) levelselect = EASY;
		break;
	case DOWN:	//아래
		gotoxy(0, 1 + levelselect);
		printf("   ");
		levelselect += 1;
		if (levelselect > INFORM) levelselect = INFORM;
		break;
	case ENTER:	//엔터
		switch (levelselect) {
		case EASY:
		case NORMAL:
		case HARD:
		case HELL:
			board.InitBoard(levelselect);
			board.ShuffleCard();
			system("cls");
			gamestart = true;
			break;
		case INFORM:
			gotoxy(0, 1 + levelselect + 2);
			printf("------------------------------------------------------------------------------------------------------\n");
			printf(" 쉬움  - 4x2  //  기회 100회  //  카드시간 2초\n");
			printf(" 보통  - 4x4  //  기회 30 회  //  카드시간 1초\n");
			printf("어려움 - 4x4  //  기회 30 회  //  카드시간 1초    //  *5번 실패시 못찾은 카드 랜덤 셔플\n");
			printf("  헬   - 4x6  //  기회 30 회  //  카드시간 0.5초  //  *5번 실패시 못찾은 카드 랜덤 셔플\n");
			printf("점수 - 콤보당 1.3배(곱연산) 증가, 실패 횟수당 0.9배(곱연산)감소\n");
			printf("------------------------------------------------------------------------------------------------------\n");
			while (_getch() != ENTER);
			gotoxy(0, 1 + levelselect + 2);
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			printf("                                                                                                      \n");
			break;
		}
		break;
	}
}

void DrawBoard(int x, int y, int levelselect) {
	switch (levelselect) {
	case EASY:
		gotoxy(x, y);
		printf("┌───┬───┬");
		gotoxy(x, y + 1);
		printf("│   │   │");
		gotoxy(x, y + 2);
		printf("├───┼───┼");
		gotoxy(x, y + 3);
		printf("│   │   │");
		gotoxy(x, y + 4);
		printf("├───┼───┼");
		gotoxy(x, y + 5);
		printf("│   │   │");
		gotoxy(x, y + 6);
		printf("├───┼───┼");
		gotoxy(x, y + 7);
		printf("│   │   │");
		gotoxy(x, y + 8);
		printf("└───┴───┴");
		break;
	case NORMAL:
	case HARD:
		gotoxy(x, y);
		printf("┌───┬───┬───┬───┬");
		gotoxy(x, y + 1);
		printf("│   │   │   │   │");
		gotoxy(x, y + 2);
		printf("├───┼───┼───┼───┼");
		gotoxy(x, y + 3);
		printf("│   │   │   │   │");
		gotoxy(x, y + 4);
		printf("├───┼───┼───┼───┼");
		gotoxy(x, y + 5);
		printf("│   │   │   │   │");
		gotoxy(x, y + 6);
		printf("├───┼───┼───┼───┼");
		gotoxy(x, y + 7);
		printf("│   │   │   │   │");
		gotoxy(x, y + 8);
		printf("└───┴───┴───┴───┴");
		break;
	case HELL:
		gotoxy(x, y);
		printf("┌───┬───┬───┬───┬───┬───┬");
		gotoxy(x, y + 1);
		printf("│   │   │   │   │   │   │");
		gotoxy(x, y + 2);
		printf("├───┼───┼───┼───┼───┼───┼");
		gotoxy(x, y + 3);
		printf("│   │   │   │   │   │   │");
		gotoxy(x, y + 4);
		printf("├───┼───┼───┼───┼───┼───┼");
		gotoxy(x, y + 5);
		printf("│   │   │   │   │   │   │");
		gotoxy(x, y + 6);
		printf("├───┼───┼───┼───┼───┼───┼");
		gotoxy(x, y + 7);
		printf("│   │   │   │   │   │   │");
		gotoxy(x, y + 8);
		printf("└───┴───┴───┴───┴───┴───┴");
		break;
	}
}

void DrawStatus(int x, int y, int levelselect, Board& board) {
	gotoxy(x, y);
	printf("─────────┬──────────┐");
	gotoxy(x, y + 1);

	switch (levelselect) {
	case EASY:
		printf("EASY/life│%4d / 50 │", board.life);
		break;
	case NORMAL:
		printf("NORM/life│%4d / 30 │", board.life);
		break;
	case HARD:
		printf("HARD/life│%4d / 30 │", board.life);
		break;
	case HELL:
		printf("HELL/life│%4d / 30 │", board.life);
		break;
	}
	gotoxy(x, y + 2);
	printf("─────────┼──────────┤");
	gotoxy(x, y + 3);
	printf("  score  │%10d│", board.score);
	gotoxy(x, y + 4);
	printf("─────────┼──────────┤");
	gotoxy(x, y + 5);
	if (board.level == EASY || board.level == NORMAL)
		printf("combo:%3d│fail:%5d│", board.combo, board.fail);
	else
		printf("combo:%3d│fail:%3d/5│", board.combo, board.fail);
	gotoxy(x, y + 6);
	printf("─────────┴──────────┤");
	gotoxy(x, y + 7);
	printf("                    │");
	gotoxy(x, y + 8);
	printf("────────────────────┘");
}

void DrawFrame(int levelselect, Board& board) {
	switch (levelselect) {
	case EASY:
		DrawBoard(0, 0, levelselect);
		DrawStatus(9, 0, levelselect, board);
		break;
	case NORMAL:
	case HARD:
		DrawBoard(0, 0, levelselect);
		DrawStatus(17, 0, levelselect, board);
		break;
	case HELL:
		DrawBoard(0, 0, levelselect);
		DrawStatus(25, 0, levelselect, board);
		break;
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}