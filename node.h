#pragma once
using namespace System;

ref class node
{
public:
	int iCountOfNodes;
	int var;
	int outcomes;
	int best, bestposs, decision, maxposs, bestvar, rv, mean, number, correct;
	bool training, useful, flag;
	
	array<int, 2> ^iNumOfVar;
	array<int, 2> ^iNumOfExamples;
	array<int, 2> ^iNumOfOutcomes; 

	array<String^, 2> ^sVar;
	array<int, 2> ^iValue;
	array<bool, 2> ^bVarFlag;// ??
	array<int, 2> ^iRuleValues;
	array<int, 3> ^bExamples;
	array<String^, 2> ^sOutcomes;
	array<int, 3> ^iRules;
	array<bool, 2> ^bOutflag;
	array<int> ^iDecision;
	array<int> ^iPossible;
	array<int, 2> ^iMini;
	array<int, 2> ^iMaxi;

	node(int iNumOfNodes, int iNumOfV, int iNumOfOutcom, int iNumOfExamp);

	void saveToFile(int numOfNode, int iNumOfV, int iNumOfOutcom, int iNumOfExamp, String^ pathToFile);
	void loadFromFile(int iNumOfNode, bool deleteIndex, String^ pathToFile);
	void saveInitData(int iNumOfNodes, int iNumOfV, int iNumOfOutcom, int iNumOfExamp, String^ pathToFile);
	//Ничего не удалить
	void doNormalOrTrainingMode(bool mode);
	void compareTheDifferent1080(int node);
	void calculationDecisionAndBest670(int node);
	void calculationPossibleAndBestposs750(int node);
	void doTrainingMode860(int node);
	//ничего нет удалить
	void defineTheBestValue1160(int node);
	void compareTheBestOutComes1270(int node);
	void correctRulesValue2680(int node);
	void trainingSystem1580();
//	void defineValueOfBestVar(int node);
	//fillOutcomes(String^ )
};
