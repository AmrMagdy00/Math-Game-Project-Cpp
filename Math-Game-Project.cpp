#include <iostream>
using namespace std;
enum enQuestionLevel {
	Easy = 1,
	Mid = 2,
	Hard = 3,
	Mix = 4,
};
enum enOperationType {
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	MixOp = 5,
};
string GetOpTypeSympol(enOperationType OP) {
	string arrOP[4]{ "+","-","*","/" };
	return arrOP[OP - 1];
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
	string arrQuestionLeveL[4]{ "Easy","Mid","Hard","Mix" };
	return arrQuestionLeveL[QuestionLevel - 1];

}
int GetRandomNumber(int From, int To) {
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
void SetScreenColor(bool right) {
	if (right) {
		system("color 2F"); //Turn screen to Green
	}
	else {
		system("color 4F"); //Turn screen to Red
		cout << "\a";		//Ring Bill
	}

}
short ReadHowManyQues() {
	short NumberOfQuestions;
	do {
		cout << "How Many Questions Do You Want To Answer ? " << endl;
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions > 10 || NumberOfQuestions < 1);
	return NumberOfQuestions;
}
enQuestionLevel ReadQuestionsLevel() {
	short QuestionLevel;
	do {
		cout << "Enter Question Level [1] Easy , [2] Mid , [3] Hard , [4] Mix ?" << endl;
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return  (enQuestionLevel)QuestionLevel;
}
enOperationType ReadOpertaionType() {
	short OperationType;
	do {
		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div, [5] Mix " << endl;
		cin >> OperationType;
	} while (OperationType > 5 || OperationType < 1);
	return  (enOperationType)OperationType;

};
struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLeveL;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult;
};
struct stQuizz {
	stQuestion QuestionsList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionLeveL;
	enOperationType OperationType;
	short CorrectAnswers = 0;
	short WrongAnswers = 0;
	bool isPass = false;
};
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType) {
	switch (OperationType) {
	case enOperationType::Add:
		return Number1 + Number2;

	case enOperationType::Sub:
		return Number1 - Number2;

	case enOperationType::Mul:
		return Number1 * Number2;

	case enOperationType::Div:
		return Number1 / Number2;
	}

}
stQuestion GenerateQuestion(enOperationType OperationType, enQuestionLevel QuestionLevel) {
	stQuestion Qustion;
	if (QuestionLevel == enQuestionLevel::Mix) {
		QuestionLevel = (enQuestionLevel)GetRandomNumber(1, 3);
	};
	if (OperationType == enOperationType::MixOp) {
		OperationType = (enOperationType)GetRandomNumber(1, 4);
	}
	Qustion.OperationType = OperationType;


	switch (QuestionLevel) {

	case enQuestionLevel::Easy:
		Qustion.Number1 = GetRandomNumber(1, 10);
		Qustion.Number2 = GetRandomNumber(1, 10);
		Qustion.CorrectAnswer = SimpleCalculator(Qustion.Number1, Qustion.Number2, Qustion.OperationType);
		Qustion.QuestionLeveL = QuestionLevel;
		return Qustion;

	case enQuestionLevel::Mid:
		Qustion.Number1 = GetRandomNumber(10, 50);
		Qustion.Number2 = GetRandomNumber(10, 50);
		Qustion.CorrectAnswer = SimpleCalculator(Qustion.Number1, Qustion.Number2, Qustion.OperationType);
		Qustion.QuestionLeveL = QuestionLevel;
		return Qustion;

	case enQuestionLevel::Hard:
		Qustion.Number1 = GetRandomNumber(50, 100);
		Qustion.Number2 = GetRandomNumber(50, 100);
		Qustion.CorrectAnswer = SimpleCalculator(Qustion.Number1, Qustion.Number2, Qustion.OperationType);
		Qustion.QuestionLeveL = QuestionLevel;
		return Qustion;

	}
	return Qustion;

}
void GenerateQuestions(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.OperationType, Quizz.QuestionLeveL);
	}
}
void PrintTheQuestion(stQuizz Quizz, short QuestionNumber) {
	int Answer = 0;


	cout << "\n\n==============================\n";
	cout << "Questin [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]" << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
	cout << GetOpTypeSympol(Quizz.QuestionsList[QuestionNumber].OperationType) << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << endl;
	cout << "==============================" << endl;


}
int ReadQuestionAnswer() {
	int Answer;
	cin >> Answer;
	return Answer;
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {

	if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer == Quizz.QuestionsList[QuestionNumber].PlayerAnswer) {
		Quizz.CorrectAnswers++;
		Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
		cout << "Right Answer :-)" << endl;
		SetScreenColor(true);
	}
	else {
		Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
		Quizz.WrongAnswers++;
		SetScreenColor(false);
		cout << "Wrong Answer :-(";
		cout << "The Correct Answer IS : " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer << endl;
	}
}void AskAndCorrectQuestions(stQuizz& Quizz) {
	short Answer;
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		PrintTheQuestion(Quizz, Question);
		Quizz.QuestionsList[Question].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, Question);

	}
	Quizz.isPass = (Quizz.CorrectAnswers >= Quizz.WrongAnswers);
}
string GetUserReult(bool pass) {
	if (pass)
		return "Pass";
	else
		return"Fail";

}
void PrintQuizzResults(stQuizz Quizz) {
	cout << "\n\n-----------------------------------------------\n" << endl;
	cout << "Fial result Is : " << GetUserReult(Quizz.isPass) << "\n" << endl;
	cout << "-----------------------------------------------\n" << endl;
	cout << "Number of Question IS : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level IS : " << GetQuestionLevelText(Quizz.QuestionLeveL) << endl;
	cout << "Number Of  Right Answer IS : " << Quizz.CorrectAnswers << endl;
	cout << "Number Of  Wrong Answer IS : " << Quizz.WrongAnswers << endl;
	cout << "-----------------------------------------------\n" << endl;



}
void PlayMathGame() {
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQues();
	Quizz.OperationType = ReadOpertaionType();
	Quizz.QuestionLeveL = ReadQuestionsLevel();
	GenerateQuestions(Quizz);
	AskAndCorrectQuestions(Quizz);
	PrintQuizzResults(Quizz);



}
void ResetScreen() {
	system("color 0f");
	system("cls");
}
void StartGame() {


	char PlayAgain;

	do {
		ResetScreen();
		PlayMathGame();

		cout << "Do You Want To Play Again ? " << endl;
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	StartGame();
}