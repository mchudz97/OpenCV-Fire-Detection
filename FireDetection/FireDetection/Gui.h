
#include <opencv2\opencv.hpp>
#include "cvui.h"


using namespace cv;
using namespace std;

class Gui {

public:

	Mat settingsWindow;
	int mixtures;
	int history;
	int vidChoice;
	vector<String> queue;
	String winName;
	Gui(String winName);
	void show();
	void getPlayerButtonValue();

};

