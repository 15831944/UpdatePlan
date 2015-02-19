//---------------------------------------------------------------------------

#ifndef TPathH
#define TPathH

#include <TEntity.h>

//---------------------------------------------------------------------------

class TPath : public TEntities {
public:
	float Angle;	//ʶ�����ʱ�������ж����ӵ��ĸ���֧�ϣ�Ϊ�˷��㣬ʹ���߶ε�Start����
	bool __fastcall FindCross(TCross * C) {
		for (int i = 0; i < size(); i++) {
			if (at(i).type() == typeid(TCross *) && boost::any_cast<TCross *>(at(i)) == C) {
				return true;
			}
		}
		return false;
	}
    bool __fastcall FindLine(TLine * L) {
        for (int i = 0; i < size(); i++) {
            if (at(i).type() == typeid(TLine *) && boost::any_cast<TLine *>(at(i)) == L)
                return true;
        }
        return false;
    }
    void __fastcall Add(TLine * L) {
        if (!FindLine(L)) {
            push_back(L);
            Angle = L->StartAngle;
        }
        return;
	}
	void __fastcall SetPosition(void);
	void __fastcall Draw(TImage * Image, float Scale, int OriginX, int OriginY);
};

class TPaths : public vector<TPath> {
public:
	void __fastcall SetPosition(void);
	void __fastcall Draw(TImage * Image, float Scale, int OriginX, int OriginY);
};
#endif
