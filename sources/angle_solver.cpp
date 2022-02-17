#include "headers.h"
#include<iostream>
#include<opencv2/opencv.hpp>

void AngleSolver::setArmorSize(int type )
{

    switch (type)
    {
    case 1://物料,直接输入数据
    case 2:
    case 3:
            SMALL_ARMOR_POINTS_3D.push_back(Point3f(0, -25, 0));   //tl top left
            SMALL_ARMOR_POINTS_3D.push_back(Point3f(25, 0, 0));	//tr top right
            SMALL_ARMOR_POINTS_3D.push_back(Point3f(0, 25, 0));   //br below right
            SMALL_ARMOR_POINTS_3D.push_back(Point3f(-25, 0, 0));  //bl below left
            break;

    case 4://色环
    case 5:
    case 6:
            BIG_ARMOR_POINTS_3D.push_back(Point3f(0, -75,0));   //tl top left
            BIG_ARMOR_POINTS_3D.push_back(Point3f(75,0,0));   //tr top right
            BIG_ARMOR_POINTS_3D.push_back(Point3f(0, 75,0));//bl below left
            BIG_ARMOR_POINTS_3D.push_back(Point3f(-75,0,0));  //br below right
            break;
    default: break;
    }
    Mat _rvec;//matlab求解
    Mat cameraMatrix(3, 3, CV_64FC1);      //Camera Intrinsic Matrix
    cameraMatrix.at<double>(0, 0) = 8.254448458970363e+02;
    cameraMatrix.at<double>(0, 1) = 0.017364985589253;
    cameraMatrix.at<double>(0, 2) = 6.566623388357270e+02;
    cameraMatrix.at<double>(1, 0) = 0;
    cameraMatrix.at<double>(1, 1) = 8.259661556483333e+02;
    cameraMatrix.at<double>(1, 2) = 3.853930320716705e+02;
    cameraMatrix.at<double>(2, 0) = 0;
    cameraMatrix.at<double>(2, 1) = 0;
    cameraMatrix.at<double>(2, 2) = 1;

    Mat distrionCoeff(1, 5, CV_64FC1);    //Camera Distrion Coeffs
    distrionCoeff.at<double>(0, 0) = -0.056660258498368;
    distrionCoeff.at<double>(0, 1) = -0.068903901460946;
    distrionCoeff.at<double>(0, 2) = 0.002765684410599;
    distrionCoeff.at<double>(0, 3) = -2.853076579838363e-04;
    distrionCoeff.at<double>(0, 4) = 0;

    vector<Point2f> targetPoints2D;

    targetPoints2D.push_back(point_identical[0]);
    targetPoints2D.push_back(point_identical[1]);
    targetPoints2D.push_back(point_identical[2]);
    targetPoints2D.push_back(point_identical[3]);

    switch (type)
    {
    case 1:
    case 2:
    case 3:
            solvePnP(SMALL_ARMOR_POINTS_3D, targetPoints2D, cameraMatrix, distrionCoeff, _rvec, tVec, false, SOLVEPNP_ITERATIVE); break;
    case 4:
    case 5:
    case 6:
            solvePnP(BIG_ARMOR_POINTS_3D, targetPoints2D, cameraMatrix, distrionCoeff, _rvec, tVec, false, SOLVEPNP_ITERATIVE); break;
    default:
        break;
    }
    Rodrigues(_rvec, rVec);


    x_pos = tVec.at<double>(0, 0);
    y_pos = tVec.at<double>(1, 0);
    z_pos = tVec.at<double>(2, 0);
    //distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
    cout << "-----------------------------------------------" << endl;
    cout << "tVec:" << endl;
    cout << " X:" << tVec.at<double>(0, 0);
    cout << " Y:" << tVec.at<double>(1, 0);
    cout << " Z:" << tVec.at<double>(2, 0);
    //cout << " y_point:  " << y_pos << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "********************************************************************************************************" << endl;

}
