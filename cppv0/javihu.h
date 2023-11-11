#pragma once
#ifndef JAVIHU
#define JAVIHU

#include "vihu.h"

class JaVihu :public Vihu
{
public:
	JaVihu(std::string aName, int aHealth, int aAttack, std::string aHut,int aExp);
	void huuto();
};

#endif // !JAVIHU
