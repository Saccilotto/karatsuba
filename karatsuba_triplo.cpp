#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string concatena(string fator1, string fator2) {
    string resultado;
    int carrier = 0;
    int i = fator1.size() - 1;
    int j = fator2.size() - 1;

    while (i >= 0 || j >= 0 || carrier) {
        int sum = carrier;
        if (i >= 0)
            sum += fator1[i--] - '0';
        if (j >= 0)
            sum += fator2[j--] - '0';
        carrier = sum / 10;
        sum %= 10;
        resultado.push_back(sum + '0');
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

string subtractStrings(string fator1, string fator2) {
    string resultado;
    int borrow = 0;
    int i = fator1.size() - 1;
    int j = fator2.size() - 1;

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? fator1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? fator2[j--] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultado.push_back(diff + '0');
    }

    reverse(resultado.begin(), resultado.end());
    return resultado;
}

string karatsuba(string numero1, string numero2) {
    int n = numero1.size();
    int m = numero2.size();

    if (n == 0 || m == 0) {
        return "0";
    }

    // Condição de parada para números pequenos
    if (n == 1 || m == 1) {
        return to_string((numero1[0] - '0') * (numero2[0] - '0'));
    }

    // Adiciona zeros à esquerda para garantir que ambos os números tenham o mesmo número de dígitos
    int max_len = max(n, m);

    numero1.size() < max_len ? numero1.insert(0, max_len - numero1.size(), '0') : numero1;
    numero2.size() < max_len ? numero2.insert(0, max_len - numero2.size(), '0') : numero2;    

    if (n == 1 || m == 1) {
        return to_string((numero1[0] - '0') * (numero2[0] - '0'));
    }

    // Calcula a posição de separação
    int quebra_indice = n / 3;

    string numero1_esquerda = numero1.substr(0, quebra_indice);
    string numero1_meio = numero1.substr(quebra_indice, quebra_indice);
    string numero1_direita = numero1.substr(quebra_indice * 2);

    string numero2_esquerda = numero2.substr(0, quebra_indice);
    string numero2_meio = numero2.substr(quebra_indice, quebra_indice);
    string numero2_direita = numero2.substr(quebra_indice * 2);

    string a0 = karatsuba(numero1_direita, numero2_direita);
    string a1 = karatsuba(concatena(numero1_direita, numero1_meio), concatena(numero2_direita, numero2_meio));
    string a2 = karatsuba(concatena(numero1_esquerda, numero1_meio), concatena(numero2_esquerda, numero2_meio));
    string a3 = karatsuba(numero1_esquerda, numero2_esquerda);

    // Ajuste dos resultados intermediários
    a1 = subtractStrings(a1, a0);
    a1 = subtractStrings(a1, a2);
    a2 = subtractStrings(a2, a3);

    // Shifts para as partes intermediárias
    for (int i = 0; i < quebra_indice; ++i) {
        a1 += "0";
        a2 += "0";
    }

    // Concatenação dos resultados
    string resultado = concatena(concatena(a3, a2), a1);
    return resultado;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <number1> <number2>" << endl;
        return 1;
    }

    string numero1 = argv[1];
    string numero2 = argv[2];

    string resultado = karatsuba(numero1, numero2);

    cout << resultado << endl;

    return 0;
}
