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
    m_cap.open(url.get());
  } catch (...)
  {

  }

  movie.load("video.mov");
  movie.play();
}

void nebulaVideoSrc::update(){
  if (srcMovie) movie.update();
  else if (srcRTP){
    m_cap >> m_frame;
    ofxCv::toOf(m_frame, m_img);
    texture.loadData(m_img.getPixels());
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
  else if (srcRTP) return m_img.getPixels();
}

void nebulaVideoSrc::srcMovieCb(bool & flag){
  if (flag) {
    srcRTP=false;
  }
}

void nebulaVideoSrc::srcRTPCb(bool & flag){
  if (flag) {
    srcMovie=false;
  }
}
