#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Vehicle {
protected:
    string manufacturer;
    string model;
    int year;
    double fuelConsumption;
    
    Vehicle(string m, string mdl, int y, double fc) 
        : manufacturer(m), model(mdl), year(y), fuelConsumption(fc) {}
        
public:
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual string getDescription() const = 0;
    virtual double calculateRange(double fuelAmount) const = 0;
    
    virtual ~Vehicle() = default;
};

ostream& operator<<(ostream& out, const Vehicle& v) {
    out << v.getDescription();
    return out;
}

class Car : public Vehicle {
    int doors;
    double trunkCapacity;
    
public:
    Car(string m, string mdl, int y, double fc, int d, double trunk) 
        : Vehicle(m, mdl, y, fc), doors(d), trunkCapacity(trunk) {}
        
    void startEngine() override {
        cout << "Car engine started: " << manufacturer << " " << model << endl;
    }
    
    void stopEngine() override {
        cout << "Car engine stopped: " << manufacturer << " " << model << endl;
    }
    
    string getDescription() const override {
        return "Car: " + manufacturer + " " + model + ", year: " + to_string(year) + 
               ", doors: " + to_string(doors);
    }
    
    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelConsumption;
    }
    
    void openTrunk() {
        cout << "Trunk opened. Capacity: " << trunkCapacity << " liters" << endl;
    }
};

class Truck : public Vehicle {
    double cargoCapacity;
    bool hasTrailer;
    
public:
    Truck(string m, string mdl, int y, double fc, double cargo, bool trailer) 
        : Vehicle(m, mdl, y, fc), cargoCapacity(cargo), hasTrailer(trailer) {}
        
    void startEngine() override {
        cout << "Truck engine started: " << manufacturer << " " << model << endl;
    }
    
    void stopEngine() override {
        cout << "Truck engine stopped: " << manufacturer << " " << model << endl;
    }
    
    string getDescription() const override {
        string trailerInfo = hasTrailer ? "yes" : "no";
        return "Truck: " + manufacturer + " " + model + ", year: " + to_string(year) + 
               ", cargo: " + to_string(cargoCapacity) + " kg, trailer: " + trailerInfo;
    }
    
    double calculateRange(double fuelAmount) const override {
        double range = fuelAmount * fuelConsumption;
        if (hasTrailer) range *= 0.7;
        return range;
    }
    
    void loadCargo() {
        cout << "Loading cargo into truck. Max capacity: " << cargoCapacity << " kg" << endl;
    }
};

class Motorcycle : public Vehicle {
    string engineType;
    bool hasSideCar;
    
public:
    Motorcycle(string m, string mdl, int y, double fc, string eType, bool sidecar) 
        : Vehicle(m, mdl, y, fc), engineType(eType), hasSideCar(sidecar) {}
        
    void startEngine() override {
        cout << "Motorcycle engine started: " << manufacturer << " " << model << endl;
    }
    
    void stopEngine() override {
        cout << "Motorcycle engine stopped: " << manufacturer << " " << model << endl;
    }
    
    string getDescription() const override {
        string sidecarInfo = hasSideCar ? "yes" : "no";
        return "Motorcycle: " + manufacturer + " " + model + ", year: " + to_string(year) + 
               ", engine: " + engineType + ", sidecar: " + sidecarInfo;
    }
    
    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelConsumption * 1.2;
    }
    
    void doWheelie() {
        cout << "Motorcycle doing wheelie!" << endl;
    }
};

unique_ptr<Vehicle> createVehicle(const string& type) {
    if (type == "Car") {
        return make_unique<Car>("Toyota", "Camry", 2020, 12.5, 4, 480.0);
    }
    else if (type == "Truck") {
        return make_unique<Truck>("Kamaz", "6520", 2018, 5.2, 15000.0, true);
    }
    else if (type == "Motorcycle") {
        return make_unique<Motorcycle>("Ural", "GearUp", 2021, 20.0, "boxer-twin", true);
    }
    return nullptr;
}

int main() {
    vector<unique_ptr<Vehicle>> vehicles;
    
    vehicles.push_back(make_unique<Car>("Volvo", "XC90", 2022, 10.3, 5, 550.0));
    vehicles.push_back(make_unique<Truck>("MAZ", "6430", 2019, 4.8, 20000.0, false));
    vehicles.push_back(make_unique<Motorcycle>("IZH", "Planeta", 1990, 25.0, "two-stroke", false));
    
    auto factoryVehicle = createVehicle("Car");
    if (factoryVehicle) vehicles.push_back(move(factoryVehicle));
    
    cout << "All vehicles:" << endl;
    for (const auto& v : vehicles) {
        cout << *v << endl;
    }
    
    cout << "\nStarting engines (polymorphism):" << endl;
    for (const auto& v : vehicles) {
        v->startEngine();
    }
    
    cout << "\nDescriptions (polymorphism):" << endl;
    for (const auto& v : vehicles) {
        cout << v->getDescription() << endl;
    }
    
    cout << "\nCalculating range for 50 liters:" << endl;
    for (const auto& v : vehicles) {
        cout << "Can travel: " << v->calculateRange(50.0) << " km" << endl;
    }
    
    return 0;
}