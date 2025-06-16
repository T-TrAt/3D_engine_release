#include "Global.h"
#include "Text.h"
LONG Text::height = 18;
int Text::line = 0;

Text::Text() {

    // ��������
    content.str(L"");
    content.clear();
    // ������
    thisLine = line;
    line++;
    // ��������ṹ��
    memset(&font, 0, sizeof(LOGFONT));

    // ������������
    font.lfHeight    = height;   // ����߶�
    font.lfWidth     = 0;       // �����ȣ�0 ��ʾ���ݸ߶��Զ�����
    font.lfWeight    = FW_BOLD; // ����Ӵ�
    font.lfItalic    = false;   // ���岻��б
    font.lfUnderline = false;   // ����û���»���
    wcscpy_s(font.lfFaceName, FACE_NAME_SIZE, _T("����")); // ��������

    settextstyle(&font);        // ���õ�ǰ����

    setbkmode(TRANSPARENT);     // ���ñ���ģʽΪ͸��

}

Text::Text(int x) {}

void Text::putText() {

    setorigin(0, 0);
    setaspectratio(1, 1);

    std::wstring strS = content.str();
    LPCTSTR      strL = strS.c_str();
    settextcolor(WHITE); //0xd0fc53
    RECT r = { 10, 10 + thisLine * height, SCREENW * 2 / 5, 10 + (thisLine + 1) * height };
    settextstyle(&font);
    drawtext(strL, &r, DT_LEFT | DT_TOP);   // ��Ϣ����ʾ
    content.str(L"");   // ��������
    content.clear();    

    setorigin(0, SCREENH);
    setaspectratio(1, -1);
}

LONG SmallText::height_ST = 9;

SmallText::SmallText(): Text(1) {

    // ��������
    content.str(L"");
    content.clear();

    // ��������ṹ��
    memset(&font, 0, sizeof(LOGFONT));

    // ������������
    font.lfHeight    = height_ST;   // ����߶�
    font.lfWidth     = 0;           // �����ȣ�0 ��ʾ���ݸ߶��Զ�����
    font.lfWeight    = FW_BOLD;     // ����Ӵ�
    font.lfItalic    = false;       // ���岻��б
    font.lfUnderline = false;       // ����û���»���
    wcscpy_s(font.lfFaceName, FACE_NAME_SIZE, _T("����")); // ��������

    settextstyle(&font);        // ���õ�ǰ����
    setbkmode(TRANSPARENT);     // ���ñ���ģʽΪ͸��
}

void SmallText::putText(int x, int y) {

    setorigin(0, 0);
    setaspectratio(1, 1);

    std::wstring strS = content.str();
    LPCTSTR      strL = strS.c_str();
    settextcolor(WHITE);
    RECT r = { x, y, x + height_ST * 10, y + height_ST };
    settextstyle(&font);
    drawtext(strL, &r, DT_LEFT | DT_TOP);   // ��Ϣ����ʾ
    content.str(L"");   // ��������
    content.clear();

    setorigin(0, SCREENH);
    setaspectratio(1, -1);
}

Text::~Text() {
    line--;
}