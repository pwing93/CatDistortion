
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

//==============================================================================
CatDistortionAudioProcessor::CatDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
    ,
    state(*this, nullptr, Identifier("params"),
          
{
    std::make_unique<AudioParameterFloat> ("type", "Type", NormalisableRange<float> (1, 3, 1), 1),
    
    std::make_unique<AudioParameterFloat> ("thresh", "Threshold", NormalisableRange<float> (0.0f, 0.25F, 0.01f), 0.0f),
    
    std::make_unique<AudioParameterFloat> ("mix", "Mix", NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.0f),
    
    std::make_unique<AudioParameterFloat> ("in", "Input Gain", NormalisableRange<float> (0.0f, 3.0f, 0.01f), 1.0f),
    
    std::make_unique<AudioParameterFloat> ("out", "Output Gain", NormalisableRange<float> (0.0f, 3.0f, 0.01f), 1.0f)
    
    
//    int menuChoice = 1;
//    float thresh = 0.0f;
//    float mix = 0.0f;
//    float gain = 1.0f;
//    float makeUp = 1.0f;
}
)
#endif
{
}

CatDistortionAudioProcessor::~CatDistortionAudioProcessor()
{
}

//==============================================================================
const String CatDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CatDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CatDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CatDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CatDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CatDistortionAudioProcessor::getNumPrograms()
{
    return 1;
}

int CatDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CatDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String CatDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void CatDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CatDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    threshParam = state.getRawParameterValue("thresh");
    mixParam = state.getRawParameterValue("mix");
    typeParam = state.getRawParameterValue("type");
    inParam = state.getRawParameterValue("in");
    outParam = state.getRawParameterValue("out");
    
}

void CatDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CatDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CatDistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            //Input Gain Stage
            channelData[i] = channelData[i] * *inParam;
            
            auto input = channelData[i];
            auto cleanOut = channelData[i];
            
            //Hard Clipping Algorithm
            if (*typeParam == 1)
            {
                if (input > *threshParam)
                {
                    input = *threshParam;
                }
                
                else if (input < -*threshParam)
                {
                    input = -*threshParam;
                }
                
                else
                {
                    input = input;
                }
            }
            
            //Soft Clipping Algorithm
            if (*typeParam == 2)
            {
                if (input > *threshParam)
                {
                    input = 1.0f - expf(-input);
                }
                
                else
                {
                    input = -1.0f + expf(input);
                }
            }
            
            //Half-Wave Rectifier Algorithm
            if (*typeParam == 3)
            {
                if (input > *threshParam)
                {
                    input = input;
                }
                
                else
                {
                    input = 0;
                }
            }

            //Formula for taking "Wet" affected Input signal and mixing back with "Dry" unaffected signal
            channelData[i] = ((1 - *mixParam) * cleanOut) + (*mixParam * input);
            
            //Output Make-up Gain stage
            channelData[i] = channelData[i] * *outParam;
        }
    }
}

//==============================================================================
bool CatDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CatDistortionAudioProcessor::createEditor()
{
    return new CatDistortionAudioProcessorEditor (*this, state);
}

//==============================================================================
void CatDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto stateTree = state.copyState();
    std::unique_ptr<XmlElement> xml (stateTree.createXml());
    copyXmlToBinary (*xml, destData);
}

void CatDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName(state.state.getType()))
    {
        state.replaceState(ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CatDistortionAudioProcessor();
}
