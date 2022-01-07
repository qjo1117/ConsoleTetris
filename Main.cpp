#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 

#define HEIGHT 25        //블록이 움직일수있는 공간 설정          
#define WIDTH  20

#define FALSE 0         //결과를 확인하기쉽게 실패값과 성공값을 상수화
#define TRUE 1

#define DOWN 80         //키보드 입력값을 상수화
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define KEY_a 97
#define KEY_A 65
#define KEY_d 100
#define KEY_D 68


void gotoxy(int, int);
void SetColor(int color);
void gotoxy_jb(int x, int y);     //이동
COORD GetCursorPosition(void); //현재 커서위치를 읽는 함수
void CursorVisible(bool blnCursorVisible);//커서 안보이게하기 

// 화면 1 
void print_block_1(void);		//블 
void print_block_2(void);		//럭 
void print_block_3(void);		//쌓 
void print_block_4(void);		//기 
void print_block_5(void);		//아래 메뉴 
void print_block_play(void);
void print_animation(int[]);

//화면 2 
int play_game(void);
void print_gameboard(void);    //게임판 생성

void print_block(int shapes);   //블럭을 찍어주는 함수
int check_block(int shapes, int move_x, int move_y); //뒤에 이동값을 받은뒤 충돌이있는지 검사
void clean_block(int shapes);  //블럭을 지워주는 함수
void copy_block(int shapes, int block_color);      //블록이 바닥에 닿으면 해당블록이 위치하는 게임보드에 블록을 넣어주는 함수
void move_cursor(int move_x, int move_y);//현재 커서의 위치에서 입력값만큼 커서를 이동시켜주는 함수
void down_gameboard(int board_y); //현재 입력받은 보드의 높이 기준으로 보드의 값을 내림
void check_gameboard(void);      //한줄이완성된 칸이 있는지검사하고 줄을 내려주는 함수 down_gameboard()함수가 포함되어있음
void print_score(void);         //스코어점수 바꾸기
void print_next_block(int shapse);   //바뀐 다음블럭모양 바꾸기

//화면 3 
void print_GAMEOVER(void);
void gameover_G(void);           // G 출력
void gameover_A(void);           // A 출력
void gameover_M(void);           // 이하 동일
void gameover_E(void);
void gameover_O(void);
void gameover_V(void);
void gameover_E2(void);
void gameover_R(void);

//화면 4 
void print_CLEAR(void);
void gameclear_C(void);             //C 출력
void gameclear_L(void);             //L 출력
void gameclear_E(void);             // 이하 동일
void gameclear_A(void);
void gameclear_R(void);

//화면 5
void print_option(void);

void initialization(int(*)[22]);
int random_duplication(int[], int);
void Cursur(char, int*);

int score = 0;          //점수 카운트
int win = 10;           //승리 조건 점수
double time_limit = 1.0;        //기본게임속도 
int block[28][4][4] =     //블록을 3차원 배열로 선언 0 4 8 12 16 20 마다 모양이 시작
{

	//	  ■■■■

	{

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 1, 1, 1, 1 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 1, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 1, 1, 1, 1 },

		{ 0, 0, 0, 0 }

	},




	// ■■
	// ■■ 

	{

		{ 1, 1, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},




	//   ■
	// ■■■ 

	{

		{ 0, 0, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 1, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 1, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 1, 1, 1, 0 },

		{ 0, 1, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 1, 0, 0 }

	},




	//    ■
	// ■■■

	{

		{ 0, 0, 0, 0 },

		{ 0, 0, 1, 0 },

		{ 1, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 1, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 1, 0 },

		{ 1, 0, 0, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 0, 0, 0 },

		{ 1, 0, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 }

	},




	// ■
	// ■■■ 

	{

		{ 0, 0, 0, 0 },

		{ 1, 0, 0, 0 },

		{ 1, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 1, 1, 0, 0 },

		{ 1, 0, 0, 0 },

		{ 1, 0, 0, 0 },

		{ 0, 0, 0, 0 }

	},




	//     ■■
	//   ■■  

	{

		{ 0, 0, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 1, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 1, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 0, 1, 0 },

		{ 0, 0, 0, 0 }

	},




	// ■■
	//   ■■

	{

		{ 0, 0, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 1, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 0, 0 },

		{ 1, 1, 0, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 0, 0, 0 }

	},

	{

		{ 0, 0, 1, 0 },

		{ 0, 1, 1, 0 },

		{ 0, 1, 0, 0 },

		{ 0, 0, 0, 0 }

	},

};

