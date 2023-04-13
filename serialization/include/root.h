#pragma once
#include <string>
#include <vector>
#include "lib.h"
#include "meta.h"


namespace ObjectModel
{
	class Root
	{
	protected:
		std::string name;
		int16_t nameLength;
		int8_t wrapper;
		int32_t size;
	protected:
		Root()
			:
			name("unknown"),
			wrapper(0),
			nameLength(0),
			size(sizeof nameLength + sizeof wrapper + sizeof size) {}
	public:
		int32_t getSize() { return size; }
		void setName(std::string name)
		{
			this->name = name;
			nameLength = (int16_t)name.length();
			size += nameLength;
		}
		std::string getName() { return name; }
		virtual void pack(std::vector<int8_t>*, int16_t*) = 0;
	};
}