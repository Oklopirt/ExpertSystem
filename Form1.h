#include "node.h"
#pragma once


namespace WinFormsProba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
			

	public ref class Form1 : public System::Windows::Forms::Form
	{
		node^ nodes;
		int INIT;
		String^ pathToFile;
		int answer;
		bool deleteRows;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьКакToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  загрузитьToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::CheckBox^  checkBox1;

	private: System::Windows::Forms::Button^  button4;


	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TabPage^  tabPage1;

	private: System::Windows::Forms::Button^  deleteColumn;
	private: System::Windows::Forms::Button^  deleteNode;
	private: System::Windows::Forms::Button^  newNode;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  initSystem;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  numOfVariable;
	private: System::Windows::Forms::TextBox^  numOfOutcomes;
	private: System::Windows::Forms::TextBox^  numOfVar;
	private: System::Windows::Forms::TextBox^  countOfNode;
	private: System::Windows::Forms::TextBox^  numOfNode;
	private: System::Windows::Forms::Button^  nextNode;
	private: System::Windows::Forms::Button^  previousNode;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::DataGridView^  tableOfOutcomes;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridView^  tableOfVariable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::Button^  button1;

			 array<int> ^arrayForInit;
	public:
		void clearWorkPlace(){
			 tableOfOutcomes->Rows->Clear();
			 tableOfVariable->Rows->Clear();
			 int countOfDeleteColumns = tableOfVariable->ColumnCount;
			 for(int i = countOfDeleteColumns - 1; i != 0; i--){
				 tableOfVariable->Columns->RemoveAt(i);
			 }							
			 //numOfNode->Text = " ";
			 numOfOutcomes->Text = " ";
			 numOfVar->Text = " ";
			 numOfVariable->Text = " ";
		}
		//-----------------------
		void initTheNode(bool swit){
			numOfVar->Text = Convert::ToString(tableOfVariable->RowCount - 2);
			numOfVariable->Text = Convert::ToString(tableOfVariable->ColumnCount - 1);
			numOfOutcomes->Text = Convert::ToString(tableOfOutcomes->RowCount - 1);

			if (arrayForInit[0] < Convert::ToInt32(numOfVar->Text)){
				arrayForInit[0] = Convert::ToInt32(numOfVar->Text);
			}
			if (arrayForInit[1] < Convert::ToInt32(numOfOutcomes->Text)){
				arrayForInit[1] = Convert::ToInt32(numOfOutcomes->Text);
			}
			if (arrayForInit[2] < Convert::ToInt32(numOfVariable->Text)){
				arrayForInit[2] = Convert::ToInt32(numOfVariable->Text);				
			}
			if (INIT == 1){
				//Для добавления одного примера в режиме тренировки
				if (swit == 1){
					nodes = gcnew node(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2] + 1);
 					for(int i = 1; i <= Convert::ToInt32(countOfNode->Text); i++){
						nodes->loadFromFile(i, 0, "~temp.dcl");
					}
				}
				else{
					nodes = gcnew node(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2]);
 					for(int i = 1; i <= Convert::ToInt32(countOfNode->Text); i++){
						nodes->loadFromFile(i, 0, "~temp.dcl");
					}
				}

			}
			if (INIT == 0){
				if (swit == 1){
					nodes = gcnew node(Convert::ToInt32(countOfNode->Text), 
									Convert::ToInt32(numOfVar->Text), 
									Convert::ToInt32(numOfOutcomes->Text), 
									Convert::ToInt32(numOfVariable->Text) + 1);
				}
				else{
					nodes = gcnew node(Convert::ToInt32(countOfNode->Text), 
									Convert::ToInt32(numOfVar->Text), 
									Convert::ToInt32(numOfOutcomes->Text), 
									Convert::ToInt32(numOfVariable->Text));
									INIT = 3;
				}
			}
			if (INIT == 3){
				nodes = gcnew node(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2]);
 				for(int i = 1; i < Convert::ToInt32(countOfNode->Text); i++){
					nodes->loadFromFile(i, 0, "~temp.dcl");
				}
			}

			nodes->iCountOfNodes = Convert::ToInt32(countOfNode->Text);
			nodes->iNumOfVar[0, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(numOfVar->Text);
			nodes->iNumOfExamples[0, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(numOfVariable->Text);
			if (swit == 1){
				nodes->iNumOfOutcomes[0, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(numOfOutcomes->Text) + 1;
			}
			else{
				nodes->iNumOfOutcomes[0, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(numOfOutcomes->Text);
			}
		}
		//Загрузка узла из файла
		void loadInitFromFile(String^ pathToFile){
			StreamReader fromFile(pathToFile);
			String^ temp;
			int iCountOfNodes, iNumOfVar, iNumOfExamples, iNumOfOutcomes;

			while (fromFile.Peek() >= 0){
				temp = fromFile.ReadLine();
				if (temp == "THE END") break;		
			}
			for (int i = 0; i < 4 ;i++){
				temp = fromFile.ReadLine();
				if (i == 0) iCountOfNodes = Convert::ToInt32(temp) + 1;
				if (i == 1) iNumOfVar = Convert::ToInt32(temp);
				if (i == 2) iNumOfExamples = Convert::ToInt32(temp);
				if (i == 3) iNumOfOutcomes = Convert::ToInt32(temp);
			}
			nodes = gcnew node(iCountOfNodes - 1, iNumOfVar, iNumOfOutcomes, iNumOfExamples);
 			for(int i = 1; i < iCountOfNodes; i++){
				nodes->loadFromFile(i, 0, pathToFile);
			}
			INIT = 1;
			countOfNode->Text = Convert::ToString(nodes->iCountOfNodes);
			arrayForInit[0] = iNumOfVar;
			arrayForInit[1] = iNumOfOutcomes;
			arrayForInit[2] = iNumOfExamples;
			

		}
		//Перегрузка функции для удаления узла
		void loadInitFromFile(int numOfDeleteNode, String^ pathToFile){
			StreamReader fromFile(pathToFile);
			String^ temp;
			int iCountOfNodes, iNumOfVar, iNumOfExamples, iNumOfOutcomes;

			while (fromFile.Peek() >= 0){
				temp = fromFile.ReadLine();
				if (temp == "THE END") break;		
			}
			for (int i = 0; i < 4 ;i++){
				temp = fromFile.ReadLine();
				if (i == 0) iCountOfNodes = Convert::ToInt32(temp);
				if (i == 1) iNumOfVar = Convert::ToInt32(temp);
				if (i == 2) iNumOfExamples = Convert::ToInt32(temp);
				if (i == 3) iNumOfOutcomes = Convert::ToInt32(temp);
			}
			nodes = gcnew node(iCountOfNodes - 1, iNumOfVar, iNumOfOutcomes, iNumOfExamples);
			INIT = 1;
			int j = 1;
 			for(int i = 1; i < iCountOfNodes; i++){
				if (i >= numOfDeleteNode){
					nodes->loadFromFile(i, 1, pathToFile);
					j++;
				}
				else nodes->loadFromFile(i, 0, pathToFile);
			}
			countOfNode->Text = Convert::ToString(nodes->iCountOfNodes);
		}	   								

		//Запись в форму данных по выбранному узлу
		void loadNodeToForm(int numOfNode){
			tableOfVariable->ColumnCount = nodes->iNumOfExamples[0, numOfNode - 1] + 1;
			tableOfVariable->RowCount = nodes->iNumOfVar[0, numOfNode - 1] + 2;
			tableOfOutcomes->RowCount = nodes->iNumOfOutcomes[0, numOfNode - 1] + 1;
			for (int i = 1; i < tableOfVariable->ColumnCount; i++){
				tableOfVariable->Columns[i]->Width = 25;
			}
			
			for (int i = 0; i < nodes->iNumOfVar[0, numOfNode - 1]; i++){				
				tableOfVariable->Rows[i]->Cells[0]->Value = nodes->sVar[i, numOfNode - 1];
			}
			//Заполнение массива с примерами. 
			for (int i = 0; i <= nodes->iNumOfVar[0, numOfNode - 1]; i++){
				for (int j = 0; j < nodes->iNumOfExamples[0, numOfNode - 1]; j++){
					tableOfVariable->Rows[i]->Cells[j + 1]->Value = nodes->bExamples[i, j, numOfNode - 1];
				}
			} 
			//Заполнение возможных исходов
			for (int i = 0; i < nodes->iNumOfOutcomes[0, numOfNode - 1]; i++){				
				tableOfOutcomes->Rows[i]->Cells[0]->Value = nodes->sOutcomes[i, numOfNode - 1];
			}
			numOfVar->Text = Convert::ToString(tableOfVariable->RowCount - 2);
			numOfVariable->Text = Convert::ToString(tableOfVariable->ColumnCount - 1);
			numOfOutcomes->Text = Convert::ToString(tableOfOutcomes->RowCount - 1);

		}

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	protected: 
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьКакToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->deleteColumn = (gcnew System::Windows::Forms::Button());
			this->deleteNode = (gcnew System::Windows::Forms::Button());
			this->newNode = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->initSystem = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->numOfVariable = (gcnew System::Windows::Forms::TextBox());
			this->numOfOutcomes = (gcnew System::Windows::Forms::TextBox());
			this->numOfVar = (gcnew System::Windows::Forms::TextBox());
			this->countOfNode = (gcnew System::Windows::Forms::TextBox());
			this->numOfNode = (gcnew System::Windows::Forms::TextBox());
			this->nextNode = (gcnew System::Windows::Forms::Button());
			this->previousNode = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableOfOutcomes = (gcnew System::Windows::Forms::DataGridView());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tableOfVariable = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->menuStrip1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tableOfOutcomes))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tableOfVariable))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripMenuItem1});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(690, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->сохранитьToolStripMenuItem, 
				this->сохранитьКакToolStripMenuItem, this->загрузитьToolStripMenuItem});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(43, 20);
			this->toolStripMenuItem1->Text = L"Узел";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem1_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьToolStripMenuItem_Click);
			// 
			// сохранитьКакToolStripMenuItem
			// 
			this->сохранитьКакToolStripMenuItem->Name = L"сохранитьКакToolStripMenuItem";
			this->сохранитьКакToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->сохранитьКакToolStripMenuItem->Text = L"Сохранить как...";
			this->сохранитьКакToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьКакToolStripMenuItem_Click);
			// 
			// загрузитьToolStripMenuItem
			// 
			this->загрузитьToolStripMenuItem->Name = L"загрузитьToolStripMenuItem";
			this->загрузитьToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->загрузитьToolStripMenuItem->Text = L"Загрузить...";
			this->загрузитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::загрузитьToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->checkBox1);
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->listBox1);
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(684, 377);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Работа с системой";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(503, 19);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(174, 17);
			this->checkBox1->TabIndex = 6;
			this->checkBox1->Text = L"Включить режим тренировки";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(89, 346);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(116, 23);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Очистить экран";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click_1);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(6, 6);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(274, 329);
			this->listBox1->TabIndex = 1;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(295, 6);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(188, 40);
			this->button3->TabIndex = 0;
			this->button3->Text = L"Нормальное функционирование\\Тренировка";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->deleteColumn);
			this->tabPage1->Controls->Add(this->deleteNode);
			this->tabPage1->Controls->Add(this->newNode);
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->initSystem);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->numOfVariable);
			this->tabPage1->Controls->Add(this->numOfOutcomes);
			this->tabPage1->Controls->Add(this->numOfVar);
			this->tabPage1->Controls->Add(this->countOfNode);
			this->tabPage1->Controls->Add(this->numOfNode);
			this->tabPage1->Controls->Add(this->nextNode);
			this->tabPage1->Controls->Add(this->previousNode);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->tableOfOutcomes);
			this->tabPage1->Controls->Add(this->tableOfVariable);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(684, 377);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Структура системы";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &Form1::tabPage1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(429, 39);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(114, 23);
			this->button1->TabIndex = 21;
			this->button1->Text = L"Удалить строку";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click_4);
			// 
			// deleteColumn
			// 
			this->deleteColumn->Location = System::Drawing::Point(562, 39);
			this->deleteColumn->Name = L"deleteColumn";
			this->deleteColumn->Size = System::Drawing::Size(111, 22);
			this->deleteColumn->TabIndex = 20;
			this->deleteColumn->Text = L"Удалить столбец";
			this->deleteColumn->UseVisualStyleBackColor = true;
			this->deleteColumn->Click += gcnew System::EventHandler(this, &Form1::deleteColumn_Click);
			// 
			// deleteNode
			// 
			this->deleteNode->Location = System::Drawing::Point(224, 39);
			this->deleteNode->Name = L"deleteNode";
			this->deleteNode->Size = System::Drawing::Size(97, 23);
			this->deleteNode->TabIndex = 19;
			this->deleteNode->Text = L"Удалить узел";
			this->deleteNode->UseVisualStyleBackColor = true;
			this->deleteNode->Click += gcnew System::EventHandler(this, &Form1::deleteNode_Click);
			// 
			// newNode
			// 
			this->newNode->Location = System::Drawing::Point(224, 10);
			this->newNode->Name = L"newNode";
			this->newNode->Size = System::Drawing::Size(97, 23);
			this->newNode->TabIndex = 18;
			this->newNode->Text = L"Добавить узел";
			this->newNode->UseVisualStyleBackColor = true;
			this->newNode->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(562, 10);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(111, 23);
			this->button2->TabIndex = 17;
			this->button2->Text = L"Добавить столбец";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click_1);
			// 
			// initSystem
			// 
			this->initSystem->Location = System::Drawing::Point(11, 56);
			this->initSystem->Name = L"initSystem";
			this->initSystem->Size = System::Drawing::Size(164, 23);
			this->initSystem->TabIndex = 15;
			this->initSystem->Text = L"Инициализировать систему";
			this->initSystem->UseVisualStyleBackColor = true;
			this->initSystem->Click += gcnew System::EventHandler(this, &Form1::initSystem_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(8, 96);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(170, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Характеристики текущего узла:";
			// 
			// numOfVariable
			// 
			this->numOfVariable->Location = System::Drawing::Point(175, 169);
			this->numOfVariable->Name = L"numOfVariable";
			this->numOfVariable->ReadOnly = true;
			this->numOfVariable->Size = System::Drawing::Size(24, 20);
			this->numOfVariable->TabIndex = 13;
			// 
			// numOfOutcomes
			// 
			this->numOfOutcomes->Location = System::Drawing::Point(175, 144);
			this->numOfOutcomes->Name = L"numOfOutcomes";
			this->numOfOutcomes->ReadOnly = true;
			this->numOfOutcomes->Size = System::Drawing::Size(24, 20);
			this->numOfOutcomes->TabIndex = 12;
			// 
			// numOfVar
			// 
			this->numOfVar->Location = System::Drawing::Point(175, 121);
			this->numOfVar->Name = L"numOfVar";
			this->numOfVar->ReadOnly = true;
			this->numOfVar->Size = System::Drawing::Size(24, 20);
			this->numOfVar->TabIndex = 11;
			// 
			// countOfNode
			// 
			this->countOfNode->Location = System::Drawing::Point(175, 10);
			this->countOfNode->Name = L"countOfNode";
			this->countOfNode->ReadOnly = true;
			this->countOfNode->Size = System::Drawing::Size(24, 20);
			this->countOfNode->TabIndex = 10;
			this->countOfNode->Text = L"1";
			// 
			// numOfNode
			// 
			this->numOfNode->Location = System::Drawing::Point(429, 12);
			this->numOfNode->Name = L"numOfNode";
			this->numOfNode->ReadOnly = true;
			this->numOfNode->Size = System::Drawing::Size(24, 20);
			this->numOfNode->TabIndex = 9;
			this->numOfNode->Text = L"1";
			// 
			// nextNode
			// 
			this->nextNode->Location = System::Drawing::Point(511, 10);
			this->nextNode->Name = L"nextNode";
			this->nextNode->Size = System::Drawing::Size(32, 23);
			this->nextNode->TabIndex = 8;
			this->nextNode->Text = L">>";
			this->nextNode->UseVisualStyleBackColor = true;
			this->nextNode->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// previousNode
			// 
			this->previousNode->Location = System::Drawing::Point(473, 10);
			this->previousNode->Name = L"previousNode";
			this->previousNode->Size = System::Drawing::Size(32, 23);
			this->previousNode->TabIndex = 7;
			this->previousNode->Text = L"<<";
			this->previousNode->UseVisualStyleBackColor = true;
			this->previousNode->Click += gcnew System::EventHandler(this, &Form1::previousNode_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(373, 15);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(50, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"№ Узла:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(8, 169);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(95, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Число примеров:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 147);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(148, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Число возможных исходов:";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 124);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(108, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Число переменных:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Число узлов:";
			// 
			// tableOfOutcomes
			// 
			this->tableOfOutcomes->BackgroundColor = System::Drawing::SystemColors::ActiveBorder;
			this->tableOfOutcomes->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tableOfOutcomes->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) {this->Column2});
			this->tableOfOutcomes->Location = System::Drawing::Point(3, 203);
			this->tableOfOutcomes->Name = L"tableOfOutcomes";
			this->tableOfOutcomes->Size = System::Drawing::Size(215, 174);
			this->tableOfOutcomes->TabIndex = 1;
			this->tableOfOutcomes->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::tableOfOutcomes_CellClick);
			this->tableOfOutcomes->Leave += gcnew System::EventHandler(this, &Form1::tableOfOutcomes_Leave);
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Возможные исходы";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 170;
			// 
			// tableOfVariable
			// 
			this->tableOfVariable->BackgroundColor = System::Drawing::SystemColors::ActiveBorder;
			this->tableOfVariable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tableOfVariable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) {this->Column1});
			this->tableOfVariable->Location = System::Drawing::Point(224, 79);
			this->tableOfVariable->Name = L"tableOfVariable";
			this->tableOfVariable->Size = System::Drawing::Size(460, 298);
			this->tableOfVariable->TabIndex = 0;
			this->tableOfVariable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::tableOfVariable_CellClick_1);
			this->tableOfVariable->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick_1);
			this->tableOfVariable->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::tableOfVariable_CellValueChanged);
			this->tableOfVariable->CurrentCellChanged += gcnew System::EventHandler(this, &Form1::tableOfVariable_CurrentCellChanged);
			this->tableOfVariable->CurrentCellDirtyStateChanged += gcnew System::EventHandler(this, &Form1::tableOfVariable_CurrentCellDirtyStateChanged);
			this->tableOfVariable->DefaultValuesNeeded += gcnew System::Windows::Forms::DataGridViewRowEventHandler(this, &Form1::tableOfVariable_DefaultValuesNeeded);
			this->tableOfVariable->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::tableOfVariable_KeyPress);
			this->tableOfVariable->Leave += gcnew System::EventHandler(this, &Form1::tableOfVariable_Leave);
			// 
			// Column1
			// 
			this->Column1->Frozen = true;
			this->Column1->HeaderText = L"Переменные";
			this->Column1->Name = L"Column1";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(0, 27);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(692, 403);
			this->tabControl1->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(690, 430);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L" ";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tableOfOutcomes))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tableOfVariable))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 INIT = 0;
				 arrayForInit = gcnew array<int>(3);
				 arrayForInit[0] = 0;
				 arrayForInit[1] = 0;
				 arrayForInit[2] = 0;
				 answer = 3;
			 }
	private: System::Void button1_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Form1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 }

	private: System::Void label1_MouseHover(System::Object^  sender, System::EventArgs^  e) {

			 }
