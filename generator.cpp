#include <vector>
#include <random>
#include <cassert>
#include "Solution.h"

std::mt19937 rng(0);
#define random(a, b) (rng() % (b - a + 1) + a)

int main(int argc, char **argv) {
    using namespace std;
    int N, T, Msum;
    vector<int> p;
    vector<vector<int> > o;
    int tot = 40;
    int test_case = atoi(argv[1]);
    rng.seed(test_case);
    T = 1e6;
    if(test_case <= tot) {
        N = 1000;
        Msum = 2000;
    } else {
        N = 1e6;
        Msum = 2e6;
    }
    p.resize(N + 1);
    if(test_case % tot == 0 || (tot < test_case && test_case <= tot * 2)) {
        // tree is a chain
        for(int i = 1;i<=N;++i) p[i] = i - 1;
    } else if(test_case % tot == 1) {
        // tree is a star
        for(int i = 1;i<=N;++i) p[i] = 0;
    } else if(test_case % tot == 2) {
        // all chambers are connected to 1 other than 0
        p[1] = 0;
        for(int i = 2;i<=N;++i) p[i] = 1;
    } else if(test_case % tot <= 10) {
        // single random tree
        p[1] = 0;
        for(int i = 2;i<=N;++i) p[i] = random(1, i - 1);
    } else if(test_case % tot <= 15) {
        // random forest
        for(int i = 1;i<=N;++i) p[i] = random(0, i - 1);
    } else if(test_case % tot <= 20) {
        // one tree with larger depth
        p[1] = 0;
        for(int i = 2;i<=N;++i) p[i] = random(max(1, i - 50), i - 1);
    } else if(test_case % tot <= 25) {
        // multiple trees with larger depth
        p[1] = 0;
        for(int i = 2;i<=N;++i) p[i] = rng() % (tot * 100) == 0 ? 0 : random(max(0, i - 50), i - 1);
    } else if(test_case % tot <= 26) {
        // binary tree
        p[1] = 0;
        for(int i = 2;i<=N;++i) p[i] = i / 2;
    } else if(test_case % tot <= 35) {
        // one subtree has significantly more children
        p[1] = 0;
        vector<int> hson(N + 1), nodes;
        nodes.push_back(1);
        int rand = (test_case - 26) * 100 / random(1, 10);
        for(int i = 2;i<=N;++i) {
            if(random(1, random(1, rand)) == 1) {
                // 1/1000 nodes randomly append
                p[i] = random(1, i - 1);
            } else {
                // otherwise randomly append to a heavy child
                p[i] = nodes[random(0, nodes.size() - 1)];
                if(hson[p[i]] == 0) {
                    hson[p[i]] = i;
                    nodes.push_back(i);
                }
            }
        }
    } else if(test_case % tot <= 40) {
        // random forest
        for(int i = 1;i<=N;++i) p[i] = random(0, i - 1);
    }

    o.resize(N + 1);
    if(test_case % tot == 0) {
        // every chamber has Msum / N ores
        for(int i = 1;i<=N;++i) {
            o[i].resize(random(0, Msum / N));
            for(int& x : o[i]) x = random(1, T);
        }
    } else if(test_case % tot <=5) {
        // ores concentrated along nodes with smaller indexes
        for(int i = 1;i<=N;++i) {
            o[i].resize(random(0, Msum));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, T);
        }
    } else if(test_case % tot <= 10) {
        // ores concentrated along nodes with bigger indexes
        for(int i = N;i;--i) {
            o[i].resize(random(0, Msum));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, T);
        }
    } else if(test_case % tot <= 15) {
        // all ores are at node N
        o[N].resize(Msum);
        for(int& x : o[N]) x = random(1, T);
    } else if(test_case % tot == 16) {
        Msum = min(Msum, T);
        int cnt = Msum;
        // all ores are unique, quadratic distrubution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = cnt--;
        }
    } else if(test_case % tot == 17) {
        // all ores are of type 1, quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = 1;
        }
    } else if(test_case % tot == 18) {
        // quadratic distrubution on T and Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) {
                double tmp = random(0, T * 1000) / 1000.0;
                x = (int)(tmp * tmp / T);
                if(x == 0) x = 1;
            }
        }
    } else if(test_case % tot == 19) {
        // only ores of type [1, 10], quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 10);
        }
    } else if(test_case % tot == 20) {
        // only ores of type [1, 100], quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 100);
        }
    } else if(test_case % tot == 21) {
        // all ores are of type 1, each node have size of max 10
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(10, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = 1;
        }
    } else if(test_case % tot == 22) {
        // quadratic distrubution on T, each node have size of max 10000
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(10000, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]){
                double tmp = random(0, T * 1000) / 1000.0;
                x = (int)(tmp * tmp / T);
                if(x == 0) x = 1;
            }
        }
    } else if(test_case % tot == 23) {
        // only ores of type [1, 10], each node have size of max 1000
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(1000, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 10) * T / 100;
        }
    } else if(test_case % tot == 24) {
        // only ores of type [1, 100], each node have size of max 100
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(100, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 100) * T / 100;
        }
    } else if(test_case % tot == 25) {
        Msum = min(Msum, T);
        int cnt = 0;
        // all ores are unique, quadratic distrubution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = ++cnt;
        }
    } else if(test_case % tot == 26) {
        Msum = min(Msum, T);
        int cnt = Msum;
        // all ores are unique, quadratic distrubution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = cnt--;
        }
    } else if(test_case % tot == 27) {
        // all ores are of type 1, quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = 1;
        }
    } else if(test_case % tot == 28) {
        // quadratic distrubution on T and Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) {
                double tmp = random(0, T * 1000) / 1000.0;
                x = (int)(tmp * tmp / T);
                if(x == 0) x = 1;
            }
        }
    } else if(test_case % tot == 29) {
        // only ores of type [1, 10], quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 10);
        }
    } else if(test_case % tot == 30) {
        // only ores of type [1, 100], quadratic distribution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 100);
        }
    } else if(test_case % tot == 31) {
        // all ores are of type 1, each node have size of max 10
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(10, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = 1;
        }
    } else if(test_case % tot == 32) {
        // quadratic distrubution on T, each node have size of max 10
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(100, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) {
                double tmp = random(0, T * 1000) / 1000.0;
                x = (int)(tmp * tmp / T);
                if(x == 0) x = 1;
            }
        }
    } else if(test_case % tot == 33) {
        // only ores of type [1, 10], each node have size of max 1000
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(1000, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 10);
        }
    } else if(test_case % tot == 34) {
        // only ores of type [1, 100], each node have size of max 100
        for(int i = N;i;--i) {
            o[i].resize(random(0, min(100, Msum)));
            Msum -= o[i].size();
            for(int& x : o[i]) x = random(1, 100);
        }
    } else if(test_case % tot == 35) {
        Msum = min(Msum, T);
        int cnt = 0;
        // all ores are unique, quadratic distrubution on Msum
        for(int i = N;i;--i) {
            if(Msum > 0) {
                double tmp = random(0, Msum * 1000) / 1000.0;
                o[i].resize((int)(tmp * tmp / Msum));
            }
            Msum -= o[i].size();
            for(int& x : o[i]) x = ++cnt;
        }
    } else if(test_case % tot <= 40) {
        // sqrt N ores in sqrt N nodes
        // all ores are at node N
        for(int i = N;i;--i) {
            o[i].push_back(i);
            --Msum;
            if(Msum == 0) break;
            for(int x : o[i]) {
                --Msum;
                o[p[i]].push_back(x);
                if(Msum == 0) break;
            }
            if(Msum == 0) break;
        }
    }
    Solution sol;
    assert(sol.solve(N, p, o, test_case) == 0);
    return 0;
}

