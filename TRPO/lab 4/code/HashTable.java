import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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

        public ArrayList<Object> getAllObjects() {
            ArrayList<Object> list = new ArrayList<>();
            forEach(list::add);
            return list;
        }

        public String getBucketStructure() {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < bucketCount; i++) {
                sb.append("корзина ").append(i).append(": ");
                Node current = heads[i];
                if (current == null) {
                    sb.append("(пусто)");
                } else {
                    while (current != null) {
                        sb.append(current.value.toString());
                        if (current.next != null) {
                            sb.append(" -> ");
                        }
                        current = current.next;
                    }
                }
                sb.append("\n");
            }
            return sb.toString();
        }

        
    }