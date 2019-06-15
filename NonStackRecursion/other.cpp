#include <iostream>
#include <vector>
#include <tuple>

namespace {
    struct Node {
        Node(int data) : data(data) {}
        Node* left = nullptr;
        Node* right = nullptr;
        int data;
    };

    void traverse(Node* node) {
        if (!node) return;
        traverse(node->left);
        std::cout << node->data << ' ';
        traverse(node->right);
    }
    void traverseIter2(Node* node) {
        std::vector<Node*> stack = { node };
        std::vector<int> returnPointIds = { 0 };

    GOTO:
        if (!node) goto STEP;
        stack.push_back(node);
        node = node->left;
        returnPointIds.push_back(1);
        goto GOTO;
    LABEL_1:
        std::cout << node->data << ' ';

        stack.push_back(node);
        node = node->right;
        returnPointIds.push_back(2);
        goto GOTO;
    LABEL_2:
        {}
    STEP:
        node = stack.back(); stack.pop_back();
        auto returnPointId = returnPointIds.back(); returnPointIds.pop_back();
        switch (returnPointId) {
        case 0: return;
        case 1: goto LABEL_1;
        case 2: goto LABEL_2;
        }
    }
    int traverseSumIter(Node* node) {
        std::vector<std::tuple<Node*>> stackArgs = { std::tuple<Node*>(node) };
        std::vector<std::tuple<int, int, int>> stackLocals = { std::tuple<int, int, int>(0, 0, 0) };
        std::vector<int> returnPointIds = { 0 };
        int sum = 0;
        int left = 0;
        int right = 0;
        int returnValue = 0;
        int returnPointId;
        goto GOTO;
    STEP:
        std::tie(node) = stackArgs.back(); stackArgs.pop_back();
        std::tie(sum, left, right) = stackLocals.back(); stackLocals.pop_back();
        returnPointId = returnPointIds.back(); returnPointIds.pop_back();
        switch (returnPointId) {
        case 0: return returnValue;
        case 1:  goto LABEL_1;
        case 2:  goto LABEL_2;
        }

    GOTO:
        if (!node) {
            returnValue = 0;
            goto STEP;
        }
        sum = node->data;
        stackArgs.emplace_back(node);
        stackLocals.emplace_back(sum, left, right);
        node = node->left;
        returnPointIds.push_back(1);
        goto GOTO;
    LABEL_1:
        sum += returnValue;
        stackArgs.emplace_back(node);
        stackLocals.emplace_back(sum, left, right);
        node = node->right;
        returnPointIds.push_back(2);
        goto GOTO;
    LABEL_2:
        sum += returnValue;
        returnValue = sum;
        goto STEP;
    }

    int traverseSum(Node* node) {
        if (!node) return 0;
        auto sum = node->data;
        auto left = traverseSum(node->left);
        sum += left;
        auto right = traverseSum(node->right);
        sum += right;
        return sum;
    }

    int sum(int n) {
        if (n == 0) return 0;
        auto sumResult = sum(n - 1);
        return 1 + sumResult;
    }

    int partition(std::vector<int>& tab, int start, int end) {
        auto pivot = tab[end];
        int p = start;
        for (int i = start; i <= end; ++i) {
            if (tab[i] < pivot) {
                std::swap(tab[i], tab[p]);
                p += 1;
            }
        }
        std::swap(tab[p], tab[end]);
        return p;
    }

    void quicksort(std::vector<int>& tab, int start, int end) {
        if (end - start > 0) {
            auto p = partition(tab, start, end);
            quicksort(tab, start, p - 1);
            quicksort(tab, p + 1, end);
        }
    }
}