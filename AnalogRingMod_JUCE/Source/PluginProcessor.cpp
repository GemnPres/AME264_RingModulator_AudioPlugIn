/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AnalogRingModAudioProcessor::AnalogRingModAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),

//Add 9 parameters; Create a Tree. We have ValueTreeState, so use it. It contains the value tree. Initialize objects
//, to separate the AudioProcessor and ValueTree
apvts(*this, nullptr, juce::Identifier("RingMod"), {
    //If int AudioParameterInt...;
    //These shows up in GUI
    std::make_unique<juce::AudioParameterFloat>(
                                                JUCEPARAMFREQ,            // parameterID ; from Processor.h
                                                "freq",            // parameter name
                                                juce::NormalisableRange<float>(20, 10000, 1, 0.2987),  // min, max, interval, skew; skew factor (0-1), if 0.5 not skewing; if 0.2987, middle is 0.2987 so get a psuedo log scale
                                                440),               // default value

    std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMGAIN,            // parameterID
                                                 "gain",            // parameter name
                                                 -80.0,              // minimum value
                                                 10.0,              // maximum value
                                                 -10.0),              // default value
    
    std::make_unique<juce::AudioParameterBool>(
                                                JUCEPAMAMGATE,            // parameterID
                                                "gate",            // parameter name
                                                false),              // defauly value

    std::make_unique<juce::AudioParameterInt>(
                                                 JUCEPARAMCARRIER,            // parameterID
                                                 "carriersig",            // parameter name
                                                 1,              // minimum value
                                                 5,              // maximum value
                                                 1),              // default value

    std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMDEPTH,            // parameterID
                                                 "depth",            // parameter name
                                                 0.0,              // minimum value
                                                 2.0,              // maximum value
                                                 1.0),              // default value

     std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMBIASING,            // parameterID
                                                 "vbias",            // parameter name
                                                 0.60,              // minimum value
                                                 0.80,              // maximum value
                                                 0.70),              // default value

     std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMRESISTANCE,            // parameterID
                                                 "rdiode",            // parameter name
                                                 0.1,              // minimum value
                                                 3.0,              // maximum value
                                                 1.0),              // default value

    std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMTURNON,            // parameterID
                                                 "von",            // parameter name
                                                 0.00,              // minimum value
                                                 0.45,              // maximum value
                                                 0.59),              // default value

     std::make_unique<juce::AudioParameterFloat>(
                                                 JUCEPARAMMIX,            // parameterID
                                                 "mix",            // parameter name
                                                 0.0,              // minimum value
                                                 1.0,              // maximum value
                                                 0.5)            // default value

})

#endif
{
    DBG("processor constructor");

    //add listeners in the constructor
    apvts.addParameterListener(JUCEPARAMFREQ, this);    //SP [P5]
    apvts.addParameterListener(JUCEPARAMGAIN, this);
    apvts.addParameterListener(JUCEPAMAMGATE, this);
    apvts.addParameterListener(JUCEPARAMCARRIER, this);
    apvts.addParameterListener(JUCEPARAMDEPTH, this);
    apvts.addParameterListener(JUCEPARAMRESISTANCE, this);
    apvts.addParameterListener(JUCEPARAMTURNON, this);
    apvts.addParameterListener(JUCEPARAMBIASING, this);
    apvts.addParameterListener(JUCEPARAMMIX, this);
}
AnalogRingModAudioProcessor::~AnalogRingModAudioProcessor()
{   
    //F4 - delete faust objects(destructor)
    //Destructors
    DBG("processor destructor");

    // SP [4]
    delete fDSP;
    delete fUI;

    apvts.removeParameterListener(JUCEPARAMFREQ, this);    //SP [P6]
    apvts.removeParameterListener(JUCEPARAMGAIN, this);
    apvts.removeParameterListener(JUCEPAMAMGATE, this);
    apvts.removeParameterListener(JUCEPARAMCARRIER, this);
    apvts.removeParameterListener(JUCEPARAMDEPTH, this);
    apvts.removeParameterListener(JUCEPARAMRESISTANCE, this);
    apvts.removeParameterListener(JUCEPARAMTURNON, this);
    apvts.removeParameterListener(JUCEPARAMBIASING, this);
    apvts.removeParameterListener(JUCEPARAMMIX, this);

}

