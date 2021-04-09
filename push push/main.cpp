
#include<Stdio.h>
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

char field[12][12];
int now;
int ball;
char name[30];
int x=1,y=1;
int rest=1;
int home=0;
int map_x,map_y;
char tmp[2];
int M=0;
int scene=0;
int sellect=1;
int cur_x;
int cur_y;
int char_x=100;
int char_y=100;
int make=0;
int sizecheck=1;

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

int main();
void sellect_map();
void new_map();
void edit_move();
void edit_map();
void main_move();
void main_scene();
void map_load();
int map_load(int num);
void gotoxy(int x,int y);
void removecursor();
void map();
void regame();
void move();
void print_map();
void map()
{
	int i=5;
	if(rest==0)
	{
		scene++;
		map_load();
		system("cls");
		while(i>0)
		{
			system("cls");
			printf("                                               !!!clear!!!\n");
			printf("                                             움직인 횟수:%d\n",M);
			sleep(1);
			i--;
		}
		system("cls");
		M=0;
	}
	printf("\n");
	gotoxy(47,1);
	printf("<stage %d>\n",tmp[0]-48);
	field[y][x/2]='4';
	for(i=0;i<map_y;i++)
		{
			printf("                                             ");
			for(int j=0;j<map_x;j++)
				{
					if(field[i][j]=='4')
						printf("◇");
					else if(field[i][j]=='0')	
						printf("  ");
					else if(field[i][j]=='1')
						printf("■");	
					else if(field[i][j]=='2')
						printf("●");
					else if(field[i][j]=='3')
						printf("□");
					else if(field[i][j]=='G')
						printf("▣");
				}
				printf("\n");
		}
		gotoxy(48+map_x*2+2,5);
		printf("남은 집:%d",rest);
		gotoxy(48+map_x*2+2,6);
		printf("움직인 횟수:%d",M);
		gotoxy(48+map_x*2+2,7);
		printf("재시작:r");
		gotoxy(48+map_x*2+2,8);
		printf("게임종료:e");
}
void regame()
{
	x=2;
	y=1;
	M=0;
	home=0;
	map_load();
	system("cls");
	map();
}
void move()
{
	char m;
	while(1)
	{
		m=getch();
		switch(m) 
		{
			case 'e':
				{
					exit(1);
				}
			case 'r':
				{
					regame();
					break;
				}
			case up:
			{	
				if(field[y-1][x/2]!='1')
				{
					if(home==1)
					{
						field[y][x/2]='3';
						home=0;
					}
					else
					{
						field[y][x/2]='0';
					}
					if(field[y-1][x/2]=='3')
					{
						home=1;
						M++;
						y--;
					}
					else if(field[y-1][x/2]=='2')
					{
						if(field[y-2][x/2]!='1'&&field[y-2][x/2]!='G' && field[y-2][x/2]!='2')
						{
							M++;
							y--;
							if(field[y-1][x/2]=='3')
							{
								field[y-1][x/2]='G';
								rest--;
							}
							else
								field[y-1][x/2]='2';
						}
					}
					else if(field[y-1][x/2]=='G')
					{
						if(field[y-2][x/2]!='1'&&field[y-2][x/2]!='G' && field[y-2][x/2]!='2')
						{
							M++;
							y--;
							if(field[y-1][x/2]=='3')
							{
								home=1;
								field[y-1][x/2]='G';
							}
							else
							{
								home=1;
								field[y-1][x/2]='2';
								rest++;
							}
						}
					}
					else
					{
						if(home==1)
						{
							field[y][x/2]='H';
							home=0;
						}
						y--;
						M++;
					}
				}
				break;
			}
			case down:
			{
				if(field[y+1][x/2]!='1')
				{
					if(home==1)
					{
						field[y][x/2]='3';
						home=0;
					}
					else
					{
						field[y][x/2]='0';
					}
					if(field[y+1][x/2]=='3')
					{
						home=1;
						M++;
						y++;
					}
					else if(field[y+1][x/2]=='2')
					{
						if(field[y+2][x/2]!='1'&&field[y+2][x/2]!='G' && field[y+2][x/2]!='2')
						{
							M++;
							y++;
							if(field[y+1][x/2]=='3')
							{
								field[y+1][x/2]='G';
								rest--;
							}
							else
								field[y+1][x/2]='2';
						}
					}
					else if(field[y+1][x/2]=='G')
					{
						if(field[y+2][x/2]!='1'&&field[y+2][x/2]!='G' && field[y+2][x/2]!='2')
						{
							M++;
							y++;
							if(field[y+1][x/2]=='3')
							{
								home=1;
								field[y+1][x/2]='G';
							}
							else
							{
								home=1;
								field[y+1][x/2]='2';
								rest++;
							}
						}
					}
					else
						{
						if(home==1)
						{
							field[y][x/2]='H';
							home=0;
						}
							M++;
							y++;	
						}
				}
				break;
			}
			case left:
			{
				if(field[y][x/2-1]!='1')
				{
					if(home==1)
					{
						field[y][x/2]='3';
						home=0;
					}
					else
					{
						field[y][x/2]='0';
					}
					if(field[y][x/2-1]=='3')
					{
						home=1;
						x-=2;
						M++;
					}
					else if(field[y][x/2-1]=='2')
					{
						if(field[y][x/2-2]!='1'&&field[y][x/2-2]!='G' && field[y][x/2-2]!='2')
						{
							M++;
							x-=2;
							if(field[y][x/2-1]=='3')
							{
								field[y][x/2-1]='G';
								rest--;
							}
							else
								field[y][x/2-1]='2';
						}
					}
					else if(field[y][x/2-1]=='G')
					{
						if(field[y][x/2-2]!='1'&&field[y][x/2-2]!='G' && field[y][x/2-2]!='2')
						{
							M++;
							x-=2;
							if(field[y][x/2-1]=='3')
							{
								home=1;
								field[y][x/2-1]='G';
							}
							else
							{
								home=1;
								field[y][x/2-1]='2';
								rest++;
							}
						}
					}
					else
						{
							
						if(home==1)
						{
							field[y][x/2]='H';
							home=0;
						}
							M++;
							x-=2;	
						}
				}
				break;
			}
			case right:
			{
				if(field[y][x/2+1]!='1')
				{
					if(home==1)
					{
						field[y][x/2]='3';
						home=0;
					}
					else
					{
						field[y][x/2]='0';
					}
					if(field[y][x/2+1]=='3')
					{
						home=1;
						M++;
						x+=2;
					}
					else if(field[y][x/2+1]=='2')
					{
						if(field[y][x/2+2]!='1'&&field[y][x/2+2]!='G' && field[y][x/2+2]!='2')
						{
							x+=2;
							M++;
							if(field[y][x/2+1]=='3')
							{
								field[y][x/2+1]='G';
								rest--;
							}
							else
								field[y][x/2+1]='2';
						}
					}
					else if(field[y][x/2+1]=='G')
					{
						if(field[y][x/2+2]!='1'&&field[y][x/2+2]!='G' && field[y][x/2+2]!='2')
						{
							M++;
							x+=2;
							if(field[y][x/2+1]=='3')
							{
								home=1;
								field[y][x/2+1]='G';
							}
							else
							{
								home=1;
								field[y][x/2+1]='2';
								rest++;
							}
						}
					}
					else
						{
							
						if(home==1)
						{
							field[y][x/2]='H';
							home=0;
						}
							M++;
							x+=2;	
						}
				}
				break;
			}
		}
		field[y][x/2]='4';
		if(m!=r)
		{
			map();
		}
	}
}
int H=0;
int g=0;
void print_map()
{
	printf("\n                 			좌우로 이동해 맵을 선택하세요.");
	printf("\n                           나가기:esc");
	printf("\n                                               <stage %d>\n",tmp[0]-48);
	for(int i=0;i<=map_y;i++)
	{
		printf("                                                ");
		for(int j=0;j<map_x;j++)
		{
			if(field[i][j]=='1')
				printf("■");	
			else if(field[i][j]=='2')
				{
					g++;
					printf("●");
				}
			else if(field[i][j]=='3')
				{
					H++;
					printf("□");
				}
			else if(field[i][j]=='4')
				printf("◇");
			else if(field[i][j]=='0')
				printf("  ");
		}
		printf("\n");
	}
}
void sellect_map()
{
	char h;
	int num=1;
	system("cls");
	map_load(num);
	print_map();
	while(h!=enter)
	{
		h=getch();
		system("cls");
		switch(h)
		{
			case right:
			{
				num++;
				if(map_load(num)==0)
				{
					num--;
					map_load(num);
				}
				break;
			}
			case left:
			{
				num--;
				if(map_load(num)==0)
				{
					num++;
					map_load(num);
				}
				
			}
		}
		print_map();
	}
}
void new_map()
{
	system("cls");
	FILE *pf;
	strcpy(name,"map");
	tmp[0]=49;
	int i=0;
	strcpy(name,"map");
	strcat(name,tmp);
	strcat(name,".txt");
	pf=fopen(name,"r");
	while(pf!=NULL)
	{
		strcpy(name,"map");
		strcat(name,tmp);
		strcat(name,".txt");
		pf=fopen(name,"r");
		tmp[0]++;
	}
	pf=fopen(name,"w");
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			field[i][j]='0';
		}
	}
}
void edit_move()
{
	g=0;
	H=0;
	char m=getch();
		switch(m)
		{
			case up:
				{
					if(sellect==1)
						{
							sellect=3;
							break;
						}
					sellect--;
					break;
				}
			case down:
				{
					if(sellect==3)
						{
							sellect=1;
							break;
						}
					sellect++;
					break;
				}
			case enter:
				{
					if(sellect==1)
					{
						new_map();
						sizecheck=1;
						scene=-3;
					}
					else if(sellect==2)
					{
						sellect_map();
						sizecheck=1;
						scene=-3;
					}
					else
					{
						scene=0;
					}
				}
		}
}

