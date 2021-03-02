/*
  =============================================================================

    ATanDistortion.cp
    Created: 6 Feb 2021 9:52:06p
    Author:  Adam Murdock

  =============================================================================
*/

#include "ATanDistortion.h"
#include <JuceHeader.h>
//#import <cmath>

float ATanDistortion::processSample(float sample,float inputDrive)  {
    setDrive(inputDrive);
    float y = (2.f/M_PI) * drive * sample;
    return y;
    
};

void ATanDistortion::setDrive(float newDrive) {
    if (newDrive <= 10.f && newDrive >= 0.f)
    drive = newDrive;
}
