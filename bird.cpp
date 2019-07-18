#include"bird.h"
#include<stdio.h>
#include<malloc.h>
// 创建一只鸟
void Createbird()
{
	PGAME_COORD p;
	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	p->x = 30;
	p->y = 120;
	return;
}
//判断是否死亡
int isdead(int x, int y, int *a, int *b,int &i,int &j)
{
	while(x == b[j])
	{
		if ((j % 2) == 0 && y >= 600-a[i])
			return 1;
		if ((j % 2) == 0)
		{   i += 7;
		    j++;
			break;
		}
		if ((j % 2) == 1 && y <= a[i])
			return 1;
		if ((j % 2) == 1)
		{
			i -= 6;
			j++;
			break;
		}
	}
	if (x > 1450) { return 2; }
	return 0;
}
