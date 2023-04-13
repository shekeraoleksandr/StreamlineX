#include "../include/array.h"
#include "../include/core.h"


namespace ObjectModel
{
	Array::Array()
	{
		size += sizeof type + sizeof count;
	}

	template<typename T>
	static Array* Array::createArray(std::string name, Type type, std::vector<T> value)
	{
		Array* arr = new Array();
		arr->setName(name);
		arr->wrapper = static_cast<int8_t>(Wrapper::ARRAY);
		arr->type = static_cast<int8_t>(type);
		arr->count = value.size();
		arr->data = new std::vector<int8_t>(value.size() * sizeof T);
		arr->size += value.size() * sizeof T;
		int16_t iterator = 0;
		Core::template encode<T>(arr->data, &iterator, value);
		return arr;
	}

	template<typename T>
	static Array* Array::createString(std::string name, Type type, T value)
	{
		Array* str = new Array();
		str->setName(name);
		str->wrapper = static_cast<int8_t>(Wrapper::STRING);
		str->type = static_cast<int8_t>(type);
		str->count = value.size();
		str->data = new std::vector<int8_t>(value.size());
		str->size += value.size();
		int16_t iterator = 0;
		Core::template encode<T>(str->data, &iterator, value);
		return str;
	}

	void Array::pack(std::vector<int8_t>* buffer, int16_t* iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int32_t>(buffer, iterator, count);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}
}