int game_board[HEIGHT + 1][WIDTH + 2] = {                  //게임에서 사용될 게임판 처음 초기화?? 1은 블록 충돌을 확인하기위한 벽 0은 블록이 있을부분들.
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },		  // 맨윗벽 시작좌표는 0.0 맨윗벽 끝좌표는 42.0  맨윗줄 첫 블록자리 좌표는 2.0 맨윗줄  마지막 블록자리 좌표는 40 . 0 
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },	 // 즉 콘솔창에서 실제 배열에서의 위치를 알고싶으면 가로는 나누기 2를 하고 세로는 그대로의 값을 받아서 쓰면된다.
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },     //예를들어 콘솔창 좌표 2.0  은 게임보드 배열에서 [1][0]의 해당하는 위치이다.
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

int game_boardcolor[HEIGHT + 1][WIDTH + 2] = { 0 };  //	게임보드의 색깔을 담는 배열
int color[5] = { 9,10,12,13,14 };//색깔을 담아두는 배열 순서대로 파랑 초록 빨강 자주 노

int main(void)
{
	system("title : Tetris 2.0");
	CursorVisible(0);
	initialization(game_board);
	print_block_play();

	gotoxy(1, 21);
	return 0;
}

void initialization(int(*game_board)[22])
{
	int i, j;

	for (i = 0; i < HEIGHT; i++) {
		for (j = 1; j < WIDTH; j++)
			game_board[i][j] = 0;
	}
}

void Cursur(char key, int* y)
{
	int result;

	switch (key) {
	case 80:
		*y += 1;
		if (19 < *y) *y = 19;
		break;
	case 72:
		*y -= 1;
		if (17 > *y) *y = 17;
		break;
	default:
		break;
	}

	if (*y == 17 && key == 13) {									//1.게임실행 
		system("cls");
		result = play_game();
		if (result)
			print_CLEAR();
		else
			print_GAMEOVER();
		system("cls");

		main();
	}

	else if (*y == 18 && key == 13) {								//2.옵션 
		print_option();
		system("cls");
	}

	else if (*y == 19 && key == 13) {								//3.게임종료 
		system("cls");
		exit(0);
	}
}

void print_CLEAR(void)
{
	int start_time, end_time, end;
	int random[1];

	_getch();
	system("cls");
	while (1) {
		start_time = clock();
		while (1) {
			end_time = clock();
			end = end_time - start_time;
			if (end > 200) {
				random_duplication(random, 1);
				SetColor(random[0]);
				gameclear_C();             //C 출력
				gameclear_L();             //L 출력
				gameclear_E();             // 이하 동일
				gameclear_A();
				gameclear_R();
				Sleep(100);
				if (_kbhit()) {
					SetColor(15);
					gotoxy(1, 22);
					break;
				}
			}
		}
		if (_kbhit())
			break;
	}
	SetColor(15);
}

void print_GAMEOVER(void)
{
	int start_time, end_time, end;
	int random[1];
	srand((unsigned)time(NULL));

	_getch();
	system("cls");
	while (1) {
		start_time = clock();
		while (1) {
			end_time = clock();
			end = end_time - start_time;

			if (end > 1000) {
				random_duplication(random, 1);
				SetColor(random[0]);
				gameover_G();           // G 출력 
				gameover_A();           // A 출일 
				gameover_M();           // 이하 동일 
				gameover_E();
				gameover_O();
				gameover_V();
				gameover_E2();
				gameover_R();
				Sleep(100);
				if (_kbhit()) {
					SetColor(15);
					gotoxy(1, 22);
					break;
				}
			}
		}
		if (_kbhit())
			break;
	}
}

void print_block_play(void)
{
	int random[4] = { 0 }, select, i, y = 17;
	srand((unsigned)time(NULL));
	int start_time, end_time, end;
	print_block_5();

	while (1) {
		SetColor(15);
		print_block_5();
		start_time = clock();
		while (1) {
			end_time = clock();
			end = end_time - start_time;

			SetColor(15);
			gotoxy(32, y);
			printf("→");
			if (end > 100) {
				random_duplication(random, 4);
				print_animation(random);
				break;
			}
			if (_kbhit()) {
				SetColor(15);
				gotoxy(32, y);
				printf("→");
				select = _getch();
				Cursur(select, &y);
				printf("\b ");
			}
		}
	}
	SetColor(15);
}

