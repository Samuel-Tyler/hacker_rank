#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#include "print_container.hpp"

using namespace std;

int main() {
    int n;
    int m;
    int x;
    int k;
    cin >> n >> m >> x >> k;
    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++){
       cin >> a[a_i];
    }
    vector<int> b(m);
    for(int b_i = 0; b_i < m; b_i++){
       cin >> b[b_i];
    }
    std::set<int,  std::less<int>> L;
    std::cout << "k = " << k << std::endl;
     std::cout << "possible iterations = " << std::min(n, m - x) * m << std::endl;
    for (int i = 0; i < std::min(n, m - x); i++)
    {
        for (int j = x + i; j < m; j++)
        {
            L.insert(a[i] * b[j]);
        }
     std::cout << "Done = " << i << " of " << std::min(n, m - x) << std::endl;
    }

    int i = 0;
    for (const auto& item : L)
    {
        if (++i == k)
        {
            std::cout << item;
            break;
        }
    }
    return 0;
}
