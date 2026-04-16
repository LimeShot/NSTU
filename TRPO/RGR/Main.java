import java.util.*;

interface ParameterListener {
    void onChange(double newValue);
}

// Модель — пружинный маятник
class OscillatorModel {
    private double mass = 1.0;        // m, кг
    private double stiffness = 100.0; // k, Н/м
    private double amplitude = 0.1;   // A, м
    private double time = 0.0;        // t, с

    // Вычисляемые
    private double angularFrequency = 0.0;
    private double position = 0.0;
    private double velocity = 0.0;
    private double acceleration = 0.0;
    private double period = 0.0;
    private double frequency = 0.0;

    private Map<String, List<ParameterListener>> listeners = new HashMap<>();

    public OscillatorModel() {
        String[] params = {"mass", "stiffness", "amplitude", "time",
                           "angularFrequency", "position", "velocity", 
                           "acceleration", "period", "frequency"};
        for (String p : params) {
            listeners.put(p, new ArrayList<>());
        }
        recalcAll();
    }

    public void subscribe(String param, ParameterListener listener) {
        listeners.get(param).add(listener);
    }

    private void notify(String param, double value) {
        listeners.get(param).forEach(l -> l.onChange(value));
    }

    // Отдельные методы для каждого параметра
    public void setMass(double value) {
        mass = value;
        notify("mass", value);
        recalcAll();
    }

    public void setStiffness(double value) {
        stiffness = value;
        notify("stiffness", value);
        recalcAll();
    }

    public void setAmplitude(double value) {
        amplitude = value;
        notify("amplitude", value);
        recalcAll();
    }

    public void setTime(double value) {
        time = value;
        notify("time", value);
        recalcAll();
    }

    private void recalcAll() {
        double omega = Math.sqrt(stiffness / mass);
        angularFrequency = omega;
        period = 2 * Math.PI / omega;
        frequency = omega / (2 * Math.PI);

        position = amplitude * Math.cos(omega * time);
        velocity = -amplitude * omega * Math.sin(omega * time);
        acceleration = -amplitude * omega * omega * Math.cos(omega * time);

        notify("angularFrequency", angularFrequency);
        notify("position", position);
        notify("velocity", velocity);
        notify("acceleration", acceleration);
        notify("period", period);
        notify("frequency", frequency);
    }

    // Геттеры для начального отображения
    public double getMass() { return mass; }
    public double getStiffness() { return stiffness; }
    public double getAmplitude() { return amplitude; }
    public double getTime() { return time; }
    public double getPosition() { return position; }
    public double getVelocity() { return velocity; }
    public double getAcceleration() { return acceleration; }
    public double getPeriod() { return period; }
    public double getFrequency() { return frequency; }
    public double getAngularFrequency() { return angularFrequency; }
}

// Консольное представление
class View {
    public void bind(OscillatorModel model) {
        model.subscribe("mass", v -> show("Масса (m)", v, "кг"));
        model.subscribe("stiffness", v -> show("Жёсткость пружины (k)", v, "Н/м"));
        model.subscribe("amplitude", v -> show("Амплитуда (A)", v, "м"));
        model.subscribe("time", v -> show("Время (t)", v, "с"));
        model.subscribe("angularFrequency", v -> show("Угловая частота (ω)", v, "рад/с"));
        model.subscribe("position", v -> show("Положение x(t)", v, "м"));
        model.subscribe("velocity", v -> show("Скорость v(t)", v, "м/с"));
        model.subscribe("acceleration", v -> show("Ускорение a(t)", v, "м/с²"));
        model.subscribe("period", v -> show("Период колебаний (T)", v, "с"));
        model.subscribe("frequency", v -> show("Частота (f)", v, "Гц"));

        System.out.println("=== Пружинный маятник — начальные значения ===");
        show("Масса (m)", model.getMass(), "кг");
        show("Жёсткость пружины (k)", model.getStiffness(), "Н/м");
        show("Амплитуда (A)", model.getAmplitude(), "м");
        show("Время (t)", model.getTime(), "с");
        show("Угловая частота (ω)", model.getAngularFrequency(), "рад/с");
        show("Положение x(t)", model.getPosition(), "м");
        show("Скорость v(t)", model.getVelocity(), "м/с");
        show("Ускорение a(t)", model.getAcceleration(), "м/с²");
        show("Период колебаний (T)", model.getPeriod(), "с");
        show("Частота (f)", model.getFrequency(), "Гц");
        System.out.println();
    }

    private void show(String name, double value, String unit) {
        System.out.printf("%-30s = %8.4f %s%n", name, value, unit);
    }
}


class MassController {
    private OscillatorModel model;
    
    public MassController(OscillatorModel model) {
        this.model = model;
    }
    
    public void setValue(double value) {
        model.setMass(value);
    }
}

class StiffnessController {
    private OscillatorModel model;
    
    public StiffnessController(OscillatorModel model) {
        this.model = model;
    }
    
    public void setValue(double value) {
        model.setStiffness(value);
    }
}

class AmplitudeController {
    private OscillatorModel model;
    
    public AmplitudeController(OscillatorModel model) {
        this.model = model;
    }
    
    public void setValue(double value) {
        model.setAmplitude(value);
    }
}

class TimeController {
    private OscillatorModel model;
    
    public TimeController(OscillatorModel model) {
        this.model = model;
    }
    
    public void setValue(double value) {
        model.setTime(value);
    }
}

public class Main {
    public static void main(String[] args) {
        OscillatorModel model = new OscillatorModel();
        View view = new View();
        view.bind(model);

        MassController massCtrl = new MassController(model);
        StiffnessController stiffnessCtrl = new StiffnessController(model);
        AmplitudeController amplitudeCtrl = new AmplitudeController(model);
        TimeController timeCtrl = new TimeController(model);

        System.out.println("=== Изменяем параметры ===");

        amplitudeCtrl.setValue(0.2);        // отклоняем на 20 см
        System.out.println();

        stiffnessCtrl.setValue(200.0);     // более жёсткая пружина
        System.out.println();

        massCtrl.setValue(0.5);            // легче грузик
        System.out.println();

        timeCtrl.setValue(0.1571);         // смотрим в момент в половину периода
        System.out.println();
    }
}