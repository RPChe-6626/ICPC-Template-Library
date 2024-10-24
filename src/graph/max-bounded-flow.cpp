#include <bits/stdc++.h>
using namespace std;
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pb push_back
#define eb emplace_back
#define pa pair<int, int>
#define fi first
#define se second
typedef long long ll;
inline int rd() {
    int x = 0;
    char ch, t = 0;
    while (!isdigit(ch = getchar())) t |= ch == '-';
    while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
    return t ? -x : x;
}
struct Dinic {
#define Maxn 505
#define Maxm 20005
    int tot = 1;
    int hea[Maxn], tmphea[Maxn], dep[Maxn];
    int nex[Maxm << 1], ver[Maxm << 1], num[Maxm << 1];
    ll edg[Maxm << 1];
    inline int addedge(int x, int y, ll d, int _n) {
        ver[++tot] = y, nex[tot] = hea[x], hea[x] = tot, edg[tot] = d, num[tot] = -1;
        ver[++tot] = x, nex[tot] = hea[y], hea[y] = tot, edg[tot] = 0, num[tot] = _n;
        return tot;
    }
    inline bool bfs(int s, int t) {
        memcpy(tmphea, hea, sizeof(hea));
        memset(dep, 0, sizeof(dep)), dep[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur == t) return true;
            for (int i = hea[cur]; i; i = nex[i])
                if (edg[i] > 0 && !dep[ver[i]])
                    dep[ver[i]] = dep[cur] + 1, q.push(ver[i]);
        }
        return false;
    }
    ll dfs(int x, int t, ll flow) {
        if (!flow || x == t) return flow;
        ll rest = flow, tmp;
        for (int i = tmphea[x]; i && rest; i = nex[i]) {
            tmphea[x] = i;
            if (dep[ver[i]] == dep[x] + 1 && edg[i] > 0) {
                if (!(tmp = dfs(ver[i], t, min(rest, edg[i]))))
                    dep[ver[i]] = 0;
                edg[i] -= tmp, edg[i ^ 1] += tmp, rest -= tmp;
            }
        }
        return flow - rest;
    }
    inline ll solve(int s, int t) {
        ll sum = 0;
        while (bfs(s, t))
            sum += dfs(s, t, infll);
        return sum;
    }
#undef Maxn
#undef Maxm
} G;
#define Maxn 505
#define Maxm 20005
int n, m, ss, tt, s, t;
int ans[Maxm];
ll needin, needout;
ll Ind[Maxn], Outd[Maxn];
int main() {
    n = rd(), m = rd(), s = rd(), t = rd(), ss = n + 1, tt = n + 2;
    for (int i = 1, x, y, Inf, Sup; i <= m; i++) {
        x = rd(), y = rd(), Inf = rd(), Sup = rd();
        G.addedge(x, y, Sup - Inf, i);
        Outd[x] += Inf;
        Ind[y] += Inf;
        ans[i] = Inf;
    }
    for (int i = 1; i <= n; i++) {
        if (Ind[i] > Outd[i])
            G.addedge(ss, i, Ind[i] - Outd[i], -1), needin += Ind[i] - Outd[i];
        if (Ind[i] < Outd[i])
            G.addedge(i, tt, Outd[i] - Ind[i], -1), needout += Outd[i] - Ind[i];
    }
    G.addedge(t, s, infll, -1);
    ll tmp = G.solve(ss, tt);
    if (needin != needout || needin != tmp) printf("please go home to sleep\n");
    else {
        tmp = G.edg[G.tot];
        G.edg[G.tot] = G.edg[G.tot - 1] = 0;
        tmp += G.solve(s, t);
        printf("%lld\n", tmp);
    }
    return 0;
}