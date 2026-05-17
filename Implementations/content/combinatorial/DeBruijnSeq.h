/**
 * Description: Given alphabet $[0,k)$ constructs a cyclic string
 * of length $k^n$ that contains every length $n$ string as substr.
 * Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.tex
 * https://en.wikipedia.org/wiki/De_Bruijn_sequence
 * pg 241 of http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.93.5967&rep=rep1&type=pdf
 * Verification: https://cses.fi/problemset/task/1692/
 */

vector<int> deBruijnSequence(int k, int n)
{ /// Recursive FKM
	if (k == 1)
		return {0};
	vector<int> seq, aux(n + 1);
	auto gen = [&](this auto &&self, int t, int p) -> void
	{
		if (t > n)
		{ // +lyndon word of len p
			if (n % p == 0)
				for (int i = 1; i <= p; i++)
				{
					seq.push_back(aux[i]);
				}
		}
		else
		{
			aux[t] = aux[t - p];
			self(t + 1, p);
			while (++aux[t] < k)
				self(t + 1, t);
		}
	};
	gen(1, 1);
	return seq;
}