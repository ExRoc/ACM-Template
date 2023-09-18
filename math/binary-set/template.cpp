inline int getBit(int a, int b) {
	return (a >> b) & 1;
}

inline int lowbit(int x) {
    return x & -x;
}

inline int nextSameHammingWeightNumber(int x) {
    int t = x + lowbit(x);
    return t | (((lowbit(t) / lowbit(x)) >> 1) - 1);
}

inline bool isPowerOfTwo(int n) {
	return n > 0 && (n & (n - 1)) == 0;
}

inline int nextSubMask(int subMask, int mask) {
	return (subMask - 1) & mask;
}