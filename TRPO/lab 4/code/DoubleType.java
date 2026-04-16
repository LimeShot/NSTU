import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

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
            try {
                String trimmed = ss.trim();
                if (trimmed.isEmpty()) {
                    throw new IllegalArgumentException("Expected a double value, got empty string");
                }
                return Double.parseDouble(trimmed);
            } catch (NumberFormatException e) {
                throw new IllegalArgumentException("Invalid double value: " + ss);
            }
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