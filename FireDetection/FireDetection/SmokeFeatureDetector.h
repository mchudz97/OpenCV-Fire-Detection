#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>


using namespace cv;
using namespace std;

class SmokeFeatureDetector {

public:

	Mat Smoke;
	SmokeFeatureDetector(Mat mat, float alpha, float grayMin, float grayMax);

};