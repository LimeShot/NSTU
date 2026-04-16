import java.util.ArrayList;

public class UserFactory {
    private final ArrayList<UserType> types = new ArrayList<>();

    public UserFactory() {
        types.add(new DoubleType());
        types.add(new SparseMatrixType());
    }

    public ArrayList<String> getTypeNameList() {
        ArrayList<String> names = new ArrayList<>();
        for (UserType t : types) names.add(t.typeName());
        return names;
    }

    public UserType getBuilderByName(String name) {
        for (UserType t : types)
            if (t.typeName().equals(name))
                return t;
        return null;
    }
}