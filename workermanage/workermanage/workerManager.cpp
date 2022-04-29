#include"workerManager.h"
WorkerManager::WorkerManager() {
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//����--���ļ�
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�����
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�����������
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ" <<num<< endl;
	this->m_EmpNum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
	this->init_Emp();
	//����
	/*for (int i = 0; i < this->m_EmpNum;i++) {
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
			<< " ������" << this->m_EmpArray[i]->m_Name
			<< " ���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}
//ͳ���ļ��е�����
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//����--���ļ�
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs>>id&&ifs>>name&&ifs>>did) {
		//ͳ������
		num++;
	}
	return num;
}
//��ʼ��Ա��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//����--���ļ�
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did==1) {
			worker = new Employee(id,name,did);
		}
		else if (did == 1) {
			worker = new Manager(id, name, did);
		}
		else {
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
//չʾ�˵�
void WorkerManager::Show_Menu() {
	cout << "***************************" << endl;
	cout << "***��ӭʹ��ְ������ϵͳ��***" << endl;
	cout << "***** 0���˳�����ϵͳ *****" << endl;
	cout << "***** 1������ְ����Ϣ *****" << endl;
	cout << "***** 2����ʾְ����Ϣ *****" << endl;
	cout << "***** 3��ɾ����ְְ�� *****" << endl;
	cout << "***** 4���޸�ְ����Ϣ *****" << endl;
	cout << "***** 5������ְ����Ϣ *****" << endl;
	cout << "***** 6�����ձ������ *****" << endl;
	cout << "***** 7����������ĵ� *****" << endl;
	cout << "***************************" << endl;
}
//����ְ��
void WorkerManager::Add_Emp() {
	cout << "����������ְ������" << endl;
	int addNum = 0;//�����û���������
	cin >> addNum;
	if (addNum>0) {
		//���������¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace=new Worker* [newSize];
		//��ԭ���ռ�����ݿ������¿ռ�
		if (this->m_EmpArray!=NULL) {
			for (int i = 0; i < this->m_EmpNum;i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//����������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;//����ѡ��
			cout << "�������" <<i+1<<"����ְ����ţ�"<< endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch(dSelect) {
				case 1:
					worker = new Employee(id,name,1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
			}
			//��������ְ��ָ�뱣�浽����
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;
		//���¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//����ְ������
		this->m_EmpNum = newSize;
		//���ļ��ǿ�
		this->m_FileIsEmpty = false;
		cout << "�ɹ�����" <<addNum <<"����ְ��"<<endl;
		//�ɹ����Ӻ󱣴浽�ļ���
		this->save();
	}
	else {
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");
}
//�����ļ�
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME,ios::out);//�����Ӧд�ļ�
	for (int i = 0; i < this->m_EmpNum;i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;

	}
	ofs.close();
}
//��ʾְ��
void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum;i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
//ɾ��ְ��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		//��ְ�����ɾ��
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index!=-1) {
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1;i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			//ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}

	}
	system("pause");
	system("cls");
}
//�ж�ְ���Ƿ����
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_EmpNum;i++) {
		if (this->m_EmpArray[i]->m_Id==id) {
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret!=-1) {
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽" << id<<"��ְ�����������µ�ְ����"<<endl;
			cin >> newId;
			cout << "�������µ�����" << endl;
			cin >> newName;
			cout << "�������µĸ�λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId,newName,dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//�������ݵ�����
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();

		}
		else {
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1.��ְ����Ų��ң�" << endl;
		cout << "2.��ְ���������ң�" << endl;
		int select = 0;
		cin >> select;
		if (select==1) {
			int id;
			cout << "��������ҵ�ְ�����" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret!=-1) {
				cout << "���ҳɹ�����ְ����ϢΪ��" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ�û�д���" << endl;
			}
		}
		else if (select==2) {
			string name;
			cout << "��������ҵ�ְ������" << endl;
			cin >> name;
			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;
			for (int i = 0; i < m_EmpNum;i++) {
				if (this->m_EmpArray[i]->m_Name==name) {
					cout << "���ҳɹ���ְ�����Ϊ" <<this->m_EmpArray[i]->m_Id<<"��ְ����Ϣ���£�"<<endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag==false) {
				cout << "����ʧ�ܣ�û�д���" << endl;
			}
		}
		else {
			cout << "������Ϣ��������������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ" << endl;
		cout << "1.��ְ���������" << endl;
		cout << "2.��ְ����Ž���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum;i++) {
			int minOrMax = i;
			for (int j = i+1; j < this->m_EmpNum;j++) {
				if (select == 1) {
					if (this->m_EmpArray[minOrMax]->m_Id>this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					if (this->m_EmpArray[minOrMax]->m_Id< this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			
			}
			if (i!=minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ������Ϊ" << endl;
		this->save();
		this->Show_Emp();
	}
}
//����ļ�
void WorkerManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select==1) {
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}
//�˳�ϵͳ
void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
WorkerManager::~WorkerManager() {
	if(this->m_EmpArray!=NULL){
		for (int i = 0; i < this->m_EmpNum;i++) {
			if (this->m_EmpArray[i]!=NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}