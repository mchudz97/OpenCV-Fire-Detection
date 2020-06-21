#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>
#include "HsiValContainer.h"

using namespace cv;
using namespace std;

class FireFeatureDetector {

public:

	vector<vector<Vec3b>> YCbCrVals;
	Mat YCbCrMat;
	FireFeatureDetector(Mat toYCbCr);
	bool detected;
	

};

