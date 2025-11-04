#include "stm32f10x.h"
#include "Delay.h"

// ==========================================
// 模块名称：Key（按键驱动模块）
// 文件说明：负责按键的GPIO初始化与状态检测
// 作者：ChatGPT 改写版
// ==========================================

// ----------------------
// 外部依赖函数声明
// ----------------------
uint32_t GetSystemTick(void);   // ★新增注释：获取系统节拍计数（ms单位）

// ----------------------
// 内部全局变量定义
// ----------------------
volatile uint32_t system_tick = 0;  // ★修改：定义系统节拍计数变量（由SysTick中断更新）

// =====================================================
// 函数名称：Key_Init
// 功能描述：初始化按键GPIO，配置为上拉输入模式
// 参数说明：无
// 返回值：无
// =====================================================
void Key_Init(void)
{
    // ① 打开 GPIOA 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // ② 配置 PA0 为上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ★新增注释：上拉输入意味着默认电平为高（1），按下时接地为低（0）
}

// =====================================================
// 函数名称：Key_GetNum
// 功能描述：检测按键是否被按下（包含简单消抖）
// 参数说明：无
// 返回值：1 = 检测到有效按下，0 = 未按下
// =====================================================
uint8_t Key_GetNum(void)
{
    static uint8_t last_state = 1;         // ★修改：记录上次状态（1=未按下，0=按下）
    static uint32_t last_press_time = 0;   // ★新增注释：记录上次按下时刻（ms）
    uint8_t current_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
    uint32_t current_time = GetSystemTick();

    // ---------- 检测按键按下（从 1 → 0） ----------
    if (last_state == 1 && current_state == 0)
    {
        // ★新增注释：进行简单消抖（延时50ms）
        Delay_ms(50);

        // 再次确认是否仍然按下
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
        {
            last_state = 0;
            last_press_time = current_time;   // ★新增注释：记录按下时间（可扩展长按功能）
            return 1;                         // 检测到有效按下
        }
    }

    // ---------- 检测按键释放（从 0 → 1） ----------
    if (last_state == 0 && current_state == 1)
    {
        last_state = 1;  // ★新增注释：更新状态为未按下
    }

    return 0; // ★新增注释：默认返回未按下
}

// =====================================================
// 函数名称：GetSystemTick
// 功能描述：返回系统节拍计数值
// 参数说明：无
// 返回值：系统运行的毫秒计数（通常由SysTick中断自增）
// =====================================================
uint32_t GetSystemTick(void)
{
    return system_tick;
}
