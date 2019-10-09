#include"Keyboard.h"
 #define uchar unsigned char
 #define uint unsigned int
char keyscan(void)
 {
    uchar temp;
    char num = 0xff;
    TRISB=0x0f;
    PORTB=0x7f;
    temp=PORTB&0x0f;
if(temp!=0x0f)
{
   _delay(10000);
   temp=PORTB&0x0f;
   if(temp!=0x0f)
   {
    num=temp|0x70; 
   }
   temp=PORTB&0x0f;
   while(temp!=0x0f)
   {
    temp=PORTB&0x0f;  
   }
   switch(num)
   {
    case 0x7e:num ='1';break;
    case 0x7d: num ='4';break;
    case 0x7b:num ='7';break;
    case 0x77:num ='E';break;
   }
}
PORTB=0xbf;
temp=PORTB&0x0f;
if(temp!=0x0f)
{
   _delay(10000);
   temp=PORTB&0x0f;
   if(temp!=0x0f)
   {
    num=temp|0xb0; 
   }
   temp=PORTB&0x0f;
   while(temp!=0x0f)
   {
    temp=PORTB&0x0f;  
   }
   switch(num)
   {
    case 0xbe:num ='2';break;
    case 0xbd: num ='5';break;
    case 0xbb:num ='8';break;
    case 0xb7:num ='0';break;
   }
}
PORTB=0xdf;
temp=PORTB&0x0f;
if(temp!=0x0f)
{
   _delay(10000);
   temp=PORTB&0x0f;
   if(temp!=0x0f)
   {
    num=temp|0xd0; 
   }
   temp=PORTB&0x0f;
   while(temp!=0x0f)
   {
    temp=PORTB&0x0f;  
   }
   switch(num)
   {
    case 0xde:num ='3';break;
    case 0xdd: num ='6';break;
    case 0xdb:num ='9';break;
    case 0xd7:num ='C';break;
   }
}
PORTB=0xef;
temp=PORTB&0x0f;
if(temp!=0x0f)
{
   _delay(10000);
   temp=PORTB&0x0f;
   if(temp!=0x0f)
   {
    num=temp|0xe0; 
   }
   temp=PORTB&0x0f;
   while(temp!=0x0f)
   {
    temp=PORTB&0x0f;  
   }
   switch(num)
   {
    case 0xee:num ='S';break;
    case 0xed: num ='G';break;
    case 0xeb:num ='L';break;
    case 0xe7:num ='P';break;
   }
}      
return num;
 }
