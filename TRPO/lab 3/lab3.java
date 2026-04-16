import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import lab1.SparseMatrix;
import java.io.*;
import java.util.Scanner;


public class lab3 {

    public interface Comparator {
        int compare(Object o1, Object o2);
    }

    public interface UserType {
        String typeName();                    // Имя типа

        Object create();                      // Создаёт новый объект по умолчанию

        Object clone(Object obj);             // Клонирует существующий объект
                                            // (изменено на приём параметра для удобства)

        Object readValue(InputStreamReader in) throws IOException; // Читает из потока

        Object parseValue(String ss);         // Парсит из строки

        Comparator getTypeComparator();       // Возвращает компаратор для типа
    }

    public class DoubleType implements UserType {

        @Override
        public String typeName() {
            return "double";
        }

        @Override
        public Object create() {
            return 0.0;
        }

        @Override
        public Object clone(Object obj) {
            if (obj instanceof Double) {
                return ((Double) obj).doubleValue();
            }
            throw new IllegalArgumentException("Object is not Double");
        }

        @Override
        public Object readValue(InputStreamReader in) throws IOException {
            BufferedReader br = new BufferedReader(in);
            String line = br.readLine();
            if (line == null) throw new IOException("End of stream");
            return Double.parseDouble(line.trim());
        }

        @Override
        public Object parseValue(String ss) {
            return Double.parseDouble(ss.trim());
        }

        @Override
        public Comparator getTypeComparator() {
            return new Comparator() {
                @Override
                public int compare(Object o1, Object o2) {
                    return Double.compare((Double) o1, (Double) o2);
                }
            };
        }
    }

    public static class SparseMatrixType implements UserType {

        @Override
        public String typeName() {
            return "SparseMatrix";
        }

        @Override
        public Object create() {
            return new SparseMatrix();
        }

        @Override
        public Object clone(Object obj) {
            if (!(obj instanceof SparseMatrix)) {
                throw new IllegalArgumentException("Object is not SparseMatrix");
            }
            SparseMatrix original = (SparseMatrix) obj;
            SparseMatrix copy = new SparseMatrix(original.n, original.m);
            for (SparseMatrix.Elem e : original.elems) {
                copy.elems.add(copy.new Elem(e.x, e.y, e.v));
            }
            return copy;
        }

        @Override
        public Object readValue(InputStreamReader in) throws IOException {
            // Чтение из текстового потока в плотном формате или в формате saveToText
            BufferedReader br = new BufferedReader(in);
            String line = br.readLine();
            if (line == null) throw new IOException("Empty input");
            Scanner scanner = new Scanner(line);
            int n = scanner.nextInt();
            int m = scanner.nextInt();
            SparseMatrix matrix = new SparseMatrix(n, m);

            while ((line = br.readLine()) != null) {
                scanner = new Scanner(line);
                if (scanner.hasNextInt()) {
                    int x = scanner.nextInt();
                    int y = scanner.nextInt();
                    double v = scanner.nextDouble();
                    if (v != 0) {
                        matrix.setElem(x, y, v);
                    }
                }
            }
            return matrix;
        }

        @Override
        public Object parseValue(String ss) {
            // Ожидаем строку вида: "n m x1 y1 v1 x2 y2 v2 ..."
            Scanner scanner = new Scanner(ss);
            int n = scanner.nextInt();
            int m = scanner.nextInt();
            SparseMatrix matrix = new SparseMatrix(n, m);
            while (scanner.hasNextDouble()) {
                int x = scanner.nextInt();
                int y = scanner.nextInt();
                double v = scanner.nextDouble();
                if (v != 0) {
                    matrix.setElem(x, y, v);
                }
            }
            return matrix;
        }

        @Override
        public Comparator getTypeComparator() {
            return new Comparator() {
                @Override
                public int compare(Object o1, Object o2) {
                    SparseMatrix m1 = (SparseMatrix) o1;
                    SparseMatrix m2 = (SparseMatrix) o2;

                    // Сравниваем по норме Фробениуса матриц
                    double norm1 = calculateFrobeniusNorm(m1);
                    double norm2 = calculateFrobeniusNorm(m2);
                    return Double.compare(norm1, norm2);
                }

                // Вспомогательный метод для расчёта нормы Фробениуса
                private double calculateFrobeniusNorm(SparseMatrix m) {
                    double sum = 0;
                    for (SparseMatrix.Elem e : m.elems) {
                        sum += e.v * e.v;
                    }
                    return Math.sqrt(sum);
                }
            };
        }
    }

    public class HashTable {
        private class Node {
            Object value;
            Node next;

            Node(Object value) {
                this.value = value;
            }
        }

        private Node[] heads;
        private int bucketCount;
        private int size;
        private UserType userType;  // Тип элементов

        public HashTable(UserType userType) {
            this(10, userType);
        }

        public HashTable(int bucketCount, UserType userType) {
            this.bucketCount = bucketCount;
            this.heads = new Node[bucketCount];
            this.size = 0;
            this.userType = userType;
        }

        private int hash(Object value) {
            int h = value.hashCode();
            return (h < 0 ? -h : h) % bucketCount;
        }

        public void addToEnd(Object value) {
            int hash = hash(value);
            Node newNode = new Node(value);
            if (heads[hash] == null) {
                heads[hash] = newNode;
            } else {
                Node current = heads[hash];
                while (current.next != null) {
                    current = current.next;
                }
                current.next = newNode;
            }
            size++;
        }

