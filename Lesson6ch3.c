#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <string.h>



/*3. *Разработать базу данных студентов из двух полей “Имя”, “Возраст”, “Табельный номер” в которой
использовать все знания, полученные на уроках.
Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных
(возраст, вес)*/

//Структура под студентов

struct student
{
 char surname[10]; //Фамилия
 int ages; //Возраст
 int uniqnumber; //Табельный номер
}stud;


//Дерево поиска+поиск
typedef int T;
typedef struct Node {
	T data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
}Node;

//Создали новый узел
Node* getFreeNode(T value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node *root) {
	if (root)
	{
		printf("%d",root->data);
		if (root->left || root->right)
		{
		printf(" [ ");
		if (root->left)
		printTree(root->left);
		else
		printf("NULL");
		printf(" , ");
		if (root->right)
		printTree(root->right);
		else
		printf("NULL");
		printf(" ] ");
		}
	}
}

// Вставка узла
void insert(Node **head, int value)
{
	Node *tmp = NULL;
	if (*head == NULL) {
		*head = getFreeNode(value, NULL);
		return;
	}
	tmp = *head;
	while (tmp) {
		if (value> tmp->data) {
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			else
			{
				tmp->right = getFreeNode(value, tmp);
				return;
			}
		}
		else if (value<tmp->data)
		{ if (tmp->left)
		{
			tmp=tmp->left;
			continue;
		}
		else
		{
			tmp->left = getFreeNode(value, tmp);
			return;
		}
		}
		else{exit(2); //дерево построено неправильно
		}
	}
}

void preOrderTravers(Node* root) {
	if (root) {
	printf("%d ", root->data);
	preOrderTravers(root->left);
	preOrderTravers(root->right);
	}
}

//2б Поиск

Node *finder(Node *root, int key)
{
	while (root) //Есть узлы
    {
        if (root->data > key) //Значение меньше узла , тогда идем влево
        {
            root = root->left;
            continue;
        }
        else if (root->data < key)//Значение больше узла , тогда идем вправо
        {
            root = root->right;
            continue;
        }
        else
        {
        	printf(" Данные по студенту найдены");
            return root;
        }
    }
	printf(" Данные по студенту не найдены");
		return NULL;

}

//filefinder
void students(int key)
{
	FILE *file= fopen("/Users/yashiro/Documents/Study/data.txt", "r");;
	const int f=30;
	char tempstr[f]; //в массив будет закладываться строка файла
	int kol=0; //количество записей в файле

	while (fgets(tempstr, f, file))
		//Преобразование полученной строки в структуру
	{
		strncpy(stud.surname,tempstr,9); //фамилию в строку
		stud.ages=atoi(&tempstr[10]); // возраст в int
		stud.uniqnumber=atoi(&tempstr[13]);
		kol++;
		if (stud.uniqnumber==key)
		{
			printf("\nФамилия  Age №");
			printf("\n%s %d %d", stud.surname,stud.ages,stud.uniqnumber); //выведем табличку
		}
	}
}


int main()
{
	Node *Tree = NULL;
	//Студентов берем из файла
	FILE *file= fopen("/Users/yashiro/Documents/Study/data.txt", "r");;
	const int f=30;
	char tempstr[f]; //в массив будет закладываться строка файла
	int kol=0; //количество записей в файле
	printf("Фамилия  Age №\n");
	while (fgets(tempstr, f, file))
		//Преобразование полученной строки в структуру
	{
		strncpy(stud.surname,tempstr,9); //фамилию в строку
		stud.ages=atoi(&tempstr[10]); // возраст в int
		stud.uniqnumber=atoi(&tempstr[13]);
		printf("\n%s %d %d", stud.surname,stud.ages,stud.uniqnumber); //выведем табличку
		insert(&Tree,stud.uniqnumber);
		kol++;
	}
	fclose(file);
	printf("\n\nДерево:\n");
		printTree(Tree);
		int x=0;
		printf("\n\nВведите элемент для поиска в дереве:\n");
		scanf("%d", &x);
		printf("\nFinder:");
		finder(Tree,x);
		students(x);
 return 0;

}

