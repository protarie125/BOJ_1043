#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

int findRoot(vi& d, int x) {
	if (d[x] == x) {
		return x;
	}

	d[x] = findRoot(d, d[x]);
	return d[x];
}

void joint(vi& d, int x, int y) {
	const auto& xr = findRoot(d, x);
	const auto& yr = findRoot(d, y);

	d[yr] = xr;
}

bool haveSameRoot(vi& d, int x, int y) {
	const auto& xr = findRoot(d, x);
	const auto& yr = findRoot(d, y);

	return (xr == yr);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	auto disjoint = vi(n + 1);
	for (auto i = 1; i <= n; ++i) {
		disjoint[i] = i;
	}

	auto party = vvi(m);

	// read know
	int ck;
	cin >> ck;

	auto know = vi(ck);
	for (auto i = 0; i < ck; ++i) {
		cin >> know[i];
	}

	// read party
	for (auto i = 0; i < m; ++i) {
		int cp;
		cin >> cp;

		party[i] = vi(cp);
		for (auto j = 0; j < cp; ++j) {
			cin >> party[i][j];
		}
	}

	// solve
	for (auto i = 0; i < m; ++i) {
		const auto& ph = party[i][0];
		const auto& pn = static_cast<int>(party[i].size());
		for (auto j = 1; j < pn; ++j) {
			joint(disjoint, ph, party[i][j]);
		}
	}

	auto ans = int{ m };
	for (auto i = 0; i < m; ++i) {
		auto isOk = bool{ true };
		const auto& pn = static_cast<int>(party[i].size());
		for (auto j = 0; j < pn && isOk; ++j) {
			const auto& x = party[i][j];
			for (auto k = 0; k < ck; ++k) {
				const auto& y = know[k];

				if (haveSameRoot(disjoint, x, y)) {
					isOk = false;
					break;
				}
			}
		}

		if (!isOk) {
			--ans;
		}
	}

	cout << ans;

	return 0;
}