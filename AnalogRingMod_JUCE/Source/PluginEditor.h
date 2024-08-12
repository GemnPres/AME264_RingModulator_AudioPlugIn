/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AnalogRingModAudioProcessorEditor  : public juce::AudioProcessorEditor , 
    private juce::Button::Listener
{
public:
    AnalogRingModAudioProcessorEditor (AnalogRingModAudioProcessor&);
    ~AnalogRingModAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AnalogRingModAudioProcessor& audioProcessor;

    juce::Slider frequencySlider;
    juce::Label frequencyLabel;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    //juce::TextButton gateButton;
    juce::Slider depthSlider;
    juce::Label depthLabel;
    juce::Slider rDiodeSlider;
    juce::Label rDiodeLabel;
    juce::Slider vOnSlider;
    juce::Label vOnLabel;
    juce::Slider vBiasSlider;
    juce::Label vBiasLabel;
    juce::Slider carrierSlider;
    juce::Label carrierLabel;
    juce::Slider mixSlider;
    juce::Label mixLabel;
    juce::ToggleButton gateButton;  //checkbox button

    //Connect audio parameters to the ValueTree; attachment; it has a listener
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> gateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rDiodeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vOnAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vBiasAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> carrierAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalogRingModAudioProcessorEditor)
};