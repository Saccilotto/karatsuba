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
    if (n1 == 0 || n2 == 0) return "0";

    vector<int> result(n1 + n2, 0);

    // Multiplica dígito a dígito
    for (int i = n1 - 1; i >= 0; i--) {
        for (int j = n2 - 1; j >= 0; j--) {
            int mult = (num1[i] - '0') * (num2[j] - '0');
            int sum = mult + result[i + j + 1];
            result[i + j] += sum / 10;
            result[i + j + 1] = sum % 10;
        }
    }

    // Converte o resultado para string
    string resultado;
    for (int i = 0; i < result.size(); i++) {
        if (!(resultado.empty() && result[i] == 0))
            resultado.push_back(result[i] + '0');
    }

    return resultado.empty() ? "0" : resultado;
}

// Função para dividir um número representado como uma string por três
string separa_tres(const string &num) {
    string result = "";
    int idx = 0;
    int temp = num[idx] - '0';
    while (temp < 3)
        temp = temp * 10 + (num[++idx] - '0');
    while (num.size() > idx) {
        result += (temp / 3) + '0';
        temp = (temp % 3) * 10 + num[++idx] - '0';
    }
    if (result.length() == 0)
        return "0";
    return result;
}

// Função para combinar coeficientes
string combina(const string &c0, const string &c1, const string &c2, const string &c3, const string &c4) {
    string term1 = c0 + string(c4.length() * 4, '0');
    string term2 = c1 + string(c4.length() * 3, '0');
    string term3 = c2 + string(c4.length() * 2, '0');
    string term4 = c3 + string(c4.length(), '0');
    string term5 = c4;

    // Combina os termos para obter o resultado final
    string result = adiciona_str(adiciona_str(adiciona_str(adiciona_str(term1, term2), term3), term4), term5);

    return result;
}

// Função para dividir um número representado como uma string por três
string divideByThree(const string &num) {
    string result = "";
    int idx = 0;
    int temp = num[idx] - '0';
    while (temp < 3)
        temp = temp * 10 + (num[++idx] - '0');
    while (num.size() > idx) {
        result += (temp / 3) + '0';
        temp = (temp % 3) * 10 + num[++idx] - '0';
    }
    if (result.length() == 0)
        return "0";
    return result;
}

// Função para dividir um número representado como uma string em três partes
void separa_tres(const string &num, string &parte1, string &parte2, string &parte3) {
    string numDivided = divideByThree(num);
    int len = numDivided.length();
    int terco = len / 3;

    // Divide o número em três partes
    parte1 = numDivided.substr(0, terco);
    parte2 = numDivided.substr(terco, terco);
    parte3 = numDivided.substr(2 * terco);
}

// Função para multiplicar dois números representados como strings usando o algoritmo de Karatsuba triplo
string karatsuba_triplo(const string &fator1, const string &fator2) {
    // Verifica se algum dos fatores é zero
    if (fator1 == "0" || fator2 == "0") {
        return "0";
    }

    int tamanho1 = fator1.length();
    int tamanho2 = fator2.length();

    // Condição de parada: se um dos números têm menos de 4 dígitos, multiplicar diretamente
    if (tamanho1 <= 3 || tamanho2 <= 3) {
        return multiplica(fator1, fator2);
    }

    // Divide os números em três partes
    string a1, a2, a3, b1, b2, b3;
    separa_tres(fator1, a1, a2, a3);
    separa_tres(fator2, b1, b2, b3);

    // Calcula as multiplicações recursivas
    string p1 = karatsuba_triplo(a1, b1);
    string p2 = karatsuba_triplo(adiciona_str(a1, a2), adiciona_str(b1, b2));
    string p3 = karatsuba_triplo(a2, b2);
    string p4 = karatsuba_triplo(adiciona_str(a2, a3), adiciona_str(b2, b3));
    string p5 = karatsuba_triplo(a3, b3);

    // Calcula os termos intermediários
    string term1 = p1 + string(2 * a2.length(), '0');
    string term2 = subtract_str(subtract_str(p2, p1), p3);
    string term3 = subtract_str(subtract_str(subtract_str(p4, p1), p3), p5);

    // Combina os termos intermediários para obter o resultado final
    string result = adiciona_str(adiciona_str(term1, adiciona_str(term2, term3)), p5);

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