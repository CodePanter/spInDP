/* 
 * File:   main.cpp
 * Author: maarten
 *
 * Created on April 22, 2014, 1:17 PM
 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int threshold_value = 0;
int threshold_type = 1;;
int const max_value = 255;
int const max_type = 1;
int const max_BINARY_value = 255;
int erosion_size = 0;
int textHeight = 30;
int orderLoop = 0;


bool orderSet = false;
bool setOrder();

char cOrder[3];

double redContour[3], greenContour[3], blueContour[3];

Mat getRed(Mat srcBGR);
Mat redFilter(Mat src);
Mat blueFilter(Mat src);
Mat greenFilter(Mat src);
Mat thresh_callback(Mat frame, Scalar color, double* contourInfo);
Mat element;
Mat frame;
Mat frameRed;
Mat frameBlue;
Mat frameGreen;

int main(int argc, char* argv[])
{
    VideoCapture cap(-1); // open the video camera no. 0    
    cap.set(CV_CAP_PROP_FPS, 2);
    cout << sizeof(double);
    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }
    cap.read(frame);
    int top     = (int) (0.02*frame.rows); 
    int bottom  = (int) (0.02*frame.rows);
    int left    = (int) (0.02*frame.cols); 
    int right   = (int) (0.02*frame.cols);
    
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    //namedWindow("RawVideo",CV_WINDOW_AUTOSIZE);
    while (1)
    {       
        bool bSuccess = cap.read(frame); // read a new frame from video       
        //imshow("RawVideo", frame);
        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
      
        RNG rng(12345);
        int borderType = BORDER_CONSTANT;
        Scalar value = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
        copyMakeBorder( frame, frame, top, bottom, left, right, borderType, value );
               
        frameRed = redFilter(frame);
        frameGreen = greenFilter(frame);
        frameBlue = blueFilter(frame);
        Mat frame_gray;
        
                
        addWeighted( frameBlue, 0.5, frameRed, 1, 0.0, frame);
        addWeighted( frameGreen, 0.5, frame, 1, 0.0, frame);
        
        if(!orderSet)
        {
            orderSet = setOrder();
            
        }
        
        imshow("MyVideo", frame); //show the frame in "MyVideo" window
        textHeight = 30;
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
    }
    return 0;

}
bool setOrder()
{
    char tmp[3];
    int const MIN_AREA = 200;
    if(redContour[0] > MIN_AREA && greenContour[0] > MIN_AREA && blueContour[0] > MIN_AREA)
    {
        if(redContour[2] < greenContour[2] && redContour[2] < blueContour[2])
        {
            tmp[0] = 'r';
            if (greenContour[2] < blueContour[2])
            {
                tmp[1] = 'g';
                tmp[2] = 'b';
            }
            else 
            {
                tmp[1] = 'b';
                tmp[2] = 'g';
            }
        } 
     
        if(orderLoop == 5)   
        {           
            string str(cOrder);
                cout << str << endl;
                return true;
        }
        else
        {
            if(cOrder[0] != tmp[0] && cOrder[1] != tmp[1] && cOrder[2] != tmp[2])
                orderLoop = 0;
            else
                orderLoop++;
            
         strcpy (cOrder,tmp);
//            cOrder[0] = tmp[0];
//            cOrder[1] = tmp[1];
//            cOrder[2] = tmp[2];
            return false;
        }
    }
    else        
        return false;
    
}
Mat redFilter(Mat src)
{
    assert(src.type() == CV_8UC3);
    cv::Mat redOnly;
    inRange(src, Scalar(0, 0, 130), Scalar(100, 100, 255), redOnly);    
    Scalar color = Scalar( 0, 0, 255 );
    redOnly = thresh_callback(redOnly, color, redContour);
    //cout << "Red area, x, y: \t" << redContour[0] <<  " | " << redContour[1] << " | " << redContour[2] << endl;
    return redOnly;
}
Mat blueFilter(Mat src)
{
    assert(src.type() == CV_8UC3);
    cv::Mat blueOnly;
    inRange(src, Scalar(130, 0, 0), Scalar(255, 100, 100), blueOnly);
    Scalar color = Scalar( 255, 0, 0 );
    blueOnly = thresh_callback(blueOnly, color, blueContour);    
    //cout << "Blue area, x, y: \t" << blueContour[0] <<  " | " << blueContour[1] << " | " << blueContour[2] << endl;
    return blueOnly;
}
Mat greenFilter(Mat src)
{
    assert(src.type() == CV_8UC3);
    cv::Mat greenOnly;
    inRange(src, Scalar(0, 130, 0), Scalar(100, 255, 100), greenOnly);
    Scalar color = Scalar( 0, 255, 0 );
    greenOnly = thresh_callback(greenOnly, color, greenContour);    
    //cout << "Green area, x, y: \t" << greenContour[0] <<  " | " << greenContour[1] << " | " << greenContour[2] << endl;
    return greenOnly;
}
// Function to remove small blobs from the binary image
Mat thresh_callback(Mat frame, Scalar color, double* contourInfo)
{
    int thresh = 60;
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    threshold( frame, frame, threshold_value, max_BINARY_value,threshold_type );
    
    erosion_size = 6; 
    element = getStructuringElement(cv::MORPH_CROSS,
    cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
    cv::Point(erosion_size, erosion_size) );

    erode(frame, frame, element);
    dilate(frame, frame, element);   
    
    
    /// Detect edges using Threshold
    threshold( frame, threshold_output, thresh, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    { 
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    }
    /// Draw polygonal contour + bonding rects + circles
    frame = Mat::zeros( threshold_output.size(), CV_8UC3 );

    rectangle(frame,Point(0,0),Point(frame.cols-20,frame.rows-20),Scalar(0,0,0),1,8,0);
    int largestIndex = 0;
    int largestContour = 0;   
    for( int i = 0; i< contours.size(); i++ )
        {
            if(contours[i].size() > largestContour){        
            largestContour = contours[i].size();
            largestIndex = i;
        }
    }
    if(largestIndex > 0)
    {
        rectangle( frame, boundRect[largestIndex].tl(), boundRect[largestIndex].br(), color, 2, 8, 0 );
        drawContours( frame, contours, largestIndex, color, CV_FILLED, 8);
        
        *contourInfo = contourArea(contours[largestIndex]);
              
        textHeight += 15;
    }
    vector<Moments> mu(1);
    vector<Point2f> mc(1);
    mu[0] = moments(contours[largestIndex], false);
    mc[0] = Point2f( mu[0].m10/mu[0].m00 , mu[0].m01/mu[0].m00 );
    
    contourInfo++;
    *contourInfo = mc[0].x; 
    contourInfo++;
    *contourInfo = mc[0].y; 
    
    return frame;
}