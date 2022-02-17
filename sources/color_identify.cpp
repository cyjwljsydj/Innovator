#include"headers.h"
#include<iostream>
#include<opencv2/opencv.hpp>


void Coloridentify::coloridentify(Mat srcjkl,int types) {
    srcjkl.copyTo(img);
    namedWindow("Video Capture",WINDOW_AUTOSIZE);
    //imshow("Video Capture", img);

    cvtColor(img, img_hsv, COLOR_BGR2HSV);
    //创建掩模在（color_lower, color_upper）之间的像素设为255，其它为0

    //inRange(img_hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);


    switch (types)
    {
    case 1:
        inRange(img_hsv, Scalar(150, 43, 46), Scalar(180, 255, 255), mask); //红色物料识别
        break;
    case 2:
        inRange(img_hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//绿色色物料识别
        break;
    case 3:
        inRange(img_hsv,Scalar(100, 43, 46), Scalar(124, 255, 255),mask);//蓝色物料识别
        break;
    case 4:
        inRange(img_hsv, Scalar(150, 43, 46), Scalar(180, 255, 255), mask); //红色色环识别
        break;
    case 5:
        inRange(img_hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//绿色物料识别
        break;
    case 6:
        inRange(img_hsv,Scalar(100, 43, 46), Scalar(124, 255, 255),mask);//蓝色物料识别
        break;
        //绿色识别
    default:
        cout << "WRONG COLOR GIVEN!" << endl;
        break;
    }

    //structElement2 = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1, -1));
    //erode(mask, mask_erode, structElement2);
    //imshow("腐蚀", mask_erode);
    //膨胀

    //structElement1 = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1, -1));
    //dilate(mask_erode, mask_dilate, structElement1);
    //imshow("膨胀", mask_dilate);
    //高斯滤波
    //GaussianBlur(mask_dilate, mask_gaussian, Size(3, 3), 0, 0);
    //imshow("mask_gussain", mask_gaussian);

    switch(types){
    case 4:
    case 5:
    case 6:
        structElement1 = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
        dilate(mask, mask, structElement1);
        structElement2 = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1, -1));
        erode(mask, mask, structElement2);
        // imshow("腐蚀", mask);
        break;
     default:
        break;
    }
    //findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    findContours(mask,contours,0,2);
    
    for (int index = (int)contours.size() - 1; index >= 0; index--)// 找到最大的轮廓
    {
        double tmparea = fabs(contourArea(contours[index]));
        if (tmparea > maxarea)
        {
            maxarea = tmparea;
            maxareaidx = index;
        }
    }

    if (maxareaidx > 0 && contours[maxareaidx].size() > 5)
    {
        drawContours(img, contours, maxareaidx, Scalar(255), 1, 8, hierarchy);
        imshow("drawcontours", img);
        int a = (int)contours[maxareaidx].size();
        int b = 0;
        int c = 0;
        //上点
        b = 100000;
        c = 0;
        for (int i = 0; i < a - 1; i++) {
            if (contours[maxareaidx][i].y < b) {
                b = contours[maxareaidx][i].y;
                c = i;
            }
        }
        point_identical[0] = contours[maxareaidx][c];
        // cout << "上点" << endl;
        // cout << "输出上点的y坐标  " << contours[maxareaidx][c].y << endl;
        //cout << "输出上点的x坐标  " << contours[maxareaidx][c].x << endl;
        //cout << "-----------" << endl;
        //右点
        b = 0;
        c = 0;
        for (int i = 0; i < a - 1; i++) {
            if (contours[maxareaidx][i].x > b) {
                b = contours[maxareaidx][i].x;
                c = i;
            }
        }
        point_identical[1] = contours[maxareaidx][c];
        //cout << "右点" << endl;
        //cout << "输出右点的y坐标  " << contours[maxareaidx][c].y << endl;
        //cout << "输出右点的x坐标  " << contours[maxareaidx][c].x << endl;
        //cout << "-----------" << endl;

        //下点  y的最大值
        b = 0;
        c = 0;
        for (int i = 0; i < a - 1; i++) {
            if (contours[maxareaidx][i].y > b) {
                b = contours[maxareaidx][i].y;
                c = i;
            }
        }
        point_identical[2] = contours[maxareaidx][c];
        //cout << "下点" << endl;
        //cout << "输出下点的y坐标  " << contours[maxareaidx][c].y << endl;
        //cout << "输出下点的x坐标  " << contours[maxareaidx][c].x << endl;
        //cout << "-----------" << endl;
        //左点
        b = 100000;
        c = 0;
        for (int i = 0; i < a - 1; i++) {
            if (contours[maxareaidx][i].x < b) {
                b = contours[maxareaidx][i].x;
                c = i;
            }
        }
        point_identical[3] = contours[maxareaidx][c];
        //cout << "左点" << endl;
        //cout << "输出左点的y坐标  " << point_identical[3].y << endl;
        //cout << "输出左点的x坐标  " << point_identical[3].x << endl;
        //cout << "-----------" << endl;

        contours.clear();
        hierarchy.clear();
    }else {
        cout << "没有找到" << endl;
        identify = 0;//没有识别到
    }
    //waitKey(0);
}
