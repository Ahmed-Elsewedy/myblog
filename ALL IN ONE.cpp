/** حَسْبِيَ اللَّهُ لا إِلَـهَ إِلاَّ هُوَ عَلَيْهِ تَوَكَّلْتُ وَهُوَ رَبُّ الْعَرْشِ الْعَظِيمِ **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define int long long
#define sz(x) int(x.size())
#define PI acos(-1)
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
#define clr(v, d) memset(v, d, sizeof(v))
#define endl "\n"
#define vl vector<ll>
#define vi vector<int>
#define pb push_back
#define MOD ((ll)1e9 + 7)

void M7MDAN_FRAG() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
}

// Dijkstra's algorithm is an algorithm for finding the shortest paths between
// nodes in a graph, which may represent.
const int N = 1e5 + 5;
vector<pair<int, int>> adj[N];
vector<int> cost(N, -1);
void dijkstra(int start) {
  priority_queue<pair<int, int>, deque<pair<int, int>>, greater<pair<int, int>>>
      pq;
  pq.push({0, start});
  while (pq.size()) {
    pair<int, int> p = pq.top();
    pq.pop();
    int node = p.second, nodecost = p.first;
    if (cost[node] != -1) {
      continue;
    }
    cost[node] = nodecost;
    for (auto [node2, cost2] : adj[node]) {
      if (cost[node2] == -1) {
        pq.push({nodecost + cost2, node2});
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
// DSU is a data structure that keeps track of a set of elements partitioned
// into a number of disjoint (non-overlapping) subsets.

struct dsu {
  int parent[N], group[N];
  dsu() {
    for (int i = 0; i < N; i++) {
      parent[i] = i;
      group[i] = 1;
    }
  }
  int find(int i) {
    if (parent[i] == i) {
      return i;
    }
    return parent[i] = find(parent[i]);
  }
  bool samegroup(int x, int y) { return find(x) == find(y); }
  void merge(int x, int y) {
    int leader1 = find(x);
    int leader2 = find(y);
    if (leader1 == leader2) {
      return;
    }
    if (group[leader1] > group[leader2]) {
      parent[leader2] = leader1;
      group[leader1] += group[leader2];
    } else {
      parent[leader1] = leader2;
      group[leader2] += group[leader1];
    }
  }
  int getsize(int x) { return group[find(x)]; }
};

/////////////////////////////////////////////////////////////////

// Fenwick tree is a data structure that can efficiently update elements and
// calculate prefix sums in a table of numbers.

const int N = 1e5 + 5;
struct FenwickTree {
  ll bit[N] = {};
  void add(int idx, ll val) {
    while (idx < N) {
      bit[idx] += val;
      idx += idx & -idx;
    }
  }
  ll query(int idx) {
    ll ret = 0;
    while (idx > 0) {
      ret += bit[idx];
      idx -= idx & -idx;
    }
    return ret;
  }
  ll prefix(int l, int r) { return query(r) - query(l - 1); }
};

/////////////////////////////////////////////////////////////////

// Floyd–Warshall algorithm is an algorithm for finding shortest paths in a
// weighted graph with positive or negative edge weights (but with no negative
// cycles).

template <typename T = int> struct Floyd {

  struct Edge {

    ll u, v, w;

    Edge(int U = 0, int V = 0, int W = 0) { u = U, v = V, w = W; }

    bool operator<(const Edge &e) const { return w < e.w; }
  };

  int n, m;
  vector<vector<T>> dist;
  vector<Edge> edges;
  T DEFAULT;

  Floyd(int N, int M) {
    n = N, m = M, DEFAULT = 1e18;
    dist.assign(n + 10, vector<T>(n + 10, DEFAULT));
    edges.resize(m);
  }

  T operation(T a, T b, T c) { return min(a, b + c); }

  void Get_Data() {
    for (auto &e : edges) {
      cin >> e.u >> e.v >> e.w;
      dist[e.u][e.u] = dist[e.v][e.v] = 0;
      dist[e.u][e.v] = dist[e.v][e.u] =
          min({dist[e.u][e.v], dist[e.v][e.u], e.w});
    }
  }

  void Build_Dist() {
    for (int i = 1; i <= n; i++)
      for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
          dist[u][v] = operation(dist[u][v], dist[u][i], dist[i][v]);
  }
};

/////////////////////////////////////////////////////////////////

// floyd cycle detection algorithm is a pointer algorithm that uses only two
// pointers, which move through the sequence at different speeds.
ll cycle_dfs(ll node) {
  ll to = node;
  ll from = node;

  do {
    to = graph[to];
    from = graph[graph[from]];
  } while (to != from);
  ll cycle = node;
  while (cycle != from) {
    cycle = graph[cycle];
    from = graph[from];
  }
  return cycle;
}
ll start = -1;
for (int i = 1; i <= n; i++) {
  if (!vis[i]) {
    start = cycle_dfs(i);
    if (start != -1) {
      break;
    }
  }
}
vl ans;
ll xd = graph[start];
while (xd != start) {
  ans.pb(xd);
  xd = graph[xd];
}
/////////////////////////////////////////////////////////////////

// graph

struct Graph {

  int n, m, connected_components;
  vector<vector<int>> adj;
  vector<bool> vis;
  vector<int> depth, parent, deg, colour;

  Graph(int N, int M) {
    n = N, m = M;
    connected_components = 0;
    adj = vector<vector<int>>(n + 10);
    vis = vector<bool>(n + 10, false);
    depth = deg = colour = vector<int>(n + 10, 0);
    parent = vector<int>(n + 10, -1);
  }

  void add_edge(int u, int v, bool is_directed = false) {
    adj[u].push_back(v), deg[u]++;
    if (!is_directed)
      adj[v].push_back(u), deg[v]++;
  }

  void remove_edge(int u, int v) {
    adj[u].erase(find(all(adj[u]), v)), adj[v].erase(find(all(adj[v]), u));
  }

  void build_adj(bool is_directed = false) {
    for (int i = 0, u, v; i < m && cin >> u >> v; i++)
      add_edge(u, v, is_directed);
  }

  void dfs(int node, int dep = 0, int par = -1) {
    vis[node] = true, parent[node] = par, depth[node] = dep;
    for (auto &new_node : adj[node])
      if (!vis[new_node])
        dfs(new_node, dep + 1, node);
  }

  bool is_cycle(int node, int par) {
    vis[node] = true;
    for (auto &new_node : adj[node]) {
      if (!vis[new_node]) {
        if (is_cycle(new_node, node))
          return true;
      } else if (new_node != par)
        return true;
    }
    return false;
  }

  void get_path(int node) {
    if (parent[node] == node)
      return;
    cout << node << " ";
    get_path(parent[node]);
  }

  void topology() {
    queue<int> topo;
    vector<int> graph;
    for (int i = 1; i <= n; i++)
      if (deg[i] == 1)
        topo.push(i), deg[i]--;
    while (!topo.empty()) {
      int curr_node = topo.front();
      topo.pop();
      graph.push_back(curr_node);
      for (auto &new_node : adj[curr_node]) {
        deg[new_node]--;
        if (deg[new_node] == 1)
          topo.push(new_node);
      }
    }
    reverse(all(graph));
    cout << graph << "\n";
  }

  int bfs(int from, int to) {
    if (from == to)
      return 0;
    queue<int> BFS;
    depth.assign(n + 10, OO);
    vis[from] = true, depth[from] = 0;
    BFS.push(from);
    while (!BFS.empty()) {
      int sz = sz(BFS);
      while (sz--) {
        int curr_node = BFS.front();
        BFS.pop();
        for (auto &new_node : adj[curr_node]) {
          if (!vis[new_node]) {
            BFS.push(new_node), parent[new_node] = curr_node;
            depth[new_node] = min(depth[new_node], depth[curr_node] + 1);
            vis[new_node] = true;
          }
        }
      }
    }
    return depth[to];
  }

  bool is_Bipartite(int u) {
    for (auto v : adj[u]) {
      if (colour[v] == colour[u])
        return false;
      else if (colour[v] == 0) {
        colour[v] = -colour[u];
        if (!is_Bipartite(v)) {
          return false;
        }
      }
    }
    return true;
  }

  bool is_Bipartite() {
    for (int i = 1; i <= n; i++) {
      if (colour[i] == 0) {
        colour[i] = -1;
        if (!is_Bipartite(i))
          return false;
      }
    }
    return true;
  }
};

/////////////////////////////////////////////////////////////////

// KMP is an algorithm that searches for occurrences of a "word" W within a main
// "text string" S by employing the observation that when a mismatch occurs, the
// word itself embodies sufficient information to determine where the next match
// could begin, thus bypassing re-examination of previously matched characters.

struct KMP {
  int longestPrefix[N] = {};
  vector<int> ans;
  void calcPrefix(string patern) {
    int n = patern.size();
    for (int i = 1, idx = 0; i < n; i++) {
      while (idx > 0 && patern[idx] != patern[i])
        idx = longestPrefix[idx - 1];
      if (patern[i] == patern[idx])
        idx++;
      longestPrefix[i] = idx;
    }
  }
  void kmp(string s, string pat) {
    int n = s.size(), m = pat.size();
    calcPrefix(pat);
    for (int i = 0, idx = 0; i < n; i++) {
      while (idx > 0 && s[i] != pat[idx])
        idx = longestPrefix[idx - 1];
      if (s[i] == pat[idx])
        idx++;
      if (idx == m)
        ans.push_back(i - m + 1), idx = longestPrefix[idx - 1];
    }
  }
};

/////////////////////////////////////////////////////////////////

// MO's algorithm is a general technique to process offline queries of the form:
// "Given a list of elements, process a list of queries on the list of
// elements". The algorithm reorders the queries to facilitate processing them
// in batches, hence the name "MO's algorithm".

const int N = 100005;
const int Q = 100005;
const int SQ = 317;
struct query {
  int l, r, q_idx, block_idx;
  query() {}
  query(int _l, int _r, int _q_idx) {
    l = _l - 1, r = _r - 1, q_idx = _q_idx, block_idx = _l / SQ;
  }
  bool operator<(const query &y) const {
    if (block_idx != y.block_idx) {
      return block_idx < y.block_idx;
    }
    return r < y.r;
  }
};
int n, q, s[N], res = 0, q_ans[Q], f[N], ff[N];
int mx = 0;
query queries[Q];
void add(int idx) {
  // what you need to add
}
void remove(int idx) {
  // what you need to remove
}
void MO_process() {
  sort(queries, queries + q);
  int l = 1, r = 0;
  for (int i = 0; i < q; i++) {
    while (r < queries[i].r)
      add(++r);
    while (r > queries[i].r)
      remove(r--);
    while (l < queries[i].l)
      remove(l++);
    while (l > queries[i].l)
      add(--l);
    q_ans[queries[i].q_idx] = res;
  }
}

/////////////////////////////////////////////////////////////////

// Monotonic_stack is a data structure that stores a list of elements such that
// the maximum value in the list is always at the top, and the next element is
// always smaller than the top element.

struct Monotonic_Stacks {

  Monotonic_Stacks() {}

  template <typename T = int> vector<T> nextGreaterelement(vector<T> &nums) {
    int n = nums.size();
    vector<T> res(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && nums[st.top()] <= nums[i])
        st.pop();
      res[i] = (st.empty() ? n : st.top());
      st.push(i);
    }
    return res;
  }

  template <typename T = int> vector<T> prevGreaterelement(vector<T> &nums) {
    int n = nums.size();
    vector<T> res(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
      while (!st.empty() && nums[st.top()] <= nums[i])
        st.pop();
      res[i] = (st.empty() ? 0 : st.top());
      st.push(i);
    }
    return res;
  }

  template <typename T = int> vector<T> nextSmallerelement(vector<T> &nums) {
    int n = nums.size();
    vector<T> res(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && nums[st.top()] >= nums[i])
        st.pop();
      res[i] = (st.empty() ? n : st.top());
      st.push(i);
    }
    return res;
  }

  template <typename T = int> vector<T> prevSmallerelement(vector<T> &nums) {
    int n = nums.size();
    vector<T> res(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
      while (!st.empty() && nums[st.top()] >= nums[i])
        st.pop();
      res[i] = (st.empty() ? 0 : st.top());
      st.push(i);
    }
    return res;
  }
};

/////////////////////////////////////////////////////////////////

// Ordered_set is a data structure that stores a list of elements such that the
// elements are sorted in ascending order.
#define ordered_set                                                            \
  tree<int, null_type, less<>, rb_tree_tag,                                    \
       tree_order_statistics_node_update> // set

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;
#define ll long long
void myerase(ordered_set &t, int v) {
  int rank = t.order_of_key(v); // Number of elements that are less than v in t
  ordered_set::iterator it = t.find_by_order(
      rank); // Iterator that points to the (rank+1)th element in t
  t.erase(it);
}
/////////////////////////////////////////////////////////////////

// Prefix_sum 2D

template <typename T = int> struct Prefix_2D {

  int n, m;
  vector<vector<T>> prefix;

  Prefix_2D(int N = 0, int M = 0) {
    n = N, m = M;
    prefix.assign(n + 5, vector<T>(m + 5));
  }

  // Get the sum of the number in the rectangle between x1, y1, x2, y2

  T Get_Query(int x1, int y1, int x2, int y2) {
    if (x1 > x2)
      swap(x1, x2);
    if (y1 > y2)
      swap(y1, y2);
    return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] +
           prefix[x1 - 1][y1 - 1];
  }

  void Build_Prefix(vector<vector<T>> &matrix) {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        prefix[i][j] = matrix[i - 1][j - 1] + prefix[i][j - 1] +
                       prefix[i - 1][j] - prefix[i - 1][j - 1];
  }

  void Print_Prefix() {
    for (int i = 1; i <= n; i++, cout << '\n')
      for (int j = 1; j <= m && cout << prefix[i][j] << ' '; j++)
        ;
  }
};

/////////////////////////////////////////////////////////////////

// Segment_tree is a data structure that stores a list of elements such that the
// elements are sorted in ascending order.

struct SegmentTree {
private:
  vector<int> seg;
  int sz, skip = INT_MAX;
  int merge(int a, int b) { return min(a, b); }
  void update(int l, int r, int node, int idx, int val) {
    if (l == r) {
      seg[node] = val;
      return;
    }
    int mid = l + r >> 1;
    if (mid < idx) {
      update(mid + 1, r, 2 * node + 2, idx, val);
    } else {
      update(l, mid, 2 * node + 1, idx, val);
    }
    seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
  }
  int query(int l, int r, int node, int lx, int rx) {
    if (l > rx || r < lx)
      return skip;
    if (l >= lx && r <= rx)
      return seg[node];
    int mid = l + r >> 1;
    int a = query(l, mid, 2 * node + 1, lx, rx);
    int b = query(mid + 1, r, 2 * node + 2, lx, rx);
    return merge(a, b);
  }

public:
  SegmentTree(int n) {
    sz = 1;
    while (sz <= n)
      sz <<= 1;
    seg = vector<int>(sz << 1, skip);
  }
  void update(int idx, int val) { update(0, sz - 1, 0, idx, val); }
  int query(int l, int r) { return query(0, sz - 1, 0, l, r); }
};

/////////////////////////////////////////////////////////////////

// Sparse_table is a data structure that stores a list of elements such that the
// elements are sorted in ascending order.

template <typename T = int, int Base = 0> struct Sparse_Table {

  struct Node {

    ll val;

    Node(ll V = 0) : val(V) {}

    Node operator=(const T &rhs) {
      val = rhs;
      return *this;
    }
  };

  int n, LOG;
  vector<vector<Node>> table;
  vector<int> Bin_Log;
  Node DEFAULT;

  Sparse_Table(const vector<T> &vec) {
    n = sz(vec) - Base, DEFAULT = INF, LOG = __lg(n) + 1;
    table = vector<vector<Node>>(n + 10, vector<Node>(LOG));
    Bin_Log = vector<int>(n + 10);
    for (int i = 2; i <= n; i++)
      Bin_Log[i] = Bin_Log[i >> 1] + 1;
    for (int i = 1; i <= n; i++)
      table[i][0] = vec[i - !Base];
    Build_Table();
  }

  Node operation(const Node &a, const Node &b) { return a.val < b.val ? a : b; }

  void Build_Table() {
    for (int log = 1; log < LOG; log++)
      for (int i = 1; i + (1 << log) - 1 <= n; i++)
        table[i][log] =
            operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
  }

  Node query_1(int L, int R) {
    int log = Bin_Log[R - L + 1];
    return operation(table[L][log], table[R - (1 << log) + 1][log]);
  }

  Node query_log_n(int L, int R) {
    Node answer = DEFAULT;
    for (int log = LOG; log >= 0; log--) {
      if (L + (1 << log) - 1 <= R) {
        answer = operation(answer, table[L][log]);
        L += 1 << log;
      }
    }
    return answer;
  }

  T query(int L, int R, bool overlap = false) {
    return (!overlap ? query_1(L, R) : query_log_n(L, R)).val;
  }
};

/////////////////////////////////////////////////////////////////

// MATH
struct Math {

  Math() {}

  // Greatest common divisors between two numbers

  ll GCD(ll a, ll b) { return (!b ? a : GCD(b, a % b)); }

  // least common multiplication between two numbers

  ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }

  // Get vector with the prime factors of number

  vector<int> prime_factorization(ll n) {
    vector<int> factors;
    while (n % 2 == 0)
      factors.push_back(2), n /= 2;
    for (int i = 3; i <= sqrt(n); i += 2)
      while (n % i == 0)
        factors.push_back(i), n /= i;
    if (n > 2)
      factors.push_back(n);
    return factors;
  }

  // Combination

  ll nCr(ll n, ll r) {
    if (r > n)
      return 0;
    ll p = 1, k = 1;
    if (n - r < r)
      r = n - r;
    // condition for minimum choose
    if (n < 1)
      return 0;
    while (r > 0) {
      p *= n, k *= r;
      ll m = __gcd(p, k);
      p /= m, k /= m, n--, r--;
    }
    return p;
  }

  // Permutation

  ll nPr(ll n, ll r) {
    if (r > n)
      return 0;
    ll npr = 1;
    while (r-- > 0)
      npr *= n--;
    return npr;
  }

  // get a mod for big int

  ll Big_Mod(string s, ll mod) {
    ll res = 0;
    for (auto &c : s)
      res = (res * 10 + (c - '0')) % mod;
    return res;
  }

  // add two number and take mod for them

  void add(ll &a, ll b, ll mod = 1e9 + 7) {
    a += b;
    if (a >= mod)
      a -= mod;
  }

  // multiply two number and take mod for them

  void mul(ll &a, ll b, ll mod = 1e9 + 7) { a = ((a % mod) * (b % mod)) % mod; }

  // b power e in O(log(n))

  ll Bin_Pow(ll b, ll e) {
    ll power = 1;
    while (e) {
      if (e & 1)
        power *= b;
      e >>= 1;
      b *= b;
    }
    return power;
  }

  // b power e % mod in O(log(e))

  ll Bin_Pow(ll b, ll e, ll mod) {
    ll power = 1;
    while (e) {
      if (e & 1)
        mul(power, b, mod);
      e >>= 1;
      mul(b, b, mod);
    }
    return power % mod;
  }

  // b multiply e % mod in O(log(e))

  ll Bin_Mul(ll b, ll e, ll mod) {
    b %= mod;
    ll mult = 0;
    while (e) {
      if (e & 1)
        add(mult, b, mod);
      e >>= 1;
      add(b, b, mod);
    }
    return mult % mod;
  }

  // Check if number is prime or not

  bool is_prime(ll n) {
    if (n < 2 || (n % 2 == 0 && n != 2))
      return false;
    for (int i = 3; i <= sqrt(n); i += 2)
      if (n % i == 0)
        return false;
    return true;
  }

  // get the number of divisors for n

  int number_of_divisors(ll n) {
    int divisors = 0;
    for (int i = 1; i < sqrt(n); i++)
      if (n % i == 0)
        divisors += 2;
    return divisors + (sqrt(n) == (int)sqrt(n));
  }

  // get Summation of divisors for n

  ll sum_of_divisors(ll n) {
    ll sum_divisors = 0;
    for (int i = 1; i < sqrt(n); i++)
      if (n % i == 0)
        sum_divisors += ((n / i) + i);
    ll sq = sqrt(n);
    return sum_divisors + (sq * sq == n ? sq : 0);
  }

  // sum of divisor of number in range [1 ... n]
  ll divisorSum(ll num) {
    ll sum = 0;
    for (ll i = 1; i <= sqrt(num); i++) {
      ll t1 = i * (num / i - i + 1);
      ll t2 = (((num / i) * (num / i + 1)) / 2) - ((i * (i + 1)) / 2);
      sum += t1 + t2;
    }
    return sum;
  }

  // get vector with the divisors for n

  vector<ll> Get_Divisors(ll n) {
    vector<ll> divisors;
    for (int i = 1; i < sqrt(n); i++)
      if (n % i == 0)
        divisors.push_back(i), divisors.push_back(n / i);
    if (sqrt(n) == int(sqrt(n)))
      divisors.push_back(sqrt(n));
    return divisors;
  }

  // print all permutation of an array

  void Print_Permutation(vector<int> &nums) {
    sort(all(nums));
    do {
      for (auto &i : nums)
        cout << i << " ";
      cout << "\n";
    } while (next_permutation(nums.begin(), nums.end()));
  }

  // print all permutation of a string

  void Print_Permutation(string s) {
    sort(all(s));
    do {
      cout << s << "\n";
    } while (next_permutation(s.begin(), s.end()));
  }

  // get the summation between two numbers or the summation between 1 and n

  ll Summation(ll r, ll l = 0) {
    if (l > r)
      swap(l, r);
    return (r * (r + 1) / 2) - (l * (l - 1) / 2);
  }

  // Get how many number divisable by c between a and b

  ll how_many_divisors(ll a, ll b, ll c) { return (b / c) - ((a - 1) / c); }

  // Get summation of numbers divisable by c between a and b

  ll Summation_of_Devisors(ll a, ll b, ll c) {
    ll right = Summation(b / c);
    ll left = Summation((a - 1) / c);
    return (right - left) * c;
  }

  // get logb(a)

  double get_log(ll a, int b) { return log(a) / log(b); }

  // Check if number power of another or not

  bool is_power(ll number, int base = 2) {
    return (get_log(number, base) - (ll)get_log(number, base) <= EPS);
  }

  // Distination Between two points

  double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  }

  // Check if it valid triangle with 3 length sides

  bool is_triangle(ll a, ll b, ll c) {
    return (a + b > c) && (a + c > b) && (b + c > a) && (a && b && c);
  }

  // Get Slope of two points

  double slope(double x1, double y1, double x2, double y2) {
    if (x2 == x1)
      return 0;
    return (y2 - y1) / (x2 - x1);
  }

  // Check if three points in the same line

  bool is_same_line(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    return (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1);
  }

  // Check if is perfect square

  bool is_perfect_square(ll n) {
    ll sq = sqrt(n);
    return sq * sq == n;
  }

  // number of coprime witn n from 1 to n

  ll phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        while (n % i == 0)
          n /= i;
        result -= result / i;
      }
    }
    if (n > 1)
      result -= result / n;
    return result;
  }

  // get the power of prime factor in n
  ll FactN_PrimePowers(ll n, ll p) {
    ll powers = 0;
    for (ll i = p; i <= n; i *= p)
      powers += n / i;
    return powers;
  }

  // Convert Decimal to any base

  string decimal_to_any_base(ll decimal, ll base) {
    if (decimal == 0)
      return "0";
    string num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    do {
      result.push_back(num[decimal % base]);
      decimal /= base;
    } while (decimal != 0);
    return string(result.rbegin(), result.rend());
  }

  // Convert any base to decimal

  ll any_base_to_decimal(string str, int base) {
    auto val = [](char c) {
      return (c >= '0' && c <= '9' ? (int)c - '0' : (int)c - 'A' + 10);
    };
    ll len = sz(str), power = 1, num = 0, i;
    for (i = len - 1; i >= 0; i--) {
      num += val(str[i]) * power;
      power = power * base;
    }
    return num;
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SEIVE
template <typename T = int> struct Seive {

  vector<bool> is_prime;
  vector<T> primes;

  Seive(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= sqrt(n); i++)
      if (is_prime[i])
        for (ll j = i * i; j <= n; j += i)
          is_prime[j] = false;
  }

  // Build vector with prime numbers

  void get_primes(int n) {
    for (int i = 1; i <= n; i++)
      if (is_prime[i])
        primes.push_back(i);
  }

  // Print the prime numbers

  void print_primes() {
    for (auto &p : primes)
      cout << p << " ";
    cout << "\n";
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FACTORIZATION
struct Factorization {

  int n;
  vector<int> factors_cnt, prime_factors_cnt;
  vector<vector<int>> factors, prime_factors;

  Factorization(int N) {
    n = N;
    factors_cnt = vector<int>(n + 5, 2);
    prime_factors_cnt = vector<int>(n + 5);
    factors = vector<vector<int>>(n + 5);
    prime_factors = vector<vector<int>>(n + 5);
    factorization(n);
    prime_factorization(n);
  }

  // Get the number of factors for each number
  void factorization() {
    factors_cnt[0] = 0, factors_cnt[1] = 1;
    for (int i = 2; i <= n; i++)
      for (int j = i + i; j <= n; j += i) {
        factors_cnt[j]++;
        factors[j].push_back(i);
      }
  }

  // get the number of factors of n
  int get_factors(int x) { return factors_cnt[x]; }

  // get the factors of n
  vector<int> get_factors() { return factors[n]; }

  // Get the number of prime factors for each number
  void prime_factorization() {
    for (int i = 2; i <= n; i++) {
      if (!prime_factors[i]) {
        for (int j = i; j <= n; j += i) {
          prime_factors[j]++;
          prime_factors[j].push_back(i);
        }
      }
    }
  }

  // get the number of prime factors of n
  int get_prime_factors(int x) { return prime_factors[x]; }

  // get the prime factors of n
  vector<int> get_prime_factors(int x) { return prime_factors[x]; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
