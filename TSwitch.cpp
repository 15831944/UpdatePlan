//---------------------------------------------------------------------------


#pragma hdrstop

#include "TSwitch.h"
#include "CoFunction.h"

#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern TSwitchList SwitchList;

__fastcall TSwitch::TSwitch()
{
   	Type = Symmetry;
	FH = 0;
	SH = 24;
	FPosition = 0;
	FDirection = 0;
	FBegin = 0;
	FEnd = 0;
	Fa = 0;
	Fb = 0;
	DrawSide = 0;
	CircuitLength = 0;
    FAngle = 0;
    FFrogNumber = 0;
    Init = false;
	FRadii = 0;
}

//---------------------------------------------------------------------------
TSwitch & __fastcall TSwitch::operator = (const TSwitch & t)
{
	Fa = t.Fa;
	Fb = t.Fb;
	FAngle = t.FAngle;
	FRadii = t.FRadii;
	FLength = t.FLength;
	CircuitLength = t.CircuitLength;
	FModel = t.FModel;
	FFrogNumber = t.FFrogNumber;
	Angle = t.Angle;
	FH = t.FH;
	CH = t.CH;
	SH = t.SH;
	FPosition = t.FPosition;
	ioPosition = t.ioPosition;
	ioSortRailLength = t.ioSortRailLength;
	SerialNumber = t.SerialNumber;
	Name = t.Name;
	FDirection = t.FDirection;
	Type = t.Type;
	Init = t.Init;
	Number = t.Number;
	FBegin = t.FBegin;
	FEnd = t.FEnd;
	ModelIndex = t.ModelIndex;
    HandTypes = t.HandTypes;
    UsedHandNumber = t.UsedHandNumber;
    DrawSide = t.DrawSide;
	return *this;
};

//---------------------------------------------------------------------------
bool __fastcall TSwitch::Initialize(const TMeasurement Measurement)
{
   TSwitch Switch;

	FPosition = ioPosition * Measurement.LengthRate;
	SortRailLength = ioSortRailLength * Measurement.LengthRate;
	Switch = SwitchList.Which(Model);
	Fa = Switch.Fa;
	Fb = Switch.Fb;
	if (Switch.Type == DiamondCrossing)
		SH = 0.5 * Switch.SH;
	else
		SH = (Direction == sdFORWARD) ? 0.5 * Switch.SH : Switch.SH;
	FH = SH + CH;
	Angle = Switch.Angle;    //�����ԳƵ������������ĽǶȲ�ͬ�������ԳƵ����ʵ��ת��ӦΪ50%
	Type = Switch.Type;
//	FH = Switch.FH;
	CircuitLength = Switch.CircuitLength;

	FLength = Fa + Fb;
	FGrade = FH / FLength;

	if (Direction == sdBACKWARD) {
		FBegin = Position - Fa;
		FEnd = Position + Fb;
	} else {
		FBegin = Position - Fb;
		FEnd = Position + Fa;
	}

	//���õ����߰뾶
   Init = true;
   return Init;
};

//---------------------------------------------------------------------------
void __fastcall TSwitch::SetPosition(const float Value)
{
   FPosition = Value;
   SetBeginEnd();
};

//---------------------------------------------------------------------------
void __fastcall TSwitch::SetBeginEnd(void)
{
	if (Direction)
   {
      FBegin = Position - Fa;
      FEnd = Position + Fb;
   }
   else
   {
      FBegin = Position - Fb;
      FEnd = Position + Fa;
   }
};

//---------------------------------------------------------------------------
void __fastcall TSwitch::SetDirection(const int Value)
{
   FDirection = Value;
}

