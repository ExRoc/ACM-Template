template <class Item, class Tag>
class LazySegmentTree {
private:
    int n;
    vector<Item> items;
    vector<Tag> tags;

    void pushUp(int rt) {
        items[rt] = items[rt << 1] + items[rt << 1 | 1];
    }

    void apply(int rt, const Tag& tag) {
        items[rt].apply(tag);
        tags[rt].apply(tag);
    }

    void pushDown(int rt) {
        apply(rt << 1, tags[rt]);
        apply(rt << 1 | 1, tags[rt]);
        tags[rt] = Tag();
    }

    void update(int rt, int l, int r, int idx, const Item& item) {
        if (r - l == 1) {
            items[rt] = item;
            return;
        }
        int m = (l + r) >> 1;
        pushDown(rt);
        if (idx < m) {
            update(rt << 1, l, m, idx, item);
        } else {
            update(rt << 1 | 1, m, r, idx, item);
        }
        pushUp(rt);
    }

    Item query(int rt, int l, int r, int L, int R) {
        if (l >= R || r <= L) {
            return Item();
        }
        if (l >= L && r <= R) {
            return items[rt];
        }
        int m = (l + r) >> 1;
        pushDown(rt);
        return query(rt << 1, l, m, L, R) +
               query(rt << 1 | 1, m, r, L, R);
    }

    void update(int rt, int l, int r, int L, int R, const Tag& tag) {
        if (l >= R || r <= L) {
            return;
        }
        if (l >= L && r <= R) {
            apply(rt, tag);
            return;
        }
        int m = (l + r) >> 1;
        pushDown(rt);
        update(rt << 1, l, m, L, R, tag);
        update(rt << 1 | 1, m, r, L, R, tag);
        pushUp(rt);
    }

    template <class Filter>
    int findFirst(int rt, int l, int r, int L, int R, Filter filter) {
        if (l >= R || r <= L || !filter(items[rt])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) >> 1;
        pushDown(rt);
        int idx = findFirst(rt << 1, l, m, L, R, filter);
        if (idx == -1) {
            idx = findFirst(rt << 1 | 1, m, r, L, R, filter);
        }
        return idx;
    }

    template <class Filter>
    int findLast(int rt, int l, int r, int L, int R, Filter filter) {
        if (l >= R || r <= L || !filter(items[rt])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) >> 1;
        pushDown(rt);
        int res = findLast(rt << 1 | 1, m, r, L, R, filter);
        if (res == -1) {
            res = findLast(rt << 1, l, m, L, R, filter);
        }
        return res;
    }

public:
    LazySegmentTree() : n(0) {}

    template <class Origin>
    LazySegmentTree(int n, Origin unit = Origin()) {
        init(n, unit);
    }

    template <class Origin>
    LazySegmentTree(vector<Origin> origins) {
        init(origins);
    }

    template <class Origin>
    void init(int n, Origin unit = Origin()) {
        init(vector<Origin>(n, unit));
    }

    template <class Origin>
    void init(vector<Origin> origins) {
        n = origins.size();
        items.assign(4 << __lg(n), Item());
        tags.assign(4 << __lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int rt, int l, int r) {
            if (r - l == 1) {
                items[rt] = origins[l];
                return;
            }
            int m = (l + r) >> 1;
            build(rt << 1, l, m);
            build(rt << 1 | 1, m, r);
            pushUp(rt);
        };
        build(1, 0, n);
    }

    void update(int idx, const Item& item) {
        update(1, 0, n, idx, item);
    }

    Item query(int l, int r) {
        return query(1, 0, n, l, r);
    }

    void update(int l, int r, const Tag& tag) {
        return update(1, 0, n, l, r, tag);
    }

    template <class Filter>
    int findFirst(int l, int r, Filter filter) {
        return findFirst(1, 0, n, l, r, filter);
    }

    template <class Filter>
    int findLast(int l, int r, Filter filter) {
        return findLast(1, 0, n, l, r, filter);
    }
};

struct Tag {
    void apply(Tag tag) {}
};

struct Item {
    void apply(Tag tag) {}
};

Item operator+(const Item& a, const Item& b) {}
