#include <iostream>
#include "MatrizDinamica.h"
#include <stdexcept> // Para std::exception

int main()
{
    std::cout << "--- Sistema Genérico de Análisis de Transformaciones Lineales ---" << std::endl
              << std::endl;

    try
    {
        std::cout << ">> Prueba de Matriz ENTERA (Matriz A) <<" << std::endl;
        std::cout << "Creando Matriz A (Tipo INT) de 2x3..." << std::endl;
        MatrizDinamica<int> A(2, 3);

        std::cout << "\nIngresar valores para A (2x3):" << std::endl;
        // Simulo la entrada de datos del README jaja
        A.setValor(0, 0, 1);
        std::cout << "A[0,0]: 1" << std::endl;
        A.setValor(0, 1, 2);
        std::cout << "A[0,1]: 2" << std::endl;
        A.setValor(0, 2, 3);
        std::cout << "A[0,2]: 3" << std::endl;
        A.setValor(1, 0, 4);
        std::cout << "A[1,0]: 4" << std::endl;
        A.setValor(1, 1, 5);
        std::cout << "A[1,1]: 5" << std::endl;
        A.setValor(1, 2, 6);
        std::cout << "A[1,2]: 6" << std::endl;

        // --- La prueba de redimension ---
        std::cout << "\n>> Redimensionando Matriz A <<" << std::endl;
        std::cout << "Redimensionando A a 3x3. Datos conservados:" << std::endl;
        A.redimensionar(3, 3);
        A.imprimir(); // Ahora se imprime
        std::cout << "(Nuevos valores inicializados a 0)" << std::endl;

        // --- Prueba de multiplicacion con tipo float ahora ---
        std::cout << "\n>> Prueba de Multiplicacion (Tipo FLOAT) <<" << std::endl;

        // Creamos la matriz B
        std::cout << "Creando Matriz B (Tipo FLOAT) de 3x2..." << std::endl;
        MatrizDinamica<float> B(3, 2);
        B.setValor(0, 0, 1.5f);
        B.setValor(0, 1, 0.5f);
        B.setValor(1, 0, 2.0f);
        B.setValor(1, 1, 1.0f);
        B.setValor(2, 0, 1.0f);
        B.setValor(2, 1, 2.5f);
        // Imprimimos los valores asignados
        std::cout << "B[0,0]: 1.5, B[0,1]: 0.5" << std::endl;
        std::cout << "B[1,0]: 2.0, B[1,1]: 1.0" << std::endl;
        std::cout << "B[2,0]: 1.0, B[2,1]: 2.5" << std::endl;

        // Vamos a convertir la matriz A que es int a float para operar
        MatrizDinamica<float> A_float(A.getFilas(), A.getColumnas());
        for (int i = 0; i < A.getFilas(); ++i)
        {
            for (int j = 0; j < A.getColumnas(); ++j)
            {
                // Convertimos el valor int a float
                A_float.setValor(i, j, static_cast<float>(A.getValor(i, j)));
            }
        }

        // Multiplicamos A_float(3x3) x B(3x2)
        std::cout << "\nMatriz C = A(3x3) x B(3x2) ..." << std::endl;
        MatrizDinamica<float> C = MatrizDinamica<float>::multiplicar(A_float, B);

        // Vamos ahora a imprimir los resultados C
        std::cout << "\nMatriz C (Resultado 3x2, Tipo FLOAT):" << std::endl;
        C.imprimir(1);
    }
    catch (const std::exception &e)
    {
        // Manejo de errores
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nYa bye" << std::endl;
    // Don't worry my friend, los destructores se llaman automaticamente aqui (o asi deberia ser xd)
    return 0;
}