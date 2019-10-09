/* 
 * File:   LCD1602.h
 * Author: charl
 *
 * Created on 2019?9?6?, ??11:25
 */

#ifndef LCD1602_H
#define	LCD1602_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif

#include <pic.h>
#define rs RC4
#define rw RC5
#define e  RC6
#define uint8_t unsigned char
void lcd_init(void);               //LCD初始化
void write(char x);                 //写一个字符
void lcd_enable(void);             //LCD使能
void delay5ms(void);
void lcd_clear(void);               //清屏
void lcd_WriteString(uint8_t addr , char * string , uint8_t len);   //写一个字符串，传入参数：显存地址、字符串地址、字符串长度
void lcd_SetAddr(uint8_t addr);     //设置显存地址
#endif	/* LCD1602_H */

