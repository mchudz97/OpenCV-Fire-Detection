#include "Gui.h"


using namespace cvui;

Gui::Gui(String winName) {

    this->queue = { "1.mp4", "2.mp4", "3.mp4", "4.mp4", "5.mp4" };
    this->winName = winName;
    this->vidChoice = 0;
    this->withSmoke = false;
    this->area = 0.0f;
    this->grayMin = 50.0f;
    this->grayMax = 220.0f;
    this->history = 10;
    this->mixtures = 10;
    this->smokeError = 5.0f;
    init(winName);

}

void Gui::show() {

    settingsWindow = Mat(620, 300, CV_8UC3);
    settingsWindow = Scalar(49, 52, 49);

    text(settingsWindow, 60, 20, "Currently playing: " + queue[vidChoice]);

    if (button(settingsWindow, 100, 40, "Play Next")) {

        vidChoice++;
        vidChoice = vidChoice % queue.size();

    }
    checkbox(settingsWindow, 40, 100, "With smoke", &withSmoke);
    text(settingsWindow, 40, 140, "Min area:");
    text(settingsWindow, 40, 220, "History:");
    text(settingsWindow, 40, 300, "Mixtures:");
    text(settingsWindow, 40, 380, "Smoke error:");
    text(settingsWindow, 40, 460, "Smoke gray min:");
    text(settingsWindow, 40, 540, "Smoke gray max:");
    trackbar(settingsWindow, 40, 160, 220, &area, 0.0f, 200.0f);
    trackbar(settingsWindow, 40, 240, 220, &history, 1, 100);
    trackbar(settingsWindow, 40, 320, 220, &mixtures, 1, 100);
    trackbar(settingsWindow, 40, 400, 220, &smokeError, 0.0f, 25.0f);
    trackbar(settingsWindow, 40, 480, 220, &grayMin, 0.0f, grayMax);
    trackbar(settingsWindow, 40, 560, 220, &grayMax, grayMin, 255.0f);


    cvui::imshow(this->winName, settingsWindow);

}

