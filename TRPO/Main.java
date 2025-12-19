import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Тестирование класса SparseMatrix ===\n");
        
        // Тест 1: Создание матрицы из двумерного массива
        System.out.println("Тест 1: Создание матрицы из двумерного массива");
        double[][] denseArray = {
            {1, 0, 0, 2},
            {0, 3, 0, 0},
            {4, 0, 5, 0}
        };
        SparseMatrix m1 = new SparseMatrix(denseArray);
        System.out.println("Матрица 1 (3x4): " + m1.elems.size() + " элементов (ожидается 4)");
        m1.printMatrixDense();
        
        // Тест 2: Создание матрицы с заданными размерами
        System.out.println("\nТест 2: Создание матрицы с заданными размерами и добавление элементов");
        SparseMatrix m2 = new SparseMatrix(3, 4);
        m2.setElem(0, 1, 5);
        m2.setElem(1, 0, 6);
        m2.setElem(2, 3, 7);
        System.out.println("Матрица 2 (3x4): " + m2.elems.size() + " элементов (ожидается 3)");
        m2.printMatrixDense();
        
        // Тест 3: Сложение матриц
        System.out.println("\nТест 3: Сложение матриц m1 + m2");
        SparseMatrix m3 = m1.add(m2);
        System.out.println("Результат сложения: " + m3.elems.size() + " элементов");
        m3.printMatrixDense();
        
        // Тест 4: Умножение на скаляр
        System.out.println("\nТест 4: Умножение матрицы m1 на скаляр 2");
        SparseMatrix m4 = m1.multiply(2);
        System.out.println("Результат умножения на 2: " + m4.elems.size() + " элементов");
        m4.printMatrixDense();
        
        // Тест 5: Транспонирование
        System.out.println("\nТест 5: Транспонирование матрицы m1 (3x4 -> 4x3)");
        SparseMatrix m5 = m1.transpose();
        System.out.println("Транспонированная матрица: размер " + m5.n + "x" + m5.m + ", элементов: " + m5.elems.size());
        m5.printMatrixDense();
        
        // Тест 6: Умножение матриц
        System.out.println("\nТест 6: Умножение матриц (m5 [4x3] * m1 [3x4])");
        SparseMatrix m6 = m5.multiply(m1);
        System.out.println("Результат умножения (4x4): " + m6.elems.size() + " элементов");
        m6.printMatrixDense();
        
        // Тест 7: Сохранение и загрузка текстовый формат
        System.out.println("\nТест 7: Сохранение и загрузка текстовый формат");
        String txtFile = "matrix_test.txt";
        m1.saveToText(txtFile);
        SparseMatrix m7 = SparseMatrix.loadFromTxt(txtFile);
        System.out.println("Загруженная матрица: размер " + m7.n + "x" + m7.m + ", элементов: " + m7.elems.size());
        System.out.println("Матрицы совпадают: " + m1.matricesEqual(m7));
        
        // Тест 8: Сохранение и загрузка двоичный формат
        System.out.println("\nТест 8: Сохранение и загрузка двоичный формат");
        String binFile = "matrix_test.bin";
        m1.saveToBin(binFile);
        SparseMatrix m8 = SparseMatrix.loadFromBin(binFile);
        System.out.println("Загруженная матрица: размер " + m8.n + "x" + m8.m + ", элементов: " + m8.elems.size());
        System.out.println("Матрицы совпадают: " + m1.matricesEqual(m8));
        
        // Тест 9: Обновление элемента
        System.out.println("\nТест 9: Обновление элемента");
        SparseMatrix m9 = new SparseMatrix(2, 2);
        m9.setElem(0, 0, 5);
        System.out.println("После добавления (0,0)=5: " + m9.elems.size() + " элементов");
        m9.setElem(0, 0, 10);
        System.out.println("После обновления (0,0)=10: " + m9.elems.size() + " элементов");
        m9.printMatrixDense();
        
        // Тест 10: Удаление элемента
        System.out.println("\nТест 10: Удаление элемента путём установки в 0");
        m9.setElem(0, 0, 0);
        System.out.println("После установки (0,0)=0: " + m9.elems.size() + " элементов (ожидается 0)");
        
        System.out.println("\n=== Все тесты завершены ===");
    }
    

}

class SparseMatrix {
    int n;
    int m;
    ArrayList<Elem> elems;

    private class Elem {
        public int x;
        public int y;
        public double v;

        Elem(int x, int y, double v) {
            this.x = x;
            this.y = y;
            this.v = v;
        }
    }

    public SparseMatrix() {
        this.n = 0;
        this.m = 0;
        elems = new ArrayList<>();
    }

    public SparseMatrix(int n, int m) {
        this.n = n;
        this.m = m;
        elems = new ArrayList<>();
    }

