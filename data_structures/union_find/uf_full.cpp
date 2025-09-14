#pragma once
#include "../../common/common.cpp"

struct UnionFind {
  vll p; // parent
  vll r; // rank
  vll s; // size
  vll e; // edge count

  UnionFind(ll n) {
    p.resize(n, -1);
    r.resize(n, 0);
    s.resize(n, 1);
    e.resize(n, 0);
  }

  ll root(ll x) {
    if (p[x] == -1) {
      return x;
    } else {
      return p[x] = root(p[x]);
    }
  }

  void unite(ll x, ll y) {
    ll rx = root(x);
    ll ry = root(y);
    if (rx == ry) {
      e[rx]++;
      return;
    } else if (r[rx] < r[ry]) {
      p[rx] = ry;
      s[ry] += s[rx];
      e[ry] += e[rx] + 1;
    } else {
      p[ry] = rx;
      s[rx] += s[ry];
      if (r[rx] == r[ry])
        r[rx]++;
      e[rx] += e[ry] + 1;
    }
    return;
  }

  bool same(ll x, ll y) { return root(x) == root(y); }

  long long size(ll x) { return s[root(x)]; }
  bool cycle(ll x) { return e[root(x)] >= s[root(x)]; }
};