void print_block_1(void)
{
	int i;
	//블록쌓기 타이틀 화면
												//                                                          "블"                출력
	//                    " ㅂ "           출력
	for (i = 0; i < 3; i++) {
		gotoxy(13, i + 3);
		printf("■");
	}

	for (i = 0; i < 3; i++) {
		gotoxy(5, i + 3);
		printf("■");
	}
	gotoxy(5, 4);
	printf("■■■■■");
	gotoxy(5, 6);
	printf("■■■■■");

	//                 " ㅡ "       출력
	gotoxy(3, 8);
	printf("■■■■■■■");
	//                " ㄹ " 출력
	gotoxy(6, 10);
	printf("■■■■");
	gotoxy(12, 11);
	printf("■");
	gotoxy(6, 12);
	printf("■■■■");
	gotoxy(6, 13);
	printf("■");
	gotoxy(6, 14);
	printf("■■■■");
}

void print_block_2(void)
{
	int i;
	//                                   "록"             출력
//                      " ㄹ  "            출력
	gotoxy(21, 4);
	printf("■■■■■");
	gotoxy(29, 5);
	printf("■");
	gotoxy(21, 6);
	printf("■■■■■");
	gotoxy(21, 7);
	printf("■");
	gotoxy(21, 8);
	printf("■■■■■");
	//                 "  ㅗ  "             출력
	gotoxy(25, 9);
	printf("■");
	gotoxy(19, 10);
	printf("■■■■■■■");
	//               "    ㄱ "        출력
	gotoxy(21, 12);
	printf("■■■■■");
	for (i = 0; i < 2; i++)
	{
		gotoxy(29, i + 13);
		printf("■");
	}
}

void print_block_3(void)
{
	int i;
	//                                      " 쌓"                출력
//                         "ㅆ"             출력
	gotoxy(39, 4);
	printf("■");
	gotoxy(37, 5);
	printf("■  ■");
	gotoxy(36, 6);
	printf("■    ■");
	gotoxy(46, 4);
	printf(" ■");
	gotoxy(45, 5);
	printf("■  ■");
	gotoxy(44, 6);
	printf("■    ■");

	//                    "ㅏ"             출력
	for (i = 0; i < 5; i++)
	{
		gotoxy(54, i + 4);
		printf("■");
	}
	gotoxy(56, 6);
	printf("■");

	//               "ㅎ"          
	gotoxy(45, 9);
	printf("■");
	gotoxy(40, 10);
	printf("■■■■■■");
	gotoxy(45, 11);
	printf("■");
	gotoxy(43, 12);
	printf("■  ■");
	gotoxy(45, 13);
	printf("■");
}

void print_block_4(void)
{
	int i;
	//                          " 기 "                     출력
//                      "ㄱ"             출력
	gotoxy(62, 6);
	printf("■■■■■");
	gotoxy(70, 7);
	printf("■");
	gotoxy(68, 8);
	printf("■");
	gotoxy(66, 9);
	printf("■");
	gotoxy(64, 10);
	printf("■");
	gotoxy(30, 20);
	//                   "   ㅣ "         출력
	for (i = 0; i < 7; i++)
	{
		gotoxy(74, i + 5);
		printf("■");
	}
}

void print_block_5(void)
{
	int i;
	char b[7], a = 0xa6;

	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;

	gotoxy(30, 16);
	printf("%c%c", a, b[3]);
	for (i = 0; i < 6; i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);

	for (i = 0; i < 3; i++) {
		gotoxy(30, 17 + i);
		printf("%c%c", a, b[2]);
		gotoxy(44, 17 + i);
		printf("%c%c", a, b[2]);
	}

	gotoxy(30, 20);
	printf("%c%c", a, b[6]);
	for (i = 0; i < 6; i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);

	gotoxy(34, 17);
	printf("1.게임실행");
	gotoxy(34, 18);
	printf("2.옵션");
	gotoxy(34, 19);
	printf("3.게임종료");
}

void print_animation(int random[])
{
	SetColor(random[0]);
	print_block_1();

	SetColor(random[1]);
	print_block_2();

	SetColor(random[2]);
	print_block_3();

	SetColor(random[3]);
	print_block_4();
}

int random_duplication(int random[], int n)
{
	int i, j;

	srand((unsigned)time(NULL));

	for (i = 0; i < n; i++) {
		random[i] = rand() % 7 + 9;
		for (j = 0; j < i; j++)
			if (random[i] == random[j]) {
				i--;
				break;
			}
	}
	return 0;
}

