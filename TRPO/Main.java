
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;

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
        public int x = 0;
        public int y = 0;
        public double v = 0;

        Elem(int x, int y, double v){
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

    public SparseMatrix(double[][] denseMatrix){
        this.n = denseMatrix.length;
        this.m = denseMatrix[0].length;
        elems = new ArrayList<>();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (denseMatrix[i][j] !=0){
                    elems.add(new Elem(i, j, denseMatrix[i][j]));
                }
            }
        }
    }

    public SparseMatrix add(SparseMatrix b){
        if (this.n != b.n || this.m != b.m){
            throw new IllegalArgumentException("Размерности матриц не совпадают");
        }
        SparseMatrix res = new SparseMatrix(this.n, this.m);

        for (Elem elemA: this.elems){
            boolean found = false;
            for (Elem elemB: b.elems){
                if (elemA.x == elemB.x && elemA.y == elemB.y){
                    res.elems.add(new Elem(elemA.x, elemA.y, elemA.v + elemB.v));
                    found = true;
                }

            }
            if (!found){
                res.elems.add(new Elem(elemA.x, elemA.y, elemA.v));
            }
        }
        return res;
    }

    public SparseMatrix multiply(SparseMatrix b){
        if (this.m != b.n){
            throw new IllegalArgumentException("Размерности матриц не совпадают");
        }
        SparseMatrix res = new SparseMatrix(this.n, b.m);

        for (Elem elemA: this.elems){
            for (Elem elemB: b.elems){
                if (elemA.y == elemB.x){
                    boolean found = false;
                    for (Elem elemRes: res.elems){
                        if (elemRes.x == elemA.x && elemRes.y == elemB.y){
                            elemRes.v += elemA.v * elemB.v;
                            found = true;
                        }
                    }
                    if (!found){
                        res.elems.add(new Elem(elemA.x, elemB.y, elemA.v * elemB.v));
                    }
                }
            }
        }
        return res;
    }

    public SparseMatrix transpose(){
        SparseMatrix result = new SparseMatrix(n, m);
        for (Elem e : elems) {
            result.elems.add(new Elem(e.y, e.x, e.v));
        }
        return result;
    }

    public void saveToText(String filePath) throws FileNotFoundException {
        PrintWriter writer = new PrintWriter(filePath);
        writer.println(n + " " + m);
        for (Elem e : elems) {
            writer.println(e.x + " " + e.y + " " + e.v);
        }
    }

    public void saveToBin(String filePath) throws FileNotFoundException {
        FileOutputStream stream = new FileOutputStream(filePath);
        
    }




}
