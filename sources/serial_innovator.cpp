#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>
#include     <time.h>
#include     <stdint.h>
#include     <string.h>
#include     "serial_innovator.h"
#include     "headers.h"

/*typedef struct vison_info_t
{
    uint8_t sof;
    uint8_t sgn;
    int8_t col;
    int16_t x_pos;
    //uint8_t fire;
    //uint8_t others;
    int16_t y_pos;
    int16_t z_pos;

}vision;

vision cam_capture;
*/
/*
typedef struct qr_info_t
{
    uint8_t sof;
    const char *qr_code;
}cod;

cod cap_code;
/*
typedef  struct rela_info_t
{
    uint8_t sof;
    uint8_t sgn;
    int8_t first;
    int8_t second;
    int8_t third;
}rela;

rela rela_up;

rela rela_down;
*/


int color_position(int col,double x_pos,double y_pos,double z_pos,int num)
{

    /*if(find == 1){
        fire = 1;
    }else{
        fire = 0;
    }*/
    int16_t u_x_pos, u_y_pos, u_z_pos;
    u_x_pos = (int16_t)x_pos;
    u_y_pos = (int16_t)y_pos;
    u_z_pos = (int16_t)z_pos;

    //cam_capture.fire=fire;
    //cam_capture.others=find;

    int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug
    int err;               //返回调用函数的状态
    int len;
    int flag=0;
    //判断是否打开串口

    const char *dev[]  = {"/dev/ttyTHS1"}; //串口名
    if (1)//yiqianshi (find)
    {
        fd = open(dev[0],O_RDWR | O_NOCTTY | O_NDELAY); //打开串口，返回文件描述符
        if(-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (0);
        }else{
            flag=1;//Seral open permit to trans
        }
    }else{
        printf("No Armor,Close the Serial\n");
        return 0;
    }

    do{
        err = UART0_Init(fd,115200,0,8,1,'N');
    }while(FALSE == err || FALSE == fd);

    while(1){
         //发送数据
         uint8_t uart0_send_buf[9];
         if (num < 4){
             uart0_send_buf[0] = (uint8_t)0xAA;
         }
         else {
             uart0_send_buf[0] = (uint8_t)0xFF;
         }

         if (num == 1 || num == 4){
             uart0_send_buf[1] = (uint8_t)0x01;
         }
         else if(num == 2 || num == 5){
             uart0_send_buf[1] = (uint8_t)0x02;
         }
         else if(num == 3 || num == 6){
             uart0_send_buf[1] = (uint8_t)0x03;
         }

         uart0_send_buf[2] = (col) & 0xff;
         uart0_send_buf[3] = (u_x_pos >> 8) & 0xff; //高八位右移八位，先发送高八位
         uart0_send_buf[4] = (u_x_pos) & 0xff;
         uart0_send_buf[5] = (u_y_pos >> 8) & 0xff;
         uart0_send_buf[6] = (u_y_pos) & 0xff;
         uart0_send_buf[7] = (u_z_pos >> 8) & 0xff;
         uart0_send_buf[8] = (u_z_pos) & 0xff;
         printf("color position data sent is:\n");
         printf("%d\t" , col);
         printf("%d\t", u_x_pos);
         printf("%d\t", u_y_pos);
         printf("%d\t", u_z_pos);


        //fgets(send_buf,256,stdin);   //输入内容，最大不超过40字节，fgets能吸收回车符，这样pc收到的数据就能自动换行
       if (flag)
       {

           len = UART0_Send(fd, uart0_send_buf, 10);

           if(len > 0)
           {
               printf("time send %d data successful\n",len);
           }
           else
               printf("send data failed!\n");
           break;

       }
  }
    UART0_Close(fd);
}


