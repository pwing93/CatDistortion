/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CatDistortionAudioProcessorEditor  :
    public
        AudioProcessorEditor,
    private
        ComboBox::Listener,
        Slider::Listener
{
public:
    CatDistortionAudioProcessorEditor (CatDistortionAudioProcessor&);
    ~CatDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged(Slider* sliderThatHasChanged) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CatDistortionAudioProcessor& processor;
    
    ComboBox disChoice;
    Slider inGain;
    Slider Threshold;
    Slider Mix;
    Slider outGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CatDistortionAudioProcessorEditor)
};
