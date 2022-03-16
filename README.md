# P1_MIA_201709282
<h1> Sistema de archivos con FLEX y BISON en C++ <h1>

<h2> MANUAL TECNICO </h2>
<h3> Simulador de un sistema de archivos EXT2 y EXT3 <h3>
<p> El siguiente proyecto es una simulación de un sistema de archivos basado en los sistemas de archivos de Linux ext2 y ext3. El sistema cuenta con una consola que soporta comandos similares a los del sistema de Linux, los cuales permiten realizar operaciones a grupos y usuarios según los permisos que estos tengan asignados para la creación, edición, eliminación, lectura y escritura de los archivos y carpetas de nuestro sistema. El sistema es simulado por medio de (discos) archivos binarios que contendrán la información que se almacenara con las estructuras definidas por un sistema de archivos de Linux, al igual que en Linux se debe montar el disco para poder realizar operaciones con él, en este primer caso sería formatearlo. Al darle formato al disco se utilizará MBR, el cual cuenta con 4 particiones primarias, de las cuales solo una puede ser extendida, dentro de la partición extendida se pueden crear más particiones, pero estas serán llamadas particiones lógicas. Los discos se irán sobrescribiendo con la información que se le va proporcionando por medio de los comandos y la información se ira ordenando y almacenando según el ajuste configurado en el disco o la partición montada. Para este proyecto es posible configurar los ajustes como “worst fit”, “best fit” & “first fit”. Para el manejo de ajustes se virtualiza la memoria disponible en el disco y con esto se lleva a cabo un ordenamiento secuencial para determinar los espacios libres según el tipo de ajuste seleccionado en los comandos se realiza la implementación.  
Adicionalmente el sistema puede elegir el formato del sistema de archivos, se puede trabajar con ext2 y con ext3, este ultimo a diferencia del primero cuenta con un sistema de registro por diario “Jurnaling”. Para verificar el funcionamiento adecuado del sistema de archivos instalado en el disco a la hora de formatearlo se cuenta con los comandos Loss y Recovery, los cuales simulan un error en el sistema y si este es en formato ext3 con el journaling se puede recuperar el sistema a la última versión estable.
Las estructuras que conforman el sistema son las siguientes: <p>
  <ul>
    <li>  MasterBootRecord: contiene la información relevante al disco y sus particiones </li>
    <li>  Partition: contiene la información de la partición del disco </li>
    <li>  ExtendedBootRecord: contiene la información de la partición extendida y las lógicas del disco </li>
    <li>  SuperBlock: contiene la información del sistema de archivos instalado en el disco. </li>
    <li>  TablaInodos: contiene la información de los inodos creados, estos tienen 12 apuntados directos a bloques de información, 1 apuntador indirecto, 1 apuntador indirecto doble y un apuntador indirecto triple. </li>
    <li>  BloquesCarpetas: contiene espacio para 4 carpetas y esta estructura almacena la información de la carpeta. </li>
    <li>  Content: contiene la información de la carpeta y su inodo. </li>
    <li>  BloquesArchivos: contiene un char de 64 bits de información que se puede almacenar con datos de un archivo del sistema. </li>
    <li>  BloquesApuntadores: contiene la información de los apuntadores indirectos y sus inodos según sea su tipo. </li>
  </ul>

  <h3> Programas y herramientas: </h3>
  <ol>
    <li> Sistema operativo Linux o cualquier distribución. </li>
    <li> Lenguaje de programación C, C++, Yacc, Flex </li>
    <li> Graphviz </li>
    <li> Generadores de lenguaje Flex y Bison </li>
  </ol>
    
  
  <h3> Pasos para la compilación e instalación del sistema: </h3>
  <ol>
    <li>	Instalar una distribución de Linux </li>
    <li>	Instalar y actualizar los paquetes apt </li>
      <ul>
        <li>	sudo apt update </li>
        <li>	sudo apt upgrade </li>
      </ul>
    <li>	Instalar el compilador de c++ </li>
      <ul>
        <li> sudo apt-get install g++ </li>
      </ul>
    <li>	Instalar flex y bison </li>
      <ul>
        <li>	sudo apt-get install flex </li>
        <li>	sudo apt-get install bison </li>
      </ul>
    <li>	Instalar graphviz </li>
      <ul>
        <li>	sudo apt-get install graphviz </li>
      </ul>
    <li>	Instalar git </li>
      <ul>
        <li>	sudo apt-get install git </li>
      </ul>
    <li>	Clonar el repositorio </li>
      <ul>
        <li>	git clone https://github.com/2730538920101/P1_MIA_201709282.git </li>
      </ul>
    <li>	Compilar Flex </li>
      <ul>
        <li>	flex --header-file=lexico.h -o lexico.cpp lexico.l </li>
      </ul>
    <li>	Compilar Bison </li>
      <ul>
        <li>	bison sintactico.y -o sintactico.cpp --defines=sintactico.h </li>
      </ul>
    <li>	Compilar Código </li>
      <ul>
        <li>	c++ *.cpp -o P1_201709282 </li>
      </ul>
    <li>	Ejecutar el sistema </li>
      <ul>
        <li>	./P1_201709282 </li>
      </ul>
 </ol>
  
  <h2> MANUAL USUARIO </h2>
  
  <h3> Comandos y parametros aceptados por el sistema </h3>

