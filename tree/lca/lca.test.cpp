#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "./lca.cpp"
#include "../../common/common.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  vvll children(n);
  rep(i, n - 1) {
    ll p;
    cin >> p;
    children[p].push_back(i + 1);
  }
  LCA lca(0, children);
  rep(qi, q) {
    ll u, v;
    cin >> u >> v;
    cout << lca.query(u, v) << "\n";
  }
}