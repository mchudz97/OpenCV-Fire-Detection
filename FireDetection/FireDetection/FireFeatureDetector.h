#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>


using namespace cv;
using namespace std;

class FireFeatureDetector {

public:

	Mat YCbCrMat;
	FireFeatureDetector(Mat toYCbCr);

};

