#define _CTR_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "linkedList.h"

char* ValidateLoad(int returns);

int main()
{
	struct SBookList* pHead = NULL;

	printf("How do you want to enter the list of books? Press (f) for file and (press any other key) for console:");
	if (toupper(getchar()) == 'F')
	{
		FILE* pFile = fopen(".\\Data.txt", "r");

		char outMessage[40] = "";
		if (strcmp(strcpy(outMessage, ValidateLoad(loadBooks(pFile, &pHead))),"\0"))
		{
			printf(outMessage);
			return -1;
		}

		fclose(pFile);
	}
	else
	{
		int nBooksNumber = 0;
		printf("Enter number of books: ");
		scanf("%d", &nBooksNumber);

		for (int i = 0; i < nBooksNumber; i++)
		{
			struct SBook curBook;

			ConsoleInput(&curBook);

			push_front(&pHead, curBook);
		}
	}
	printf("\n");
	printf("%-30s%-30s%-10s%-10s%-10s\n", "Autor name", "Book name", "Year", "Pages number", "Price");
	printBookList(pHead);

	sortByPrice(&pHead);

	printf("\n");
	printf("List after sort:\n");
	printf("%-30s%-30s%-10s%-10s%-10s\n", "Autor name", "Book name", "Year", "Pages number", "Price");
	printBookList(pHead);

	printf("\n");
	printf("Do you want find books whose autor name stats with 'A'? Press (1) to find: ");
	char szCoise[20];
	scanf("%s", &szCoise);
	if (szCoise[0] == '1')
	{
		struct SBookList* pFindedBooks = findAllByLetter(pHead, 'A');

		if (pFindedBooks)
		{
			printf("%-30s%-30s%-10s%-10s%-10s\n", "Autor name", "Book name", "Year", "Pages number", "Price");
			printBookList(pFindedBooks);
		}
		clear(&pFindedBooks);
	}

	printf("Do you want delte books whose price lower then avarange price? Press (1) to delete: ");
	scanf("%s", &szCoise);
	if (szCoise[0] == '1')
	{
		removeAllSmaller(&pHead, findAvgPrice(pHead));
	}
	printf("\n");
	printf("Final list:\n");
	printf("%-30s%-30s%-10s%-10s%-10s\n", "Autor name", "Book name", "Year", "Pages number", "Price");
	printBookList(pHead);

	printf("\n");
	printf("Do you want to save data? Press (1) to save: ");
	scanf("%s", &szCoise);
	if (szCoise[0] == '1')
	{
		FILE* pFile = fopen(".\\Out.txt", "w");
		saveBooks(pFile, pHead);
		fclose(pFile);
	}

	clear(&pHead);
	return 0;
}

char* ValidateLoad(int returns)
{
	if (returns == 0)
	{
		return "\0";
	}
	if (returns == -3)
	{
		return "Argument exeption";
	}
	if (returns == -2)
	{
		return "File was corrupted";
	}
	if (returns == EOF)
	{
		return "File is empty";
	}
}