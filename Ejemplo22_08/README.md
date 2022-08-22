# Ejercicio para Preparacion de Parcial

Se tiene un archivo llamado ***alumnos.dat***, de organización directa, que contiene los datos de los alumnos de la facultad según la siguiente estructura: 


```c
typedef struct {
    long legajo;
    char nombre[30];
    char apellido[30];
    unsigned char edad;
    char regular; //'C': cursando, 'E': Egresado
    long long materias; // 64bits
} alumnos_t;
```
El campo "regular", de tipo char, indica con una 'C' si el alumno está cursando, o con el valor 'E' si ya egresó.
El campo "materias", se lee en forma binaria. Cada bit corresponde a una materia ("Informatica1": bit0 .... "algebra":bit4, etc ), si el bit esta en 1 la materia esta aprobada, en caso contrario aun no se aprobó.

Además, se tiene un archivo llamado ***examenes.dat*** que contiene los datos de los examenes finales y de la promoción de las materias del ultimo año, con la siguiente estructura:

```c
typedef struct {
    long legajo;    
    unsigned char nota;
    char nombreyApellido[61];
    char aprobado; //'S' -> si | 'N' -> no
    char materia[40]; 
    int materia_bit;  // bit que indica a la materia en la estructura alumno
    
} materia_t;
```

Se pide hacer una función que lea al archivo ***examenes.dat*** y vuelque las novedades en el archivo ***alumnos.dat***. 
En caso de que el legajo no se encuentre en el archivo de ***alumnos.dat***, se deberá crear un archivo, ***rechazados.dat***, en donde se guarden todos los registros erroneos. Si el alumno alcanzó 44 materias aprobadas, se lo marcará como "Egresado" y, utilizando punteros, se imprimirá en pantalla todo el apellido en Mayusculas, y el nombre solo con la primera letra en mayusculas, ejemplo: (PEREZ, Juan).

Al finalizar se deberá renombrar al archivo ***examenes.dat*** por ***examenes_procesados.dat***

