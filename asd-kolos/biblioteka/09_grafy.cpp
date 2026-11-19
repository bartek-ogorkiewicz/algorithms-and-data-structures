// ============================================================
//  09 GRAFY — BFS, DFS iteracyjny, dwudzielność, spójne składowe,
//  sortowanie topologiczne, Dijkstra, DSU (find-union), BFS na kratce
//  Wierzchołki 1..n (jak w treściach), lista sąsiedztwa vector<vector<int>>.
//  n, m do 5*10^5: REKURENCYJNY DFS MOŻE PRZEPEŁNIĆ STOS -> BFS albo iteracyjny DFS.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<int>>;

// wczytanie (nieskierowany):
//   int n, m; cin >> n >> m; Graph g(n + 1);
//   for (int i = 0; i < m; i++) { int a, b; cin >> a >> b; g[a].push_back(b); g[b].push_back(a); }

// ---------- BFS: odległości (liczba krawędzi) od źródła, -1 = nieosiągalny ----------
vector<int> bfs(const Graph& g, int s) {
    vector<int> dist(g.size(), -1); queue<int> q;
    dist[s] = 0; q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : g[v]) if (dist[u] == -1) { dist[u] = dist[v] + 1; q.push(u); }
    }
    return dist;
}
// Wiele źródeł naraz (np. "odległość do najbliższego sklepu"): wrzuć wszystkie z dist=0 na start.
// Odtworzenie ścieżki: trzymaj par[u] = v przy odwiedzeniu, potem cofaj się od celu.

// ---------- DWUDZIELNOŚĆ (zadanie SKI) — BFS kolorowanie, graf może być niespójny ----------
// dwudzielny <=> brak cyklu nieparzystego
bool isBipartite(const Graph& g, vector<int>& color) {
    int n = g.size(); color.assign(n, -1);
    for (int s = 1; s < n; s++) if (color[s] == -1) {
        color[s] = 0; queue<int> q; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : g[v]) {
                if (color[u] == -1) { color[u] = color[v] ^ 1; q.push(u); }
                else if (color[u] == color[v]) return false;
            }
        }
    }
    return true;
}

// ---------- SPÓJNE SKŁADOWE: comp[v] = numer składowej (od 0) ----------
int components(const Graph& g, vector<int>& comp) {
    int n = g.size(), c = 0; comp.assign(n, -1);
    for (int s = 1; s < n; s++) if (comp[s] == -1) {
        vector<int> st = {s}; comp[s] = c;
        while (!st.empty()) { int v = st.back(); st.pop_back();
            for (int u : g[v]) if (comp[u] == -1) { comp[u] = c; st.push_back(u); } }
        c++;
    }
    return c;
}

// ---------- DFS ITERACYJNY z kolejnością post-order (np. rozmiary poddrzew) ----------
// Na drzewie z korzeniem r: parent, kolejność odwiedzin; potem przetwarzaj od końca = od liści.
vector<int> subtreeSizes(const Graph& g, int root) {
    int n = g.size(); vector<int> par(n, 0), order, sz(n, 1);
    vector<int> st = {root}; par[root] = -1;
    while (!st.empty()) { int v = st.back(); st.pop_back(); order.push_back(v);
        for (int u : g[v]) if (u != par[v]) { par[u] = v; st.push_back(u); } }
    for (int i = order.size() - 1; i > 0; i--) sz[par[order[i]]] += sz[order[i]];   // od liści w górę
    return sz;
}

// ---------- SORTOWANIE TOPOLOGICZNE (Kahn) — graf SKIEROWANY ----------
// Zwraca pusty wektor, gdy jest cykl. Najmniejsza leksykograficznie: priority_queue z greater.
vector<int> topoSort(const Graph& g) {
    int n = g.size(); vector<int> indeg(n, 0), res; queue<int> q;
    for (int v = 1; v < n; v++) for (int u : g[v]) indeg[u]++;
    for (int v = 1; v < n; v++) if (indeg[v] == 0) q.push(v);
    while (!q.empty()) { int v = q.front(); q.pop(); res.push_back(v);
        for (int u : g[v]) if (--indeg[u] == 0) q.push(u); }
    if ((int)res.size() != n - 1) return {};
    return res;
}
// Najdłuższa ścieżka w DAG-u: dp po kolejności topologicznej.

// ---------- DIJKSTRA  O((n+m) log n), wagi NIEUJEMNE ----------
using WGraph = vector<vector<pair<int, ll>>>;   // (sąsiad, waga)
vector<ll> dijkstra(const WGraph& g, int s) {
    const ll INF = LLONG_MAX; vector<ll> dist(g.size(), INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d != dist[v]) continue;            // przestarzały wpis (leniwe usuwanie)
        for (auto [u, w] : g[v]) if (d + w < dist[u]) { dist[u] = d + w; pq.push({dist[u], u}); }
    }
    return dist;
}
// Wagi tylko 0/1: BFS z deque (0 -> push_front, 1 -> push_back).

