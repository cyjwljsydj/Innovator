#include"headers.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>


void relative_position_identify::relative_position2(Mat srcjkl, int types) {
    srcjkl.copyTo(img);
    namedWindow("Video Capture", WINDOW_AUTOSIZE);
    //imshow("Video Capture", img);

    cvtColor(img, img_hsv, COLOR_BGR2HSV);

    //inRange(img_hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);


    switch (types)
    {
    case 3:
        inRange(img_hsv, Scalar(100, 100, 46), Scalar(124, 255, 255), mask); //蓝色识别

        structElement2 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        erode(mask, mask, structElement2);
        //imshow("��ʴ", mask_erode);
        //����
        structElement1 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        dilate(mask, mask, structElement1);
        //imshow("����", mask_dilate);
        //��˹�˲�
        GaussianBlur(mask, mask, Size(5, 5), 0, 0);

        break;
    case 1:
        inRange(img_hsv, Scalar(0, 43, 46), Scalar(20, 255, 255), mask);//红色识别

        structElement2 = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
        erode(mask, mask, structElement2);
        //imshow("��ʴ", mask_erode);
        //����
        structElement1 = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
        dilate(mask, mask, structElement1);
        //imshow("����", mask_dilate);
        //��˹�˲�    +

        GaussianBlur(mask, mask, Size(5, 5), 0, 0);

        break;
    case 2:
        inRange(img_hsv, Scalar(55, 210, 100), Scalar(77, 255, 255), mask);
        break;
/*
        structElement2 = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));
        erode(mask, mask, structElement2);
        structElement1 = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));
        dilate(mask, mask, structElement1);
        mask_gaussian;
        GaussianBlur(mask, mask, Size(5, 5), 0, 0);
 */
   default:
        cout << "WRONG COLOR GIVEN!" << endl;
        break;
    }
    /*
    int select_num ;
    switch(types)
    {
        case 1:select_num = 7;
            break;
        case 2:select_num = 11;
             break;
        case 3:select_num = 7;
            break;
        default:
            break;
    }
    mask_erode;
    structElement2 = getStructuringElement(MORPH_RECT, Size(select_num, select_num), Point(-1, -1));
    erode(mask, mask, structElement2);
    //imshow("腐蚀ʴ", mask_erode);
    //膨胀

    structElement1 = getStructuringElement(MORPH_RECT, Size(select_num, select_num), Point(-1, -1));
    dilate(mask, mask, structElement1);
    //imshow("膨胀", mask_dilate);
    //高斯滤波
    GaussianBlur(mask, mask, Size(5, 5), 0, 0);
*/
    relative_position1(mask,types);
    //imshow("mask_gussain", mask_gaussian);
    /*
    for (int index = contours.size() - 1; index >= 0; index--)//找到最大轮廓
    {
        double tmparea = fabs(contourArea(contours[index]));
        if (tmparea > maxarea)
        {
            maxarea = tmparea;
            maxareaidx = index;
        }
    }
    */
}


void relative_position_identify::relative_position1(Mat identify,int types)
{
    float RPidentify_y[2];
    for (int i = 0; i < 2; i++)
        RPidentify_y[i] = 0.0;

    float RPidentify_x[2];
    for (int i = 0; i < 2; i++)
        RPidentify_x[i] = 0.0;

    int i = 0;
    //img = identify;
    //findContours(identify, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    findContours(identify, contours, 0, 2);
        for (int index = contours.size() - 1; index >= 0; index--) {
            if (contours[index].size() < 100)continue;
            box = fitEllipse(contours[index]);

            ellipse(img, box, Scalar(0, 0, 255), 1, LINE_8);
            //imshow("Video Capture", img);
            w = box.size.width;
            h = box.size.height;
            //椭圆的中心坐标
            center = box.center;
            centerx = center.x;
            centery = center.y;

            cout << "-----------------------------------------------" << endl;
            cout << "w:" << endl << w << endl;
            cout << "h:" << endl << h << endl;
            cout << "center.x:" << endl << center.x << endl;
            cout << "center.y:" << endl << center.y << endl;
            cout << "-----------------------------------------------" << endl;
            if ( i < 2) {
                RPidentify_y[i] = center.y;
                RPidentify_x[i] = center.x;

                i++;
            }
        }
        if (RPidentify_y[0] > RPidentify_y[1]) {
            RPidentify_down[types - 1] = RPidentify_x[0];
            RPidentify_up[types - 1] = RPidentify_x[1];
        }
        else {
            RPidentify_down[types - 1] = RPidentify_x[1];
            RPidentify_up[types - 1] = RPidentify_x[0];
        }
        //imshow("Video Capture", img);
        contours.clear();
        hierarchy.clear();
        //waitKey(0);
}

