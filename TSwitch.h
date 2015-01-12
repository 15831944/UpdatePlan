//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include <system.hpp>
#include <vector.h>
#include <deque.h>
#include <Graphics.hpp>
#include "TSerialNumber.h"
#include "TMeasurement.h"

//---------------------------------------------------------------------------

//enum eConnectWay {Straight = 0, Side};
enum eSwitchHandType {shtSTRAIGHT,	//ֱ��
                      shtSIDE,		//����
                      shtLEFT,		//��
                      shtRIGHT,		//��
                      shtLEFTBACKWARD,	//�������ν���ʹ�ã�
                      shtRIGHTBACKWARD};	//�ҷ���
enum eSwitchDirection {sdBACKWARD, sdFORWARD};     //���� ˳��
enum eSwitchType {Symmetry = 0,	//�����ԳƵ���
                  SimpleLeft,				//�󿪵�������
                  SimpleRight,				//�ҿ���������
				  Treble,			//�����ԳƵ���
                  DiamondCrossing};		//���ν���
enum eSwitch {sNone, sSimpleLeft6, sSimpleLeft7, sSimpleLeft9, sSymmetry6, sSymmetry65, sSymmetry9, sTreble7, sDiamondCrossing,
              sSimpleRight6, sSimpleRight7, sSimpleRight9};

#define TSwitchHandNumber unsigned short int

class TSwitchHandNumbers : public vector<TSwitchHandNumber> {

};

class TSwitch : public TElementSerialNumber
{
private:
	float Fa, Fb;
	float FLength;
	float FAngle;
	float FRadii;

	float FBegin, FEnd;
	float FPosition;
	int FDirection;
	WideString FModel;
	float FFrogNumber;
	float FH;
	float FGrade;

	bool Init;

    float __fastcall GetInPos(void);
    float __fastcall GetOutPos(void);

    void __fastcall SetPosition(const float Value);
    void __fastcall SetBeginEnd(void);
	void __fastcall SetDirection(const int Value);

public:
	unsigned short Number;  //���
	eSwitch ModelIndex;
	eSwitchType Type;
	float CircuitLength;        //���ڹ����·����
	float SortRailLength;       //��Ե�̹쳤��
//	int DirectionQuantity;
	float ioPosition, ioSortRailLength;
	float Angle;

    unsigned short UsedHandNumber;
    vector<eSwitchHandType> HandTypes;		//���մ������Ҵ洢����֧�����ʣ��������������ӵķ�������
	int DrawSide;		// ��ͼ���� 1������	-1�����ҡ� Ϊ�˼���0�������ļ���ʽ�������������
//	eHandType ConnectWay;    //  ����
//	bool Symmetry;		//�Ƿ�Ϊ�ԳƵ���
//	bool DiamondCrossing;		//�Ƿ������ν�����ߡ�

	float CH;  	//Curve Height	�����ܸ�
	float SH;	// Switch Height	�����ܸ�

	__property float a = { read=Fa, write=Fa };
	__property float b = { read=Fb, write=Fb };
	__property float Length = { read=FLength, write=FLength };
	__property float Radii = { read=FRadii, write=FRadii };
	__property float FrogNumber = { read=FFrogNumber, write=FFrogNumber };

	__property float Position = { read=FPosition, write=SetPosition };
	__property float InPos = { read=GetInPos };
	__property float OutPos = { read=GetOutPos };
	__property int Direction = { read=FDirection, write=SetDirection };	// ���� 1����˳��0��������
	__property float Begin = { read=FBegin };
	__property float End = { read=FEnd };

   __property WideString Model = { read=FModel, write=FModel };

   __property float H = { read=FH, write=FH };
   __property float Grade = { read=FGrade, write=FGrade };

   __fastcall TSwitch();
	bool __fastcall Initialize(const TMeasurement Measurement);
	TSwitch & __fastcall operator = (const TSwitch & t);
	void __fastcall Save(const int Handle);
	void __fastcall Load(const int Handle);
    void __fastcall SetHandNumber(unsigned short HandNumber);
};

class ptrTSwitches : public vector<TSwitch *>
{

};

class TSwitches : public vector<TSwitch>
{
public:
	__fastcall TSwitches();
//	TItemCaption PositionCaption, SortRailLengthCaption;
	TSwitches & __fastcall operator = (const TSwitches & t);
	bool __fastcall VerifyInput(const WideString PositionText,
										 const WideString SwitchNumberText,
										 const WideString SortRailLengthText);
	bool __fastcall Initialize(const TMeasurement Measurement);
	void __fastcall Add(const WideString ModelName, const float Position);
	void __fastcall Save(const int Handle);
	void __fastcall Load(const int Handle);
	void __fastcall ResetIndex(void);
	TSwitch __fastcall Find(const WideString SerialNumber);
    ptrTSwitches __fastcall Find(const TSerialNumbers SerialNumbers);
	void __fastcall WriteListView(TListView * ListView);

	void __fastcall Draw(TCanvas *Canvas, const int PlanBase, const float Scale,
								const float BeginPos, const float EndPos, const int PlanHeight);
};

//---------------------------------------------------------------------------
class TSwitchList : public vector<TSwitch>
{
public:
   __fastcall TSwitchList();
//   TSwitchList & __fastcall operator = (const TSwitchList & List);
	TSwitch __fastcall Which(const WideString ModelName);
	TSwitch __fastcall Which(const unsigned short ModelIndex);
	unsigned short __fastcall Index(const WideString ModelName);
	WideString __fastcall Model(const unsigned short Index);
//    TSwitch __fastcall Model(const unsigned short Index);
private:
	TSwitch __fastcall New(const unsigned short ModelIndex, const WideString ModelName,
								  const float FrogNumber, const float a, const float b,
								  const float FH);

	TSwitch __fastcall New(const unsigned short ModelIndex, const WideString ModelName,
								  const float Angle, const float a, const float b,
								  const float CircuitLength,
								  const eSwitchType Type);
};

class TSwitchesList : public vector<TSwitches>
{

};

#endif


