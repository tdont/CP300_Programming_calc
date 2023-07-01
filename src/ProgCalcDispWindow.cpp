#include "ProgCalcDispWindow.hpp"
#include <stdlib.h>


#include <stdio.h>
#ifdef WIN32
#include <stdio.h>
#endif


#define VALDISP_VERTICAL_INTERVAL (12)
#define VALDISP_VERTICAL_OFFSET (2)
#define VALDISP_HORIZ_INTERVAL  (38)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c %c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 



ProgCalcDisplayWindow::ProgCalcDisplayWindow(PegRect rect):CPWindow(rect)
{
    PegThing *valueDisplayer = new PegThing(rect);
    m_rdbtn_hex = new PegRadioButton(rect.wLeft + 2, rect.wTop + VALDISP_VERTICAL_OFFSET, "HEX:", CSTM_EVENT_HEX);
    valueDisplayer->Add(m_rdbtn_hex);
    m_pgprmt_hex = new PegPrompt(VALDISP_HORIZ_INTERVAL, rect.wTop + 2 + VALDISP_VERTICAL_OFFSET, (PEGCHAR*)"HEX Value");
    valueDisplayer->Add(m_pgprmt_hex);

    m_rdbtn_dec = new PegRadioButton(rect.wLeft + 2, rect.wTop + VALDISP_VERTICAL_OFFSET + 1* VALDISP_VERTICAL_INTERVAL, "DEC:", CSTM_EVENT_DEC);
    valueDisplayer->Add(m_rdbtn_dec);  
    m_pgprmt_dec = new PegPrompt(VALDISP_HORIZ_INTERVAL, rect.wTop + 2 + VALDISP_VERTICAL_OFFSET + 1* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"DEC Value     ");
    valueDisplayer->Add(m_pgprmt_dec);

    m_rdbtn_oct = new PegRadioButton(rect.wLeft + 2, rect.wTop + VALDISP_VERTICAL_OFFSET + 2* VALDISP_VERTICAL_INTERVAL , "OCT:", CSTM_EVENT_OCT);
    valueDisplayer->Add(m_rdbtn_oct);
    m_pgprmt_oct = new PegPrompt(VALDISP_HORIZ_INTERVAL, rect.wTop + 2 + VALDISP_VERTICAL_OFFSET + 2* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"OCT Value     ");
    valueDisplayer->Add(m_pgprmt_oct);

    m_rdbtn_bin = new PegRadioButton(rect.wLeft + 2, rect.wTop + VALDISP_VERTICAL_OFFSET + 3* VALDISP_VERTICAL_INTERVAL, "BIN:", CSTM_EVENT_BIN);
    valueDisplayer->Add(m_rdbtn_bin);
    m_pgprmt_bin = new PegPrompt(VALDISP_HORIZ_INTERVAL, rect.wTop + 2 + VALDISP_VERTICAL_OFFSET + 3* VALDISP_VERTICAL_INTERVAL,          (PEGCHAR*)"BIN Value (MSB)     ");
    valueDisplayer->Add(m_pgprmt_bin);
    m_pgprmt_bin_2nd_line = new PegPrompt(VALDISP_HORIZ_INTERVAL, rect.wTop + 2 + VALDISP_VERTICAL_OFFSET + 4* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"BIN 2nd line (LSB)  ");
    valueDisplayer->Add(m_pgprmt_bin_2nd_line);

    Add(valueDisplayer);

    /* Select by default Decimal entry */
    m_rdbtn_dec->SetSelected(true);
}

ProgCalcDisplayWindow::~ProgCalcDisplayWindow()
{
   /* Do not delete dynamically allocated PEG things as it seems to cause double free */
}

void ProgCalcDisplayWindow::display_value(ProgClassValue& value)
{
    display_value_hex(value);
    display_value_bin(value);
    display_value_dec(value);
    display_value_oct(value);

    Draw();

    return;
}

typingmode_t ProgCalcDisplayWindow::getSelectedInputType()
{
    typingmode_t ret_val = TYPING_MODE_UNKNOWN;
    if(m_rdbtn_bin && m_rdbtn_bin->IsSelected())
    {
        ret_val = TYPING_MODE_BIN;
    }
    else if(m_rdbtn_hex && m_rdbtn_hex->IsSelected())
    {
        ret_val = TYPING_MODE_HEX;
    }
    else if(m_rdbtn_oct && m_rdbtn_oct->IsSelected())
    {
        ret_val = TYPING_MODE_OCT;
    }
    else if(m_rdbtn_dec && m_rdbtn_dec->IsSelected())
    {
        ret_val = TYPING_MODE_DEC;
    }

    return ret_val;
}

void ProgCalcDisplayWindow::display_value_hex(ProgClassValue& value)
{
    static CP_CHAR hex_value[9] = {0};

    //CP_LongToStringHex(value.get_value(), hex_value);
    sprintf((char*)hex_value, "%X", value.get_value());

    hex_value[8] = 0;
    m_pgprmt_hex->DataSet((const PEGCHAR*) hex_value);
    return;
}

void ProgCalcDisplayWindow::display_value_bin(ProgClassValue& value)
{
    static CP_CHAR bin_value[33] = {0};
    static CP_CHAR bin_value_2ndline[33] = {0};

    sprintf((char*)bin_value, BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN, 
                                    BYTE_TO_BINARY(((value.get_value() & 0xFF000000) >> 24)),
                                    BYTE_TO_BINARY((value.get_value() & 0xFF0000) >> 16));

    sprintf((char*)bin_value_2ndline, BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN, 
                                    BYTE_TO_BINARY(((value.get_value() & 0xFF00) >> 8)),
                                    BYTE_TO_BINARY((value.get_value() & 0xFF)));

    m_pgprmt_bin->DataSet((const PEGCHAR*) bin_value);
    m_pgprmt_bin_2nd_line->DataSet((const PEGCHAR*) bin_value_2ndline);
    
    return;
}

void ProgCalcDisplayWindow::display_value_oct(ProgClassValue& value)
{
    static CP_CHAR oct_value[20] = {0};
    sprintf((char*)oct_value, "%o", value.get_value());

    m_pgprmt_oct->DataSet((const PEGCHAR*) oct_value);

    return;
}

void ProgCalcDisplayWindow::display_value_dec(ProgClassValue& value)
{
    static CP_CHAR dec_value[12] = {0};
    if (value.get_mode() == MODE_UNSIGNED)
    {        
        sprintf((char*)dec_value, "%lu", value.get_value());
    }
    else
    {
        sprintf((char*)dec_value, "%ld", value.get_value());
    }

    m_pgprmt_dec->DataSet((const PEGCHAR*) dec_value);
    
    return;
}