//---------------------------------------------------------------------------
TSwitches & __fastcall TSwitches::operator = (const TSwitches & t)
{
   unsigned short i, q;

   clear();
   q = t.size();
   for (i = 0; i < q; i++)
      push_back(t[i]);

	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TSwitch::SetHandNumber(unsigned short HandNumber) {
    UsedHandNumber = HandNumber;
    eSwitchHandType SwitchHandType = HandTypes[HandNumber];
   	switch (SwitchHandType) {
       	case shtSTRAIGHT:
       		CH = 0;
            break;
   	    case shtSIDE:
       	    CH = Angle * 8;
       		break;
        case shtLEFT:
   	    case shtRIGHT:
			CH = 0.5 * Angle * 8;
        	break;
		default:
   	    ;
    }
    DrawSide = 1 - HandNumber * 2;     //HandNumber == 0ʱ��ӦΪ�ң��� 1�� HandNumber == 1ʱ��ӦΪ�󣬼� -1
    return;
}

//---------------------------------------------------------------------------
__fastcall TSwitches::TSwitches()
{
//	PositionCaption.SetCaption(uLength, L"λ��", "Position");
//	SortRailLengthCaption.SetCaption(uLength, L"��Ե�̹쳤", "Sort Rail Length");
}

bool __fastcall TSwitches::VerifyInput(const WideString PositionText,
									   const WideString SwitchNumberText,
									   const WideString SortRailLengthText)
{
	float f;
	TSwitchList List;
	if (!IsFloat(PositionText, f, L"����λ�ò���Ϊ������Ҳ���ܿհף�", 0)) return false;
	if (List.Index(SwitchNumberText) == 0) {
		MessageBox(NULL, L"�����ͺű������б��еı�ţ�", L"����", MB_OK);
		return false;
	}
	if (!IsFloat(SortRailLengthText, f, L"��Ե�̹쳤�Ȳ���Ϊ������Ҳ���ܿհף�", 0)) return false;
	return true;	
}

//---------------------------------------------------------------------------
bool __fastcall TSwitches::Initialize(const TMeasurement Measurement)
{
   unsigned short i, q;

   q = size();
   for(i = 0; i < q; i++)
		if (!at(i).Initialize(Measurement)) return false;

   return true;
};

//---------------------------------------------------------------------------
void __fastcall TSwitches::Add(const WideString ModelName, const float Position)
{
   TSwitch Switch;

   Switch.Model = ModelName;
   Switch.Position = Position;

   push_back(Switch);
}

//---------------------------------------------------------------------------
__fastcall TSwitchList::TSwitchList()
{
	// Set H of all switches is 24 in New function.
	// Other part of H will set in class TCurve.
   TSwitch Switch;

	Switch = New(sNone, L"Not Exist", 0, 0, 0, 0);
	push_back(Switch);                  // ModelIndex ��������Ķ�����Ӱ��0�������ļ���ȡ��

	Switch = New(sSymmetry6, L"6#�Գ�", 9.462222, 7.437, 9.994, 8.874, Symmetry);
	Switch.CircuitLength = 7.82;
	push_back(Switch);
	Switch = New(sSimpleLeft9, L"9#�󵥿�", 6.340278, 13.839, 15.009, 12.509, SimpleLeft);
	Switch.CircuitLength = 15.455;
	push_back(Switch);
	Switch = New(sSimpleRight9, L"9#�ҵ���", 6.340278, 13.839, 15.009, 12.509, SimpleRight);
	Switch.CircuitLength = 15.455;
	push_back(Switch);
	Switch = New(sTreble7, L"7#����", 8.1300000, 11.465, 12.658, 8.5, Treble);
	Switch.CircuitLength = 7.748;
	push_back(Switch);
	Switch = New(sDiamondCrossing, L"���ν���", 0, 4.735, 4.735, 0, DiamondCrossing);
	Switch.CircuitLength = 0;
	push_back(Switch);
	Switch = New(sSimpleLeft6, L"6#�󵥿�", 9.462222, 8.491, 9.994, 8.874, SimpleLeft);
	Switch.CircuitLength = 7.741;
	push_back(Switch);
	Switch = New(sSimpleRight6, L"6#�ҵ���", 9.462222, 8.491, 9.994, 8.874, SimpleRight);
	Switch.CircuitLength = 7.741;
	push_back(Switch);
    Switch = New(sSimpleLeft7, L"7#�󵥿�", 8.130000, 10.897, 12.070, 10.839, SimpleLeft);
	Switch.CircuitLength = 7.748;
	push_back(Switch);
    Switch = New(sSimpleRight7, L"7#�ҵ���", 8.130000, 10.897, 12.070, 10.839, SimpleRight);
	Switch.CircuitLength = 7.748;
	push_back(Switch);
	Switch = New(sSymmetry65, L"6.5#�Գ�", 8.079494444, 8.913, 11.268, 8, Symmetry);
	Switch.CircuitLength = 7.61;
	push_back(Switch);
	Switch = New(sSymmetry9, L"9#�Գ�", 6.340278,13.839,15.009, 6.107, Symmetry);
	Switch.CircuitLength = 15.455;
	push_back(Switch);
  	return;
}

//---------------------------------------------------------------------------
TSwitch __fastcall TSwitchList::New(const unsigned short ModelIndex,
									const WideString ModelName,
									const float FrogNumber,
									const float a,
									const float b,
									const float FH)
{
	TSwitch Switch;

	Switch.ModelIndex = ModelIndex;
	Switch.a = a;
	Switch.b = b;
	Switch.FrogNumber = FrogNumber;
//   Switch.H = FH;
//	Switch.H = 24;
	Switch.Model = ModelName;

	return Switch;
};

//---------------------------------------------------------------------------
TSwitch __fastcall TSwitchList::New(const unsigned short ModelIndex,
									const WideString ModelName,
									const float Angle,
									const float a,
									const float b,
									const float CircuitLength,
									const eSwitchType Type)
	{
		TSwitch Switch;

		Switch.ModelIndex = ModelIndex;
		Switch.a = a;
		Switch.b = b;
		Switch.Angle = Angle;
		Switch.Model = ModelName;
		Switch.CircuitLength = CircuitLength;
		Switch.Type = Type;
//      0.139626337778 = 3.1415926 / 180 * 8
		switch (Type) {
			case Symmetry:
				Switch.HandTypes.push_back(shtLEFT);
                Switch.HandTypes.push_back(shtRIGHT);
				break;
			case SimpleLeft:
				Switch.HandTypes.push_back(shtSIDE);
                Switch.HandTypes.push_back(shtSTRAIGHT);
				break;
            case SimpleRight:
				Switch.HandTypes.push_back(shtSTRAIGHT);
                Switch.HandTypes.push_back(shtSIDE);
				break;
			case Treble:
				Switch.HandTypes.push_back(shtLEFT);
                Switch.HandTypes.push_back(shtSTRAIGHT);
                Switch.HandTypes.push_back(shtRIGHT);
				break;
			case DiamondCrossing:
				Switch.HandTypes.push_back(shtSTRAIGHT);
                Switch.HandTypes.push_back(shtSTRAIGHT);
				break;
		default:
			;
		}

		return Switch;
	}


//---------------------------------------------------------------------------
TSwitch __fastcall TSwitchList::Which(const WideString ModelName)
{
	unsigned short i, q;

	q = size();
	for(i = 0; i < q; i++)
		if (at(i).Model == ModelName)
		{
 //			List[i].H;      //?
			return at(i);
		}
	return at(0);
};

//---------------------------------------------------------------------------
TSwitch __fastcall TSwitchList::Which(const unsigned short ModelIndex)
{
	unsigned short i, q;
	q = size();
	for (i = 0; i < q; i++) {
		if (at(i).ModelIndex == ModelIndex) {
			return at(i);
		}
	}
	return at(0);
}
//---------------------------------------------------------------------------

TSwitch __fastcall TSwitchList::GetSwitch(const double FrogAngle, eSwitchType SwitchType) {
	for (int i = 0; i < size(); i++) {
        if (at(i).Angle == FrogAngle && at(i).Type == SwitchType) {
            return at(i);
        }
    }
    return at(0);
}
//---------------------------------------------------------------------------
unsigned short __fastcall TSwitchList::Index(const WideString ModelName)
{
   unsigned short i, q;

   q = size();
   for (i = 0; i < q; i++)
      if (at(i).Model == ModelName)
			return at(i).ModelIndex;
	return at(0).ModelIndex;
};

//---------------------------------------------------------------------------
WideString __fastcall TSwitchList::Model(const unsigned short ModelIndex)
{
	unsigned short i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).ModelIndex == ModelIndex)
      {
			return at(i).Model;
		}
	}
	return at(0).Model;
}
                    /*
TSwitch __fastcall TSwitchList::Modelconst unsigned short ModelIndex)
{
	unsigned short i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).ModelIndex == ModelIndex)
      {
			return at(i);
		}
	}
	return at(0)
}                                   */

