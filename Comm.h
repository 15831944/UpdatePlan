//---------------------------------------------------------------------------

#ifndef CommH
#define CommH

#include <math.h>
//---------------------------------------------------------------------------

enum eBranchSide {bsMAIN = 1, bsLEFT = 2, bsSTRAIGHT = 4, bsRIGHT = 8, bsUNKNOWN = 128};        //bsMAIN ���� ����֧��

bool __fastcall InRange(const double x, const double y, const double X, const double Y, const double R) {
	double dx = X - x;
    double dy = Y - y;
    if (dx * dx + dy * dy < R * R)
        return true;
    else
    	return false;
}

//---------------------------------------------------------------------------
double __fastcall OppositeAngle(const double Angle) {
    if (Angle >= 179.999) {
		return Angle - 180;
    } else {
		return Angle + 180;
    }
}

//---------------------------------------------------------------------------
double __fastcall GetAngle(const double StartAngle, const double EndAngle) {
	double a;
    a = fabs(StartAngle - EndAngle);
    if (a >= 179.999)
        return 360 - a;
    else
    	return a;
}

//---------------------------------------------------------------------------
bool __fastcall EqualAngle(const double AngleA, const double AngleB) {
    if (fabs(AngleA - AngleB) < 0.06) {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------
eBranchSide __fastcall GetBranchSide(const double MainAngle, const double BranchAngle) {
	if (fabs(MainAngle - BranchAngle) < 0.001) return bsMAIN;
    if (fabs(MainAngle - OppositeAngle(BranchAngle)) < 0.001) return bsSTRAIGHT;
    if (MainAngle > 180) {
        if (BranchAngle < MainAngle && BranchAngle > OppositeAngle(MainAngle)) return bsLEFT;
        else return bsRIGHT;
    } else {
        if (BranchAngle > MainAngle && BranchAngle < OppositeAngle(MainAngle)) return bsRIGHT;
        else return bsLEFT;
    }
}
#endif