private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void dataGridView1_CellContentClick_1(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (Convert::ToInt32(numOfNode->Text) + 1 <= Convert::ToInt32(countOfNode->Text)){
				 numOfNode->Text = Convert::ToString(Convert::ToInt32(numOfNode->Text) + 1);
				 clearWorkPlace();
				 loadNodeToForm(Convert::ToInt32(numOfNode->Text));
			 }
		 }
private: System::Void initSystem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Инициализация массива
			 initTheNode(0);
			 //Заполнение узлов
			 for (int i = 0; i < Convert::ToInt32(numOfVar->Text); i++){				
				 nodes->sVar[i, Convert::ToInt32(numOfNode->Text) - 1] = tableOfVariable->Rows[i]->Cells[0]->Value->ToString();
			 }
			 //Заполнение массива с примерами. 
			 for (int i = 0; i <= Convert::ToInt32(numOfVar->Text); i++){
				 for (int j = 0; j < Convert::ToInt32(numOfVariable->Text); j++){
					 nodes->bExamples[i, j, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(tableOfVariable->Rows[i]->Cells[j + 1]->Value->ToString());
				 }
			 }
			 //Заполнение возможных исходов
			 for (int i = 0; i < Convert::ToInt32(numOfOutcomes->Text); i++){				
				 nodes->sOutcomes[i, Convert::ToInt32(numOfNode->Text) - 1] = tableOfOutcomes->Rows[i]->Cells[0]->Value->ToString();
			 }
			 //Заполнение исходов в нижней строке примеров
			 nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], "~temp.dcl");
		 }
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 //добавление нового столбца
			 int i = tableOfVariable->ColumnCount;
			 String ^columnName = "Column" + i,
					^columnText = " ";
			 tableOfVariable->Columns->Add(columnName, columnText);
			 tableOfVariable->Columns[i]->Width = 25;
			 for (int j = 0; j < tableOfVariable->Rows->Count - 1; j++){
				 tableOfVariable->Rows[j]->Cells[i]->Value = 0;
			 }
		 }