int up_rela()
{

    /*if(find == 1){
        fire = 1;
    }else{
        fire = 0;
    }*/
    //cam_capture.yaw=(int16_t)(yaw*100);//*100
    //cam_capture.pitch=(int16_t)(pitch*100);//*100
    uint8_t u_first, u_second, u_third;
    u_first = (uint8_t)ajkl[0];
    u_second = (uint8_t)ajkl[1];
    u_third = (uint8_t)ajkl[2];
    //cam_capture.fire=fire;
    //cam_capture.others=find;

    int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug
    int err;               //返回调用函数的状态
    int len;
    int flag=0;
    //判断是否打开串口

    const char *dev[]  = {"/dev/ttyTHS1"}; //串口名
    if (1)//yiqianshi (find)
    {
        fd = open(dev[0],O_RDWR | O_NOCTTY | O_NDELAY); //打开串口，返回文件描述符
        if(-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (0);
        }else{
            flag=1;//Seral open permit to trans
        }
    }else{
        printf("No Armor,Close the Serial\n");
        return 0;
    }

    do{
        err = UART0_Init(fd,115200,0,8,1,'N');
    }while(FALSE == err || FALSE == fd);

    while(1){
        uint8_t uart1_send_buf[5];
        uart1_send_buf[0] = (uint8_t)0xBB;
        uart1_send_buf[1] = (uint8_t)0x01;
        uart1_send_buf[2] = (u_first) & 0xff;
        uart1_send_buf[3] = (u_second) & 0xff;
        uart1_send_buf[4] = (u_third) & 0xff;

        printf("real serial relative up position is:\n");
        printf("%d\t",u_first);
        printf("%d\t",u_second);
        printf("%d\t",u_third);


        //fgets(send_buf,256,stdin);   //输入内容，最大不超过40字节，fgets能吸收回车符，这样pc收到的数据就能自动换行
       if (flag)
       {

           len = UART0_Send(fd, uart1_send_buf, 10);

           if(len > 0)
           {
               printf("time send %d data successful\n",len);
           }
           else
               printf("send data failed!\n");
           break;

       }
  }
    UART0_Close(fd);
}

int down_rela()
{

    /*if(find == 1){
        fire = 1;
    }else{
        fire = 0;
    }*/
    //cam_capture.yaw=(int16_t)(yaw*100);//*100
    //cam_capture.pitch=(int16_t)(pitch*100);//*100
    uint8_t y_first, y_second, y_third;
    y_first = (uint8_t)ajkl1[0];
    y_second = (uint8_t)ajkl1[1];
    y_third = (uint8_t)ajkl1[2];
    //cam_capture.fire=fire;
    //cam_capture.others=find;

    int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug
    int err;               //返回调用函数的状态
    int len;
    int flag=0;
    //判断是否打开串口

    const char *dev[]  = {"/dev/ttyTHS1"}; //串口名
    if (1)//yiqianshi (find)
    {
        fd = open(dev[0],O_RDWR | O_NOCTTY | O_NDELAY); //打开串口，返回文件描述符
        if(-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (0);
        }else{
            flag=1;//Seral open permit to trans
        }
    }else{
        printf("No Armor,Close the Serial\n");
        return 0;
    }

    do{
        err = UART0_Init(fd,115200,0,8,1,'N');
    }while(FALSE == err || FALSE == fd);

    while(1){
        uint8_t uart2_send_buf[5];
        uart2_send_buf[0] = (uint8_t)0xBB;
        uart2_send_buf[1] = (uint8_t)0x02;
        uart2_send_buf[2] = (y_first) & 0xff;
        uart2_send_buf[3] = (y_second) & 0xff;
        uart2_send_buf[4] = (y_third) & 0xff;

        printf("real serial relative down position is:\n");
        printf("%d\t",y_first);
        printf("%d\t",y_second);
        printf("%d\t",y_third);


        //fgets(send_buf,256,stdin);   //输入内容，最大不超过40字节，fgets能吸收回车符，这样pc收到的数据就能自动换行
       if (flag)
       {

           len = UART0_Send(fd, uart2_send_buf, 10);

           if(len > 0)
           {
               printf("time send %d data successful\n",len);
           }
           else
               printf("send data failed!\n");
           break;

       }
  }
    UART0_Close(fd);
}

