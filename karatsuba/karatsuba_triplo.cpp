#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Função para adicionar dois números representados como strings
string adiciona_str(const string &num1, const string &num2) {
    string result = "";
    int carry = 0;
    int n1 = num1.length(), n2 = num2.length();
    int diff = abs(n1 - n2);

    // Adiciona zeros ao menor numero
    string str1 = num1;
    string str2 = num2;
    if (n1 > n2) {
        str2 = string(diff, '0') + num2;
    } else if (n2 > n1) {
        str1 = string(diff, '0') + num1;
    }

    // Adiciona numeros digito à digito
    for (int i = str1.length() - 1; i >= 0; i--) {
        int sum = (str1[i] - '0') + (str2[i] - '0') + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    // Se tiver um carry restante, adicione-o ao resultado
    if (carry) {
        result.push_back(carry + '0');
    }

    // Reverte o resultado e retorna
    reverse(result.begin(), result.end());

    return result;
}

// Função para subtrair dois números representados como strings
string subtract_str(const string &num1, const string &num2) {
    string result = "";
    int carry = 0;
    int n1 = num1.length(), n2 = num2.length();
    int diff = abs(n1 - n2);

    // Preenche o número menor com zeros à esquerda
    string str1 = num1;
    string str2 = num2;
    if (n1 > n2) {
        str2 = string(diff, '0') + num2;
    } else if (n2 > n1) {
        str1 = string(diff, '0') + num1;
    }

    int i = str1.length() - 1, j = str2.length() - 1;
    
    // Continua enquanto houver dígitos
    while (i >= 0) {
        int sub = ((str1[i] - '0') - (j >= 0 ? str2[j] - '0' : 0) - carry);
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(sub + '0');
        i--;
        j--;
    }

    // Remove zeros à esquerda
    int start = 0;
    while (start < result.length() && result[start] == '0') {
        start++;
    }

    if (start == result.length()) {
        return "0";
    }

    // Inverte o resultado e retorna
    result = result.substr(start, result.length() - start);
    reverse(result.begin(), result.end());
    
    return result;
}

// Função para multiplicar dois números representados como strings
string multiplica(const string &num1, const string &num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0) {
        return "0";
    }

    vector<int> result(n1 + n2, 0);

    int i_n1 = 0;
    int i_n2 = 0;

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = num1[i] - '0';

        i_n2 = 0;

        for (int j = n2 - 1; j >= 0; j--) {
            int n2 = num2[j] - '0';

            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            carry = sum / 10;

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        if (carry > 0) {
            result[i_n1 + i_n2] += carry;
        }

        i_n1++;
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0) {
        i--;
    }

    if (i == -1) {
        return "0";
    }

    string s = "";

    while (i >= 0) {
        s += std::to_string(result[i--]);
    }

    return s;
}

// Função para dividir um número representado como uma string por uma constante
string divide_str(const string &num, const string &divisor_str) {
    int divisor = stoi(divisor_str);
    string result = "";
    int idx = 0;
    int temp = num[idx] - '0';

    while (temp < divisor) {
        temp = temp * 10 + (num[++idx] - '0');
    }

    while (num.size() > idx) {
        result += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + num[++idx] - '0';
    }

    if (result.length() == 0) {
        return "0";
    }

    return result;
}

// Função para combinar coeficientes
string combina(const string &c0, const string &c1, const string &c2, const string &c3, const string &c4, int original_length) {
    string term1 = c0 + string(2 * original_length, '0');
    string term2 = divide_str(subtract_str(subtract_str(c1, c0), c2), "2") + string(3 * original_length / 2, '0');
    string term3 = c2 + string(original_length, '0');
    string term4 = divide_str(subtract_str(subtract_str(c3, c1), c4), "2") + string(original_length / 2, '0');
    string term5 = c4;

    // Combina os termos para obter o resultado final
    string result = adiciona_str(adiciona_str(adiciona_str(adiciona_str(term1, term2), term3), term4), term5);

    return result;
}

// Função para dividir um número em três partes
void separa_tres(const string &num, string &part1, string &part2, string &part3) {
    int length = num.length();
    int part_length = length / 3;

    // If the length of the number is not divisible by 3, the first part should be one digit longer
    if (length % 3 != 0) {
        part_length++;
    }

    part1 = num.substr(0, part_length);
    part2 = num.substr(part_length, part_length);
    part3 = num.substr(2 * part_length);
}

// Função para multiplicar dois números representados como strings usando o algoritmo de Karatsuba triplo
string karatsuba_triplo(string fator1, string fator2) {
    // Verifica se algum dos fatores é zero
    if (fator1 == "0" || fator2 == "0") {
        return "0";
    }

    // Preenche o número menor com zeros à esquerda
    if (fator1.length() < fator2.length()) {
        fator1 = string(fator2.length() - fator1.length(), '0') + fator1;
    } else if (fator2.length() < fator1.length()) {
        fator2 = string(fator1.length() - fator2.length(), '0') + fator2;
    }

    // Condição de parada: se um dos números têm menos de 4 dígitos, multiplicar diretamente
    if (fator1.length() <= 3 || fator2.length() <= 3) {
        return multiplica(fator1, fator2);
    }

    // Divide os números em três partes
    string a0, a1, a2, b0, b1, b2;
    separa_tres(fator1, a0, a1, a2);
    separa_tres(fator2, b0, b1, b2);

    // Calcula os cinco produtos necessários
    string p0 = karatsuba_triplo(a0, b0);
    string p1 = karatsuba_triplo(adiciona_str(a0, a1), adiciona_str(b0, b1));
    string p2 = karatsuba_triplo(a1, b1);
    string p3 = karatsuba_triplo(adiciona_str(a1, a2), adiciona_str(b1, b2));
    string p4 = karatsuba_triplo(a2, b2);

    // Combina os produtos para obter os coeficientes
    string c0 = p0;
    string c1 = subtract_str(subtract_str(p1, p0), p2);
    string c2 = p2;
    string c3 = subtract_str(subtract_str(p3, p1), p4);
    string c4 = p4;

    // Combina os coeficientes para obter o resultado final
    string result = combina(c0, c1, c2, c3, c4, fator1.length());

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <numero1> <numero2>" << endl;
        return 1;
    }
    
    string fator1 = argv[1];
    string fator2 = argv[2];
    
    // Calcula o produto dos fatores usando o algoritmo de Karatsuba triplo
    string result = karatsuba_triplo(fator1, fator2);
    
    // Imprime o resultado
    cout << result << endl;
    
    return 0;
}