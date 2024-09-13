#include <gtest/gtest.h>
#include <sstream>
#include "MPointer.h"
#include "DoublyLinkedList.h"

// Prueba de creación de MPointer
TEST(MPointerTest, CreateNewMPointer) {
    MPointer<int> mp = MPointer<int>::New();
    *mp = 5;
    EXPECT_EQ(*mp, 5);
}

// Prueba de asignación de MPointer
TEST(MPointerTest, AssignMPointer) {
    MPointer<int> mp1 = MPointer<int>::New();
    MPointer<int> mp2 = MPointer<int>::New();
    *mp1 = 10;
    mp2 = mp1;
    EXPECT_EQ(*mp2, 10);
}

// Prueba de ordenamiento con QuickSort
TEST(DoublyLinkedListTest, QuickSort) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(1);
    list.append(2);

    // Captura de salida de printList
    std::ostringstream oss;
    auto old_buf = std::cout.rdbuf(oss.rdbuf());

    list.quickSort();
    list.printList(); // Captura la salida

    std::cout.rdbuf(old_buf); // Restaura el buffer original

    EXPECT_EQ(oss.str(), "1 2 3\n"); // Salida esperada con el salto de línea al final
}

// Prueba de ordenamiento con BubbleSort
TEST(DoublyLinkedListTest, BubbleSort) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(1);
    list.append(2);

    // Captura de salida de printList
    std::ostringstream oss;
    auto old_buf = std::cout.rdbuf(oss.rdbuf());

    list.bubbleSort();
    list.printList(); // Captura la salida

    std::cout.rdbuf(old_buf); // Restaura el buffer original

    EXPECT_EQ(oss.str(), "1 2 3\n"); // Ajusta la salida esperada para incluir el salto de línea al final
}

// Prueba de ordenamiento con InsertionSort
TEST(DoublyLinkedListTest, InsertionSort) {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(3);
    list.append(1);

    // Captura de salida de printList
    std::ostringstream oss;
    auto old_buf = std::cout.rdbuf(oss.rdbuf());

    list.insertionSort();
    list.printList(); // Captura la salida

    std::cout.rdbuf(old_buf); // Restaura el buffer original

    EXPECT_EQ(oss.str(), "1 2 3 4\n"); // Ajusta la salida esperada para incluir el salto de línea al final
}

// Prueba de sobrecarga del operador &
TEST(MPointerTest, AddressOfOperator) {
    MPointer<int> mp = MPointer<int>::New();
    *mp = 10;
    EXPECT_EQ(*mp, 10);
    EXPECT_EQ(*mp.operator&(), 10); // Verifica el valor usando el operador & sobrecargado
}

// Prueba de liberación de memoria y conteo de referencias
TEST(MPointerTest, ReferenceCounting) {
    MPointer<int> mp1 = MPointer<int>::New();
    {
        MPointer<int> mp2 = mp1;
        EXPECT_EQ(*mp1, 0); // Verifica el valor inicial
    }
    EXPECT_NO_THROW(*mp1); // Verifica que no se lance una excepción
}

// Prueba de puntero nulo
TEST(MPointerTest, NullPointer) {
    MPointer<int> mp; // Este puntero debería ser nulo
    EXPECT_THROW(*mp, std::runtime_error); // Verifica que se lance una excepción si se intenta acceder a un puntero nulo
}

// Ejecutar las pruebas
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
