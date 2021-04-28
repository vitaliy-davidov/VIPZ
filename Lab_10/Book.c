#include "stdafx.h"
#include "Book.h"
//------------------------------------------------------------------------------
int printBook(struct SBook* pBook)
{
	if (!pBook)
		return -1;
	printf("%-30s%-30s%-10d%-10d%-10lf\n", pBook->szAutor, pBook->szTitle, pBook->nYear, pBook->nPagesNumber, pBook->dPrice);
	return 0;
}
//------------------------------------------------------------------------------
int isBookEqual(struct SBook* pBook1, struct SBook* pBook2)
{
	if (!pBook1 || !pBook2)
		return -1;

	if (pBook1->szAutor != pBook2->szAutor)
		return 0;
	if (pBook1->szTitle != pBook2->szTitle)
		return 0;
	if (pBook1->nPagesNumber != pBook2->nPagesNumber)
		return 0;
	if (pBook1->nYear != pBook2->nYear)
		return 0;
	if (pBook1->dPrice != pBook2->dPrice)
		return 0;

	return 1;
}
//------------------------------------------------------------------------------
int saveToFile(FILE* pFile, const struct SBook book)
{
	if (!pFile)
		return -1;

	char* pch = NULL;
	do
	{
		pch = (char*)memchr(book.szAutor, ' ', strlen(book.szAutor));
		if (pch)
			*pch = '_';
	} while (pch);
	do
	{
		pch = (char*)memchr(book.szTitle, ' ', strlen(book.szTitle));
		if (pch)
			*pch = '_';
	} while (pch);

	fprintf(pFile, "%-30s%-30s%-10d%-10d%-10lf\n", book.szAutor, book.szTitle, book.nYear, book.nPagesNumber, book.dPrice);

	return 0;
}
//------------------------------------------------------------------------------
int loadFromFile(FILE* pFile, struct SBook* pBook)
{
	if (!pFile)
		return -3;
	if (feof(pFile))
		return EOF;

	char szYear[10] = "", szPagesNumber[10] = "", szPrice[10] = "";
	fscanf(pFile, "%s%s%s%s%s\n", pBook->szAutor, pBook->szTitle, szYear,szPagesNumber, szPrice);

	if (testStrByNoNumber(szYear) || testStrByNoNumber(szPagesNumber) || testStrByNoNumber(szPrice))
		return -2;

	pBook->nYear = atoi(szYear);
	pBook->nPagesNumber = atoi(szPagesNumber);
	pBook->dPrice = atof(szPrice);

	char* pch = NULL;
	do
	{
		pch = (char*)memchr(pBook->szAutor, '_', strlen(pBook->szAutor));
		if (pch)
			*pch = ' ';
	} while (pch);
	do
	{
		pch = (char*)memchr(pBook->szTitle, '_', strlen(pBook->szTitle));
		if (pch)
			*pch = ' ';
	} while (pch);

	return 0;
}
//------------------------------------------------------------------------------
void ConsoleInput(struct SBook* pBook)
{
	while (getchar() != '\n');
	do
	{
		printf("Enter author name: ");
		gets_s(pBook->szAutor, 30);
		if (testStrByNoLetter(pBook->szAutor))
			printf("Wrong input\n");
		else break;
	} while (1);

	printf("Enter book name: ");
	gets_s(pBook->szTitle, 30);

	do
	{
		printf("Enter year of publish: ");
		if (scanf("%d", &pBook->nYear))break;
		printf("Wrong input\n");
	} while (getchar() != '\n');
	do
	{
		printf("Enter count of pages: ");
		if (scanf("%d", &pBook->nPagesNumber))break;
		printf("Wrong input\n");
	} while (getchar() != '\n');
	do
	{
		printf("Enter price: ");
		if (scanf("%lf", &pBook->dPrice))break;
		printf("Wrong input\n");
	} while (getchar() != '\n');
}
//------------------------------------------------------------------------------
int testStrByNoNumber(char* str)
{
	if (strlen(str) == 0) return -1;
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]) && str[i] != '.')
			return -1;
	}
	return 0;
}
//------------------------------------------------------------------------------
int testStrByNoLetter(char* str)
{
	if (strlen(str) == 0) return -1;
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isalpha(str[i]))
			return -1;
	}
	return 0;
}