void gameover_G(void)
{
	int i;

	gotoxy(4, 2);
	for (i = 0; i < 6; i++)
		printf("■");

	for (i = 0; i < 5; i++) {
		gotoxy(4, i + 3);
		printf("■");
	}

	gotoxy(4, 8);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(8, 5);
	for (i = 0; i < 5; i++)
		printf("■");

	for (i = 0; i < 2; i++) {
		gotoxy(12, i + 6);
		printf("■");
	}
}

void gameover_A(void)
{
	int i;

	gotoxy(26, 2);
	printf("■");
	gotoxy(24, 3);
	printf("■  ■");
	gotoxy(23, 4);
	printf("■    ■");
	gotoxy(22, 5);
	printf("■      ■");
	gotoxy(21, 6);
	printf("■        ■");
	gotoxy(20, 7);
	printf("■          ■");
	gotoxy(19, 8);
	printf("■            ■");

	gotoxy(22, 5);
	for (i = 0; i < 4; i++)
		printf("■");
}

void gameover_M(void)
{
	int i;

	for (i = 0; i < 7; i++) {
		gotoxy(38, i + 2);
		printf("■");
	}

	gotoxy(40, i);
	for (i = 0; i < 7; i++) {
		gotoxy(40 + i, i + 2);
		printf("■");
	}

	gotoxy(54, i);
	for (i = 0; i < 7; i++) {
		gotoxy(52 - i, i + 2);
		printf("■");
	}

	for (i = 0; i < 7; i++) {
		gotoxy(54, i + 2);
		printf("■");
	}
}

void gameover_E(void)
{
	int i;
	for (i = 0; i < 7; i++) {
		gotoxy(60, i + 2);
		printf("■");
	}

	gotoxy(62, 2);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(62, 5);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(62, 8);
	for (i = 0; i < 5; i++)
		printf("■");
}
void gameover_O(void)
{
	int i;
	gotoxy(4, 10);
	for (i = 0; i < 5; i++)
		printf("■");

	for (i = 0; i < 7; i++) {
		gotoxy(3, 11 + i);
		printf("■");
	}

	for (i = 0; i < 7; i++) {
		gotoxy(13, 11 + i);
		printf("■");
	}

	gotoxy(4, 17);
	for (i = 0; i < 5; i++)
		printf("■");
}

void gameover_V(void)
{
	int i;

	for (i = 0; i < 7; i++) {
		gotoxy(20 + i, 10 + i);
		printf("■");
	}

	for (i = 0; i < 7; i++) {
		gotoxy(26 + i, 16 - i);
		printf("■");
	}
}
void gameover_E2(void)
{
	int i;

	for (i = 0; i < 7; i++) {
		gotoxy(38, i + 10);
		printf("■");
	}

	gotoxy(38, 10);
	for (i = 0; i < 6; i++)
		printf("■");

	gotoxy(38, 13);
	for (i = 0; i < 6; i++)
		printf("■");

	gotoxy(38, 16);
	for (i = 0; i < 6; i++)
		printf("■");
}
void gameover_R(void)
{
	int i;
	for (i = 0; i < 7; i++) {
		gotoxy(54, 10 + i);
		printf("■");
	}

	gotoxy(56, 10);
	for (i = 0; i < 4; i++)
		printf("■");
	for (i = 0; i < 3; i++) {
		gotoxy(64, 10 + i);
		printf("■");
	}

	gotoxy(56, 13);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(56, 14);
	printf("■");
	gotoxy(58, 15);
	printf("■");
	gotoxy(60, 16);
	printf("■");
	gotoxy(62, 16);
	printf("■");
	gotoxy(64, 16);
	printf("■");
}

void gameclear_C(void)
{
	int i;
	for (i = 0; i < 7; i++)
	{
		gotoxy(2, 10 + i);
		printf("■");
	}
	gotoxy(3, 10);
	for (i = 0; i < 5; i++)
	{
		printf("■");
	}
	gotoxy(3, 16);
	for (i = 0; i < 5; i++)
	{
		printf("■");
	}
}


void gameclear_L(void)
{
	int i;
	for (i = 0; i < 7; i++) {
		gotoxy(19, 10 + i);
		printf("■");
	}

	gotoxy(19, 16);
	for (i = 0; i < 4; i++)
		printf("■");
}


void gameclear_E(void)
{
	int i;
	for (i = 0; i < 7; i++) {
		gotoxy(50, i + 10);
		printf("■");
	}

	gotoxy(50, 10);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(50, 13);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(50, 16);
	for (i = 0; i < 5; i++)
		printf("■");
}