//==============================================================================
const juce::String AnalogRingModAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AnalogRingModAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AnalogRingModAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AnalogRingModAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AnalogRingModAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AnalogRingModAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AnalogRingModAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AnalogRingModAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AnalogRingModAudioProcessor::getProgramName (int index)
{
    return {};
}

void AnalogRingModAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AnalogRingModAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    //we have an audio engine MinimalInlined1.h
    DBG("prepareToPlay");

    // SP [F3]
    fDSP = new mydsp();
    fDSP->init(sampleRate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);

    // for reference to get faust parameter addresses
    //print out Faust para that is from the README FILE
    DBG("faust parameters: " << fUI->getParamsCount());
    for (auto i = 0; i < fUI->getParamsCount(); ++i) {
        DBG(i << ": " << fUI->getParamAddress(i));
    }
}

void AnalogRingModAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AnalogRingModAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void AnalogRingModAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // SP [5]
    //F5 - compute faust algorithm(processBlock)
    juce::ScopedNoDenormals noDenormals;

    auto audioArray = buffer.getArrayOfWritePointers();
    fDSP->compute(buffer.getNumSamples(), audioArray, audioArray);  //2 in; 2 out
    //fDSP->compute(buffer.getNumSamples(), NULL, audioArray);
    // call the compute func; 
    // pass the buffer to MinimalInlined1.h to compute
}

//==============================================================================
bool AnalogRingModAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//generic editor
juce::AudioProcessorEditor* AnalogRingModAudioProcessor::createEditor()
{
    return new AnalogRingModAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void AnalogRingModAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    //save param to XML data struct
    DBG("getStateInformation");         // SP [P9]
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void AnalogRingModAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    /*DBG("setStateInformation");         // SP [10]
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName(apvts.state.getType())) {
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }*/
}

//Body part; change the parameter
//If have generic GUI, change para, it goes to MinimalInlined.h and call the func here to process(processBlock did nothing)
//It's a CallBack Func. We have a ValueTreeState that includes a listener, that listener listens to any change of all these param
//Use parameter ID to check each one
//2 pair param (JUCE - FAUST) so change in ValueTreeState juce param can also change that in Faust audio engine (MinimumInline.h)
void AnalogRingModAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue) {       // SP [F6]  [P7]
    if (parameterID == JUCEPARAMFREQ) {
        
        fUI->setParamValue(FAUSTPARAMFREQ, newValue);   //Link juce param with Faust param and pass the new val
        DBG("freq: " << newValue << " "<<fUI->getParamValue(FAUSTPARAMFREQ));   //In DBG get prepocessed value and post processed value to test 
        //fUI->getParamValue(FAUSTPARAMFREQ);                                                //If freq slider change, change val in Faust audio engine also 
    }
    else if (parameterID == JUCEPARAMGAIN) {
        DBG("gain: " << newValue);
        fUI->setParamValue(FAUSTPARAMGAIN, newValue);
    }
    else if (parameterID == JUCEPAMAMGATE) {
        DBG("gate: " << newValue);
        fUI->setParamValue(FAUSTPARAMGATE, newValue);
    }
    else if (parameterID == JUCEPARAMDEPTH) {
        DBG("depth: " << newValue);
        fUI->setParamValue(FAUSTPARAMDEPTH, newValue);
    }
    else if (parameterID == JUCEPARAMBIASING) {
        DBG("vbias: " << newValue);
        fUI->setParamValue(FAUSTPARAMBIASING, newValue);
    }
    else if (parameterID == JUCEPARAMRESISTANCE) {
        DBG("rdiode: " << newValue);
        fUI->setParamValue(FAUSTPARAMRESISTANCE, newValue);
    }
    else if (parameterID == JUCEPARAMTURNON) {
        DBG("von: " << newValue);
        fUI->setParamValue(FAUSTPARAMTURNON, newValue);
    }
    else if (parameterID == JUCEPARAMMIX) {
        DBG("mix: " << newValue);
        fUI->setParamValue(FAUSTPARAMMIX, newValue);
    }
    else if (parameterID == JUCEPARAMCARRIER) {
        DBG("mix: " << newValue);
        fUI->setParamValue(FAUSTPARAMCARRIER, newValue);
    }
    else {
        // unlisted / unknown parameter(s) / catch-all; in case sth wrong
        DBG("parameterChanged: " << parameterID << " " << newValue);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AnalogRingModAudioProcessor();
}
