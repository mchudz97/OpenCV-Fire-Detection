#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "EnhancedWindow.h"
#include "FireFeatureDetector.h"
#include <opencv2\video\background_segm.hpp>

using namespace cv;
using namespace std;

String WINDOW_NAME = "yolo";
VideoCapture videocap;
Mat frame, frame_gray, fire;
Ptr<BackgroundSubtractorMOG2> bsmog2;

float minArea = 0;
Rect FireRoi;

int main() {


    bsmog2 = createBackgroundSubtractorMOG2();
    bsmog2->setHistory(3);
    bsmog2->setNMixtures(5);

    

    videocap.open("2.mp4");

    while (waitKey(15) != 27) {

        vector<vector<Point>> contours;

        videocap >> frame;
        FireFeatureDetector ffd = FireFeatureDetector(frame);

        fire = ffd.YCbCrMat;
        //GaussianBlur(fire, fire, Size(5, 5), 3);
        cvtColor(fire, frame_gray, COLOR_BGR2GRAY);
        
        bsmog2->apply(frame_gray, frame_gray);
        findContours(frame_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
      

        for (int i = 0; i < contours.size(); i++) {

            if (contourArea(contours[i]) > minArea) {

  
                for (int j = 0; j < contours[i].size(); j++) {

                    frame.at<Vec3b>(contours[i][j]) = Vec3b(255, 0, 0);

                }

            

            }

        }
 

        //HsiMat hsimat = HsiMat(frame);
        imshow(WINDOW_NAME, frame);
        

    }

    return 0;

}