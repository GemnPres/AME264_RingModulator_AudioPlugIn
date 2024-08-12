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
