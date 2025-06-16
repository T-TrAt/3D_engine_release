#pragma once
#include "Widget.h"
#include <easyx.h>
#include <sstream>
#define FACE_NAME_SIZE 32
class Text {
public:
    static LONG height;
    static int line;

    LOGFONT             font;       // ����
    int                 thisLine;   // ��������
    std::wostringstream content;    // ����
    Text();
    Text(int x);

    virtual void putText();
    ~Text();
};

class SmallText : public Text {
public:
    static LONG height_ST;

    SmallText();

    void putText(int x, int y);
};