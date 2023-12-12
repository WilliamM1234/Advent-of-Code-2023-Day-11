#include <bits/stdc++.h> // build and run w/ crtl + f9 followed by crtl + f10
using namespace std;

#define ll long long
#define all(a) (a).begin(), (a).end()
#define MP(a,b) make_pair(a,b)
#define pb(a) push_back(a)

int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}
int lcm(int a, int b) {return a * (b / gcd(a, b));}

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}
ll lcm(ll a, ll b) {return a * (b / gcd(a, b));}

int main() { // int32_t for large numbers, codeforces: GNU G++20 11.2.0 (64 bit, winlibs)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<string> g;
    ll exp_factor = 1e6;
    exp_factor--;
    while (true) {
        string s;
        cin >> s;
        if (s=="poo") {
            break;
        }
        g.pb(s);
    }
    ll rs = g.size(), cs = g[0].length(), cnt = 1;
    vector<pair<ll, ll>> rv, cv;
    rv.pb(MP(0, 0));
    cv.pb(MP(0, 0));
    int rc[rs], cc[cs];
    memset(rc, 0, sizeof(rc));
    memset(cc, 0, sizeof(cc));
    vector<pair<ll, ll>> rd, cd;
    for (ll r = 0; r < rs; r++) {
        for (ll c = 0; c < cs; c++) {
            if (g[r][c]=='#') {
                rc[r]++;
                cc[c]++;
                rv.pb(MP(r, cnt));
                cv.pb(MP(c, cnt));
                cnt++;
            }
        }
    }
    sort(all(cv));

    for (ll i = 1; i < rv.size(); i++) {
        rd.pb(MP(rv[i].first - rv[i-1].first, rv[i].second));
    }
    for (ll i = 1; i < cv.size(); i++) {
        cd.pb(MP(cv[i].first - cv[i-1].first, cv[i].second));
    }

    vector<ll> ers;
    for (ll r = 0; r < rs; r++) {
        bool ok = false;
        for (ll c = 0; c < cs; c++) {
            if (g[r][c]=='#') {
                ok = true;
            }
        }
        if (!ok) {
            ers.pb(r);
        }
    }

    vector<ll> ecs;
    for (ll c = 0; c < cs; c++) {
        bool ok = false;
        for (ll r = 0; r < rs; r++) {
            if (g[r][c]=='#') {
                ok = true;
            }
        }
        if (!ok) {
            ecs.pb(c);
        }
    }
    ll rcp[rs+1], ccp[cs+1];
    rcp[0] = 0;
    ccp[0] = 0;
    for (ll i = 1; i <= rs; i++) {
        rcp[i] = rc[i-1] + rcp[i-1];
    }
    for (ll i = 1; i <= cs; i++) {
        ccp[i] = cc[i-1] + ccp[i-1];
    }
    for (auto er: ers) {
        rd[rcp[er+1]].first += exp_factor;
    }
    for (auto ec: ecs) {
        cd[ccp[ec+1]].first += exp_factor;
    }
    vector<pair<ll,ll>> gc(rd.size());
    gc[rd[0].second-1].first = rd[0].first;
    for (ll i = 1; i < rd.size(); i++) {
        gc[rd[i].second-1].first = rd[i].first + gc[rd[i-1].second-1].first;
    }
    gc[cd[0].second-1].second = cd[0].first;
    for (ll i = 1; i < cd.size(); i++) {
        gc[cd[i].second-1].second = cd[i].first + gc[cd[i-1].second-1].second;
    }
    vector<pair<ll,ll>> crds;
    for (auto p: gc) {
        crds.pb(MP(p.first, p.second));
    }
    ll ans = 0;
    for (ll i = 0; i < crds.size(); i++) {
        for (ll j = i+1; j < crds.size(); j++) {
            ans += abs(crds[i].first-crds[j].first) + abs(crds[i].second-crds[j].second);
        }
    }
    cout << ans;
}

// cout << fixed << n << setprecision(d);
// double a or b --> ans = ceil(a/b);
// 1e9=10^9
// memset(arr, 0, sizeof(arr)); --> fast; sets all values in arr to 0 (only works for 0)
// fill(arr, arr[i]+sizeof(arr)/sizeof(arr[0]), x); --> slower; sets all values in arr to any value x
// # of multiples of x in given bounds a and b (inclusive): b/x-(a-1)/x where a < b
//
// learn flush for interactive problems
