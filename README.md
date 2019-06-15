# NonStackRecursion
Normally recursive code relies on compiler/processor to create call stack frames for each function call, which, as the name suggests, puts everthing on the stack. There is no way to redirect it to the heap memory, so in case of limited stack space and deep enough recursion you will get stack overflow.

There are 2 obvious ways to combat that stack overflow:
- increase the stack size
- rewrite code so that it's not recursive

The problem with code rewriting is that there is no easy generalized way of removing recursivness from a function. It also usually makes the function less readable.

This solution lets you leave the function code basicly untouched (so it still looks like its recursive), but it uses std::vector<> (so heap memory) instead of the stack to create the call stack.
It requires some changes to the code, but outside of required additional lines of code at the start and at the end of the function, the code itself is similar.

For example quicksort function that looks like this:
```C++
if (end - start > 0) {
    p = partition(tab, start, end);
    quicksort(tab, start, p - 1);
    quicksort(tab, p + 1, end);
}
```

Has to be written as:
```C++
if (end - start > 0) {
    p = partition(tab, start, end);
    STACK_CALL(quicksort, 1, tab, start, p - 1);
    STACK_CALL(quicksort, 2, tab, p + 1, end);
}
STACK_RETURN(0);
```

Or recursive fibbonacci:
```C++
if (n <= 2) {
    return 1;
}
int f1 = fib(n - 1);
int f2 = fib(n - 2);
return f1 + f2;
```
Has to be written as:
```C++
if (n <= 2) {
    STACK_RETURN(1);
}
STACK_CALL(fib, 1, n - 1);
f1 = RETURN_VALUE;
STACK_CALL(fib, 2, n - 2);
f2 = RETURN_VALUE;
STACK_RETURN(f1 + f2);
```

For this to work properly you need to have 6 #defines and 1 macro call before the code and 1 macro call at the end. For example full example of fibonacci looks like this:
```C++
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
```
Those additional lines are mostly needed for STACK_CALL macros to be able to save all argument and local variables in our own call stack.
