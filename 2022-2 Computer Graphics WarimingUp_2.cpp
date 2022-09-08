#include <iostream>
#include <fstream>

void CheckWord(std::string str[10]);
void Del_all_newline(std::string str[10]);
int main() {
	FILE* fp;
	char fileName[50];

	std::cout << "input data file name: ";
	std::cin >> fileName;
	std::string str[10];
	if (fopen_s(&fp, fileName, "r")==0) {
		for (int i = 0; i < 10; ++i) {
			char temp[100];
			fgets(temp, 100, fp);
			str[i] = temp;
		}
		fclose(fp);
	}
	else {
		printf("파일을 찾을 수 없음\n");
		exit(0);
	}

	Del_all_newline(str);

	while (1) {
		system("cls");
		printf("1 - 문자열 모두 출력 / 2 - 2번실행 / 3 - 3번실행 / Q, q - 종료 : ");
		char select;
		std::cin >> select;
		
		switch (select) {
		case '1' :
			for (int i = 0; i < 10; ++i) {
				std::cout << str[i] << std::endl;
			}
			system("pause");
			break;
		case '2':
			CheckWord(str);
			system("pause");
			break;
		case '3':
			while (1) {
				system("cls");
				for (int i = 0; i < 10; ++i) {
					std::cout << str[i] << std::endl;
				}
				std::cout << "\n--------------------------------------------------------------------------------------------" << std::endl;
				printf("\n\nD/d - 문장 전체 뒤집기\nE/e - 문장 3글자 당 2칸씩 @ 삽입\nF/f - 띄어쓰기 기준으로 단어 뒤집기\nG/g - 특정 문자 다른 문자로 바꾸기\nH/h - 뒤집어 읽을 때 같은 만큼 출력\nQ/q - 종료\n");
				char select_3;
				std::cout << "입력: ";
				std::cin >> select_3;
				switch (select_3) {
				case 'D':
				case 'd':
					
			
					

					
					system("pause");
					break;
				case 'E':
				case 'e':
					break;
				case 'F':
				case 'f':
					break;
				case 'G':
				case 'g':
					break;
				case 'H':
				case 'h':
					break;
				case 'Q':
				case 'q':
					printf("이용해 주셔서 감사합니다.\n");
					exit(0);
					break;
				default:
					break;
				}
			}



			break;
		case 'Q':
		case 'q':
			printf("이용해주셔서 감사합니다.\n");
			exit(0);
			break;
		default:
			printf("잘못된 입력입니다. 2번과 3번 중 선택해주세요.\n");
			system("pause");
		}
	}

	

}

void CheckWord(std::string str[10]) {
	int word_count{}, num_count{}, cap_count{};
	bool check_cap = false;
	bool check_num = false;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < str[i].size(); ++j) {
			//std::cout << str[i][j];
			if ('0' <= str[i][j] && str[i][j] <= '9' && !check_num) {
				++num_count;
				check_num = true;
			}
			if ('A' <= str[i][j] && str[i][j] <= 'Z'&&!check_cap) {
				++cap_count;
				check_cap = true;
				
			}
			if (str[i][j] == ' ' || str[i][j] == '\n' || str[i][j]=='\0') {
				++word_count; 
				check_cap = false;
				check_num = false;
			}
			if (check_num) {
				if ('0' <= str[i][j] && str[i][j] <= '9') {
				}
				else {
					--num_count;
				}
			}
		}
		std::cout << std::endl;

	}
	std::cout << "단어 갯수: " << word_count << std::endl;
	std::cout << "대문자 갯수: " << cap_count << std::endl;
	std::cout << "숫자 갯수: " << num_count << std::endl;
}
void Del_all_newline(std::string str[10]) {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < str[i].size(); ++j) {
			if (str[i][j] == '\n') {
				str[i][j] = str[i][j + 1];
			}
		}
	}
}