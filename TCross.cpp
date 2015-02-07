//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCross.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall CrossAngleList::CrossAngleList() {
	CrossAngle sa;
    sa.Angle = 9.462222;
    sa.FrogNumber = 6;
    push_back(sa);

    sa.Angle = 6.340278;
    sa.FrogNumber = 9;
    push_back(sa);

    sa.Angle = 8.13;
    sa.FrogNumber = 7;
    push_back(sa);

    sa.Angle = 8.079494;
    sa.FrogNumber = 65;
    push_back(sa);
}

//---------------------------------------------------------------------------
TCrossLine & __fastcall TCrossLine::operator = (TLine * Line) {
	StartX = Line->StartX;
    StartY = Line->StartY;
    EndX = Line->EndX;
    EndY = Line->EndY;
    Length = Line->Length;
    StartAngle = Line->StartAngle;
	Angle = StartAngle;
    StartSign = Line->StartSign;
    EndSign = Line->EndSign;
	ptr = Line;
	return *this;
}

//---------------------------------------------------------------------------
TCrossLine & __fastcall TCrossLine::operator = (const TCrossLine & CrossLine) {
	StartX = CrossLine.StartX;
    StartY = CrossLine.StartY;
    EndX = CrossLine.EndX;
    EndY = CrossLine.EndY;
    Length = CrossLine.Length;
    StartAngle = CrossLine.StartAngle;
	Angle = CrossLine.Angle;
    StartSign = CrossLine.StartSign;
    EndSign = CrossLine.EndSign;
    ptr = CrossLine.ptr;
    Pos = CrossLine.Pos;
    return *this;
}

//---------------------------------------------------------------------------
void __fastcall TCross::AddLine(eLinePos Pos, TLine * Line) {
    TCrossLine sl;
    sl = Line;
    sl.Pos = Pos;
    Lines.push_back(sl);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::UpdateAngle(void) {
	int i, j, m = -1;
    double a = 90;
    int SwitchType = 0;
    CrossAngleList AngleList;     //ת�޽��б�
    TSwitchList SwitchList;
    TCrossLine CL;
    int BranchLineNumber = -1;
    MainLineNumber = -1;
    eBranchSide BranchSide;
    for (i = 0; i < Lines.size(); i++) {          // ���lpMIDDLE���߶�
        if (Lines[i].Pos == lpMIDDLE) {
        	CL = Lines[i];
            Lines[i].EndX = X;
            Lines[i].EndY = Y;
            Lines[i].Pos = lpEND;
            Lines[i].EndSign = true;
            CL.StartX = X;
            CL.StartY = Y;
            CL.Pos = lpSTART;
            CL.StartSign = true;
            Lines.push_back(CL); //��ֺ���߶�û��lpMIDDLE�ģ���������ټ�顣
        }
    }
	for (i = 0; i < Lines.size(); i++) {           // ���ø��߶εĽǶȡ�
		if (InRange(X, Y, Lines[i].EndX, Lines[i].EndY, 1)) {
        	Lines[i].Angle = OppositeAngle(Lines[i].StartAngle);
        } else {
			Lines[i].Angle = Lines[i].StartAngle;
        }
    }
    sort(Lines.begin(), Lines.end());                                     // ɾ���ظ��߶Ρ�
    Lines.erase(unique(Lines.begin(), Lines.end()), Lines.end());
    MaxAngle = MinAngle = GetAngle(Lines[0].Angle, Lines[1].Angle);       //���������С�Ƕȣ�ͬʱ�����������߶μнǴ���90����߶Σ�������ΪltMAIN
    MaxAngleA = MaxAngleB = MinAngleA = MinAngleB = -1;
    int k = 0;
    for (i = 0; i < Lines.size(); i++) {
        for (j = i + 1; j < Lines.size(); j++) {
        	a = GetAngle(Lines[i].Angle, Lines[j].Angle);
            if (a > 90) {
                k++;
            }
            if (a > MaxAngle) {
                MaxAngle = a;
                MaxAngleA = i;
                MaxAngleB = j;
            } else if (a < MinAngle) {
            	MinAngle = a;
                MinAngleA = i;
                MinAngleB = j;
            }
        }
        if (k > 1) {
            MainLineNumber = i;
        }
    }
    for (i = 0; i < Lines.size(); i++) {
        Lines[i].Type = GetBranchSide(Lines[MainLineNumber].Angle, Lines[i].Angle);
        SwitchType += Lines[i].Type;
    }
    FrogNumber = -1;                                  //������С�ǲ��Ҷ�Ӧ���޲�š�
    for (i = 0; i < AngleList.size(); i++) {
        if (EqualAngle(MinAngle, AngleList[i].Angle)) {
        	FrogNumber = AngleList[i].FrogNumber;
            break;
        }
    }
    if (FrogNumber == -1) {
        Type = sNone;
        return;
    }
    switch (SwitchType) {                         // ȷ�������ͺ�
        case 7:		// �󵥿�
        	switch (FrogNumber) {
                case 6:
                	Type = sSimpleLeft6;
                    break;
                case 9:
                	Type = sSimpleLeft9;
                    break;
                case 7:
                	Type = sSimpleLeft7;
                    break;
	            default:
                	Type = sNone;
            }
        	break;
        case 11:	// �Գ�
        	switch (FrogNumber) {
                case 6:
                	Type = sSymmetry6;
                    break;
                case 65:
                	Type = sSymmetry65;
                    break;
                case 9:
                	Type = sSymmetry9;
                    break;
            	default:
                	Type = sNone;
            }
            break;
        case 13:	//�ҵ���
        	switch (FrogNumber) {
                case 6:
                	Type = sSimpleRight6;
                    break;
                case 9:
                	Type = sSimpleRight9;
                    break;
                case 7:
                	Type = sSimpleRight7;
                    break;
	            default:
                	Type = sNone;
            }
        case 15:	//�����Գ�
        	if (FrogNumber == 7)
                Type = sTreble7;
            else
            	Type = sNone;
	    default:
        	Type = sNone;
    }
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	for (int i = 0; i < Lines.size(); i++) {
		Lines[i].Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::SetSimpleSwitchType(const eBranchSide BranchSide) {
    switch (BranchSide) {
		case bsLEFT:
        	Type = SimpleLeft;     //��൥������
            break;
         case bsRIGHT:
         	Type = SimpleRight;
            break;
         default:
         	Type = NoSwitch;
            break;
	}
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCrosses::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	Image->Canvas->Pen->Color = clRed;
	for (int i = 0; i < size(); i++) {
		at(i).Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}


