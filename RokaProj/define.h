#pragma once
#define SINGLETON(ctype)private: ctype();~ctype();\
private:static ctype* minstance;\
public:  static ctype* GetInst(){\
 if(minstance==nullptr)\
  minstance = new ctype();\
return minstance;\
}