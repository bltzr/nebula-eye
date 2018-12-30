#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class nebulaVideoSrc
{
public:
    void setup();
    void update();
    void draw(int x, int y, int w, int h);
    void draw(int x, int y){draw(x,y,0,0);};
    bool isFrameNew();
    ofPixels& getPixels();

    void srcMovieCb(bool & flag);
    void srcRTPCb(bool & flag);

    ofVideoPlayer movie;
    ofTexture texture;
    ofParameterGroup guiGrp;

    cv::VideoCapture m_cap;
    ofImage m_img;
    cv::Mat m_frame;

    ofParameter<bool> srcMovie, srcRTP;
    ofParameter<string> url;
};
