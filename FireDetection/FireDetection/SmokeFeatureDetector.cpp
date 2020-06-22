#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\video\tracking.hpp>
#include "SmokeFeatureDetector.h"

using namespace cv;
using namespace std;


SmokeFeatureDetector::SmokeFeatureDetector(Mat mat, float alpha) {

	float r, g, b, y, cb, cr;
	Smoke = Mat::zeros(mat.rows, mat.cols, mat.type());

	for (int i = 0; i < mat.rows; i++) {

		for (int j = 0; j < mat.cols; j++) {


			r = mat.at<Vec3b>(i, j)[2];
			g = mat.at<Vec3b>(i, j)[1];
			b = mat.at<Vec3b>(i, j)[0];

			if (abs(r - g) <= alpha && abs(r - b) <= alpha  && abs(b - g) <= alpha
				&& (r + g + b) / 3.0f >= 15 && (r + g + b) / 3.0f <= 220) {

				Smoke.at<Vec3b>(i, j) = Vec3b(0, 0, 255);

			}

		}

	}


}
