#include "stdafx.h"
#include "node.h"
#include "math.h"

using namespace System::IO;


node::node(int iNumOfNodes, int iNumOfV, int iNumOfOutcom, int iNumOfExamp)
{
	iCountOfNodes = iNumOfNodes;
	iNumOfVar = gcnew array<int, 2>(1, iNumOfNodes);
	iNumOfExamples = gcnew array<int, 2>(1, iNumOfNodes);
	iNumOfOutcomes = gcnew array<int, 2>(1, iNumOfNodes);
	
	sVar = gcnew array<String^, 2>(iNumOfV, iNumOfNodes);
	iValue = gcnew array<int, 2>(iNumOfV, iNumOfNodes);
	bVarFlag = gcnew array<bool, 2>(iNumOfV, iNumOfNodes);
	iRuleValues = gcnew array<int, 2>(iNumOfV, iNumOfNodes);
	
	bExamples = gcnew array<int, 3>(iNumOfV + 1, iNumOfExamp, iNumOfNodes);
	sOutcomes = gcnew array<String^, 2>(iNumOfOutcom, iNumOfNodes);
	iRules = gcnew array<int, 3>(iNumOfV, iNumOfOutcom, iNumOfNodes);
	bOutflag = gcnew array<bool, 2>(iNumOfOutcom, iNumOfNodes);
	iDecision = gcnew array<int>(iNumOfOutcom);
	iPossible = gcnew array<int>(iNumOfOutcom);
	iMini = gcnew array<int, 2>(iNumOfV, iCountOfNodes);
	iMaxi = gcnew array<int, 2>(iNumOfV, iCountOfNodes);
}

// Перезаписывает файл экспертной системы
void node::saveToFile(int numOfNode, int iNumOfV, int iNumOfOutcom, int iNumOfExamp, String^ pathToFile){
	StreamWriter outFile(pathToFile);
	for (int n = 0; n < numOfNode; n++){
		//Подпись узла в файле
		String^ nodeSign = "Node" + (n + 1); 

		outFile.WriteLine(nodeSign);
		outFile.WriteLine(this->iCountOfNodes); 
		outFile.WriteLine(this->iNumOfVar[0, n]); 
		outFile.WriteLine(this->iNumOfExamples[0, n]);
		outFile.WriteLine(this->iNumOfOutcomes[0, n]);
	
		//Запись в файл переменных
		for (int i = 0; i < this->iNumOfVar[0, n]; i++){				
			outFile.WriteLine(this->sVar[i, n]);
		}
			 
		//Запись в файл примеров
		for (int i = 0; i <= this->iNumOfVar[0, n]; i++){
			for (int j = 0; j < this->iNumOfExamples[0, n]; j++){
				outFile.Write(Convert::ToString(Convert::ToInt32(this->bExamples[i, j, n])), " ");
			}
			outFile.WriteLine();
		}
		//Запись в файл исходов
		for (int i = 0; i < this->iNumOfOutcomes[0, n]; i++){				
			outFile.WriteLine(this->sOutcomes[i, n]);
		}
		//Запись в файл rules
		for (int i = 0; i < this->iNumOfVar[0, n]; i++){
			for (int j = 0; j < this->iNumOfOutcomes[0, n]; j++){
				outFile.Write(Convert::ToString(Convert::ToInt32(this->iRules[i, j, n])), " ");
			}
			outFile.WriteLine();
		}

		outFile.WriteLine("-----");
	}
	outFile.WriteLine("THE END");
	outFile.WriteLine(numOfNode);
	outFile.WriteLine(iNumOfV);
	outFile.WriteLine(iNumOfExamp);
	outFile.WriteLine(iNumOfOutcom);
	
	outFile.Close();
}

