#pragma once

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Camera
{
  public:
    Camera(void);
    void startCamera(void);
    bool active = true;
};