int check=0;
char before_B='0';
void edit_map()
{
	
	char save_how;
	FILE *pf;
	pf=fopen(name,"r+");
	int map_x;
	int map_y;
	char h;
	int i;
	system("cls");
	if(sizecheck)
	{
		printf("			맵의 가로길이(최대 12):");
		scanf("%d",&map_x);
		printf("			맵의 세로길이(최대 12):");
		scanf("%d",&map_y);
		for(int i=0;i<map_y;i++)
		{
			for(int j=0;j<map_x;j++)
			{
				if(field[i][j]==NULL || field[i][j]=='\n')
					field[i][j]='0';
			}
		}
		field[y][x]='0';
		before_B=field[cur_y][cur_x/2];
		sizecheck=0;
		system("cls");
	}
	field[cur_y][cur_x/2]='5';
	for(i=0;i<map_y;i++)
	{
		if(i==0)
		{
			printf("                                                ");
			for(int j=0;j<map_x+1;j++)
				printf("□");
			printf("□\n");
		}
		printf("                                                ");
		printf("□");
		for(int j=0;j<map_x;j++)
		{
			if(field[i][j]=='4')
				printf("◇"); 
			else if(field[i][j]=='1')
				printf("■");	
			else if(field[i][j]=='2')
					printf("●");
			else if(field[i][j]=='3')
					printf("□");
			else if(field[i][j]=='0')
				printf("  ");
			else if(field[i][j]=='5')
				printf("⊙");
		}
		printf("□\n");
		if(i==map_y-1)
		{
			printf("                                                ");
			for(int j=0;j<map_x+1;j++)
				printf("□");
			printf("□\n");
		}
	}
	printf("\n\n\n\n");
	printf("                                                  1:■\n");
	printf("                                                  2:●\n");
	printf("                                                  3:□\n");
	printf("                                                  4:◇\n");
	printf("                                                  d:지우기\n");
	printf("                                                  r:모두 지우기\n");
	printf("                                                  e:맵 에디터 종료\n");
	h=getch();
	switch(h)
	{
		case 'e':
			{
				fclose(pf);
				scene=0;
				return;
			}
		case 'd':
			{
				if(before_B=='H')
				{
					g--;
				}
				else if(before_B=='@')
				{
					H--;
				}
				field[cur_y][cur_x/2]='0';
				before_B='0';
				if(cur_x==map_x-1&&cur_y==map_y-1)
				{
					before_B=field[0][0];
					cur_y=0;
					cur_x=0;
				}
				else if(cur_x/2==map_x-1)
				{
					cur_y++;
					cur_x=0;
				}
				else
					{
						before_B=field[cur_y][cur_x/2+1];
						cur_x+=2;
					}
				break;		
			}
		case 'r':
			{
				for(int i=0;i<map_x;i++)
				{
					for(int j=0;j<map_y;j++)
					{
						field[j][i]='0';
					}
				}
				before_B='0';
				cur_x=0;
				cur_y=0;
				check=0;
				g=0;
				H=0;
				break;
			}
		case enter:
			{
				if(H==0||g==0)
				{
					gotoxy(41,6);
					printf("집이나 공을 만들지 않았음");
					sleep(1);
				}
				else if(H!=g)
				{
					gotoxy(41,6);
					printf("집의 갯수와 공의 갯수가 다름"); 
					sleep(1);
				}
				else if(check==0)
				{
					gotoxy(41,7);
					printf("플레이어를 만들지 않았음");
					sleep(1);
				}
				else
				{
					char save_how;
					gotoxy(65,4);
					printf("이대로 맵을 저장하시겠습니까?");
					gotoxy(65,6);
					printf("저장하기:enter   취소:esc");
					save_how=getch();
					if(save_how==enter)
					field[cur_y][cur_x]='0';
					save_how=getch();
					if(save_how==13)
					{
						for(int i=0;i<=map_y;i++)
						{
							for(int j=0;j<=map_x;j++)
							{
								if(field[i][j]==NULL || field[i][j]=='\n')
									field[i][j]='0';
							}
						}
						fprintf(pf,"%d %d %d %d %d\n",char_x/2-1,char_y-1,H,map_x,map_y);
						for(int i=0;i<map_y;i++)
						{
							for(int j=0;j<map_x;j++)
							{
								if(field[i][j]!='+')
									fprintf(pf,"%c",field[i][j]);
							}
							fprintf(pf,"\n");
						}
						system("cls");
						printf("새로운 맵 생성이 완료됨.");
						fclose(pf);
						sleep(1);
						scene=0;
					}
					
				}
				break;
			}
		case '1':
			{
				if(before_B=='3')
					g--;
				else if(before_B=='2')
					H--;
				else if(before_B=='4')
					check=0;
				field[cur_y][cur_x/2]='1';
				if(cur_x==map_x-1&&cur_y==map_y-1)
				{
					before_B=field[0][0];
					cur_y=0;
					cur_x=0;
				}
				else if(cur_x/2==map_x-1)
				{
					before_B=field[cur_y+1][0];
					cur_y++;
					cur_x=0;
				}
				else
					{
						before_B=field[cur_y][cur_x/2+1];
						cur_x+=2;
					}
				printf("%c",field[cur_y][cur_x/2]);
				break;
			}
		case '2':
			{
				if(before_B=='3')
					g--;
				else if(before_B=='2')
					H--;
				else if(before_B=='4')
					check=0;
				H++;
				field[cur_y][cur_x/2]='2';
				if(cur_x==map_x-1&&cur_y==map_y-1)
				{
					before_B=field[0][0];
					cur_y=0;
					cur_x=0;
				}
				else if(cur_x/2==map_x-1)
				{
					before_B=field[cur_y+1][0];
					cur_y++;
					cur_x=0;
				}
				else
					{
						before_B=field[cur_y][cur_x/2+1];
						cur_x+=2;
					}
				printf("%c",field[cur_y][cur_x/2]);
				break;
			}
		case '3':
			{
				if(before_B=='3')
					g--;
				else if(before_B=='2')
					H--;
				else if(before_B=='4')
					check=0;
				g++;
				field[cur_y][cur_x/2]='3';
				if(cur_x==map_x-1&&cur_y==map_y-1)
				{
					before_B=field[0][0];
					cur_y=0;
					cur_x=0;
				}
				else if(cur_x/2==map_x-1)
				{
					before_B=field[cur_y+1][0];
					cur_y++;
					cur_x=0;
				}
				else
					{
						before_B=field[cur_y][cur_x/2+1];
						cur_x+=2;
					}
				printf("%c",field[cur_y][cur_x/2]);
				break;
			}
		case '4':
			{
				if(before_B=='3')
					g--;
				else if(before_B=='2')
					H--;
				else if(before_B=='4')
					check=0;
				check=1;
				field[char_y][char_x/2]='0';
				field[cur_y][cur_x/2]='4';
				char_x=cur_x;
				char_y=cur_y;
				if(cur_x==map_x-1&&cur_y==map_y-1)
				{
					before_B=field[0][0];
					cur_y=0;
					cur_x=0;
				}
				else if(cur_x/2==map_x-1)
				{
					before_B=field[cur_y+1][0];
					cur_y++;
					cur_x=0;
				}
				else
					{
						before_B=field[cur_y][cur_x/2+1];
						cur_x+=2;
					}
				printf("%c",field[cur_y][cur_x/2]);
				break;
			}
		case left:
			{
				if(cur_x-1>=0)
				{
					field[cur_y][cur_x/2]=before_B;
					before_B=field[cur_y][cur_x/2-1];
					cur_x-=2;
				}
				break;
			}
		case right:
			{
				if(cur_x/2+1<map_x)
				{
					field[cur_y][cur_x/2]=before_B;
					before_B=field[cur_y][cur_x/2+1];
					cur_x+=2;
				}
				break;
			}
		case up:
			{
				if(cur_y-1>=0)
				{
					field[cur_y][cur_x/2]=before_B;
					before_B=field[cur_y-1][cur_x/2];
					cur_y--;
				}
				break;
			}
		case down:
			{
				if(cur_y+1<map_y)
				{
					field[cur_y][cur_x/2]=before_B;
					before_B=field[cur_y+1][cur_x/2];
					cur_y++;
				}
				break;
			}
	}
}
void main_move()
{
	char m=0;
	m=getch();
		switch(m)
		{
			case up:
				{
					if(sellect==1)
						{
							sellect=4;
							break;
						}
					sellect--;
					break;
				}
			case down:
				{
					if(sellect==4)
						{
							sellect=1;
							break;
						}
					sellect++;
					break;
				}
			case enter:
				{
					if(sellect==1)
					{
						scene=1;
					}
					else if(sellect==2)
					{
						scene=-1;
					}
					else if(sellect==4)
					{
						exit(1);
					}
					else
					{
						sellect=1;
						scene=-2;
					}
				}
		}
}
void main_scene()
{
	int m;
	while(scene==0)
	{
		system("cls");
		printf("           <push push>\n");
		printf("           "); 
		if(sellect==1)
			printf("●");
		printf("게임 시작\n");
		printf("           "); 
		if(sellect==2)
			printf("●");
		printf("게임 방법\n");
		printf("           "); 
		if(sellect==3)
			printf("●");
		printf("맵 에디터\n");
		printf("           ");
		if(sellect==4)
			printf("●");
		printf("게임 종료\n");
		main_move();
	}
}
void map_load()
{
	FILE *pf;
	strcpy(name,"map");
	tmp[0]=scene+48;
	strcat(name,tmp);
	strcat(name,".txt");
	pf=fopen(name,"r");
	int i=0;
	if(pf==NULL) 
	{	
		scene=0;
		sellect=1;
		system("cls");
		printf("                                             !!all clear!!!");
		sleep(1);
		system("cls");
		printf("                                            메인메뉴:1\n");
		printf("                                             게임 종료:2\n");
		char a;
		a=getch();
		if(a=='1')
		{
			scene=0; 
			main();
			return;
		}
		else if(a=='2')
		{
			exit(1);
		}
	}
	fscanf(pf,"%d %d %d %d %d\n",&x,&y,&rest,&map_x,&map_y);
	x*=2;
	while(1)
	{	
		fgets(name,sizeof(name),pf);
		strcpy(field[i],name);
		if(feof(pf))
			break;
		i++;
	}
	fclose(pf);
}
int map_load(int num)
{
	FILE *pf;
	strcpy(name,"map");
	tmp[0]=num+48;
	strcat(name,tmp);
	strcat(name,".txt");
	pf=fopen(name,"r");
	int i=0;
	if(pf==NULL)
	{
		return 0;
	}
	fscanf(pf,"%d %d %d %d %d\n",&x,&y,&rest,&map_x,&map_y);
	while(1)
	{	
		fgets(name,sizeof(name),pf);
		strcpy(field[i],name);
		if(feof(pf))
			break;
		i++;
	}
	return 1;
}
int main()
{
	removecursor();
	char h;
	field[y][x]='!';
	while(1)
	{
	
		if(scene==0)
			main_scene();
		else if(scene>=1)
		{
			system("cls");
			map_load();
			map();
			move();
		}
		else if(scene==-1)
		{
			system("cls");
			printf("→:오른쪽 이동\n");
			printf("←:왼쪽 이동\n");
			printf("↑:위로 이동\n");
			printf("↓:아래로 이동\n");
			printf("!:캐릭터\n");
			printf("@:공\n");
			printf("H:집\n\n");
			printf("캐릭터로 공을 밀어 집으로 집어 넣으십시오!\n모든 공을 집에 넣는다면 승리합니다!\n\n");
			printf("enter키를 누르면 게임을 시작합니다.\n");
			printf("e키를 누르면 게임을 종료합니다.\n");
			printf("esc키를 누르면 메인메뉴로 나갑니다.\n");
			h=getch();
			if(h==enter)
			{
				scene=1;
				continue;
			} 
			else if(h==esc)
			{
				scene=0;
				continue;
			}
			else if(h=='e'||h=='E')
			{
				exit(1);
			}
		}
		else if(scene==-2)
		{
			system("cls");
			printf("           ");
		if(sellect==1)
			printf("●");
		printf("1.신규 맵 제작\n");
		printf("           "); 
		if(sellect==2)
			printf("●");
		printf("2.기존 맵 수정\n");
		printf("           "); 
		if(sellect==3)
			printf("●");
		printf("3.맵 에디터 종료\n");
		edit_move();
		}
		else if(scene==-3)
		{
			edit_map();
		}
	}
}
