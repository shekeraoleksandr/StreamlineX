#include <serialization.h>
#include <cassert>

using namespace ObjectModel;

namespace TestFrame
{
	void testPack()
	{
		int32_t foo = 231;
		std::unique_ptr<Primitive> p = Primitive::create("int32", Type::I32, foo);

		Object Test("Foo");
		Test.addEntity(p.get());

		Core::Util::retriveNsave(&Test);
	}
}

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian());

	TestFrame::testPack();

	(void)argc;
	(void)argv;
	return 0;
}