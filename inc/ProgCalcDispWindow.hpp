#ifndef PROGCALC_DISPWINDOW_H
#define PROGCALC_DISPWINDOW_H

#include "ClassPad.h"
#include "ProgCalcValue.hpp"

class ProgCalcDisplayWindow : public CPWindow
{
    public:
    ProgCalcDisplayWindow(PegRect rect);
    virtual ~ProgCalcDisplayWindow();
	
	// void AddText(PEGCHAR* txt);
    void display_value(ProgClassValue& value);

    typingmode_t getSelectedInputType();
	
private:
    void display_value_hex(ProgClassValue& value);
    void display_value_bin(ProgClassValue& value);
    void display_value_oct(ProgClassValue& value);
    void display_value_dec(ProgClassValue& value);

    PegRadioButton* m_rdbtn_hex;
    PegRadioButton* m_rdbtn_dec;
    PegRadioButton* m_rdbtn_oct;
    PegRadioButton* m_rdbtn_bin;
    PegPrompt* m_pgprmt_hex;
    PegPrompt* m_pgprmt_dec;
    PegPrompt* m_pgprmt_oct;
    PegPrompt* m_pgprmt_bin;
    PegPrompt* m_pgprmt_bin_2nd_line;
};    

#endif
