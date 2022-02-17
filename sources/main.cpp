/*
#include <iostream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <opencv4/opencv2/imgproc/types_c.h>
#include <opencv4/opencv2/videoio.hpp>

using namespace std;
using namespace cv;

string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method)
{
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + to_string(capture_width) + ", height=(int)" +
           to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + to_string(flip_method) + " ! video/x-raw, width=(int)" + to_string(display_width) + ", height=(int)" +
           to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main( int argc, char** argv )
{
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;
    int flip_method2 = 0 ;
    //创建管道
    string pipeline = gstreamer_pipeline(capture_width,
    capture_height,
    display_width,
    display_height,
    framerate,
    flip_method);
    std::cout << "使用gstreamer管道: \n\t" << pipeline << "\n";

    //管道与视频流绑定
    VideoCapture cap(pipeline, CAP_GSTREAMER);
    if(!cap.isOpened())
    {
        std::cout<<"打开摄像头失败."<<std::endl;
        return (-1);
    }
    string pipeline2 = gstreamer_pipeline(capture_width,
    capture_height,
    display_width,
    display_height,
    framerate,
    flip_method2);
    VideoCapture cap2(pipeline2, CAP_GSTREAMER);

    //创建显示窗口
    namedWindow("CSI Camera", WINDOW_AUTOSIZE);
    Mat img;
    //创建窗口2
    namedWindow("CSI Camera2", WINDOW_AUTOSIZE);
    Mat img2;
    //逐帧显示
    while(true)
    {
        if (!cap.read(img))
        {
            std::cout<<"捕获失败"<<std::endl;
            break;
        }
        int new_width,new_height,width,height,channel;
            width=img.cols;
            height=img.rows;
            channel=img.channels();


        //调整图像大小
        new_width=640;
        if(width>800)
          {
             new_height=int(new_width*1.0/width*height);
           }
         resize(img, img, cv::Size(new_width, new_height));

        imshow("CSI Camera",img);


        if (!cap2.read(img))
        {
            std::cout<<"捕获失败"<<std::endl;
            break;
        }
        int new_width2,new_height2,width2,height2,channel2;
            width2=img2.cols;
            height2=img2.rows;
            channel2=img2.channels();


        //调整图像大小
        new_width2=640;
        if(width2>800)
          {
             new_height2=int(new_width2*1.0/width2*height2);
           }

        resize(img2, img2, cv::Size(new_width2, new_height2));

       imshow("CSI Camera",img2);



        int keycode = cv::waitKey(30) & 0xff ; //ESC键退出
            if (keycode == 27) break ;
    }

    cap.release();
    destroyAllWindows() ;
}
*/

#include <iostream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <opencv4/opencv2/imgproc/types_c.h>
#include <opencv4/opencv2/videoio.hpp>
#include "serial_innovator.h"
#include "headers.h"

using namespace std;
using namespace cv;


