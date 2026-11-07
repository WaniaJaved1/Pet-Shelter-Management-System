#include <iostream>
#include <fstream>
using namespace std;

class Pet {
protected:
    int id;
    string name;
    int age;
    bool adopted;
    
public:
	Pet(int i , string n , int a){
		id =i;
		name=n;
		age=a;
		adopted= false;
	}
	int getId() {
        return id;
    }

    bool isAdopted() {
        return adopted;
    }

    void markAdopted() {
        adopted = true;
    }
    virtual string getType() = 0;
    virtual void display() = 0;
};

class Dog : public Pet{
	
private :
	string breed;
public:
	Dog(int i , string n , int a , string b) : Pet(i , n ,  a){
		breed = b;
	}
	string getType() override {
        return "Dog";
    }
    void display() override {
    if (!adopted) {
        cout << id << " | " << name << " | " << age
             << " | Dog | " << breed << endl;
    }
}
};
class Cat : public Pet{
	
private :
	string breed;
public:
	Cat(int i , string n , int a , string b) : Pet(i , n ,  a){
		breed = b;
	}
	string getType() override {
        return "Cat";
    }
    void display() override {
    if (!adopted) {
        cout << id << " | " << name << " | " << age
             << " | Cat | " << breed << endl;
    }
}
};
class Bird: public Pet{
	
private :
	string breed;
public:
	 Bird(int i , string n , int a , string b) : Pet(i , n ,  a){
		breed = b;
	}
	string getType() override {
        return "Bird";
    }
   void display() override {
    if (!adopted) {
        cout << id << " | " << name << " | " << age
             << " | Bird | " << breed << endl;
    }
}
};
class Adopter {
public:
    string cnic;
    string name;
    string phone;


    Adopter(string c, string n, string p) {
        cnic = c;
        name = n;
        phone = p;
    }
};
class Adoption{
	public:
    static int totalAdoptions;

    void saveRecord(Pet* pet, Adopter a) {
        ofstream file("adoptions.txt",ios::app);

        file << "Pet ID: " << pet->getId() << endl;
        file << "Pet Type: " << pet->getType() << endl;
        file << "Adopter CNIC: " << a.cnic << endl;
        file << "Adopter Name: " << a.name << endl;
        file << "Phone: " << a.phone << endl;
        
        cout<< endl;

        file.close();

        totalAdoptions++;
    }
    
     void viewRecords() {
        ifstream file("adoptions.txt");

        string line;
        int count =0;
        
        cout <<"ADOPTION RECORDS" << endl;
        
        while (getline(file, line)) {
            cout << line << endl;
            count++;
        }
        cout << endl;
        
        file.close();
        if (count == 0) {
        cout << "No adoption yet" << endl;
    }
    }
};
int Adoption::totalAdoptions = 0;

int main() {

    Pet* pets[20];
    int petCount = 6;

    Adoption adoption;

    pets[0] = new Dog(101, "Bruno", 2, "Labrador");
    pets[1] = new Dog(102, "Max", 3, "German Shepherd");
    pets[2] = new Cat(201, "Luna", 1, "Persian");
    pets[3] = new Cat(202, "Kitty", 2, "Siamese");
    pets[4] = new Bird(301, "Coco", 1, "Parrot");
    pets[5] = new Bird(302, "Rio", 2, "Canary");
    
    int choice;

    do {
        cout << "PET SHELTER SYSTEM " << endl;
        cout << "1. View Available Pets" << endl;
        cout << "2. Adopt Pet" << endl;
        cout << "3. View Adoption Records" << endl;
        cout << "4. Add New Pet" << endl;
        cout << "5. Exit"<< endl;
        cout << "Enter choice: ";
        cin >> choice;
        
    switch(choice){
         case 1: {
            cout << endl << "ID | Name | Age | Type | Breed" << endl;
            for (int i = 0; i < petCount; i++) {
                pets[i]->display();
            }
            break;
        }

        case 2: {
            int id;
            cout << "Enter Pet ID: ";
            cin >> id;

            Pet* selected = NULL;

            for (int i = 0; i < petCount; i++) {
                if (pets[i]->getId() == id && !pets[i]->isAdopted()) {
                    selected = pets[i];
                    break;
                }
            }

            if (selected == NULL) {
                cout << "Not available" << endl;
            }
            else {
                string cnic, name, phone;

                cout << "Enter CNIC: ";
                cin >> cnic;
                
                cout << "Enter Name: ";
                cin >> name;

                cout << "Enter Phone: ";
                cin >> phone;

                Adopter a(cnic, name, phone);

                selected->markAdopted();
                adoption.saveRecord(selected, a);

                cout << "Adopted Successfully" << endl;
            }
            break;
        }

        case 3: {
            adoption.viewRecords();
            break;
        }

        case 4: {
            if (petCount >= 20) {
                cout << "Full" << endl;
                break;
            }

            string type, name, breed;
            int id, age;

            cout << "Type: ";
            cin >> type;

            cout << "ID: ";
            cin >> id;

            cout << "Name: ";
            cin >> name;

            cout << "Age: ";
            cin >> age;

            cout << "Breed: ";
            cin >> breed;

            if (type == "Dog") {
                pets[petCount] = new Dog(id, name, age, breed);
            }
            else if (type == "Cat") {
                pets[petCount] = new Cat(id, name, age, breed);
            }
            else if (type == "Bird") {
                pets[petCount] = new Bird(id, name, age, breed);
            }
            else {
                cout << "Invalid" << endl;
                break;
            }

            petCount++;
            cout << "Added" << endl;
            break;
        }

        case 5: {
            cout << "Exit" << endl;
            break;
        }

        default: {
            cout << "Invalid" << endl;
        }

        }
} while (choice != 5);

    return 0;
}