int qr_serial()
{

    /*if(find == 1){
        fire = 1;
    }else{
        fire = 0;
    }*/

    //cam_capture.yaw=(int16_t)(yaw*100);//*100
    //cam_capture.pitch=(int16_t)(pitch*100);//*100
    uint8_t u_qr_code1, u_qr_code2, u_qr_code3, u_qr_code4, u_qr_code5, u_qr_code6;
    u_qr_code1=(uint8_t)a[0];
    u_qr_code2=(uint8_t)a[1];
    u_qr_code3=(uint8_t)a[2];
    u_qr_code4=(uint8_t)a[3];
    u_qr_code5=(uint8_t)a[4];
    u_qr_code6=(uint8_t)a[5];
    //cam_capture.fire=fire;
    //cam_capture.others=find;

    int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug
    int err;               //返回调用函数的状态
    int len;
    int flag=0;
    //判断是否打开串口

    const char *dev[]  = {"/dev/ttyTHS1"}; //串口名
    if (1)//yiqianshi (find)
    {
        fd = open(dev[0],O_RDWR | O_NOCTTY | O_NDELAY); //打开串口，返回文件描述符
        if(-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (0);
        }else{
            flag=1;//Seral open permit to trans
        }
    }else{
        printf("No Armor,Close the Serial\n");
        return 0;
    }

    do{
        err = UART0_Init(fd,115200,0,8,1,'N');
    }while(FALSE == err || FALSE == fd);

    while(1){
        uint8_t uart3_send_buf[7];
        uart3_send_buf[0] = (uint8_t)0xEE;
        uart3_send_buf[1] = (u_qr_code1) & 0xff;
        uart3_send_buf[2] = (u_qr_code2) & 0xff;
        uart3_send_buf[3] = (u_qr_code3) & 0xff;
        uart3_send_buf[4] = (u_qr_code4) & 0xff;
        uart3_send_buf[5] = (u_qr_code5) & 0xff;
        uart3_send_buf[6] = (u_qr_code6) & 0xff;

        printf("the qrcode sent is:\n");
        printf("%d\t", u_qr_code1);
        printf("%d\t", u_qr_code2);
        printf("%d\t", u_qr_code3);
        printf("%d\t", u_qr_code4);
        printf("%d\t", u_qr_code5);
        printf("%d\t", u_qr_code6);


        //fgets(send_buf,256,stdin);   //输入内容，最大不超过40字节，fgets能吸收回车符，这样pc收到的数据就能自动换行
       if (flag)
       {

           len = UART0_Send(fd, uart3_send_buf, 10);

           if(len > 0)
           {
               printf("time send %d data successful\n",len);
           }
           else
               printf("send data failed!\n");
           break;

       }
  }
    UART0_Close(fd);
}







//functional function
/*******************************************************************
*名称：             UART0_Open
*功能：             打开串口并返回串口设备文件描述
*入口参数：         fd      文件描述符
                    port    串口号(ttyTHS0,ttyTHS1,ttyTHS2)
*出口参数：正确返回为1，错误返回为0
*******************************************************************/
int UART0_Open(int fd,char*port)
{
    fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd<0)
    {
        perror("Can't Open Serial Port");
        return(FALSE);
    }
    //恢复串口为阻塞状态
    if(fcntl(fd, F_SETFL, 0) < 0)
    {
        printf("fcntl failed!\n");
        return(FALSE);
    }
    else
    {
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
    }
    //测试是否为终端设备
    if(0 == isatty(STDIN_FILENO))
    {
        printf("standard input is not a terminal device\n");
        return(FALSE);
    }
    else
    {
        printf("isatty success!\n");
    }
    printf("fd->open=%d\n",fd);
    return fd;
}
/*******************************************************************
*名称：             UART0_Close
*功能：             关闭串口并返回串口设备文件描述
*入口参数：         fd          文件描述符
                    port        串口号(ttyS0,ttyS1,ttyS2)
*出口参数：void
*******************************************************************/

void UART0_Close(int fd)
{
    close(fd);
}