private: System::Void tableOfVariable_DefaultValuesNeeded(System::Object^  sender, System::Windows::Forms::DataGridViewRowEventArgs^  e) {
			 //Значение по умолчанию
			 e->Row->Cells["Column1"]->Value = " ";
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //+1 к количеству узлов
			 clearWorkPlace();
			 countOfNode->Text = Convert::ToString(Convert::ToInt32(countOfNode->Text) + 1);
			 numOfNode->Text = Convert::ToString(Convert::ToInt32(countOfNode->Text));
			 INIT = 3;
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void deleteColumn_Click(System::Object^  sender, System::EventArgs^  e) {
			 tableOfVariable->Columns->RemoveAt(tableOfVariable->CurrentCell->ColumnIndex);
		 }
private: System::Void previousNode_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i = Convert::ToInt32(numOfNode->Text) - 1;
			 if (i > 0){ 
				 numOfNode->Text = Convert::ToString(Convert::ToInt32(numOfNode->Text) - 1);
				 clearWorkPlace();
				 loadNodeToForm(Convert::ToInt32(numOfNode->Text));
			 }
		 }
private: System::Void deleteNode_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Удалить узел
			 loadInitFromFile(Convert::ToInt32(numOfNode->Text), pathToFile);
			 loadNodeToForm(1);
			 numOfNode->Text = Convert::ToString(1);
			 countOfNode->Text = Convert::ToString(Convert::ToInt32(countOfNode->Text) - 1);
		 }
