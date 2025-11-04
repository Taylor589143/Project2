#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"

/* ==========================================================
 * PID 控制头文件
 * 
 * 提供以下接口：
 *  1️速度环增量式 PID 控制
 *  2️位置环比例控制
 *  3️参数动态调整接口
 *  4️控制器状态重置接口
 * 
 * 函数接口设计保持与原版本一致，
 * 仅在命名与注释上进行了改进。
 * ========================================================== */

/* ---------------- PID 参数设置接口 ---------------- */
/**
 * @brief 设置速度环 PID 参数
 * @param p 比例系数
 * @param i 积分系数
 * @param d 微分系数
 */
void Speed_PID_SetParams(float p, float i, float d);

/**
 * @brief 设置位置环 PID 参数
 * @param p 比例系数
 * @param i 积分系数（保留参数，不使用）
 * @param d 微分系数（保留参数，不使用）
 */
void Position_PID_SetParams(float p, float i, float d);


/* ---------------- PID 计算接口 ---------------- */
/**
 * @brief 速度环 PID 计算（增量式）
 * @param target 目标速度
 * @param actual 实际速度
 * @return 输出 PWM 值（±800 限幅）
 * 
 * ★修改：原函数名 Speed_PID_Calculate → Speed_PID_Compute
 */
int16_t Speed_PID_Compute(int16_t target, int16_t actual);  // ★修改


/**
 * @brief 位置环 PID 计算（比例环）
 * @param target 目标位置
 * @param actual 实际位置
 * @return 输出 PWM 值（±50 限幅）
 * 
 * ★修改：原函数名 Position_PID_Calculate → Position_PID_Compute
 */
int16_t Position_PID_Compute(int32_t target, int32_t actual);  // ★修改


/* ---------------- PID 状态重置接口 ---------------- */
/**
 * @brief 重置速度环 PID 状态
 * 
 * 清空积分项与误差缓存，用于模式切换或停止时。
 */
void Speed_PID_Reset(void);

#endif
