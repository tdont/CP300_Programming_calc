#ifndef PROGCALC_MAINWINDOW_H
#define PROGCALC_MAINWINDOW_H

#include "ClassPad.h"
#include "ProgCalcDispWindow.hpp"



class ProgCalcMainWindow : public CPModuleWindow
{
    public:
	ProgCalcMainWindow(PegRect rect, CPMainFrame* frame); 
 	virtual ~ProgCalcMainWindow();
  
    virtual SIGNED Message(const PegMessage &Mesg);
	virtual PegMenuDescriptionML* GetMenuDescriptionML();
    virtual void AddUI();
		
    virtual void Draw();
	void DrawWidget(void);
	
	void updateStatusBar();
	
	private:
	ProgCalcDisplayWindow* m_dispWin;
	mode_signed_t m_selectedMode;
	length_t m_selectedLength;
	CPPegString* m_pgstr_input;
	PegPrompt* m_pgprmt_history;
	bool HasLines;
};    

#endif
