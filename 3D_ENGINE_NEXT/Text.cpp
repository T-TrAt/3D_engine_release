#include "Global.h"
#include "Text.h"
LONG Text::height = 18;
int Text::line = 0;

Text::Text() {

    // 重置内容
    content.str(L"");
    content.clear();
    // 设置行
    thisLine = line;
    line++;
    // 清零字体结构体
    memset(&font, 0, sizeof(LOGFONT));

    // 设置字体属性
    font.lfHeight    = height;   // 字体高度
    font.lfWidth     = 0;       // 字体宽度，0 表示根据高度自动调整
    font.lfWeight    = FW_BOLD; // 字体加粗
    font.lfItalic    = false;   // 字体不倾斜
    font.lfUnderline = false;   // 字体没有下划线
    wcscpy_s(font.lfFaceName, FACE_NAME_SIZE, _T("等线")); // 字体名称

    settextstyle(&font);        // 设置当前字体

    setbkmode(TRANSPARENT);     // 设置背景模式为透明

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
    drawtext(strL, &r, DT_LEFT | DT_TOP);   // 信息行显示
    content.str(L"");   // 重置内容
    content.clear();    

    setorigin(0, SCREENH);
    setaspectratio(1, -1);
}

LONG SmallText::height_ST = 9;

SmallText::SmallText(): Text(1) {

    // 重置内容
    content.str(L"");
    content.clear();

    // 清零字体结构体
    memset(&font, 0, sizeof(LOGFONT));

    // 设置字体属性
    font.lfHeight    = height_ST;   // 字体高度
    font.lfWidth     = 0;           // 字体宽度，0 表示根据高度自动调整
    font.lfWeight    = FW_BOLD;     // 字体加粗
    font.lfItalic    = false;       // 字体不倾斜
    font.lfUnderline = false;       // 字体没有下划线
    wcscpy_s(font.lfFaceName, FACE_NAME_SIZE, _T("等线")); // 字体名称

    settextstyle(&font);        // 设置当前字体
    setbkmode(TRANSPARENT);     // 设置背景模式为透明
}

void SmallText::putText(int x, int y) {

    setorigin(0, 0);
    setaspectratio(1, 1);

    std::wstring strS = content.str();
    LPCTSTR      strL = strS.c_str();
    settextcolor(WHITE);
    RECT r = { x, y, x + height_ST * 10, y + height_ST };
    settextstyle(&font);
    drawtext(strL, &r, DT_LEFT | DT_TOP);   // 信息行显示
    content.str(L"");   // 重置内容
    content.clear();

    setorigin(0, SCREENH);
    setaspectratio(1, -1);
}

Text::~Text() {
    line--;
}