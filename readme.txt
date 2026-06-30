============================================================
 Tarea 3 - ELO329: Simulador Grafico en C++ y Qt
 EloTelTags y Aplicacion Find My
============================================================

Integrantes : Julian Nunez, Vicente Mujica, Valentina Soto, Vicente Andrade
Profesor    : Agustin Gonzalez Valenzuela
Semestre    : 1er. Semestre 2026


1. DESCRIPCION
------------------------------------------------------------
Simulador grafico, desarrollado en C++ con la biblioteca Qt, que modela la
interaccion entre dispositivos de rastreo (EloTelTags), celulares y tablets
que se desplazan sobre un territorio. Reimplementa en C++/Qt el sistema
desarrollado previamente en Java/JavaFX.


2. ETAPAS DESARROLLADAS
------------------------------------------------------------
El repositorio contiene una solucion independiente para cada etapa, en su
carpeta correspondiente:

  Stage1/  Lectura del archivo de configuracion y despliegue grafico de los
           celulares unicamente (menu inactivo).

  Stage2/  Incorpora EloTelTags y tablets. Todos los equipos se muestran y se
           mueven por el territorio.

  Stage3/  Agrega la clase ETNube. Los celulares reportan a la nube las
           posiciones de los equipos cercanos; los tags y tablets muestran su
           senal de radar y el menu Find My despliega informacion estatica.

  Stage4/  Version final. Completa todas las funcionalidades: menu Play/Pause,
           reporte periodico de posiciones, radar, ventana Find My con
           actualizacion dinamica cada 1 segundo, funcion traza, y la opcion
           extra GFind My (visualizacion geografica de los equipos del dueno).

NOTA: El readme y la documentacion corresponden a la ultima etapa (Stage4).


3. REQUISITOS
------------------------------------------------------------
  - Qt 6.5 o superior (modulos Core y Widgets)
  - Compilador C++ compatible con C++17 (MinGW o equivalente)
  - CMake 3.19 o superior
  - Qt Creator (IDE recomendado)


4. COMPILACION Y EJECUCION
------------------------------------------------------------
Con Qt Creator (recomendado):

  1. Abrir Qt Creator.
  2. File > Open File or Project... y seleccionar el archivo
     CMakeLists.txt dentro de la carpeta de la etapa que se desea ejecutar
     (por ejemplo Stage4/CMakeLists.txt).
  3. Seleccionar un kit de compilacion (por ejemplo Desktop Qt 6.x MinGW).
  4. Esperar a que CMake configure el proyecto.
  5. Presionar Run (Ctrl+R) o Build (Ctrl+B) seguido de Run.
  6. Al iniciar, la aplicacion abre un QFileDialog: seleccionar el archivo
     de configuracion config.txt.

Alternativamente, desde consola:

  cd Stage4
  cmake -S . -B build
  cmake --build build
  ./build/Tarea3        (o Tarea3.exe en Windows)


5. ARCHIVO DE CONFIGURACION
------------------------------------------------------------
La aplicacion solicita un archivo de configuracion (config.txt) con el
siguiente formato:

  <archivo_imagen_de_fondo>
  <delta_tiempo>
  <numero de personas>
  <nombre persona> <numero de EloTelTags> (0 | 1)
  <celular_x> <celular_y> <rapidez> <angulo> <delta_angulo>
  (<nombre EloTelTag> <tag_x> <tag_y> <rapidez> <angulo> <delta_angulo>) *
  [<tablet_x> <tablet_y> <rapidez> <angulo> <delta_angulo>]

La imagen de fondo (por ejemplo Placeres.jpg) debe ser accesible en la ruta
indicada en la primera linea del archivo.


6. USO
------------------------------------------------------------
  - Menu Simulation > Play   : inicia / reanuda la simulacion.
  - Menu Simulation > Pause  : pausa la simulacion.
  - Clic sobre un celular o tablet: despliega el menu emergente con las
    opciones "Find My" y "GFind My".
      * Find My  : abre una ventana con los reportes de la nube para los
                   equipos del dueno, actualizada cada 1 segundo. Cada equipo
                   incluye un boton "Traza" que dibuja/borra su trayectoria
                   sobre el mapa.
      * GFind My : abre una ventana con el mapa de fondo y los iconos de los
                   equipos del dueno, actualizados cada 1 segundo.
