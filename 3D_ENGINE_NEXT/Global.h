#pragma once
#define     SCREEN_DISTANCE 200                     // ����ͷ����Ļ����
#define	    SCREENW         640			            // ��������
#define     SCREENH         480			            // ��������
const int   SCREEN_SIZE = SCREENW * SCREENH;
const int   H_SCREENW = SCREENW / 2;
const int   H_SCREENH = SCREENH / 2;

const int   MAXVTS = 1000;	                // ���洢������

const float FPS = 60.0f;
const float TDN = 1.0e9f / FPS;