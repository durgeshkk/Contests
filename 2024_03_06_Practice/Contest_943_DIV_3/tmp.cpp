#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long base = 31;
long long mod = 1000000007;

long long computeHash(const string& s) {
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * base) % mod;
    }
    return hash_value;
}

vector<int> computeLCP(const string& s, int k) {
    int n = s.size();
    vector<int> lcp(n - k + 1);

    vector<long long> hashes(n + 1);
    vector<long long> p_pow(n + 1);
    p_pow[0] = 1;
    for (int i = 0; i < n; ++i) {
        hashes[i + 1] = (hashes[i] + (s[i] - 'a' + 1) * p_pow[i]) % mod;
        p_pow[i + 1] = (p_pow[i] * base) % mod;
    }

    for (int i = 0; i < n - k + 1; ++i) {
        long long hash1 = (hashes[i + k] + mod - hashes[i]) % mod;
        long long hash2 = (hashes[i + k] + mod - hashes[i + 1] * p_pow[k] % mod) % mod;
        if (hash1 == hash2) {
            lcp[i] = min(k, n - i);
        } else {
            int low = 0, high = k - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                long long hash1 = (hashes[i + mid + 1] + mod - hashes[i]) % mod;
                long long hash2 = (hashes[i + mid + 1] * p_pow[mid + 1] % mod + mod - hashes[i + 1] * p_pow[mid + 1] % mod) % mod;
                if (hash1 == hash2)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            lcp[i] = low;
        }
    }
    return lcp;
}

int main() {
    string s = "abababcab";
    int k = 4;

    vector<int> max_lcps = computeLCP(s, k);
    for (int lcp : max_lcps) {
        cout << lcp << " ";
    }
    cout << endl;

    return 0;
}
