/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)

struct Person {
	char name[30];
	int age;
};

int main() {
	struct Person* p[5];
	for (int i = 0; i < sizeof(p) / sizeof(struct Person*); i++) {
		p[i] = malloc(sizeof(struct Person));
	}
	scanf("%s %d %s %d %s %d %s %d %s %d", p[0]->name, &p[0]->age,
		p[1]->name, &p[1]->age, p[2]->name, &p[2]->age,
		p[3]->name, &p[3]->age, p[4]->name, &p[4]->age);


	struct Person senior;
	senior.age = p[0]->age;
	strcpy(senior.name, p[0]->name);
	for (int i = 0; i < sizeof(p) / sizeof(struct Person*)-1; i++) {
		 if (senior.age < p[i+1]->age) {
			senior.age = p[i+1]->age;
			strcpy(senior.name, p[i+1]->name);
		}
	}
	printf("%s\n", senior.name);

	for (int i = 0; i < sizeof(p) / sizeof(struct Person*); i++)
	{
		free(p[i]);
	}
	return 0;
}*/


/*int age = 0;
	int senior = 0;
	for (int i = 0; i < sizeof(p) / sizeof(struct Person*); i++) {
		if (age < p[i]->age) {
			age = p[i]->age;
			senior = i;
		}
	}
	printf("%s\n", p[senior]->name);//코딩도장 풀이*/