//创建相机通道
/*string gstreamer_pipeline (int sensor_id, int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method)
{
    return "nvarguscamerasrc sensor-id=" + to_string(sensor_id) + " ! video/x-raw(memory:NVMM), width=(int)" + to_string(capture_width) + ", height=(int)" +
           to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + to_string(flip_method) + " ! video/x-raw, width=(int)" + to_string(display_width) + ", height=(int)" +
           to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}
*/
string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method)
{
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + to_string(capture_width) + ", height=(int)" +
           to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + to_string(flip_method) + " ! video/x-raw, width=(int)" + to_string(display_width) + ", height=(int)" +
           to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//


//图片拟合椭圆中心点和长半轴和短半轴
 float centerx;
 float centery;
 float w;
 float h;


//存放物料位置的
 float RPidentify_up[3];
 float RPidentify_down[3];

//extern string qrchar1;//二维码解码
 double x_pos;//xyz坐标
 double y_pos;
 double z_pos;
//要改成数组
 double y_point[6];

//extern Point2f centerc;
 int identify;
 string code;

//定义排序数组
//extern int *a;
//extern int *b;
 int ajkl[3];
 int ajkl1[3];
 //图片像素四个点
 Point2d point_identical[4];

 int a[6];

int main( int argc, char** argv )
{

    /*Mat jkl;
    jkl =imread("/home/tars-go/qc.jpg");
    if (!jkl.data)
    {
        std::cout<<"相机1 捕获失败"<<std::endl;
        return -1;
    }

    QRcode sjsj;
    sjsj.qrcode(jkl);*/

    //相机的初始参数
    //int sensor_id1 = 1 ;
    //int sensor_id0 = 0 ;
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;
    //------------------------------------------------------------------------------

    //创建管道
    string pipeline1 = gstreamer_pipeline(capture_width,
    capture_height,
    display_width,
    display_height,
    framerate,
    flip_method);

    /*string pipeline0 = gstreamer_pipeline(sensor_id0,capture_width,
    capture_height,
    display_width,
    display_height,
    framerate,
    flip_method);*/
    //------------------------------------------------------------------------------

    std::cout << "使用gstreamer管道: \n\t" << pipeline1 << "\n";
    //std::cout << "使用gstreamer管道: \n\t" << pipeline0 << "\n";


    //text

    //管道与视频流绑定
    VideoCapture cap1(pipeline1, CAP_GSTREAMER);
    if(!cap1.isOpened())
    {
        std::cout<<"打开摄像头1 失败."<<std::endl;
        return (-1);
    }

    /*VideoCapture cap0(pipeline0, CAP_GSTREAMER);
    if(!cap0.isOpened())
    {
        std::cout<<"打开摄像头2 失败."<<std::endl;
        return (-1);
    }*/
    //------------------------------------------------------------------------------

    //创建显示窗口
    namedWindow("CSI Camera_1", WINDOW_AUTOSIZE);
    //namedWindow("CSI Camera_2", WINDOW_AUTOSIZE);

    Mat img1;
    //Mat img1Calibration;

    //Mat img0;

    //Mat frame;
    //string imgname;
    //int f = 1;

    //逐帧显示 img1
    while(true)
    {
        if (!cap1.read(img1))
        {
            std::cout<<"相机1 捕获失败"<<std::endl;
            break;
        }

        //--------------------------------------------------------------

        //蓝色识别
       //frame = img1;
       //imshow("das",frame);
       //char key =waitKey(1);
       //if (key == 27)break;
       //if (key =='q'||key == 'Q')
       //{
           //imgname = to_string(f++) + ".jpg";
           //imwrite(imgname, frame);
       //}

        //创建新图像参数 img1
/*color position identify
 * prototype

        imshow("das",img1);
        //红色识别
        cout << "红色识别" << endl;
        identify = 1;
        Coloridentify retestr;
        retestr.coloridentify(img1, 1);
        //角度解算
        AngleSolver angler;
        if (identify == 1)
        {
            angler.setArmorSize(1);
            //串口
            color_position(1,x_pos,y_pos,z_pos,1);
        }
        //--------------------------------------------------------------



        //绿色识别
        cout << "绿色识别" << endl;
        identify = 1;
        Coloridentify retestg;
        retestg.coloridentify(img1, 2);
        //角度解算
        AngleSolver anglerg;
        if (identify == 1)
        {
            anglerg.setArmorSize(2);
            //串口
            color_position(2,x_pos,y_pos,z_pos,2);
        }
        //-------------------------------------------------------------
        //蓝色识别
        cout << "蓝色识别" << endl;
        identify = 1;
        Coloridentify retestb;
        retestb.coloridentify(img1,3);//3蓝色1红色1绿色
        //角度解算
        AngleSolver angleb;
        if (identify == 1)       //identify为一,则识别到,为0,则未识别到
        {
            angleb.setArmorSize(3);//1是物料,二是色环
            //串口
            color_position(3,x_pos,y_pos,z_pos,3);
        }
        //--------------------------------------------------------------

        //分隔符
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
        //


        cout << "Red色色环识别" << endl;
        identify = 1;
        Coloridentify circler;
        circler.coloridentify(img1, 4);//1蓝色2红色3绿色
        //角度解算
        AngleSolver circle_angle_r;
        if (identify == 1)
        {
            circle_angle_r.setArmorSize(4);//1是物料,二是色环
            //串口
            color_position(4,x_pos,y_pos,z_pos,4);
        }


        cout << "lv色色环识别" << endl;
        identify = 1;
        Coloridentify circleg;
        circleg.coloridentify(img1, 5);//1蓝色2红色3绿色
        //角度解算
        AngleSolver circle_angle_g;
        if (identify == 1)
        {
            circle_angle_g.setArmorSize(5);//1是物料,二是色环
            //串口
            color_position(5,x_pos,y_pos,z_pos,5);
        }

        //蓝色色环识别
        cout << "蓝色色环识别" << endl;
        identify = 1;
        Coloridentify circleb;
        circleb.coloridentify(img1, 6);//1蓝色2红色3绿色
        //角度解算
        AngleSolver circle_angle_b;
        if (identify == 1)
        {
            circle_angle_b.setArmorSize(6);//1是物料,二是色环
            //串口
            color_position(6,x_pos,y_pos,z_pos,6);
        }
*/


        relative_position_identify relapos;
        relapos.relative_position3(img1);
        cout<<"up relative is:"<<ajkl[3]<<endl;
        cout<<"down relative is:"<<ajkl1[3]<<endl;

        //串口
        up_rela();

        down_rela();

        /*for(int i = 0; i < 5; i++){
            cout << "real serial relative position is:" << rela_up[i] << endl;
        }*/



        //------------------------------------------------------------

        //创建新图像参数 img1
        /*int new_width1,new_height1,width1,height1,channel1;
            width1=img1.cols;
            height1=img1.rows;
            channel1=img1.channels();


        //调整图像大小
        new_width1=640;
        if(width1>800)
          {
             new_height1=int(new_width1*1.0/width1*height1);
           }
         resize(img1, img1, cv::Size(new_width1, new_height1));
        */
       // imshow("CSI Camera_1",img1);//   物料识别
        //imshow("Original",img1);
        
        
        //畸变校正
        /*Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
        cameraMatrix.at<double>(0,0) = 4.246550592360193e+02;
        cameraMatrix.at<double>(0,1) = 0.443655502972530;
        cameraMatrix.at<double>(0,2) = 3.170188602211277e+02;
        cameraMatrix.at<double>(1,1) = 5.678956483516620e+02;
        cameraMatrix.at<double>(1,2) = 2.317969190543426e+02;

        Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
        distCoeffs.at<double>(0,0) = -0.026665193913615;
        distCoeffs.at<double>(1,0) = -0.0102272994238830;
        distCoeffs.at<double>(2,0) = -9.222865148887594e-04;
        distCoeffs.at<double>(3,0) = -3.301227026455217e-05;
        distCoeffs.at<double>(4,0) = 0;

        Mat view, review, map1, map2;
        Size imageSize;
        imageSize = img1.size();
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
            getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
            imageSize, CV_16SC2, map1, map2);

        remap(img1, img1Calibration, map1, map2, INTER_LINEAR);

        imshow("Calibration",img1Calibration);
        */

        //--------------------------------------------------------------

        //逐帧显示 img0
        /*if (!cap0.read(img0))
        {
            std::cout<<"相机2 捕获失败"<<std::endl;
            break;
        }*/
        //--------------------------------------------------------------

        identify=1;

        QRcode retestqr;
        //retestqr.qrcode(srcjkl);
        //返回二维码信息
        retestqr.qrcode(img1);
        if (identify == 1) {
            cout << "" << endl << code << endl;
            //transfer string to char str[]

            char p[50] = {0};
            code.copy(p, code.size(), 0);

            a[6] = 0;
            int j = 0;
            for(int i = 0; i < 7; i++){
                if((int)p[i] < 48 || (int)p[i] > 52) continue;

                a[j] = (int)p[i] - 48;

                j++;
            }

            //将code从string类型转换成char*型
           //const char *qrcap;
           //qrcap=code.data();
            //串口
           qr_serial();
        }


        //创建新图像参数 img0
        /*int new_width0,new_height0,width0,height0,channel0;
            width0=img0.cols;
            height0=img0.rows;
            channel0=img0.channels();



        //调整图像大小
        new_width0=640;
        if(width0>800)
          {
             new_height0=int(new_width0*1.0/width0*height0);
           }
         resize(img0, img0, cv::Size(new_width0, new_height0));

        //imshow("CSI Camera_2",img0);*/

        int keycode = cv::waitKey(30) & 0xff ; //ESC键退出
            if (keycode == 27) break ;

        waitKey(30);
    }

    cap1.release();
    //cap0.release();

    destroyAllWindows() ;

}



