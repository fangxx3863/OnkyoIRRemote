# OnkyoIRRemote

使用红外遥控控制支持OnkyoRI的设备

可用ArduinoNano制作

# ID列表（这是我自己测试出来的我的安桥收音机的代码）

> 3072	列表下一个电台（全组切换）
> 
> 3073	列表上一个电台（全组切换）

> 3080	SLEEP 90
> 
> 3081	FM
> 
> 3082	AM

> 3088	SCAN

> 3092	0
> 
> 3093	1
> 
> 3094	2
> 
> 3095	3

> 3138	频率加
> 
> 3139	频率减

> 3148	切换组

> 3162	4
> 
> 3163	5
> 
> 3164	6
> 
> 3165	7
> 
> 3166	8
> 
> 3167	9

> 3224	搜索下一个台
> 
> 3225	搜索上一个台

# 遇到的坑

1. 不知道有哪些ID支持，前前后后扫了几小时
2. 加了IRRemote库后莫名其妙无法控制，最后上示波器才发现差了200ms，不清楚怎么导致的，直接在代码里加了偏移解决了

# 免责声明

本程序部分设计借鉴了https://github.com/docbender/Onkyo-RI

如果需要自己扫描ID请用原项目的test工具
