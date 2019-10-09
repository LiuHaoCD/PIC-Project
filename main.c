
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#include <pic.h>
#include "LCD1602.h"
#include "Keyboard.h"
#include"EEPROM.h"
#define uint8_t unsigned char
char isActivation[] = {'a','a','a','a'};   //存储四个区域激活状态


void delay2s(){
      _delay(2000000);
}//延时两秒

void PasswordDetect(uint8_t * password){
    lcd_SetAddr(0xc0); 
    
    uint8_t digit = 0;//计数已输入位数

    while(1){
            char num = keyscan();
            if(num!=0xff){
                if(num == 'C'){
                    if(digit != 0){
                    digit--;
                    lcd_SetAddr(0Xc0+digit); 
                    write(' ');
                    lcd_SetAddr(0Xc0+digit); 
                    }
                }//退格
                else{
                write('*');
                password[digit] = num;
                digit ++ ;
                if(digit == 6) break;
                }
            }
        }
}

void SSZ(void){
    lcd_clear();
    char WhichZone[] = {"Which Zone ?"};
    lcd_WriteString(0x80 , WhichZone , 12);
    
    while(1){
            char num = keyscan();
            if(num=='S'||num == 'G'||num == 'L'||num == 'P'){
                char selected[] = {"A is selected"};
                if(num == 'S'){
                    selected[0]='A';
                }else if(num == 'G'){
                    selected[0]='B';
                }else if(num == 'L'){
                    selected[0]='C';
                }else if(num == 'P'){
                    selected[0]='D';
                }//替换区域字母
                lcd_WriteString(0xC0 , selected , 13);
                delay2s();
                lcd_clear();
                char aORi[] = {"Active:1 Inact:2"};
                lcd_WriteString(0x80 , aORi , 16);
                char result[] = {"A is inavtived"};
                while(1){
                    char num2 = keyscan();
                if(num2 == '1'){
                    result[5]='a';
                    result[6]='c';
                    result[7]='t';
                    result[8]='i';
                    result[9]='v';
                    result[10]='e';
                    result[11]='d';
                    
                if(num == 'S'){
                    isActivation[0]='a';
                    result[0]= 'A';
                }else if(num == 'G'){
                    isActivation[1]='a';
                    result[0]= 'B';
                }else if(num == 'L'){
                    isActivation[2]='a';
                    result[0]= 'C';
                }else if(num == 'P'){
                    isActivation[3]='a';
                    result[0]= 'D';
                }
                lcd_WriteString(0xC0 , result , 12);
                    delay2s();
                break;
              }
            else if(num2 == '2'){
                
                if(num == 'S'){
                    isActivation[0]='i';
                    result[0]= 'A';
                }else if(num == 'G'){
                    isActivation[1]='i';
                    result[0]= 'B';
                }else if(num == 'L'){
                    isActivation[2]='i';
                    result[0]= 'C';
                }else if(num == 'P'){
                    isActivation[3]='i';
                    result[0]= 'D';
                }
                lcd_WriteString(0xC0 , result , 14);
                delay2s();
                break;
                }
            }
                    
                break;
        } 
    }
}
    
    
void SUP(void){
    lcd_clear();
    char lineOne[]={"New Password:"};
    lcd_WriteString(0x80 , lineOne , 13);
    lcd_SetAddr(0xc0);
    uint8_t    inputPassword[6];
    PasswordDetect(inputPassword);
    
    for(uint8_t i=0;i<6;i++){
        WriteByte(i,inputPassword + i);
    }       //将密码写入EEPROM
}

void LCD_Welcome(void){
    char group[] = {"Group 7"};
    char welcome[] = {"Welcome!"};
    lcd_WriteString(0x84 , group , 7);
    lcd_WriteString(0xc4 , welcome , 8);
}

void System_init(void){
        TRISC = 0;
        TRISD = 0;
        OPTION_REG=0x06;    
        CCPR1L = 0x7F;      
        CCP1CON =  0x3C;    
        T2CON = 0x09;       
        PR2 = 255;  
        //TMR2ON = 0;
}



void PressPassword(void){
    char passwordTitle[] = {"Press Password:"};
    lcd_WriteString(0x80, passwordTitle ,15);
    
    uint8_t password[6],inputPassword[6];
    for(uint8_t i = 0; i<6;i++){
        ReadByte(i,password + i);
    }       //从eeprom读取密码
    
    
    
InputPassword:

    PasswordDetect(inputPassword);
    
    //检查密码是否正确
    for(uint8_t i = 0 ;i<6; i++){
        if(password[i] == inputPassword[i]){
            continue ; 
        }else{
            char wrong[] = {"Wrong!!!"};
            lcd_WriteString(0xc0 , wrong,8);//提示密码输入错误
            delay2s();
            
            lcd_SetAddr(0xc0); 
            for(uint8_t j = 0; j <8 ;j++) write(' ');//写8个空格相当于清楚之前的错误提示
            goto InputPassword; //从新开始输入密码
        }
    }
}


void SystemConfig(void){
    PressPassword();
    lcd_clear();
    char configMenu[] = {"SUP:1 SSZ:2"};
    lcd_WriteString(0x80 , configMenu, 11);
     while(1){
            char num = keyscan();
            if(num == '1'){
                SUP();
                break;
            }
            else if(num == '2'){
                SSZ();
                break;
            }
     }
    lcd_clear();
}

void SystemMenu(void){
    char fourZones[] = {"A:a B:a C:a D:a"};
    fourZones[2]=isActivation[0];
    fourZones[6]=isActivation[1];
    fourZones[10]=isActivation[2];
    fourZones[14]=isActivation[3];
    char config[] = {"Config: ENT"};
    lcd_WriteString(0x80 ,fourZones,15);
    lcd_WriteString(0xc0 ,config,11);
}

void Trigger(char zone){
    TMR2ON = 1; //开启TIMER2以启动PWM
    lcd_clear();
    char zoneTrigger[] = {"A is triggered"};
    zoneTrigger[0] = zone;
    lcd_WriteString(0x80, zoneTrigger, 14);
   delay2s();
    lcd_clear();    //清屏
    PressPassword();
    TMR2ON = 0;//关闭TIMER2
}

void MenuKey(void){
    while(1){
            char num = keyscan();
            if(num=='E'){
                lcd_clear();
                SystemConfig(); 
                SystemMenu();
            }//进入系统设置
            
            else if(num == 'S'&&isActivation[0]=='a' ){
            Trigger('A');
            SystemMenu();
        }
            else if(num == 'G' &&isActivation[1]=='a' ){
            Trigger('B');
            SystemMenu();
        }
            else if(num == 'L'&&isActivation[2]=='a'  ){
            Trigger('C');
            SystemMenu();
        }
            else if(num == 'P' &&isActivation[3]=='a' ){
            Trigger('D');
            SystemMenu();
        }
    }    
}


void main(){
    
        uint8_t initialPassword[] = {'1','2','3','4','5','6'};
        for(uint8_t i = 0; i<6;i++){
        WriteByte(i,initialPassword +i);
        }   //写入初始密码，正式使用时需要被注释
        
        
        
     
        System_init();  //初始化IO口及PWM
        lcd_init();     
        LCD_Welcome();  //显示组号及欢迎
        delay2s();
        lcd_clear();
        SystemMenu();
        MenuKey();
}
