/*
  =============================================================================

    ATanDistortion.h
    Created: 6 Feb 2021 9:52:06p
    Author:  Adam Murdock

  =============================================================================
*/

#pragma once
#include <JuceHeader.h>



class ATanDistortion {
public:
    float processSample(float sample, float inputDrive);
    
    void setDrive(float newDrive);
private:
    float drive = 1.f;

};
