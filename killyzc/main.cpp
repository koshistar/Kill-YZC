#include"head.h"
#include<graphics.h>
int main()
{
	initgraph(swidth, sheight, EW_NOMINIMIZE | EW_SHOWCONSOLE);
	bool is_live = true;

	while (is_live)
	{
		Welcome();
		is_live = Play();
	}
	return 0;
}