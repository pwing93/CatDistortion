
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CatDistortionAudioProcessorEditor::CatDistortionAudioProcessorEditor (CatDistortionAudioProcessor& p, AudioProcessorValueTreeState& state)
    : AudioProcessorEditor (&p), processor (p), params(state)
{
    addComboBox("type", "Type", typeBox, typeLabel, typeAttachment);
    addSlider("thresh", "Threshold", threshSlider, threshLabel, threshAttachment);
    addSlider("mix", "Mix", mixSlider, mixLabel, mixAttachment);
    addSlider("in", "Input Gain", inSlider, inLabel, inAttachment);
    addSlider("out", "Output Gain", outSlider, outLabel, outAttachment);
    
    setSize(610, 380);
//
//    addAndMakeVisible(&disChoice);
//    disChoice.addItem("Hard Clip", 1);
//    disChoice.addItem("Soft Clip", 2);
//    disChoice.addItem("Half-Wave Rect", 3);
//    disChoice.setSelectedId(processor.menuChoice);
//    disChoice.addListener(this);
//
//    addAndMakeVisible(&inGain);
//    inGain.setSliderStyle(Slider::Rotary);
//    inGain.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
//    inGain.setTextValueSuffix(" Input Gain");
//    inGain.setRange(0.0f, 3.0f, 0.01f);
//    inGain.setValue(processor.gain);
//    inGain.addListener(this);
//
//    addAndMakeVisible(&Threshold);
//    Threshold.setSliderStyle(Slider::Rotary);
//    Threshold.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
//    Threshold.setTextValueSuffix(" Threshold");
//    Threshold.setRange(0.0f, 0.25f, 0.01f);
//    Threshold.setValue(processor.thresh);
//    Threshold.addListener(this);
//
//    addAndMakeVisible(&Mix);
//    Mix.setSliderStyle(Slider::Rotary);
//    Mix.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
//    Mix.setTextValueSuffix(" Wet/Dry Mix");
//    Mix.setRange(0.0f, 1.0f, 0.01f);
//    Mix.setValue(processor.mix);
//    Mix.addListener(this);
//
//    addAndMakeVisible(&outGain);
//    outGain.setSliderStyle(Slider::Rotary);
//    outGain.setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
//    outGain.setTextValueSuffix(" Make-Up Gain");
//    outGain.setRange(0.0f, 3.0f, 0.01f);
//    outGain.setValue(processor.makeUp);
//    outGain.addListener(this);
//
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
    typeBox.setBounds(205, 10, 200, 50);
    inSlider.setBounds(10, 60, 140, 140);
    threshSlider.setBounds(10, 220, 140, 140);
    mixSlider.setBounds(460, 60, 140, 140);
    outSlider.setBounds(460, 220, 140, 140);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//void CatDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
//{
//    processor.menuChoice = comboBoxThatHasChanged->getSelectedId();
//}
//
//void CatDistortionAudioProcessorEditor::sliderValueChanged(Slider* sliderThatHasChanged)
//{
//    if (&inGain == sliderThatHasChanged)
//    {
//        processor.gain = sliderThatHasChanged->getValue();
//    }
//
//    if (&outGain == sliderThatHasChanged)
//    {
//        processor.makeUp = sliderThatHasChanged->getValue();
//    }
//
//    if (&Mix == sliderThatHasChanged)
//    {
//        processor.mix = sliderThatHasChanged->getValue();
//    }
//
//    if (&Threshold == sliderThatHasChanged)
//    {
//        processor.thresh = sliderThatHasChanged->getValue();
//    }
//}
