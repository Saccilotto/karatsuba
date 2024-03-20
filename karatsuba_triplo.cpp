#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Função para adicionar dois números representados como strings
string adiciona_str(const string &fator1, const string &fator2) {
    string result = "";
    int carry = 0;
    int i = fator1.length() - 1, j = fator2.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += fator1[i--] - '0';
        if (j >= 0) sum += fator2[j--] - '0';
        carry = sum / 10;
        sum %= 10;
        result.push_back(sum + '0');
    }
    
    reverse(result.begin(), result.end());
    return result;
}

// Função para subtrair dois números representados como strings
string subtract_str(const string &fator1, const string &fator2) {
    string result = "";

    int borrow = 0;
    int i = fator1.length() - 1, j = fator2.length() - 1;
    
    while (i >= 0 || borrow) {
        int diff = (i >= 0 ? fator1[i--] - '0' : 0) - borrow;

        if (j >= 0)
            diff -= fator2[j--] - '0';

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(diff + '0');
    }
    
    reverse(result.begin(), result.end());

    // Remover zeros à esquerda
    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);

    return result;
}

// Função para multiplicar dois números representados como strings
string multiplica(const string &num1, const string &num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0) return "0";

    vector<int> result(n1 + n2, 0);

    for (int i = n1 - 1; i >= 0; i--) {
        for (int j = n2 - 1; j >= 0; j--) {
            int mult = (num1[i] - '0') * (num2[j] - '0');
            int sum = mult + result[i + j + 1];
            result[i + j] += sum / 10;
            result[i + j + 1] = sum % 10;
        }
    }

    string resultado;
    for (int i = 0; i < result.size(); i++) {
        if (!(resultado.empty() && result[i] == 0))
            resultado.push_back(result[i] + '0');
    }

    return resultado.empty() ? "0" : resultado;
}

void separa_tres(const string &numero, string &parte1, string &parte2, string &parte3) {
    int len = numero.length();

    if (len <= 3) {
        if (len == 0) {
            parte1 = "0";
            parte2 = "0";
            parte3 = "0";
        } else if (len == 1) {
            parte1 = numero;
            parte2 = "0";
            parte3 = "0";
        } else if (len == 2) {
            parte1 = numero.substr(0, 1);
            parte2 = numero.substr(1, 1);
            parte3 = "0";
        } else {
            parte1 = numero.substr(0, 1);
            parte2 = numero.substr(1, 1);
            parte3 = numero.substr(2, 1);
        }
        return;
    }

    int terco = len / 3;
    int resto = len % 3;

    if (resto == 0) {
        parte1 = numero.substr(0, terco);
        parte2 = numero.substr(terco, terco);
        parte3 = numero.substr(2 * terco);
    } else if (resto == 1) {
        parte1 = numero.substr(0, terco + 1);
        parte2 = numero.substr(terco + 1, terco);
        parte3 = numero.substr(2 * terco + 1);
    } else {
        parte1 = numero.substr(0, terco + 1);
        parte2 = numero.substr(terco + 1, terco + 1);
        parte3 = numero.substr(2 * terco + 2);
    }
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

    // Calcula as multiplicações recursivamente
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
    
    string result = karatsuba_triplo(fator1, fator2);
    
    cout << result << endl;
    
    return 0;
}