#include "FireFeatureDetector.h"




FireFeatureDetector::FireFeatureDetector(Mat toCheck) {

	float r, g, b, y, cb, cr;

	YCbCrMat = Mat::zeros(toCheck.rows, toCheck.cols, toCheck.type());

	for (int i = 0; i < toCheck.rows; i++) {

		vector<Vec3b> YCbCrCols;

		for (int j = 0; j < toCheck.cols; j++) {

			r = toCheck.at<Vec3b>(i, j)[2];

			g = toCheck.at<Vec3b>(i, j)[1];

			b = toCheck.at<Vec3b>(i, j)[0];

			y = 16 + r * 65.481 + g * 128.553 + b *
				24.996;
			cb = 128 + r * -37.797 - g * 74.203 + b *
				112.0;
			cr = 128 + r * 112.00 + g * -93.7864 + b *
				-18.214;
			
			YCbCrCols.push_back(Vec3b(y,cb,cr));
			

			if (r > g && g > b && r > 190 && g > 100 && b < 140  && y >= cb && y >= cb && cr >= cb) {

				YCbCrMat.at<Vec3b>(i, j) = Vec3b(y, cb, cr);

				detected = true;

			}		

		}

		YCbCrVals.push_back(YCbCrCols);

	}

}

