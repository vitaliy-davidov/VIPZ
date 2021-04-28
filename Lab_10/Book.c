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

	if (5 != fscanf(pFile, "%s%s%d%d%lf\n", pBook->szAutor, pBook->szTitle, &pBook->nYear, &pBook->nPagesNumber, &pBook->dPrice))
		return -2;

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

	printf("Enter author name: ");
	gets_s(pBook->szAutor, 30);

	printf("Enter book name: ");
	gets_s(pBook->szTitle, 30);

	printf("Enter year of publish: ");
	scanf("%d", &pBook->nYear);

	printf("Enter count of pages: ");
	scanf("%d", &pBook->nPagesNumber);

	printf("Enter price: ");
	scanf("%lf", &pBook->dPrice);

	while (getchar() != '\n');
}