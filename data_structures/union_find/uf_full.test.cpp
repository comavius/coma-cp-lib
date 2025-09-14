#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "./uf_full.cpp"
#include "../../common/common.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  UnionFind uf(n);
  for (ll i = 0; i < q; i++) {
    ll t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      uf.unite(u, v);
    } else {
      cout << (uf.same(u, v) ? 1 : 0) << "\n";
    }
  }
}
