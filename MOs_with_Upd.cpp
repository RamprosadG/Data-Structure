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

int a[N], last[N], k;

struct query {
	int l, r, t, id;
	query() {}
	query(int _l, int _r, int _t, int _id) : l(_l), r(_r), t(_t), id(_id) {}
	bool operator < (const query a) const {
		int l = l / k, l_a = a.l / k;
		int r = r / k, r_a = a.r / k;
		if (l != l_a) return l < l_a;
		if (r != r_a) return r < r_a;
		return t < a.t;
	}
};

struct update {
	int x, pre, now;
	update() {}
	update(int _x, int _pre, int _now) : x(_x), pre(_pre), now(_now) {}
};

std::vector<query> qry;
std::vector<update> upd;
int cur_res = 0;
int cnt[N], ans[N];

void add(int x) {
	x = a[x];
	cnt[x]++;
	if (cnt[x] == 1) cur_res++;
}

void remove(int x) {
	x = a[x];
	cnt[x]--;
	if (cnt[x] == 0) cur_res--;
}

void apply(int x, int y, int l, int r) {
	if (l <= x and x <= r) {
		remove(x);
		a[x] = y;
		add(x);
	} else {
		a[x] = y;
	}
}

void process() {
	int q = sz(qry);
	sort(all(qry));
	int l = 1, r = 0, t = 0;
	for (int i = 0; i < q; i++) {
		while (t < qry[i].t) t++, apply(upd[t - 1].x, upd[t - 1].now, l, r);
		while (t > qry[i].t) apply(upd[t - 1].x, upd[t - 1].pre, l, r), t--;

		while (l > qry[i].l) add(--l);
		while (r < qry[i].r) add(++r);
		while (l < qry[i].l) remove(l++);
		while (r > qry[i].r) remove(r--);

		ans[qry[i].id] = cur_res;
	}
}

int solve() {
	int n; Int(n);
	k = max(1, (int)pow(n,  2.0 / 3.0));
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
		last[i] = a[i];
	}
	int q; Int(q);
	std::vector<bool> vis(q + 1, false);
	for (int i = 1; i <= q; i++) {
		int ck; Int(ck);
		int l, r; Int(l, r);
		if (ck == 1) {
			qry.push_back(query(l, r, sz(upd), i));
			vis[i] = true;
		}
		else {
			upd.push_back(update(l, last[l], r));
			last[l] = r;
		}
	}
	process();
	for (int i = 1; i <= q; i++) {
		if (vis[i]) printf("%d\n", ans[i]);
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
