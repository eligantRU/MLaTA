/*
16.4. Сугробы на ЛЭП (8)
Служба электроснабжения проводит мониторинг уровня снега, лежащего на ЛЭП. Вся ЛЭП
разбивается на участки опорами. Если снег падает на некоторый интервал ЛЭП, то высота
снежного покрова на этом интервале увеличивается на высоту выпавшего снега. Снег также имеет
тенденцию таять на некотором участке трассы в результате оттепели, однако сугробов
отрицательной толщины быть не может. Энергетикам крайне важно уметь узнавать суммарную
высоту снежного покрова на некоторых участках, чтобы определять вероятность обрыва проводов.

Егоров Никита, ПС-21
*/

#include <chrono>

#include "Impl.hpp"

template <class T>
auto MeasureTime(T&& fn)
{
	auto begin = chrono::high_resolution_clock::now();
	fn();
	auto end = chrono::high_resolution_clock::now();
	return (end - begin);
}

int main()
{
	auto t = MeasureTime([=] {
		size_t pillarsCount, commandsCount;
		cin >> pillarsCount >> commandsCount;

		SegmentTree<int64_t> tree(vector<int64_t>(pillarsCount - 1, 0));
		for (size_t i = 0; i < commandsCount; ++i)
		{
			size_t commandType, leftPillar, rightPillar;
			cin >> commandType >> leftPillar >> rightPillar;
			if (commandType == 1)
			{
				int val;
				cin >> val;
				tree.Add(leftPillar, rightPillar - 1, val);
			}
			else if (commandType == 2)
			{
				cout << tree.Sum(leftPillar - 1, rightPillar - 1) << endl;
			}
		}
	});

	cerr << "runtime = " << chrono::duration_cast<chrono::milliseconds>(t).count() << " ms" << endl;
}
