#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string adiciona_str(string num1, string num2) {
    string result = "";
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    reverse(result.begin(), result.end());
    
    return result;
}

string subtract_str(string num1, string num2) {
    string result = "";
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0) {
        int sub = ((num1[i] - '0') - (j >= 0 ? num2[j] - '0' : 0) - carry);
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else
            carry = 0;

        result.push_back(sub + '0');
        i--;
        j--;
    }

    int start = result.size() - 1;
    
    while (start >= 0 && result[start] == '0') {
        start--;
    }
    
    if (start < 0) {
        return "0";
    }
    
    result = result.substr(0, start + 1);

    reverse(result.begin(), result.end());
    
    return result;
}

string multiplica_inteiros(string num1, string num2) {
    int n1 = num1[0] - '0';
    int n2 = (num2.size() != 0) ? num2[0] - '0' : 0;
    int product = n1 * n2;
    return to_string(product);
}

string karatsuba(string num1, string num2) {
    int n = num1.size();
    int m = num2.size();

    if (n == 0 || m == 0) {
        return "0";
    }

    if (n == 1 && m == 1) {
        return multiplica_inteiros(num1, num2);
    }

    int mid = max(n, m) / 2;

    string num1_low = num1.substr(mid);
    string num1_high = num1.substr(0, mid);
    string num2_low = num2.substr(mid);
    string num2_high = num2.substr(0, mid);

    string a0 = karatsuba(num1_low, num2_low);
    string a1 = karatsuba(adiciona_str(num1_low, num1_high), adiciona_str(num2_low, num2_high));
    string a2 = karatsuba(num1_high, num2_high);

    string produto1 = subtract_str(a1, adiciona_str(a0, a2));

    for (int i = 0; i < 2 * (n - mid); i++) { 
        a2 += "0";
    } 

    for (int i = 0; i < n - mid; i++) {
        produto1 += "0";
    }

    string result = adiciona_str(a0, adiciona_str(produto1, a2));
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <number1> <number2>" << endl;
        return 1;
    }

    string num1 = argv[1];
    string num2 = argv[2];

    string result = karatsuba(num1, num2);

    cout << result << endl;

    return 0;
}