//---------------------------------------------------------------------------
void __fastcall TSwitch::Load(const int Handle)
{
	ioPosition = ReadFloat(Handle);
	ioSortRailLength = ReadFloat(Handle);
	ModelIndex = ReadInt(Handle);
	Model = SwitchList.Model(ModelIndex);
	Direction = ReadInt(Handle);
//	ConnectWay = ReadInt(Handle);
	DrawSide = ReadInt(Handle);
	Type= ReadInt(Handle);
//	if (DrawSide == -1) {
//		DrawSide = 1;
//	}

}

//---------------------------------------------------------------------------
void __fastcall TSwitch::Save(const int Handle)
{
	WriteFloat(Handle, ioPosition);
	WriteFloat(Handle, ioSortRailLength);
	WriteInt(Handle, ModelIndex);
	WriteInt(Handle, Direction);
//	WriteInt(Handle, ConnectWay);
	WriteInt(Handle, DrawSide);
	WriteInt(Handle, Type);
}


//---------------------------------------------------------------------------
void __fastcall TSwitches::Load(const int Handle)
{
	unsigned short i, q;
	TSwitch Switch;
	float p, l;
	int Index;
	WideString Model;

	q = ReadFloat(Handle);
//	resize(q);
	clear();
	for (i = 0; i < q; i++) {
//      at(i).Load(Handle);
		p = ReadFloat(Handle);
		l = ReadFloat(Handle);
		Index = ReadInt(Handle);
		Model = SwitchList.Model(Index);
		Switch = SwitchList.Which(Model);
		Switch.ioPosition = p;
		Switch.ioSortRailLength = l;
		Switch.Direction = ReadInt(Handle);
//		Switch.ConnectWay = ReadInt(Handle);
		Switch.DrawSide = ReadInt(Handle);
		Switch.Type= ReadInt(Handle);
		push_back(Switch);
	}
	return;
};


