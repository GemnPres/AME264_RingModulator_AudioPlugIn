/* ------------------------------------------------------------
name: "faustMinimalInlined"
faust2jucecpp demo project prepared by Steve Philbert & Ming-Lun Lee @2021
updated & designed for AME264/ECE476 Audio Software Design II at the University of Rochester
https://faustdoc.grame.fr/workshops/2020-04-10-faust-juce/
Code generated with Faust 2.23.4 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            do {
                if ((*it).second == zone) return (*it).first;
            }
            while (it++ != fPathZoneMap.end());
            return "";
        }
    
        static bool endsWith(std::string const& str, std::string const& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/

// BEGIN-FAUSTDSP

//Append after the template the Cpp exported from Faust-Source-Cpp
/* ------------------------------------------------------------
name: "RingModFinalCpp"
Code generated with Faust 2.30.7 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class mydspSIG0 {

private:

    int iRec3[2];

public:

    int getNumInputsmydspSIG0() {
        return 0;
    }
    int getNumOutputsmydspSIG0() {
        return 1;
    }
    int getInputRatemydspSIG0(int channel) {
        int rate;
        switch ((channel)) {
        default: {
            rate = -1;
            break;
        }
        }
        return rate;
    }
    int getOutputRatemydspSIG0(int channel) {
        int rate;
        switch ((channel)) {
        case 0: {
            rate = 0;
            break;
        }
        default: {
            rate = -1;
            break;
        }
        }
        return rate;
    }

    void instanceInitmydspSIG0(int sample_rate) {
        for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
            iRec3[l3] = 0;
        }
    }

    void fillmydspSIG0(int count, float* table) {
        for (int i = 0; (i < count); i = (i + 1)) {
            iRec3[0] = (iRec3[1] + 1);
            table[i] = std::sin((9.58738019e-05f * float((iRec3[0] + -1))));
            iRec3[1] = iRec3[0];
        }
    }

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];
static float mydsp_faustpower2_f(float value) {
    return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {

private:

    FAUSTFLOAT fCheckbox0;
    FAUSTFLOAT fHslider0;
    float fRec0[2];
    FAUSTFLOAT fHslider1;
    float fRec1[2];
    FAUSTFLOAT fHslider2;
    float fRec2[2];
    FAUSTFLOAT fHslider3;
    int fSampleRate;
    float fConst0;
    FAUSTFLOAT fHslider4;
    float fRec5[2];
    float fRec4[2];
    float fRec6[2];
    FAUSTFLOAT fHslider5;
    float fRec7[2];
    FAUSTFLOAT fHslider6;
    float fRec8[2];
    FAUSTFLOAT fHslider7;
    float fRec9[2];

public:

    void metadata(Meta* m) {
        m->declare("basics.lib/name", "Faust Basic Element Library");
        m->declare("basics.lib/version", "0.1");
        m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
        m->declare("filename", "RingModFinalCpp.dsp");
        m->declare("maths.lib/author", "GRAME");
        m->declare("maths.lib/copyright", "GRAME");
        m->declare("maths.lib/license", "LGPL with exception");
        m->declare("maths.lib/name", "Faust Math Library");
        m->declare("maths.lib/version", "2.3");
        m->declare("name", "RingModFinalCpp");
        m->declare("oscillators.lib/name", "Faust Oscillator Library");
        m->declare("oscillators.lib/version", "0.1");
        m->declare("platform.lib/name", "Generic Platform Library");
        m->declare("platform.lib/version", "0.1");
        m->declare("signals.lib/name", "Faust Signal Routing Library");
        m->declare("signals.lib/version", "0.0");
    }

    virtual int getNumInputs() {
        return 2;
    }
    virtual int getNumOutputs() {
        return 2;
    }
    virtual int getInputRate(int channel) {
        int rate;
        switch ((channel)) {
        case 0: {
            rate = 1;
            break;
        }
        case 1: {
            rate = 1;
            break;
        }
        default: {
            rate = -1;
            break;
        }
        }
        return rate;
    }
    virtual int getOutputRate(int channel) {
        int rate;
        switch ((channel)) {
        case 0: {
            rate = 1;
            break;
        }
        case 1: {
            rate = 1;
            break;
        }
        default: {
            rate = -1;
            break;
        }
        }
        return rate;
    }

    static void classInit(int sample_rate) {
        mydspSIG0* sig0 = newmydspSIG0();
        sig0->instanceInitmydspSIG0(sample_rate);
        sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
        deletemydspSIG0(sig0);
    }

    virtual void instanceConstants(int sample_rate) {
        fSampleRate = sample_rate;
        fConst0 = (1.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
    }

    virtual void instanceResetUserInterface() {
        fCheckbox0 = FAUSTFLOAT(0.0f);
        fHslider0 = FAUSTFLOAT(-10.0f);
        fHslider1 = FAUSTFLOAT(0.5f);
        fHslider2 = FAUSTFLOAT(1.0f);
        fHslider3 = FAUSTFLOAT(1.0f);
        fHslider4 = FAUSTFLOAT(440.0f);
        fHslider5 = FAUSTFLOAT(0.45000000000000001f);
        fHslider6 = FAUSTFLOAT(0.69999999999999996f);
        fHslider7 = FAUSTFLOAT(1.0f);
    }

    virtual void instanceClear() {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
            fRec0[l0] = 0.0f;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0f;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
            fRec2[l2] = 0.0f;
        }
        for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
            fRec5[l4] = 0.0f;
        }
        for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
            fRec4[l5] = 0.0f;
        }
        for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
            fRec6[l6] = 0.0f;
        }
        for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
            fRec7[l7] = 0.0f;
        }
        for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
            fRec8[l8] = 0.0f;
        }
        for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
            fRec9[l9] = 0.0f;
        }
    }

    virtual void init(int sample_rate) {
        classInit(sample_rate);
        instanceInit(sample_rate);
    }
    virtual void instanceInit(int sample_rate) {
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    virtual mydsp* clone() {
        return new mydsp();
    }

    virtual int getSampleRate() {
        return fSampleRate;
    }

    virtual void buildUserInterface(UI* ui_interface) {
        ui_interface->openVerticalBox("RingModFinalCpp");
        ui_interface->addHorizontalSlider("Carrier Signal", &fHslider3, 1.0f, 1.0f, 5.0f, 1.0f);
        ui_interface->addHorizontalSlider("Depth", &fHslider2, 1.0f, 0.0f, 2.0f, 0.100000001f);
        ui_interface->addHorizontalSlider("Diode Biasing Voltage", &fHslider6, 0.699999988f, 0.600000024f, 0.800000012f, 0.00999999978f);
        ui_interface->addHorizontalSlider("Diode Resistance", &fHslider7, 1.0f, 0.100000001f, 3.0f, 0.100000001f);
        ui_interface->addHorizontalSlider("Diode Turn-On Voltage", &fHslider5, 0.449999988f, 0.0f, 0.589999974f, 0.00999999978f);
        ui_interface->addHorizontalSlider("Frequency", &fHslider4, 440.0f, 20.0f, 10000.0f, 1.0f);
        ui_interface->addHorizontalSlider("Gain", &fHslider0, -10.0f, -80.0f, 10.0f, 1.0f);
        ui_interface->addCheckButton("Gate", &fCheckbox0);
        ui_interface->addHorizontalSlider("Mix", &fHslider1, 0.5f, 0.0f, 1.0f, 0.100000001f);
        ui_interface->closeBox();
    }

    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
        FAUSTFLOAT* input0 = inputs[0];
        FAUSTFLOAT* input1 = inputs[1];
        FAUSTFLOAT* output0 = outputs[0];
        FAUSTFLOAT* output1 = outputs[1];
        float fSlow0 = float(fCheckbox0);
        float fSlow1 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fHslider0))));
        float fSlow2 = (0.00100000005f * float(fHslider1));
        float fSlow3 = (0.00100000005f * float(fHslider2));
        float fSlow4 = (float(fHslider3) + -1.0f);
        int iSlow5 = (fSlow4 >= 3.0f);
        int iSlow6 = (fSlow4 >= 2.0f);
        int iSlow7 = (fSlow4 >= 1.0f);
        float fSlow8 = (0.00100000005f * float(fHslider4));
        int iSlow9 = (fSlow4 >= 4.0f);
        float fSlow10 = (0.00100000005f * float(fHslider5));
        float fSlow11 = (0.00100000005f * float(fHslider6));
        float fSlow12 = (0.00100000005f * float(fHslider7));
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
            float fTemp0 = float(input0[i]);
            fRec1[0] = (fSlow2 + (0.999000013f * fRec1[1]));
            float fTemp1 = (1.0f - fRec1[0]);
            fRec2[0] = (fSlow3 + (0.999000013f * fRec2[1]));
            fRec5[0] = (fSlow8 + (0.999000013f * fRec5[1]));
            float fTemp2 = (fConst0 * fRec5[0]);
            float fTemp3 = (fRec4[1] + fTemp2);
            fRec4[0] = (fTemp3 - std::floor(fTemp3));
            float fTemp4 = (fTemp2 + fRec6[1]);
            fRec6[0] = (fTemp4 - std::floor(fTemp4));
            float fTemp5 = ((2.0f * fRec6[0]) + -1.0f);
            float fTemp6 = (fRec2[0] * (iSlow5 ? (iSlow9 ? (0.100000001f * fTemp5) : (0.100000001f * ((2.0f * (1.0f - std::fabs(fTemp5))) + -1.0f))) : (iSlow6 ? (0.100000001f * ((2.0f * float((fRec6[0] <= 0.5f))) + -1.0f)) : (iSlow7 ? (0.100000001f * ftbl0mydspSIG0[int((65536.0f * fRec4[0]))]) : 0.0f))));
            float fTemp7 = (0.5f * fTemp0);
            float fTemp8 = (fTemp6 + fTemp7);
            fRec7[0] = (fSlow10 + (0.999000013f * fRec7[1]));
            float fTemp9 = (0.100000001f * fRec7[0]);
            fRec8[0] = (fSlow11 + (0.999000013f * fRec8[1]));
            float fTemp10 = (0.100000001f * fRec8[0]);
            float fTemp11 = mydsp_faustpower2_f((fTemp8 - fTemp9));
            float fTemp12 = (0.0f - (0.200000003f * (fRec7[0] - fRec8[0])));
            fRec9[0] = (fSlow12 + (0.999000013f * fRec9[1]));
            float fTemp13 = (fRec9[0] * fTemp12);
            float fTemp14 = (0.0f - fTemp8);
            float fTemp15 = (fTemp9 + fTemp6);
            float fTemp16 = mydsp_faustpower2_f((0.0f - (fTemp7 + fTemp15)));
            float fTemp17 = (fTemp6 - fTemp7);
            float fTemp18 = mydsp_faustpower2_f((fTemp6 - (fTemp9 + fTemp7)));
            float fTemp19 = (0.0f - fTemp17);
            float fTemp20 = mydsp_faustpower2_f((fTemp7 - fTemp15));
            float fTemp21 = float(input1[i]);
            float fTemp22 = (0.5f * fTemp21);
            float fTemp23 = (fTemp6 + fTemp22);
            float fTemp24 = mydsp_faustpower2_f((fTemp23 - fTemp9));
            float fTemp25 = (0.0f - fTemp23);
            float fTemp26 = mydsp_faustpower2_f((0.0f - (fTemp15 + fTemp22)));
            float fTemp27 = (fTemp6 - fTemp22);
            float fTemp28 = mydsp_faustpower2_f((fTemp6 - (fTemp9 + fTemp22)));
            float fTemp29 = (0.0f - fTemp27);
            float fTemp30 = mydsp_faustpower2_f((fTemp22 - fTemp15));
            float fTemp31 = (fSlow0 * (fRec0[0] * (((fTemp0 * fTemp1) + (fRec1[0] * ((((fTemp8 <= fTemp9) ? 0.0f : ((fTemp8 <= fTemp10) ? (fTemp11 / fTemp13) : (((fTemp8 - fTemp10) + (fTemp11 / fTemp12)) / fRec9[0]))) + ((fTemp14 <= fTemp9) ? 0.0f : ((fTemp14 <= fTemp10) ? (fTemp16 / fTemp13) : (((fTemp14 - fTemp10) + (fTemp16 / fTemp12)) / fRec9[0])))) - (((fTemp17 <= fTemp9) ? 0.0f : ((fTemp17 <= fTemp10) ? (fTemp18 / fTemp13) : (((fTemp17 - fTemp10) + (fTemp18 / fTemp12)) / fRec9[0]))) + ((fTemp19 <= fTemp9) ? 0.0f : ((fTemp19 <= fTemp10) ? (fTemp20 / fTemp13) : (((fTemp19 - fTemp10) + (fTemp20 / fTemp12)) / fRec9[0]))))))) + ((fTemp21 * fTemp1) + (fRec1[0] * ((((fTemp23 <= fTemp9) ? 0.0f : ((fTemp23 <= fTemp10) ? (fTemp24 / fTemp13) : (((fTemp23 - fTemp10) + (fTemp24 / fTemp12)) / fRec9[0]))) + ((fTemp25 <= fTemp9) ? 0.0f : ((fTemp25 <= fTemp10) ? (fTemp26 / fTemp13) : (((fTemp25 - fTemp10) + (fTemp26 / fTemp12)) / fRec9[0])))) - (((fTemp27 <= fTemp9) ? 0.0f : ((fTemp27 <= fTemp10) ? (fTemp28 / fTemp13) : (((fTemp27 - fTemp10) + (fTemp28 / fTemp12)) / fRec9[0]))) + ((fTemp29 <= fTemp9) ? 0.0f : ((fTemp29 <= fTemp10) ? (fTemp30 / fTemp13) : (((fTemp29 - fTemp10) + (fTemp30 / fTemp12)) / fRec9[0]))))))))));
            output0[i] = FAUSTFLOAT(fTemp31);
            output1[i] = FAUSTFLOAT(fTemp31);
            fRec0[1] = fRec0[0];
            fRec1[1] = fRec1[0];
            fRec2[1] = fRec2[0];
            fRec5[1] = fRec5[0];
            fRec4[1] = fRec4[0];
            fRec6[1] = fRec6[0];
            fRec7[1] = fRec7[0];
            fRec8[1] = fRec8[0];
            fRec9[1] = fRec9[0];
        }
    }

};

#endif

