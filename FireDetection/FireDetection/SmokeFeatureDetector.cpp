#include "SmokeFeatureDetector.h"


using namespace cv;
using namespace std;


SmokeFeatureDetector::SmokeFeatureDetector(Mat mat, float alpha, float grayMin, float grayMax) {

	float r, g, b;
	Smoke = Mat::zeros(mat.rows, mat.cols, mat.type());

	for (int i = 0; i < mat.rows; i++) {

		for (int j = 0; j < mat.cols; j++) {


			r = mat.at<Vec3b>(i, j)[2];
			g = mat.at<Vec3b>(i, j)[1];
			b = mat.at<Vec3b>(i, j)[0];

			if (abs(r - g) <= alpha && abs(r - b) <= alpha  && abs(b - g) <= alpha
				&& (r + g + b) / 3.0f >= grayMin && (r + g + b) / 3.0f <= grayMax) {

				Smoke.at<Vec3b>(i, j) = mat.at<Vec3b>(i, j);

			}

		}

	}


}
