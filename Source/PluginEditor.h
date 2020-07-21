
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class CatDistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    CatDistortionAudioProcessorEditor (CatDistortionAudioProcessor&, AudioProcessorValueTreeState&);
    ~CatDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    CatDistortionAudioProcessor& processor;
    AudioProcessorValueTreeState& params;
    Slider threshSlider, mixSlider, inSlider, outSlider;
    ComboBox typeBox;
    Label threshLabel, mixLabel, typeLabel, inLabel, outLabel;
    std::unique_ptr<SliderAttachment> threshAttachment, mixAttachment, inAttachment, outAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;
    
    void addSlider(String name, String labelText, Slider& slider, Label& label, std::unique_ptr<SliderAttachment>& attachment)
    {
        addAndMakeVisible(slider);
        attachment.reset(new SliderAttachment (params, name, slider));
        label.setText(labelText, dontSendNotification);
        label.attachToComponent(&slider, true);
        addAndMakeVisible(label);
    }
    
    void addComboBox(String name, String labelText, ComboBox& comboBox, Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>& attachment)
    {
        addAndMakeVisible(comboBox);
        attachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment (params, name, comboBox));
        label.setText(labelText, dontSendNotification);
        label.attachToComponent(&comboBox, true);
        addAndMakeVisible(label);
    }
    
//    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
//    void sliderValueChanged(Slider* sliderThatHasChanged) override;
//    // This reference is provided as a quick way for your editor to
//    // access the processor object that created it.
//    CatDistortionAudioProcessor& processor;
//
//    ComboBox disChoice;
//    Slider inGain;
//    Slider Threshold;
//    Slider Mix;
//    Slider outGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CatDistortionAudioProcessorEditor)
};
