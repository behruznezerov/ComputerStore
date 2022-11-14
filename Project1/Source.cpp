#include <iostream>
using namespace std;

class ComputerStore;

class Computer {

	int objectid;
	char* model = nullptr;
	char* vendor = nullptr;
	char* videocard = nullptr;
	char* monitor = nullptr;
	double cpuhz = 0;
	int core = 0;
	int ram = 0;
	int sized = 0;
	bool ssd = true;
	static int staticid;

public:
	friend class ComputerStore;




	Computer() {
		objectid = ++staticid;
	}

	Computer(const char* m, const char* v, const char* vc, const char* mon, double hz, int c, int r, int ds, bool isS) {

		objectid = ++staticid;
		SetModel(m);
		SetVendor(v);
		Setvideocard(vc);
		SetMonitor(mon);
		SetCore(c);
		SetCpuHz(hz);
		SetRam(r);
		SetDiskSize(ds);
		Setssd(isS);

	}

	Computer(const Computer& other) {

		objectid = other.objectid;
		SetModel(other.model);
		SetVendor(other.vendor);
		Setvideocard(other.videocard);
		SetMonitor(other.monitor);
		SetCore(other.core);
		SetCpuHz(other.cpuhz);
		SetRam(other.ram);
		SetDiskSize(other.sized);
		Setssd(other.ssd);

	}

	~Computer()
	{
		delete[] model;
		delete[] vendor;
		delete[] monitor;
		delete[] videocard;
	}



	void SetModel(const char* m) {
		delete[] model;
		int len = strlen(m) + 1;
		model = new char[len];
		strcpy_s(model, len, m);
	}

	void SetVendor(const char* v) {
		delete[] vendor;
		int len = strlen(v) + 1;
		vendor = new char[len];
		strcpy_s(vendor, len, v);
	}

	void Setvideocard(const char* vc) {
		delete[] videocard;
		int len = strlen(vc) + 1;
		videocard = new char[len];
		strcpy_s(videocard, len, vc);
	}

	void SetMonitor(const char* mon) {
		delete[] monitor;
		int len = strlen(mon) + 1;
		monitor = new char[len];
		strcpy_s(monitor, len, mon);
	}
	void SetCpuHz(double hz) {
		cpuhz = hz;
	}

	void SetCore(int c) {
		core = c;
	}

	void SetRam(int r) {
		ram = r;
	}

	void SetDiskSize(int ds) {
		sized = ds;
	}

	void Setssd(bool isS) {
		ssd = isS;
	}



	friend ostream& operator<<(ostream& out, const Computer& obj) {
		out << "Computer \n"
			<< "objectid:" << obj.objectid
			<< "\nVendor: " << obj.vendor
			<< "\nModel: " << obj.model
			<< "\nMonitor: " << obj.monitor
			<< "\nCpuHz: " << obj.cpuhz
			<< "\nCore: " << obj.core
			<< "\nRam: " << obj.ram
			<< "\nDisksize: " << obj.sized
			<< "\nSsd: " << obj.ssd << "\n";
		return out;
	}

	friend istream& operator>>(istream& in, Computer& obj) {
		char* bf = new char[40];
		cout << "Model: ";
		in.getline(bf, 40);
		obj.SetModel(bf);

		cout << "Vendor: ";
		in.getline(bf, 40);
		obj.SetVendor(bf);

		cout << "videocard: ";
		in.getline(bf, 40);
		obj.Setvideocard(bf);

		cout << "Monitor: ";
		in.getline(bf, 40);
		obj.SetMonitor(bf);

		cout << "Cpuhz: ";
		double y;
		cin >> y;
		obj.SetCpuHz(y);

		cout << "Core: ";
		int c;
		cin >> c;
		obj.SetCore(c);

		cout << "Ram: ";
		int r;
		cin >> r;
		obj.SetRam(r);

		cout << "Disk Size: ";
		int d;
		cin >> d;
		obj.SetDiskSize(d);

		cout << " SSD ? (1 = Yes, 0 = No) : ";
		int i;
		cin >> i;
		obj.Setssd(i);

		delete[] bf;
		return in;
	}



};

int Computer::staticid = 0;

class ComputerStore {
	char* storeName = nullptr;
	char* storeAdress = nullptr;
	int size = 0;
	Computer** computers = nullptr;
public:



	ComputerStore() = default;

	ComputerStore(const char* name, const char* adress) {
		SetName(name);
		SetAdress(adress);
	}

	~ComputerStore()
	{
		for (int i = 0; i < size; i++)
		{
			delete computers[i];
		}
		delete[] storeName;
		delete[] storeAdress;
		delete[] computers;
	}


	void SetName(const char* name) {
		delete[] storeName;
		int len = strlen(name) + 1;
		storeName = new char[len];
		strcpy_s(storeName, len, name);
	}

	void SetAdress(const char* adress) {
		delete[] storeAdress;
		int len = strlen(adress) + 1;
		storeAdress = new char[len];
		strcpy_s(storeAdress, len, adress);
	}



	void AddComputer(Computer& obj) {

		Computer** temp = new Computer * [size + 1];
		for (int i = 0; i < size; i++)
		{
			temp[i] = computers[i];
		}
		temp[size] = new Computer(obj);
		delete computers;
		computers = temp;
		temp = nullptr;
		size++;

	}

	void DeleteComputer(int id) {
		for (int i = 0; i < size; i++)
		{
			if (id == computers[i]->objectid)
			{
				Computer** temp = new Computer * [size - 1];
				for (int j = 0; j < i; j++)
				{
					temp[j] = computers[j];
				}
				for (int j = i; j < size - 1; j++)
				{
					temp[j + 1] = computers[i + 1];
				}
				size--;
				delete computers;
				computers = temp;
			}
		}
	}

	void PrintComputers() {
		for (int i = 0; i < size; i++)
		{
			cout << *computers[i];
		}
	}

	friend ostream& operator<<(ostream& out, const ComputerStore& obj) {
		out << obj.storeName << endl;
		out << obj.storeAdress << endl;
		for (int i = 0; i < obj.size; i++) {
			cout << *obj.computers[i];
		}
		cout << "\n\n";
		return out;
	}



};

int main() {
	Computer lenovo;
	Computer lenovo2("hp", "hp", "hp", "hp", 1, 1, 1, 1, 1);
	ComputerStore BazarStore;
	cin >> lenovo;
	BazarStore.AddComputer(lenovo);
	BazarStore.AddComputer(lenovo2);
}