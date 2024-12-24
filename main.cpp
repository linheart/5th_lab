#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class PeripheralDevice {
 public:
  PeripheralDevice(const string &_id, const string &_brand, double _price,
                   const string &_deviceName)
      : id(_id), brand(_brand), price(_price), deviceName(_deviceName) {}

  virtual ~PeripheralDevice() {}

  virtual void displayInfo() const {
    cout << "Device: " << deviceName << "\n"
         << "ID: " << id << "\n"
         << "Brand: " << brand << "\n"
         << "Price: $" << price << "\n";
  }

  const string &getId() const { return id; }

 protected:
  string id;
  string brand;
  double price;
  string deviceName;
};

class Headphones : public PeripheralDevice {
 public:
  Headphones(const string &_id, const string &_brand, double _price,
             const string &_constructionType, const string &_mountingMethod)
      : PeripheralDevice(_id, _brand, _price, "Headphones"),
        constructionType(_constructionType),
        mountingMethod(_mountingMethod) {}

  void displayInfo() const override {
    PeripheralDevice::displayInfo();
    cout << "Construction Type: " << constructionType << "\n"
         << "Mounting Method: " << mountingMethod << "\n";
  }

 private:
  string constructionType;
  string mountingMethod;
};

class Microphone : public PeripheralDevice {
 public:
  Microphone(const string &_id, const string &_brand, double _price,
             const string &_frequencyRange, const string &_sensitivity)
      : PeripheralDevice(_id, _brand, _price, "Microphone"),
        frequencyRange(_frequencyRange),
        sensitivity(_sensitivity) {}

  void displayInfo() const override {
    PeripheralDevice::displayInfo();
    cout << "Frequency Range: " << frequencyRange << "\n"
         << "Sensitivity: " << sensitivity << "\n";
  }

 private:
  string frequencyRange;
  string sensitivity;
};

class Keyboard : public PeripheralDevice {
 public:
  Keyboard(const string &_id, const string &_brand, double _price,
           const string &_switchType, const string &_interfaceType)
      : PeripheralDevice(_id, _brand, _price, "Keyboard"),
        switchType(_switchType),
        interfaceType(_interfaceType) {}

  void displayInfo() const override {
    PeripheralDevice::displayInfo();
    cout << "Switch Type: " << switchType << "\n"
         << "Interface Type: " << interfaceType << "\n";
  }

 private:
  string switchType;
  string interfaceType;
};

class PeripheralFactory {
 public:
  virtual ~PeripheralFactory() {}
  virtual unique_ptr<PeripheralDevice> createDevice(
      const string &_id, const string &_brand, double _price,
      const string &_param1, const string &_param2) const = 0;
};

class HeadphonesFactory : public PeripheralFactory {
 public:
  unique_ptr<PeripheralDevice> createDevice(
      const string &_id, const string &_brand, double _price,
      const string &_constructionType,
      const string &_mountingMethod) const override {
    return make_unique<Headphones>(_id, _brand, _price, _constructionType,
                                   _mountingMethod);
  }
};

class MicrophoneFactory : public PeripheralFactory {
 public:
  unique_ptr<PeripheralDevice> createDevice(
      const string &_id, const string &_brand, double _price,
      const string &_frequencyRange,
      const string &_sensitivity) const override {
    return make_unique<Microphone>(_id, _brand, _price, _frequencyRange,
                                   _sensitivity);
  }
};

class KeyboardFactory : public PeripheralFactory {
 public:
  unique_ptr<PeripheralDevice> createDevice(
      const string &_id, const string &_brand, double _price,
      const string &_switchType, const string &_interfaceType) const override {
    return make_unique<Keyboard>(_id, _brand, _price, _switchType,
                                 _interfaceType);
  }
};

int main() {
  HeadphonesFactory headphonesFactory;
  MicrophoneFactory microphoneFactory;
  KeyboardFactory keyboardFactory;

  vector<unique_ptr<PeripheralDevice>> devices;

  devices.push_back(headphonesFactory.createDevice("HP001", "Sony", 99.99,
                                                   "Over-Ear", "Headband"));
  devices.push_back(microphoneFactory.createDevice("MC002", "Shure", 199.99,
                                                   "20Hz-20kHz", "-38dB"));
  devices.push_back(keyboardFactory.createDevice("KB003", "Logitech", 129.99,
                                                 "Mechanical", "USB"));

  cout << "Full List of Devices:" << endl;
  for (const auto &device : devices) {
    device->displayInfo();
    cout << "--------------------" << endl;
  }

  string searchId;
  cout << "Enter the ID of the device to search: ";
  cin >> searchId;

  bool found = false;
  for (const auto &device : devices) {
    if (device->getId() == searchId) {
      device->displayInfo();
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "\nDevice with ID " << searchId << " not found." << endl;
  }

  return 0;
}
