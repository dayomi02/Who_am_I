#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <mysql.h>
#include <TCHAR.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

#pragma comment(lib,"libmysql.lib")

#define UP 0 //w
#define DOWN 1 //s
#define LEFT 2 //a
#define RIGHT 3 //d
#define SUBMIT 4 //�����̽��� ����

static int numSum;			//bored���� ���

const char* host = "localhost";			//db���� ���
const char* user = "root";
const char* pw = "mirim2";
const char* db = "heeda";

int keyControl(); //Ű���� �Է°� ����
void gotoxy(int x, int y);
void titleDraw();
int menuDraw();
void infoDraw();

int filein();
void fileout();
void boredQuestionPrint();
void boredResultPrint();
void personalityTest();
void UnconsciousTest();
int enneagram();
void todayFortune();
int count(int* da, int* dam, int* uoo, int* jum);		//�����׽�Ʈ���� ���
void gijilresult(int* da, int* dam, int* uoo, int* jum);
void gijiltest();
void dbconn();

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void titleDraw() {
	gotoxy(2, 3); printf("��");
	gotoxy(2, 4); printf("��");
	gotoxy(3, 5); printf("��");
	gotoxy(3, 6); printf("��");
	gotoxy(4, 7); printf("��");
	gotoxy(4, 8); printf("��");
	gotoxy(5, 9); printf("��");
	gotoxy(5, 10); printf("��");
	gotoxy(7, 11); printf("��");
	gotoxy(9, 10); printf("��");
	gotoxy(9, 9); printf("��");
	gotoxy(10, 8); printf("��");
	gotoxy(10, 7); printf("��");
	gotoxy(11, 6); printf("��");
	gotoxy(12, 6); printf("��");
	gotoxy(13, 7); printf("��");
	gotoxy(13, 8); printf("��");
	gotoxy(14, 9); printf("��");
	gotoxy(14, 10); printf("��");
	gotoxy(16, 11); printf("��");
	gotoxy(18, 10); printf("��");
	gotoxy(18, 9); printf("��");
	gotoxy(19, 8); printf("��");
	gotoxy(19, 7); printf("��");
	gotoxy(20, 6); printf("��");
	gotoxy(20, 5); printf("��");
	gotoxy(21, 4); printf("��");
	gotoxy(21, 3); printf("��");

	gotoxy(24, 3); printf("��");
	gotoxy(24, 4); printf("��");
	gotoxy(24, 5); printf("��");
	gotoxy(24, 6); printf("��");
	gotoxy(24, 7); printf("��");
	gotoxy(24, 8); printf("��");
	gotoxy(24, 9); printf("��");
	gotoxy(24, 10); printf("��");
	gotoxy(24, 11); printf("��");
	gotoxy(26, 7); printf("��");
	gotoxy(27, 6); printf("��");
	gotoxy(29, 6); printf("��");
	gotoxy(31, 7); printf("��");
	gotoxy(31, 8); printf("��");
	gotoxy(31, 9); printf("��");
	gotoxy(31, 10); printf("��");
	gotoxy(31, 11); printf("��");

	gotoxy(40, 11); printf("��");
	gotoxy(38, 11); printf("��");
	gotoxy(36, 11); printf("��");
	gotoxy(35, 10); printf("��");
	gotoxy(34, 9); printf("��");
	gotoxy(35, 8); printf("��");
	gotoxy(36, 7); printf("��");
	gotoxy(38, 7); printf("��");
	gotoxy(40, 7); printf("��");
	gotoxy(41, 8); printf("��");
	gotoxy(42, 9); printf("��");
	gotoxy(41, 10); printf("��");

	gotoxy(51, 8); printf("��");
	gotoxy(49, 8); printf("��");
	gotoxy(48, 9); printf("��");
	gotoxy(48, 10); printf("��");
	gotoxy(49, 11); printf("��");
	gotoxy(51, 11); printf("��");
	gotoxy(52, 10); printf("��");
	gotoxy(52, 9); printf("��");
	gotoxy(54, 7); printf("��");
	gotoxy(54, 8); printf("��");
	gotoxy(54, 9); printf("��");
	gotoxy(54, 10); printf("��");
	gotoxy(55, 11); printf("��");

	gotoxy(58, 11); printf("��");
	gotoxy(58, 10); printf("��");
	gotoxy(58, 9); printf("��");
	gotoxy(58, 8); printf("��");
	gotoxy(58, 7); printf("��");
	gotoxy(60, 9); printf("��");
	gotoxy(61, 8); printf("��");
	gotoxy(63, 8); printf("��");
	gotoxy(64, 9); printf("��");
	gotoxy(65, 10); printf("��");
	gotoxy(65, 11); printf("��");
	gotoxy(66, 9); printf("��");
	gotoxy(67, 8); printf("��");
	gotoxy(69, 8); printf("��");
	gotoxy(70, 9); printf("��");
	gotoxy(70, 10); printf("��");
	gotoxy(70, 11); printf("��");

	gotoxy(76, 11); printf("��");
	gotoxy(78, 11); printf("��");
	gotoxy(80, 11); printf("��");
	gotoxy(78, 10); printf("��");
	gotoxy(78, 9); printf("��");
	gotoxy(78, 8); printf("��");
	gotoxy(78, 7); printf("��");
	gotoxy(78, 6); printf("��");
	gotoxy(78, 5); printf("��");
	gotoxy(78, 4); printf("��");
	gotoxy(76, 3); printf("��");
	gotoxy(78, 3); printf("��");
	gotoxy(80, 3); printf("��");
}
int menuDraw() {
	int x = 31;
	int y = 16;
	gotoxy(x - 2, y); cout << "��   �׽�Ʈ �����ϱ�";
	gotoxy(x, y + 1); cout << "   ���α׷� �Ұ�";
	gotoxy(x, y + 2); cout << "   ���� ���� ����  ";
	gotoxy(x, y + 3); cout << "   ����  ";

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 16) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << "��";
			}
			break;
		}

		case DOWN: {
			if (y < 19) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << "��";
			}
			break;
		}

		case SUBMIT: {
			return y - 16;
		}
		}//switch
	}//while
}
int testMenuDraw() {
	system("cls");
	int x = 31;
	int y = 10;
	gotoxy(x - 2, y); cout << "��   �ɽ��� �� �ϴ� �ɸ� �׽�Ʈ";
	gotoxy(x, y + 1); cout << "   ������ �˾ƺ��� �ɸ� �׽�Ʈ";
	gotoxy(x, y + 2); cout << "   ���ǽ� �ɸ� �׽�Ʈ  ";
	gotoxy(x, y + 3); cout << "   ���Ͼ�׷� ���� �׽�Ʈ  ";
	gotoxy(x, y + 4); cout << "   ���� �׽�Ʈ  ";
	gotoxy(x, y + 5); cout << "   ������ �  ";


	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 10) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << "��";
			}
			break;
		}

		case DOWN: {
			if (y < 16) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << "��";
			}
			break;
		}

		case SUBMIT: {
			return y - 10;
		}
		}//switch
	}//while
}
int keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}
}
void infoDraw() {
	system("cls");
	cout << "\n\n                              << Who am I >>" << endl;
	cout << "        �����׽�Ʈ���� �����׽�Ʈ���� ���� �׽�Ʈ ���� ���� ����" << endl;
	cout << "            +) �׽�Ʈ ����� �ؼ����� �����Ѵٱ�~!!~! \n\n" << endl;
	cout << "\n\n                              << Who am I ������ �Ұ� >>" << endl;
	cout << "  �� ���� �� 2209" << endl;
	cout << "  �����褻\n" << endl;
	cout << "  �� �ִٿ� �� 2216" << endl;
	cout << "  �� �Ϳ����� ���� �ѽ�><\n" << endl;
	cout << "  \n\n(���� ȭ������ ���� ������ �����̽��� ����)\n" << endl;
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}
int filein() {
	system("cls");
	char userName[20];
	int starNum;
	string impression;

	ofstream fout("guestBook.txt", ios::app);
	cout << "<< ���� �ۼ� >>" << endl;
	cout << "�̸��� �Է��ϼ���\n-> ";
	cin >> userName;
	while (true) {
		cout << "������ �Է��ϼ��� (5�� ����)\n-> ";
		cin >> starNum;
		if (starNum >= 1 && starNum <= 5)
			break;
		else
			cout << "�Է� ������ �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���....\n";
	}
	cout << "�������� �����ּ���\n-> ";
	getline(cin, impression);
	getline(cin, impression);


	fout << setw(13) << userName << setw(10) << starNum << setw(40) << impression << endl;
	cout << setw(13) << userName << setw(10) << starNum << setw(40) << impression << endl;
	cout << endl;
	cout << "�����մϴ�.";

	return 1;
}
void fileout() {
	system("cls");
	string line;

	ifstream	fin;

	fin.open("guestBook.txt");

	cout << "\n==============================����=============================\n" << endl;
	cout << "	�̸�		����			������			\n" << endl;
	while (getline(fin, line)) {
		cout << line << endl;
	}
	fin.close();
	cout << "\n<���� ȭ������ ���ư��÷��� space bar�� �����ּ���...>";
}
void dbconn() {
	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
	{
		cout << "mysql_init() error!!!!!" << endl;
	}

	connection = mysql_real_connect(&conn, host, user, pw, db, 3307, (const char*)NULL, 0);
	if (connection == NULL)
	{
		cout << "����" << mysql_errno(&conn) << mysql_error(&conn);
	}
	else
	{
		if (mysql_select_db(&conn, db))
		{
			cout << "����" << mysql_errno(&conn) << mysql_error(&conn);
		}

		mysql_query(connection, "set session character_set_connection=euckr;");
		mysql_query(connection, "set session character_set_results=euckr;");
		mysql_query(connection, "set session character_set_client=euckr;");

		int inum = enneagram();
		char intStr[3] = { 0, };
		itoa(inum, intStr, 10);
		string num = string(intStr);

		const char* query = "select *from ennea";
		int state = 0;

		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				if (sql_row[0] == num) {
					cout << "����� ��Ÿ���� �ܾ�� " << sql_row[2] << "�Դϴ�!" << endl;
					cout << "���������� " << sql_row[3] << endl;
				}
			}
			mysql_free_result(sql_result);
		}
		mysql_close(connection);
	}
}
void boredResultPrint() {
	if (numSum <= 20) {
		cout << "������ ���� ����� �ҽ��ϰ� �����δ��մϴ�. " << endl;
		cout << "������ �ϵ� �������� ����ؼ� ��������߸� �ϰ�, " << endl;
		cout << "Ÿ���̳� � �Ͽ� ����Ǵ� ���� ���ϴ� ����Դϴ�." << endl;
		cout << "����, ������ �缭 �ϴ� Ÿ���̱⵵ �մϴ�." << endl;
		cout << "����� �� �𸣴� ������ ����� �����ϴٰ� �����ϱ⵵ �մϴ�.\n" << endl;
	}
	else if (numSum >= 21 && numSum <= 30) {
		cout << "������ ���� ����� �����ϸ� ����� �������" << endl;
		cout << "�����ϰ� ���ɽ������ϸ� �������� �����ϴ� ���Դϴ�." << endl;
		cout << "����� ���� ���ΰ� �浿������ �ϴ� ����� ���ٸ�" << endl;
		cout << "ģ������ ����� �������� �𸨴ϴ�. " << endl;
		cout << "���� ���̵� �Ĳ��� ��ȹ�ϸ� ���� ������ �ϴ� ���� ��ȣ�մϴ�." << endl;
		cout << "����ϱ� ������ NO��� ���� �� �ִ� ����̱⵵ �մϴ�." << endl;
	}
	else if (numSum >= 31 && numSum <= 40) {
		cout << "������ ���� ����� �����ϰ� �����ϸ� �������Դϴ�." << endl;
		cout << "����� ��� �� ���ϰų� ������ �������� ������" << endl;
		cout << "������� ������Դ� �ſ� �����ֽø� �ڽŵ� ���� ��츦" << endl;
		cout << "���ֱ⸦ ����մϴ�. ����� ������� �ƴ� ������� " << endl;
		cout << "����� �ŷڸ� ���� ���� ��ƴٴ� �Ͱ� " << endl;
		cout << "�� �ŷڰ� �������� �ٽ� �ǵ����� ��ƴٴ� ���� �˰� ���� �̴ϴ�." << endl;
	}
	else if (numSum >= 41 && numSum <= 50) {
		cout << "������ ���� ����� �ſ� �ŷ� �ִ� Ÿ���̱⵵ �ϸ�," << endl;
		cout << "���δ� �̼����̸鼭�� ��ſ� ����̶�� �����մϴ�." << endl;
		cout << "������ �̸��� ������ ��������� ������ ��ġ�� ������" << endl;
		cout << "���������� �ʴ� ����̱⵵ �մϴ�. ���� �����ϸ�" << endl;
		cout << "ģ���ϰ�, ���ؽ��� ���� �ٸ� ����� ���� �� �ƴ� " << endl;
		cout << "������ ����Ŀ ������ �ϱ⵵ �մϴ�." << endl;
	}
	else if (numSum >= 51 && numSum <= 60) {
		cout << "������ ���� ����� �����������, �浿���� ����̶��" << endl;
		cout << "�����մϴ�. ���� ���������� ���� ������ ���� �� �ƴ�" << endl;
		cout << "����̱⵵ �մϴ�. �����̵� �õ��غ� �� �ƴ� ������ " << endl;
		cout << "������ Ÿ������ ���� ������ ȣ����� �ſ� �����ϴ�." << endl;
		cout << "����� ģ������ ����� ���ϴ� �����Կ� �̲����ϴ�." << endl;
	}
	else if (numSum <= 60) {
		cout << "������ ���� ����� ��� �������̶�� �����ϸ�" << endl;
		cout << "�ణ�� �㿵���� �ְ� ���� �����ϰ� ���� �屸�� ���մϴ�." << endl;
		cout << "���� ���ִ� Ī���� ��������, ���� ������ ���鿡��" << endl;
		cout << "Ī���� �������� ���ϴ� ����� ������ �ֽ��ϴ�." << endl;
		cout << "�ǿܷ� ����� ����� ������ �η����ϰ� �췯������" << endl;
		cout << "������� ������, ����� �׷��� ������� �� ���� ���մϴ�." << endl;
	}
}
void boredQuestionPrint() {
	int choosenum = 0;
	cout << "\n\n         << �ɸ��׽�Ʈ >>\n\n#������_������_����?\n";
	cout << " ! ������ �� 10���� �ڽſ� ���� �����ٰ� �����ϴ� ���⸦ ���ø� �˴ϴ� !\n\n" << endl;
	//1�� 
	while (true) {
		cout << "-------------------------------------------" << endl;
		cout << "Q1. �Ϸ� �� ����� ���� ���� �ð����?" << endl;
		cout << "1. ��ħ\n2. ���ĳ� �̸� ����\n3. ���� ��" << endl;
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 2;
			break;
		}
		else if (choosenum == 2) {
			numSum += 4;
			break;

		}
		else if (choosenum == 3) {
			numSum += 6;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}

	}
	//2��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "\nQ2. ���� ���� ��, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. �Ӹ��� ���, �������� �ٶ󺸸� �� ������ �� �ȴ´�\n";
		cout << "2. ������ �а�, ���� �ȴ´�\n";
		cout << "3. ������ ����, ���� �ȴ´�\n";
		cout << "4. �ٴ��� ���� �� ������ �ȴ´�\n";
		cout << "5. ���� ������ �ȴ´�\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 7;
			break;
		}
		else if (choosenum == 2) {
			numSum += 6;
			break;

		}
		else if (choosenum == 3) {
			numSum += 4;
			break;
		}
		else if (choosenum == 4) {
			numSum += 2;
			break;
		}
		else if (choosenum == 5) {
			numSum += 1;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//3��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q3. ���� ������ �̾߱��� ��, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ������� ��ġ�ϸ�\n";
		cout << "2. �� ���� ������ �Ÿ��ų� �� �Ӹ��� ������\n";
		cout << "3. �� ���̳� �� ���� �㸮�� �ø���\n";
		cout << "4. �� ��¯�� ���� ����\n";
		cout << "5. �� ���� ���� ���\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 7;
			break;
		}
		else if (choosenum == 2) {
			numSum += 6;
			break;

		}
		else if (choosenum == 3) {
			numSum += 5;
			break;
		}
		else if (choosenum == 4) {
			numSum += 4;
			break;
		}
		else if (choosenum == 5) {
			numSum += 2;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//4��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q4. �� ���� ���� ��, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. �ٸ��� ���� �ɴ´�\n";
		cout << "2. �ٸ��� ����ä ������ �ΰ� �ɴ´�\n";
		cout << "3. �ٸ��� �� ��� �ɴ´�\n";
		cout << "4. �� �� �ٸ��� ���� ��� �ɴ´�\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 6;
			break;
		}
		else if (choosenum == 2) {
			numSum += 4;
			break;

		}
		else if (choosenum == 3) {
			numSum += 2;
			break;
		}
		else if (choosenum == 4) {
			numSum += 1;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//5��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q5. ���� ����� ���� ��������, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ��ſ��� ������ �ʰ� ũ�� ���´�\n";
		cout << "2. ������ �̼Ҹ� ���´�\n";
		cout << "3. ������ ũ�� �ʰ� ���´�\n";
		cout << "4. �Ҹ��� ���� ������ ���´�\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 6;
			break;
		}
		else if (choosenum == 2) {
			numSum += 5;
			break;

		}
		else if (choosenum == 3) {
			numSum += 4;
			break;
		}
		else if (choosenum == 4) {
			numSum += 3;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//6��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q6. ���� ���� �����ϴ� ������?" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ����\n";
		cout << "2. ���� �Ǵ� ��Ȳ\n";
		cout << "3. ��� �Ǵ� ���Ķ�\n";
		cout << "4. ���\n";
		cout << "5. ���Ķ� �Ǵ� ����\n";
		cout << "6. �Ͼ�\n";
		cout << "7. ���� �Ǵ� ȸ��\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 7;
			break;
		}
		else if (choosenum == 2) {
			numSum += 6;
			break;

		}
		else if (choosenum == 3) {
			numSum += 5;
			break;
		}
		else if (choosenum == 4) {
			numSum += 4;
			break;
		}
		else if (choosenum == 5) {
			numSum += 3;
			break;
		}
		else if (choosenum == 6) {
			numSum += 2;
			break;
		}
		else if (choosenum == 7) {
			numSum += 1;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//7��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q7. ���� ����� ���� ���̴� ��ҿ���, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ����ó�� �����ؼ� ����ó�� ���\n";
		cout << "2. ������ ���� ������� �Ѵ�\n";
		cout << "3. �ü� ���� �ʵ��� ������ �ִ´�\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 6;
			break;
		}
		else if (choosenum == 2) {
			numSum += 4;
			break;

		}
		else if (choosenum == 3) {
			numSum += 2;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//8��
	while (true) {
		cout << "\n--------------------------------------------------" << endl;
		cout << "Q8. ���� ���𰡿� ������ ä ������ �ϴٰ� ���� ������" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "1. �޽��� ��ȸ�� �ݰ��� �����Ѵ�\n";
		cout << "2. ¥���� ������ Ƽ�� ���� �ʴ´�\n";
		cout << "3. ¥���̳��� �����Ÿ���\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 6;
			break;
		}
		else if (choosenum == 2) {
			numSum += 4;
			break;

		}
		else if (choosenum == 3) {
			numSum += 2;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//9��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q9. ���� ���� ���� ���ϴ� �����, ����" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ���� ��ٷ� ��� ���� ����\n";
		cout << "2. ���帰 ä�� ���� �� �� ����\n";
		cout << "3. ������ ���� ��ũ�� ����\n";
		cout << "4. �� ���� ���� �ִ� ����\n";
		cout << "5. �Ӹ��� �̺� �ؿ� ���� ����\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 7;
			break;
		}
		else if (choosenum == 2) {
			numSum += 6;
			break;

		}
		else if (choosenum == 3) {
			numSum += 4;
			break;
		}
		else if (choosenum == 4) {
			numSum += 2;
			break;
		}
		else if (choosenum == 5) {
			numSum += 1;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
	//10��
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q10. ���� ��ҿ� ���� �ٴ� ����?" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. ���� �� ���� �ʴ´�\n";
		cout << "2. ���ƿ����ų� �������� ��\n";
		cout << "3. �������� ��\n";
		cout << "4. ���𰡸� ã�� ��\n";
		cout << "5. �ο�ų� �־��� ��\n";
		cout << "6. ��� ���� ������ ��\n";
		cout << "\n�亯�� �Է����ּ���(���ڷ�) : ";
		cin >> choosenum;
		if (choosenum == 1) {
			numSum += 6;
			break;
		}
		else if (choosenum == 2) {
			numSum += 5;
			break;

		}
		else if (choosenum == 3) {
			numSum += 4;
			break;
		}
		else if (choosenum == 4) {
			numSum += 3;
			break;
		}
		else if (choosenum == 5) {
			numSum += 2;
			break;
		}
		else if (choosenum == 6) {
			numSum += 1;
			break;
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���^^" << endl;
		}
	}
}
void personalityTest() {
	int choicenum;

	cout << "\n\n      << ���� �ɸ��׽�Ʈ >> \n\n" << endl;

	cout << "�� �ɸ��׽�Ʈ�� �ܼ��� ��̸� ���� ���̴� �������ֽñ� �ٶ��ϴ�. ����" << endl;
	cout << "�׽�Ʈ�� ������ �غ� �Ǿ��ٸ� ENTERŰ�� �����ּ���...!\n" << endl; getchar();
	cout << "! ! ENTERŰ�� ������ ��ȭ�� �Ѱ��ּ��� ! !\n" << endl;
	cout << "��������? �� �ڱ�~ ����;�� " << endl; getchar();
	cout << "���� :  ���� ����;� �ڱ�� ���� �б����� ���߾�?" << endl; getchar();
	cout << "��? ���� �б����� ���߳İ�?" << endl; getchar();
	cout << "�� ���� ������ �ʹ� ���Ƽ� �Ϸ� ���� ������ �߾�" << endl; getchar();
	cout << "���� : ��¥? �� ������ڴ٤�" << endl; getchar();
	cout << "�¾Ƥ̤�" << endl; getchar();
	cout << ".\n.\n.\n.\n." << endl; getchar();
	cout << "((ģ���� �����̶� �㿡 ��ȭ�� �ϰ� �ִٰ� �ð��� ���� �ʹ� �ʾ ������ �λ縦 �Ϸ��� �մϴ�.))" << endl; getchar();
	cout << "�̶� ����� � �λ縻�� ���� �ǰ���?" << endl; getchar();

	while (true) {
		cout << "   1. ����\n   2. ���� ����\n   3. ���� �� ��\n   4. ������\n" << endl;
		cout << "����� ������ ����� ��ȣ�� �Է����ּ��� : ";
		cin >> choicenum;
		if (choicenum == 1) {
			cout << "\n�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
			cout << "     1���� ������ ���!!!!" << endl;
			cout << "���� ���� ���� ���� ���� ����! " << endl;
			cout << "����� �����ϱ⵵ �ϰ� å�Ӱ��� ���� Ÿ���Դϴ�. �Ż翡 ���� ������ �������. \n�� �� �ο��� �˰� �Ǹ� ���� ���� ������ ���踦 �̾�ϴ�. \n";
			cout << "������ �̷� ������ �е��� ������ �ʹ� ���Ƽ� ���� �� ���� �������� ���� �� �ֽ��ϴ�.\n " << endl;

			break;
		}
		else if (choicenum == 2) {
			cout << "\n�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
			cout << "     2���� ������ ���!!!!" << endl;
			cout << "�̰����� ȣ����� ���� �׳� ����ġ�� ���� ���� ����! " << endl;
			cout << "�� �� ��� ���� �� ���ϴ� ȭ���� ������ Ÿ���Դϴ�. \n������ �ſ� ���ϰ� �米���� �پ�� � ���ӿ� ���� ������ ����Ŀ ������ �մϴ�. \n";
			cout << "������ �̷� ������ ������ ���ϰ� ��д�� �ൿ�Ѵٴ� �� �����̶�� �մϴ�. \n" << endl;

			break;
		}
		else if (choicenum == 3) {
			cout << "\n�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
			cout << "     3���� ������ ���!!!!" << endl;
			cout << "������ �����ϰ� �������� ����! " << endl;
			cout << "�ɰ��� ���� �Ⱦ��ϰ� ���õǰ� �ųʰ� ���Ƽ� ������� �α⸦ ���� �ŷ����� Ÿ���Դϴ�. \n";
			cout << "������ ���� ����鿡�� �����̶�� ������ �� ����� �ϴ� ���� �����̶�� �մϴ�.\n " << endl;

			break;
		}
		else if (choicenum == 4) {
			cout << "\n�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
			cout << "     4���� ������ ���!!!!" << endl;
			cout << "���� ���� �� �� ������������ ���� ����! " << endl;
			cout << "���� �����⿡ ���� Ÿ���Դϴ�. �ݸ鿡 �Ѱ��� ���� �ϴ���� �Ϻ��ϰ� �Ϸ��� �ϴ� ������ ���� �ִٰ� �ϳ׿�. �̷� ����� �ε巴�� ���ϵ��� �ŷ��� ū ����. \n";
			cout << "������ �������̶�� ���� �����Դϴ�\n " << endl;

			break;
		}
		else {
			cout << "��ȣ�� �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���..." << endl;
		}
	}
}
void UnconsciousTest() {
	string people, houseSize, fenceText, onTable, sound;
	bool fence;
	int definition = 0;

	cout << "\n\n      << ���ǽ� �ɸ��׽�Ʈ >> \n\n" << endl;

	cout << "�� �ɸ��׽�Ʈ�� �ܼ��� ��̸� ���� ���̴� �������ֽñ� �ٶ��ϴ�. ����" << endl;
	cout << "�׽�Ʈ�� ������ �غ� �Ǿ��ٸ� ENTERŰ�� �����ּ���...!\n" << endl;
	getchar();
	system("cls");

	//Q1
	cout << "������ �޺�, " << endl;
	getchar();
	cout << "�ż��� �ٶ��� �δ� �Ϻ��� ���� " << endl;
	getchar();
	cout << "����� ���� ǳ��ȭ ���� ��ġ�� ������ �Ȱ� �ֽ��ϴ�. " << endl;
	getchar();
	cout << "		Q1. �̶� ��� �����ִ� ����� �����ΰ���?? " << endl;
	cout << "		�亯�� �Է����ּ��� --->  ";
	getline(cin, people);

	//Q2 -2
	cout << "\n�� �ӿ� �� ����� �װ����� ���� �߰��߽��ϴ�. " << endl;
	getchar();
	cout << "		Q2-1. ����� �߰��� ���� ũ��� ��� �����ΰ���? " << endl;
	cout << "		�亯�� �Է����ּ��� ---> ";
	getline(cin, houseSize);

	cout << "\n		Q2-2. �� ���� ��Ÿ���� �ֳ���? " << endl;
	while (1) {
		cout << "		�ִٰ� �����Ͻø� <<��>>�� ���ٰ� �����Ͻø� <<�ƴϿ�>>�� �Է����ּ��� ---> ";
		cin >> fenceText;
		if (fenceText == "��") {
			fence = true;
			break;
		}
		else if (fenceText == "�ƴϿ�") {
			fence = false;
			break;
		}
	}//while
	//Q3
	cout << "\n���� ������ �ٰ��� ���� " << endl;
	getchar();
	cout << "�� ��ó�� ���̺��� ������ �ֽ��ϴ�. " << endl;
	getchar();
	cout << "		Q3 ���̺� ���� ������ �ֽ��ϱ�? " << endl;
	cout << "		�亯�� �Է����ּ��� ---> ";
	getline(cin, onTable);

	//Q4
	cout << "\n����� ��𼱰� ������� ���Ҹ��� ������ϴ�. " << endl;
	getchar();
	cout << "�� �Ҹ��� ���� ���ϴ�. " << endl;
	getchar();
	cout << "		Q4. �� ���� ��ü�� ����, ��, �ٴ� �߿� �����ΰ���? " << endl;
	while (1) {
		cout << "		<����> <��> <�ٴ�> �� �� ���� �Է����ּ��� ---> ";
		cin >> sound;
		if ((sound == "����") || (sound == "�ٴ�") || (sound == "��")) break;
	}//while
	//Q5
	cout << "\n�� ���� ����� ���� ���纾�ϴ� " << endl;
	getchar();
	cout << "		Q5. ������ �� ����� ���� ������ �����? " << endl;
	while (1) {
		cout << "		�����ϴٸ� <1>�� �������� �ʴٸ� <2>�� �Է����ּ��� ---> ";
		cin >> definition;
		if ((definition == 1) || (definition == 2)) 	break;
	}//while

	//���
	system("cls");
	cout << "\n\n      << ���ǽ� �ɸ��׽�Ʈ ��� >> \n\n" << endl;
	cout << "	Q1. �̶� ��� �����ִ� ����� �����ΰ���?? " << endl;
	getchar();
	cout << "�̶� ����� < " << people << " > �� ����� �λ����� ���� �����ϴٰ� �����ϴ� ����Դϴ�. \n" << endl;
	getchar();

	cout << "\n	Q2-1. ����� �߰��� ���� ũ��� ��� �����ΰ���? " << endl;
	getchar();
	cout << "���� ũ��� ����� �߸��� ũ�⸦ ��Ÿ���ϴ�\n "; //getchar();
	cout << " < " << houseSize << " > ��� ����� ����� �߸��� ũ��� �����? ����\n" << endl;
	getchar();

	cout << "\n	Q2-2. �� ���� ��Ÿ���� �ֳ���? " << endl;
	getchar();
	cout << "��Ÿ���� ���� ���� �������� ����, ��Ÿ���� �ִ� ���� �ұ����� �����̶�� �մϴ�. \n";
	if (fence == 1) {
		cout << "��Ÿ���� �ִٰ� ������ ���! ��� �ұ����� ������ ������ �ֱ���!\n" << endl;
		getchar();
	}
	else {
		cout << "��Ÿ���� ���ٰ� ������ ���! ��� �������� ������ ������ �ֱ���!\n" << endl;
		getchar();
	}

	cout << "\n	Q3 ���̺� ���� ������ �ֽ��ϱ�? " << endl;
	getchar();
	cout << "���̺� ���� < " << onTable << " >�� �����ִٰ� �����ϼ̱���\n ";
	cout << "���̺� ���� ���� ������ ���� ���� ���� �������� �����ϴ�. Ư�� ���̳� �����̶�� ����� ����� �ູ�� ����̶�� �ϳ׿� ���� " << endl;
	getchar();


	cout << "\n	Q4. �� ���� ��ü�� ����, ��, �ٴ� �߿� �����ΰ���? " << endl;
	getchar();
	cout << " < " << sound << " > ��� ����ϼ̳׿�.";
	cout << "����� ������ ũ�⸦ �˷��ִ� �����̾����ϴ�. \n ���� �� �ϼ��� ������ ū ��� �Դϴ�!^^ (���� < �� < �ٴ�)\n " << endl;
	getchar();

	cout << "\n	Q5. ������ �� ����� ���� ������ �����? " << endl;
	getchar();
	cout << "���� ������ 1������ ������ ������� �����Դϴ�!\n���� �����ϰ� ���� ���� ����� ���̶�� �ϳ׿�. \n";
	if (definition == 1) {
		cout << "��� < " << people << " > ��(��) ����� ���̳׿�!!" << endl;
		getchar();
	}
	else
		cout << "< " << people << " > ��(��) ������ �ʴ� ���ΰ���? ����" << endl;
	getchar();

	cout << "���ǽ� �ɸ��׽�Ʈ�� ������ ��̸� ���� ���̴� ��̷θ� ���ּ��� ����\n�����մϴ� ���� " << endl;
	getchar();

}
int enneagram() {
	string question1[3][6] = {
		{ //A
		"���� �������� ���̰� �ڱ������� �� �Ѵ�.",
		"���� ��ǥ�� �����ϰ� �� ���� ������ ������. �׸��� �װ��� ����Ǳ⸦ ���Ѵ�.",
		"���� ������ �ɾ� �ִ� ���� �������� �ʴ´�.",
		"���� ū ���� �����ϰ� ������� ����ϱ⸦ ���Ѵ�.",
		"���� ���� ����� �������� ������ ������� ���� �����ϴ� �͵� �������� �ʴ´�.",
		"�밳�� ��� ���� ���� ���ϴ� ���� �� �˰� �ִ�." },
		{ //B
		"���� �����ϰ� ȥ�� �ִ� ���� �����Ѵ�.",
		"���� ��ȸ���� Ȱ���� ���Ǹ� ���� ������ ��ü�� �� �ǰ��� ���ϰ� �������� �ʴ´�.",
		"���� �տ� �����ų� �ٸ� ����� �����ϴ� ���� �׸� �������� �ʴ´�.",
		"������� ���� ���󰡶�� ���Ѵ�.",
		"�� ����� ���� �ȿ����� ���� ��̷ο� �ϵ��� ��������.",
		"���� �������̰� Ȱ�����̱��⺸�ٴ� ������ �����̴�." },
		{ //C
		"���� ���� å�Ӱ��� ���ϰ� ������̴�.",
		"���� �� �ǹ��� ������ ���� �� ���� ����� ���ڴ�.",
		"���� ������� �ʿ��� �� �׵��� ���� ���� �� �ڸ��� �ִٴ� ���� �˾� �־����� ���ڴ�.",
		"�̵��ݾ� ���� ������� ���� �˾� �ֵ� �˾� ���� �ʵ� �׵��� ���� ū ����� �Ѵ�.",
		"���� �� �ڽ��� ����� ������ �ʴ´�.",
		"���� �ؾ� �� ���� �� ������ �ð��� ���� �޽��� ���ϰų� ���� ���ϴ� ���� �Ѵ�." }
	};
	string question2[3][5] = {
		{ //X
		"���� �밳 �������� �ڼ��� ��Ȱ�ϸ�, ��� ���� ������ ������ ������ Ǯ���ٰ� ������.",
		"���� ���� ������ ���� �� �ִ� ���� ���� ����� ã�´�.",
		"���� ������ �Բ� �ϰ� ������� �ູ�������� ���� ���� �����Ѵ�.",
		"���� ���� ���������� �ٸ� ����鵵 �� �����⸦ �ٶ���.",
		"���� �ٸ� ����鿡�� �׻� ���������� ���̰��� ����ϱ� ������ ���δ� �� �ڽ��� ������ �ٷ�� ���� �̷�⵵ �Ѵ�." },
		{ //Y
		"��κ��� ������� ���� ��� �Ϳ� ���� �Ҹ��� ���� �ִٰ� �����Ѵ�.",
		"���� ������ �Բ� ���� �� �׵��� � �������, ������ ����� �� �ִ����� �˱� ���Ѵ�.",
		"� �Ͽ� ���� ȭ�� ���� �� ���� ������� �װͿ� ���� �����ϰ� ����ŭ �� ���� �ذ��Ϸ��� ����� �ֱ⸦ ���Ѵ�.",
		"���� ��Ģ�� �˰� �ִ�. ������ ������� ���� ������ �϶�� �����ϴ� ���� �������� �ʴ´�.",
		"���� �� ������ �����ϱ⸦ ���Ѵ�." },
		{ //Z
		"���� �����θ� �� �����ϰ� �����̴�.",
		"���� ������ �ٷ�� ���� ��������� �ʴ´�. ���� ȿ�����̰� �Ϻ��ϰ� ���� ó���ϸ� ȥ�� ���ϴ� ���� �����Ѵ�.",
		"������ �������� ������ ���� �� ���� �� ��Ȳ�� ������ �������� �ʵ��� �Ѵ�.",
		"� ������� ���� �ʹ� ���� ���ڿ��ϴٰ� �������� ���� ���� ������ �߿��� ���� �׸�ġ�� ���� �ʴ�.",
		"���� ������� ���� ȭ���� �� �� ��κ��� ��� ������ ������ �ʴ´�." }
	};
	string desc[9] = {
		"�Ϻ��������Դϴ�.\n��Ģ���̰� ��ǥ�� �и��ϸ�, �ڽ��� �� �����ϰ� �Ϻ����� ������ �ֽ��ϴ�.",
		"������ �ϴ� ����Դϴ�.\n�����ϰ� �ڽ��� ������ �� �巯����, ������� ��̰� �� �ְ� �������� ���մϴ�.",
		"�����ϴ� ����Դϴ�.\n������ ���ϰ� �پ�ٴϸ�, �ڽ��� �̹����� ������ �����ϴ�.",
		"�����������Դϴ�.\nǥ������ �ְ� �����̸�, �ڽ��� ���鿡 ���� �����������ϴ�.",
		"Ž�����Դϴ�.\n�������� �ְ� â�����̸� ȥ�� ������ �ֱ⸦ �����ϰ� �ڽ��� ������ �� �巯���� �ʽ��ϴ�.",
		"����� ����Դϴ�.\nå�Ӱ��ְ� �ǽɰ� �Ҿ��� ������, ����鿡�� ȣ���� �ݴϴ�.",
		"�������� ����Դϴ�.\n�������̰� �����������, ����� ���� �길�մϴ�.",
		"�����ϴ� ����Դϴ�.\n�ڽŰ��ְ� ��ܷ� ������, ���������� ������ �¼��⸦ �����մϴ�.",
		"��ȭ�������Դϴ�.\n�������̰� ������ ������ �ָ�, �� �����ϰ� �ڽſ��� �����մϴ�."
	};
	int result[3][3] = {
		{ 7, 8, 3 },
		{ 9, 4, 5 },
		{ 2, 6, 1 }
	};
	int cnt[2][3] = { 0 }, n;

	cout << "**********���Ͼ�׷� ���� �׽�Ʈ**********" << endl;
	cout << "�־��� ������ 1. �� / 2. �ƴϿ� �� ����ϼ���\n" << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			cout << question1[i][j] << endl;
			cout << "1. �� / 2. �ƴϿ� : ";
			cin >> n;
			if (n == 1)
				cnt[0][i]++;
			cout << endl;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			cout << question2[i][j] << endl;
			cout << "1. �� / 2. �ƴϿ� : ";
			cin >> n;
			if (n == 1)
				cnt[1][i]++;
			cout << endl;
		}
	}
	cout << endl;

	int max1 = 0, max2 = 0, index1, index2;
	for (int i = 0; i < 3; i++) {
		if (cnt[0][i] > max1) {
			max1 = cnt[0][i];
			index1 = i;
		}
		if (cnt[1][i] > max2) {
			max2 = cnt[1][i];
			index2 = i;
		}
	}
	cout << "����� " << result[index1][index2] << "�� ������ " << desc[result[index1][index2] - 1] << endl;

	return result[index1][index2];
}
void todayFortune() {
	string name[11] = { "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" };
	string food[17] = { "���", "ī��", "�쵿", "��â", "����", "����", "���" , "������", "�Ľ�Ÿ", "ġŲ", "����" , "ȸ", "¥���", "����", "�ұ���", "�ܹ���", "�ʹ�" };
	string color[13] = { "����", "��Ȳ", "���", "�ʷ�", "����", "�Ķ�", "�ϴ�", "��", "����", "�Ͼ�", "����", "ȸ", "��ȫ" };
	int year, month, day, total, today;
	time_t t;
	struct tm now;
	t = time(NULL);
	localtime_s(&now, &t);
	today = now.tm_mday;

	cout << "��������� �Է��ϼ���!" << endl;
	cout << "�⵵ : ";
	cin >> year;
	cout << "�� : ";
	cin >> month;
	cout << "�� : ";
	cin >> day;
	total = year + month + day + today;

	cout << "\n������ ��� ��� ���Դϴ�";
	for (int i = 0; i < 3; i++) {
		Sleep(1000);
		cout << ".";
	}
	Sleep(1000);
	cout << "\n\n���� �����ؾ� �� ����� " << name[total % 11] << name[(total + today) % 11] << "�Դϴ�.." << endl;
	cout << "���� ���� ���ƾ� �� ������ " << food[total % 17] << "�Դϴ٤Ф�" << endl;
	cout << "������ ����� ���� " << color[total % 13] << "���Դϴ�!" << endl;
}
int count(int* da, int* dam, int* uoo, int* jum) {
	int n;
	cout << "��ȣ�� �Է��ϼ��� : ";
	cin >> n;
	switch (n) {
	case 1:
		(*da)++;
		return 1;
	case 2:
		(*dam)++;
		return 1;
	case 3:
		(*uoo)++;
		return 1;
	case 4:
		(*jum)++;
		return 1;
	default:
		cout << "�߸� �Է��߽��ϴ�.. �ٽ� �Է��ϼ���" << endl;
		return 0;
	}
}
void gijilresult(int* da, int* dam, int* uoo, int* jum) {
	cout << "***** ��� *****" << endl;
	cout << "����� ������ ���� : " << *da << endl;
	cout << "����� ������ ���� : " << *dam << endl;
	cout << "����� ����� ���� : " << *uoo << endl;
	cout << "����� ������ ���� : " << *jum << endl;
}
void gijiltest() {
	int da = 0, dam = 0, uoo = 0, jum = 0;
	string question[40] = {
		"1. ������ �ִ�			2. �������̴�			3. �м����̴�			4. ���뼺�ִ�",
		"1. �㼼�� �θ���		2. �Ǽ��� �θ���		3. ���Ⱑ ����			4. ��ǥ���ϴ�",
		"1. ��Ȱ�ϴ�			2. ����� �ִ�			3. ���� �ִ�			4. ����ϴ�",
		"1. ������ ����			2. �������� ����		3. �뼭���� �ʴ´�		4. ������ ����",
		"1. �米���̴�			2. ������ ���ϴ�		3. ������̴�			4. �����Ѵ�",
		"1. �� ���� ��Ǯ���Ѵ�	2. �Ž�����			3. ���� ǰ��		4. ����� ����",
		"1. �ŷ��ִ�			2. ����� �ִ�			3. ���ؽ� ����			4. ������ �����Ѵ�",
		"1. �Ǹ����� �ִ�		2. ������̴�			3. ��ٷӴ�			4. �η����ϴ�",
		"1. �����ϴ�			2. �ɷ��� ����ϴ�		3. �����Ѵ�			4. �ﰡ��",
		"1. �߰��� ������		2. �����ϴ�			3. �ڽŰ��� ����		4. ��ܷ��� ����",
		"1. �ų��ϴ� ��			2. �������� ��			3. �ΰ��� ��			4. �������� ��",
		"1. ������ �� ����		2. ����ǥ���� ����		3. �α� ����			4. �������� �ʴ´�",
		"1. ����ϴ�			2. �������̴�			3. ��ȹ�ϴ�			4. ������ �ִ�",
		"1. �Ǵ´�� �Ѵ�		2. �ϰ��ϴ�			3. �Ҹ��� ���� ��			4. �����̴� ��",
		"1. �浿���� ��			2. Ȯ���ϴ� ��			3. ��ȹ�� ������		4. �����ϴ�",
		"1. �����ϴ�			2. �����ϴ�			3. �������̴�			4. �����Ӵ�",
		"1. ��õ���̴�			2. �����ϴ�			3. ���� �ִ�			4. ����� �ִ�",
		"1. ���� �г��Ѵ�		2. ������ �����Ѵ�		3. �ڽ��� �ݸ��Ѵ�		4. ��ǥ�� ����",
		"1. ����� �ִ�			2. �ְ��� �ѷ��ϴ�		3. �Ž��ϴ�			4. �������̴�",
		"1. �ǻ����̴�			2. �ڸ��Ѵ�			3. �������̴�			4. �����ϴ�",
		"1. ��̴�			2. ���� ����			3. �����ϴ�			4. �ܱ����̴�",
		"1. Ī���� �ٶ���		2. �Ϲ����� ��			3. �ڷ� �������� ��		4. �����ϴ�",
		"1. ����ϴ�			2. �ڽŰ� �ִ�			3. ��ȭ���̴�			4. �����Ǵ�",
		"1. ���� ����			2. �����ϴ�			3. �����ϴ�			4. �ҽ��ϴ�",
		"1. �ݷ��ϴ� ��			2. �������̴�			3. �̻����̴�			4. �Ž����� �ʴ´�",
		"1. �������ϴ�			2. �����ϴ�			3. �����ϴ�			4. Ȯ���� ����",
		"1. ǥ���ϴ� ��			2. ��ȣ�ϴ�			3. �����ϴ� ��			4. �����ϰ� ����Ѵ�",
		"1. �ϰ����� ����		2. �������� ���ϴ�		3. �������̴�		4. �������ϴ�",
		"1. ���� ��︰��		2. �ൿ�� ��			3. ������ �����Ѵ�		4. �����ϴ� ��",
		"1. �������� ��			2. �����ϴ�			3. ����� ��			4. �߾�Ÿ���",
		"1. ���ϱ� �����Ѵ�		2. ���� ������			3. ��� ���� ��			4. �����ϴ�",
		"1. �����Ѵ�			2. ������ ����			3. ȸ�����̴�			4. ������",
		"1. �������̴�			2. å�Ӱ��ִ�			3. �漺������ ��		4. �� ��´�",
		"1. �ò����� ��			2. �����Ѵ�			3. �ܷο� ��			4. ������ ��",
		"1. �������̴�			2. ������ �ִ�			3. �������̴�			4. �����ϴ� ��",
		"1. �길�� ��			2. ���̰� ���ϴ�		3. �ǽ� ���� ��			4. �����ϴ�",
		"1. �α� �ִ�			2. �������̴�			3. �Ϻ��� �߱��Ѵ�		4. ����ϴ�",
		"1. ħ������ ���� ��	2. ����ϴ�			3. ����� ���� ��			4. �������� �ϴ� ��",
		"1. Ȱ�� �ִ�			2. ����ϴ�			3. ���ǹٸ���			4. �ߵ����̴�",
		"1. ����������			2. ��������		3. �������̴�			4. Ÿ���Ѵ�"
	};
	cout << "***** ����ũ���׽��� ���� �׽�Ʈ *****" << endl;
	cout << "��� : �� �׸� �� ���ο��� ���� ������ �׸��� ��ȣ�� �Է��ϼ��� !" << endl << endl;
	for (int i = 0; i < 20; i++) {
		cout << question[i] << endl;
		if (!(count(&da, &dam, &uoo, &jum)))
			i--;
		cout << endl;
	}
	system("cls");
	gijilresult(&da, &dam, &uoo, &jum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	while (true) {
		titleDraw();
		int menuCode = menuDraw();
		if (menuCode == 0) {
			int testCode = testMenuDraw(); //�׽�Ʈ ����						
			if (testCode == 0) {
				system("cls");
				boredQuestionPrint();
				cout << "\n-----------------------------------------------------------" << endl;
				cout << "�� 10���� ������ ������ �������ϴ�!! " << endl;
				cout << "�׽�Ʈ ����� ���� �غ� �Ǿ�����~? �׷� �׽�Ʈ ��� �����帮�ڽ��ϴ�!" << endl; getchar();
				cout << "-----------------------------------------------------------" << endl;
				boredResultPrint();
				cout << "-----------------------------------------------------------" << endl;
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 1) {		//����
				system("cls");
				personalityTest();
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 2) {		//���ǽ�
				system("cls");
				UnconsciousTest();
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 3) {		//�ִϾ�׷�
				system("cls");
				dbconn();
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}

			}
			else if (testCode == 4) {		//�����½�Ʈ
				system("cls");
				gijiltest();
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 5) {		//�����ǿ
				system("cls");
				todayFortune();
				cout << "\n<< �ٸ� �׽�Ʈ�� space bar�� ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
		}

		else if (menuCode == 1) { //���α׷� �Ұ�
			infoDraw();
		}

		else if (menuCode == 2) { //����
			fileout();
			while (1) {
				if (keyControl() == SUBMIT) {
					break;
				}
			}
		}

		else if (menuCode == 3) { //����
			if (filein() == 1) {
				cout << "���� �ۼ��� �Ϸ�Ǿ����ϴ�. �����մϴ�.\n������ �� ã���ּ���~!" << endl;
				return 0;
			}
			else {
				cout << "������ �ۼ����� �ʾҽ��ϴ�. �����մϴ�.\n������ �� ã���ּ���~!" << endl;
				return 0;
			}
		}

		system("cls");



		//return 0;
	}
}