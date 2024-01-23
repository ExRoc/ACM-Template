void discrete() {
    vector<int> sand;
    // init sand
    sort(sand.begin(), sand.end());
    sand.erase(unique(sand.begin(), sand.end()), sand.end());
    for (int &item : origin) {
        item = lower_bound(sand.begin(), sand.end(), item) - sand.begin();
    }
}
