#include "HelloWindow.h"
//////////////////
///// ScribbleWindow functions
//////////////////

/// This is the over-written draw function for the Hello Window
void HelloWindow::Draw()
{
	BeginDraw();
	Invalidate(mClient); 
	DrawFrame();
	AddR(new PegPrompt(10, 10, "Hello World"));
	EndDraw();
}

extern "C" char *ExtensionGetLang(ID_MESSAGE MessageNo)
{
	return "";
}


