
/* c206.c **********************************************************}
{* Topic: Double-linked list
**
**                                  Created by: Bohuslav Køena, October 2001
**                             C code migration: Martin Tuèek, October 2004
**                                      Modified by: Bohuslav Køena, October 2008
**

** Create an implementation of the Abstract Data Type for the double-linked list.
** Useful content of the list's items are whole numbers from the data type int.
** The list will be represented as data abstraction in the variable of tDLList (DL means
** Double-Linked and and the abbrevation is used for distinguishing functions, constans and
** types of double linked list from single linked list).
** The definition of constants and data types you can find in the header file c206.h.
**
** Your task is to implement following operations that create together with
** with above mentioned data part the abstract data type double-linked list:
**
**      DLInitList ...... initializes the list before first usage,
**      DLDisposeList ... disposes all items of the list,
**      DLInsertFirst ... inserts element at the list's begining,
**      DLInsertLast .... inserts element at the list's end,
**      DLFirst ......... sets activity of the first element,
**      DLLast .......... sets activity of the last element,
**      DLCopyFirst ..... returns value of the first element,
**      DLCopyLast ...... returns value of the last element,
**      DLDeleteFirst ... deletes first element of the list,
**      DLDeleteLast .... deletes last element of the list,
**      DLPostDelete .... deletes an element behind the active element,
**      DLPreDelete ..... deletes an element before the active element,
**      DLPostInsert .... inserts new element behind the active element of the list,
**      DLPreInsert ..... inserts new element before the active element of the list,
**      DLCopy .......... returns value of active element,
**      DLActualize ..... rewrites content of the active element with new value,
**      DLSucc .......... shift activity on the next element in the list,
**      DLPred .......... shift activity on the previous element in the list,
**      DLActive ........ finds out the list's activity.
**
** During the functions' implementation don't call any functions implemented
** within this example, in case that it is not order explicitly in the function.
**
** Don't care about situation when instead of the valid pointer on the list
** someone else puts as a parameter the value of NULL.
**
** Please, comment your solution properly!
**
** Note: In C language there is no procedure.
** Therefore the term of function is used for operations too, that would be
** implemented in the Pascal as procedures (in language C functions returning the
** type of void are equivelents for procedures in Pascal language).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Print notice that error happened.
** You will this function call within some further implemented operations.
**/
    printf ("*ERROR* Error during work with the list.\n");
    errflg = TRUE;             /* global variable -- errorerror flag */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Operation perfoms the list's initialisation before first use (it means that any following
** function will not be called for uninitialized list).
** This initialisation will not be performed on the initialised list and therefore don't handle
** this posibility. Expect always that uninitialised variables have undefined value.
**/
    L->First = NULL;
	L->Last = NULL;
	L->Act = NULL;
}

void DLDisposeList (tDLList *L)	{
/*
** Disposes all items in the list L and sets the list into the state before the initialisation.
** All items of the list L will be properly released with call of the free operation.
**/
	tDLElemPtr auxElem = L->First;
	tDLElemPtr next;
	while (auxElem != NULL) {
		next = auxElem->rptr;
		free(auxElem);
		auxElem = next;
	}
	auxElem = NULL;
	DLInitList(L);
}

void DLInsertFirst (tDLList *L, int val)	{
/*
** Insert the iterm with a value val at the list begining.
** In case that the memory heap is too small the function DLError() is called.
**/
	tDLElemPtr firstElem = (tDLElemPtr) malloc (sizeof (tDLElemPtr));
	
	if (firstElem != NULL) {
		firstElem-> data = val;
		firstElem-> lptr = NULL;
		firstElem-> rptr = L->First;
	if (L->First == NULL) {
		L->Last = firstElem;
	} else {
		L->First->lptr = firstElem;
	}
		L->First = firstElem;	
	}else {
		DLError();
	}
}

void DLInsertLast(tDLList *L, int val)	{
/*
** Insert the iterm with a value val at the list end (a symmetrical operation to DLInsertFirst).
** In case that the memory heap is too small the function DLError() is called.
**/
	tDLElemPtr auxElem = (tDLElemPtr) malloc (sizeof (tDLElemPtr));
	if (auxElem != NULL) {
		auxElem-> data = val;
		auxElem-> lptr = L->Last;
		L->Last->rptr = auxElem;
		auxElem-> rptr = NULL;
		L->Last = auxElem;
	} else {
		DLError();
	}

}

void DLFirst (tDLList *L)	{
/*
** Set the activity of the list on the first element.
** The function will be implemented as one comand, whereas you will not test whether the list is empty.
**/
  L->Act = L->First;
}

void DLLast (tDLList *L)	{
/*
** Set the activity of the list on the last element.
** The function will be implemented as one comand (except tthe return command),
** whereas you will not test whether the list is empty.
**/
	if (L->First != NULL) L->Act = L->Last;

}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Return the value of the first iterm of the list L.
** If the list is empty, function will call the function DLError().
**/
	if (L->First!=NULL) {
		*val = L->First->data;
	} else {
		DLError();
	}
}