// ---------- DSU (Find-Union) — kompresja ścieżek + łączenie po rozmiarze ----------
// Prawie O(1). Do: "czy x i y w tej samej grupie", liczba składowych przy dodawaniu krawędzi,
// Kruskal (MST), wykrywanie cyklu w nieskierowanym.
struct DSU {
    vector<int> p, sz; int comps;
    DSU(int n) : p(n + 1), sz(n + 1, 1), comps(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; } return x; }   // iteracyjnie, bez rekurencji
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;          // już razem => ta krawędź zamyka cykl
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; comps--;
        return true;
    }
};
// Kruskal: posortuj krawędzie po wadze, bierz te, dla których unite == true.
ll kruskal(int n, vector<tuple<ll,int,int>> edges) {   // (waga, a, b); zwraca -1 gdy niespójny
    sort(edges.begin(), edges.end()); DSU d(n); ll total = 0;
    for (auto [w, a, b] : edges) if (d.unite(a, b)) total += w;
    return d.comps == 1 ? total : -1;
}

// ---------- BFS NA KRATCE (labirynt) ----------
int gridBfs(const vector<string>& g, int sr, int sc, int tr, int tc) {
    int n = g.size(), m = g[0].size(); vector<vector<int>> d(n, vector<int>(m, -1));
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    queue<pair<int,int>> q; d[sr][sc] = 0; q.push({sr, sc});
    while (!q.empty()) { auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) { int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || g[nr][nc] == '#' || d[nr][nc] != -1) continue;
            d[nr][nc] = d[r][c] + 1; q.push({nr, nc}); } }
    return d[tr][tc];
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(10);
    for (int it = 0; it < 1000; it++) {
        int n = rng() % 8 + 1; Graph g(n + 1); vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
        DSU dsu(n);
        for (int a = 1; a <= n; a++) for (int b = a + 1; b <= n; b++) if (rng() % 3 == 0) { g[a].push_back(b); g[b].push_back(a); adj[a][b] = adj[b][a] = 1; dsu.unite(a, b); }
        // Floyd jako brute
        vector<vector<int>> D(n + 1, vector<int>(n + 1, 1e9));
        for (int i = 1; i <= n; i++) { D[i][i] = 0; for (int j = 1; j <= n; j++) if (adj[i][j]) D[i][j] = 1; }
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
        auto dist = bfs(g, 1);
        for (int v = 1; v <= n; v++) assert(dist[v] == (D[1][v] >= 1e9 ? -1 : D[1][v]));
        vector<int> comp; int c = components(g, comp); assert(c == dsu.comps);
        for (int a = 1; a <= n; a++) for (int b = 1; b <= n; b++) assert((comp[a] == comp[b]) == (dsu.find(a) == dsu.find(b)) && (comp[a] == comp[b]) == (D[a][b] < 1e9));
        // dwudzielność: brute po kolorowaniach
        bool bb = false; for (int m = 0; m < (1 << n) && !bb; m++) { bool ok = true;
            for (int a = 1; a <= n; a++) for (int b = 1; b <= n; b++) if (adj[a][b] && ((m >> (a - 1)) & 1) == ((m >> (b - 1)) & 1)) ok = false;
            bb = ok; }
        vector<int> col; assert(isBipartite(g, col) == bb);
        // drzewo: rozmiary poddrzew
        Graph t(n + 1); for (int v = 2; v <= n; v++) { int p = rng() % (v - 1) + 1; t[p].push_back(v); t[v].push_back(p); }
        auto sz = subtreeSizes(t, 1); assert(sz[1] == n);
        // DAG: krawędzie i->j dla i<j w losowej permutacji
        vector<int> pm(n); iota(pm.begin(), pm.end(), 1); shuffle(pm.begin(), pm.end(), rng);
        Graph dag(n + 1); vector<pair<int,int>> E;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (rng() % 2) { dag[pm[i]].push_back(pm[j]); E.push_back({pm[i], pm[j]}); }
        auto ts = topoSort(dag); assert((int)ts.size() == n);
        vector<int> pos(n + 1); for (int i = 0; i < n; i++) pos[ts[i]] = i;
        for (auto [a, b] : E) assert(pos[a] < pos[b]);
        if (!E.empty()) { dag[E[0].second].push_back(E[0].first); assert(topoSort(dag).empty()); }
        // Dijkstra vs Floyd z wagami
        WGraph wg(n + 1); vector<vector<ll>> W(n + 1, vector<ll>(n + 1, LLONG_MAX / 4)); vector<tuple<ll,int,int>> edges;
        for (int i = 1; i <= n; i++) W[i][i] = 0;
        for (int a = 1; a <= n; a++) for (int b = 1; b <= n; b++) if (a != b && rng() % 3 == 0) { ll w = rng() % 10; wg[a].push_back({b, w}); W[a][b] = min(W[a][b], w); }
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
        auto dd = dijkstra(wg, 1);
        for (int v = 1; v <= n; v++) assert(dd[v] == (W[1][v] >= LLONG_MAX / 4 ? LLONG_MAX : W[1][v]));
    }
    assert(kruskal(4, {{1, 1, 2}, {2, 2, 3}, {3, 1, 3}, {4, 3, 4}}) == 7);
    assert(gridBfs({"..#", ".##", "..."}, 0, 0, 2, 2) == 4);
    puts("09_grafy: OK");
}
