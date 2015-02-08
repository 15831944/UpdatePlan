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
};

class TPaths : public vector<TPath> {

};
#endif
