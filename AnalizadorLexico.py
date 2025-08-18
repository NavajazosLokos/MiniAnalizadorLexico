def es_letra(c):
    return c.isalpha()

def es_digito(c):
    return c.isdigit()

def analizar_token(token):
    estado = 0
    i = 0
    while i < len(token):
        c = token[i]

        if estado == 0:
            if es_letra(c):        # Inicio identificador
                estado = 1
            elif es_digito(c):     # Inicio número
                estado = 2
            else:
                return "ERROR"
        
        elif estado == 1:  # Identificador
            if es_letra(c) or es_digito(c):
                estado = 1
            else:
                return "ERROR"
        
        elif estado == 2:  # Entero o inicio de real
            if es_digito(c):
                estado = 2
            elif c == '.':        # Posible real
                estado = 3
            else:
                return "ERROR"
        
        elif estado == 3:  # Después del punto en un real
            if es_digito(c):
                estado = 4
            else:
                return "ERROR"
        
        elif estado == 4:  # Parte decimal del real
            if es_digito(c):
                estado = 4
            else:
                return "ERROR"
        
        i += 1
    
    # Estados de aceptación
    if estado == 1:
        return "IDENTIFICADOR"
    elif estado == 2:
        return "ENTERO"
    elif estado == 4:
        return "REAL"
    else:
        return "ERROR"


# --- Cadena de entrada ---
entrada = "Hola12 0.2 2 123.45 99hola 5"

# Procesar cada token separado por espacio
tokens = entrada.split()
print("")
for token in tokens:
    print(f"{token:10} -> {analizar_token(token)}")
