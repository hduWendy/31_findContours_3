// 31_findContours_3.cpp : 定义控制台应用程序的入口点。
//
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	double i_minH = 0;
	double i_maxH = 180;

	double i_minS = 70;
	double i_maxS = 255;

	double i_minV = 46;
	double i_maxV = 255;

	double scale = 0.2;

		cv::Mat hsvMat;
		cv::Mat detectMat;
		cv::Mat smoothMat;

		cv::Mat frame = imread("C:/Users/lenovo/Desktop/数图图片/topic1.JPG");

		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
		cv::Mat  labels, stats, centroids;

		//连通域标记
		int num = cv::connectedComponentsWithStats(detectMat, labels, stats, centroids);
		//画框
		int i_num = num - 1;
		for (int i = 1; i <= i_num; i++)
		{
			cv::Rect rect;
			rect.x = stats.at<int>(i, 0);
			rect.y = stats.at<int>(i, 1);
			rect.width = stats.at<int>(i, 2);
			rect.height = stats.at<int>(i, 3);
			if (rect.width > 100)
			{
				rectangle(rFrame, rect, CV_RGB(255, 0, 0), 1, 8, 0);
			}
			else
			{
				num -= 1;
			}
		}


		//		cv::imshow("whie: in the range", detectMat);
		cv::imshow("rFrame", rFrame);

		//等待用户按键
		waitKey(0);
		return 0;

}

