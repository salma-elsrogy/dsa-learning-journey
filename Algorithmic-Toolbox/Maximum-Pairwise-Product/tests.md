# Test Cases

The following test cases cover normal inputs, negative numbers, duplicates, and integer overflow scenarios.

## Test 1: Basic Positive Numbers

**Input**
```text
5
1 2 3 4 5
```

**Expected Output**
```text
20
```

## Test 2: Negative and Positive Numbers

**Input**
```text
6
-10 -20 1 2 3 4
```

**Expected Output**
```text
200
```

## Test 3: Two Negative Numbers

**Input**
```text
2
-5 -10
```

**Expected Output**
```text
50
```

## Test 4: Duplicate Maximum Values

**Input**
```text
3
5 5 2
```

**Expected Output**
```text
25
```

## Test 5: Duplicate Minimum Values

**Input**
```text
3
-5 -5 2
```

**Expected Output**
```text
25
```

## Test 6: Zero

**Input**
```text
3
-5 0 2
```

**Expected Output**
```text
0
```

## Test 7: Large Product Exceeding LLONG_MAX

**Input**
```text
2
-9223372036854775808 -9223372036854775808
```

**Expected Output**
```text
85070591730234615865843651857942052864
```

This test verifies that multiplication is performed using `__int128` before the operation takes place.

## Test 8: Fewer Than Two Elements

**Input**
```text
1
10
```

**Expected Output**
```text
At least two numbers are required.
```