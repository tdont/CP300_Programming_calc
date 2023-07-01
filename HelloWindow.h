#ifndef EXAMPLE_INCLUDED
#define EXAMPLE_INCLUDED

#include "cfc.h"

class HelloWindow: public CPModuleWindow
{
public:

	HelloWindow(PegRect rect,CPMainFrame* frame)
		:CPModuleWindow(rect,0,0,frame)
	{
	}
	
	~HelloWindow(){}
	
/// Overwritten draw function Draws the frame, and Adds "Hello World" 	
	void Draw();

};

#endif

