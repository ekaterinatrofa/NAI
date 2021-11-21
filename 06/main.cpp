#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui_c.h>
#include <iostream>


using namespace cv;

using namespace std;


int main( int argc, char** argv ) {


    bool capturing = true;
    // Question for you
    // cv::VideoCapture cap( "szukaj_zielonego.webm" );

    cv::VideoCapture cap(0); //capture video from default camera


    // if not success, exit program
    if ( !cap.isOpened() ) {
        cerr << "error opening frames source" << endl;
        return -1;
    }

    cout << "Video size: " << cap.get( CAP_PROP_FRAME_WIDTH )
    << "x" << cap.get( CAP_PROP_FRAME_HEIGHT ) << endl;

    do {
        Mat frame; // declare the frame before rotate
        Mat mirror;

        if ( cap.read( frame ) ) {

            //flip(source, destination, flipcode)
            //flipcode:
            //1 - flip around y-axis
            //0 - flip around x-axis
            //-1 -flip both axes

            flip(frame, mirror, 1);


            //show window before rotating
            imshow("Not-yet smart windown", frame );  //.imshow() method is used to display an image in a window


            imshow("odbicie lustrzane", mirror);
        } else {
            // stream finished
            capturing = false;
        }
        //czekaj na klawisz, sprawdz czy to jest 'Q'
        if( (waitKey( 1000.0/60.0 )&0x0ff) == 81 ) capturing = false;
    } while( capturing );
    return 0;
}
