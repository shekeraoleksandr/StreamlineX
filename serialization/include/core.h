#pragma once
#include <bitset>
#include <fstream>
#include <vector>
#include "root.h"

namespace Core
{
	namespace Util
	{
		bool isLittleEndian();
		void save(const char* file, std::vector<int8_t> buffer);
		void retriveNsave(ObjectModel::Root* r);
	}

	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value)
	{
		for (unsigned i = 0, j = 0; i < sizeof T; i++)
		{
			(*buffer)[(*iterator)++] = (value >> ((sizeof T * 8) - 8) - ((i == 0) ? j : j += 8));
		}
	}

	template<>
	void encode<float>(std::vector<int8_t>* buffer, int16_t* iterator, float value)
	{
		int32_t result = *reinterpret_cast<int32_t*>(&value);
		encode<int32_t>(buffer, iterator, result);
	}

	template<>
	void encode<double>(std::vector<int8_t>* buffer, int16_t* iterator, double value)
	{
		int32_t result = *reinterpret_cast<int64_t*>(&value);
		encode<int64_t>(buffer, iterator, result);
	}

	template<>
	void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value)
	{
		for (unsigned i = 0; i < value.size(); i++)
		{
			encode<int8_t>(buffer, iterator, value[i]);
		}
	}

	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value)
	{
		for (unsigned i = 0; i < value.size(); i++)
		{
			encode<T>(buffer, iterator, value[i]);
		}
	}
}