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
#define SUBMIT 4 //스페이스바 선택

static int numSum;			//bored에서 사용

const char* host = "localhost";			//db에서 사용
const char* user = "root";
const char* pw = "mirim2";
const char* db = "heeda";

int keyControl(); //키보드 입력값 리턴
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
int count(int* da, int* dam, int* uoo, int* jum);		//기질테스트에서 사용
void gijilresult(int* da, int* dam, int* uoo, int* jum);
void gijiltest();
void dbconn();

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void titleDraw() {
	gotoxy(2, 3); printf("■");
	gotoxy(2, 4); printf("■");
	gotoxy(3, 5); printf("■");
	gotoxy(3, 6); printf("■");
	gotoxy(4, 7); printf("■");
	gotoxy(4, 8); printf("■");
	gotoxy(5, 9); printf("■");
	gotoxy(5, 10); printf("■");
	gotoxy(7, 11); printf("■");
	gotoxy(9, 10); printf("■");
	gotoxy(9, 9); printf("■");
	gotoxy(10, 8); printf("■");
	gotoxy(10, 7); printf("■");
	gotoxy(11, 6); printf("■");
	gotoxy(12, 6); printf("■");
	gotoxy(13, 7); printf("■");
	gotoxy(13, 8); printf("■");
	gotoxy(14, 9); printf("■");
	gotoxy(14, 10); printf("■");
	gotoxy(16, 11); printf("■");
	gotoxy(18, 10); printf("■");
	gotoxy(18, 9); printf("■");
	gotoxy(19, 8); printf("■");
	gotoxy(19, 7); printf("■");
	gotoxy(20, 6); printf("■");
	gotoxy(20, 5); printf("■");
	gotoxy(21, 4); printf("■");
	gotoxy(21, 3); printf("■");

	gotoxy(24, 3); printf("■");
	gotoxy(24, 4); printf("■");
	gotoxy(24, 5); printf("■");
	gotoxy(24, 6); printf("■");
	gotoxy(24, 7); printf("■");
	gotoxy(24, 8); printf("■");
	gotoxy(24, 9); printf("■");
	gotoxy(24, 10); printf("■");
	gotoxy(24, 11); printf("■");
	gotoxy(26, 7); printf("■");
	gotoxy(27, 6); printf("■");
	gotoxy(29, 6); printf("■");
	gotoxy(31, 7); printf("■");
	gotoxy(31, 8); printf("■");
	gotoxy(31, 9); printf("■");
	gotoxy(31, 10); printf("■");
	gotoxy(31, 11); printf("■");

	gotoxy(40, 11); printf("■");
	gotoxy(38, 11); printf("■");
	gotoxy(36, 11); printf("■");
	gotoxy(35, 10); printf("■");
	gotoxy(34, 9); printf("■");
	gotoxy(35, 8); printf("■");
	gotoxy(36, 7); printf("■");
	gotoxy(38, 7); printf("■");
	gotoxy(40, 7); printf("■");
	gotoxy(41, 8); printf("■");
	gotoxy(42, 9); printf("■");
	gotoxy(41, 10); printf("■");

	gotoxy(51, 8); printf("■");
	gotoxy(49, 8); printf("■");
	gotoxy(48, 9); printf("■");
	gotoxy(48, 10); printf("■");
	gotoxy(49, 11); printf("■");
	gotoxy(51, 11); printf("■");
	gotoxy(52, 10); printf("■");
	gotoxy(52, 9); printf("■");
	gotoxy(54, 7); printf("■");
	gotoxy(54, 8); printf("■");
	gotoxy(54, 9); printf("■");
	gotoxy(54, 10); printf("■");
	gotoxy(55, 11); printf("■");

	gotoxy(58, 11); printf("■");
	gotoxy(58, 10); printf("■");
	gotoxy(58, 9); printf("■");
	gotoxy(58, 8); printf("■");
	gotoxy(58, 7); printf("■");
	gotoxy(60, 9); printf("■");
	gotoxy(61, 8); printf("■");
	gotoxy(63, 8); printf("■");
	gotoxy(64, 9); printf("■");
	gotoxy(65, 10); printf("■");
	gotoxy(65, 11); printf("■");
	gotoxy(66, 9); printf("■");
	gotoxy(67, 8); printf("■");
	gotoxy(69, 8); printf("■");
	gotoxy(70, 9); printf("■");
	gotoxy(70, 10); printf("■");
	gotoxy(70, 11); printf("■");

	gotoxy(76, 11); printf("■");
	gotoxy(78, 11); printf("■");
	gotoxy(80, 11); printf("■");
	gotoxy(78, 10); printf("■");
	gotoxy(78, 9); printf("■");
	gotoxy(78, 8); printf("■");
	gotoxy(78, 7); printf("■");
	gotoxy(78, 6); printf("■");
	gotoxy(78, 5); printf("■");
	gotoxy(78, 4); printf("■");
	gotoxy(76, 3); printf("■");
	gotoxy(78, 3); printf("■");
	gotoxy(80, 3); printf("■");
}
int menuDraw() {
	int x = 31;
	int y = 16;
	gotoxy(x - 2, y); cout << "▶   테스트 시작하기";
	gotoxy(x, y + 1); cout << "   프로그램 소개";
	gotoxy(x, y + 2); cout << "   방명록 보러 가기  ";
	gotoxy(x, y + 3); cout << "   종료  ";

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 16) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << "▶";
			}
			break;
		}

		case DOWN: {
			if (y < 19) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << "▶";
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
	gotoxy(x - 2, y); cout << "▶   심심할 때 하는 심리 테스트";
	gotoxy(x, y + 1); cout << "   성격을 알아보는 심리 테스트";
	gotoxy(x, y + 2); cout << "   무의식 심리 테스트  ";
	gotoxy(x, y + 3); cout << "   에니어그램 유형 테스트  ";
	gotoxy(x, y + 4); cout << "   기질 테스트  ";
	gotoxy(x, y + 5); cout << "   오늘의 운세  ";


	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 10) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << "▶";
			}
			break;
		}

		case DOWN: {
			if (y < 16) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << "▶";
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
	cout << "        기질테스트부터 성격테스트까지 각종 테스트 종합 모음 어플" << endl;
	cout << "            +) 테스트 결과와 해설까지 제공한다규~!!~! \n\n" << endl;
	cout << "\n\n                              << Who am I 개발자 소개 >>" << endl;
	cout << "  ♥ 윤희나 ♥ 2209" << endl;
	cout << "  못생김ㅋ\n" << endl;
	cout << "  ♥ 최다연 ♥ 2216" << endl;
	cout << "  넘 귀여워서 지구 뿌심><\n" << endl;
	cout << "  \n\n(이전 화면으로 가고 싶으면 스페이스바 눌러)\n" << endl;
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
	cout << "<< 방명록 작성 >>" << endl;
	cout << "이름을 입력하세요\n-> ";
	cin >> userName;
	while (true) {
		cout << "별점을 입력하세요 (5점 만점)\n-> ";
		cin >> starNum;
		if (starNum >= 1 && starNum <= 5)
			break;
		else
			cout << "입력 형식이 올바르지 않습니다. 다시 입력해주세요....\n";
	}
	cout << "한줄평을 남겨주세요\n-> ";
	getline(cin, impression);
	getline(cin, impression);


	fout << setw(13) << userName << setw(10) << starNum << setw(40) << impression << endl;
	cout << setw(13) << userName << setw(10) << starNum << setw(40) << impression << endl;
	cout << endl;
	cout << "감사합니다.";

	return 1;
}
void fileout() {
	system("cls");
	string line;

	ifstream	fin;

	fin.open("guestBook.txt");

	cout << "\n==============================방명록=============================\n" << endl;
	cout << "	이름		평점			한줄평			\n" << endl;
	while (getline(fin, line)) {
		cout << line << endl;
	}
	fin.close();
	cout << "\n<메인 화면으로 돌아가시려면 space bar를 눌러주세요...>";
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
		cout << "에러" << mysql_errno(&conn) << mysql_error(&conn);
	}
	else
	{
		if (mysql_select_db(&conn, db))
		{
			cout << "에러" << mysql_errno(&conn) << mysql_error(&conn);
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
					cout << "당신을 나타내는 단어는 " << sql_row[2] << "입니다!" << endl;
					cout << "마지막으로 " << sql_row[3] << endl;
				}
			}
			mysql_free_result(sql_result);
		}
		mysql_close(connection);
	}
}
void boredResultPrint() {
	if (numSum <= 20) {
		cout << "남들이 보는 당신은 소심하고 우유부단합니다. " << endl;
		cout << "본인의 일도 누군가가 대신해서 결정해줘야만 하고, " << endl;
		cout << "타인이나 어떤 일에 연루되는 것을 피하는 사람입니다." << endl;
		cout << "또한, 걱정을 사서 하는 타입이기도 합니다." << endl;
		cout << "당신을 잘 모르는 남들은 당신을 지루하다고 생각하기도 합니다.\n" << endl;
	}
	else if (numSum >= 21 && numSum <= 30) {
		cout << "남들이 보는 당신은 집요하며 깐깐한 사람으로" << endl;
		cout << "신중하고 조심스러워하며 느리지만 발전하는 편입니다." << endl;
		cout << "당신이 무슨 일인가 충동적으로 하는 모습을 본다면" << endl;
		cout << "친구들이 충격을 받을지도 모릅니다. " << endl;
		cout << "무슨 일이든 꼼꼼히 계획하며 다음 결정을 하는 것을 선호합니다." << endl;
		cout << "깐깐하기 때문에 NO라고 말할 수 있는 사람이기도 합니다." << endl;
	}
	else if (numSum >= 31 && numSum <= 40) {
		cout << "남들이 보는 당신은 현명하고 신중하며 현실적입니다." << endl;
		cout << "사람을 사귈 때 급하거나 가볍게 접근하지 않으며" << endl;
		cout << "가까워진 사람에게는 매우 잘해주시며 자신도 같은 대우를" << endl;
		cout << "해주기를 기대합니다. 당신의 참모습을 아는 사람들은 " << endl;
		cout << "당신의 신뢰를 흔드는 것이 어렵다는 것과 " << endl;
		cout << "그 신뢰가 무너지면 다시 되돌리기 어렵다는 것을 알고 있을 겁니다." << endl;
	}
	else if (numSum >= 41 && numSum <= 50) {
		cout << "남들이 보는 당신은 매우 매력 있는 타입이기도 하며," << endl;
		cout << "때로는 이성적이면서도 즐거운 사람이라고 생각합니다." << endl;
		cout << "주위의 이목을 사로잡는 사람이지만 적당한 눈치도 있으며" << endl;
		cout << "교만해지지 않는 사람이기도 합니다. 또한 다정하며" << endl;
		cout << "친절하고, 이해심이 많아 다른 사람을 도울 줄 아는 " << endl;
		cout << "분위기 메이커 역할을 하기도 합니다." << endl;
	}
	else if (numSum >= 51 && numSum <= 60) {
		cout << "남들이 보는 당신은 변덕스러우며, 충동적인 사람이라고" << endl;
		cout << "생각합니다. 또한 리더형으로 빠른 결정을 내릴 줄 아는" << endl;
		cout << "사람이기도 합니다. 무엇이든 시도해볼 줄 아는 과감한 " << endl;
		cout << "모험형 타입으로 겁이 없으며 호기심이 매우 많습니다." << endl;
		cout << "당신의 친구들은 당신이 발하는 강렬함에 이끌립니다." << endl;
	}
	else if (numSum <= 60) {
		cout << "남들이 보는 당신은 취급 주의형이라고 생각하며" << endl;
		cout << "약간의 허영심이 있고 남을 지배하고 싶은 욕구가 강합니다." << endl;
		cout << "남이 해주는 칭찬에 약하지만, 막상 본인은 남들에게" << endl;
		cout << "칭찬을 잘해주지 못하는 양면의 성격이 있습니다." << endl;
		cout << "의외로 당신의 당당한 성격을 부러워하고 우러러보는" << endl;
		cout << "사람들이 있지만, 당신은 그러한 사람들은 잘 보지 못합니다." << endl;
	}
}
void boredQuestionPrint() {
	int choosenum = 0;
	cout << "\n\n         << 심리테스트 >>\n\n#남들이_생각한_나는?\n";
	cout << " ! 질문은 총 10개로 자신에 가장 가깝다고 생각하는 보기를 고르시면 됩니다 !\n\n" << endl;
	//1번 
	while (true) {
		cout << "-------------------------------------------" << endl;
		cout << "Q1. 하루 중 기분이 가장 좋은 시간대는?" << endl;
		cout << "1. 아침\n2. 오후나 이른 저녁\n3. 늦은 밤" << endl;
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}

	}
	//2번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "\nQ2. 나는 걸을 때, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 머리를 들고, 정면으로 바라보며 덜 빠르게 덜 걷는다\n";
		cout << "2. 보폭을 넓게, 뻘리 걷는다\n";
		cout << "3. 보폭을 좁게, 빨리 걷는다\n";
		cout << "4. 바닥을 보며 덜 빠르게 걷는다\n";
		cout << "5. 아주 느리게 걷는다\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//3번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q3. 나는 사람들과 이야기할 때, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 생대방을 터치하며\n";
		cout << "2. 내 몸을 만지작 거리거나 내 머리를 만지며\n";
		cout << "3. 한 손이나 양 손을 허리에 올리고\n";
		cout << "4. 내 팔짱을 끼고 서서\n";
		cout << "5. 두 손을 마주 잡고\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//4번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q4. 난 편히 앉을 때, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 다리를 꼬고 앉는다\n";
		cout << "2. 다리를 곱힌채 나란히 두고 앉는다\n";
		cout << "3. 다리를 쭉 펴고 앉는다\n";
		cout << "4. 한 쪽 다리를 접어 깔고 앉는다\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//5번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q5. 나는 재밌을 일이 생겼을때, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 즐거움을 숨기지 않고 크게 웃는다\n";
		cout << "2. 가벼운 미소를 짓는다\n";
		cout << "3. 웃지만 크지 않게 웃는다\n";
		cout << "4. 소리를 내지 않으며 웃는다\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//6번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q6. 내가 가장 좋아하는 색깔은?" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 검정\n";
		cout << "2. 빨강 또는 주황\n";
		cout << "3. 노랑 또는 연파랑\n";
		cout << "4. 녹색\n";
		cout << "5. 진파랑 또는 보라\n";
		cout << "6. 하양\n";
		cout << "7. 갈색 또는 회색\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//7번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q7. 나는 사람이 많이 모이는 장소에서, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 관종처럼 등장해서 관종처럼 논다\n";
		cout << "2. 차분히 들어가서 사람구경 한다\n";
		cout << "3. 시선 끌지 않도록 조용히 있는다\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//8번
	while (true) {
		cout << "\n--------------------------------------------------" << endl;
		cout << "Q8. 나는 무언가에 집중한 채 열심히 하다가 방해 받으면" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "1. 휴식의 기회를 반갑게 맞이한다\n";
		cout << "2. 짜증이 나지만 티를 내진 않는다\n";
		cout << "3. 짜증이나서 투덜거린다\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//9번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q9. 내가 잠들기 직전 취하는 포즈는, 보통" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 몸을 톡바로 펴고 누운 포즈\n";
		cout << "2. 엎드린 채로 몸을 쭉 편 포즈\n";
		cout << "3. 옆으로 누워 웅크린 포즈\n";
		cout << "4. 한 팔을 베고 있는 포즈\n";
		cout << "5. 머리를 이불 밑에 넣은 포즈\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
	//10번
	while (true) {
		cout << "\n-------------------------------------------" << endl;
		cout << "Q10. 내가 평소에 자주 꾸는 꿈은?" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 꿈을 잘 꾸지 않는다\n";
		cout << "2. 날아오르거나 떠오르는 꿈\n";
		cout << "3. 떨어지는 꿈\n";
		cout << "4. 무언가를 찾는 꿈\n";
		cout << "5. 싸우거나 애쓰는 꿈\n";
		cout << "6. 기분 좋은 느낌의 꿈\n";
		cout << "\n답변을 입력해주세요(숫자로) : ";
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
			cout << "올바른 값을 입력해주세요^^" << endl;
		}
	}
}
void personalityTest() {
	int choicenum;

	cout << "\n\n      << 성격 심리테스트 >> \n\n" << endl;

	cout << "이 심리테스트는 단순히 재미를 위한 것이니 참고해주시기 바랍니다. ㅎㅎ" << endl;
	cout << "테스트를 진행할 준비가 되었다면 ENTER키를 눌러주세요...!\n" << endl; getchar();
	cout << "! ! ENTER키를 눌러서 대화를 넘겨주세요 ! !\n" << endl;
	cout << "여보세요? 응 자기~ 보고싶어ㅠ " << endl; getchar();
	cout << "애인 :  나도 보고싶어 자깅ㅠ 오늘 학교에서 뭐했어?" << endl; getchar();
	cout << "나? 오늘 학교에서 뭐했냐고?" << endl; getchar();
	cout << "음 오늘 과제가 너무 많아서 하루 종일 과제만 했어" << endl; getchar();
	cout << "애인 : 진짜? ㅠ 힘들었겠다ㅠ" << endl; getchar();
	cout << "맞아ㅜㅠ" << endl; getchar();
	cout << ".\n.\n.\n.\n." << endl; getchar();
	cout << "((친구나 연인이랑 밤에 통화를 하고 있다가 시간을 보니 너무 늦어서 마지막 인사를 하려고 합니다.))" << endl; getchar();
	cout << "이때 당신은 어떤 인사말을 말한 건가요?" << endl; getchar();

	while (true) {
		cout << "   1. 잘자\n   2. 내일 보자\n   3. 좋은 꿈 꿔\n   4. 끊을게\n" << endl;
		cout << "당신이 선택한 대답의 번호를 입력해주세요 : ";
		cin >> choicenum;
		if (choicenum == 1) {
			cout << "\n★★★★★★★★★★★★★★★★★★" << endl;
			cout << "     1번을 선택한 당신!!!!" << endl;
			cout << "겉을 보나 속을 보나 알찬 성격! " << endl;
			cout << "당신은 성실하기도 하고 책임감이 강한 타입입니다. 매사에 아주 신중한 사람이죠. \n한 번 인연을 알게 되면 변함 없고 꾸준한 관계를 이어갑니다. \n";
			cout << "하지만 이런 유형의 분들은 생각이 너무 많아서 일을 할 때에 추진력이 약할 수 있습니다.\n " << endl;

			break;
		}
		else if (choicenum == 2) {
			cout << "\n★★★★★★★★★★★★★★★★★★" << endl;
			cout << "     2번을 선택한 당신!!!!" << endl;
			cout << "이것저것 호기심이 많아 그냥 지나치는 법이 없는 성격! " << endl;
			cout << "놀 땐 놀고 일할 땐 일하는 화끈한 성격의 타입입니다. \n개성이 매우 강하고 사교성이 뛰어나서 어떤 모임에 가든 분위기 메이커 역할을 합니다. \n";
			cout << "하지만 이런 성격은 변덕이 심하고 기분대로 행동한다는 게 단점이라고 합니다. \n" << endl;

			break;
		}
		else if (choicenum == 3) {
			cout << "\n★★★★★★★★★★★★★★★★★★" << endl;
			cout << "     3번을 선택한 당신!!!!" << endl;
			cout << "언제나 명쾌하고 감각적인 성격! " << endl;
			cout << "심각한 것을 싫어하고 세련되고 매너가 좋아서 사람들의 인기를 끄는 매력적인 타입입니다. \n";
			cout << "하지만 주의 사람들에게 조금이라고도 마음을 더 열어야 하는 것이 단점이라고 합니다.\n " << endl;

			break;
		}
		else if (choicenum == 4) {
			cout << "\n★★★★★★★★★★★★★★★★★★" << endl;
			cout << "     4번을 선택한 당신!!!!" << endl;
			cout << "무슨 일을 할 때 만사태평형이 많은 성격! " << endl;
			cout << "좋은 분위기에 약한 타입입니다. 반면에 한가지 일을 하더라고 완벽하게 하려고 하는 기질을 갖고 있다고 하네요. 이런 사람은 부드럽고 마일드한 매력이 큰 장점. \n";
			cout << "하지만 내성적이라는 것이 단점입니다\n " << endl;

			break;
		}
		else {
			cout << "번호를 잘못 입력하셨습니다. 다시 입력해주세요..." << endl;
		}
	}
}
void UnconsciousTest() {
	string people, houseSize, fenceText, onTable, sound;
	bool fence;
	int definition = 0;

	cout << "\n\n      << 무의식 심리테스트 >> \n\n" << endl;

	cout << "이 심리테스트는 단순히 재미를 위한 것이니 참고해주시기 바랍니다. ㅎㅎ" << endl;
	cout << "테스트를 진행할 준비가 되었다면 ENTER키를 눌러주세요...!\n" << endl;
	getchar();
	system("cls");

	//Q1
	cout << "따뜻한 햇볕, " << endl;
	getchar();
	cout << "신선한 바람이 부는 완벽한 날씨 " << endl;
	getchar();
	cout << "당신은 지금 풍경화 같은 경치의 숲속을 걷고 있습니다. " << endl;
	getchar();
	cout << "		Q1. 이때 당신 옆에있는 사람은 누구인가요?? " << endl;
	cout << "		답변을 입력해주세요 --->  ";
	getline(cin, people);

	//Q2 -2
	cout << "\n숲 속에 들어간 당신은 그곳에서 집을 발견했습니다. " << endl;
	getchar();
	cout << "		Q2-1. 당신이 발견한 집의 크기는 어느 정도인가요? " << endl;
	cout << "		답변을 입력해주세요 ---> ";
	getline(cin, houseSize);

	cout << "\n		Q2-2. 그 집에 울타리가 있나요? " << endl;
	while (1) {
		cout << "		있다고 생각하시면 <<네>>를 없다고 생각하시면 <<아니요>>를 입력해주세요 ---> ";
		cin >> fenceText;
		if (fenceText == "네") {
			fence = true;
			break;
		}
		else if (fenceText == "아니요") {
			fence = false;
			break;
		}
	}//while
	//Q3
	cout << "\n집에 가까이 다가가 보니 " << endl;
	getchar();
	cout << "집 근처에 테이블이 놓여져 있습니다. " << endl;
	getchar();
	cout << "		Q3 테이블 위에 무엇이 있습니까? " << endl;
	cout << "		답변을 입력해주세요 ---> ";
	getline(cin, onTable);

	//Q4
	cout << "\n당신은 어디선가 들려오는 물소리를 들었습니다. " << endl;
	getchar();
	cout << "그 소리를 따라가 봅니다. " << endl;
	getchar();
	cout << "		Q4. 그 물의 정체는 연못, 강, 바다 중에 무엇인가요? " << endl;
	while (1) {
		cout << "		<연못> <강> <바다> 중 한 개를 입력해주세요 ---> ";
		cin >> sound;
		if ((sound == "연못") || (sound == "바다") || (sound == "강")) break;
	}//while
	//Q5
	cout << "\n그 물에 당신의 얼굴을 비춰봅니다 " << endl;
	getchar();
	cout << "		Q5. 물에서 본 당신의 얼굴의 선명도는 어떤가요? " << endl;
	while (1) {
		cout << "		선명하다면 <1>을 선명하지 않다면 <2>를 입력해주세요 ---> ";
		cin >> definition;
		if ((definition == 1) || (definition == 2)) 	break;
	}//while

	//결과
	system("cls");
	cout << "\n\n      << 무의식 심리테스트 결과 >> \n\n" << endl;
	cout << "	Q1. 이때 당신 옆에있는 사람은 누구인가요?? " << endl;
	getchar();
	cout << "이때 대답한 < " << people << " > 은 당신이 인생에서 가장 소중하다고 생각하는 사람입니다. \n" << endl;
	getchar();

	cout << "\n	Q2-1. 당신이 발견한 집의 크기는 어느 정도인가요? " << endl;
	getchar();
	cout << "집의 크기는 당신의 야망의 크기를 나타냅니다\n "; //getchar();
	cout << " < " << houseSize << " > 라고 대답한 당신의 야망의 크기는 어떤가요? ㅎㅎ\n" << endl;
	getchar();

	cout << "\n	Q2-2. 그 집에 울타리가 있나요? " << endl;
	getchar();
	cout << "울타리가 없는 집은 적극적인 성격, 울타리가 있는 집은 소극적인 성격이라고 합니다. \n";
	if (fence == 1) {
		cout << "울타리가 있다고 생각한 당신! 평소 소극적인 성격을 가지고 있군요!\n" << endl;
		getchar();
	}
	else {
		cout << "울타리가 없다고 생각한 당신! 평소 적극적인 성격을 가지고 있군요!\n" << endl;
		getchar();
	}

	cout << "\n	Q3 테이블 위에 무엇이 있습니까? " << endl;
	getchar();
	cout << "테이블 위에 < " << onTable << " >이 놓여있다고 생각하셨군요\n ";
	cout << "테이블 위에 놓인 물건이 많을 수록 삶의 만족도가 높습니다. 특히 꽃이나 음식이라고 대박한 사람은 행복한 사람이라고 하네요 ㅎㅎ " << endl;
	getchar();


	cout << "\n	Q4. 그 물의 정체는 연못, 강, 바다 중에 무엇인가요? " << endl;
	getchar();
	cout << " < " << sound << " > 라고 대답하셨네요.";
	cout << "당신의 성욕의 크기를 알려주는 질문이었습니다. \n 넓은 곳 일수록 성욕이 큰 사람 입니다!^^ (연못 < 강 < 바다)\n " << endl;
	getchar();

	cout << "\n	Q5. 물에서 본 당신의 얼굴의 선명도는 어떤가요? " << endl;
	getchar();
	cout << "얼굴의 선명도는 1번에서 생각한 사람과의 관계입니다!\n얼굴이 선명하게 보일 수록 가까운 사이라고 하네요. \n";
	if (definition == 1) {
		cout << "평소 < " << people << " > 와(과) 가까운 사이네요!!" << endl;
		getchar();
	}
	else
		cout << "< " << people << " > 와(과) 가깝지 않는 사인가요? ㅎㅎ" << endl;
	getchar();

	cout << "무의식 심리테스트는 오로지 재미를 위한 것이니 재미로만 봐주세요 ㅎㅎ\n감사합니다 ㅎㅎ " << endl;
	getchar();

}
int enneagram() {
	string question1[3][6] = {
		{ //A
		"나는 독립적인 편이고 자기주장을 잘 한다.",
		"나는 목표를 설정하고 그 일을 추진해 나간다. 그리고 그것이 성취되기를 원한다.",
		"나는 가만히 앉아 있는 것을 좋아하지 않는다.",
		"나는 큰 일을 성취하고 영향력을 행사하기를 원한다.",
		"나는 정면 대결을 원하지는 않지만 사람들이 나를 통제하는 것도 좋아하지 않는다.",
		"대개의 경우 나는 내가 원하는 것을 잘 알고 있다." },
		{ //B
		"나는 조용하게 혼자 있는 것을 좋아한다.",
		"나는 사회적인 활동에 주의를 쏟지 않으며 대체로 내 의견을 강하게 주장하지 않는다.",
		"나는 앞에 나서거나 다른 사람과 경쟁하는 것을 그리 좋아하지 않는다.",
		"사람들은 나를 몽상가라고 말한다.",
		"내 상상의 세계 안에서는 많은 흥미로운 일들이 벌어진다.",
		"나는 적극적이고 활동적이기라기보다는 조용한 성격이다." },
		{ //C
		"나는 아주 책임감이 강하고 헌신적이다.",
		"나는 내 의무를 다하지 못할 때 아주 기분이 나쁘다.",
		"나는 사람들이 필요할 때 그들을 위해 내가 그 자리에 있다는 것을 알아 주었으면 좋겠다.",
		"이따금씩 나는 사람들이 나를 알아 주든 알아 주지 않든 그들을 위해 큰 희생을 한다.",
		"나는 내 자신을 제대로 돌보지 않는다.",
		"나는 해야 할 일을 한 다음에 시간이 나면 휴식을 취하거나 내가 원하는 일을 한다." }
	};
	string question2[3][5] = {
		{ //X
		"나는 대개 긍정적인 자세로 생활하며, 모든 일이 나에게 유리한 쪽으로 풀린다고 느낀다.",
		"나는 나의 열정을 쏟을 수 있는 여러 가지 방법을 찾는다.",
		"나는 사람들과 함께 하고 사람들이 행복해지도록 돕는 것을 좋아한다.",
		"나는 나와 마찬가지로 다른 사람들도 잘 지내기를 바란다.",
		"나는 다른 사람들에게 항상 긍정적으로 보이고자 노력하기 때문에 때로는 내 자신의 문제를 다루는 것을 미루기도 한다." },
		{ //Y
		"대부분의 사람들은 내가 모든 것에 대해 불만을 갖고 있다고 생각한다.",
		"나는 사람들과 함께 있을 때 그들이 어떤 사람인지, 무엇을 기대할 수 있는지를 알기 원한다.",
		"어떤 일에 내가 화가 났을 때 나는 사람들이 그것에 대해 반응하고 나만큼 그 일을 해결하려고 노력해 주기를 원한다.",
		"나는 규칙을 알고 있다. 하지만 사람들이 내게 무엇을 하라고 지시하는 것을 좋아하지 않는다.",
		"나는 내 스스로 결정하기를 원한다." },
		{ //Z
		"나는 스스로를 잘 통제하고 논리적이다.",
		"나는 느낌을 다루는 것을 편안해하지 않는다. 나는 효율적이고 완벽하게 일을 처리하며 혼자 일하는 것을 좋아한다.",
		"문제나 개인적인 갈등이 있을 때 나는 그 상황에 감정이 끼여들지 않도록 한다.",
		"어떤 사람들은 내가 너무 차고 초자연하다고 말하지만 나는 감정 때문에 중요한 일을 그르치고 싶지 않다.",
		"나는 사람들이 나를 화나게 할 때 대부분의 경우 반응을 보이지 않는다." }
	};
	string desc[9] = {
		"완벽주의자입니다.\n원칙적이고 목표가 분명하며, 자신을 잘 통제하고 완벽주의 기질이 있습니다.",
		"돕고자 하는 사람입니다.\n관대하고 자신의 감정을 잘 드러내며, 사람들을 즐겁게 해 주고 소유욕이 강합니다.",
		"성취하는 사람입니다.\n적응을 잘하고 뛰어다니며, 자신의 이미지에 관심이 많습니다.",
		"개인주의자입니다.\n표현력이 있고 극적이며, 자신의 내면에 빠져 변덕스럽습니다.",
		"탐구자입니다.\n지각력이 있고 창의적이며 혼자 떨어져 있기를 좋아하고 자신의 마음을 잘 드러내지 않습니다.",
		"충실한 사람입니다.\n책임감있고 의심과 불안이 많으며, 사람들에게 호감을 줍니다.",
		"열정적인 사람입니다.\n즉흥적이고 변덕스러우며, 욕심이 많고 산만합니다.",
		"도전하는 사람입니다.\n자신감있고 결단력 있으며, 고집스럽고 사람들과 맞서기를 좋아합니다.",
		"평화주의자입니다.\n수용적이고 남에게 위안을 주며, 잘 동의하고 자신에게 만족합니다."
	};
	int result[3][3] = {
		{ 7, 8, 3 },
		{ 9, 4, 5 },
		{ 2, 6, 1 }
	};
	int cnt[2][3] = { 0 }, n;

	cout << "**********에니어그램 유형 테스트**********" << endl;
	cout << "주어진 문제에 1. 예 / 2. 아니오 로 대답하세용\n" << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			cout << question1[i][j] << endl;
			cout << "1. 예 / 2. 아니오 : ";
			cin >> n;
			if (n == 1)
				cnt[0][i]++;
			cout << endl;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			cout << question2[i][j] << endl;
			cout << "1. 예 / 2. 아니오 : ";
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
	cout << "당신은 " << result[index1][index2] << "번 유형의 " << desc[result[index1][index2] - 1] << endl;

	return result[index1][index2];
}
void todayFortune() {
	string name[11] = { "ㄱ", "ㄴ", "ㄷ", "ㅁ", "ㅂ", "ㅅ", "ㅇ", "ㅈ", "ㅊ", "ㅌ", "ㅎ" };
	string food[17] = { "라면", "카레", "우동", "곱창", "삼겹살", "갈비", "김밥" , "떡볶이", "파스타", "치킨", "피자" , "회", "짜장면", "국밥", "쌀국수", "햄버거", "초밥" };
	string color[13] = { "빨간", "주황", "노란", "초록", "연두", "파란", "하늘", "남", "보라", "하얀", "검정", "회", "분홍" };
	int year, month, day, total, today;
	time_t t;
	struct tm now;
	t = time(NULL);
	localtime_s(&now, &t);
	today = now.tm_mday;

	cout << "생년월일을 입력하세요!" << endl;
	cout << "년도 : ";
	cin >> year;
	cout << "월 : ";
	cin >> month;
	cout << "일 : ";
	cin >> day;
	total = year + month + day + today;

	cout << "\n오늘의 운세를 계산 중입니다";
	for (int i = 0; i < 3; i++) {
		Sleep(1000);
		cout << ".";
	}
	Sleep(1000);
	cout << "\n\n오늘 조심해야 할 사람은 " << name[total % 11] << name[(total + today) % 11] << "입니다.." << endl;
	cout << "오늘 먹지 말아야 할 음식은 " << food[total % 17] << "입니다ㅠㅠ" << endl;
	cout << "오늘의 행운의 색은 " << color[total % 13] << "색입니다!" << endl;
}
int count(int* da, int* dam, int* uoo, int* jum) {
	int n;
	cout << "번호를 입력하세요 : ";
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
		cout << "잘못 입력했습니다.. 다시 입력하세요" << endl;
		return 0;
	}
}
void gijilresult(int* da, int* dam, int* uoo, int* jum) {
	cout << "***** 결과 *****" << endl;
	cout << "당신의 다혈질 점수 : " << *da << endl;
	cout << "당신의 담즙질 점수 : " << *dam << endl;
	cout << "당신의 우울질 점수 : " << *uoo << endl;
	cout << "당신의 점액질 점수 : " << *jum << endl;
}
void gijiltest() {
	int da = 0, dam = 0, uoo = 0, jum = 0;
	string question[40] = {
		"1. 생동감 있다			2. 모험적이다			3. 분석적이다			4. 융통성있다",
		"1. 허세를 부린다		2. 권세를 부린다		3. 숫기가 없다			4. 무표정하다",
		"1. 쾌활하다			2. 설득력 있다			3. 끈기 있다			4. 평온하다",
		"1. 규율이 없다			2. 동정심이 없다		3. 용서하지 않는다		4. 열정이 없다",
		"1. 사교적이다			2. 의지가 강하다		3. 희생적이다			4. 순응한다",
		"1. 한 말을 되풀이한다	2. 거스른다			3. 분을 품다		4. 상관이 없다",
		"1. 매력있다			2. 경쟁심 있다			3. 이해심 많다			4. 감정을 억제한다",
		"1. 건망증이 있다		2. 노골적이다			3. 까다롭다			4. 두려워하다",
		"1. 참신하다			2. 능력이 비상하다		3. 존중한다			4. 삼가다",
		"1. 중간에 끼어든다		2. 성급하다			3. 자신감이 없다		4. 결단력이 없다",
		"1. 신나하는 편			2. 독자적인 편			3. 민감한 편			4. 수용적인 편",
		"1. 예측할 수 없다		2. 애정표현이 없다		3. 인기 없다			4. 관계하지 않는다",
		"1. 장려하다			2. 긍정적이다			3. 계획하다			4. 참을성 있다",
		"1. 되는대로 한다		2. 완고하다			3. 불만이 많은 편			4. 망설이는 편",
		"1. 충동적인 편			2. 확신하는 편			3. 계획을 따른다		4. 과묵하다",
		"1. 방임하다			2. 교만하다			3. 염세적이다			4. 단조롭다",
		"1. 낙천적이다			2. 솔직하다			3. 질서 있다			4. 포용력 있다",
		"1. 쉽게 분노한다		2. 논쟁을 좋아한다		3. 자신을 격리한다		4. 목표가 없다",
		"1. 재담이 있다			2. 주관이 뚜렷하다		3. 신실하다			4. 응답적이다",
		"1. 피상적이다			2. 자만한다			3. 부정적이다			4. 안일하다",
		"1. 즐겁다			2. 겁이 없다			3. 섬세하다			4. 외교적이다",
		"1. 칭찬을 바란다		2. 일벌레인 편			3. 뒤로 물러서는 편		4. 염려하다",
		"1. 명랑하다			2. 자신감 있다			3. 문화적이다			4. 안정되다",
		"1. 말이 많다			2. 무례하다			3. 과민하다			4. 소심하다",
		"1. 격려하는 편			2. 독립적이다			3. 이상적이다			4. 거슬리지 않는다",
		"1. 무질서하다			2. 지배하다			3. 낙담하다			4. 확신이 없다",
		"1. 표현하는 편			2. 단호하다			3. 몰두하는 편			4. 정색하고 농담한다",
		"1. 일관성이 없다		2. 관대하지 못하다		3. 내성적이다		4. 무관심하다",
		"1. 쉽게 어울린다		2. 행동가 형			3. 음악을 좋아한다		4. 중재하는 형",
		"1. 어지르는 편			2. 조종하다			3. 우울한 편			4. 중얼거린다",
		"1. 말하기 좋아한다		2. 성취 지향적			3. 사려 깊은 편			4. 관대하다",
		"1. 과시한다			2. 고집이 세다			3. 회의적이다			4. 느리다",
		"1. 열정적이다			2. 책임감있다			3. 충성스러운 편		4. 잘 듣는다",
		"1. 시끄러운 편			2. 주장한다			3. 외로운 편			4. 게으른 편",
		"1. 무대형이다			2. 지도력 있다			3. 조직적이다			4. 만족하는 편",
		"1. 산만한 편			2. 성미가 급하다		3. 의심 많은 편			4. 나태하다",
		"1. 인기 있다			2. 생산적이다			3. 완벽을 추구한다		4. 편안하다",
		"1. 침착하지 못한 편	2. 경솔하다			3. 양심이 많은 편			4. 마지못해 하는 편",
		"1. 활기 있다			2. 담대하다			3. 예의바르다			4. 중도적이다",
		"1. 변덕스럽다			2. 약삭빠르다		3. 비판적이다			4. 타협한다"
	};
	cout << "***** 히포크라테스의 기질 테스트 *****" << endl;
	cout << "방법 : 각 항목 중 본인에게 가장 적합한 항목의 번호를 입력하세요 !" << endl << endl;
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
			int testCode = testMenuDraw(); //테스트 시작						
			if (testCode == 0) {
				system("cls");
				boredQuestionPrint();
				cout << "\n-----------------------------------------------------------" << endl;
				cout << "총 10개의 질문의 응답이 끝났습니다!! " << endl;
				cout << "테스트 결과를 보실 준비가 되었나요~? 그럼 테스트 결과 보여드리겠습니다!" << endl; getchar();
				cout << "-----------------------------------------------------------" << endl;
				boredResultPrint();
				cout << "-----------------------------------------------------------" << endl;
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 1) {		//성격
				system("cls");
				personalityTest();
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 2) {		//무의식
				system("cls");
				UnconsciousTest();
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 3) {		//애니어그램
				system("cls");
				dbconn();
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}

			}
			else if (testCode == 4) {		//기질태스트
				system("cls");
				gijiltest();
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
			else if (testCode == 5) {		//오늘의운세
				system("cls");
				todayFortune();
				cout << "\n<< 다른 테스트는 space bar로 ..... >>" << endl;
				while (1) {
					if (keyControl() == SUBMIT) {
						break;
					}
				}
			}
		}

		else if (menuCode == 1) { //프로그램 소개
			infoDraw();
		}

		else if (menuCode == 2) { //방명록
			fileout();
			while (1) {
				if (keyControl() == SUBMIT) {
					break;
				}
			}
		}

		else if (menuCode == 3) { //종료
			if (filein() == 1) {
				cout << "방명록 작성이 완료되었습니다. 감사합니다.\n다음에 또 찾아주세요~!" << endl;
				return 0;
			}
			else {
				cout << "방명록이 작성되지 않았습니다. 감사합니다.\n다음에 또 찾아주세요~!" << endl;
				return 0;
			}
		}

		system("cls");



		//return 0;
	}
}