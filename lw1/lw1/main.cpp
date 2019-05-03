#include "Impl.hpp"

int main()
{
	{
		const auto bla = Check(22411, 23000);
		const auto q = *bla == list<size_t>{1, 2, 21, 211, 422, 224, 2241, 22411};
		Print(bla);
	}
}
