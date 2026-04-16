import javax.swing.*;
import javax.swing.BoxLayout;
import javax.swing.BorderFactory;
import java.awt.*;
import java.util.ArrayList;


public class MainWindow extends JFrame {
    private UserFactory factory;
    private UserType currentType;
    private HashTable table;

    private JComboBox<String> typeComboBox;
    private JTextArea inputTextArea;
    private JButton addButton;
    private JButton sortButton;
    private JButton addByIndexButton;
    private JButton removeByIndexButton;
    private JTextField indexTextField;
    private JList<String> objectList;
    private DefaultListModel<String> listModel;

    public MainWindow() {
        factory = new UserFactory();
        currentType = factory.getBuilderByName("double"); // тип по умолчанию
        table = new HashTable(5, currentType);

        setTitle("Универсальная структура данных (Лабораторная работа №4)");
        setSize(1000, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout(10, 10));

        initComponents();
        updateObjectList();

        setVisible(true);
    }

    private void initComponents() {
        // Панель выбора типа
        JPanel topPanel = new JPanel();
        topPanel.add(new JLabel("Тип данных:"));
        typeComboBox = new JComboBox<>();
        for (String name : factory.getTypeNameList()) {
            typeComboBox.addItem(name);
        }
        typeComboBox.setSelectedItem(currentType.typeName());
        typeComboBox.addActionListener(e -> {
            String selected = (String) typeComboBox.getSelectedItem();
            currentType = factory.getBuilderByName(selected);
            // При смене типа очищаем таблицу и пересоздаём её
            table = new HashTable(10, currentType);
            updateObjectList();
        });
        topPanel.add(typeComboBox);

        // Поле ввода
        inputTextArea = new JTextArea(4, 50);
        inputTextArea.setText("3.14"); // пример для double
        inputTextArea.setLineWrap(true);
        inputTextArea.setWrapStyleWord(true);

        // Кнопка добавления
        addButton = new JButton("Добавить");
        addButton.addActionListener(e -> addElementFromInput());

        // Кнопка сортировки
        sortButton = new JButton("Сортировать");
        sortButton.addActionListener(e -> {
            HashTable sorted = table.sort();
            table = sorted; // заменяем текущую таблицу отсортированной
            updateObjectList();
            JOptionPane.showMessageDialog(this, "Таблица отсортирована!");
        });

        // Основная панель ввода
        JPanel inputSection = new JPanel(new BorderLayout(5, 5));
        inputSection.setBorder(BorderFactory.createTitledBorder("Добавление элемента"));
        
        JPanel inputFieldPanel = new JPanel(new BorderLayout());
        inputFieldPanel.add(new JLabel("Значение:"), BorderLayout.WEST);
        inputFieldPanel.add(new JScrollPane(inputTextArea), BorderLayout.CENTER);
        inputSection.add(inputFieldPanel, BorderLayout.CENTER);
        
        JPanel inputButtonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        inputButtonPanel.add(addButton);
        inputButtonPanel.add(sortButton);
        inputSection.add(inputButtonPanel, BorderLayout.SOUTH);

        // Панель для работы с индексами
        JPanel indexSection = new JPanel(new BorderLayout(5, 5));
        indexSection.setBorder(BorderFactory.createTitledBorder("Работа по индексу"));
        
        JPanel indexInputPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        indexInputPanel.add(new JLabel("Индекс:"));
        indexTextField = new JTextField(8);
        indexInputPanel.add(indexTextField);
        
        addByIndexButton = new JButton("Вставить");
        addByIndexButton.addActionListener(e -> insertElementByIndex());
        indexInputPanel.add(addByIndexButton);
        
        removeByIndexButton = new JButton("Удалить");
        removeByIndexButton.addActionListener(e -> removeElementByIndex());
        indexInputPanel.add(removeByIndexButton);
        
        indexSection.add(indexInputPanel, BorderLayout.NORTH);

        // Список объектов
        listModel = new DefaultListModel<>();
        objectList = new JList<>(listModel);
        objectList.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane listScroll = new JScrollPane(objectList);
        listScroll.setBorder(BorderFactory.createTitledBorder("Элементы таблицы"));

        add(topPanel, BorderLayout.NORTH);
        
        JPanel centerPanel = new JPanel(new BorderLayout(5, 5));
        centerPanel.add(inputSection, BorderLayout.NORTH);
        centerPanel.add(indexSection, BorderLayout.CENTER);
        add(centerPanel, BorderLayout.CENTER);
        
        add(listScroll, BorderLayout.SOUTH);
    }

    private void addElementFromInput() {
        String input = inputTextArea.getText().trim();
        if (input.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Введите значение!");
            return;
        }

        try {
            // Используем parseValue прототипа для создания объекта
            Object newObj = currentType.parseValue(input);

            // Добавляем клон (на случай, если объект будет изменён позже)
            table.addToEnd(newObj);

            updateObjectList();
            inputTextArea.setText("");
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this,
                "Ошибка парсинга значения для типа " + currentType.typeName() + ":\n" + ex.getMessage(),
                "Ошибка ввода", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void insertElementByIndex() {
        String input = inputTextArea.getText().trim();
        String indexStr = indexTextField.getText().trim();
        
        if (input.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Введите значение!");
            return;
        }

        try {
            Object newObj = currentType.parseValue(input);
            
            if (indexStr.isEmpty()) {
                // Если индекс не указан, добавляем в конец
                table.addToEnd(newObj);
            } else {
                // Если индекс указан, вставляем по индексу
                int index = Integer.parseInt(indexStr);
                table.insert(newObj, index);
            }
            
            updateObjectList();
            inputTextArea.setText("");
            indexTextField.setText("");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Неверный индекс!");
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this,
                "Ошибка: " + ex.getMessage(),
                "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void removeElementByIndex() {
        String indexStr = indexTextField.getText().trim();
        
        if (indexStr.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Введите индекс для удаления!");
            return;
        }

        try {
            int index = Integer.parseInt(indexStr);
            table.delete(index);
            updateObjectList();
            indexTextField.setText("");
            JOptionPane.showMessageDialog(this, "Элемент удалён!");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Неверный индекс!");
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this,
                "Ошибка: " + ex.getMessage(),
                "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void updateObjectList() {
        listModel.clear();
        ArrayList<Object> objects = table.getAllObjects();
    
        for (int i = 0; i < objects.size(); i++) {
            Object obj = objects.get(i);
            String display = String.format("[%d] %s", i, obj.toString());
            listModel.addElement(display);
        }
    }


    public static void main(String[] args) {
        SwingUtilities.invokeLater(MainWindow::new);
    }
}