declare filename "RingModFinalCpp.dsp"; declare name "RingModFinalCpp"; import("stdfaust.lib");
import("basics.lib");

freq = hslider("Frequency",440,20,10000,1.0):si.smoo;

s = hslider("Carrier Signal",1,1,5,1);

//Assume the an analog audio system go from +-10v
//*0.1 to aboid clipping
Off = 0;
Sine = 0.1 * os.oscsin(freq);  
Square = 0.1 * os.lf_squarewave(freq);
Tri = 0.1 * os.lf_triangle(freq);
Saw = 0.1 * os.lf_saw(freq);

Vc = ((Off,Sine,Square,Tri,Saw):ba.selectn(5,s-1) ) * depth; //use the select and radio to select the carrier signal

Vin = _ ;   //input signal

depth = hslider("Depth",1,0,2,0.1):si.smoo;

vDiodeOn = hslider("Diode Turn-On Voltage",0.45,0,0.59,0.01):si.smoo;
vDiodeLin = hslider("Diode Biasing Voltage",0.7,0.6,0.8,0.01):si.smoo;

vb = 0.1 * vDiodeOn ;  //turn on voltage for diode
vL = 0.1 * vDiodeLin;   //forward biasing voltage for the diode
Rd = hslider("Diode Resistance",1,0.1,3,0.1):si.smoo;
h = 1/Rd;

expCurve(v) = h*((v -vb)^2)/(2*vL - 2*vb);
linCurve(v) = h* v - h*vL + expCurve(v);

//Find the Vout based on Vin
f_v1(v) = ba.if( v <= vb,0,f_v2);
f_v2(v) = ba.if( v <= vL, expCurve(v), f_v3);
f_v3(v) = linCurve(v);


// faust2juce just slider parameter Frequeency Gain Mix ...
//
diodeSet1 = _ <: ( f_v1( _ ) , ( _ * (-1) <:  f_v1( _ ) )) :> _ ; 


Wet =(Vc <: _,_) , (Vin * 0.5 <: _ , (-1)* _ ) :> diodeSet1 , (diodeSet1 * (-1)) :> *(1) ; 

gain = hslider("Gain",-10,-80,10,1) : ba.db2linear:si.smoo;

Mix = hslider("Mix",0.5,0,1.0,0.1):si.smoo;

gate = checkbox("Gate");

ringMod = _ <:(Vin*(1-Mix) + Wet*(Mix)) * (gain) *gate;

process = ringMod,ringMod :> _ <: _,_;



