#include<bits/stdc++.h>
using namespace std;

#define ll       long long
#define ull      unsigned ll
#define pii      pair<int, int>
#define pll      pair<ll, ll>
#define mp       make_pair
#define ff       first
#define ss       second
#define sz(x)    (int) x.size()
#define all(v)   v.begin(), v.end()

template <typename T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <typename T> inline void smax(T &a, T b) {a = a > b ? a : b;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << ", ";
	err(++it, args...);
}

template <typename T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

template <typename T, typename TT> inline void Int(T &n, TT &m) { Int(n); Int(m); }
template <typename T, typename TT, typename TTT> inline void Int(T &n, TT &m, TTT &l) { Int(n, m); Int(l); }

const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b) {return (ll) a * b % mod;}

const int inf = (int) 2e9 + 5;
const ll  Inf = (ll) 2e18 + 5;
const int N   = (int) 2e5 + 5;

int a[N], k;

struct MO {
	int id, l, r;
	MO() {}
	MO(int _id, int _l, int _r) : id(_id), l(_l), r(_r) {}
	bool operator < (const MO a) const {
		int block = l / k, block_a = a.l / k;
		return block != block_a ? block < block_a : (block & 1 ? a.r < r : r < a.r);
	}
};

vector<MO> qry;
int cur_res = 0;
int cnt[N], ans[N];

void add(int x) {
	cnt[a[x]]++;
	if (cnt[a[x]] == 1) cur_res++;
}

void remove(int x) {
	cnt[a[x]]--;
	if (cnt[a[x]] == 0) cur_res--;
}

void process(int n, int q) {
	sort(all(qry));
	int cur_l = 1, cur_r = 0;
	for (int i = 0; i < q; i++) {
		int l = qry[i].l, r = qry[i].r, id = qry[i].id;
		while (cur_l > l) add(--cur_l);
		while (cur_r < r) add(++cur_r);
		while (cur_l < l) remove(cur_l++);
		while (cur_r > r) remove(cur_r--);
		ans[id] = cur_res;
	}
}

int solve() {
	int n; Int(n);
	k = (int)sqrt(n + 2);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	int q; Int(q);
	for (int i = 1; i <= q; i++) {
		int l, r; Int(l, r);
		qry.push_back(MO(i, l, r));
	}
	process(n, q);
	for (int i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

int main() {
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int test = 1, tc = 0;
	//Int(test);
	//cin >> test;
	while (test--) {
		//printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}
