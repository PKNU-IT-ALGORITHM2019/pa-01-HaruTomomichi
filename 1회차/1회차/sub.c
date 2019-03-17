#include "sub.h"

DATA words[SIZE];

int total = 0;

void make_dict1(char buffer[]) {

	char first[MAX] = { NULL }, second[MAX] = { NULL }, third[MAX] = { NULL };

	char *token;
	token = strtok(buffer, " ");

	if (strcmp(token, "\n") == 0) {
		return;
	}

	strcpy(first, token);

	while (1) {
		token = strtok(NULL, " ");

		if (token[0] == '(') {
			break;
		}
		else {
			strcat(first, token);
		}
	}

	strcpy(second, token);

	if (token[0] == '(' && token[strlen(token) - 1] == ')') {
		token = strtok(NULL, " ");
	}
	else {
		while (1) {
			token = strtok(NULL, " ");

			if (token == NULL) {
				break;
			}

			if (token[strlen(token) - 1] == ')') {
				strcat(second, " ");
				strcat(second, token);
				token = strtok(NULL, " ");
				break;
			}
			else {
				strcat(second, " ");
				strcat(second, token);
			}
		}
	}

	if (token != NULL) {
		strcpy(third, token);
	}

	while (1) {
		token = strtok(NULL, " ");

		if (token == NULL) {
			break;
		}
		else {
			strcat(third, " ");
			strcat(third, token);
		}
	}

	make_dict2(first, second, third);
}

void make_dict2(char first[], char second[], char third[]) {
	words[total].word = strdup(first);
	words[total].part = strdup(second);
	words[total].meaning = strdup(third);

	total++;
}

void read_dict(char *token) {

	char temp[MAX];
	
	FILE *fp = fopen(token, "r");

	while (!feof(fp)) {

		fgets(temp, MAX, fp);

		char buffer[MAX] = { NULL };
		int i = 0, j = 0;

		if (strcmp(temp, "\n") == 0) {
			continue;
		}

		while (temp[i] != -52) {
			if (i == strlen(temp)) {
				break;
			}

			if (temp[i] < 0) {
				i++;
				continue;
			}
			else if (temp[i] != '\0') {
				buffer[j] = temp[i];
				i++;
				j++;

			}
			else {
				i++;
			}

		}

		make_dict1(buffer);

		fgets(temp, MAX, fp);
	}
}

void size_dict() {
	printf("%d\n", total);
}

void find_dict1(char *token) {

	int cal1 = 0, cal2 = 0;

	while (1) {

		int ret = find_dict2(token, 0, total);

		if (ret < 0) {
			printf("Not Found\n");
			ret += total;

			printf("%s %s\n- - -\n", words[ret].word, words[ret].part);
			printf("%s %s\n", words[ret + 1].word, words[ret + 1].part);
			break;
		}
		else {
			
			int temp = ret;

			cal1++;
			ret++;

			while (ret < total && strcasecmp(token, words[ret].word) == 0) {
				cal1++;
				ret++;
			}

			temp--;

			while (temp >= 0 && strcasecmp(token, words[temp].word) == 0) {
				cal2++;
				temp--;
			}

			temp++;

			printf("Found %d items\n", cal1+cal2);
			for (int i = 0; i < cal2; i++) {
				printf("%s %s %s\n", words[temp+i].word, words[temp + i].part, words[temp + i].meaning);
			}
			for (int i = 0; i < cal1; i++) {
				printf("%s %s %s\n", words[ret - cal1 + i].word, words[ret - cal1 + i].part, words[ret - cal1 + i].meaning);
			}
			break;
		}
	}
}

int find_dict2(char *token,int start,int end) {

	if (start == end - 1 && strcasecmp(token, words[start].word) != 0) {
		return start - total-1;
	}
	else if (start + 1 == end && strcasecmp(token, words[start].word) != 0) {
		return end - total-1;
	}

	int result = (start + end) / 2;

	if (strcasecmp(token, words[result].word) == 0) {
		return result;
	}
	else if (strcasecmp(token, words[result].word) < 0) {
		return find_dict2(token, start, result);
	}
	else {
		return find_dict2(token, result, end);
	}
}