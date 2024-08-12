/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AnalogRingModAudioProcessorEditor::AnalogRingModAudioProcessorEditor (AnalogRingModAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(frequencySlider);
    frequencySlider.setSliderStyle(juce::Slider::Rotary);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param      GUI
    freqAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMFREQ, frequencySlider));
    //Connect the freq slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree
    
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.setJustificationType(juce::Justification::centred);


    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setNumDecimalPlacesToDisplay(1);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMGAIN, gainSlider));

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);


    addAndMakeVisible(depthSlider);
    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param      GUI
    depthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMDEPTH, depthSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree
    
    addAndMakeVisible(depthLabel);
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(gateButton);
    gateButton.setButtonText("Gate");
    gateAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.apvts, JUCEPAMAMGATE, gateButton));
    
    //Call back func here
    gateButton.onStateChange = [this] {
        if (gateButton.getToggleState() == true) {
            DBG("button pressed");
            gateButton.setToggleState(true, juce::NotificationType::sendNotification);  //another call back func
        }
        else {
            DBG("gate off");
            gateButton.setToggleState(false, juce::NotificationType::sendNotification);
        }
    };
    gateButton.addListener(this);

    addAndMakeVisible(rDiodeSlider);
    rDiodeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    rDiodeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 20);
    rDiodeSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param           GUI
    rDiodeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMRESISTANCE, rDiodeSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree
    
    addAndMakeVisible(rDiodeLabel);
    rDiodeLabel.setText("Diode Resistance", juce::dontSendNotification);
    rDiodeLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(vOnSlider);
    vOnSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    vOnSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 20);
    vOnSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param           GUI
    vOnAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMTURNON, vOnSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree
    
    addAndMakeVisible(vOnLabel);
    vOnLabel.setText("Turn-On Voltage ", juce::dontSendNotification);
    vOnLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(vBiasSlider);
    vBiasSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    vBiasSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 20);
    vBiasSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param           GUI
    vBiasAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMBIASING, vBiasSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree

    addAndMakeVisible(vBiasLabel);
    vBiasLabel.setText("Biasing Voltage ", juce::dontSendNotification);
    vBiasLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(carrierSlider);
    carrierSlider.setSliderStyle(juce::Slider::Rotary);
    carrierSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    carrierSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState          Juce param           GUI
    carrierAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMCARRIER, carrierSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree

    addAndMakeVisible(carrierLabel);
    carrierLabel.setText("Carrier: 1-OFF  2-Sine  3-Square  4-Tri  5-Sawtooth", juce::dontSendNotification);
    carrierLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider.setNumDecimalPlacesToDisplay(1);
    //Reset it; Connect it with the Tree; use Slider Attachment to connect with      the TreeState       Juce param           GUI
    mixAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, JUCEPARAMMIX, mixSlider));
    //Connect the slider to this everytime when the slider is changed;
    //Call back func here also so also has listener; it changes the value in the tree

    addAndMakeVisible(mixLabel);
    mixLabel.setText("Blend", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);
}


AnalogRingModAudioProcessorEditor::~AnalogRingModAudioProcessorEditor()
{
    DBG("editor destructor");
    gateButton.removeListener(this);
    freqAttachment = nullptr;
    gainAttachment = nullptr;
    depthAttachment = nullptr;
    gateAttachment = nullptr;
    rDiodeAttachment = nullptr;
    vOnAttachment = nullptr;
    vBiasAttachment = nullptr;
    carrierAttachment = nullptr;
    mixAttachment = nullptr;
}

//==============================================================================
void AnalogRingModAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::orange);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Analog Ring Modulator", getLocalBounds(), juce::Justification::centredTop, 1);
}

void AnalogRingModAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto height = getHeight();
    auto width = getWidth();
    auto area = getLocalBounds();
    auto border = width * 0.05;
    auto labelWidth = width * 0.05;
    auto labelHeight = height * 0.05;

    area.removeFromLeft(border);
    area.removeFromRight(border);
    area.removeFromTop(height * 0.05);

    auto gateArea = area.removeFromTop(0.1 * height);
    gateButton.setBounds(gateArea);
    
    auto gainArea = area.removeFromRight(0.2 * width);
    gainLabel.setBounds(gainArea.removeFromBottom(labelHeight));
    gainSlider.setBounds(gainArea);

    auto freqCarrierArea = area.removeFromTop(0.3 * height);
    auto freqArea = freqCarrierArea.removeFromLeft(0.4 * width);
    auto carrierArea = freqCarrierArea;
    frequencyLabel.setBounds(freqArea.removeFromBottom(labelHeight));
    frequencySlider.setBounds(freqArea);
    carrierLabel.setBounds(carrierArea.removeFromBottom(labelHeight));
    carrierSlider.setBounds(carrierArea);

    auto mixDepthArea = area.removeFromTop(0.3 * height);
    auto mixArea = mixDepthArea.removeFromLeft(0.4 * width);
    auto depthArea = mixDepthArea;
    mixLabel.setBounds(mixArea.removeFromBottom(labelHeight));
    mixSlider.setBounds(mixArea);
    depthLabel.setBounds(depthArea.removeFromBottom(labelHeight));
    depthSlider.setBounds(depthArea);

    auto rDiodeArea = area.removeFromTop(0.1 * height);
    rDiodeLabel.setBounds(rDiodeArea.removeFromLeft(labelWidth));
    rDiodeSlider.setBounds(rDiodeArea);

    auto vOnArea = area.removeFromTop(0.1 * height);
    vOnLabel.setBounds(vOnArea.removeFromLeft(labelWidth));
    vOnSlider.setBounds(vOnArea);

    auto vBiasArea = area;
    vBiasLabel.setBounds(vBiasArea.removeFromLeft(labelWidth));
    vBiasSlider.setBounds(vBiasArea);
}

void AnalogRingModAudioProcessorEditor::buttonClicked(juce::Button* button) {
    //
}

