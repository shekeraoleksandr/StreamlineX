#pragma once
#include <stdint.h>



namespace ObjectModel
{

	enum class Wrapper : uint8_t
	{
		PRIMITIVE = 1,
		ARRAY,
		STRING,
		OBJECT
	};

	enum class Type : uint8_t
	{
		I8 = 1,
		I16,
		I32,
		I64,

		FLOAT,
		DOUBLE,

		BOOL
	};
}