void gameclear_A(void)
{
	int i;
	gotoxy(38, 10);
	printf("■");
	gotoxy(36, 11);
	printf("■  ■");
	gotoxy(35, 12);
	printf("■    ■");
	gotoxy(34, 13);
	printf("■      ■");
	gotoxy(33, 14);
	printf("■        ■");
	gotoxy(32, 15);
	printf("■          ■");
	gotoxy(31, 16);
	printf("■            ■");
	gotoxy(34, 13);
	for (i = 0; i < 5; i++)
		printf("■");
}

void gameclear_R(void)
{
	int i;
	for (i = 0; i < 7; i++) {
		gotoxy(64, 10 + i);
		printf("■");
	}

	gotoxy(66, 10);
	for (i = 0; i < 4; i++)
		printf("■");

	for (i = 0; i < 3; i++) {
		gotoxy(74, 10 + i);
		printf("■");
	}

	gotoxy(66, 13);
	for (i = 0; i < 5; i++)
		printf("■");

	gotoxy(66, 14);
	printf("■");
	gotoxy(68, 15);
	printf("■");
	gotoxy(70, 16);
	printf("■");
	gotoxy(72, 16);
	printf("■");
	gotoxy(74, 16);
	printf("■");
}

int play_game(void)
{
	char key;
	int block_shapes, block_color;
	int start_time, end_time, end;
	int temp;
	int next_block, next_color;
	score = 0;
	srand((unsigned)time(NULL));

	print_gameboard();
	print_score();

	block_shapes = rand() % 7; //블록 모양 초기화
	block_shapes *= 4;
	block_shapes += rand() % 4;

	next_block = rand() % 28;
	next_color = rand() % 5;
	SetColor(color[next_color]);

	print_next_block(next_block); //다음나올 블록 알려주기

	block_color = rand() % 5; //블록색깔 만들기

	SetColor(color[block_color]);

	gotoxy_jb(18, 0); //중앙으로 위치이동
	print_block(block_shapes);

	while (1)
	{
		start_time = clock(); //시작시간계산

		while (1)
		{
			end_time = clock();  //반복시작시 시간계산
			end = end_time - start_time; //처음시작과 반복시작 시간과의 차이계산

			if (score >= 10) //만약 1점 이상을 얻으면 게임승리
				return TRUE;

			if (end > (time_limit * 1000) - (score * 50)) // 시간차이 계산해서 블록 내려가게하기
			{							// 하강시간은 점수가 1씩 늘어날수록 0.05초씩 줄어듬
				if (check_block(block_shapes, 0, 1) == TRUE)// 아래로 이동가능할시
				{
					clean_block(block_shapes);
					move_cursor(0, 1);
					print_block(block_shapes);
					break;
				}
				else                                  //아닐시
				{
					print_block(block_shapes);

					copy_block(block_shapes, block_color); //블록배열을 저장
					check_gameboard();        //한줄이 완성되었는지 검사

					block_shapes = next_block; //다음 블럭을 넣어준뒤
					next_block = rand() % 28;

					block_color = next_color; //다음색깔넣고
					next_color = rand() % 5;

					SetColor(color[next_color]);
					print_next_block(next_block);

					SetColor(color[block_color]);
					gotoxy_jb(18, 0);                  //블록이 땅에닿았기 ??문에 블록을 지우지않고 게임 시작자리로이동
					print_block(block_shapes);   //하고 이동 시작자리에 블록찍어주기

					if (check_block(block_shapes, 0, 0) == FALSE) //만약 첫시작자리에서 움직일수 없을경우
						return FALSE;                                 //게임 종료

					break;
				}
			}




			if (_kbhit())
			{

				key = _getch();

				switch (key)
				{
				case LEFT:                                         //왼쪽이동
					if (check_block(block_shapes, -2, 0) == TRUE)  //만약 왼쪽으로 이동시에 충돌이없다면
					{
						clean_block(block_shapes);                //원래있던자리에 블록을 제거하고
						move_cursor(-2, 0);                      //커서의 위치이동후
						print_block(block_shapes);                //해당 위치에 블록찍기
					}
					break;

				case RIGHT:
					if (check_block(block_shapes, 2, 0) == TRUE) //오른쪽이동 설명은 위와동일
					{
						clean_block(block_shapes);
						move_cursor(2, 0);
						print_block(block_shapes);
					}
					break;
				case DOWN:          //2 칸씩 내려가기
					if (check_block(block_shapes, 0, 2) == TRUE)
					{
						clean_block(block_shapes);
						move_cursor(0, 2);
						print_block(block_shapes);
					}
					break;

				case SPACE:                 // 블록이 닿기전까지 이동      
					clean_block(block_shapes);
					while (check_block(block_shapes, 0, 1) == TRUE)
						move_cursor(0, 1);

					print_block(block_shapes);

					copy_block(block_shapes, block_color); //블록배열을 저장
					check_gameboard();        //한줄이 완성되었는지 검사

					block_shapes = next_block; //다음 블럭을 넣어준뒤
					next_block = rand() % 28;

					block_color = next_color; //다음색깔넣고
					next_color = rand() % 5;

					SetColor(color[next_color]);
					print_next_block(next_block);

					SetColor(color[block_color]);
					gotoxy_jb(18, 0);                  //블록이 땅에닿았기 ??문에 블록을 지우지않고 게임 시작자리로이동
					print_block(block_shapes);   //하고 이동 시작자리에 블록찍어주기

					if (check_block(block_shapes, 0, 0) == FALSE) //만약 첫시작자리에서 움직일수 없을경우
						return FALSE;      //게임 종료
					break;

				case KEY_A:                       // a키 입력시 시계회전
				case KEY_a:

					temp = block_shapes; //블록모양이 바뀌었을때 가능한지 여부확인

					if (block_shapes % 4 == 0)  // 블록의 첫시작은 0 4 8 12 16 20 24이기 ??문에 4로나눌?? 0이나오면 블록의 첫시작이기??문에
						temp += 3;              // +3을 더해줘서 배열 맨뒷자리로 보내줌
					else
						temp -= 1;            //그게아니면 -1을해줘서 배열을 앞으로 보내줌

					if (check_block(temp, 0, 0) == TRUE)  //블럭의 방향이 바뀌었을??도 블럭이 들어갈수있으면
					{
						clean_block(block_shapes); //현재 위치에 있던 블럭을 지워주고
						block_shapes = temp;       //블럭 모양을 바뀐 블럭 모양으로 바꾸어준뒤에
						print_block(block_shapes);// 바뀐 블럭 모양으로 출력
					}
					break;

				case KEY_D:                  //b키입력시 반시계회전
				case KEY_d:

					temp = block_shapes;    //반시계회전은 블럭값이 증가하면서 변화하니 위의 식을 반대로 전환

					if (block_shapes % 4 == 3)
						temp -= 3;
					else
						temp += 1;

					if (check_block(temp, 0, 0) == TRUE) //이것도 마찬가지로 블럭을 회전해도 가능하면
					{
						clean_block(block_shapes); //현재 위치에 있던 블럭을 지워주고
						block_shapes = temp;       //블럭 모양을 바뀐 블럭 모양으로 바꾸어준뒤에
						print_block(block_shapes);// 바뀐 블럭 모양으로 출력

					}
					break;

				default:
					break;
				}

			}

		}
	}
}

