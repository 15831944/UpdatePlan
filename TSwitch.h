//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include "Comm.h"
#include "TLine.h"

//---------------------------------------------------------------------------
enum eLinePos {lpNONE, lpSTART, lpMIDDLE, lpEND };
enum eLineType {ltUNKNOW, ltMAIN, ltBRANCH};
enum eSwitchType {Symmetry = 0,	//单开对称道岔
                  SimpleLeft,				//左开单开道岔
                  SimpleRight,				//右开单开道岔
				  Treble,			//三开对称道岔
                  DiamondCrossing};		//菱形交叉

//---------------------------------------------------------------------------
class SwitchAngle {
public:
	double Angle;
    int FrogNumber;
};

//---------------------------------------------------------------------------
class SwitchAngleList : public vector<SwitchAngle> {
public:
	__fastcall SwitchAngleList();
};

//---------------------------------------------------------------------------
class TSwitchLine {
public:
	eLinePos Pos;
    eLineType Type;
    TLine * ptr;
};

//---------------------------------------------------------------------------
class TSwitch {
public:
	double X, Y;
    double MinAngle, MaxAngle;
    int MinAngleA, MinAngleB, MaxAngleA, MaxAngleB;
    int FrogNumber, MainLineNumber;
    eSwitchType Type;
    vector<TSwitchLine> Lines;
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
    void __fastcall UpdateAngle(void);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};

//---------------------------------------------------------------------------
class TSwitches : public vector<TSwitch> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