|COMANDO|PARAMETROS OBLIGATORIOS| | | |PARAMETROS OPCIONALES| | | |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|#|ID| |TIPO DATO|ENTRADAS|ID| |TIPO DATO|ENTRADAS|
|1|-size| |int|TOK_NUMERO|-fit| |STRING|TOK_AJUSTE|
|MKDISK|-path| |STRING|TOK_RUTA/TOK_CADENA|-unit| |STRING|TOK_UNIDADES|
| | | | | | | | | |
|2|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|RMDISK| | | | | | | | |
| | | | | | | | | |
|3|-size| |int|TOK_NUMERO|-unit| |STRING|TOK_UNIDADES|
|FDISK|-path| |STRING|TOK_RUTA/TOK_CADENA|-type| |STRING|TOK_TIPO|
| |-name| |STRING|TOK_NOMBRE/TOK_CADENA|-fit| |STRING|TOK_AJUSTE|
| | | | | |-delete| |STRING|TOK_CAPACIDAD|
| | | | | |-add| |int|TOK_NUMERO|
| | | | | | | | | |
| | | | | | | | | |
|4|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|MOUNT|-name| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|5|-id| |STRING|TOK_IDENTIFICADOR| | | | |
|UNMOUNT| | | | | | | | |
| | | | | | | | | |
|6|-id| |STRING|TOK_IDENTIFICADOR|-type| |STRING|TOK_CAPACIDAD|
|MKFS| | | | |-fs| |STRING|TOK_SISTEMA|
| | | | | | | | | |
|7| | | | | | | | |
|LOGIN|-usuario| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| |-password| |STRING|TOK_NOMBRE| | | | |
| |-id| |STRING|TOK_IDENTIFICADOR| | | | |
| | | | | | | | | |
|8| | | | | | | | |
|LOGOUT| | | | | | | | |
| | | | | | | | | |
|9|-name| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
|MKGRP| | | | | | | | |
| | | | | | | | | |
|10|-name| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
|RMGRP| | | | | | | | |
| | | | | | | | | |
|11|-usuario| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
|MKUSER|-pwd| |STRING|TOK_NOMBRE| | | | |
| |-grp| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|12|-usuario| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
|RMUSR| | | | | | | | |
| | | | | | | | | |
|13|-path| |STRING|TOK_RUTA/TOK_CADENA|-r| | | |
|CHMOD|-ugo| |int|TOK_PERMISOS| | | | |
| | | | | | | | | |
|14|-path| |STRING|TOK_RUTA/TOK_CADENA|-r| | | |
|MKFILE| | | | |-size| |int|TOK_NUMERO|
| | | | | |-cont| |STRING|TOK_RUTA|
| | | | | | | | | |
| | | | | | | | | |
|15|-filen| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|CAT| | | | | | | | |
| | | | | | | | | |
|16|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|REMOVE| | | | | | | | |
| | | | | | | | | |
|17|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|EDIT|-contenido| |STRING|TOK_RUTA/TOK_CADENA| | | | |
| | | | | | | | | |
| | | | | | | | | |
|18|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|RENAME|-name| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|19|-path| |STRING|TOK_RUTA/TOK_CADENA|-p| | | |
|MKDIR| | | | | | | | |
| | | | | | | | | |
|20|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|COPY|-destino| |STRING|TOK_RUTA/TOK_CADENA| | | | |
| | | | | | | | | |
|21|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|MOVE|-destino| |STRING|TOK_RUTA/TOK_CADENA| | | | |
| | | | | | | | | |
|22|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|FIND|-name| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|23|-path| |STRING|TOK_RUTA/TOK_CADENA|-r| | | |
|CHOWN|-usuario| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|24|-usuario| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
|CHGRP|-grp| |STRING|TOK_NOMBRE/TOK_CADENA| | | | |
| | | | | | | | | |
|25|-id| |STRING|TOK_IDENTIFICADOR| | | | |
|RECOVERY| | | | | | | | |
| | | | | | | | | |
|26|-id| |STRING|TOK_IDENTIFICADOR| | | | |
|LOSS| | | | | | | | |
| | | | | | | | | |
|27|-path| |STRING|TOK_RUTA/TOK_CADENA| | | | |
|EXEC| | | | | | | | |
| | | | | | | | | |
| | | | | | | | | |
|28| | | | | | | | |
|PAUSE| | | | | | | | |
| | | | | | | | | |
|29|-name| | |TOK_REPORTES|-ruta| | |TOK_RUTA/TOK_CADENA|
|REP|-path| | |TOK_RUTA/TOK_CADENA| | | | |
| |-id| | |TOK_IDENTIFICADOR| | | | |
| | | | | | | | | |

  <h3>Lista de Tokens: </h3>
  
  |NUMERO|TOKENS|REGEX| |
