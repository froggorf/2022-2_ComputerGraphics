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
		printf("������ ã�� �� ����\n");
		exit(0);
	}

	Del_all_newline(str);

	while (1) {
		system("cls");
		printf("1 - ���ڿ� ��� ��� / 2 - 2������ / 3 - 3������ / Q, q - ���� : ");
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
				printf("\n\nD/d - ���� ��ü ������\nE/e - ���� 3���� �� 2ĭ�� @ ����\nF/f - ���� �������� �ܾ� ������\nG/g - Ư�� ���� �ٸ� ���ڷ� �ٲٱ�\nH/h - ������ ���� �� ���� ��ŭ ���\nQ/q - ����\n");
				char select_3;
				std::cout << "�Է�: ";
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
					printf("�̿��� �ּż� �����մϴ�.\n");
					exit(0);
					break;
				default:
					break;
				}
			}



			break;
		case 'Q':
		case 'q':
			printf("�̿����ּż� �����մϴ�.\n");
			exit(0);
			break;
		default:
			printf("�߸��� �Է��Դϴ�. 2���� 3�� �� �������ּ���.\n");
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
	std::cout << "�ܾ� ����: " << word_count << std::endl;
	std::cout << "�빮�� ����: " << cap_count << std::endl;
	std::cout << "���� ����: " << num_count << std::endl;
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