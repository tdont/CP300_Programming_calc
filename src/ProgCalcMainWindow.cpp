#include "ClassPad.h"

#include "ProgCalcMainWindow.hpp"
#include "progCalcShared.h"
#include "ProgCalcDispWindow.hpp"
#include "ProgCalcValue.hpp"

#include <stdlib.h>
#ifdef WIN32
#include <time.h>
#include <stdio.h>
#endif

#define MAINWINDOW_VERTICAL_INTERVAL (12)

/* SubMendu definitions */
PegMenuDescriptionML SubMenuMode[] = 
{
    {"Signed", CMN_NO_ID, CSTM_EVENT_MODE_SIGNED, AF_ENABLED, NULL },
    {"Unsigned", CMN_NO_ID, CSTM_EVENT_MODE_UNSIGNED, AF_ENABLED, NULL },
    {"", CMN_NO_ID, 0, 0, 0}
};

PegMenuDescriptionML SubMenuLength[] = 
{
    {" 8 bits", CMN_NO_ID, CSTM_EVENT_TYPE_BYTE, AF_ENABLED, NULL },
    {"16 bits", CMN_NO_ID, CSTM_EVENT_TYPE_WORD, AF_ENABLED, NULL },
    {"32 bits", CMN_NO_ID, CSTM_EVENT_TYPE_DWORD, AF_ENABLED, NULL },
    {"", CMN_NO_ID, 0, 0, 0}
};

/* Menu Definition */
PegMenuDescriptionML MainMenu[] =
{
    {"Mode", CMN_NO_ID, 0, AF_ENABLED, SubMenuMode },
    {"Length", CMN_NO_ID, 0, AF_ENABLED, SubMenuLength },
    {"", CMN_NO_ID, 0, 0, 0}
};



ProgCalcMainWindow::ProgCalcMainWindow(PegRect rect, CPMainFrame *frame) :CPModuleWindow(rect,0,0,frame)
{
  m_selectedLength = LENGTH_32BIT;
  m_selectedMode = MODE_UNSIGNED;
  HasLines = false;
	//SetScrollMode(WSM_AUTOSCROLL);

  PegPrompt* m_pgprmt_history = new PegPrompt(25, 2, "History Of Command");
  AddR(m_pgprmt_history);

  CPPegString* m_pgstr_input = new CPPegString(2, 2 + MAINWINDOW_VERTICAL_INTERVAL, 150, NULL, CSTM_EVENT_INPUT_STRING);
  AddR(m_pgstr_input);
  m_pgstr_input->SetSignals(SIGMASK(PSF_TEXT_EDIT));
  SetDefaultFocus(m_pgstr_input);

  PegRect rectValDisplayer = mClient;
  rectValDisplayer.wTop = mClient.wTop + 2 * 15;
  rectValDisplayer.wBottom = rectValDisplayer.wTop + 64;
  m_dispWin = new ProgCalcDisplayWindow(rectValDisplayer);
  Add(m_dispWin);

  // PegRect r = mClient;
  // r -= 20; // make the pan window a bit smaller
  // m_panWin = new PanWindow(r);
  //Add(m_panWin);
}    

ProgCalcMainWindow::~ProgCalcMainWindow()
{
  /* Do not delete dynamically allocated PEG things as it seems to cause double free */
}

PegMenuDescriptionML* ProgCalcMainWindow::GetMenuDescriptionML()
{
    return MainMenu;    
}

//Add UI creates the toolbar buttons
void ProgCalcMainWindow::AddUI()
{
	PegTextButton *b = NULL;
	b = new PegTextButton(4,0,"AND",CSTM_EVENT_OP_AND);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"OR",CSTM_EVENT_OP_OR);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"NOT",CSTM_EVENT_OP_NOT);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"XOR",CSTM_EVENT_OP_XOR);
	m_ui->AddToolbarButton(b);
    b = new PegTextButton(4,0,"<<",CSTM_EVENT_LSH);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,">>",CSTM_EVENT_RSH);
	m_ui->AddToolbarButton(b);

}

//The overridden drawn function.
void ProgCalcMainWindow::Draw()
{
	BeginDraw();
	DrawFrame();

  DrawWidget();

	DrawChildren();
	EndDraw();
}

