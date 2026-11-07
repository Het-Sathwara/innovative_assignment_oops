#include <iostream>
#include <vector>

using namespace std;
class Contact {
private:
  int contactid;
  string name;
  string phone;
  string email;
  static int next_contactid;

protected:
  Contact() {
    contactid = next_contactid++;
    name = "";
    phone = "";
    email = "";
  }
  Contact(string name1, string phone1, string email1) {
    contactid = next_contactid++;
    name = name1;
    phone = phone1;
    email = email1;
  }
  void display_contactdetails() {
    cout << "Contact ID: " << contactid << endl;
    cout << "Name: " << name << endl;
    cout << "Phone Number: " << phone << endl;
    cout << "Email: " << email << endl;
  }

public:
  int getid() const { return contactid; }
  string get_name() const { return name; }
  void update_details() {
    cout << endl << "Name: ";
    getline(cin, name);
    cout << endl << "Phone Number: ";
    cin >> phone;
    cout << endl << "Email: ";
    cin >> email;
  }
  virtual void displaydetails() = 0;
  virtual string get_contact_type() = 0;
  virtual ~Contact();
};

int Contact::next_contactid = 1;

class Lead : public Contact {
private:
  string source;
  string status;
  double estimated_value;

public:
  Lead() : Contact() {
    source = "unknown";
    status = "new";
    estimated_value = 0;
  }
  Lead(string n, string p, string e, string src, string stat, double value)
      : Contact(n, p, e) {
    source = src;
    status = stat;
    if (value < 0)
      estimated_value = 0;
    else
      estimated_value = value;
  }
  void update_status() {
    int op;
    cout << "Update Status \n1. New \n2. Contacted \n3. Qualified \n4. "
            "Converted \n5. Lost: \n6. Exit";
    cin >> op;
    switch (op) {
    case 1:
      status = "New";
      break;
    case 2:
      status = "Contacted";
      break;
    case 3:
      status = "Qualified";
      break;
    case 4:
      status = "Converted";
      break;
    case 5:
      status = "Lost";
      break;
    case 6:
      break;
    default:
      cout << "Invalid option! Status not updated.\n";
      break;
    }
  }
  void update_estimated_value() {
    double value;
    cout << "Update Value: ";
    cin >> value;
    if (value < 0)
      estimated_value = 0;
    else
      estimated_value = value;
  }
  void displaydetails() override {
    display_contactdetails();
    cout << "Lead Source: " << source << endl;
    cout << "Lead Status: " << status << endl;
    cout << "Estimate Value: " << estimated_value << endl;
  }
  string get_contact_type() override { return "Lead"; }
};