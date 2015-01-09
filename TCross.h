//---------------------------------------------------------------------------

#ifndef TCrossH
#define TCrossH

#include "Comm.h"
#include "TLine.h"

//---------------------------------------------------------------------------
enum eLinePos {lpNONE, lpSTART, lpMIDDLE, lpEND };
enum eLineType {ltUNKNOW, ltMAIN, ltBRANCH};
enum eCrossType {Symmetry = 0,	//�����ԳƵ���
                  SimpleLeft,				//�󿪵�������
                  SimpleRight,				//�ҿ���������
				  Treble,			//�����ԳƵ���
                  DiamondCrossing};		//���ν���

//---------------------------------------------------------------------------
class CrossAngle {
public:
	double Angle;
    int FrogNumber;
};

//---------------------------------------------------------------------------
class CrossAngleList : public vector<CrossAngle> {
public:
	__fastcall CrossAngleList();
};

//---------------------------------------------------------------------------
class TCrossLine {
public:
	eLinePos Pos;
    eLineType Type;
    double Angle
private:
    TLine * ptr;
};

//---------------------------------------------------------------------------
class TCrosss {
public:
	double X, Y;
    double MinAngle, MaxAngle;
    int MinAngleA, MinAngleB, MaxAngleA, MaxAngleB;
    int FrogNumber, MainLineNumber;
    eSwitchType Type;
    vector<TCrossLine> Lines;
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
    void __fastcall UpdateAngle(void);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};

//---------------------------------------------------------------------------
class TCrosses : public vector<TCross> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
