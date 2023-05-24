#define cat_len 40
#define que_len 200
#define ans_len 40
#pragma warning( disable : 4703)
#pragma warning( disable : 4996)

struct QuestionList {
	int id; 
	char category[cat_len]; 
	char question[que_len];
	char ans_a[ans_len];
	char ans_b[ans_len];
	char ans_c[ans_len];
	char ans_d[ans_len];
	int correct;
	struct QuestionList* next;
};

struct Game {

	int question_nr;
	int activeQuestion; 
	int goodAnswer; 
	int wrongAnswer; 

	int leftAnswers[2]; 

	bool win;
	bool lose;

	bool fiftyAvailable;
	bool phoneAvailable;
	bool crowdAvailable; 

	bool fiftyUsed; 
	bool phoneUsed;
	bool crowdUsed;

	bool panelOn;

	int phoneOption;
	int phoneChosen;

	int crowdChosen;
	char crowdPrint[30]; 

}new_game;

struct QuestionToPrint {
	char category[cat_len];
	char question[que_len];
	char ans_a[ans_len];
	char ans_b[ans_len];
	char ans_c[ans_len];
	char ans_d[ans_len];
}question;

int CountQuestions(struct QuestionList* head) {
	int licznik = 0;
	while (head->next != NULL) {
		licznik++;
		head = head->next;
	}
	return licznik;
}

int Cash(int id) {
	int rewards[] = { 500,1000,2000,5000,10000,20000,40000,75000,125000,250000,500000,1000000 };
	if (id == -1)
		return 0;
	else
		return rewards[id];
}

void Question(struct QuestionList* head)
{
	if (CountQuestions(head) > 1)
	{
		int pos = rand() % CountQuestions(head) + 1;
		struct QuestionList* temp = head;
		int i;
		for (i = 0; i < pos - 2; i++)
		{
			temp = temp->next;
		}
		struct QuestionList* del = temp->next;
		temp->next = temp->next->next;
		new_game.goodAnswer = del->correct;
		strcpy(question.category, del->category);
		strcpy(question.question, del->question);
		strcpy(question.ans_a, del->ans_a);
		strcpy(question.ans_b, del->ans_b);
		strcpy(question.ans_c, del->ans_c);
		strcpy(question.ans_d, del->ans_d);
		del->next = NULL;
		free(del);
	}
}

void deleteList(struct QuestionList** head)
{
	struct QuestionList* prev = *head;
	while (*head)
	{
		*head = (*head)->next;
		free(prev);
		prev = *head;
	}
}

void file_read(struct QuestionList** head)
{
	FILE* file = fopen("pytania.txt", "r");
	int i = 0; char line[128];
	while (!feof(file)) {
		struct QuestionList* new_QuestionList
			= (struct QuestionList*)malloc(sizeof(struct QuestionList));
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->category, line);
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->question, line);
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_a, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_b, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_c, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_d, line);
		fgets(line, sizeof(line), file);
		new_QuestionList->correct = atoi(line);
		new_QuestionList->id = i;
		i++;
		new_QuestionList->next = *head;
		*head = new_QuestionList;
	}

}