void print_gameboard(void)          //게임판 출력
{
	int x, y;

	for (y = 0; y <= HEIGHT; y++)         // 0부터 시작하니  HEiGHT에 +1 하지 않아도 모든 세로줄을 포함함
		for (x = 0; x <= WIDTH + 1; x++)  //위와 비슷하지만 +2를 하였기에 +1 를함 
			if (game_board[y][x] == 1)   //첫 초기화시작시 보드배열에 1이있으면 벽이 있다는 것이니 벽해당위치에 벽돌을 생성
			{
				gotoxy_jb(x * 2, y); //좌표 ( 1, 1 ) 부터 찍기시작
				printf("※");
			}
			else
				printf("  ");    //일단 임시로 테스트를 확인하기쉽게 별모양으로 바꿈

	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 0);
		printf("※");
	}

	for (y = 0; y < 26; y++)
	{
		gotoxy_jb(60, y);
		printf("※");
	}

	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 25);
		printf("※");
	}

	gotoxy_jb(45, 1);
	printf("★다음 블록★");
	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 2);
		printf("※");
	}

	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 9);
		printf("※");
	}

	gotoxy_jb(44, 10);
	printf("   ★ 점 수 ★");
	gotoxy_jb(44, 11);
	printf("       0 0");
	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 12);
		printf("※");
	}

	gotoxy_jb(44, 13);
	printf(" ★ 조 작 키 ★");
	for (x = 0; x < 8; x++)
	{
		gotoxy_jb(44 + x * 2, 14);
		printf("※");
	}


	gotoxy_jb(44, 15);
	printf("  좌 우  이 동");
	gotoxy_jb(44, 16);
	printf("    ←    →\n");

	gotoxy_jb(44, 17);
	printf("  바 로  내 림\n");
	gotoxy_jb(44, 18);
	printf("   S P A C E\n");

	gotoxy_jb(44, 19);
	printf("  두 칸  내 림");
	gotoxy_jb(44, 20);
	printf("       ↓");

	gotoxy_jb(44, 21);
	printf(" 시계 방향 회전");
	gotoxy_jb(44, 22);
	printf("       A");

	gotoxy_jb(44, 23);
	printf("반시계 방향 회전");
	gotoxy_jb(44, 24);
	printf("       D");
}

