def karatsuba(x, y):

    if len(str(x)) == 1 or len(str(x)) == 1:
        return int(x)*int(y)
    
    else:
        n = max(len(str(x)), len(str(y)))  # n é do tamanho do maior string

        if n%3!=0: #quando n for par 
            x=str(x).zfill(n+1)
            y=str(y).zfill(n+1)
            n = max(len(str(x)), len(str(y)))  # atualiza o tamanho

        tamanho_parte = n // 3  # divisão inteira em 3 parte

        x_left = int(str(x)[:tamanho_parte])
        x_center = int(str(x)[tamanho_parte:-tamanho_parte])
        x_right = int(str(x)[-tamanho_parte:])

        y_left = int(str(y)[:tamanho_parte])
        y_center = int(str(y)[tamanho_parte:-tamanho_parte])
        y_right = int(str(y)[-tamanho_parte:])
            

        a = karatsuba(x_left, y_left)
        b = karatsuba(x_center, y_center)
        c = karatsuba(x_right, y_right)
        d = karatsuba(x_left + x_center + x_right , y_left + y_center + y_right) - a - b - c

        return a * 10**(4*tamanho_parte) + d * 10**(2*tamanho_parte) + b + c
        
x = input()
y = input()  

print(karatsuba(int(x), int(y)))
