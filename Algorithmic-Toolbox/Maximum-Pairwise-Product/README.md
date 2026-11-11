# Maximum Pairwise Product

> A problem-solving journey exploring algorithm optimization, integer overflow, and safe arithmetic in C++.

## 1. Problem Description

Given a sequence of `n` integers, find the maximum product that can be obtained by multiplying two distinct elements from the sequence.

The challenge is not only to find an efficient algorithm but also to ensure that the result is calculated correctly, even when dealing with very large positive and negative integers.

---

## 2. Problem-Solving Journey

This problem started as a simple array problem, but exploring it revealed several important concepts related to algorithm design, integer representation, and safe arithmetic.

### Step 1: The Initial Approach — Brute Force

The first approach is to examine every possible pair of elements, calculate their product, and keep track of the maximum result.

For every element, we consider all elements that come after it.

**Complexity Analysis:**

- Time Complexity: O(n²)
- Auxiliary Space Complexity: O(1)

Although this approach is straightforward, it performs unnecessary comparisons when the input becomes large.

This led to the next question:

**Can we find the maximum product without checking every possible pair?**

### Step 2: Optimizing the Algorithm — One-Pass Approach

The key observation is that the maximum product must come from one of two possibilities:

1. The two largest elements.
2. The two smallest elements.

Why do we need the two smallest elements?

Because multiplying two negative numbers produces a positive result. For example:

```text
-10 × -20 = 200
```

This result can be greater than the product of the two largest positive elements.

Instead of sorting the entire array or checking every pair, we maintain four values during a single traversal:

| Variable | Meaning |
|---|---|
| `max1` | Largest element |
| `max2` | Second-largest element |
| `min1` | Smallest element |
| `min2` | Second-smallest element |

After processing all elements, we calculate:

```cpp
product1 = max1 * max2;
product2 = min1 * min2;
```

The answer is the larger of the two products.

**Complexity Analysis:**

- Time Complexity: O(n)
- Auxiliary Space Complexity: O(1)

We reduced the time complexity from O(n²) to O(n), while maintaining constant auxiliary space.

---

## 3. Going Beyond the Algorithm — Integer Overflow

While developing the solution, another important issue appeared.

Even if the algorithm is logically correct, multiplying two `long long` values can produce a result outside the representable range of `long long`.

For a typical 64-bit `long long`:

```text
LLONG_MIN = -9223372036854775808
LLONG_MAX =  9223372036854775807
```

For example:

```cpp
long long a = LLONG_MIN;
long long b = -1;
```

The mathematical result of `a * b` cannot be represented by `long long`.

This is an example of signed integer overflow, which causes undefined behavior in C++.

### Investigating Safe Multiplication

Before considering a wider integer type, I explored how to determine whether multiplication is safe without actually performing it.

The idea is to use division and the integer limits to check whether the multiplication would exceed the representable range.

For example, when both operands are positive:

```cpp
a <= LLONG_MAX / b
```

Different sign combinations require different conditions because division by a negative number changes the direction of an inequality.

This exploration helped me understand:

- Integer limits.
- Signed arithmetic.
- Division-based overflow checks.
- Why checking the result after multiplication is too late.

---

## 4. Choosing `__int128` for the Final Implementation

For this particular problem, I chose `__int128` to calculate the candidate products.

```cpp
__int128 product1 = static_cast<__int128>(max1) * max2;
__int128 product2 = static_cast<__int128>(min1) * min2;
```

### Why must the cast happen before multiplication?

Consider these two statements:

```cpp
__int128 result = static_cast<__int128>(a) * b;
```

```cpp
__int128 result = a * b;
```

They are not equivalent.

In the first statement, one operand is converted to `__int128` before multiplication. Therefore, the multiplication itself is performed using the wider type.

In the second statement, both operands are `long long`, so multiplication happens using `long long` before the result is assigned to `__int128`.

If overflow happens during multiplication, assigning the result to a wider type cannot fix it.

### Why is `__int128` sufficient?

The product of any two signed 64-bit `long long` values fits within the range of signed 128-bit integers.

Therefore, `__int128` is sufficient for calculating the products in this problem.

**Portability Note:**

`__int128` is a compiler extension supported by GCC and Clang. It is not part of the standard C++ language.

---

## 5. Converting `__int128` to a String

Another challenge appeared when printing the result.

Unlike standard integer types, `__int128` is not directly supported by `std::cout`.

Instead of relying on a non-standard printing function, I implemented a custom conversion function.

The conversion process works as follows:

1. Handle zero as a special case.
2. Store the original sign of the number.
3. Extract the last digit using `% 10`.
4. Convert the digit into a character.
5. Remove the last digit using integer division by 10.
6. Reverse the resulting string.
7. Restore the negative sign if necessary.

### An Important Edge Case: The Minimum Negative Value

A common approach to handling negative numbers is to multiply the number by `-1` or use `abs()`.

However, this is unsafe for the minimum representable signed value because its positive counterpart cannot be represented using the same signed integer type.

Instead, the implementation preserves the original sign and converts each extracted digit individually.

This avoids negating the entire number.

---

## 6. Final Algorithm

The final implementation:

1. Validates that at least two elements are provided.
2. Traverses the input once.
3. Tracks the two largest and two smallest values.
4. Calculates both candidate products using `__int128`.
5. Returns the maximum product.
6. Converts the result to a string for output.

See [`solution.cpp`](solution.cpp) for the complete implementation.

---

## 7. Complexity Analysis

Let `n` be the number of input elements.

| Operation | Time Complexity |
|---|---|
| Finding the two largest elements | O(n) |
| Finding the two smallest elements | O(n) |
| Calculating candidate products | O(1) |
| Comparing candidate products | O(1) |

**Overall Time Complexity: O(n)**

The input is traversed only once.

**Auxiliary Space Complexity: O(1)** for the main algorithm.

The input vector itself requires O(n) space.

The `__int128` to string conversion requires O(d) time and O(d) space, where `d` is the number of decimal digits in the result.

---

## 8. Edge Cases and Testing

The implementation considers the following scenarios:

- Two elements only.
- Duplicate maximum values.
- Duplicate minimum values.
- All positive numbers.
- All negative numbers.
- Mixed positive and negative numbers.
- Zero.
- Very large products exceeding the `long long` range.
- Fewer than two input elements.

See [`tests.md`](tests.md) for test cases and expected outputs.

---

## 9. Key Takeaways

This problem helped me explore several concepts beyond the initial algorithm:

- Moving from brute-force solutions to optimized one-pass algorithms.
- Maintaining multiple minimum and maximum values efficiently.
- Understanding why the two smallest elements matter when maximizing a product.
- Understanding signed integer overflow and undefined behavior in C++.
- Using division-based conditions to investigate safe multiplication.
- Understanding integer promotion and type conversion.
- Knowing why casting before an arithmetic operation matters.
- Using `__int128` for wider integer arithmetic.
- Converting a non-standard integer type into a printable string.
- Handling negative numbers without overflowing during sign conversion.
- Evaluating algorithmic complexity and implementation trade-offs.

## 10. Technical Details

| Property | Value |
|---|---|
| Language | C++ |
| Standard | C++17 |
| Compiler | GCC / Clang |
| Main Algorithm | One-pass traversal |
| Time Complexity | O(n) |
| Auxiliary Space Complexity | O(1) |
| Extended Integer Type | `__int128` |

---

**The main lesson:** Solving a problem is not just about finding an algorithm that works. It is also about understanding why it works, recognizing implementation risks, and making informed engineering decisions.