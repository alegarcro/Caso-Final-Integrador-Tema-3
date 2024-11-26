# Caso-Final-Integrador-Tema-3
## Trabajos prácticos
### 1. Carga de scripts en tiny-lisp
El módulo Labmain.cpp define la función load_script(), que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.

Implementa las funciones load_script() y load_script(filename, true) en CLion, de tal manera que puedas abrir y leer archivos de texto. El primer método toma el nombre de un archivo como entrada del usuario, mientras que el segundo muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.

void load_script(const char* filename, bool show_script = false);
void load_script();
### 2. Asegurando la robustez del código
Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada. Esto incluye, pero no se limita a:

El usuario proporciona un nombre de archivo que no existe.
El archivo proporcionado no se puede abrir por alguna razón.
Se produce un error de lectura durante la lectura del archivo.
Para manejar estos y otros errores potenciales, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.

## Notas
Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo _s). En cambio, deberías usar las funciones estándar de C/C++ disponibles en todas las plataformas y compiladores, como fopen, printf y scanf.


## Rúbrica
Carga de scripts (50 puntos)

Se proporciona una implementación correcta de load_script(const char* filename, bool show_script = false) que carga correctamente el archivo dado y muestra su contenido si show_script es verdadero. (25 puntos)
Se proporciona una implementación correcta de load_script() que solicita al usuario un nombre de archivo, llama a la función load_script(const char* filename, bool show_script = false) y maneja cualquier error de manera apropiada. (25 puntos)
Manejo de errores (50 puntos)

El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)
Total: 100 puntos

## Propuesta de solución
En CLion, las funciones seguras de la biblioteca estándar de C (*_s funciones) generalmente no están disponibles porque estas son específicas de Microsoft y no son estándar de C/C++. Por lo tanto, en lugar de utilizar funciones como fopen_s, printf_s y scanf_s, puedes usar sus equivalentes no seguros, que son fopen, printf y scanf.

A continuación se muestra cómo se podría reescribir el código para CLion:

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
Este código debería compilar y funcionar en CLion sin necesidad de agregar la directiva _CRT_SECURE_NO_WARNINGS, ya que no se están utilizando las versiones seguras específicas de Microsoft de las funciones de la biblioteca estándar de C.

Por último, ten en cuenta que este código no realiza una comprobación completa de errores y no es robusto contra varios tipos de errores de entrada. Dependiendo de tu caso de uso específico, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.

# Correción Caso Final Integrador 3 de Encina 

### Evaluación del código y justificación de la calificación


  1. Implementación de load_script(const char* filename, bool show_script = false) :
     - La función está correctamente implementada. Lee el archivo especificado, gestiona errores de apertura y lectura, y muestra el contenido si se solicita. Cumple con todos los requerimientos.
  2. Implementación de load_script() :
     - Si bien funciona correctamente, esta implementación incluye código que debería estar en el archivo principal (main), rompiendo la modularidad del programa. En un diseño limpio, load_script() debería recibir directamente el nombre del archivo o solicitarlo desde main, y no manejar entradas directamente.


- *Manejo de errores *:
  1. Archivo no existente :
     - Gestiona correctamente cuando el archivo no existe, mostrando un mensaje de error adecuado.
  2. Error al abrir el archivo :
     - Detecta y maneja fallos al abrir el archivo (e.g., permisos insuficientes).
  3. Error durante la lectura del archivo :
     - Usa ferror y excepciones para capturar errores de lectura y asegurar que se manejen correctamente.



### *Justificación*

   - La implementación de manejo de errores es adecuada y completa.
   - Usa buenas prácticas como la limpieza de recursos (cerrar archivos) en bloques catch.

2. *Inconsistencia con la separación de responsabilidades*:
   - Según la pauta adicional, el archivo main debería contener únicamente el flujo principal (int main) y llamar a las funciones correspondientes. En este caso, la función load_script() incluye lógica de interacción con el usuario (cin y getline), que debería estar en main.
   - Ejemplo de un diseño más modular:
     cpp
     void load_script_from_user_input() {
         string filename;
         cout << "Ingrese el nombre del archivo: ";
         getline(cin, filename);
         if (filename.empty()) {
             cerr << "Error: No se ingresó un nombre de archivo." << endl;
             return;
         }
         load_script(filename.c_str(), true);
     }

     int main() {
         try {
             load_script_from_user_input();
         } catch (const exception &e) {
             cerr << "Error inesperado: " << e.what() << endl;
         }
         return 0;
     }
     

3. *Buen manejo de errores*:
   - Usa excepciones estándar (std::runtime_error) para errores de lectura y asegura que los recursos sean liberados apropiadamente.
   - Proporciona mensajes de error informativos para distintos escenarios.

4. *Estilo y legibilidad*:
   - El código es legible, usa nombres claros y sigue un estilo consistente.
   - Usa adecuadamente estructuras y colores de consola para mejorar la funcionalidad.

---

### *Recomendaciones *
1. *Separación de responsabilidades*:
   - Desplaza la lógica de entrada del usuario fuera de load_script() hacia main o una función auxiliar.
2. *Optimización del manejo de errores*:
    podrías simplificar la estructura de excepciones con std::unique_ptr para gestionar automáticamente la liberación del archivo.
3. *Comentarios*:
   - Añade comentarios explicativos en las partes más críticas del código, como el manejo de excepciones o la lectura del archivo.