//---------------------------------------------------------------------------
void __fastcall TSwitches::Save(const int Handle)
{
   unsigned short i, q;

   q = size();
   WriteFloat(Handle, q);
   for (i = 0; i < q; i++)
		at(i).Save(Handle);
};

void __fastcall TSwitches::ResetIndex(void)
{
	for (int i = 0; i < size(); i++) at(i).Index = i;
	return;
}

TSwitch __fastcall TSwitches::Find(const WideString SerialNumber)
{
	TSwitch A;
	for (int i = 0; i < size(); i++)
		if (at(i).SerialNumber == SerialNumber) return at(i);
	A.ModelIndex = 0;
	MessageBox(NULL, L"δ�ҵ���Ӧ�ĵ������ݣ������ݿ����Ѿ���ɾ����", L"����", MB_OK + MB_ICONERROR);
	return A;
}

ptrTSwitches __fastcall TSwitches::Find(const TSerialNumbers SerialNumbers)
{
    ptrTSwitches ptrSwitches;
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < SerialNumbers.size(); j++) {
            if (SerialNumbers[j] == at(i).SerialNumber) {
                ptrSwitches.push_back(&at(i));
            }
        }
    }
    return ptrSwitches;
}


void __fastcall TSwitches::WriteListView(TListView * ListView)
{
	int i;
	TListItem * Item;
//	TSwitchCharacterization Characterization;
	ListView->Clear();
	for (i = 0; i < size(); i++) {
		Item = ListView->Items->Add();
		Item->Caption = at(i).Name;
		Item->SubItems->Add(FloatToStrF(at(i).ioPosition, 3));
		Item->SubItems->Add(at(i).Model);
		Item->SubItems->Add(FloatToStrF(at(i).ioSortRailLength, 3));
//		Item->SubItems->Add(Characterization.StraightLateral[at(i).ConnectWay].ChineseCaption);
		if (at(i).DrawSide < 0) {
				at(i).DrawSide = 0;
		}
//		Item->SubItems->Add(Characterization.Direct[at(i).Direction].ChineseCaption);
//		Item->SubItems->Add(Characterization.DrawDirect[at(i).DrawSide].ChineseCaption);
	}
	return;
}

//---------------------------------------------------------------------------
float __fastcall TSwitch::GetInPos(void)
{
   return Position - a - SortRailLength;
}

//---------------------------------------------------------------------------
float __fastcall TSwitch::GetOutPos(void)
{
	return Position - a + CircuitLength;
}

void __fastcall TSwitches::Draw(TCanvas *Canvas,
								const int PlanBase,
								const float Scale,
								const float BeginPos,
								const float EndPos,
								const int PlanHeight)
{
	int i, q;
	int x, y;

	int Width;

	Width = PlanHeight * 0.5 - 1;

	q = size();
	for (i = 0; i < q; i++)
	{
		x = Scale * (at(i).ioPosition - BeginPos);
		y = PlanBase;
		Canvas->MoveTo(x, y);
		if (at(i).Direction > 0)
			x = Scale * (at(i).ioPosition - BeginPos - at(i).b);
		else
			x = Scale * (at(i).ioPosition - BeginPos + at(i).b); //at(i).b);
		if (at(i).DrawSide < 0)
			y = PlanBase - Width; //DONE 1:���Ϸ����ж�
		else
			y = PlanBase + Width;
      Canvas->LineTo(x, y);
	}
}
