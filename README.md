# stm32f1_esp32_udp
使用udp协议让stm32f1和esp32单片机通信，esp32可以接收类似123R这样的指令，并把指令显示在iic的OLED屏幕上<br>
一部分程序来源于洋桃电子http://doyoung.net/YT/index.html<br>
使用方法：<br>
1：keil创建一个stm32f103的工程，我使用的是stm32f103c8t6，也可以到上面我贴出的网址里下载一个<br>
2.把128*64的单色iic屏幕的scl线连接到b6，sda线连接到b7端口<br>
3.修改esp32_prog.ino中的信息，把前两行引号中内容换成你的wifi ssid和密码<br>
4.连接成功后，oled屏幕上会显示IP地址<br>
5：使用udp软件发送信息，信息就会显示在屏幕上。<br>
