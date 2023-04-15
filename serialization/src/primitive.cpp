#include "primitive.h"
#include "core.h"
#include <stdint.h>

namespace ObjectModel
{

	Primitive::Primitive()
		: Root()
	{
		size += sizeof type;
	}

	Primitive::~Primitive()
	{
		delete data;
	}

	void Primitive::pack(std::vector<uint8_t>& buffer, int16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);

	}
}