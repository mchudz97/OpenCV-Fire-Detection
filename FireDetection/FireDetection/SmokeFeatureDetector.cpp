#include "SmokeFeatureDetector.h"


using namespace cv;
using namespace std;


SmokeFeatureDetector::SmokeFeatureDetector(Mat mat, float alpha, float grayMin, float grayMax) {

	float r, g, b, y, cb, cr;
	Smoke = Mat::zeros(mat.rows, mat.cols, mat.type());

	for (int i = 0; i < mat.rows; i++) {

		for (int j = 0; j < mat.cols; j++) {

			r = mat.at<Vec3b>(i, j)[2];
			g = mat.at<Vec3b>(i, j)[1];
			b = mat.at<Vec3b>(i, j)[0];

			y = 16 + (r * 65.481 + g * 128.553 + b * 24.996) / 256;
			cb = 128 + (r * -37.797 - g * 74.203 + b * 112.0) / 256;
			cr = 128 + (r * 112.00 + g * -93.7864 + b * -18.214) / 256;

			/*if ( abs(r - g) <= alpha && abs(r - b) <= alpha  && abs(b - g) <= alpha
				&& (r + g + b) / 3.0f >= grayMin && (r + g + b) / 3.0f <= grayMax ) {

				Smoke.at<Vec3b>(i, j) = mat.at<Vec3b>(i, j);

			}*/

			if ((cb - 128) * (cb - 128) + (cr - 128) * (cr - 128) <= alpha * alpha && y >= grayMin && y <= grayMax) {

				Smoke.at<Vec3b>(i, j) = mat.at<Vec3b>(i, j);

			}

		}

	}

}
