#include "../../common/common.cpp"

/// Lowest Common Ancestor.
///
/// constructor: `O(N log(N))`.
/// query: `O(log(N))`.
/// where `N = |V|`
struct LCA {
  /// List of i^2 generation ago node.
  vvll anc;
  /// Size of given graph.
  ll n;
  /// Log2 of the maximum possible depth
  ll k;
  /// Distance from root node.
  vll dist;

  LCA(ll root, vvll &children) {
    n = children.size();
    k = 64 - __builtin_clzll(n);
    anc.resize(n, vll(k, -1));
    dist.resize(n, 0);
    function<void(ll, ll)> dfs;
    dfs = [&](ll now, ll parent) {
      anc[now][0] = parent;
      rep(i, k - 1) {
        if (anc[now][i] == -1)
          break;
        anc[now][i + 1] = anc[anc[now][i]][i];
      }
      for (auto c : children[now]) {
        dist[c] = dist[now] + 1;
        dfs(c, now);
      }
    };
    dfs(root, -1);
  }

  ll query(ll u, ll v) {
    if (dist[u] < dist[v])
      swap(u, v);

    rep(i, k) {
      ll nu = anc[u][k - i - 1];
      if (nu == -1)
        continue;
      if (dist[nu] >= dist[v])
        u = nu;
    }
    if (u == v)
      return u;
    rep(i, k) {
      ll nu = anc[u][k - i - 1];
      ll nv = anc[v][k - i - 1];
      if (nu != nv) {
        u = nu;
        v = nv;
      }
    }
    return anc[u][0];
  }
};