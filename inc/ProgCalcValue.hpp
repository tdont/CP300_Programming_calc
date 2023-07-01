#ifndef PROGCALC_VALUE_H
#define PROGCALC_VALUE_H

#include "ClassPad.h"
#include "progCalcShared.h"

class ProgClassValue
{
    public:
    ProgClassValue(DWORD value, mode_signed_t mode, length_t length);
    virtual ~ProgClassValue();

    DWORD get_value();
    mode_signed_t get_mode();
    length_t get_length();

    void set_value(DWORD);
    void set_mode(mode_signed_t);
    void set_length(length_t);

    private:
    DWORD m_value;
    mode_signed_t m_mode;
    length_t m_length;

};

#endif
