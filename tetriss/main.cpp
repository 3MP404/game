#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <mmsystem.h>    
#define up 72
#define down 80
#define left 75
#define right 77    
#define space 32
#pragma comment(lib,"winmm.lib")	
//#define bgm "E:\\프로그램\\tetriss\\bgm.wav"


int block_x=10,block_y=-1;
int block_dir=0;
int block_num=0;
int next_block_num=0;
int down_flag=0;
int high=20;
int hard_check=0;
int score=0;
int down_speed=800;

int map[20][12]={0,};
int blocks[7/*번호*/][4/*방향*/][4/*세로*/][4/*가로*/]=
{
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{2,2,2,2}
		},
		{
			{0,2,0,0},
			{0,2,0,0},
			{0,2,0,0},
			{0,2,0,0}
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,2},
			{0,2,2,2}
		},
		{
			{0,0,0,0},
			{0,2,0,0},
			{0,2,0,0},
			{0,2,2,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,2,2},
			{0,2,0,0}////
		},
		{
			{0,0,0,0},
			{0,2,2,0},
			{0,0,2,0},
			{0,0,2,0}/////
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,0,0},////
			{0,2,2,2}
		},
		{
			{0,0,0,0},
			{0,0,2,0},
			{0,0,2,0},
			{0,2,2,0}////
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,2,2},
			{0,0,0,2}
		},
		{
			{0,0,0,0},
			{0,2,2,0},
			{0,2,0,0},
			{0,2,0,0}////
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,2,0},
			{0,0,2,2}////
		},
		{
			{0,0,0,0},
			{0,0,2,0},
			{0,2,2,0},
			{0,2,0,0}////
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,2,2},
			{0,2,2,0}////
		},
		{
			{0,0,0,0},
			{0,2,0,0},
			{0,2,2,0},
			{0,0,2,0}////
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,2,0},
			{0,2,2,2}////
		},
		{
			{0,0,0,0},
			{0,2,0,0},
			{0,2,2,0},
			{0,2,0,0}////
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,2,2},
			{0,0,2,0}
		},
		{
			{0,0,0,0},
			{0,0,2,0},
			{0,2,2,0},
			{0,0,2,0}
		}
	},
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,2,2,0},
			{0,2,2,0}
		}
	}
};



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
void score_up(char how[5])
{
	gotoxy(28,10);
	if(how=="one")
	{
		score++;
		printf("score:%d",score);
	}
	else if(how=="boom")
	{
		score+=50;
		printf("score:%d",score);
	}
}
void print_board()
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<13;j++)
		{
			if(i==19)
				printf("□");
			else if(j==0||j==12)
				printf("□");
			else
				printf("  ");
		}
		printf("\n");
	}
	gotoxy(26,3);
		printf("※※※※※(Dead line)");
	gotoxy(26,4);
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(i==0||i==5||j==4)
				{
					printf("□");
					continue;
				}
			else
				printf("  ");
		}
		gotoxy(26,i+5);
	}
	gotoxy(28,10);
	printf("score:%d",score);
}
void set_cur(int i)
{
	gotoxy(10,i);
}
void print_map()
{
	gotoxy(2,0);
	for(int i=0;i<19;i++)
	{
		for(int j=1;j<12;j++)
		{
			if(map[i][j]==2)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),7);
				printf("■");
			}
			else if(map[i][j]==0)
				printf("  ");
		}
		gotoxy(2,1+i);
	}
}
void print_block()
{
	set_cur(block_y);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(blocks[block_num][block_dir][i][j]==2)
				{
						gotoxy(block_x+(j*2),block_y+i);
							SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),block_num+8);
						printf("■");
						SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),7);
				}
		}
		printf("\n");
	}
}
void random_block()
{
	next_block_num=rand()%7;
}
void preview_block()
{
	gotoxy(26,5);
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<8	;j++)
		{
			printf(" ");
		}
		gotoxy(26,4+i+1);
	}
	gotoxy(26,5);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(blocks[next_block_num][0][i][j]==2)
				{
					gotoxy(26+j*2,5+i);
					printf("■");
				}
		}
		printf("\n");
	}
}
void effect(int* y)
{
	int i,check=1,many=0;
	for(i=0;i<4;i++)
	{
		if(y[i]==0)
			continue;
		gotoxy(2,block_y+i);
		for(int j=0;j<10;j++)
			printf("  ");
	}
	Sleep(80);
	for(int i=0;i<4;i++)
	{
		if(y[i]==0)
			continue;
		gotoxy(2,block_y+i);
		for(int j=0;j<11;j++)
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),block_num+8);
		printf("■");
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),7);
	}
	Sleep(80);
	for(int i=0;i<4;i++)
	{
		if(y[i]==0)
			continue;
		gotoxy(2,block_y+i);
		for(int j=0;j<11;j++)
			printf("  ");
		if(y[i]==1)
		{
			for(int j=block_y+i;j>high-1;j--)
			{
				
				for(int k=1;k<12;k++)
				{
					map[j][k]=map[j-1][k];
				}
			}
			many++;
			continue;
		}
	}
	gotoxy(28,10);
	printf("score:%d",score);
	for(;many>0;many--)
		{
			score_up("boom");
		}
}
void save_map()
{
	hard_check=1;
	int check_effect=0;
	int check[4]={1,1,1,1};
	if(high<=3)
	{
		system("cls");
		gotoxy(15,6);
		printf("!!!GAME OVER!!!");
		exit(1);
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(map[block_y+i][block_x/2+j]==1||map[block_y+i][block_x/2+j]==2)
				continue;
			map[block_y+i][block_x/2+j]=blocks[block_num][block_dir][i][j];
		}
	}
	for(int i=block_y;i<block_y+4;i++)
	{
		for(int j=1;j<12;j++)
		{
			if(map[i][j]==0)
			{
				check[i-block_y]=0;
				break;
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		if(check[i])
		{
			check_effect=1;
			break;
		}
	}
	if(check_effect)
		{
			effect(check);
		}
	print_map();
	block_num=next_block_num; 
	random_block();
	preview_block();
	block_y=0;
	block_x=10;
	block_dir=0;
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<11;j++)
		{
			if(map[i][j]==2)
			{
				high=i;
				return;
			}
		}
	}
}
void remove_block()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(blocks[block_num][block_dir][i][j]==2)
				{
					gotoxy(block_x+j*2,block_y+i);
					printf("  ");
				}
		}
	}
}
void down_block()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(blocks[block_num][block_dir][i][j]==2)
			{
				if(i==3)
				{
					if(map[block_y+4][block_x/2+j]==1||map[block_y+4][block_x/2+j]==2)
					{
						save_map();
						return;
					}
				}
				else if(blocks[block_num][block_dir][i+1][j]==0)
				{
					if(map[block_y+i+1][block_x/2+j]==2)
					{
						save_map();
						return;
					}
				}
			}
		}
	}
	remove_block();
	block_y++;
}
void move_block(char h)
{
	int hight=9999;
	int height_j=5;
	int l=0;
	switch(h)
	{
		case space:
			{
				while(hard_check==0)
				{
					down_block();
				}
				hard_check=0;
			}
		case left:
			{
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						if(blocks[block_num][block_dir][i][j]==2)
						{
							if(blocks[block_num][block_dir][i][j-1]==0)
							{
								if(map[block_y+i][block_x/2+j-1]==2||map[block_y+i][block_x/2+j-1]==1)
								{
									return;
								}
							}
						}
					}
				}
				remove_block();
				block_x-=2;
				print_block();
				break;
			}
		case right:
			{
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						if(blocks[block_num][block_dir][i][j]==2)
						{
							if(blocks[block_num][block_dir][i][j+1]==0)
							{
								if(map[block_y+i][block_x/2+j+1]==2||map[block_y+i][block_x/2+j+1]==1)
								{
									return;
								}
							}
						}
					}
				}
				remove_block();
				block_x+=2;
				print_block();
				break;
			}
		case up:
			{
				switch(block_num)
				{
					case 0:
						{
							if(block_dir==0)
							{
								for(int i=0;i<3;i++)
								{
										if(map[block_y+i][block_x/2+1]==2)
										{
											return;
										}
								}
							}
							else if(block_dir==1)
							{
								
									if(map[block_y+3][block_x/2]==1||map[block_y+3][block_x/2]==2)
									{
										for(int i=2;i<5;i++)
										{
											if(map[block_y+3][block_x/2+i]==1||map[block_y+3][block_x/2+i]==2)
												{
													return;
												}
										}
									remove_block();
									block_x+=2;
									break;
									}
									for(int i=2;i<4;i++)
									{
										if(map[block_y+3][block_x/2+i]==1||map[block_y+3][block_x/2+i]==2)
										{
											for(int j=1;j<3;j++)
											if(map[block_y+3][block_x/2-j]==1||map[block_y+3][block_x/2-j]==2)
												{
													return;
												}
											remove_block();
											block_x-=4;
											break;
										}
									}
							}
							break;
						}
					case 1:
						{
							if(block_dir==0)
							{
								for(int i=1;i<3;i++)
								{
									if(map[block_y+i][block_x/2+1]==2)
									{
										return;
									}
								}
							}
							else if(block_dir==1)
							{
								for(int i=2;i<4;i++)
								{
									if(map[block_y+2][block_x/2+i]==2||map[block_y+2][block_x/2+i]==1)
									{
										for(int i=0;i<2;i++)
										{
												if(map[block_y+i][block_x/2]==1||map[block_y+i][block_x/2]==2)
													return;
												remove_block();
												block_x-=2;
												break;
										}
										break;
									}
								}
							}
							else if(block_dir==2)
							{
								for(int i=1;i<3;i++)
								{
									if(map[block_y+1][block_x/2+i]==2)
									{
										if(map[block_y-4][block_x/2+2]==1||map[block_y-4][block_x/2+2]==2)
										{
											return;
										}
										remove_block();
										block_y++;
										break;
									}
								}
							}
							else if(block_dir==3)
							{
								for(int i=2;i<4;i++)
								{
									if(map[block_y+i][block_x/2+3]==1||map[block_y+i][block_x/2+3]==2)
									{
										if(map[block_y+3][block_x/2]==1||map[block_y+3][block_x/2]==2)
										{
											return;	
										}
										remove_block();
	 									block_x-=2;
										break;
									}	
								}
							}
							break;
						}
						
					case 2:
						{
							if(block_dir==0)
							{
								for(int i=1;i<3;i++)
								{
									if(map[block_y+2][block_x/2+i]==2)
									{
										return;
									}
								}
							}
							else if(block_dir==1)
							{
								if(map[block_y+2][block_x/2]==1||map[block_y+2][block_x/2]==2)
								{
									for(int i=2;i<4;i++)
									{
										if(map[block_y+i][block_x/2+3]==1||map[block_y+i][block_x/2+3]==2)
											return;
										remove_block();
										block_x+=2;
										break;
									}
								}
								remove_block();
								block_x-=2;
								break;
							}
							else if(block_dir==2)
							{
								for(int i=1;i<3;i++)
								{
									if(map[block_y+1][block_x/2+i]==2)
									{
										if(map[block_y+4][block_x/2+i]==2||map[block_y+4][block_x/2+i]==1)
											return;
										remove_block();
										block_y++;
										break;
									}
								}
							}
							else if(block_dir==3)
							{
								for(int i=2;i<4;i++)
								{
									if(map[block_y+3][block_x/2+i]==1||map[block_y+3][block_x/2+i]==2)
									{
										for(int j=2;j<4;j++)
										{
											if(map[block_y+j][block_x/2]==1||map[block_y+j][block_x/2]==2)
												return;
											remove_block();
											block_x-=2;
											break;
										}
									}
								}
							}
							break;
						}
						case 3:
						{
							if(block_dir==0)
								{
									if(map[block_y+1][block_x+2]==2)
									{
										remove_block();
										block_y++;
										break;
									}
								}
							else if(block_dir==1)
								{
										if(map[block_y+2][block_x+2]==2)
										{
											remove_block();
											block_x--;
											break;
										}
								}
						}
						case 4:
							{
								 if(map[block_y][block_x+1]==2)
								 {
								 	remove_block();
								 	block_y++;
								 	break;
								 }
							}
				}
				if(block_num==6)
					break;
				remove_block();
				block_dir++;
				if(block_num==0||block_num==3||block_num==4)
				{
					if(block_dir>1)
					{
						block_dir=0;
					}
				}
				else
					block_dir=block_dir%4;
				
				print_block();
				break;
			}
		case down:
			{				
				score_up("one");
				down_block();
				print_block();
			}
	}
}
int main()
{
	char h;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<13;j++)
		{
			if(i==19)
			{
				map[i][j]=1;
			}
			else if(j==0||j==12)
			{
				map[i][j]=1;
			}
		}
	}
	time_t start_t;
	removecursor();
	srand(time(NULL));
	block_num=rand()%7; 
	random_block();
	print_board();
	preview_block();
	while(1)
	{
		
		start_t=clock();
		down_block();
		print_block();
	 	while(clock()-start_t<down_speed)
		{
			if(kbhit())
			{
				h=getch();
				if(h==up||h==down||h==left||h==right||h==space)
					move_block(h);
				
			}
		}
	}
}
