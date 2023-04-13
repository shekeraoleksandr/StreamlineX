#include "../include/serialization.h"
#include <cassert>
#include "../include/primitive.h"

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian());

	(void)argc;
	(void)argv;
	return 0;
}
