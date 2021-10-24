//--------------------------------------------------------
//
// 项目：       安桥RI端口红外遥控
// 作者：       Fangxx3863
// 创建日期：   2021/06/25
// 协议：       MIT
//
//--------------------------------------------------------


#include "Arduino.h"
#include <IRremote.h>
#include <stdlib.h>
//#include "OnkyoRI.h"
#define ONKYO_PIN 13

const byte IR_RECEIVE_PIN = 2; //定义红外接收模块的信号接收为D2引脚 


void setup()
{
  Serial.begin(9600); //定义波特率
  IrReceiver.begin(IR_RECEIVE_PIN);

  pinMode(ONKYO_PIN, OUTPUT);
  digitalWrite(ONKYO_PIN, LOW);
  Serial.println("Ready");
}

void loop() 
{
  delay(600); //延时600毫秒（按键消抖）
  if(IrReceiver.decode())  //当红外接收模块接收到信号时
  { 
    Serial.print("\nIR-Code: 0x"); //打印出"irCode: " 
    Serial.print(IrReceiver.decodedIRData.command, HEX); //打印出当前信号16进制的值
    Serial.print("\n");
    //Serial.println();
    IrReceiver.resume();
   
  
    if(IrReceiver.decodedIRData.command == 0x40)  //如果接收到的信号为40
    {
      onkyoSend(3138);
      Serial.println("NEXT!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x44) //如果接收到的信号为44
    {
      onkyoSend(3139);
      Serial.println("FOWARD!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x47||IrReceiver.decodedIRData.command == 0x20) //如果接收到的信号为47
    {
      onkyoSend(3072);
      Serial.println("CH+!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x45||IrReceiver.decodedIRData.command == 0x21) //如果接收到的信号为45
    {
      onkyoSend(3073);
      Serial.println("CH-!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x15||IrReceiver.decodedIRData.command == 0x1E) //如果接收到的信号为15
    {
      onkyoSend(3224);
      Serial.println("AUTO CH+!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x7||IrReceiver.decodedIRData.command == 0x1F) //如果接收到的信号为7
    {
      onkyoSend(3225);
      Serial.println("AUTO CH-!\n");
    }
    else if(IrReceiver.decodedIRData.command == 0x16) //如果接收到的信号为16
    {
      onkyoSend(3092);
      Serial.println("0!");
    }
    else if(IrReceiver.decodedIRData.command == 0xC) //如果接收到的信号为C
    {
      onkyoSend(3093);
      Serial.println("1!");
    }
    else if(IrReceiver.decodedIRData.command == 0x18) //如果接收到的信号为18
    {
      onkyoSend(3094);
      Serial.println("2!");
    }
    else if(IrReceiver.decodedIRData.command == 0x5E) //如果接收到的信号为5E
    {
      onkyoSend(3095);
      Serial.println("3!");
    }
    else if(IrReceiver.decodedIRData.command == 0x8) //如果接收到的信号为8
    {
      onkyoSend(3162);
      Serial.println("4!");
    }
    else if(IrReceiver.decodedIRData.command == 0x1C) //如果接收到的信号为1C
    {
      onkyoSend(3163);
      Serial.println("5!");
    }
    else if(IrReceiver.decodedIRData.command == 0x5A) //如果接收到的信号为5A
    {
      onkyoSend(3164);
      Serial.println("6!");
    }
    else if(IrReceiver.decodedIRData.command == 0x42) //如果接收到的信号为42
    {
      onkyoSend(3165);
      Serial.println("7!");
    }
    else if(IrReceiver.decodedIRData.command == 0x52) //如果接收到的信号为52
    {
      onkyoSend(3166);
      Serial.println("8!");
    }
    else if(IrReceiver.decodedIRData.command == 0x4A) //如果接收到的信号为4A
    {
      onkyoSend(3167);
      Serial.println("9!");
    }
    else if(IrReceiver.decodedIRData.command == 0x43) //如果接收到的信号为43
    {
      onkyoSend(3088);
      Serial.println("SCAN!");
    }
    else if(IrReceiver.decodedIRData.command == 0x9) //如果接收到的信号为9
    {
      onkyoSend(3148);
      Serial.println("GROUP!");
    }
    else if(IrReceiver.decodedIRData.command == 0x19) //如果接收到的信号为19
    {
      onkyoSend(3081);
      Serial.println("FM!");
    }
    else if(IrReceiver.decodedIRData.command == 0xD) //如果接收到的信号为D
    {
      onkyoSend(3082);
      Serial.println("AM!");
    }
    

    //随机电台部分
    else if(IrReceiver.decodedIRData.command == 0x46)
    {
      int group = (rand() % (3-1+1))+ 1;
      int num = (rand() % (9-0+1))+ 0;
      for (group; group <= 3; group++)
      {
        onkyoSend(3148);
        Serial.println("Group! ");
        delayMicroseconds(20000);
      }
      if(num >= 0 && num <= 3)
      {
        num = num + 3092;
        onkyoSend(num);
        Serial.println(num);
      }
      else if(num >= 4 && num <= 9)
      {
        num = num + 3158;
        onkyoSend(num);
        Serial.println(num);
      }
      Serial.println();
      
    }
    //delay(70);
  //IrReceiver.decodedIRData.command = 0x0; //复位
  }
}


//ONKYO SEND

void onkyoSend(int command)
{
  onkyoWriteHeader();
  Serial.println("Header send");
  
  for(int i=0;i<12;i++)
  {
    bool level = command & 0x800;
    command <<= 1;
    onkyoWriteBit(level);
    //Serial.println(level);
  }

  onkyoWriteFooter();
  Serial.println("Footer send");
}

void onkyoWriteHeader()
{
  //Serial.println(micros());
  digitalWrite(ONKYO_PIN,HIGH);
  delayMicroseconds(2500);
  digitalWrite(ONKYO_PIN,LOW);
  delayMicroseconds(800);
  //Serial.println(micros());
}
void onkyoWriteBit(bool level)
{
  digitalWrite(ONKYO_PIN,HIGH);
  delayMicroseconds(800);  
  digitalWrite(ONKYO_PIN,LOW);
    
  if(level)
    delayMicroseconds(1600); 
  else
    delayMicroseconds(800); 
}
void onkyoWriteFooter()
{
  digitalWrite(ONKYO_PIN,HIGH);
  delayMicroseconds(800);
  digitalWrite(ONKYO_PIN,LOW);
  delay(20);
}
