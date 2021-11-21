#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui_c.h>
#include <iostream>


using namespace cv;

const int max_value_H = 360/2;
const int max_value = 255;

const String window_detection_name = "Object Detection";

int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value, high_S = max_value, high_V = max_value;

int main( int argc, char** argv )
{
    bool capturing = true;
    cv::VideoCapture cap(0); //capture video from default camera

    int width;
    int height;

    if(argc==3)
    {
        width = atoi(argv[1]);
        height = atoi (argv[2]);
    }
    else
    {

        width = 320;
        height = 200;

    }

    // if not success, exit program
    if ( !cap.isOpened() )
    {
        std:: cerr << "error opening frames source" << std::endl;
        return -1;
    }



    cv::namedWindow("HSV slider",WINDOW_AUTOSIZE);

    // Trackbars to set thresholds for HSV values
    cv::createTrackbar("Low H", "HSV slider", &low_H, max_value_H);
    cv::createTrackbar("High H", "HSV slider", &high_H, max_value_H);

    cv::createTrackbar("Low S", "HSV slider", &low_S, max_value);
    cv::createTrackbar("High S", "HSV slider", &high_S, max_value);

    cv::createTrackbar("Low V", "HSV slider", &low_V, max_value);
    cv::createTrackbar("High V", "HSV slider", &high_V, max_value);


    do
    {
        cv::Mat frame, blurFrame, frame_HSV, frame_threshold; // declare the frame



        if(cap.read( frame ))
        {
            cv::resize(frame, frame, {width, height});
            cv::imshow("Not blurr", frame);
            cv::GaussianBlur(frame, blurFrame, cv::Size(5, 5), 0);

            cv::imshow("Blur", blurFrame);  //.imshow() method is used to display an image in a window

            // Convert from BGR to HSV colorspace
            cv::cvtColor(blurFrame, frame_HSV, COLOR_BGR2HSV);


            // Detect the object based on HSV Range Values
            cv::inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V),frame_HSV);



            cv::putText(frame_HSV, std::to_string(low_H), cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
            cv::putText(frame_HSV, std::to_string(low_S), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
            cv::putText(frame_HSV, std::to_string(low_V), cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.5,cv::Scalar(255,255,25));

            cv::putText(frame_HSV, std::to_string(high_H), cv::Point(10, 80), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
            cv::putText(frame_HSV, std::to_string(high_S),cv::Point(10, 100), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
            cv::putText(frame_HSV, std::to_string(high_V), cv::Point(10, 120), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));

            cv::imshow(window_detection_name, frame_HSV);

        }
        else
        {
            // stream finished
            capturing = false;
        }




        //czekaj na klawisz, sprawdz czy to jest 'Q'
        //  if( (waitKey( 1000.0/60.0 )&0x0ff) == 81 ) capturing = false;

        char key = (char) waitKey(30);

        if (key == 'x')
        {

            // Select ROI
            cv::Rect2d r = cv::selectROI(window_detection_name, frame_HSV);
            cv::imwrite("nai.jpg", cv::Mat(frame_HSV, r));
        }
        if (key == 'q' || key == 27)
        {
            capturing = false;
        }
    }
    while( capturing );
    return 0;
}
