#ifndef _SPELL_H_
#define _SPELL_H_

#include "extern.h"
#include "graph.h"

struct SPELLDATA{
	float	x,
		y,
		large,
		angle,
		f_hanyou[8];
	int	img,
		count,
		player,
		flash,
		type,
		i_hanyou[8];
	bool	bDelete;
};

extern list<SPELLDATA> Spell;

extern void SpLoad();
extern void SpMake(float x,float y,int type,int player);
extern void SpDraw();
extern void SpMove(list<SPELLDATA>::iterator &it);

#endif