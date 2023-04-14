#include "array.h"
#include "core.h"


namespace ObjectModel
{

	int Array::count = 0;

	Array::Array()
	{
		size += sizeof type + sizeof count;
	}

	template<typename T>
	static std::unique_ptr<Array> Array::createArray(std::string name, Type type, std::vector<T> value)
	{
		std::unique_ptr<Array> arr = std::make_unique<Array>();
		arr->setName(name);
		arr->wrapper = static_cast<uint8_t>(Wrapper::ARRAY);
		arr->type = static_cast<uint8_t>(type);
		arr->count = (int32_t)value.size();
		arr->data = new std::vector<uint8_t>(sizeof(T) * arr->count);
		arr->size += (int32_t)(value.size()) * sizeof T;
		int16_t iterator = 0;
		Core::template encode<T>(*arr->data, iterator, value);


		return arr;
	}

	template<typename T>
	static std::unique_ptr<Array> Array::createString(std::string name, Type type, T value)
	{
		std::unique_ptr<Array>str = std::make_unique<Array>();
		str->setName(name);
		str->wrapper = static_cast<uint8_t>(Wrapper::STRING);
		str->type = static_cast<uint8_t>(type);
		str->count = (int32_t)value.size();
		str->data = new std::vector<uint8_t>(value.size());
		str->size += (int32_t)value.size();
		int16_t iterator = 0;
		Core::template encode<T>(*str->data, iterator, value);


		return str;
	}

	void Array::pack(std::vector<uint8_t>& buffer, int16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<int32_t>(buffer, iterator, count);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}

}