#include "FireFeatureDetector.h"




FireFeatureDetector::FireFeatureDetector(Mat toCheck) {

	float r, g, b, y, cb, cr;

	YCbCrMat = Mat::zeros(toCheck.rows, toCheck.cols, toCheck.type());

	for (int i = 0; i < toCheck.rows; i++) {

		for (int j = 0; j < toCheck.cols; j++) {

			r = toCheck.at<Vec3b>(i, j)[2];
			g = toCheck.at<Vec3b>(i, j)[1];
			b = toCheck.at<Vec3b>(i, j)[0];

			y = 16 + (r * 65.481 + g * 128.553 + b * 24.996)/256;
			cb = 128 + (r * -37.797 - g * 74.203 + b * 112.0)/256;
			cr = 128 + (r * 112.00 + g * -93.7864 + b * -18.214)/256;

			if (r>100 && r > g && g > b && r > 190 && g > 100 && b < 140 && y >= cb && cr >= cb) {

				YCbCrMat.at<Vec3b>(i, j) = Vec3b(y, cb, cr);

			}

		}

		

	}


}

