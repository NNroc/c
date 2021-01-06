/******************/
/* 硬件课设
 * 利用8255、8253、0832、LCD屏显示模拟机床加工过程。
 * 加工过程通过0832控制直流电机转动2秒（2秒时间由8253提供）
 * 停止后8255控制步进电机转动3秒（3秒时间由8253提供）
 * 停止后8255控制步进电机转动3秒（3秒时间由8253提供）
 * 停止后8255控制继电器输出灯亮
 * 由0832控制直流电机转动2秒（2秒时间由8253提供）停止
 * 完成一个加工过程，并由LCD屏显示模拟机床加工过程（图示方式）
 */
/******************/
#include <stdio.h>
#include <conio.h>
#include <initializer_list>
#include "ApiExusb.h"

#pragma comment(lib, "ApiExusb.lib")

#define io0832_in 0x290

#define io8254_0 0x280
#define io8254_1 0x281
#define io8254_ctl 0x283

#define io8255_ctl 0x28b
#define io8255_a 0x288
#define io8255_b 0x289
#define io8255_c 0x28a

char direct[9] = {0xd6, 0xb1, 0xc1, 0xf7, 0xb5, 0xe7, 0xbb, 0xfa, '\0'}; /*直流电机*/
char step_cw[11] = {0xb2, 0xbd, 0xbd, 0xf8, 0xb5, 0xe7, 0xbb, 0xfa, 0xcb, 0xb3, '\0'}; /*步进电机顺*/
char step_acw[11] = {0xb2, 0xbd, 0xbd, 0xf8, 0xb5, 0xe7, 0xbb, 0xfa, 0xc4, 0xe6, '\0'}; /*步进电机逆*/
char direct_light[17] = {0xd6, 0xb1, 0xc1, 0xf7, 0xb5, 0xe7, 0xbb, 0xfa, 0xbc, 0xcc, 0xb5, 0xe7, 0xc6, 0xf7, 0xbf, 0xaa, '\0'}; /*直流电机继电器开*/

BYTE buf = 0x33;
BYTE data;

void direct_m_2s();

void step_m_cw_3s();

void step_m_acw_3s();

void clear();

void cmdsetup();

void datasetup();

void LCD(char data[]);

std::initializer_list<int> main() {
    if (!Startup()) {
        printf("ERROR: Open Device Error!\n");
        return 0;
    }

    PortWriteByte(io8255_ctl, 0x88);
    LCD(direct);
    // 直流电机转动2s
    direct_m_2s();

    LCD(step_cw);
    // 步进电机顺时针转3s
    step_m_cw_3s();

    LCD(step_acw);
    // 步进电机逆时针转3s
    step_m_acw_3s();

    LCD(direct_light);
    // 继电器灯亮

    PortWriteByte(io8255_c, 0x08);
    // 直流电机转动2s
    direct_m_2s();

    // 继电器灯灭
    PortWriteByte(io8255_c, 0x00);

    // kbhit() 检查当前是否有键盘输入，若有则返回一个非0值，随后关闭设备，否则再次检查
    while (!kbhit());
    // 关闭设备
    Cleanup();
    return 0;
}

/// 直流电机转动2s
void direct_m_2s() {
    // 线性增长的周期性锯齿波
    PortWriteByte(io0832_in, 0xff);      /*D/A 输出一个正电压，直流电动机开始转动*/
    /*********延时2s begin*********/
    // 10000对应的16位值：0010 0111 0001 0000
    PortWriteByte(io8254_ctl, 0x36); /*设8254计数器0工作方式3，输出2khz的方波*/
    PortWriteByte(io8254_0, 0x10);   /*先写计数器初值10000的低字节*/
    PortWriteByte(io8254_0, 0x27);   /*后写计数器初值10000的高字节*/

    // 1101 1000
    PortWriteByte(io8254_ctl, 0x54); /*设8254计数器1工作方式2，连续脉冲*/
    PortWriteByte(io8254_1, 0xc8);   /*写计数器初值200*/
    int count = 0;
    while (1) {
        PortReadByte(io8255_c, &data);
        // 1000 0000
        if (!(data & 0x80)) {
            count++;
            if (count == 2)
                break;
        }
    }
    /*********延时2s end*********/
    PortWriteByte(io0832_in, 0x80);   /*D/A 输出0V，直流电动机停止转动，输出数据*/
}

/// 步进电机顺时针转3s
void step_m_cw_3s() {
    PortWriteByte(io8254_ctl, 0x36);
    PortWriteByte(io8254_0, 0x10);
    PortWriteByte(io8254_0, 0x27);

    PortWriteByte(io8254_ctl, 0x74); /*设8254计数器1工作方式2*/
    PortWriteByte(io8254_1, 0x2c);   /*写计数器初值300的低字节*/
    PortWriteByte(io8254_1, 0x01);   /*写计数器初值300的高字节*/
    int count = 0;
    while (1) {
        PortReadByte(io8255_c, &data);
        if (!(data & 0x80)) {
            count++;
            if (count == 2)
                break;
        }
        buf = ((buf & 128) >> 7) | (buf << 1);
        PortWriteByte(io8255_b, buf);
        int delay = 1000000;
        while (delay--);
    }
}

/// 步进电机逆时针转3s
void step_m_acw_3s() {
    PortWriteByte(io8254_ctl, 0x36);
    PortWriteByte(io8254_0, 0x10);
    PortWriteByte(io8254_0, 0x27);

    PortWriteByte(io8254_ctl, 0x74);
    PortWriteByte(io8254_1, 0x2c);   /*写计数器初值300的低字节*/
    PortWriteByte(io8254_1, 0x01);   /*写计数器初值300的高字节*/
    int count = 0;
    while (1) {
        PortReadByte(io8255_c, &data);
        if (!(data & 0x80)) {
            count++;
            if (count == 2)
                break;
        }
        buf = ((buf & 1) << 7) | (buf >> 1);
        PortWriteByte(io8255_b, buf);
        int delay = 1000000;
        while (delay--);
    }
}

void clear() {
    PortWriteByte(io8255_a, 0x0c);
    cmdsetup();
}

void cmdsetup() {
    PortWriteByte(io8255_c, 0x00);
    Sleep(1);
    PortWriteByte(io8255_c, 0x04);
    Sleep(1);
    PortWriteByte(io8255_c, 0x00);
    Sleep(1);
}

void datasetup() {
    PortWriteByte(io8255_c, 0x01);
    Sleep(1);
    PortWriteByte(io8255_c, 0x05);
    Sleep(1);
    PortWriteByte(io8255_c, 0x01);
    Sleep(1);
}

void LCD(char data[]) {
    clear();
    PortWriteByte(io8255_a, 0x90);        /*控制让lcd在第2行输出*/
    cmdsetup();
    int len = strlen(data);
    for (int i = 0; i < len; i++) {
        PortWriteByte(io8255_a, data[i]);
        datasetup();
    }
    Sleep(100);
}