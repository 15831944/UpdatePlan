//---------------------------------------------------------------------------

#ifndef TPlanH
#define TPlanH
//---------------------------------------------------------------------------

#include "TArc.h"
#include "TLine.h"
#include "TSwitch.h"

class TPlan {
public:
    double OriginX, OriginY;	// TImage基点（左下角）在Plan中的位置。
    double Scale;
	TArcs Arcs;
    TLines Lines;
    TSwitches Switches;
    __fastcall TPlan();
    void __fastcall SetOrigin(TImage * Image);
    void __fastcall Clear(void);
    void __fastcall Draw(TImage * Image);
private:
	double MaxX, MaxY, MinX, MinY, Width, Height;
    void __fastcall SetMaxMin(void);
};
#endif