void relative_position_identify::relative_position3(Mat identify_size)
{
    //比较RPidentify_up的大小，为
    for (int i = 0; i < 3; i++)
        RPidentify_down[i] = 0.0;
    for (int i = 0; i < 3; i++)
        RPidentify_down[i] = 0.0;
    imgasd = identify_size;
    relative_position2(imgasd, 1);
    imshow("Video Capture_red", img);
    relative_position2(imgasd, 2);
    imshow("Video Capture_green", img);
    relative_position2(imgasd, 3);
    imshow("Video Capture_blue", img);


    //判断是否有空
    for (int i = 0; i < 3; i++) {
        if (RPidentify_up[i] == 0.0) {
            identify = 1;
            cout << "could not find" << endl;
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (RPidentify_down[i] == 0.0) {
            identify = 1;
            cout << "could not find" << endl;
            return;
        }
    }

    //比较RPidentify_down的大小，为

    for (int i = 0; i < 3; i++)
        cout << "" << endl << RPidentify_down[i] << endl;
    for (int i = 0; i < 3; i++)
        cout << "" << endl << RPidentify_up[i] << endl;

    float a, b, c, t;
    a = RPidentify_up[0];
    b = RPidentify_up[1];
    c = RPidentify_up[2];
    if (a > b)
    {
        t = a;
        a = b;
        b = t;
    }
    if (a > c)
    {
        t = a;
        a = c;
        c = t;
    }
    if (b > c)
    {
        t = b;
        b = c;
        c = t;
    }
    //printf("这三个数中最大的数是：%d\n", c);
    //printf("将这三个书按从小到大的顺序排列为：%d\t%d\t%d\n", c, b, a);
    if (RPidentify_up[0] == a)ajkl[0] = 1;
    if (RPidentify_up[1] == a)ajkl[0] = 2;
    if (RPidentify_up[2] == a)ajkl[0] = 3;
    if (RPidentify_up[0] == b)ajkl[1] = 1;
    if (RPidentify_up[1] == b)ajkl[1] = 2;
    if (RPidentify_up[2] == b)ajkl[1] = 3;
    if (RPidentify_up[0] == c)ajkl[2] = 1;
    if (RPidentify_up[1] == c)ajkl[2] = 2;
    if (RPidentify_up[2] == c)ajkl[2] = 3;
    for (int i = 0; i < 3; i++) {

        cout << ajkl[i] << endl;
    }
    float a1, b1, c1, t1;
    a1 = RPidentify_down[0];
    b1 = RPidentify_down[1];
    c1 = RPidentify_down[2];
    if (a1 > b1)
    {
        t1 = a1;
        a1 = b1;
        b1 = t1;
    }
    if (a1 > c1)
    {
        t1 = a1;
        a1 = c1;
        c1 = t1;
    }
    if (b1 > c1)
    {
        t1 = b1;
        b1 = c1;
        c1 = t1;
    }
    //printf("这三个数中最大的数是：%d\n", c);
    //printf("将这三个书按从小到大的顺序排列为：%d\t%d\t%d\n", c, b, a);
    if (RPidentify_down[0] == a1)ajkl1[0] = 1;
    if (RPidentify_down[1] == a1)ajkl1[0] = 2;
    if (RPidentify_down[2] == a1)ajkl1[0] = 3;
    if (RPidentify_down[0] == b1)ajkl1[1] = 1;
    if (RPidentify_down[1] == b1)ajkl1[1] = 2;
    if (RPidentify_down[2] == b1)ajkl1[1] = 3;
    if (RPidentify_down[0] == c1)ajkl1[2] = 1;
    if (RPidentify_down[1] == c1)ajkl1[2] = 2;
    if (RPidentify_down[2] == c1)ajkl1[2] = 3;
    for (int i = 0; i < 3; i++) {
        cout << ajkl1[i] << endl;
    }
}