|:----|:----|:----|:----|
|1|TOK_MKDISK|MKDISK| |
|2|TOK_RMDISK|RMDISK| |
|3|TOK_FDISK|FDISK| |
|4|TOK_MOUNT|MOUNT| |
|5|TOK_UNMOUNT|UNMOUNT| |
|6|TOK_MKFS|MKFS| |
|7|TOK_LOGIN|LOGIN| |
|8|TOK_LOGOUT|LOGOUT| |
|9|TOK_MKGRP|MKGRP| |
|10|TOK_RMGRP|RMGRP| |
|11|TOK_MKUSR|MKUSR| |
|12|TOK_RMUSR|RMUSR| |
|13|TOK_CHMOD|CHMOD| |
|14|TOK_MKFILE|MKFILE| |
|15|TOK_CAT|CAT| |
|16|TOK_REMOVE|REMOVE| |
|17|TOK_EDIT|EDIT| |
|18|TOK_RENAME|RENAME| |
|19|TOK_MKDIR|MKDIR| |
|20|TOK_COPY|COPY| |
|21|TOK_MOVE|MOVE| |
|22|TOK_FIND|FIND| |
|23|TOK_CHOWN|CHOWN| |
|24|TOK_CHGRP|CHGRP| |
|25|TOK_RECOVERY|RECOVERY| |
|26|TOK_LOSS|LOSS| |
|27|TOK_EXEC|EXEC| |
|28|TOK_SIZE|-size| |
|29|TOK_PATH|-path| |
|30|TOK_NAME|-name| |
|31|TOK_ID|-id| |
|32|TOK_USUARIO|-usuario| |
|33|TOK_PWD|-pwd| |
|34|TOK_PASSWORD|-password| |
|35|TOK_GRP|-grp| |
|36|TOK_UGO|-ugo| |
|37|TOK_FILEN|-file"[0-9]+	
38|TOK_CONT|-cont| |
|39|TOK_CONTENIDO|-contenido| |
|40|TOK_DESTINO|-destino| |
|41|TOK_UNIT|-unit| |
|42|TOK_REP|REP| |
|43|TOK_TYPE|-type| |
|44|TOK_DELETE|-delete| |
|45|TOK_ADD|-add| |
|46|TOK_FS|-fs| |
|47|TOK_R|-r| |
|48|TOK_P|-p| |
|49|TOK_RUTA|-ruta| |
|50|TOK_FIT|-fit| |
|51|TOK_NUMERO|[0-9]+| |
|52|TOK_AJUSTE|BF" or "FF" or "WF| |
|53|TOK_UNIDADES|B" or "K" or "M| |
|54|TOK_RUTA_R|([\"][^\"\n]*[\"]) or ([/][^\n\" ]+)+| |
|55|TOK_TIPO|P" or "E" or "L| |
|56|TOK_NOMBRE|([\"][^\"\n]{1,10}[\"]) or ([^\n\" ]){1,10}| |
|57|TOK_CAPACIDAD|FAST"or "FULL| |
|58|TOK_SISTEMA|2FS" or "3FS| |
|59|TOK_CADENA|REGEX PARA CADENAS| |
|60|TOK_IDENTIFICADOR|[0-9]{3}[Aa-zZ]| |
|61|TOK_IGUAL|=| |
|62|TOK_REPORTES|REGEX PARA REPORTES| |


