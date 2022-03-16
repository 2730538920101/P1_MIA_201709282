# P1_MIA_201709282
<h1> Sistema de archivos con FLEX y BISON en C++ <h1>

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






