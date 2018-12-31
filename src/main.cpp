#include "ofApp.h"

int main()
{
  ofGLFWWindowSettings settings;
  settings.width = 1280;
  settings.height = 960;
  settings.title = "nebula-eye";
  settings.windowMode = OF_FULLSCREEN;
  auto window = ofCreateWindow(settings);
  auto app = make_shared<nebulaEye>();
  ofRunApp(window, app);

  return ofRunMainLoop();
}
