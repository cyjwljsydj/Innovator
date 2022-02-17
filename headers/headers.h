/*
#pragma once
#ifndef ANGLE_SOLVER
#define ANGLE_SOLVER
*/

//#pragma once
//#ifndef ANGLE_SOLVER
//#define ANGLE_SOLVER
#include<opencv2/calib3d.hpp>
#include<iostream>

#include "zbar.h"
//#include "cv.h"
//#include "highgui.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<string>

using namespace std;
using namespace zbar;  //添加zbar名称空间
using namespace cv;
//图片拟合椭圆中心点和长半轴和短半轴
extern float centerx;
extern float centery;
extern float w;
extern float h;


//存放物料位置的
extern float RPidentify_up[3];
extern float RPidentify_down[3];

//extern string qrchar1;//二维码解码
extern double x_pos;//xyz坐标
extern double y_pos;
extern double z_pos;
//要改成数组
extern double y_point[6];

//extern Point2f centerc;
extern int identify;
extern string code;

//定义排序数组
//extern int *a;
//extern int *b;
extern int ajkl[3];
extern int ajkl1[3];
//图片像素四个点
extern Point2d point_identical[4];

//qrcode char str
extern int a[6];

//extern int *q;

//extern int *up_rela[5];



class Coloridentify
{
public:

    /*
    识别物料轮廓
    */
    void coloridentify(Mat srcjkl,int types);
    //void coloridentify(Mat srcjkl,int types);
private:
    Mat img;
    Mat  img_hsv;
    Mat mask;
    Mat mask_erode;
    Mat mask_dilate;
    Mat structElement1;
    Mat mask_gaussian;

    vector<vector<Point>> contours;  //轮廓
    vector<Vec4i> hierarchy;  //存放轮廓结构变量
    Mat imgcontours;
    Mat structElement2;

    double maxarea = 0;
    int maxareaidx = 0;

    RotatedRect box;

    //拟合的圆型中心点和半径
    Point2f center;
    double radius;
};


class relative_position_identify
{
public:

    /*
    识别物料轮廓
    */

    void relative_position2(Mat srcjkl, int types);

    void relative_position1(Mat identify,int types);

    void relative_position3(Mat identify_size);

private:
    Mat img;
    Mat imgasd;
    Mat img_hsv;
    Mat mask;
    Mat mask_erode;
    Mat mask_dilate;
    Mat structElement1;
    Mat mask_gaussian;

    int upwheel[3];
    int downwheel[3];

    vector<vector<Point>> contours;  //轮廓
    vector<Vec4i> hierarchy;  //存放轮廓结构变量
    Mat imgcontours;
    Mat structElement2;

    double maxarea = 0;
    int maxareaidx = 0;

    RotatedRect box;

    //拟合的圆型中心点和半径
    Point2f center;
    double radius;
};
class AngleSolver
{
public:
    void setArmorSize(int type);

private:

    Mat CAMERA_MATRIX;    //IntrinsicMatrix		  fx,fy,cx,cy
    Mat DISTORTION_COEFF; //DistortionCoefficients k1,k2,p1,p2

    //Object points in world coordinate
    vector<Point3f> SMALL_ARMOR_POINTS_3D;
    vector<Point3f> BIG_ARMOR_POINTS_3D;

    //distance between camera and barrel in y axis(positive when camera is under barrel)  barrel_y = camera_y + barrel_camera_y
    double GUN_CAM_DISTANCE_Y;

    // calculated by solvePnP
    //s[R|t]=s'  s->world coordinate;s`->camera coordinate
    Mat rVec;    //rot rotation between camera and target center
    Mat tVec;  //trans tanslation between camera and target center

    //Results
};

//#endif // !ANGLE_SOLVER
class QRcode
{
public:
    void qrcode(Mat srcjkl);

    string qrchar;

private:
    //ImageScanner scanner;
    Mat imageGray;
    int width;
    int height;
    uchar* raw;
    //Image imageZbar;
};