    public SparseMatrix(double[][] denseMatrix) {
        this.n = denseMatrix.length;
        this.m = denseMatrix[0].length;
        elems = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (denseMatrix[i][j] != 0) {
                    elems.add(new Elem(i, j, denseMatrix[i][j]));
                }
            }
        }
    }

    public SparseMatrix add(SparseMatrix b) {
        if (this.n != b.n || this.m != b.m) {
            throw new IllegalArgumentException("Размерности матриц не совпадают");
        }
        SparseMatrix res = new SparseMatrix(this.n, this.m);

        for (Elem elemA : this.elems) {
            boolean found = false;
            for (Elem elemB : b.elems) {
                if (elemA.x == elemB.x && elemA.y == elemB.y) {
                    if (elemA.v + elemB.v != 0)
                        res.elems.add(new Elem(elemA.x, elemA.y, elemA.v + elemB.v));
                    found = true;
                }
            }
            if (!found)
                res.elems.add(new Elem(elemA.x, elemA.y, elemA.v));
        }

        for (Elem elemB : b.elems) {
            boolean found = false;
            for (Elem elemA : this.elems) {
                if (elemA.x == elemB.x && elemA.y == elemB.y) {
                    found = true;
                    break;
                }
            }
            if (!found)
                res.elems.add(new Elem(elemB.x, elemB.y, elemB.v));
        }
        return res;
    }

    public SparseMatrix multiply(SparseMatrix b) {
        if (this.m != b.n) {
            throw new IllegalArgumentException("Размерности матриц не совпадают");
        }
        SparseMatrix res = new SparseMatrix(this.n, b.m);

        for (Elem elemA : this.elems) {
            for (Elem elemB : b.elems) {
                if (elemA.y == elemB.x) {
                    boolean found = false;
                    for (Elem elemRes : res.elems) {
                        if (elemRes.x == elemA.x && elemRes.y == elemB.y) {
                            elemRes.v += elemA.v * elemB.v;
                            found = true;
                        }
                    }
                    if (!found)
                        res.elems.add(new Elem(elemA.x, elemB.y, elemA.v * elemB.v));
                }
            }
        }

        for (Elem elemRes : res.elems) {
            if (elemRes.v == 0)
                res.elems.remove(elemRes);
        }
        return res;
    }

    public SparseMatrix multiply(double b) {
        SparseMatrix res = new SparseMatrix(this.n, this.m);
        for (Elem elemA : this.elems)
            res.elems.add(new Elem(elemA.x, elemA.y, elemA.v * b));
        return res;
    }

    public SparseMatrix transpose() {
        SparseMatrix result = new SparseMatrix(m, n);
        for (Elem e : elems) 
            result.elems.add(new Elem(e.y, e.x, e.v));
        return result;
    }

    public SparseMatrix setElem(int x, int y, double v) {
        for (Elem e : elems) {
            if (e.x == x && e.y == y) {
                if (v == 0) 
                    elems.remove(e);
                else 
                    e.v = v;
                return this;
            }
        }
        elems.add(new Elem(x, y, v));
        return this;
    }

    public void saveToText(String filePath) {
        try (PrintWriter writer = new PrintWriter(filePath)) {
            writer.println(n + " " + m);
            for (Elem e : elems)
                writer.println(e.x + " " + e.y + " " + e.v);
        } catch (IOException e) {
            System.err.println("Ошибка при сохранении файла: " + e.getMessage());
        }
    }

    public void saveToBin(String fileName) {
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(fileName))) {
            dos.writeInt(n);
            dos.writeInt(m);
            dos.writeInt(elems.size());
            for (Elem e : elems) {
                dos.writeInt(e.x);
                dos.writeInt(e.y);
                dos.writeDouble(e.v);
            }
            System.out.println("Файл успешно сохранен: " + fileName);
        } catch (IOException e) {
            System.err.println("Ошибка при сохранении файла: " + e.getMessage());
        }
    }

    public static SparseMatrix loadFromTxt(String filePath) {
        try (Scanner scanner = new Scanner(new File(filePath))){
            scanner.useLocale(java.util.Locale.US);
            int n = scanner.nextInt();
            int m = scanner.nextInt();
            SparseMatrix returnMatrix = new SparseMatrix(n, m);
            while (scanner.hasNextInt()) {
                int x = scanner.nextInt();
                int y = scanner.nextInt();
                double v = scanner.nextDouble();
                returnMatrix.setElem(x,y,v);
            }
            return returnMatrix;
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла:" + e.getMessage());
            return new SparseMatrix();
        }
    }

    public static SparseMatrix loadFromBin (String filePath){
        try (DataInputStream dis = new DataInputStream(new FileInputStream(filePath))) {
            int n = dis.readInt();
            int m = dis.readInt();
            int count = dis.readInt();
            SparseMatrix returnMatrix = new SparseMatrix(n, m);
            for(int i = 0; i < count; i++){
                int x = dis.readInt();
                int y = dis.readInt();
                double v = dis.readDouble();
                returnMatrix.setElem(x,y,v);
            }
            return returnMatrix;
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла:" + e.getMessage());
            return new SparseMatrix();
        }
    }

    public void printMatrixDense() {
        System.out.println("Размер: " + n + "x" + m);
        double[][] dense = new double[n][m];
        for (Elem e : elems) {
            dense[e.x][e.y] = e.v;
        }
        for (int i = 0; i < n; i++) {
            System.out.print("[");
            for (int j = 0; j < m; j++) {
                System.out.printf("%6.1f", dense[i][j]);
                if (j < m - 1) System.out.print(" ");
            }
            System.out.println("]");
        }
    }

    public boolean matricesEqual(SparseMatrix other) {
        if (this.n != other.n || this.m != other.m || this.elems.size() != other.elems.size()) {
            return false;
        }
        for (int i = 0; i < this.elems.size(); i++) {
            Elem e1 = this.elems.get(i);
            Elem e2 = other.elems.get(i);
            if (e1.x != e2.x || e1.y != e2.y || e1.v != e2.v) {
                return false;
            }
        }
        return true;
    }
}
