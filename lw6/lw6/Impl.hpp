#include <algorithm>
#include <iostream>
#include <vector>

using namespace::std;

bool IsFirstWinner(size_t N)
{
	++(++N);
	const auto Ssize = 1 + max(N / 2, (size_t)1);
	vector<vector<unsigned>> S(N - 1, vector<unsigned>(Ssize, 0));

	for (size_t M = 1; M < Ssize; ++M)
	{
		if (S.size() > 1)
		{
			S[1][M] = 1;
		}
		if (S.size() > 2)
		{
			S[2][M] = 2;
		}
	}

	for (size_t K = 3; K < S.size(); ++K)
	{
		for (size_t M = 1; M < Ssize; ++M)
		{
			if (K <= 2 * M)
			{
				S[K][M] = K;
			}
		}
	}

	for (size_t K = 3; K < S.size(); ++K)
	{
		for (size_t M = 1; M < Ssize; ++M)
		{
			if (K > 2 * M)
			{
				bool marker = false;
				for (size_t L = 1; L <= 2 * M; ++L)
				{
					if ((K >= L) && (L < Ssize) && (S[K - L][L] == 0))
					{
						S[K][M] = L;
						marker = true;
					}
				}
				if (!marker)
				{
					S[K][M] = 0;
				}
			}
		}
	}

	return S[N - 2][1] > 0;
}
