#include "ClassPad.h"
#include "ProgCalcMainWindow.hpp"

//////////////////////////////////////////////////////////////////

void PegAppInitialize(PegPresentationManager *pPresentation)
{
	// create some simple Windows: 
	PegRect Rect;
	Rect.Set(MAINFRAME_LEFT, MAINFRAME_TOP, MAINFRAME_RIGHT, MAINFRAME_BOTTOM);

	CPMainFrame *mainFrame = new CPMainFrame(Rect);
    // Create your window(s)
	PegRect childRect = mainFrame->FullAppRectangle();	
	ProgCalcMainWindow *mainWindow = new ProgCalcMainWindow(childRect,mainFrame);
    // Load the window into the MainFrame
    mainFrame->SetTopWindow(mainWindow);
    // Set a main window for this module.
    mainFrame->SetMainWindow(mainWindow);
    
    // Add the MainFrame to the Peg Presentation Manager
	pPresentation->Add(mainFrame);
};



//////////////////////////////////////////////////////////////////

extern "C" char *ExtensionGetLang(ID_MESSAGE MessageNo)
{
	return "";
}

//////////////////////////////////////////////////////////////////
