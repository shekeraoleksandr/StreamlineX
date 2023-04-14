#pragma once
#include <iostream>
#include "root.h"

namespace ObjectModel
{
	class LIB Object : public Root
	{
	public:
		std::vector<Root*> entities;
		int16_t count = 0;
	public:
		Object(std::string);
		void addEntity(Root*);
		void pack(std::vector<uint8_t>&, int16_t&);

		Root* findByName(std::string name);
		
	};

}