        public Object get(int index) {
            if (index < 0 || index >= size) {
                throw new IndexOutOfBoundsException("Index out of bounds");
            }
            int count = 0;
            for (int i = 0; i < bucketCount; i++) {
                Node current = heads[i];
                while (current != null) {
                    if (count == index) {
                        return current.value;
                    }
                    count++;
                    current = current.next;
                }
            }
            throw new RuntimeException("Unexpected error");
        }

        public void insert(Object value, int index) {
            if (index < 0 || index > size) {
                throw new IndexOutOfBoundsException("Index out of bounds");
            }
            if (index == size) {
                addToEnd(value);
                return;
            }
            int count = 0;
            for (int i = 0; i < bucketCount; i++) {
                Node current = heads[i];
                Node prev = null;
                while (current != null) {
                    if (count == index) {
                        Node newNode = new Node(value);
                        if (prev == null) {
                            newNode.next = heads[i];
                            heads[i] = newNode;
                        } else {
                            newNode.next = current;
                            prev.next = newNode;
                        }
                        size++;
                        return;
                    }
                    prev = current;
                    current = current.next;
                    count++;
                }
            }
        }

        public void delete(int index) {
            if (index < 0 || index >= size) {
                throw new IndexOutOfBoundsException("Index out of bounds");
            }
            int count = 0;
            for (int i = 0; i < bucketCount; i++) {
                Node current = heads[i];
                Node prev = null;
                while (current != null) {
                    if (count == index) {
                        if (prev == null) {
                            heads[i] = current.next;
                        } else {
                            prev.next = current.next;
                        }
                        size--;
                        return;
                    }
                    prev = current;
                    current = current.next;
                    count++;
                }
            }
        }

        public interface Callback {
            void toDo(Object v);
        }

        public void forEach(Callback callback) {
            for (int i = 0; i < bucketCount; i++) {
                Node current = heads[i];
                while (current != null) {
                    callback.toDo(current.value);
                    current = current.next;
                }
            }
        }

        public HashTable sort() {
            HashTable newTable = new HashTable(bucketCount, userType);
            List<Object> allElements = new ArrayList<>();
            forEach(allElements::add);

            Comparator comp = userType.getTypeComparator();
            Collections.sort(allElements, comp::compare);

            for (Object v : allElements) {
                newTable.addToEnd(v);
            }
            return newTable;
        }

        public int size() {
            return size;
        }
    }


    public void main(String[] args) {
        System.out.println("=== Тестирование HashTable ===\n");

        UserType matrixType = new SparseMatrixType();

        HashTable table = new HashTable(10, matrixType);

        SparseMatrix m1 = new SparseMatrix(3, 3);
        m1.setElem(0, 0, 1.5);
        m1.setElem(1, 1, 2.0);
        m1.setElem(2, 2, 3.0);                  
        SparseMatrix m2 = new SparseMatrix(3, 3);
        m2.setElem(0, 1, 4.0);
        m2.setElem(1, 2, 5.0);                 

        SparseMatrix m3 = new SparseMatrix(2, 2);
        m3.setElem(0, 0, 10.0);                 
        SparseMatrix m4 = new SparseMatrix(4, 4); 
        table.addToEnd(m1);
        table.addToEnd(m2);
        table.addToEnd(m3);
        table.addToEnd(m4);

        System.out.println("1. Исходное состояние таблицы (SparseMatrix):");
        table.forEach(obj -> ((SparseMatrix) obj).printMatrixDense());

        table.insert(matrixType.clone(m1), 1);

        System.out.println("\nПосле клонирования и вставки m1 на позицию 1:");
        table.forEach(obj -> ((SparseMatrix) obj).printMatrixDense());

        System.out.println("\nПолучение по индексу:");
        System.out.println("Элемент с индексом 0:");
        ((SparseMatrix) table.get(0)).printMatrixDense();
        System.out.println("Элемент с индексом 3:");
        ((SparseMatrix) table.get(3)).printMatrixDense();

        System.out.println("\nУдаление элементов:");
        table.delete(2);
        table.delete(0); 

        System.out.println("После удаления (осталось " + table.size() + " элементов):");
        table.forEach(obj -> ((SparseMatrix) obj).printMatrixDense());

        System.out.println("\n\n=== Тестирование с типом double ===\n");

        UserType doubleType = new DoubleType();

        HashTable table2 = new HashTable(5, doubleType);

        table2.addToEnd(doubleType.parseValue("3.14"));
        table2.addToEnd(doubleType.parseValue("-7.5"));
        table2.addToEnd(doubleType.parseValue("10.0"));
        table2.addToEnd(doubleType.parseValue("3.14"));  
        table2.addToEnd(doubleType.parseValue("0.0"));
        table2.addToEnd(doubleType.parseValue("-100.5"));

        System.out.println("До сортировки:");
        printBucketState(table2);
        System.out.println();

        table2.insert(doubleType.parseValue("999.9"), 0);

        System.out.println("После вставки 999.9 в начало:");
        printBucketState(table2);
        System.out.println();

        HashTable sortedDouble = table2.sort();
        System.out.println("После сортировки:");
        printBucketState(sortedDouble);

        table2.delete(0);              
        table2.delete(table2.size() - 1);

        System.out.println("После удаления двух элементов (осталось " + table2.size() + "):");
        table2.forEach(v -> System.out.print(v + " "));
        System.out.println();
    }

    private static void printBucketState(HashTable table) {
        for (int i = 0; i < table.bucketCount; i++) {
            System.out.printf("   Корзина %d: ", i);
            HashTable.Node current = table.heads[i];
            if (current == null) {
                System.out.println("(пусто)");
            } else {
                while (current != null) {
                    System.out.print(current.value);
                    if (current.next != null) System.out.print(" -> ");
                    current = current.next;
                }
                System.out.println();
            }
        }
    }
}