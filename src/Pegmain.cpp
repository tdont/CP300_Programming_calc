
#include "HelloWindow.h"
#include "pegmain.hpp"

/*--------------------------------------------------------------------------*/
void PegAppInitialize(PegPresentationManager *pPresentation)
{
	// create some simple Windows: 
	
	PegRect Rect;
	Rect.Set(MAINFRAME_LEFT, MAINFRAME_TOP, MAINFRAME_RIGHT, MAINFRAME_BOTTOM);

	CPMainFrame *mw = new CPMainFrame(Rect);

	PegRect ChildRect = mw->FullAppRectangle();
	HelloWindow* swin = new HelloWindow(ChildRect,mw);
	mw->SetTopWindow(swin);

	// Set a main window for this module.  In our case, it is the hello window
	mw->SetMainWindow(swin);

	pPresentation->Add(mw);
}