//В качестве аргумента передается номер узла - 1
void node::loadFromFile(int iNumOfNode, bool deleteIndex, String^ pathToFile){
	StreamReader fromFile(pathToFile);
	String^ temp;
	String^ nameOfNode;
	//int iCountOfNodes, iNumOfVar, iNumOfExamples, iNumOfOutcomes;
	if (deleteIndex == 0)
		nameOfNode = "Node" + iNumOfNode;
	else
		nameOfNode = "Node" + (iNumOfNode + 1);
	 
	while (fromFile.Peek() >= 0){
		temp = fromFile.ReadLine();
		if (temp == nameOfNode) break;		
	}
	for (int i = 0; ;i++){
		temp = fromFile.ReadLine();
		if (temp == "-----") break;
		if (i == 0) this->iCountOfNodes = Convert::ToInt32(temp);
		if (i == 1) this->iNumOfVar[0, iNumOfNode - 1] = Convert::ToInt32(temp);
		if (i == 2) this->iNumOfExamples[0, iNumOfNode - 1] = Convert::ToInt32(temp);
		if (i == 3) this->iNumOfOutcomes[0, iNumOfNode - 1] = Convert::ToInt32(temp);
		
		if (i > 3){ 
			if(i < (4 + this->iNumOfVar[0, iNumOfNode - 1])) 
				this->sVar[i - 4, iNumOfNode - 1] = temp;
		}
		if (i > 3 + this->iNumOfVar[0, iNumOfNode - 1]){ 
			if (i < 5 + this->iNumOfVar[0, iNumOfNode - 1] * 2){
				for (int j = 0; j < this->iNumOfExamples[0, iNumOfNode - 1]; j++){
					this->bExamples[i - (4 + this -> iNumOfVar[0, iNumOfNode - 1]), j, iNumOfNode - 1] = Convert::ToInt32(temp->Substring(j, 1));
				}
			} 
		}
		if (i > 4 + this->iNumOfVar[0, iNumOfNode - 1] * 2){
			if (i < 5 + this->iNumOfVar[0, iNumOfNode - 1] * 2 + iNumOfOutcomes[0, iNumOfNode - 1]){ 
				this->sOutcomes[i - (5 + this->iNumOfVar[0, iNumOfNode - 1] * 2), iNumOfNode - 1] = temp;
			}
		}
		if (i > 4 + this->iNumOfVar[0, iNumOfNode - 1] * 2 + iNumOfOutcomes[0, iNumOfNode - 1]){
			int j1 = 0;
			for (int j = 0; j1 < this->iNumOfOutcomes[0, iNumOfNode - 1]; j++){
				int t = 0;
				if (temp->Substring(j, 1) == "-"){
					t = (-1) * Convert::ToInt32(temp->Substring(j + 1, 1));
					j++;
				}
				else{
					t = Convert::ToInt32(temp->Substring(j, 1));
				}
				this->iRules[i - (5 + this->iNumOfVar[0, iNumOfNode - 1] * 2 + iNumOfOutcomes[0, iNumOfNode - 1]), j1++, iNumOfNode - 1] = t;
			} 
		}
	}
	fromFile.Close();
}

void node :: saveInitData(int iNumOfNodes, int iNumOfV, int iNumOfOutcom, int iNumOfExamp, String^ pathToFile){
	StreamWriter outFile(pathToFile);
	StreamReader fromFile(pathToFile);
	while (fromFile.Peek() >= 0){
		fromFile.ReadLine();
	}
	outFile.WriteLine("THE END");
	outFile.WriteLine(iNumOfNodes);
	outFile.WriteLine(iNumOfV);
	outFile.WriteLine(iNumOfExamp);
	outFile.WriteLine(iNumOfOutcom);

	outFile.Close();
	fromFile.Close();

}

//Тренировка системы или нормальное функционирование
void node::doNormalOrTrainingMode(bool mode){
	for (int n = 0; n < iCountOfNodes; n++){
		for (int i = 0; i < iNumOfVar[0, n]; i++){
			bVarFlag[i, n] = 1;
			iValue[i, n] = 0;
		}
		for (int j = 0; j < iNumOfOutcomes[0, n]; j++){
			bOutflag[j, n] = 1;
		}

	}
	//Основной цикл
	for (int node = 0; node < iCountOfNodes; node++){
		var = iNumOfVar[0, node];
		outcomes = iNumOfOutcomes[0, node];
		best = 1;
		bestposs = 1;
		decision = 0;
		maxposs = 0;
	}
}

void node :: calculationDecisionAndBest670(int node){
	decision = - 10000;
	for (int j = 0; j < iNumOfOutcomes[0, node]; j++){
		//iDecision[j] = 0;
		if (iDecision[j] >= decision){
			best = j;
			decision = iDecision[j];
		}
	}
}

void node :: calculationPossibleAndBestposs750(int node){
	for (int j = 0; j < iNumOfOutcomes[0, node]; j++){
		iPossible[j] = iDecision[j];
		for (int k = 0; k < iNumOfVar[0, node]; k++){
			if (bVarFlag[k, node] && bOutflag[j, node]){
				if (iRules[k, j, node] > iRules[k, best, node]){
					iPossible[j] = iPossible[j] + (iRules[k, j, node] - iRules[k, best, node]) * iMaxi[k, node];
				}
				else{
					iPossible[j] = iPossible[j] - (iRules[k, best, node] - iRules[k, j, node]) * iMini[k, node];
				}
			}
		}
		if (iPossible[j] < iPossible[best]) {
			bOutflag[j, node] = 0;
		}
		if (iPossible[j] >= maxposs){
			maxposs = iPossible[j];
			bestposs = j;
		}
	}
}