void print_block(int shapes)  //현재의 좌표값을 받아와 해당위치에 블록 찍기
{
	COORD cursor_position = GetCursorPosition();  // 현재 커서위치 파악 
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[shapes][y][x] == 1)   // 해당위치에 블록이있으면 블록찍기
			{
				gotoxy_jb(cursor_position.X + x * 2, cursor_position.Y + y); //블록을 찍기위해 좌표이동
				printf("■");
			}

	gotoxy_jb(cursor_position.X, cursor_position.Y); //블록을 찍기위해 커서를 이동하였기??문에 첫 블록 위치로 되돌아가게해줌
}

int check_block(int shapes, int move_x, int move_y)    //해당값으로 이동할시 겹치는 블럭이나 벽이 있는지검사
{
	COORD board_position = GetCursorPosition();        //현재 커서위치받기 현재커서의 정보를 받고 그위치에 해당하는 보드배열값을 받으려면
	board_position.X = (board_position.X + move_x) / 2;  // x는 크기를 2씩 가지기에 나누기 2해줘야 비교가 가능
	board_position.Y += move_y;                         // y는 값만 대입해줘도 가능

	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[shapes][y][x] == 1 && game_board[board_position.Y + y][board_position.X + x] == 1)  //만약 같은위치에 블럭이 겹친다면
				return FALSE;                                                                              //FALSE을 반환

	return TRUE;     //만약 겹치는 블럭이 없으면 TRUE반환
}

void move_cursor(int move_x, int move_y) //현재 커서의 위치에서 입력값만큼 커서를 이동시켜주는 함수
{
	COORD pos = GetCursorPosition();         //현재커서위치를받고
	gotoxy_jb(pos.X + move_x, pos.Y + move_y);  //입력받은 값만큼 위치이동
}

void clean_block(int shapes)
{
	COORD cursor_position = GetCursorPosition();    //현재 커서위치파악

	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[shapes][y][x] == 1) //블럭이 있는자리이면
			{
				gotoxy_jb(cursor_position.X + x * 2, cursor_position.Y + y); //현재 비교한 배열의 위치로 이동
				printf("  ");                                          //해당자리에 블록을 찍음으로서 블럭제거
			}

	gotoxy_jb(cursor_position.X, cursor_position.Y);                     //커서위치를 원래자리로 이동
}

void copy_block(int shapes, int block_color) //블록이 땅에 닿으면 해당블록에 위치하는 게임보드에 블록을 넣어주는 함수 색깔도 넣어줌
{
	COORD board_position = GetCursorPosition();  //현재커서의 위치를 받고
	board_position.X /= 2;                       //보드 배열의 위치로 변환 y는 그대로값이니 생략

	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[shapes][y][x] == 1)                                  //만약 해당자리에 블록이 있으면
			{
				game_board[board_position.Y + y][board_position.X + x] = 1;  //해당위치에있는 게임보드에 블록값입력
				game_boardcolor[board_position.Y + y][board_position.X + x] = block_color; //해당 위치에 색깔넣기
			}

}

void check_gameboard(void)    //현재 게임보드에 완성된 줄이 있는지 검사하고 줄을 내려주는 함수
{
	int x, y;
	int z;
	int i;

	for (y = 24; y >= 0; y--)//맨밑바닥부터 위로 확인
		for (z = 0; z < 4; z++)//한번에 4줄이 완성될경우 블록을내린뒤 다시 검사해줄경우가 생기기??문에 한줄당 4번씩검사
		{
			i = 0;         //한줄에 몇개의 블럭있는지 세는 변수

			for (x = 1; x <= 20; x++) //왼쪽부터 오른쪽으로 검사
			{
				if (game_board[y][x] == 1) //만약 해당 게임보드칸에 블럭이 쌓여져 있으면
					i++;

				if (i == 20)            //만약 해당줄에 블록이 모두 쌓여있을??
				{
					score++;          //점수를 올리고
					print_score();    //점수판을 갱신해준다음
					down_gameboard(y);//블록 배열을 한칸씩 낮추고 게임판 안쪽을 다시출력
				}
			}
		}
}

