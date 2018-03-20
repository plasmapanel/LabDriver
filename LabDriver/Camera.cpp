#include "Camera.h"

Camera::Camera(void)
{
 
}

void Camera::startCamera(void)
{
  cv::VideoCapture capture(1);       // open a first USB camera found (0-based camera index)
  //if (!capture.isOpened())           // if camera not found, display an error message
  //printf("Error: cannot open a camera\n");

  cv::Mat cam;

  while (true)
  {
    if (active == false)
      break;
    if (capture.isOpened())
      capture >> cam;                   // read a next frame from camera live stream

    // cv::imshow("Still image", pic);      // display the still image on a window

    //if (!cam.empty())
    cv::line(cam, cv::Point(0, 218), cv::Point(640, 218), cv::Scalar(110, 220, 0), 1, 8);
    cv::line(cam, cv::Point(344, 0), cv::Point(344, 480), cv::Scalar(110, 220, 0), 1, 8);
    cv::imshow("Camera image", cam);  // display live camera stream on another window

  if (cv::waitKey(1) == 27)            // exit this loop when ESC was pressed
      break;                           // also locks up wx if commented out
  }

  capture.release();
}