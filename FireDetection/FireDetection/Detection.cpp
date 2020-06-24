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

String WINDOW_NAME = "Original with detection";
VideoCapture videocap;
Mat frame, frame_gray, fire;
Ptr<BackgroundSubtractorMOG2> bsmog2;
int mixtures;
int history;
int currFile;

void draw(Mat mat, vector<vector<Point>> points, float bySize) {

    bool found = false;

    for (int i = 0; i < points.size(); i++) {

        if (contourArea(points[i]) >= bySize) {

            found = true;
            drawContours(mat, points, i, (0, 0, 255));

        }

    }

    if (found) {

        putText(mat, "Fire detected!", Point(20, 20), 1, 1, Scalar(0, 0, 255));

    }

}

void trackbarCallback(int h, int m) {

    if (h != history || m != mixtures) {

        bsmog2.release();
        bsmog2 = createBackgroundSubtractorMOG2();
        bsmog2->setHistory(h);
        bsmog2->setNMixtures(m);
        history = h;
        mixtures = m;

    }

}

int main() {

    Gui g = Gui("Detection Settings");
    videocap.open(g.queue[0]);

    if (!videocap.isOpened()) {

        bsmog2.release();
        videocap.release();
        destroyAllWindows();
        return -1;

    }

    bsmog2 = createBackgroundSubtractorMOG2();
    bsmog2->setHistory(g.history);
    bsmog2->setNMixtures(g.mixtures);

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
        fire = ffd.YCbCrMat;
        imshow("Fire", fire);

        if (g.withSmoke) {

            SmokeFeatureDetector sfd = SmokeFeatureDetector(frame, g.smokeError, g.grayMin, g.grayMax);
            imshow("Smoke", sfd.Smoke);
            addWeighted(fire, 0.5, sfd.Smoke, 0.5, 0.0, fire);

        }

        else {

            destroyWindow("Smoke");

        }

        cvtColor(fire, frame_gray, COLOR_BGR2GRAY);
        bsmog2->apply(frame_gray, frame_gray);
        findContours(frame_gray, contours, RETR_CCOMP, CHAIN_APPROX_NONE);
        draw(frame, contours, g.area);

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