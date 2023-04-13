#include "../include/primitive.h"
#include "../include/core.h"
#include <stdint.h>


namespace ObjectModel
{
	Primitive::Primitive()
	{
		size += sizeof type;
	}

	template<typename T>
	static Primitive* Primitive::create(std::string name, Type type, T value)
	{
		Primitive* p = new Primitive();
		p->setName(name);
		p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<int8_t>(type);
		p->data = new std::vector<int8_t>(sizeof value);
		p->size += p->data->size();
		int16_t iterator = 0;
		Core::template encode<T>(p->data, &iterator, value);
		return p;
	}

	void Primitive::pack(std::vector<int8_t>* buffer, int16_t* iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}
}