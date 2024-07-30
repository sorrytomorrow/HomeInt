# 主控板用的是stm32C8t6
# wifi模块是esp8266-01s(得需用串口调试下)



# 更改keil代码的以下配置
## esp8266.c文件
### ![image](https://github.com/user-attachments/assets/ab1220de-4d53-4058-982f-d3283adffb66)->--改成自己的手机热点和密码(路由器名称和密码也行)
## onenet.c文件
### ![image](https://github.com/user-attachments/assets/aba64853-329a-4443-8f46-a2cb65a2f041)->--改成自己onenet设备平台的三要素信息
### ![image](https://github.com/user-attachments/assets/9ec36da7-d549-4c8c-a366-bdf343872170)->下发json数据的接收(用一些cjson结构体指针变量，接收cjson函数所传递过来的结构体地址)-->需要先在onenet设备平台设置自己的设备
### ![image](https://github.com/user-attachments/assets/82dbba15-02c5-4f6f-b706-4eb5680938e2)->json数据格式的上传到云平台(注意json数据格式正确)-->需要先在onenet设备平台设置自己的设备
# 更改APP代码以下配置(用的是uniapp)
## ![image](https://github.com/user-attachments/assets/2598a058-eedf-4268-8c7b-e7c6c23237cb)->更改接收数据端的自己的onenet平台信息
## ![image](https://github.com/user-attachments/assets/6ad10965-5608-48bd-96de-53760989bf30)->更改发送数据端的自己的onenet平台信息


# APP效果
![image](https://github.com/user-attachments/assets/b53cf548-bc99-4e2c-9014-f8623fa05a5d)
# 视频演示
# 参考的b站up主视频(链接在下方，onenet平台设备需自己创建，可以参考下方链接)
## https://www.bilibili.com/video/BV1HH4y1o7EN?p=1&vd_source=23ff000af5bf725a92efa02f9d617847









