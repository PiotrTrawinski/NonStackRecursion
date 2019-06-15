#include <iostream>
#include <vector>
#include <tuple>

#define STACK_END_1_ case 1: goto LABEL_1; 
#define STACK_END_2_ STACK_END_1_ case 2: goto LABEL_2; 
#define STACK_END_3_ STACK_END_2_ case 3: goto LABEL_3; 
#define STACK_END_4_ STACK_END_3_ case 4: goto LABEL_4; 
#define STACK_END_5_ STACK_END_4_ case 5: goto LABEL_5; 
#define STACK_END_6_ STACK_END_5_ case 6: goto LABEL_6; 
#define STACK_END_7_ STACK_END_6_ case 7: goto LABEL_7; 
#define STACK_CREATE(FUN_NAME, NUMBER) \
    std::vector<std::tuple<FUN_NAME##_ARG_TYPES>> STACK_ARGS__; \
    STACK_ARGS__.emplace_back(FUN_NAME##_ARG_NAMES); \
    std::vector<std::tuple<FUN_NAME##_LOCAL_TYPES>> STACK_LOCALS__; \
    STACK_LOCALS__.emplace_back(FUN_NAME##_LOCAL_VALS); \
    auto [FUN_NAME##_LOCAL_NAMES] = STACK_LOCALS__.back(); \
    std::vector<int> RETURN_POINT_IDS__ = { 0 }; \
    FUN_NAME##_RETURN_TYPE RETURN_VALUE__; \
    int RETURN_POINT_ID__; \
    goto GOTO; \
STEP: \
    std::tie(FUN_NAME##_ARG_NAMES) = STACK_ARGS__.back(); STACK_ARGS__.pop_back(); \
    std::tie(FUN_NAME##_LOCAL_NAMES) = STACK_LOCALS__.back(); STACK_LOCALS__.pop_back(); \
    RETURN_POINT_ID__ = RETURN_POINT_IDS__.back(); RETURN_POINT_IDS__.pop_back();\
    switch (RETURN_POINT_ID__) {\
    case 0: return RETURN_VALUE__;\
    STACK_END_##NUMBER##_ \
    } \
GOTO:
#define STACK_RETURN(VALUE) do { RETURN_VALUE__ = VALUE; goto STEP; } while(false)
#define STACK_CALL(FUN_NAME, NUMBER, ...) do {\
    STACK_ARGS__.emplace_back(FUN_NAME##_ARG_NAMES); \
    STACK_LOCALS__.emplace_back(FUN_NAME##_LOCAL_NAMES); \
    std::tie(FUN_NAME##_ARG_NAMES) = std::tuple(__VA_ARGS__); \
    RETURN_POINT_IDS__.push_back(NUMBER); \
    goto GOTO; \
    LABEL_##NUMBER: {}\
} while (false)
#define STACK_END() do { goto STEP; } while(false)
#define RETURN_VALUE RETURN_VALUE__



struct Node {
    Node(int data) : data(data) {}
    Node* left = nullptr;
    Node* right = nullptr;
    int data;
};

uint64_t traverseSum(Node* node) {
    #define traverseSum_LOCAL_TYPES uint64_t, uint64_t,  uint64_t
    #define traverseSum_LOCAL_NAMES sum,      left,      right
    #define traverseSum_LOCAL_VALS  0,        0,         0
    #define traverseSum_ARG_TYPES Node*
    #define traverseSum_ARG_NAMES node
    #define traverseSum_RETURN_TYPE uint64_t
    STACK_CREATE(traverseSum, 2);

    // real algorithm start
    if (!node) {
        STACK_RETURN(0);
    }
    sum = node->data;
    STACK_CALL(traverseSum, 1, node->left);
    sum += RETURN_VALUE;
    STACK_CALL(traverseSum, 2, node->right);
    sum += RETURN_VALUE;
    STACK_RETURN(sum);
    // real algorithm end

    STACK_END();
}

int sum(int n) {
    #define sum_LOCAL_TYPES int
    #define sum_LOCAL_NAMES _
    #define sum_LOCAL_VALS 0
    #define sum_ARG_TYPES int
    #define sum_ARG_NAMES n
    #define sum_RETURN_TYPE int
    STACK_CREATE(sum, 1);

    // real algorithm start
    if (n == 0) STACK_RETURN(0);
    STACK_CALL(sum, 1, n-1);
    STACK_RETURN(1 + RETURN_VALUE);
    // real algorithm end

    STACK_END();
}

template <typename T> int partition(std::vector<T>& tab, int start, int end) {
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

template <typename T> int quicksort(std::vector<T>& tab, int start, int end) {
    #define quicksort_LOCAL_TYPES int
    #define quicksort_LOCAL_NAMES p
    #define quicksort_LOCAL_VALS 0
    #define quicksort_ARG_TYPES std::vector<int>&, int, int
    #define quicksort_ARG_NAMES tab, start, end
    #define quicksort_RETURN_TYPE int
    STACK_CREATE(quicksort, 2);

    // real algorithm start
    if (end - start > 0) {
        p = partition(tab, start, end);
        STACK_CALL(quicksort, 1, tab, start, p - 1);
        STACK_CALL(quicksort, 2, tab, p + 1, end);
    }
    STACK_RETURN(0);
    // real algorithm end

    STACK_END();
}
template <typename T> void quicksort(std::vector<T>& tab) {
    quicksort(tab, 0, tab.size() - 1);
}

int fib(int n) {
    #define fib_LOCAL_TYPES int, int
    #define fib_LOCAL_NAMES f1, f2
    #define fib_LOCAL_VALS 0, 0
    #define fib_ARG_TYPES int
    #define fib_ARG_NAMES n
    #define fib_RETURN_TYPE int
    STACK_CREATE(fib, 2);

    // real algorithm start
    if (n <= 2) {
        STACK_RETURN(1);
    }
    STACK_CALL(fib, 1, n - 1);
    f1 = RETURN_VALUE;
    STACK_CALL(fib, 2, n - 2);
    f2 = RETURN_VALUE;
    STACK_RETURN(f1 + f2);
    // real algorithm end

    STACK_END();
}

uint64_t traverseSumRecursive(Node* node) {
    if (!node) {
        return 0;
    }
    uint64_t sum = node->data;
    sum += traverseSumRecursive(node->left);
    sum += traverseSumRecursive(node->right);
    return sum;
}

Node* createTree() {
    Node* root;
    root = new Node(5);
    root->left = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->left->right->right = new Node(4);
    root->right = new Node(8);
    root->right->left = new Node(7);
    root->right->left->left = new Node(6);
    root->right->right = new Node(9);
    root->right->right->right = new Node(10);
    return root;
}
Node* createBigTree() {
    Node* root = new Node(0);
    Node* node = root;
    for (int i = 0; i < 500000; ++i) {
        node->right = new Node(i);
        node = node->right;
    }
    node = root;
    for (int i = 0; i < 500000; ++i) {
        node->left = new Node(i);
        node = node->left;
    }
    return root;
}
template<typename T> std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    out << '[';
    for (auto& elem : vec) {
        out << elem << ' ';
    }
    out << ']';
    return out;
}

int main() {
    // sum
    std::cout << "sum(10) = " << sum(10) << '\n';
    std::cout << '\n';

    // traverseSum
    auto root = createTree();
    std::cout << "traverseSum(root) = " << traverseSum(root) << '\n';
    std::cout << '\n';

    // quicksort
    std::vector<int> vec = { 9, 3, 7, 1, 8, 2, 4, 6, 5 };
    std::cout << "before quicksort = " << vec << '\n';
    quicksort(vec);
    std::cout << "after quicksort = " << vec << '\n';
    std::cout << "fib(30) = " << fib(30) << '\n';
    std::cout << '\n';

    // traverseSum on unbalanced tree
    auto bigTreeRoot = createBigTree();
    std::cout << "stack overflow test:\n";
    std::cout << "iterative = " << traverseSum(bigTreeRoot) << '\n'; // no stack overflow
    std::cout << "recursive = " << traverseSumRecursive(bigTreeRoot) << '\n'; // here stack overflow
    std::cout << '\n';
    
    return 0;
}