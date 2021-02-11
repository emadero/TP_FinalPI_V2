# Trabajo Práctico Especial - Programación Imperativa - Febrero 2021 
## Objetivos

Lectura y procesamiento de dataset que contienen información sobre los árboles y barrios de la Ciudad Autónoma de Buenos Aires, y Vancouver.

--------------------------------------------------------------------------------------------------------------------------

## Descripción

Programa con dos archivos ejecutables diferentes, que leen los dataset (en formato .CSV ), y resuelven 
los siguientes queries:

###  1. Diámetro promedio por barrio
    Donde cada línea de la salida contenga, separados por “;” el nombre del barrio y el promedio del diámetro del árbol a la altura del pecho de los árboles pertenecientes a ese barrio. El orden de impresión es descendente por diámetro y luego alfabético por nombre de barrio.  El promedio del diámetro del árbol a la altura del pecho debe imprimirse truncado a dos decimales.
###  2. Especie de árbol por habitante.
    Donde cada línea de la salida contenga, separados por “;” el nombre del barrio, el nombre de
    la especie con mayor cantidad de árboles por habitante de ese barrio y el valor numérico
    correspondiente. La cantidad de árboles por habitante de un barrio consiste en el cociente entre el
    total de árboles localizados en ese barrio y el número de habitantes del mismo. Por lo tanto, para un
    barrio y una especie, el valor numérico a considerar consiste en el cociente entre la cantidad de
    árboles de esa especie ubicados en ese barrio y la cantidad de habitantes de ese barrio.
    Sólo se deben listar los barrios presentes en el archivo CSV de barrios.
    El valor numérico debe imprimirse truncado a dos decimales.
    El orden de impresión es alfabético por nombre de barrio
### 3. Calle con más arboles por barrio.
    Donde cada línea de la salida contenga, separados por “;” el nombre del barrio, el nombre de
    la calle con más árboles de ese barrio y la cantidad de árboles que hay en esa calle de ese barrio.
    Sólo se deben listar los barrios presentes en el archivo CSV de barrios.
    El orden de impresión es alfabético por el nombre del barrio
### 4. Mínimo y máximo diámetro por especie de árbol.
    Donde cada línea de la salida contenga, separados por “;” el nombre de la especie del árbol,
    el mínimo diámetro del árbol a la altura del pecho de esa especie y el máximo diámetro del árbol a
    la altura del pecho de esa especie.
    El orden de impresión es alfabético por especie.
    Todos los valores deben imprimirse con dos decimales.

--------------------------------------------------------------------------------------------------------------------------

## Compilación

Debemos ubicarnos en el directorio coincidente al cuál se encuentran nuestros archivos .h, .c, y los datasets. 
Dependiendo de cuales ejecutables quiera generar, escriba los siguientes comandos en la terminal:
    - Ambos: make all
    - CABA: make BUE
    - Vancouver: make VAN
En el caso de querer eliminar los ejecutables creados:
    - make clean

--------------------------------------------------------------------------------------------------------------------------

## Ejecución

Una vez que los ejecutables fueron generados, estos se pueden invocar de la siguiente forma:

``./arbolesADTBUE arbolesBUE.csv barriosBUE.csv`` 

``./arbolesADTVAN arbolesVAN.csv barriosVAN.csv`` 

Deberá respetarse el orden en el que los dataset son enviados para no obtener resultados no deseados.

Luego de la ejecución deberá ver un mensaje que diga : ``Los archivos fueron creados con exito.``.

Si este texto no aparece es porque hubo un error. De ser este el caso, tambien aparecera un mensaje apropiado explicando que fue lo que sucedio.

--------------------------------------------------------------------------------------------------------------------------

## Archivos

En el direcotorio en el cual es corrido el programa podrá observar los archivos generados.
- query1.csv

- query2.csv

- query3.csv

- query4.csv

Cada uno estos tendran la informacion correspondiente a cada query.

Nota Obtenida: 7
Correciones hechas por los profesores:
- Habría que validar cuando se hace un fopen que el archivo exista, porque sino existe falla. (Funcionamiento)
- Verificar que si se agrega un dato en los archivos csv (un barrio más) se rompe. (Funcionamiento)
- No deberíamos utilizar toda la información de una, deberíamos ir iterando por la misma (Diseño)
- Error en constante simbolica de Vancouver en la de CALLE, era otra columna en el archivo csv. (Funcionamiento)

--------------------------------------------------------------------------------------------------------------------------
