#ifndef _SPELL_H_
#define _SPELL_H_

#include "extern.h"
#include "graph.h"

struct SPELLDATA{
	float	x,
		y,
		large,
		angle,
		spark_angle,
		haba,
		f_hanyou[8];
	int	img,
		count,
		player,
		flash,
		type,
		level,
		i_hanyou[8];
	bool	bDelete;
};

extern list<SPELLDATA> Spell;

extern void SpLoad();
extern void SpMake(float x,float y,int type,int player,int level,bool special=false);
extern void SpDraw();
extern void SpMove(list<SPELLDATA>::iterator &it);
extern int SpAtari(list<SPELLDATA>::iterator &it, bool bDeath=true);

#endif