private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		 }
private: System::Void загрузитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			String^ myPath;
			myPath = System::Reflection::Assembly::GetExecutingAssembly()->Location;
			openFileDialog1->InitialDirectory = myPath;
			openFileDialog1->Filter = "Expert system files (*.exprt)|*.exprt";
			openFileDialog1->FilterIndex = 1;
			openFileDialog1->RestoreDirectory = true;

			if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
				pathToFile = openFileDialog1->FileName;
				loadInitFromFile(pathToFile);
				loadNodeToForm(Convert::ToInt32(numOfNode->Text));
				nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], "~temp.dcl");
			}
		 }
private: System::Void сохранитьКакToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
			  saveFileDialog1->Filter = "Expert system files (*.exprt)|*.exprt";
			  saveFileDialog1->FilterIndex = 1;
			  saveFileDialog1->RestoreDirectory = true;
			  if ( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
				  pathToFile = saveFileDialog1->FileName;
				  nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], pathToFile);
			  }
		 }
private: System::Void сохранитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], pathToFile);
		 }
private: System::Void button1_Click_3(System::Object^  sender, System::EventArgs^  e) {
			 MessageBoxButtons::YesNo;
			 MessageBox::Show("sdfsdfsdfs");
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 answer = 1;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			//Нормальное функционирование, тренировка
			nodes->trainingSystem1580();
			for (int n = 0; n < nodes->iCountOfNodes; n++){
				for (int i = 0; i < nodes->iNumOfVar[0, n]; i++){
					nodes->bVarFlag[i, n] = 1;
					nodes->iValue[i, n] = 0;
					nodes->iMaxi[i, n] = 1;
				}
				for (int j = 0; j < nodes->iNumOfOutcomes[0, n]; j++){
					nodes->bOutflag[j, n] = 1;
				}
				

			}
			//Основной цикл
			for (int node = 0; node < nodes->iCountOfNodes; node++){
				nodes->var = nodes->iNumOfVar[0, node];
				nodes->outcomes = nodes->iNumOfOutcomes[0, node];
				do{
					nodes->best = 1;
					nodes->bestposs = 1;
					nodes->decision = 0;
					nodes->maxposs = 0;

					nodes->calculationDecisionAndBest670(node);
					nodes->calculationPossibleAndBestposs750(node);
					if (nodes->bestposs == nodes->best) break;
					nodes->doTrainingMode860(node);
					if (nodes->rv == 0) break;

					//2560
					listBox1->Items->Add("Переменная '" + nodes->sVar[nodes->bestvar, node] + "' есть?");
					if (MessageBox::Show("Переменная '" + nodes->sVar[nodes->bestvar, node] + "' есть?", "  ",
						MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){
						listBox1->Items->Add("Да");
						nodes->iValue[nodes->bestvar, node] = 1;
						nodes->bVarFlag[nodes->bestvar, node] = 0;
					}
					else{
						listBox1->Items->Add("Нет");
						nodes->iValue[nodes->bestvar, node] = 0;
						nodes->bVarFlag[nodes->bestvar, node] = 0;
					}
					nodes->compareTheDifferent1080(node);

				}while (nodes->bestposs != nodes->best);
				if (!nodes->training){
					listBox1->Items->Add("В качестве возможного исхода предлагается - " + nodes->sOutcomes[nodes->best, node]);
					MessageBox::Show("В качестве возможного исхода предлагается - " + nodes->sOutcomes[nodes->best, node] + " ");
					nodes->correct = nodes->best;
					nodes->compareTheBestOutComes1270(node);
				}
				else{
					listBox1->Items->Add("Возможный результат - " + nodes->sOutcomes[nodes->best, node]);
					if (MessageBox::Show("Возможный результат - " + nodes->sOutcomes[nodes->best, node] + " ", "  ",
						MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){

						listBox1->Items->Add("Да");
						nodes->correct = nodes->best;
					}
					else{
						//2610
						for (int i = 0; i < nodes->iNumOfOutcomes[0, node]; i++){
						listBox1->Items->Add("Допустимый исход - " + nodes->sOutcomes[i, node]);
							if (MessageBox::Show("Допустимый исход - " + nodes->sOutcomes[i, node] + " ", "  ",
								MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){
								nodes->correct = i;
								listBox1->Items->Add("Да");
								break;
							}
							else{
								listBox1->Items->Add("Нет");
							}
						}
					}

					//Сохранение
					listBox1->Items->Add("Вы хотите сохранить этот пример?");
					if (MessageBox::Show("Вы хотите сохранить этот пример?", "  ",
						MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){
						listBox1->Items->Add("Да");
						numOfNode->Text = Convert::ToString(node + 1);
						clearWorkPlace();
						loadNodeToForm(Convert::ToInt32(numOfNode->Text));
						//добавление нового столбца
						int i = tableOfVariable->ColumnCount;
						String ^columnName = "Column" + i,
							^columnText = " ";
						tableOfVariable->Columns->Add(columnName, columnText);
						tableOfVariable->Columns[i]->Width = 25;
						for (int j = 0; j < tableOfVariable->Rows->Count - 1; j++){
							tableOfVariable->Rows[j]->Cells[i]->Value = 0;
						}
						
						for (int i = 0; i < nodes->iNumOfVar[0, node]; i++){
							tableOfVariable->Rows[i]->Cells[nodes->iNumOfExamples[0, node] + 1]->Value = nodes->iValue[i, node];
						}
						tableOfVariable->Rows[nodes->iNumOfVar[0, node]]->Cells[nodes->iNumOfExamples[0, node] + 1]->Value = nodes->correct + 1;
					}
					else{
						listBox1->Items->Add("Нет");   
					}
					nodes->correctRulesValue2680(node);
					nodes->compareTheBestOutComes1270(node);
				}
			}
			//ВОзожмно не надо
			nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], "~temp.dcl");
			initTheNode(0);
			//Заполнение узлов
			for (int i = 0; i < Convert::ToInt32(numOfVar->Text); i++){				
				nodes->sVar[i, Convert::ToInt32(numOfNode->Text) - 1] = tableOfVariable->Rows[i]->Cells[0]->Value->ToString();
			}
			//Заполнение массива с примерами. 
			for (int i = 0; i <= Convert::ToInt32(numOfVar->Text); i++){
				for (int j = 0; j < Convert::ToInt32(numOfVariable->Text); j++){
					nodes->bExamples[i, j, Convert::ToInt32(numOfNode->Text) - 1] = Convert::ToInt32(tableOfVariable->Rows[i]->Cells[j + 1]->Value->ToString());
				}
			}
			//Заполнение возможных исходов
			for (int i = 0; i < Convert::ToInt32(numOfOutcomes->Text); i++){				
				nodes->sOutcomes[i, Convert::ToInt32(numOfNode->Text) - 1] = tableOfOutcomes->Rows[i]->Cells[0]->Value->ToString();
			}
			//Заполнение исходов в нижней строке примеров
			nodes->saveToFile(Convert::ToInt32(countOfNode->Text), arrayForInit[0], arrayForInit[1], arrayForInit[2], "~temp.dcl");
		 }
private: System::Void button4_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 listBox1->Items->Clear();
		 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void noButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 answer = 0;
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkBox1->Checked == true){
				 nodes->training = 1;
			 }
			 else{
				 nodes->training = 0;
			 }
		 }
private: System::Void button1_Click_4(System::Object^  sender, System::EventArgs^  e) {
			 if (deleteRows == 1){
				tableOfVariable->Rows->RemoveAt(tableOfVariable->CurrentCell->RowIndex);
			 }
			 if (deleteRows == 0){
				tableOfOutcomes->Rows->RemoveAt(tableOfOutcomes->CurrentCell->RowIndex);
			 }
		 }
private: System::Void tableOfVariable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void tableOfOutcomes_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 //Для удаления строки
			 deleteRows = 0;
		 }
private: System::Void tableOfVariable_CellClick_1(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 //ДЛя удаления строки
			 deleteRows = 1;
		 }
};
}
				
