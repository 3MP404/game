#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#define up 72
#define down 80
#define left 75
#define right 77
#define r 114
#define e 101
#define enter 13
#define DEL 127
#define esc 27
#define space 32

int char_x=8,char_y=16,num=2,del=2,ch_eat=0;
int board[20][20]={0,};//1:벽-1:머리 -2:사과 나머지:몸 
int dir=1;
int speed=100;
int score=-103;
void gotoxy();
void removecursor();

void gotoxy(int x,int y)
{
	COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void removecursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo); 
}
void make_apple()
{
	speed-=3;
	score+=200-speed;
	srand(time(NULL));
	int x,y;
	while(1)
	{
		x=rand()%19+1;
		y=rand()%19+1;
		if(board[y][x]==0)
			break;
	}
	gotoxy(0,30);
	board[y][x]=-2;
}
void print_board()
{
	for(int i=0;i<20;i++)
	{
		gotoxy(30,i+2);
		for(int j=0;j<20;j++)
		{
			if(board[i][j]==1)
				printf("■");
			else if(board[i][j]==0)
				printf("  ");
		}
		printf("\n");
	}
}
void print_char()
{
	for(int i=1;i<20;i++)
	{
		gotoxy(32,i+2);
		for(int j=1;j<20;j++)
		{
			if(board[i][j]==-1)
			{		
				switch(dir)
				{
					case 1:
						printf("▶");
						break;
					case 2:
						printf("◀");
						break;
					case 3:
						printf("▼");
						break;
					case 4:
						printf("▲");
						break;
				}
			}
			else if(board[i][j]==0)
				printf("  ");
			else if(board[i][j]==-2)
				printf("◎");
			else if(board[i][j]!=1)
				{
					printf("□");
				}
		}
	}
}
void move_char()
{
	board[char_y][char_x]=num;
	num++;
	switch(dir)
	{
		case 1:
			char_x++;
			break;
		case 2:
			char_x--;
			break;
		case 3:
			char_y++;
			break;
		case 4:
			char_y--;
			break;
	}
	if(board[char_y][char_x]!=0&&board[char_y][char_x]!=-2)
	{
		
		gotoxy(38,5);
    	printf("+----------------------+");
		gotoxy(38,6);
    	printf("|      GAME OVER..     |");
		gotoxy(38,7);
    	printf("+----------------------+");
		gotoxy(38,8);
    	printf(" YOUR SCORE : %d",score);
		while(1)
		{
			if(kbhit())
				exit(1);
		}
	}
	else if(board[char_y][char_x]==-2)
		{
			make_apple();
			ch_eat=1;
			del--;
		}
	board[char_y][char_x]=-1;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(board[i][j]==del)
			{
				board[i][j]=0;
				del++;
				return;
			}
		}
	}
}
void change_dir(char h)
{
	switch(h)
	{
		case up:
			if(dir==3)
				break;
			dir=4;
			break;
		case down:
			if(dir==4)
				break;
			dir=3;
			break;
		case left:
			if(dir==1)
				break;
			dir=2;
			break;
		case right:
			if(dir==2)
				break;
			dir=1;
			break;
	}
}
int main()
{
	char h;
	removecursor();
	time_t start;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(i==0||j==0||j==19||i==19)
				board[i][j]=1;
		}
	}
	print_board();
	for(int i=3;i>=0;i--,num++)
		board[char_y][char_x-i]=num;
	num--;
	board[char_y][char_x]=-1;
		gotoxy(70,3);
		printf("                  ");
		gotoxy(70,3);
		make_apple();
	while(1)
	{
		gotoxy(72,4);
		printf("score:%d",score);
		print_char();
		start=clock();
		while(clock()-start<speed)
		{
			if(kbhit())
			{
				h=getch();
				change_dir(h);
			}
		}
		move_char();
		if(ch_eat==1)
		{
			del++;
			ch_eat=0;
		}
	}
	gotoxy(0,25);
}
