// https://www.luogu.com.cn/problem/P1225
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (1 << 16) + 100;
struct Node {
    int preStatus;
    int s, t;

    Node() {}

    Node(int ss, int tt, int p) {
        s = ss;
        t = tt;
        preStatus = p;
    }
};

int ss, tt;
char s[10][10], t[10][10];
bool vis[maxn];
Node node[maxn];
queue<int> que;
const int dir[4][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

int getX(int id) {
    return id / 4;
}

int getY(int id) {
    return id % 4;
}

int id(int x, int y) {
    return x * 4 + y;
}

bool in(int x, int y) {
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

int getStatus(char s[10][10]) {
    int status = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (s[i][j] == '1') {
                status |= (1 << id(i, j));
            }
        }
    }
    return status;
}

int get(int status, int dig) {
    return (status >> dig) & 1;
}

int get(int status, int x, int y) {
    return get(status, id(x, y));
}

int st(int status, int dig, int x) {
    status -= (get(status, dig) << dig);
    status |= (x << dig);
    return status;
}

int st(int status, int x, int y, int xx) {
    return st(status, id(x, y), xx);
}

int swap(int status, int dig1, int dig2) {
    int x1 = get(status, dig1);
    int x2 = get(status, dig2);
    status = st(status, dig1, x2);
    status = st(status, dig2, x1);
    return status;
}

int swap(int status, int x1, int y1, int x2, int y2) {
    return swap(status, id(x1, y1), id(x2, y2));
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    for (int i = 0; i < 4; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < 4; ++i) {
        cin >> t[i];
    }
    ss = getStatus(s);
    tt = getStatus(t);
    vis[ss] = true;
    node[ss] = Node(-1, -1, -1);
    que.push(ss);
    while (!que.empty()) {
        int tmp = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int x = i + dir[k][0];
                    int y = j + dir[k][1];
                    if (in(x, y) && get(tmp, i, j) != get(tmp, x, y)) {
                        int ttmp = swap(tmp, i, j, x, y);
                        if (!vis[ttmp]) {
                            que.push(ttmp);
                            node[ttmp] = Node(id(i, j), id(x, y), tmp);
                            vis[ttmp] = true;
                        }
                    }
                }
            }
        }
    }
    vector<string> ans;
    int tmp = tt;
    while (tmp != ss) {
        string tmps;
        tmps += ((char)(getX(node[tmp].s) + 1 + '0'));
        tmps += ((char)(getY(node[tmp].s) + 1 + '0'));
        tmps += ((char)(getX(node[tmp].t) + 1 + '0'));
        tmps += ((char)(getY(node[tmp].t) + 1 + '0'));
        tmp = node[tmp].preStatus;
        ans.push_back(tmps);
    }
    cout << ans.size() << endl;
    while (!ans.empty()) {
        cout << ans.back() << endl;
        ans.pop_back();
    }

    return 0;
}