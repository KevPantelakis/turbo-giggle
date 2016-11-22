#include <iostream>

#include "Test_TP5.h"

int main() {
	Test_TP5 TestCorrection;

	//TestCorrection.executeCompositeTest();
	//TestCorrection.executeTemplateMethodTest();
	TestCorrection.executeVisiteurTest();
	TestCorrection.executeCommandeTest();

	return 0;
}