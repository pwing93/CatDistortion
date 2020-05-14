/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CatDistortionAudioProcessorEditor::CatDistortionAudioProcessorEditor (CatDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(610, 380);
    
    addAndMakeVisible(&disChoice);
    disChoice.addItem("Hard Clip", 1);
    disChoice.addItem("Soft Clip", 2);
    disChoice.addItem("Half-Wave Rect", 3);
    disChoice.setSelectedId(1);
    disChoice.addListener(this);
    
    addAndMakeVisible(&inGain);
    inGain.setSliderStyle(Slider::Rotary);
    inGain.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
    inGain.setTextValueSuffix(" Input Gain");
    
    addAndMakeVisible(&Threshold);
    Threshold.setSliderStyle(Slider::Rotary);
    Threshold.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
    Threshold.setTextValueSuffix(" Threshold");
    Threshold.setRange(0.0f, 0.25f, 0.001f);
    Threshold.setValue(0.0f);
    Threshold.addListener(this);
    
    addAndMakeVisible(&Mix);
    Mix.setSliderStyle(Slider::Rotary);
    Mix.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
    Mix.setTextValueSuffix(" Wet/Dry Mix");
    Mix.setRange(0.0f, 1.0f, 0.001f);
    Mix.setValue(0.0f);
    Mix.addListener(this);
    
    addAndMakeVisible(&outGain);
    outGain.setSliderStyle(Slider::Rotary);
    outGain.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
    outGain.setTextValueSuffix(" Make-Up Gain");
}

CatDistortionAudioProcessorEditor::~CatDistortionAudioProcessorEditor()
{
}

//==============================================================================
void CatDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkred);
    Image cat = ImageCache::getFromMemory (BinaryData::catSmash_png, BinaryData::catSmash_pngSize);
    g.drawImageAt(cat, 151, 61);
    g.setColour (Colours::white);
    g.setFont (20.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void CatDistortionAudioProcessorEditor::resized()
{
    disChoice.setBounds(205, 10, 200, 50);
    inGain.setBounds(10, 60, 140, 140);
    Threshold.setBounds(10, 220, 140, 140);
    Mix.setBounds(460, 60, 140, 140);
    outGain.setBounds(460, 220, 140, 140);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void CatDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    processor.menuChoice = comboBoxThatHasChanged->getSelectedId();
}

void CatDistortionAudioProcessorEditor::sliderValueChanged(Slider* sliderThatHasChanged)
{
    if (&Mix == sliderThatHasChanged)
    {
        processor.mix = sliderThatHasChanged->getValue();
    }
    
    if (&Threshold == sliderThatHasChanged)
    {
        processor.thresh = sliderThatHasChanged->getValue();
    }
}
