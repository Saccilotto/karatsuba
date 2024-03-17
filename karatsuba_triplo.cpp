#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addStrings(string num1, string num2) {
    
    string result;
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0)
            sum += num1[i--] - '0';
        if (j >= 0)
            sum += num2[j--] - '0';
        carry = sum / 10;
        sum %= 10;
        result.push_back(sum + '0');
    }
    reverse(result.begin(), result.end());
    return result;
}

string subtractStrings(string num1, string num2) {

    string result;
    int borrow = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }

    while (result.size() > 1 && result[result.size() - 1] == '0') {
        result.pop_back();
    }

    reverse(result.begin(), result.end());
    return result;
}

string karatsuba(string num1, string num2) {

    int n = num1.size();
    int m = num2.size();

    if (n == 0 || m == 0)
        return "0";

    if (n == 1 || m == 1) {
        return to_string(stoi(num1) * stoi(num2));
    }

    int maxLength = max(n, m);
    int splitPosition = maxLength / 3;

    string num1_high = num1.substr(0, n - splitPosition * 2);
    string num1_mid = num1.substr(n - splitPosition * 2, splitPosition);
    string num1_low = num1.substr(n - splitPosition);
    
    string num2_high = num2.substr(0, m - splitPosition * 2);
    string num2_mid = num2.substr(m - splitPosition * 2, splitPosition);
    string num2_low = num2.substr(m - splitPosition);

    string z0 = karatsuba(num1_low, num2_low);
    string z1 = karatsuba(addStrings(num1_low, num1_mid), addStrings(num2_low, num2_mid));
    string z2 = karatsuba(addStrings(num1_high, num1_mid), addStrings(num2_high, num2_mid));
    string z3 = karatsuba(num1_high, num2_high);

    z1 = subtractStrings(subtractStrings(z1, z2), z0);
    z2 = subtractStrings(subtractStrings(z2, z3), z0);

    string result = z3;
    for (int i = 0; i < splitPosition * 2; ++i)
        result += '0';
    result = addStrings(result, z2);
    for (int i = 0; i < splitPosition; ++i)
        result += '0';
    result = addStrings(result, z1);
    for (int i = 0; i < splitPosition; ++i)
        result += '0';
    result = addStrings(result, z0);

    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    return result;
}

int main(int argc , char *argv[]) {

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <number1> <number2>" << endl;
        return 1;
    }
    

    string numero1 = argv[1];
    string numero2 = argv[2];

    string result = karatsuba(numero1, numero2);

    cout << result << endl;

    return 0;
}
