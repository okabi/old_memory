#ifndef _PARA_H_
#define _PARA_H_

#include "extern.h"
#include "player.h"
#include "graph.h"

class CLASS_PARA{
private:
	int count;
public:
	int time_count;
	int start_count;
	void draw();
};

extern CLASS_PARA Para;

extern void ParaMain();

#endif