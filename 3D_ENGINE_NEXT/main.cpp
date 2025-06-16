#include "Timer.h"
#include "ModeController.h"
#include <iostream>
#include <thread>
void initializeGraph();
int main() {
    
    initializeGraph();
    LookupTable::init();
    Camera::init(10.0, 10.0, -10.0);
    Camera::XZangle = -45.0f;
    Camera::YZangle = -45.0f;

    Text frame;
    Text CPU_usage;

    ModeController modeController;

    FrameTimer frameTimer;
    Timer usageTimer;

    ParallelLight light(WHITE, 1, Vector(1.0, -1.0, 0.0));

    Object table(Mesh("secretla.txt", "clockwise", 0), 0.2);
    table.setPosition(Vector(10.0, 0.0, 5.0));
    table.rotateTo(0.0, 90.0, 0.0);
    table.setColor(0x34183e);
    table.setName(L"桌子");
    //Shader::objects.push_back(&table);

    //0xd0fc53
    Object power_chair(Mesh("power_chair.txt", "clockwise", 0), 10);
    power_chair.setPosition(Vector(0.0, 0.0, 5.0));
    power_chair.rotateTo(0.0, 180.0, 0.0);
    power_chair.setColor(BGR(0xdddddd));
    power_chair.setName(L"抛瓦！！！");
    Shader::objects.push_back(&power_chair);

    //0x2dffff
    Object power_chair2(Mesh("power_chair.txt", "clockwise", 0), 10);
    power_chair2.setPosition(Vector(20.0, 0.0, 5.0));
    power_chair2.rotateTo(0.0, 180.0, 0.0);
    power_chair2.setColor(BGR(0xdddddd));
    power_chair2.setName(L"抛瓦瓦！！！");
    Shader::objects.push_back(&power_chair2);

    Object scene_a(Mesh("scene_a.txt", "clockwise", 0), 5);
    scene_a.setPosition(Vector(0.0, 0.0, 0.0));
    scene_a.rotateTo(0.0, 0.0, 0.0);
    scene_a.setColor(0xaaaaaa);
    scene_a.setName(L"场景");
    //Shader::objects.push_back(&scene_a);

    Shader shader(1);
    shader.light = &light;

    //std::thread handleMsg(&ModeController::getMessage, &modeController);
    while (true) {
        
        BeginBatchDraw();
        cleardevice();

        modeController.getMessage();
        modeController.handleMessage();

        Camera::update();

        frameTimer.timeStart();
        usageTimer.timeStart();

        
        shader.prepare();
        shader.run();
        
        power_chair.rotateFor(0.0, 0.2, 0.0);
        power_chair2.rotateFor(0.0, 0.2, 0.0);

        shader.object = &power_chair;
        shader.run();

        modeController.printInformation();

        usageTimer.timeUpdate();
        auto runningTime = usageTimer.getDuration();
        frameTimer.timeUpdate();    // 刷新时间
        frameTimer.wait();          // 忙等待
        auto frameTime = frameTimer.getDuration();

        float runningTimeValue = runningTime.count() * 1.0e3;
        float frameTimeValue = frameTime.count() * 1.0e3;
        float CPU_usage_value = runningTimeValue / frameTimeValue; // 计算CPU 占用率

        // 帧率信息行
        frame.content << L"实时帧率：" << std::setprecision(4)
                    << frameTimer.getFrameRate();
        frame.putText();

        // CPU 占用信息行
        CPU_usage.content << L"CPU运算时间：" << std::setprecision(4)
                              << CPU_usage_value;
        CPU_usage.putText();

        
        EndBatchDraw();
    }

    return 0;
}

void initializeGraph() {

    initgraph(SCREENW, SCREENH);
    setorigin(0, SCREENH);
    setaspectratio(1, -1);
    setfillcolor(WHITE);
    fillcircle(0, 0, 100);
    setbkcolor(BGR(0xdce2ff));

    HWND hwnd = FindWindow(NULL, L"3D_ENGINE_NEXT");
    if (hwnd == NULL) {
        MessageBoxW(NULL, L"无法找到窗口。", L"问题", NULL);        // FindWindow调用失败，没有找到窗口
        return;
    }
    RECT rect;
    GetWindowRect(hwnd, &rect);
    MoveWindow(hwnd, 0, 0, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}