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
void lcd_init(void);               //LCD��ʼ��
void write(char x);                 //дһ���ַ�
void lcd_enable(void);             //LCDʹ��
void delay5ms(void);
void lcd_clear(void);               //����
void lcd_WriteString(uint8_t addr , char * string , uint8_t len);   //дһ���ַ���������������Դ��ַ���ַ�����ַ���ַ�������
void lcd_SetAddr(uint8_t addr);     //�����Դ��ַ
#endif	/* LCD1602_H */

