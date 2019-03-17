#include "main.h"

int main() {

	char first_input[MAX];

	while (1) {

		printf("$ ");
		scanf("%[^\n]", first_input);

		int result = analysis(first_input);

		if (result == 1) {
			break;
		}
		else if (result == -1) {
			printf("유효하지 않은 명령입니다! 다시 입력해주십시오\n");
		}

		getchar();
	}

	getchar();
	getchar();

}

int analysis(char first_input[]) {

	char *token;
	
	token = strtok(first_input, " ");

	if (strcmp(token, "read") == 0) {
		token = strtok(NULL, " ");
		read_dict(token);
		return 0;
	}
	else if (strcmp(token, "size") == 0) {
		size_dict();
		return 0;
	}
	else if (strcmp(token, "find") == 0) {
		token = strtok(NULL, " ");
		find_dict1(token);
		return 0;
	}
	else if (strcmp(token, "exit") == 0) {
		return 1;
	}
	else {
		return -1;
	}
	return -1;
}