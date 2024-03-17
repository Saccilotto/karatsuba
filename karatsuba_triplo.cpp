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

    while (resultado.size() > 1 && resultado[resultado.size() - 1] == '0') {
        resultado.pop_back();
    }

    reverse(resultado.begin(), resultado.end());
    return resultado;
}

string karatsuba(string numero1, string numero2) {

    int n = numero1.size();
    int m = numero2.size();

    if (n == 0 || m == 0)
        return "0";

    if (n == 1 || m == 1) {
        return to_string(stoi(numero1) * stoi(numero2));
    }

    // Calcula a posição de separação
    int quebra_indice = max(n, m) / 3;
    if (quebra_indice == 0) {
        quebra_indice = 1;
    }

    string numero1_esquerda, numero1_meio, numero1_direita;
    string numero2_esquerda, numero2_meio, numero2_direita;

    // separação de acordo com o tamanho dos números
    if (n >= 3) {
        numero1_esquerda = numero1.substr(0, n - quebra_indice * 2);
        numero1_meio = numero1.substr(n - quebra_indice * 2, quebra_indice);
        numero1_direita = numero1.substr(n - quebra_indice);
    } else {
        numero1_esquerda = "0";
        numero1_meio = numero1.substr(0, n / 2);
        numero1_direita = numero1.substr(n / 2);
    }

    if (m >= 3) {
        numero2_esquerda = numero2.substr(0, m - quebra_indice * 2);
        numero2_meio = numero2.substr(m - quebra_indice * 2, quebra_indice);
        numero2_direita = numero2.substr(m - quebra_indice);
    } else {
        numero2_esquerda = "0";
        numero2_meio = numero2.substr(0, m / 2);
        numero2_direita = numero2.substr(m / 2);
    }

    string a0 = karatsuba(numero1_direita, numero2_direita);
    string a1 = karatsuba(concatena(numero1_direita, numero1_meio), concatena(numero2_direita, numero2_meio));
    string a2 = karatsuba(concatena(numero1_esquerda, numero1_meio), concatena(numero2_esquerda, numero2_meio));
    string a3 = karatsuba(numero1_esquerda, numero2_esquerda);

    a1 = subtractStrings(subtractStrings(a1, a2), a0);
    a2 = subtractStrings(subtractStrings(a2, a3), a0);

    // Concatenação dos resultadoados
    string resultado = a3;
    for (int i = 0; i < quebra_indice * 2; ++i)
        resultado += '0';
    resultado = concatena(resultado, a2);
    for (int i = 0; i < quebra_indice; ++i)
        resultado += '0';
    resultado = concatena(resultado, a1);
    for (int i = 0; i < quebra_indice; ++i)
        resultado += '0';
    resultado = concatena(resultado, a0);

    // Remoção de zeros à esquerda
    while (resultado.size() > 1 && resultado[0] == '0') {
        resultado.erase(0, 1);
    }

    return resultado;
}


int main(int argc , char *argv[]) {

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
