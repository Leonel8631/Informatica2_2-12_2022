/**
 * Enunciado
 Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es directa, y tiene la siguiente estructura: id(clave) entero largo; d(descripción) cadena de caracteres; t(Tipo) entero; m(Marca 'A': Alta  'B': Baja) caracter.

Se pide:
1. Realizar una función que pase como parámetro el id de la pieza, si el registro esta marcado como ‘A’ deberá modificar la descripción por  "Registro Procesado", marcarlo como ‘B’ en el archivo y retornar el registro.
  Si esta marcado como 'B' utilizando punteros cambiar la descripción las ‘a’ y ‘o’ por ‘-’,   retornando el registro y grabándolo en el archivo "Baja_Pieza.dat"     
 No usar variables globales.

 **/

#include <stdio.h>
#include <string.h>

typedef struct {
    long id;
    char d[30];
    int t;
    char m;
}datos_t;

datos_t mi_funcion (long id);

/**
 * @function main
 * @description llama a mi funcion e imprime al registro procesado.
 * */
int main(){
    long clave;
    datos_t registro;

    printf("Hola, ingrese el id");
    scanf("%d",&clave);
    registro = mi_funcion(clave);
    printf("El %d, tiene la descripcion %s", registro.id,registro.d);
}


/**
 * @function mi_funcion
 * @param {long} id - Clave de pieza
 * @description ejecuta lo pedido en el enunciado
 * */
datos_t mi_funcion(long id) {
    FILE *datos, *baja;
    datos_t registro;
    char *s;

    if((datos = fopen("datos.dat","rb+")) == NULL) {
        printf("Error al abrir el archivo datos.dat");
        return ;
    }
    fseek(datos, sizeof(datos_t)*id,0); // busca el id
    fread(&registro, sizeof(datos_t),1,datos); //lee el registro
    if(registro.id != id) { //verifica que el registro leido es el registro buscado
        printf("Registro no encontrado");
        return;
    }
    if(registro.m == 'A') { 
        strcpy(registro.d,"Registro Procesado");
        registro.m = 'B';
        fseek(datos, -1L*sizeof(datos_t),1);
        fwrite(&registro, sizeof(datos_t),1,datos);
        fclose(datos);
        return registro;
    }
    if(registro.m == 'B') {
        s=registro.d;
        while(*s){            
            *s = (*s=='a' || *s=='o') ? '-' : *s; // Equvalente a if(*s=='a' || *s=='o') *s = '-';
            s++;
        }
        if((baja = fopen("Baja_Pieza.dat","ab+")) == NULL) {
            printf("Error al abrir el archivo Baja_Pieza.dat");
            return ;
         }
         fwrite(&registro, sizeof(datos_t),1,baja);
         fclose(datos);
         fclose(baja);
         return registro;
    }
    return ;
}

