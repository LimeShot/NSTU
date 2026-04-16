import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class HashTable {
    private class Node {
        int value;
        Node next;

        Node(int value) {
            this.value = value;
        }
    }

    private Node[] heads;
    private int bucketCount;
    private int size;

    public HashTable() {
        this(10); // Количество корзин по умолчанию
    }

    public HashTable(int bucketCount) {
        this.bucketCount = bucketCount;
        this.heads = new Node[bucketCount];
        this.size = 0;
    }

    // Add to end: хешируем значение и добавляем в конец списка соответствующей корзины
    public void addToEnd(int value) {
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

    // Получаем значение по позиции в порядке обхода всех элементов, игнорируя хеш
    public int get(int index) {
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

    // Вставляем значение по позиции в порядке обхода всех элементов, игнорируя хеш
    public void insert(int value, int index) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
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

    // Удаление по позиции в порядке обхода всех элементов, игнорируя хеш
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
        throw new RuntimeException("Unexpected error");
    }

    // Итератор forEach с обратным вызовом
    public interface Callback {
        void toDo(int v);
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

    // Сортировка всех элементов в каждой корзине и создание новой хеш-таблицы
    public HashTable sort() {
        HashTable newTable = new HashTable(bucketCount);
        for (int i = 0; i < bucketCount; i++) {
            List<Integer> bucketList = new ArrayList<>();
            Node current = heads[i];
            while (current != null) {
                bucketList.add(current.value);
                current = current.next;
            }
            Collections.sort(bucketList);
            for (int v : bucketList) {
                newTable.addToEnd(v);
            }
        }
        return newTable;
    }

    // Хэш-функция
    private int hash(int value) {
        int h = Integer.hashCode(value);
        return (h < 0 ? -h : h) % bucketCount;
    }

    // Получаем текущий размер
    public int size() {
        return size;
    }

    public static void main(String[] args) {
        System.out.println("=== Тестирование хэш-таблицы ===\n");

        // 1. Создание пустой хэш-таблицы с 5 бакетами
        HashTable table = new HashTable(5);
        System.out.println("1. Создана пустая хэш-таблица с 5 бакетами.");
        printTableState(table);
        System.out.println();

        // 2. Добавление элементов в конец
        System.out.println("2. Добавление элементов в конец:");
        int[] valuesToAdd = {10, 25, 7, 42, 18, 33, 7};
        for (int v : valuesToAdd) {
            table.addToEnd(v);
            System.out.printf("   addToEnd(%d) -> размер: %d\n", v, table.size());
        }
        printTableState(table);
        printBucketState(table);
        System.out.println();

        // 3. Получение элементов по индексу
        System.out.println("3. Получение элементов по логическому индексу:");
        for (int i = 0; i < table.size(); i++) {
            System.out.printf("   get(%d) = %d\n", i, table.get(i));
        }
        System.out.println();

        // 4. Вставка элементов по индексу
        System.out.println("4. Вставка элементов по индексу:");
        table.insert(999, 0); // в начало
        System.out.println("   insert(999, 0) — вставка в начало");
        printTableState(table);

        table.insert(555, 3); // в середину
        System.out.println("   insert(555, 3) — вставка в середину");
        printTableState(table);

        table.insert(777, table.size()); // в конец
        System.out.println("   insert(777, size) — вставка в конец");
        printTableState(table);
        System.out.println();

        // 5. Удаление элементов по индексу
        System.out.println("5. Удаление элементов по индексу:");
        table.delete(0); // удаляем 999 из начала
        System.out.println("   delete(0) — удаление первого элемента");
        printTableState(table);

        table.delete(table.size() - 1); // удаляем последний
        System.out.println("   delete(size-1) — удаление последнего элемента");
        printTableState(table);

        table.delete(2); // удаляем из середины
        System.out.println("   delete(2) — удаление из середины");
        printTableState(table);
        System.out.println();

        // 6. Итерация с использованием forEach
        System.out.println("6. Итерация по всем элементам (forEach):");
        table.forEach(v -> System.out.print(v + " "));
        System.out.println("\n");

        // 7. Сортировка
        System.out.println("7. Сортировка хэш-таблицы:");
        System.out.println("   До сортировки:");
        table.forEach(v -> System.out.print(v + " "));
        System.out.println();

        HashTable sortedTable = table.sort();
        System.out.println("   После сортировки (в новой таблице):");
        sortedTable.forEach(v -> System.out.print(v + " "));
        System.out.println("\n");
        printTableState(sortedTable);        
        printBucketState(sortedTable);
        System.out.println("\n=== Тестирование завершено успешно ===");
    }

    // Вспомогательный метод для красивого вывода текущего состояния таблицы
    private static void printTableState(HashTable table) {
        System.out.print("   Текущее состояние (логический порядок): ");
        if (table.size() == 0) {
            System.out.println("[]");
            return;
        }
        for (int i = 0; i < table.size(); i++) {
            System.out.print(table.get(i));
            if (i < table.size() - 1) System.out.print(" -> ");
        }
        System.out.println("  (размер: " + table.size() + ")");
    }

    // Вспомогательный метод для вывода хеш-таблицы без логического порядка (по корзинам)
    private static void printBucketState(HashTable table) {
        System.out.println("   Текущее состояние (по корзинам):");
        for (int i = 0; i < table.bucketCount; i++) {
            System.out.printf("   Корзина %d: ", i);
            Node current = table.heads[i];
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
