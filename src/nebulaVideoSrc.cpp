#include "nebulaVideoSrc.h"
#include "ofxCv.h"

void nebulaVideoSrc::setup()
{
  guiGrp.setName("video source");
  guiGrp.add(url.set("url","192.168.1.194:5000"));
  guiGrp.add(srcRTP.set("RTP stream", true));
  guiGrp.add(srcMovie.set("movie", false));

  srcMovie.addListener(this, &nebulaVideoSrc::srcMovieCb);
  srcRTP.addListener(this, &nebulaVideoSrc::srcRTPCb);

  try {
    m_cap.open(0); //was: m_cap.open(url.get());
  } catch (...)
  {

  }

  movie.load("video.mov");
  movie.stop();

  m_crop = cv::Rect(0, 200, 1000, 1000);

}

void nebulaVideoSrc::update(){
  if (srcMovie) movie.update();
  else if (srcRTP){
    m_cap >> m_frame;
    //m_cropped = m_frame(m_crop).clone();
    ofxCv::toOf(m_frame, m_img);
    //ofLog() << "IMG:" << m_img.getWidth() << " " << m_img.getHeight();
    int cropX1{120}, cropX2{140}, cropY{110}, cropLoY{70};
    m_img.getPixels().cropTo(cropped, cropX1, cropY, m_img.getWidth()-cropX1-cropX2, m_img.getHeight()-cropY-cropLoY);
    //ofLog() << "CROP:" << cropped.getWidth() << " " << cropped.getHeight();
    texture.loadData(cropped);
  }
}

void nebulaVideoSrc::draw(int x, int y, int w, int h){
  if (srcMovie) movie.draw(x,y,w,h);
  else if (srcRTP) {
    if ( texture.isAllocated() )
      texture.draw(x,y,w,h);
    }
}

bool nebulaVideoSrc::isFrameNew(){
  if (srcMovie) return movie.isFrameNew();
  else if (srcRTP) return true;
}

ofPixels& nebulaVideoSrc::getPixels(){
  if (srcMovie) return movie.getPixels();
  else if (srcRTP) return cropped;
}

void nebulaVideoSrc::srcMovieCb(bool & flag){
  if (flag) {
    srcRTP=false;
    movie.play();
  }
}

void nebulaVideoSrc::srcRTPCb(bool & flag){
  if (flag) {
    srcMovie=false;
    movie.stop();
  }
}
