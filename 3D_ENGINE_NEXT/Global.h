#pragma once
#define     SCREEN_DISTANCE 200                     // 摄像头到屏幕距离
#define	    SCREENW         640			            // 屏宽像素
#define     SCREENH         480			            // 屏高像素
const int   SCREEN_SIZE = SCREENW * SCREENH;
const int   H_SCREENW = SCREENW / 2;
const int   H_SCREENH = SCREENH / 2;

const int   MAXVTS = 1000;	                // 最大存储顶点数

const float FPS = 60.0f;
const float TDN = 1.0e9f / FPS;