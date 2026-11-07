#include <iostream>
#include <string>
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
  bool valid_status(string stat) {
    return (stat == "New" || stat == "Contacted" || stat == "Qualified" ||
            stat == "Converted" || stat == "Lost");
  }
  Lead(string n, string p, string e, string src, string stat, double value)
      : Contact(n, p, e) {
    source = src;
    if (valid_status(stat))
      status = stat;
    else
      status = "New";
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

class Customer : public Contact {
private:
  string customer_type;
  double total_purchase;

  bool isValidCustomerType(string type) {
    return (type == "Regular" || type == "Premium" || type == "VIP");
  }

public:
  Customer() : Contact() {
    customer_type = "Regular";
    total_purchase = 0;
  }

  Customer(string n, string p, string e, string type, double purchase)
      : Contact(n, p, e) {

    if (isValidCustomerType(type))
      customer_type = type;
    else
      customer_type = "Regular";

    if (purchase < 0)
      total_purchase = 0;
    else
      total_purchase = purchase;
  }

  void set_customer_type(string type) {
    if (isValidCustomerType(type))
      customer_type = type;
    else
      cout << "Invalid customer type!\n";
  }

  string get_customer_type() const { return customer_type; }

  void set_total_purchase(double purchase) {
    if (purchase < 0)
      cout << "Purchase amount cannot be negative!\n";
    else
      total_purchase = purchase;
  }
  double get_total_purchase() const { return total_purchase; }
  void update_customer_type() {
    int op;

    cout << "\nUpdate Customer Type\n"
         << "1. Regular\n"
         << "2. Premium\n"
         << "3. VIP\n"
         << "4. Exit\n"
         << "Enter choice: ";

    cin >> op;

    switch (op) {
    case 1:
      set_customer_type("Regular");
      break;

    case 2:
      set_customer_type("Premium");
      break;

    case 3:
      set_customer_type("VIP");
      break;

    case 4:
      break;

    default:
      cout << "Invalid option! Customer type not updated.\n";
    }
  }
  void add_purchase() {
    double purchase;

    cout << "Enter purchase amount: ";
    cin >> purchase;

    if (purchase <= 0) {
      cout << "Invalid purchase amount!\n";
      return;
    }
    total_purchase += purchase;
    cout << "Purchase added successfully!\n";
  }
  void displaydetails() override {
    display_contactdetails();

    cout << "Customer Type: " << customer_type << endl;
    cout << "Total Purchase: " << total_purchase << endl;
  }
  string get_contact_type() override { return "Customer"; }
};

class FollowUp {
private:
  int taskId;
  int contactId;
  string description;
  string dueDate;
  string status;

  static int next_task_id;

  bool valid_status(string stat) {
    return (stat == "Pending" || stat == "Completed");
  }

public:
  FollowUp() {
    taskId = next_task_id++;
    contactId = 0;
    description = "";
    dueDate = "";
    status = "Pending";
  }

  FollowUp(int c_id, string desc, string date, string stat) {
    taskId = next_task_id++;

    contactId = c_id;
    description = desc;
    dueDate = date;

    if (valid_status(stat))
      status = stat;
    else
      status = "Pending";
  }

  int get_taskid() { return taskId; }

  int get_contactid() { return contactId; }

  string get_description() { return description; }

  string get_duedate() { return dueDate; }

  string get_status() { return status; }

  void set_contactid(int c_id) {
    if (c_id > 0)
      contactId = c_id;
    else
      cout << "Invalid Contact ID!\n";
  }

  void set_description(string desc) {
    if (desc.empty())
      cout << "Description cannot be empty!\n";
    else
      description = desc;
  }

  void set_duedate(string date) {
    if (date.empty())
      cout << "Due date cannot be empty!\n";
    else
      dueDate = date;
  }

  void set_status(string stat) {
    if (valid_status(stat))
      status = stat;
    else
      cout << "Invalid task status!\n";
  }

  void updateTask() {
    int op;
    cout << "1. Update Description\n";
    cout << "2. Update Due Date\n";
    cout << "3. Update Status\n";
    cout << "4. Edit all of them\n";
    cout << "Enter choice: ";
    cin >> op;
    string value;

    switch (op) {
    case 1:
      cout << "Enter new description: ";
      getline(cin, value);
      set_description(value);
      break;

    case 2:
      cout << "Enter new due date (DD-MM-YYYY): ";
      getline(cin, value);
      set_duedate(value);
      break;

    case 3:
      cout << "1. Pending\n2. Completed\n";
      cout << "Enter status: ";

      int choice;
      cin >> choice;

      if (choice == 1)
        set_status("Pending");
      else if (choice == 2)
        set_status("Completed");
      else
        cout << "Invalid option!\n";
      break;
    case 4:
      cout << "Enter new description: ";
      getline(cin, value);
      set_description(value);
      cout << "Enter new due date (DD-MM-YYYY): ";
      getline(cin, value);
      set_duedate(value);
      cout << "1. Pending\n2. Completed\n";
      cout << "Enter status: ";
      int stat;
      cin >> stat;

      if (stat == 1)
        set_status("Pending");
      else if (stat == 2)
        set_status("Completed");
      else
        cout << "Invalid option!\n";
      break;
    default:
      cout << "Invalid option!\n";
    }
  }

  void mark_complete() {
    status = "Completed";
    cout << "Task marked as completed!\n";
  }

  void display() {
    cout << "Task ID: " << taskId << endl;
    cout << "Contact ID: " << contactId << endl;
    cout << "Description: " << description << endl;
    cout << "Due Date: " << dueDate << endl;
    cout << "Status: " << status << endl;
  }
};

int FollowUp::next_task_id = 1;