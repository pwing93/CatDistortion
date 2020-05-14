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
    setSize (400, 300);
    
    addAndMakeVisible(&disChoice);
    disChoice.addItem("Hard Clip", 1);
    disChoice.addItem("Soft Clip", 2);
    disChoice.addItem("Half-Wave Rect", 3);
    disChoice.setSelectedId(1);
    disChoice.addListener(this);
    
    addAndMakeVisible(&Threshold);
    Threshold.setRange(0.0f, 1.0f, 0.001f);
    Threshold.addListener(this);
    
    addAndMakeVisible(&Mix);
    Mix.setRange(0.0f, 1.0f, 0.001f);
    Mix.addListener(this);
}

CatDistortionAudioProcessorEditor::~CatDistortionAudioProcessorEditor()
{
}

//==============================================================================
void CatDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void CatDistortionAudioProcessorEditor::resized()
{
    disChoice.setBounds(50, 50, 200, 50);
    Threshold.setBounds(50, 100, 200, 50);
    Mix.setBounds(50, 150, 200, 50);
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