void down_gameboard(int by)          // 한줄이 완성되고 그줄을 기준으로 배열을 내려주고 다시 출력해주는 함수 gotoxy_jb로 커서위치가 바뀌긴하나 
{									// 이함수를 쓴경우에는 블록이 닿았을 경우이니 커서위치를 다시 안바꿔도‰?
	int x, y;

	for (y = by; y > 0; y--)                   //한줄이 된 블록 기준으로  위칸에잇는 블록배열을 아래로 내림 +색상도
		for (x = 1; x <= 20; x++)
		{
			game_board[y][x] = game_board[y - 1][x];
			game_boardcolor[y][x] = game_boardcolor[y - 1][x];
		}

	for (x = 1; x <= 20; x++)                    //맨윗줄은 내려줄수있는 배열이 없기??문에 0으로 다시초기화
	{
		game_board[0][x] = 0;
		game_boardcolor[0][x] = 0;
	}


	for (y = 0; y <= by; y++)      //해당 줄까지 바뀐 배열 초기화
		for (x = 1; x <= 20; x++)
			if (game_board[y][x] == 1) //만약 해당칸에 블록이 있으면
			{
				gotoxy_jb(x * 2, y); //해당 위치하는 칸으로 이동
				SetColor(color[game_boardcolor[y][x]]); //해당 칸에있는 색깔을 찍고
				printf("■");
			}
			else
			{
				gotoxy_jb(x * 2, y);
				printf("  ");
			}
}

void print_score(void)
{
	SetColor(7);
	gotoxy_jb(53, 11);
	printf("%d", score);

	if (score / 10 > 0)
	{
		gotoxy_jb(51, 11);
		printf("%d", score / 10);
	}
	else
	{
		gotoxy_jb(51, 11);
		printf("0");
	}
}

void print_next_block(int shapes)   //다음블록 표시
{
	int x, y;

	for (y = 0; y < 6; y++)
		for (x = 0; x < 8; x++)
		{
			gotoxy_jb(44 + x * 2, 3 + y);
			printf("  ");
		}

	switch (shapes)  //다음블록칸에 블록을 예쁘게 찍기위해 블록 마다 ?는 위치 전환
	{                //배열을 찍기시작하는 위치를 바꾸어 주어야 예쁘게 찍힘 
	case 0:         // 전부 설명할순없으니 여기선 주석 생략
	case 2:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 16:
	case 20:
	case 22:
	case 24:
	case 26:
		gotoxy_jb(49, 4);
		break;

	case 1:
	case 3:
		gotoxy_jb(48, 3);
		break;

	case 13:
	case 17:
	case 21:
	case 23:
	case 25:
	case 27:
		gotoxy_jb(48, 4);
		break;

	case 4:
	case 5:
	case 6:
	case 7:
		gotoxy_jb(50, 5);
		break;

	case 14:
	case 18:
		gotoxy_jb(49, 5);
		break;

	case 19:
	case 15:
		gotoxy_jb(50, 4);
		break;

	default:
		break;
	}

	print_block(shapes); //해당좌표부터 블록쌓기
}

COORD GetCursorPosition(void)   // 현재 커서의 위치를 구조체에 담아 리턴하는 함수 

{

	COORD cursor;

	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;




	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	cursor.X = cursorInfo.dwCursorPosition.X;

	cursor.Y = cursorInfo.dwCursorPosition.Y;

	return cursor;

}

void print_option(void)
{
	system("cls");
	gotoxy(10, 10);
	printf("주의! 점수가 1점씩 증가할시 블록 떨어지는 속도가 0.05초씩 빨라짐.");
	gotoxy(18, 11);
	printf("게임 시작시 처음 블록 떨어시간(1당 1초씩 느려짐):");
	scanf_s("%lf", &time_limit);
	system("cls");
	gotoxy(10, 10);
	printf("주의! 점수가 1점씩 증가할시 블록 떨어지는 속도가 0.05초씩 빨라짐.");
	gotoxy(20, 11);
	printf("게임 승리 조건(파괴해야되는 블록개수):");
	scanf_s("%d", &win);

}

void gotoxy_jb(int x, int y)              // 입력받은 좌표로 이동
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1 , y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorVisible(bool blnCursorVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}