/*******************************************************************
*名称：             UART0_Set
*功能：             设置串口数据位，停止位和效验位
*入口参数：         fd          串口文件描述符
*                   speed       串口速度
*                   flow_ctrl   数据流控制
*                   databits    数据位   取值为 7 或者8
*                   stopbits    停止位   取值为 1 或者2
*                   parity      效验类型 取值为N,E,O,,S
*出口参数：正确返回为1，错误返回为0
*******************************************************************/
int UART0_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{

    int   i;
    int   status;
    int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};

    struct termios options;

    /*  tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，
        该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.  */
    if( tcgetattr( fd,&options)  !=  0)
    {
        perror("SetupSerial 1");
        return(FALSE);
    }

    //设置串口输入波特率和输出波特率
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
        }
    }

    //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取输入数据
    options.c_cflag |= CREAD;

    //设置数据流控制
    switch(flow_ctrl)
    {

        case 0 ://不使用流控制
              options.c_cflag &= ~CRTSCTS;
              break;

        case 1 ://使用硬件流控制
              options.c_cflag |= CRTSCTS;
              break;
        case 2 ://使用软件流控制
              options.c_cflag |= IXON | IXOFF | IXANY;
              break;
    }
    //设置数据位
    //屏蔽其他标志位
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
        case 5    :
                     options.c_cflag |= CS5;
                     break;
        case 6    :
                     options.c_cflag |= CS6;
                     break;
        case 7    :
                 options.c_cflag |= CS7;
                 break;
        case 8:
                 options.c_cflag |= CS8;
                 break;
        default:
                 fprintf(stderr,"Unsupported data size\n");
                 return (FALSE);
    }
    //设置校验位
    switch (parity)
    {
        case 'n':
        case 'N': //无奇偶校验位。
                 options.c_cflag &= ~PARENB;
                 options.c_iflag &= ~INPCK;
                 break;
        case 'o':
        case 'O'://设置为奇校验
                 options.c_cflag |= (PARODD | PARENB);
                 options.c_iflag |= INPCK;
                 break;
        case 'e':
        case 'E'://设置为偶校验
                 options.c_cflag |= PARENB;
                 options.c_cflag &= ~PARODD;
                 options.c_iflag |= INPCK;
                 break;
        case 's':
        case 'S': //设置为空格
                 options.c_cflag &= ~PARENB;
                 options.c_cflag &= ~CSTOPB;
                 break;
        default:
                 fprintf(stderr,"Unsupported parity\n");
                 return (FALSE);
    }
    // 设置停止位
    switch (stopbits)
    {
        case 1:
                 options.c_cflag &= ~CSTOPB; break;
        case 2:
                 options.c_cflag |= CSTOPB; break;
        default:
                       fprintf(stderr,"Unsupported stop bits\n");
                       return (FALSE);
    }

    //修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    //options.c_lflag &= ~(ISIG | ICANON);

    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */

    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
    tcflush(fd,TCIFLUSH);

    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("com set error!\n");
        return (FALSE);
    }
    return (TRUE);
}
/*******************************************************************
*名称：                UART0_Init()
*功能：                串口初始化
*入口参数：            fd         文件描述符
*                      speed      串口速度
*                      flow_ctrl  数据流控制
*                      databits   数据位   取值为 7 或者8
*                      stopbits   停止位   取值为 1 或者2
*                      parity     效验类型 取值为N,E,O,,S
*
*出口参数：正确返回为1，错误返回为0
*******************************************************************/
int UART0_Init(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity)
{
    int err=0;
    //设置串口数据帧格式
    if (UART0_Set(fd,115200,0,8,1,'N') == FALSE)
    {
        return FALSE;
    }
    else
    {
        return  TRUE;
    }
}

/*******************************************************************
* 名称：            UART0_Recv
* 功能：            接收串口数据
* 入口参数：        fd         文件描述符
*                   rcv_buf    接收串口中数据存入rcv_buf缓冲区中
*                   data_len   一帧数据的长度
* 出口参数：        正确返回为1，错误返回为0
*******************************************************************/
int UART0_Recv(int fd, char *rcv_buf,int data_len)
{
    int len,fs_sel;
    fd_set fs_read;

    struct timeval time;

    FD_ZERO(&fs_read);
    FD_SET(fd,&fs_read);

    time.tv_sec = 1;
    time.tv_usec = 0;

    //串口的多路通信
    fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
    printf("fs_sel = %d\n",fs_sel);
    if(fs_sel)
    {
        len = read(fd,rcv_buf,data_len);
        return len;
    }
    else
    {
        return FALSE;
    }
}
/********************************************************************
* 名称：            UART0_Send
* 功能：            发送数据
* 入口参数：        fd           文件描述符
*                   send_buf     存放串口发送数据
*                   data_len     一帧数据的个数
* 出口参数：        正确返回为1，错误返回为0
*******************************************************************/
int UART0_Send(int fd, u_int8_t *send_buf,int data_len)
{
    int len = 0;

    len = write(fd,send_buf,data_len);
    if (len == data_len )
    {
        //printf("send data is %d\n",send_buf);
        return len;
    }
    else
    {

        tcflush(fd,TCOFLUSH);
        return FALSE;
    }

}
