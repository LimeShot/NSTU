import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * @author Lime
 */
public class Main {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
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

    // Добавляем элементы из this, но не добавляем элементы из b, которых нет в this
    // Переписать со словарем?
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
        SparseMatrix result = new SparseMatrix(n, m);
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
        try (Scanner scanner = new Scanner(new File("numbers.txt"))){
            int n = scanner.nextInt();
            int m = scanner.nextInt();
            SparseMatrix returnMatrix = new SparseMatrix(n, m);
            while (scanner.hasNext()) {
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
        try (DataInputStream dis = new DataInputStream(new FileInputStream("file.bin"))) {
            int n = dis.readInt();
            int m = dis.readInt();
            SparseMatrix returnMatrix = new SparseMatrix(n, m);
            while(dis.available() > 0){
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
}
