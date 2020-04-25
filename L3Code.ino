#include "LedControl.h"
// Pin 11 to Data In, 13to Clk, 10 to LOAD, number of devices is 8
// Pin 5 to Data In, 6 to Clk, 4 to LOAD, number of devices is 8
LedControl lc1=LedControl(7,6,5,8);
LedControl lc2=LedControl(4,3,2,8);
//LedControl lc3=LedControl(14,15,16,8);
LedControl lc3=LedControl(A0,A1,A2,8);
void setup()
{
  Serial.begin(9600);
  // Initialize the 3 MAX7219 devices
  for(int k=0; k<9; k++){
    lc1.shutdown(k,false);  // Enable display
    lc1.setIntensity(k,15); // Set brightness level (0 is min, 15 is max)
    lc1.clearDisplay(k);    // Clear display register
  
    lc2.shutdown(k,false);  // Enable display
    lc2.setIntensity(k,15); // Set brightness level (0 is min, 15 is max)
    lc2.clearDisplay(k);    // Clear display register
    
    lc3.shutdown(k,false);  // Enable display
    lc3.setIntensity(k,15); // Set brightness level (0 is min, 15 is max)
    lc3.clearDisplay(k);    // Clear display register
    
  }
}
int k=0;

void loop()
{
led1(0,0,"00000000",false);
led1(1,0,"11111111",false);
led1(2,0,"22222222",false);
led1(3,0,"33333333",false);
led1(4,0,"44444444",false);
led1(5,0,"55555555",false);
led1(6,0,"66666666",false);
led1(7,0,"66666666",false);

led2(0,0,"77777777",false);
led2(1,0,"88888888",false);
led2(2,0,"99999999",false);
led2(3,0,"10101010",false);
led2(4,0,"11011011",false);
led2(5,0,"12121212",false);
led2(6,0,"12121212",false);
led2(7,0,"12121212",false);

led3(0,0,"13131313",false);
led3(1,0,"14141414",false);
led3(2,0,"15151515",false);
led3(3,0,"16161616",false);
led3(4,0,"17171717",false);
led3(5,0,"18181818",false);
led3(6,0,"12121212",false);
led3(7,0,"12121212",false);

}
void led1(int module, int place, String datas, boolean dot)
{
  for(int i=place;datas[i]!='\0';i++)
  {
    lc1.setDigit(module,i,int(datas[i])-48, false);
  } 
   
}
void led2(int module, int place, String datas, boolean dot)
{
  for(int i=place;datas[i]!='\0';i++)
  {
    lc2.setDigit(module,i,int(datas[i])-48, false);
  } 
   
}
void led3(int module, int place, String datas, boolean dot)
{
  for(int i=place;datas[i]!='\0';i++)
  {
    lc3.setDigit(module,i,int(datas[i])-48, false);
  } 
}
