#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui_c.h>
#include <opencv4/opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CascadeClassifier plate_cascade;

/** @function detectAndDisplay */

vector<Rect> find_cars(Mat frame)
{
    Mat frame_gray;
    vector<Rect> cars;

    cvtColor(frame,frame_gray,COLOR_BGR2GRAY);

    equalizeHist(frame_gray, frame_gray);
    plate_cascade.detectMultiScale(frame_gray, cars, 1.1, 3, 0, Size(20, 20));
    return cars;
}


int last_x = 0;
int last_y = 0;

int carCounter=0;


int main()
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascade

    if (!plate_cascade.load("C:\\Users\\PC\\Documents\\3 rok\\NAI\\09\\haarcascade_russian_plate_number.xml"))
    {
        return -9;
    }

    capture.open(0);
    //capture.open("C:\\Users\\PC\\Documents\\3 rok\\NAI\\09\\car.mp4");

    //-- 2. Read the video stream

    if (!capture.isOpened())
    {
        return -7;
    }


    while (capture.read(frame))
    {
        if (frame.empty())
        {

            return -1;
        }




        flip(frame, frame, 1);

        resize(frame, frame, {800, 600});


        vector<Rect> detected_cars = find_cars(frame);

        for(auto car:detected_cars)
        {
            Point center(car.x + car.width/2, car.y + car.height/2 );
            rectangle(frame, Point(car.x, car.y), Point(car.x+car.width, car.y+car.height), Scalar(255, 0, 255), 3);

            if(! (last_x - car.x < 90 && last_x - car.x > -90 && last_y - car.y < 90 && last_y - car.y > -90) )

            {
                carCounter++;
                cout<<"New car number "<<carCounter<<endl;
            }

            last_x=car.x;
            last_y=car.y;


            break;
        }


        putText(frame,to_string(carCounter), Point2f(100,100), FONT_HERSHEY_PLAIN, 3,  Scalar(0,0,255,255), 2);
        imshow("DWI", frame);

        if ((waitKey(1) & 0x0ff) == 27)
            return 0;
    }
    return 0;
}
