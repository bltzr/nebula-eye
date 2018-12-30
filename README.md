# nebula-eye
This is an interactive disposal based on Raspberry Pi camera and Max patches to detect people activity in the area

On the Raspberry Pi, start the stream with : 

    raspivid -t 0 -b 2000000 -fps 60 -w 640 -h 480 -sa -100 -o - | gst-launch-1.0 -e -vvv fdsrc ! h264parse ! rtph264pay pt=96 config-interval=5 ! udpsink host=<DESTINATION_IP> port=5000

And don't forget to add the destination computer IP.

You also play the `movie.mov` file inside the `bin` folder.

All the parameters are saved together in one `settings.xml` file and recalled automatically on start.
Background subtraction and motion flow algorithms will run on the OpenCL device if available.

# Dependencies

This is an openFrameworks application, so you need openFrameworks to build it : http://openframeworks.cc/download/
The common way is to put this repo inside the `apps/myApps` folder.
Then use the openFrameworks project generator to generate an IDE project.
But this way hasn't been tested for a while.

The alternative way, which is recommanded, is to use a CMake build system : https://github.com/ofnode/of/tree/nebula-eye.
Please note that you need to checkout the `nebula-eye` branch.
If you feel confortable with CMake but doesn't know openFrameworks very well, this could be easier.
Also, with CMake you choose your project generator, and then you can use Ninja.

## Addons

This project depends on severals OF addons.
There are setted as git submodules, but it seems that openFrameworks project generator assumes all addons should be in the main addons repository.
Which is bad to my eyes. I think it's better to use a specific commit of each addon then you can have different version of the same addon accross projects,
and the update of such an addon doesn't break your build. But this is only my point of view.
So if you're using the OF project generator, you will have to move all the `ofx*` folders to of's addons folder.
Check addons.make and / or CMakeLists' `ofxaddon()` calls to see which one are needed.

CMake build system support these local addon out-of-the-box.
So after update the submodule you be ready to configure and build.

### Known issues on OSX

OpenCV library shipped with openFraworks or brew doesn't include openCL support (which is needed).
Thus you need to build it yourself with the following command : 

	git clone --branch 2.4.13.7 --single-branch  --depth=1 https://github.com/opencv/opencv.git
	mkdir build-opencv
	cd build-opencv
	cmake ../opencv -GNinja \
      -DBUILD_opencv_apps=OFF \
      -DBUILD_opencv_calib3d=ON  \
	  -DBUILD_opencv_contrib=OFF \
	  -DBUILD_opencv_core=ON \
	  -DBUILD_opencv_features2d=ON \
	  -DBUILD_opencv_flann=ON \
	  -DBUILD_opencv_gpu=OFF \
	  -DBUILD_opencv_highgui=ON \
	  -DBUILD_opencv_imgproc=ON \
	  -DBUILD_opencv_legacy=ON \
	  -DBUILD_opencv_ml=ON \
	  -DBUILD_opencv_nonfree=OFF \
	  -DBUILD_opencv_objdetect=ON \
	  -DBUILD_opencv_ocl=ON \
	  -DBUILD_opencv_photo=OFF \
	  -DBUILD_opencv_python=OFF \
	  -DBUILD_opencv_stitching=OFF \
	  -DBUILD_opencv_superres=OFF \
	  -DBUILD_opencv_ts=OFF \
	  -DBUILD_opencv_video=ON \
	  -DBUILD_opencv_videostab=OFF \
	  -DBUILD_opencv_world=OFF \
	  -DBUILD_TEST=OFF \
	  -DBUILD_DOCS=OFF
	ninja
	ninja install

If you want to open network stream, you also need FFMPEG and/or GStreamer : 

    brew install ffmpeg gstreamer gst-plugins-base gst-plugins-good

and so on...

You could check which backend is supported when configuring project with CMake.
