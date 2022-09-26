/*
El siguiente codigo responde al siguiente enunciado.

Existe un archivo llamdo "datos.dat", de tipo binario, cuya organizacion es secuencial. Los datos estan organizados segun
la siguiente estructura:

struct d{
  long clave; //Clave o Id del registro guardado
  char d[30]; //Descripcion
  unsigned char tipo; //Tipo de datos como entero sin signo
  char b; //'A':Alta 'B':Baja
}

Se pide:
Realizar una funcion que pase como parametro la clave, entre otros parametros, y apile dos valores, la Clave y su posicion fisica respecto
al archivo (registro 1,2,etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo Mostrar por pantalla "Registro no encontrado",
la funcion debe devolver el puntero de pila.

Realizar el main con varias llamadas a dicha funcion y proceder a mostrar las descripciones
del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.

*********************************************************************************************************************
Breve explicacion. Hay varias formas de resolver el enunciado. La mas simple y que cumpliria todo lo pedido. Es hacer en el main un ciclo que cree la pila
con las llamadas sucesivas que pide el enunciado y luego volver a recorrer la pila mostrando las descripciones
*/

#include <stdio.h>
#include <malloc.h>

/*Defino las estructuras*/
struct datos{
  long clave; //Clave o Id del registro guardado
  char d[30]; //Descripcion
  unsigned char tipo; //Tipo de datos como entero sin signo
  char b; //'A':Alta 'B':Baja
}

struct pila{
  long clave;
  long acceso; //Ubicacion del registro en el archivo
  struct pila *siguiente;
}

/*Prototipo de la funcion*/
/*
La funcion deber devolver el punter de la pila. Como el apilado se hace en funcion tambien debere darle el ultimo registro apilado en la pila
*/
struct pila * funcion(long clave, struct pila *anterior);

/*Mmin*/
int main(int argc, char const *argv[]) {
  struct pila *ultimo,*aux;
  struct datos fdata;
  FILE *archivo;
  long claves[]={45,32,15,47,96,85,754,1,2,18}; //hago un vector con diferentes claves a apilar, tambien se podria pedir las claves al usuario.
  char i; // como en el ejemplo pongo menos de 127 claves, uso variabe tipo char para la iteracion.
  ultimo = NULL;
  /*El bucle recorrera el vector pidiendo las diferentes claves para apilar y al finalizar tendre la ultima parte de la pila*/
  for(i=0;i<sizeof(claves);i++){
    ultimo = funcion(claves[i],ultimo);
  }
  /*El enunciado no lo pide pero ademas de imprimir la descripcion liberare la memoria de la pila*/
  if(ultimo == NULL){
    printf("No se encontro ningun registro con esas claves\n"); // Esta verificacion tampoco se pide en el enunciado pero si no hay pila lo aviso aca.
    return 0;
  }
  do{
    if((archivo=fopen("datos.dat","rb"))==NULL){
      printf("Error al intentar abrir Datos.dat");
      return 0;
    }
    fseek(archivo,ultimo -> acceso*(long)sizeof(struct datos),SEEK_SET); // ubica al puntero de archivo en la posion del registro leido.
    fread(&fdata,sizeof(datos),1,archivo);
    printf("Descripcion: %s\n",fdata.d); // imprimo la Descripcion
    /*A parti de aca libero la pila, no lo pide el enunciado*/
    aux = ultimo;
    ultimo = ultimo -> siguiente;
    free(aux);
  }while (ultimo -> siguiente != NULL);

      printf("Gracias por usar nuestro programa\n", );
      fclose(archivo);
  return 0;
}
/*funcion
la funcion debera crear la pila en caso de no existir y devolver siempre el ultimo elemento.
*/
struct pila * funcion(long clave, struct pila *anterior){
    struct pila *aux;
    FILE *bf;
    struct datos data;
    long contador = 0;

    if((bf=fopen("datos.dat","rb"))== NULL){
      printf("No se pudo abrir archivo");
      return NULL;
    }
    fread(&data,sizeof(struct datos),1,bf);//lectura anticipada
    while(!feof(bf)){
      if(data.clave == clave){ //verifico que coincida la clave
        if(data.tipo & (1<<4)){ //verifico que en tipo el bit 4 tenga valor 1 y en caso afirmativo apilo
          aux = malloc(sizeof(struct pila));
          aux -> clave = data.clave;
          aux -> acceso = contador; // contador tiene la cantidad de registros leidos del archivo
          if(anterior == NULL){ //Primer elemento de la pila
            aux -> siguiente = NULL;
          }else{
            aux -> siguiente = anterior;
          }
          fclose(bf);
          return aux; // Ultimo elemento de la pila actualizado
        }
      }
      fread(&data,sizeof(struct datos),1,bf);//vuelvo a leer
      contador++;
    }
    printf("Registro no encontrado\n", ); // Si llego aca es porque no encontro el Registro
    fclose(bf);
    return anterior; // La funcion siempre tiene que devolver el ultimo elemento de la pila, si no apilo debo devolver la pila sin modificar

}