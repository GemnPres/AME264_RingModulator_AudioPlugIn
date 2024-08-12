/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "faust/faustMinimalInlined1.h"  //use this as audio engine
// SP [P8]
// 2 Sets; 
//One set for JUCE
#define JUCEPARAMFREQ   "freq"
#define JUCEPARAMGAIN   "gain"
#define JUCEPAMAMGATE   "gate"
#define JUCEPARAMCARRIER    "carriersig"
#define JUCEPARAMDEPTH  "depth"
#define JUCEPARAMBIASING    "vbias"
#define JUCEPARAMRESISTANCE "rdiode"
#define JUCEPARAMTURNON "von"
#define JUCEPARAMMIX    "mix"

//One set for Faust
#define FAUSTPARAMFREQ  "/RingModFinalCpp/Frequency"
#define FAUSTPARAMGAIN  "/RingModFinalCpp/Gain"
#define FAUSTPARAMGATE  "/RingModFinalCpp/Gate"
#define FAUSTPARAMCARRIER   "/RingModFinalCpp/Carrier_Signal"
#define FAUSTPARAMDEPTH "/RingModFinalCpp/Depth"
#define FAUSTPARAMBIASING   "/RingModFinalCpp/Diode_Biasing_Voltage"
#define FAUSTPARAMRESISTANCE    "/RingModFinalCpp/Diode_Resistance"
#define FAUSTPARAMTURNON    "/RingModFinalCpp/Diode_Turn-On_Voltage"
#define FAUSTPARAMMIX   "/RingModFinalCpp/Mix"
//==============================================================================
/**
*/
class AnalogRingModAudioProcessor  : public juce::AudioProcessor
,      private juce::AudioProcessorValueTreeState::Listener // SP [P2]; inherit the valuetreestate listener
                                                            //listener has pure virtual member func so that can tell changes
                                                            //Have parameter changes
{
public:
    //==============================================================================
    AnalogRingModAudioProcessor();
    ~AnalogRingModAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //P3 - prototype and override parameterChanged function(processor header) (https://docs.juce.com/master/structAudioProcessorValueTreeState_1_1Listener.html)
    void parameterChanged(const juce::String& parameterID, float newValue) override;   // SP [P3]

    juce::AudioProcessorValueTreeState apvts;   // SP [P1]; ValueTree param called apvts
private:
    // SP [F2]
    //F2 - declare faust objects, MapUI*and dsp* (processor header)
    MapUI* fUI;
    dsp* fDSP;  //The 2 para in MinimalInlined1.h
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalogRingModAudioProcessor)
};
