#pragma once
#include "root.h"
#include <memory>
#include "core.h"


namespace ObjectModel
{
	class Array : public Root
	{
	private:
		int8_t type = 0;
		int32_t count = 0;
		std::vector<int8_t>* data = nullptr;
	private:
		Array();
	public:
		template<typename T>
		static Array* createArray(std::string name, Type type, std::vector<T> value);

		template<typename T>
		static Array* createString(std::string name, Type type, T value);

		void pack(std::vector<int8_t>*, int16_t*);
	};
}
