

#include "Gui.h"
using namespace cvui;

Gui::Gui(String winName) {

    this->queue = { "1.mp4", "2.mp4" };
    this->winName = winName;
    this->vidChoice = 0;
    this->history = 10;
    this->mixtures = 10;
    init(winName);

}

void Gui::show() {

    settingsWindow = Mat(400, 400, CV_8UC3);
    settingsWindow = Scalar(49, 52, 49);

    text(settingsWindow, 100, 20, "Currently playing: " + queue[vidChoice]);

    if (button(settingsWindow, 100, 40, "Play Next")) {

        vidChoice++;
        vidChoice = vidChoice % queue.size();

    }

    text(settingsWindow, 40, 180, "History:");
    text(settingsWindow, 40, 280, "Mixtures:");
    trackbar(settingsWindow, 40, 300, 220, &mixtures, 1, 100);
    trackbar(settingsWindow, 40, 200, 220, &history, 1, 100);


    cvui::imshow(this->winName, settingsWindow);

}

