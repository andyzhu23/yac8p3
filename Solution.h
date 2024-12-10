#include <vector>
#include <iostream>
#include <cassert>

struct Solution {

    std::vector<std::vector<int> > children, *ores;
    std::vector<int> freq, atLeastFreq, ans, sz, heavyChild; 

    void dfs(int v) {
        if (children[v].empty()) {
            for (int i : (*ores)[v]) {
                atLeastFreq[++freq[i]]++;
                ans[v] = std::max(ans[v], atLeastFreq[freq[i]] * freq[i]);
            }
            return;
        }
        for (int u : children[v]) {
            if (u != heavyChild[v]) {
                dfs(u);
                for (int i : (*ores)[u]) {
                    atLeastFreq[freq[i]--]--;
                    (*ores)[v].push_back(i);
                }
            }
        }
        dfs(heavyChild[v]);
        ans[v] = ans[heavyChild[v]];
        (*ores)[v].swap((*ores)[heavyChild[v]]);
        for (int i : (*ores)[heavyChild[v]]) {
            (*ores)[v].push_back(i);
            atLeastFreq[++freq[i]]++;
            ans[v] = std::max(ans[v], atLeastFreq[freq[i]] * freq[i]);
        }
    }

    int solve(int n, std::vector<int>& p, std::vector<std::vector<int> >& o, int test_case) {
        children.resize(n + 1);
        freq.resize(1e6 + 1);
        atLeastFreq.resize(2e6 + 1);
        ans.resize(n + 1);
        sz.resize(n + 1);
        heavyChild.resize(n + 1);

        if(test_case <= 36) assert(1 <= n && n <= 1000);
        assert(1 <= n && n <= 1e6);
        printf("%d\n", n);

        for (int i = 1; i <= n; i++) {
            assert(0 <= p[i] && p[i] < i);
            printf("%d%c", p[i], " \n"[i==n]);
            children[p[i]].push_back(i);
        }
        
        int cnt = 0;
        for(int i = 1;i<=n;++i) {
            cnt += o[i].size();
            printf("%d", o[i].size());
            for(int j = 0;j<o[i].size();++j) {
                printf(" %d", o[i][j]);
                assert(1 <= o[i][j] && o[i][j] <= 1e6);
            }
            printf("\n");
        }
        if(test_case <= 36) assert(1 <= cnt && cnt <= 2000);
        assert(cnt <= 2e6);

        for (int i = n; i >= 0; i--) {
            sz[i] = o[i].size();
            int big = 0;
            for (int j : children[i]) {
                sz[i] += sz[j];
                if (sz[j] >= big) {
                    big = sz[j];
                    heavyChild[i] = j;
                }
            }
        }
        ores = &o;
        dfs(0);
        for(int i = 1;i<=n;++i) fprintf(stderr, "%d\n", ans[i]);
        return 0;
    }
};