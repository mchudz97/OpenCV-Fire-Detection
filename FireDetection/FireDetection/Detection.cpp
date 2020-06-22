#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>
#include "FireFeatureDetector.h"
#include <opencv2\video\background_segm.hpp>
#include <opencv2\imgproc.hpp>
#define CVUI_IMPLEMENTATION
#include "Gui.h"
#include "SmokeFeatureDetector.h"

using namespace cv;
using namespace std;

String WINDOW_NAME = "Detector";
VideoCapture videocap;
Mat frame, frame_gray, fire;
Ptr<BackgroundSubtractorMOG2> bsmog2;

int mixtures;
int history;
int currFile;

void drawRects(Mat mat, vector<vector<Point>> points, float bySize) {

    
    for (int i = 0; i < points.size(); i++) {

        if (contourArea(points[i]) >= bySize) {

            Rect bRect = boundingRect(points[i]);
            rectangle(mat, bRect, (0, 255, 0));

        }

    }

}

void trackbarCallback(int h, int m) {

    if (h != history || m != mixtures) {

        bsmog2 = createBackgroundSubtractorMOG2();
        bsmog2->setHistory(h);
        bsmog2->setNMixtures(m);
        history = h;
        mixtures = m;

    }

}

int main() {


    bsmog2 = createBackgroundSubtractorMOG2();
    bsmog2->setHistory(3);
    bsmog2->setNMixtures(5);

    Gui g = Gui("Detection Settings");

    videocap.open("1.mp4");

    if (!videocap.isOpened()) {

        bsmog2.release();
        videocap.release();
        return -1;

    }

    while (waitKey(15) != 27) {

        g.show();

        trackbarCallback(g.history, g.mixtures);

        vector<vector<Point>> contours;

        
        

        videocap >> frame;

        if (frame.empty()) {

            videocap.release();
            videocap.open(g.queue[currFile]);

        }

        GaussianBlur(frame, frame, Size(3, 3), 3);
        erode(frame, frame, MORPH_CROSS);
         
        FireFeatureDetector ffd = FireFeatureDetector(frame);
        
        imshow("ycbcr", ffd.YCbCrMat);

        fire = ffd.YCbCrMat;
        if (g.withSmoke) {

            SmokeFeatureDetector sfd = SmokeFeatureDetector(frame, g.smokeError);
            imshow("Smoke", sfd.Smoke);
            addWeighted(fire, .5, sfd.Smoke, .5, 0.0, fire);

        }

        else {

            destroyWindow("Smoke");

        }

        cvtColor(fire, frame_gray, COLOR_BGR2GRAY);
        bsmog2->apply(frame_gray, frame_gray);
        findContours(frame_gray, contours, RETR_LIST, CHAIN_APPROX_NONE);
        
        if (contours.size() != 0) {

            putText(frame, "Fire detected!", Point(20, 20), 1, 1, Scalar(0, 0, 255));
            for (int i = 0; i < contours.size(); i++) {

                drawContours(frame, contours, i, (0, 0, 255));

            }

            drawRects(frame, contours, g.area);

        }

        if (currFile != g.vidChoice) {

            videocap.release();
            bsmog2.release();
            bsmog2 = createBackgroundSubtractorMOG2();
            bsmog2->setNMixtures(g.mixtures);
            bsmog2->setHistory(g.history);
            currFile = g.vidChoice;
            videocap.open(g.queue[currFile]);

        }

        imshow(WINDOW_NAME, frame);

    }

    bsmog2.release();
    destroyAllWindows();
    videocap.release();
    return 0;

}