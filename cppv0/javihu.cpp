#include "javihu.h"

#include <string>
#include <iostream>


JaVihu::JaVihu(std::string aName, int aHela, int aIsku, std::string aHut):Vihu(aName,aHela,aIsku,aHut)
{
	this->Name = aName;
	this->Health = aHela;
	this->Attack = aIsku;
	this->hut = aHut;
}

void JaVihu::huuto()
{
	std::cout << Name + " huutaa " + hut << std::endl;
}