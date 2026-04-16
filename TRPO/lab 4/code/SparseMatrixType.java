import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Locale;
import java.util.Scanner;

public class SparseMatrixType implements UserType {

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
        Scanner scanner = new Scanner(line).useLocale(Locale.US);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        SparseMatrix matrix = new SparseMatrix(n, m);

        while ((line = br.readLine()) != null) {
            scanner = new Scanner(line).useLocale(Locale.US);
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
        Scanner scanner = new Scanner(ss).useLocale(Locale.US);
        if (!scanner.hasNextInt()) {
            throw new IllegalArgumentException("Expected format: n m x1 y1 v1 x2 y2 v2 ...");
        }
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        SparseMatrix matrix = new SparseMatrix(n, m);
        
        while (scanner.hasNextInt()) {
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            if (!scanner.hasNextDouble()) {
                throw new IllegalArgumentException("Missing value for element at (" + x + ", " + y + ")");
            }
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