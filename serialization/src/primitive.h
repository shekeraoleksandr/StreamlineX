#pragma once
#include "root.h"
#include <memory>

namespace ObjectModel
{
	class LIB Primitive : public Root
	{
	private:
		uint8_t type = 0;
		std::vector<uint8_t>* data = nullptr;
	private:
		Primitive();
	public:
		template<typename T>
		static std::unique_ptr<Primitive> create(std::string name, Type type, T value);

		void pack(std::vector<uint8_t>&, int16_t&);

	};



}