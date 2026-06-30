# Tarea 3 - ELO329: Simulador Gráfico en C++ y Qt

### EloTelTags y Aplicación Find My

**Integrantes:** Julián Núñez, Vicente Mujica, Valentina Soto, Vicente Andrade
**Profesor:** Agustín González Valenzuela
**Semestre:** 1er. Semestre 2026

---

## Descripción

Simulador gráfico, desarrollado en C++ con la biblioteca Qt, que modela la interacción entre
dispositivos de rastreo (EloTelTags), celulares y tablets que se desplazan sobre un
territorio. Reimplementa en C++/Qt el sistema desarrollado previamente en Java/JavaFX.

---

## Etapas desarrolladas

El repositorio contiene una solución independiente para cada etapa, en su carpeta
correspondiente:

| Carpeta | Descripción |
|---------|-------------|
| `Stage1/` | Lectura del archivo de configuración y despliegue gráfico de los celulares únicamente (menú inactivo). |
| `Stage2/` | Incorpora EloTelTags y tablets. Todos los equipos se muestran y se mueven por el territorio. |
| `Stage3/` | Agrega la clase `ETNube`. Los celulares reportan a la nube las posiciones de los equipos cercanos; los tags y tablets muestran su señal de radar y el menú Find My despliega información estática. |
| `Stage4/` | Versión final. Completa todas las funcionalidades: menú Play/Pause, reporte periódico de posiciones, radar, ventana Find My con actualización dinámica cada 1 segundo, función traza, y la opción extra **GFind My** (visualización geográfica de los equipos del dueño). |

> **Nota:** El README y la documentación corresponden a la última etapa (Stage 4).

---

## Requisitos

- **Qt 6.5** o superior (módulos Core y Widgets)
- Compilador **C++17** (MinGW o equivalente)
- **CMake 3.19** o superior
- **Qt Creator** (IDE recomendado)

---

## Compilación y ejecución

### Con Qt Creator (recomendado)

1. Abrir Qt Creator.
2. `File > Open File or Project...` y seleccionar el archivo `CMakeLists.txt` dentro de la
   carpeta de la etapa que se desea ejecutar (por ejemplo `Stage4/CMakeLists.txt`).
3. Seleccionar un kit de compilación (por ejemplo *Desktop Qt 6.x MinGW*).
4. Esperar a que CMake configure el proyecto.
5. Presionar **Run** (`Ctrl+R`) o **Build** (`Ctrl+B`) seguido de Run.
6. Al iniciar, la aplicación abre un diálogo de archivos: seleccionar `config.txt`.

### Desde consola

```bash
cd Stage4
cmake -S . -B build
cmake --build build
./build/Tarea3        # Tarea3.exe en Windows
```

---

## Archivo de configuración

La aplicación solicita un archivo `config.txt` con el siguiente formato:

```
<archivo_imagen_de_fondo>
<delta_tiempo>
<número de personas>
<nombre persona> <número de EloTelTags> (0 | 1)
<celular_x> <celular_y> <rapidez> <ángulo> <delta_ángulo>
(<nombre EloTelTag> <tag_x> <tag_y> <rapidez> <ángulo> <delta_ángulo>) *
[<tablet_x> <tablet_y> <rapidez> <ángulo> <delta_ángulo>]
```

La imagen de fondo (por ejemplo `Placeres.jpg`) debe ser accesible en la ruta indicada en la
primera línea del archivo.

---

## Uso

- **Menú Simulation → Play:** inicia / reanuda la simulación.
- **Menú Simulation → Pause:** pausa la simulación.
- **Clic sobre un celular o tablet:** despliega el menú emergente con las opciones *Find My* y
  *GFind My*.
  - **Find My:** abre una ventana con los reportes de la nube para los equipos del dueño,
    actualizada cada 1 segundo. Cada equipo incluye un botón *Traza* que dibuja/borra su
    trayectoria sobre el mapa.
  - **GFind My:** abre una ventana con el mapa de fondo y los íconos de los equipos del dueño,
    actualizados cada 1 segundo.
