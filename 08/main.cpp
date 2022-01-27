#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui_c.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    bool capturing = true;

    int loRange[3] = {36, 90, 88};
    int hiRange[3] = {88, 235, 227};

    namedWindow("jakostam", cv::WINDOW_AUTOSIZE);
    createTrackbar("loRange0", "jakostam", &(loRange[0]), 255);
    createTrackbar("loRange1", "jakostam", &(loRange[1]), 255);
    createTrackbar("loRange2", "jakostam", &(loRange[2]), 255);
    createTrackbar("hiRange0", "jakostam", &(hiRange[0]), 255);
    createTrackbar("hiRange1", "jakostam", &(hiRange[1]), 255);
    createTrackbar("hiRange2", "jakostam", &(hiRange[2]), 255);

    cv::VideoCapture cap(0); //capture video from default camera

    // if not success, exit program
    if ( !cap.isOpened() )
    {
        std:: cerr << "error opening frames source" << std::endl;
        return -1;
    }




    do
    {
        // declare the frames

        cv::Mat frame;
        cv::Mat frameMask;
        cv::Mat frameNegMask;



        if(cap.read( frame ))
        {

            flip(frame, frame, 1);


            // Convert from BGR to HSV colorspace
            cv::cvtColor(frame, frameMask, COLOR_BGR2HSV);


            // Detect the object based on HSV Range Values

            cv::inRange(frameMask, cv::Scalar(loRange[0], loRange[1], loRange[2]), cv::Scalar(hiRange[0], hiRange[1], hiRange[2]), frameNegMask);

            int dilation_size = 5;
            auto structElem = getStructuringElement(MORPH_RECT,
                                                    Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                                    Point(dilation_size, dilation_size));




            cv::morphologyEx(frameNegMask, frameNegMask, MORPH_CLOSE, structElem);
            cv::morphologyEx(frameNegMask, frameNegMask, MORPH_OPEN, structElem);

            imshow("neg", frameNegMask);


            std::vector<vector<Point>> contours;
            cv::findContours(frameNegMask, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

            sort(contours.begin(), contours.end(),
                 [](auto &a, auto &b)
            {
                return contourArea(a, false) > contourArea(b, false);
            });


            for (int i = 0; i < contours.size(); i++)
            {
//                approxPolyDP(contours.at(i), contours.at(i), 10, true);

                //frame, contours, contourIdx, color, thickness
                cv::drawContours(frame, contours, i, Scalar(0, 255, 0), 2);
            }


            if (contours.size() >= 2)
            {
                int x[2], y[2];
                for (int i = 0; i < 2; i++)
                {
                  //compute the center of the contour

                    auto mnts = cv::moments(contours.at(i));
                    x[i] = int(mnts.m10 / mnts.m00);
                    y[i] = int(mnts.m01 / mnts.m00);

                 // center of the shape on the image
                    cv::circle(frame, cv::Point(x[i],y[i]), 7, (255,255,255), -1);
                    cv::putText(frame, "center", cv::Point(x[i]-5,y[i]-5), cv::FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2);
                }



                if((y[0] < y[1] + 50) && (y[0] > y[1] - 50))
                    cv::line(frame, {x[0], y[0]}, {x[1], y[1]}, {255, 0, 0, 255}, 3);
            }


            cv::imshow("frame", frame);


        }
        else
        {
            // stream finished
            capturing = false;
        }




        //czekaj na klawisz, sprawdz czy to jest 'Q'
        //  if( (waitKey( 1000.0/60.0 )&0x0ff) == 81 ) capturing = false;

        char key = (char) waitKey(30);


        if (key == 'q' || key == 27)
        {
            capturing = false;
        }
    }
    while( capturing );
    return 0;
}
