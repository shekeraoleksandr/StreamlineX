#pragma once
#include "root.h"
#include <memory>


namespace ObjectModel
{
	class LIB Array : public Root
	{
	private:
		uint8_t type = 0;
		static int32_t count;
		std::vector<uint8_t>* data = nullptr;
	public:
		Array();
	public:
		template<typename T>
		static std::unique_ptr<Array> createArray(std::string name, Type type, std::vector<T> value);

		template<typename T>
		static std::unique_ptr<Array> createString(std::string name, Type type, T value);

		void pack(std::vector<uint8_t>&, int16_t&);
	};
}