void DLCopyLast (tDLList *L, int *val)	{
/*
** Return the value of the last iterm of the list L.
** If the list is empty, function will call the function DLError().
**/
	if (L->Last!=NULL) {
		*val = L->Last->data;
	} else {
		DLError();
	}
}

void DLDeleteFirst (tDLList *L)	{
/*
** Delete the first element of the list L. If the deleting element is active then this activity is lost.
** If the list L is empty then nothing happend!
**/
	if (L->First!=NULL) {
		if (L->Act == L-> First) L->Act = NULL;
		if (L->Last == L-> First) L->Last = NULL;
		tDLElemPtr new = L->First;
		L->First=L->First->rptr;
		free(new);
	}
}

void DLDeleteLast (tDLList *L)	{
/*
** Delete the last element of the list L. If the deleting element is active then this activity is lost.
** If the list L is empty then nothing happend!
**/
	if (L->First!=NULL) {
		if (L->Act == L-> Last) L->Act = NULL;
		if (L->First == L-> Last) L->Last = NULL;
		tDLElemPtr new = L->Last;
		L->Last=L->Last->lptr;
		L->Last->rptr=NULL;
		free(new);
	}
}

void DLPostDelete (tDLList *L)	{
/*
** Delete element behind active element in the list L. If the list is not active
** or the last element of the list is active then nothing happened!
**/
	if (DLActive(L) && (L->Act!=L->Last)) {
		tDLElemPtr temp = L->Act->rptr;
		if (temp == L->Last) {
			L->Act = L->Last;
		} else {
			L->Act->rptr = temp->rptr;
			temp->rptr->lptr=L->Act;
		}
		free(temp);
	}
}

void DLPreDelete (tDLList *L)	{
/*
** Delete element front of the active element in the list L. If the list is not active
** or the last element of the list is active then nothing happened!
**/
		printf("%d", L->Act->lptr->data);
		if (DLActive(L) && (L->Act!=L->First)) {
		tDLElemPtr temp = L->Act->lptr;
		if (temp == L->First) {
			L->First = L->Act;
		} else {
			L->Act->lptr = temp->lptr;
			temp->lptr->rptr = L->Act;
		}
		free(temp);
	}
}

void DLPostInsert (tDLList *L, int val) {
/*
** Insert the element with the value of val after the active element of the list L.
** If the list was not active nothing happened.
** In case that the memory is insufficient for the new element within a call of the malloc then call
** function of DLError().
**/
	if (DLActive(L)){
		tDLElemPtr auxElem = (tDLElemPtr) malloc (sizeof (tDLElemPtr));
		if (auxElem != NULL) {
			auxElem->data = val;
			auxElem->lptr = L->Act;
			auxElem->rptr = L->Act->rptr;
			L->Act->rptr = auxElem;
		} else {
			DLError();
		}
	}
}


void DLPreInsert (tDLList *L, int val)		{
/*
** Insert the element with the value of val front of the active element of the list L.
** If the list was not active nothing happened.
** In case that the memory is insufficient for the new element within a call of the malloc then call
** function of DLError().
**/
	if (DLActive(L)){
		tDLElemPtr auxElem = (tDLElemPtr) malloc (sizeof (tDLElemPtr));
		if (auxElem != NULL) {
			auxElem->data = val;
			auxElem->rptr = L->Act;
			auxElem->lptr = L->Act->lptr;
			L->Act->lptr = auxElem;
		} else {
			DLError();
		}
	}
}

void DLCopy (tDLList *L, int *val)	{
/*
** Returns a value of the active element in the list L.
** If the list is inactive the call function of DLError().
**/
		if (DLActive(L)) {
		*val = L->Act->data;
	} else {
		DLError();
	}
}

void DLActualize (tDLList *L, int val) {
/*
** Rewrite value of the active element in the list L.
** If the list L is not active, then do nothing.
**/
	if (DLActive(L)) {
		L->Act->data = val;
	}
}

void DLSucc (tDLList *L)	{
/*
** Shift activity on the next element in the list.
** Remark, that this operation can caussed inactivity of the list L in case that
** the last element of the list is active.
** If the list L is not active, then do nothing.
**/
	if (DLActive(L)) {
		if (L->Act != L->Last) {
			L->Act = L->Act->rptr;
		} else {
			L->Act = NULL;
		}
	}
}


void DLPred (tDLList *L)	{
/*
** Shift activity on the previous element in the list.
** Remark, that this operation can caussed inactivity of the list L in case that
** the first element of the list is active.
** If the list L is not active, then do nothing.
**/
	if (DLActive(L)) {
		if (L->Act != L->First) {
			L->Act = L->Act->lptr;

		} else {
			L->Act = NULL;
		}
	}
}

int DLActive (tDLList *L) {
/*
** If the list L is active, then return True else return False.
** This function will be implemented as one command return.
**/
	return L->Act != NULL;
}

/* Konec c206.c*/
