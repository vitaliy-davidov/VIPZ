#pragma once

struct SBook
{
	char szAutor[30];
	char szTitle[30];
	int nYear;
	int nPagesNumber;
	double dPrice;
};

//------------------------------------------------------------------------------

/*???????? ? ??????? ?????.
??????? ????????? ?? ?????*/
int printBook(struct SBook* pBook);

//------------------------------------------------------------------------------

/*????????? ????? ?? ?????????.
??????? ?????????? ?? ?????*/
int isBookEqual(struct SBook* pBook1, struct SBook* pBook2);

//------------------------------------------------------------------------------

/*???????? ????? ? ????.
??????? ????????? ?? ???????? ????? ?? ?????*/
int saveToFile(FILE* pFile, const struct SBook book);

//------------------------------------------------------------------------------

/*?????? ????? ? ????.
??????? ????????? ?? ???????? ????? ?? ????????? ?? ?????*/
int loadFromFile(FILE* pFile, struct SBook* pBook);

//------------------------------------------------------------------------------

/*?????? ????? ? ???????.
??????? ????????? ????????? ?? ?????*/
void ConsoleInput(struct SBook* pBook);
