#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int profit;
    int weight;
};

bool compare(Item a, Item b) {
    double ratio1 = (double)a.profit / a.weight;
    double ratio2 = (double)b.profit / b.weight;
    return ratio1 > ratio2;
}

class Node {
public:
    int level;
    int profit;
    int weight;
    double bound;

    Node() {}
    Node(int l, int p, int w) : level(l), profit(p), weight(w) {}
};

int bound(Node u, int n, int W, vector<Item>& items) {
    if (u.weight >= W) return 0;

    int profit_bound = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;

    while (j < n && total_weight + items[j].weight <= W) {
        total_weight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n) {
        profit_bound += (W - total_weight) * (double)items[j].profit / items[j].weight;
    }

    return profit_bound;
}

int knapsack(int W, vector<Item>& items, int n) {
    sort(items.begin(), items.end(), compare);

    vector<Node> queue;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    queue.push_back(u);

    int maxProfit = 0;

    while (!queue.empty()) {
        u = queue.back();
        queue.pop_back();

        if (u.level == -1) v.level = 0;
        if (u.level == n - 1) continue;

        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].profit;

        if (v.weight <= W && v.profit > maxProfit) {
            maxProfit = v.profit;
        }

        v.bound = bound(v, n, W, items);

        if (v.bound > maxProfit) {
            queue.push_back(v);
        }

        v.weight = u.weight;
        v.profit = u.profit;

        v.bound = bound(v, n, W, items);

        if (v.bound > maxProfit) {
            queue.push_back(v);
        }
    }

    return maxProfit;
}

int main() {
    int W, n;
    cout << "Enter bag weight: " << endl;
    cin >> W;
    cout << "Enter the number of objects: " << endl;
    cin >> n;

    vector<Item> items;

    for (int i = 0; i < n; i++) {
        int profit, weight;
        cout << "Enter profit " << i + 1 << ": " << endl;
        cin >> profit;
        cout << "Enter weight " << i + 1 << ": " << endl;
        cin >> weight;
        items.push_back({profit, weight});
    }

    int maxProfit = knapsack(W, items, n);
    cout << "The maximum value that can be obtained is: " << maxProfit << endl;

    return 0;
}
