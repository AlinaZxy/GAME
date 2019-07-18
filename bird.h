#pragma once
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;
void Createbird();

int isdead(int x, int y, int *a, int *b, int &i, int &j);
