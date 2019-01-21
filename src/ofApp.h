#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxOscParameterSync.h"
#include "ofxCsv.h"

#include "nebulaVideoSrc.h"
#include "nebulaFlow.h"
#include "nebulaBackground.h"
#include "nebulaContourFinder.h"
#include "nebulaZone.h"

#define OSC_IP "192.168.1.108"
#define OSC_PORT 6868
#define OSC_LISTENING_PORT 12321

class nebulaEye : public ofBaseApp
{
  public:
    void setup  ();
    void update ();
    void draw   ();
    void exit   ();
    void mouseMoved(ofMouseEventArgs& mouse);
    void mouseDragged(ofMouseEventArgs& mouse);
    void mousePressed(ofMouseEventArgs& mouse);
    void mouseReleased(ofMouseEventArgs& mouse);
    void mouseScrolled(ofMouseEventArgs& mouse);
    void mouseEntered(ofMouseEventArgs& mouse);
    void mouseExited(ofMouseEventArgs& mouse);
    void keyPressed(int key);

    void learningTimeChanged(int & _time);
    void thresholdChanged(int & tresh);

    //void showBg();
    void sendOSC();
    void updateOSC();

    void recordCSVData();
    void setupCSVrecorder();
    void csvRecordCb(bool & flag);
    string getDate(), getHour();
    void clearTestImg(bool & flag);

    ofxPanel gui, recordPanel;
    ofParameterGroup displayGuiGrp;
    ofParameter<bool> showGui, showBgImage, showVideo, showBgSub, showContour, showFlow, showZone, record, mouseTest;
    ofParameter<int> bgSubIntensity, showDebug;
    ofxOscParameterSync parameterSync;

    nebulaVideoSrc video;
    nebulaFlow flow;
    nebulaBackground bgSub;
    nebulaContourFinder contour;
    nebula::Zone zone;

    ofPixels img;
    ofImage bgImg;
    cv::Mat testimg;
    ofxOscSender sender;
    ofxOscReceiver receiver;
    wng::ofxCsv csvRecorder;

    vector<float> flowZone;
};
