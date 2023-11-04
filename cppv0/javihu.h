#pragma once
#ifndef JAVIHU
#define JAVIHU

#include "vihu.h"

class JaVihu :public Vihu
{
public:
	JaVihu(std::string name, int hela, int isku, std::string aHut);
	void huuto();
};


#endif // !JAVIHU
