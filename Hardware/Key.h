#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

// 模块名称：Key（按键驱动模块）
// 功能说明：实现单个按键的初始化与消抖检测
// 依赖模块：Delay、SysTick

// 按键初始化函数：配置GPIOA引脚为上拉输入模式
void Key_Init(void);

// 按键检测函数：
// 返回值：1 = 检测到按键有效按下，0 = 未按下
uint8_t Key_GetNum(void);

#endif
