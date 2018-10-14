#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>

// Анна Зубкова
/*
 * 2. Переписать программу, реализующее двоичное дерево поиска.
а) Добавить в него обход дерева различными способами;+
б) Реализовать поиск в двоичном дереве поиска; +
в) *Добавить в программу обработку командной строки с помощью которой можно указывать
из какого файла считывать данные, каким образом обходить дерево. +

(заменила круглые скобки на квадратные и расставила пробелы,иначе очень сложно проверять - плохо видно)
 */
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
//Симметричный обход
void symmbypass(Node* root)
{
   if (root)
   {
	   symmbypass(root->left);
	   printf("%d ", root->data);
	   symmbypass(root->right);
   }
}
//Обратный обход
void reverseround(Node* root)
{
   if (root)
   {
	   reverseround(root->left);
	   reverseround(root->right);
	   printf("%d ", root->data);
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
        	printf(" Элемент найден");
            return root;
        }
    }
	printf(" Элемент не найден");
		return NULL;

}

int main()
{
	Node *Tree = NULL;
	//С обработкой файла что-то странное - считывается со второго символа и "буксует" в конце, числа для дерева беру из массива

	/*FILE* file = fopen("/Users/yashiro/Documents/Study/data.txt", "r");
	if (file == NULL)
	{
		puts("Can't open file!");
		exit(1);
	}
	int count;
	fscanf(file, "%d", &count);// Считываем количество записей
	int q;
	for (q = 0; q < count; q++)
	{
		int value;
		fscanf(file,"%d",&value);
		printf("\nvalue: %d", value);
		insert(&Tree,value);
	}
	fclose(file);*/

	const int n=8;
	int arr[n]={8, 9, 4, 5, 1, 15, 3, 2};
	int i;
	for(i = 0; i < n; i++)
	{
		int value;
		value=arr[i];
		insert(&Tree, value);
	}
	//fclose(file);
	printf("Дерево:\n");
	printTree(Tree);
    int x=0;
    //Обработка командной строки для выявления типа обхода
	printf("\n\nа) Если требуется произвести обход в прямом порядке (КЛП), то нажмите 1\nб) Если требуется произвести обход в симметричном порядке (ЛКП), то нажмите 2\nв) Если требуется произвести обход в обратном порядке (ЛПК), то нажмите 3\n");
	scanf("%d", &x);
	if (x==1)
	{
	printf("\nПрямой обход: ");
	preOrderTravers(Tree);
	}
	if (x==2)
	{
	printf("\nСимметричный обход: ");
	symmbypass(Tree);
	}
	if (x==3)
	{
	printf("\nОбход в обратном порядке: ");
	reverseround(Tree);
	}
	if (x!=1 & x!=2 & x!=3)
	{
		printf("\nУказано неверное значение, обход произведен не будет!");
	}
	printf("\n\nВведите элемент для поиска в дереве:\n");
	scanf("%d", &x);
	printf("\nFinder:");
	finder(Tree,x);

	return 0;
}
