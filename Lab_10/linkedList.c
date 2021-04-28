#include "stdafx.h"
#include "Book.h"
#include "linkedList.h"
//------------------------------------------------------------------------------
int push_front(struct SBookList** ppHead, struct SBook book)
{
	if (!ppHead || !&book)
		return -1;

	struct SBookList* pFront = (struct SBookList*)malloc(sizeof(struct SBookList));

	if (!pFront)
		return -2;

	pFront->book = book;
	pFront->pNext = NULL;

	if (!*ppHead)
	{
		*ppHead = pFront;
	}
	else
	{
		pFront->pNext = *ppHead;
		(*ppHead) = pFront;
	}
	return 0;
}
//------------------------------------------------------------------------------
int push_back(struct SBookList** ppHead, struct SBook book)
{
	if (!ppHead || !&book)
		return -1;

	struct SBookList* pBack = (struct SBookList*)malloc(sizeof(struct SBookList));

	if (!pBack)
		return -2;

	pBack->book = book;
	pBack->pNext = NULL;

	struct SBookList* ptr = *ppHead;

	if (!ptr)
	{
		*ppHead = pBack;
	}
	else
	{
		while (ptr->pNext)
		{
			ptr = ptr->pNext;
		}
		ptr->pNext = pBack;
	}
	return 0;
}
//------------------------------------------------------------------------------
int pushAndSort(struct SBookList** ppHead, struct SBook book)
{
	int nResult = push_front(ppHead, book);
	if (nResult)
		return nResult;

	sortByPrice(ppHead);

	return 0;
}

//------------------------------------------------------------------------------
int pop_front(struct SBookList** ppHead)
{
	if (!*ppHead || !ppHead)
		return -1;
	struct SBookList* ptr = (*ppHead)->pNext;
	free(*ppHead);
	*ppHead = ptr;
	return 0;
}
//------------------------------------------------------------------------------
int pop_back(struct SBookList** ppHead)
{
	if (!*ppHead || !ppHead)
		return -1;
	struct SBookList* ptr = *ppHead;
	if (!ptr->pNext)
	{
		free(*ppHead);
		*ppHead = NULL;
	}
	else
	{
		while (ptr->pNext->pNext)
		{
			ptr = ptr->pNext;
		}
		free(ptr->pNext);
		ptr->pNext = NULL;
	}
	return 0;
}
//------------------------------------------------------------------------------
int removeAllSmaller(struct SBookList** ppHead, double dPrice)
{
	if (!*ppHead)
		return -1;

	while ((*ppHead)->book.dPrice < dPrice)
	{
		pop_front(ppHead);
	}
	return 0;
}
//------------------------------------------------------------------------------
void clear(struct SBookList** ppHead)
{
	while (*ppHead)
	{
		pop_front(ppHead);
	}
}

//------------------------------------------------------------------------------
int sortByPrice(struct SBookList** ppHead)
{
	if (!*ppHead)
		return -1;

	if (!(*ppHead)->pNext)
		return 0;

	int nExit = 0;
	while (!nExit)
	{
		nExit = 1;
		struct SBookList* ptr = *ppHead;

		while (ptr->pNext)
		{
			if (ptr->book.dPrice > ptr->pNext->book.dPrice)
			{
				swap(ptr, ptr->pNext);
				nExit = 0;
			}
			ptr = ptr->pNext;
		}
	}
	return 0;
}
//------------------------------------------------------------------------------
int swap(struct SBookList* pNode1, struct SBookList* pNode2)
{
	if (!pNode1 || !pNode2)
		return -1;

	struct SBook ptr = pNode1->book;
	pNode1->book = pNode2->book;
	pNode2->book = ptr;

	return 0;
}

//------------------------------------------------------------------------------
struct SBookList* find(struct SBookList* pHead, struct SBook* pBook)
{
	if (!pHead)
		return NULL;

	struct SBookList* ptr = pHead;

	while (ptr)
	{
		if (isBookEqual(&ptr->book, pBook))
			return ptr;
		ptr = ptr->pNext;
	}
	return NULL;
}
//------------------------------------------------------------------------------
struct SBookList* findAllByLetter(struct SBookList* pHead, char chLetter)
{
	if (!pHead)
		return NULL;

	struct SBookList* ptr = pHead;

	struct SBookList* pFindedBooks = NULL;

	while (ptr)
	{
		if (ptr->book.szAutor[0] == toupper(chLetter))
		{
			push_front(&pFindedBooks, ptr->book);
		}
		ptr = ptr->pNext;
	}
	return pFindedBooks;
}
//------------------------------------------------------------------------------
double findAvgPrice(struct SBookList* pHead)
{
	if (!pHead)
		return -1;
	int nNodeCounter = 0;
	double dPrice = 0;

	struct SBookList* ptr = pHead;

	while (ptr)
	{
		nNodeCounter++;
		dPrice += ptr->book.dPrice;
		ptr = ptr->pNext;
	}
	return dPrice / nNodeCounter;
}

//------------------------------------------------------------------------------
int printBookList(struct SBookList* pHead)
{
	if (!pHead)
		return -1;
	struct SBookList* ptr = pHead;

	while (ptr)
	{
		printBook(&ptr->book);
		ptr = ptr->pNext;
	}
	return 0;
}
//------------------------------------------------------------------------------
int saveBooks(FILE* pFile, struct SBookList* pHead)
{
	if (!pFile || !pHead)
		return -1;

	struct SBookList* ptr = pHead;

	while (ptr)
	{
		saveToFile(pFile, ptr->book);

		ptr = ptr->pNext;
	}

	return 0;
}
//------------------------------------------------------------------------------
int loadBooks(FILE* pFile, struct SBookList** ppHead)
{
	if (!ppHead || !pFile)
		return -3;

	struct SBookList* ptr = *ppHead;

	if (feof(pFile))
	{
		return EOF;
	}

	while (!feof(pFile))
	{
		struct SBook b;
		int nOut = loadFromFile(pFile, &b);
		if(-2 == nOut || EOF == nOut) return nOut;

		push_back(ppHead, b);
	}

	return 0;
}
//------------------------------------------------------------------------------