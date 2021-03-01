/*
  =============================================================================

    ATanDistortion.
    Created: 6 Feb 2021 9:52:06p
    Author:  Adam Murdoc

  =============================================================================
*/

#pragma once
#inclue <JuceHeader.h>


class ATanDistortion {
public:
    float processSample(float , float inputDrivex);
    
    void setDrive(float newDrive);
private:
    float drive = 1.f;

};
