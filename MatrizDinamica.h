#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

template <typename T>
class MatrizDinamica
{
private:
    T **datos;
    int filas;
    int columnas;

    // Metodo para asignar memoria que se usara por constructor
    void asignarMemoria(int f, int c)
    {
        filas = f;
        columnas = c;
        datos = new T *[filas];
        for (int i = 0; i < filas; ++i)
        {
            datos[i] = new T[columnas];
            // Inicializar a cero
            for (int j = 0; j < columnas; ++j)
            {
                datos[i][j] = T();
            }
        }
    }

    // Metodo para liberar memoria que se usara por el destructor y lo que caiga
    void liberarMemoria()
    {
        for (int i = 0; i < filas; ++i)
        {
            delete[] datos[i];
        }
        delete[] datos;
    }

public:
    // Pues... un constructor
    MatrizDinamica(int f, int c)
    {
        if (f <= 0 || c <= 0)
        {
            throw std::invalid_argument("Las dimensiones deben ser positivas");
        }
        asignarMemoria(f, c);
    }

    // Pues... el destructor, o sea tiene hasta la cosita ~ jaja
    ~MatrizDinamica()
    {
        liberarMemoria();
    }

    // Es el constructor de copia
    MatrizDinamica(const MatrizDinamica<T> &otra)
    {
        asignarMemoria(otra.filas, otra.columnas);
        // Copiar los datos
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                datos[i][j] = otra.datos[i][j];
            }
        }
    }

    // Es el operador de asignacion
    MatrizDinamica<T> &operator=(const MatrizDinamica<T> &otra)
    {
        // Evita una auto-asignacion
        if (this == &otra)
        {
            return *this;
        }

        // Liberamos la memoria antigua
        liberarMemoria();

        // Y asignamos la  nueva memoria y copiamos los datos
        asignarMemoria(otra.filas, otra.columnas);
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                datos[i][j] = otra.datos[i][j];
            }
        }
        return *this;
    }

    // La redimension dinamica
    void redimensionar(int nuevaF, int nuevaC)
    {
        if (nuevaF <= 0 || nuevaC <= 0)
        {
            throw std::invalid_argument("Las nuevas dimensiones deben ser positivas");
        }

        // Creamos una nueva matriz temporal
        T **nuevosDatos = new T *[nuevaF];
        for (int i = 0; i < nuevaF; ++i)
        {
            nuevosDatos[i] = new T[nuevaC];
        }

        // Calculamos los limites de copia
        int filasCopiables = std::min(filas, nuevaF);
        int colsCopiables = std::min(columnas, nuevaC);

        // Copiamos los datos antiguos e inicializamos los nuevos
        for (int i = 0; i < nuevaF; ++i)
        {
            for (int j = 0; j < nuevaC; ++j)
            {
                if (i < filasCopiables && j < colsCopiables)
                {
                    nuevosDatos[i][j] = datos[i][j]; // Copiar datos antiguos
                }
                else
                {
                    nuevosDatos[i][j] = T(); // Inicializar nuevos espacios a cero
                }
            }
        }

        // Liberamos la memoria antigua
        liberarMemoria();

        // Asignamos la nueva matriz
        datos = nuevosDatos;
        filas = nuevaF;
        columnas = nuevaC;
    }

    // Hacemos la multiplicacion matricial
    static MatrizDinamica<T> multiplicar(const MatrizDinamica<T> &A, const MatrizDinamica<T> &B)
    {
        // Validamos las dimensiones
        if (A.columnas != B.filas)
        {
            throw std::invalid_argument("Dimensiones incompatibles para la multiplicación");
        }

        // Dimensiones de la matriz resultante C
        int M = A.filas;
        int N = A.columnas;
        int P = B.columnas;

        MatrizDinamica<T> C(M, P);

        // Usamos la formula: C_ij = Sum(A_ik * B_kj) es para que no se me olvide jajaja
        for (int i = 0; i < M; ++i)
        { // Iteramos las filas de C
            for (int j = 0; j < P; ++j)
            {                 // Iteramos las columnas de C
                T suma = T(); // Acumulador
                for (int k = 0; k < N; ++k)
                {
                    suma += A.datos[i][k] * B.datos[k][j];
                }
                C.datos[i][j] = suma;
            }
        }
        return C; // Se devuelve la matriz C
    }

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }

    void setValor(int f, int c, T valor)
    {
        if (f >= 0 && f < filas && c >= 0 && c < columnas)
        {
            datos[f][c] = valor;
        }
    }

    T getValor(int f, int c) const
    {
        if (f >= 0 && f < filas && c >= 0 && c < columnas)
        {
            return datos[f][c];
        }
        throw std::out_of_range("Índice fuera de rango.");
    }

    // El metodo para imprimir la matriz
    void imprimir(int precision = 1) const
    {
        // Configuramos la salida para que sea mas precisa
        std::cout << std::fixed << std::setprecision(precision);

        for (int i = 0; i < filas; ++i)
        {
            std::cout << "|";
            for (int j = 0; j < columnas; ++j)
            {
                std::cout << " " << datos[i][j] << " |";
            }
            std::cout << std::endl;
        }
    }
};

#endif // MATRIZDINAMICA_H