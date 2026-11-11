#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <optional>

using namespace std;

using int128 = __int128;


// Convert __int128 to string
string to_string_128(int128 number) {

    if (number == 0)
        return "0";

    bool is_negative = number < 0;

    string result;

    while (number != 0) {

        int digit = static_cast<int>(number % 10);

        if (digit < 0)
            digit = -digit;

        result += static_cast<char>('0' + digit);

        number /= 10;
    }

    reverse(result.begin(), result.end());

    if (is_negative)
        result.insert(result.begin(), '-');

    return result;
}


// Find the maximum product of two distinct elements
optional<int128> Max_PairWise_Product(
    const vector<long long>& numbers
) {

    if (numbers.size() < 2)
        return nullopt;

    long long max1 = LLONG_MIN;
    long long max2 = LLONG_MIN;

    long long min1 = LLONG_MAX;
    long long min2 = LLONG_MAX;

    for (long long x : numbers) {

        // Track the two largest values
        if (x > max1) {
            max2 = max1;
            max1 = x;
        }
        else if (x > max2) {
            max2 = x;
        }

        // Track the two smallest values
        if (x < min1) {
            min2 = min1;
            min1 = x;
        }
        else if (x < min2) {
            min2 = x;
        }
    }

    // Cast BEFORE multiplication to prevent long long overflow
    int128 product1 = static_cast<int128>(max1) * max2;
    int128 product2 = static_cast<int128>(min1) * min2;

    return max(product1, product2);
}


int main() {

    int n;

    if (!(cin >> n))
        return 0;

    if (n < 2) {
        cout << "At least two numbers are required.\n";
        return 0;
    }

    vector<long long> numbers(n);

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    optional<int128> answer = Max_PairWise_Product(numbers);

    if (!answer.has_value()) {
        cout << "Invalid input.\n";
        return 0;
    }

    cout << to_string_128(answer.value()) << '\n';

    return 0;
}