void node :: doTrainingMode860(int node){
	useful = 0;
	rv = 0;
	bestvar = 0;
	do{
		for (int i = 0; i < iNumOfVar[0, node]; i++){
			iRuleValues[i, node] = 0;
			mean = 0;
			number = 0;
			for (int j = 0; j < iNumOfOutcomes[0, node]; j++){
				mean = mean + iRules[i, j, node] * bVarFlag[i, node] * bOutflag[j, node];
				number = number + bOutflag[j, node];
			}
			if (number > 0){
				mean = mean / number;
			}
			for (int j = 0; j < iNumOfOutcomes[0, node]; j++){
				iRuleValues[i, node] = iRuleValues[i, node] + 
							abs(iMini[i, node] - iMaxi[i, node]) * ((iRules[i, j, node] - mean) * (iRules[i, j, node] - mean)) * bVarFlag[i, node] * bOutflag[j, node];
			}
			if (iRuleValues[i, node] > rv){
				bestvar = i;
				rv = iRuleValues[i, node];
			}
		}
		if (rv == 0) break;   
		bVarFlag[bestvar, node] = 0;
		for (int j = 0; j < iNumOfOutcomes[0, node] - 1; j++){
			for (int k = j + 1; k < iNumOfOutcomes[0, node]; k++){
				if (iRules[bestvar, j, node] != iRules[bestvar, k, node] && bOutflag[j, node] && bOutflag[k, node]){
					useful = 1;
				}
			}
		}
	}while (useful == 0);
}

void node :: compareTheDifferent1080(int node){
	for (int nn = 0; nn < iCountOfNodes; nn++){
		for (int i = 0; i < iNumOfVar[0, nn]; i++){
			if (sVar[i, nn] == sVar[bestvar, node]){
				iValue[i, nn] = iValue[bestvar, node];
				bVarFlag[i, nn] = 0;
			}
		}
	}
	for (int j = 0; j < iNumOfOutcomes[0, node]; j++){
		iDecision[j] = iDecision[j] + iValue[bestvar, node] * iRules[bestvar, j, node];
	}

}

 //?????
void node :: defineTheBestValue1160(int node){
	for (bestvar = 0; bestvar < var; bestvar++){
		if (bVarFlag[bestvar, node]){
			
		}
	}
}

void node :: correctRulesValue2680(int node){
	flag = 0;
	for (int i = 0; i < outcomes; i++){
		if (iDecision[i] >= iDecision[correct] && i != correct){
			flag = 1;
			for (int j = 0; j < var; j++){
				iRules[j, i, node] = iRules[j, i, node] - iValue[j, node];
			}
		}
	}
	if (flag == 1){
		for (int j = 0; j < var; j++){
			iRules[j, correct, node] = iRules[j, correct, node] + iValue[j, node];
		}
	}
}

void node :: compareTheBestOutComes1270(int node){
	for (int nn = 0; nn < iCountOfNodes; nn++){
		for (int i = 0; i < iNumOfVar[0, nn]; i++){
			if (sVar[i, nn] == sOutcomes[correct, node]){
				iValue[i, nn] = iMaxi[i, nn];
				bVarFlag[i, nn] = 0;
			}
			for (int j = 0; j < outcomes; j++){
				if (sVar[i, nn] == sOutcomes[j, node] && j != correct){
					iValue[i, nn] = iMini[i, nn];
					bVarFlag[i, nn] = 0;
				}
			}
		}
	}	
}

void node :: trainingSystem1580(){
	Random rnd;
	int example;
	int x;
	for (int node = 0; node < iCountOfNodes; node++){

		for (int p = 0; p < iNumOfExamples[0, node] * 10; p++){
			x = rnd.Next(0, iNumOfExamples[0, node]);
			example = x;
			correct = bExamples[iNumOfVar[0, node], example, node] - 1;
			var = iNumOfVar[0, node];
			outcomes = iNumOfOutcomes[0, node];

			for (int i = 0; i < outcomes; i++){
				iDecision[i] = 0;

				for (int j = 0; j < var; j++){
					iValue[j, node] = bExamples[j, example, node];
					iDecision[i] = iDecision[i] + iValue[j, node] * iRules[j, i, node];
				}
			}
			correctRulesValue2680(node);
		}
	}
}