SIGNED ProgCalcMainWindow::Message(const PegMessage &Mesg)
{
  PEGCHAR* data = 0;
  ProgClassValue input_value(125, m_selectedMode, m_selectedLength);

  CPPegString* ptr_to_things_emiting = 0;

	switch(Mesg.wType)
    {
      case SIGNAL( CSTM_EVENT_TYPE_BYTE, PSF_CLICKED):	
        m_selectedLength = LENGTH_8BIT;
        break;
      case SIGNAL( CSTM_EVENT_TYPE_WORD, PSF_CLICKED):	
        m_selectedLength = LENGTH_16BIT;
        break;
      case SIGNAL( CSTM_EVENT_TYPE_DWORD, PSF_CLICKED):	
        m_selectedLength = LENGTH_32BIT;
        break;
      case SIGNAL( CSTM_EVENT_MODE_SIGNED, PSF_CLICKED):	
        m_selectedMode = MODE_SIGNED;
        break;
      case SIGNAL( CSTM_EVENT_MODE_UNSIGNED, PSF_CLICKED):	
        m_selectedMode = MODE_UNSIGNED;
        break;
      case SIGNAL( CSTM_EVENT_OP_AND, PSF_CLICKED):	

        break;
      case SIGNAL( CSTM_EVENT_OP_OR, PSF_CLICKED):	

        break;
      case SIGNAL( CSTM_EVENT_OP_NOT, PSF_CLICKED):	

        break;
      case SIGNAL( CSTM_EVENT_OP_XOR, PSF_CLICKED):	

        break;
      case SIGNAL( CSTM_EVENT_RSH, PSF_CLICKED):	

        break;
      case SIGNAL( CSTM_EVENT_LSH, PSF_CLICKED):	

        break;
      case SIGNAL (CSTM_EVENT_HEX, PSF_DOT_ON):

        break;
      case SIGNAL (CSTM_EVENT_OCT, PSF_DOT_ON):

        break;
      case SIGNAL (CSTM_EVENT_DEC, PSF_DOT_ON):

        break;
      case SIGNAL (CSTM_EVENT_BIN, PSF_DOT_ON):

        break;
      case SIGNAL (CSTM_EVENT_INPUT_STRING, PSF_TEXT_EDIT):
        /* Retrieve the value typed in */
        ptr_to_things_emiting = (CPPegString*) Mesg.pSource;
        data = ptr_to_things_emiting->DataGet();

        /* Convert it to a value */
        /* TODO handle the selected input mode (8, 16 or 32 bits and Hex, Binary, Octal, Decimal)*/
        input_value.set_value(CP_StringToLong((CP_CHAR *)data));
        m_dispWin->display_value(input_value);
        break;
 	  default:
          return CPModuleWindow::Message(Mesg);
          break;
    }
    updateStatusBar();
    return 0;
}

void ProgCalcMainWindow::DrawWidget(void)
{    
    updateStatusBar();
}

void ProgCalcMainWindow::updateStatusBar()
{
    static PEGCHAR statusText[20];
    for (int i = 0; i < 20; i++)
    {
      statusText[i] = ' ';
    }

    switch(m_selectedMode)
    {
      case MODE_UNSIGNED:
        memcpy(statusText, "unsigned", 8);
        break;
      case MODE_SIGNED:
        memcpy(statusText, "  signed", 8);
        break;
      default:
        memcpy(statusText, " unknown", 8);
      break;
    }  

    switch(m_selectedLength)
    {
      case LENGTH_8BIT:
        memcpy(&statusText[12], " 8 bits", 7);
        break;
      case LENGTH_16BIT:
        memcpy(&statusText[12], "16 bits", 7);
        break;
      case LENGTH_32BIT:
        memcpy(&statusText[12], "32 bits", 7);
      break;
      default:
        memcpy(&statusText[12], " unknown", 8);
      break;
    }  
    
    /* Set end of string */
    statusText[sizeof(statusText) - 1] = 0;
   
    PegStatusBar* bar = GetStatusBar();
    if (bar != 0)
    {
      bar->SetTextField(1, statusText);
    }
    // Set the text
    //SetStatusBar(statusText);
}
 
