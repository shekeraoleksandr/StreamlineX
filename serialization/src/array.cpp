#include "array.h"
#include "core.h"


namespace ObjectModel
{

	int Array::count = 0;

	Array::Array()
	{
		size += sizeof type + sizeof count;
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