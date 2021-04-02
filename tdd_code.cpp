//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Jakub Kuzník <xkuzni04@stud.fit.vutbr.cz>
// $Date:       $2021-02-22
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Jakub Kuzník
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>
#include "tdd_code.h"
#include <cstdio>


//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = nullptr;
}

/*Destructor*/
PriorityQueue::~PriorityQueue()
{
    Element_t *actual = m_pHead;
    for(int i = 0; i < Length(); i++)
        Remove(actual->value);    
}


/*
Funciton that insert value and sort it in list from biggest to smallest.
exam:
pt->30->10  insert(20);
pt->30->20->10
*/
void PriorityQueue::Insert(int value)
{
    Element_t *actual = m_pHead, *help = m_pHead, *help2 = m_pHead; //for simple values switching 
    bool before_end_append = false;
    
    if(m_pHead == nullptr) //if list is empty
    {
        m_pHead = new Element_t
        {
            .pNext = nullptr,
            .value = value
        };
        return;
    }
    while (actual != nullptr) // if list is not empty it ll find smaller node or last node 
    {
        if(actual->value < value)
        {
            before_end_append = true; //if we find smaller node we want to insert new node before that small one 
            break;
        }
        actual = actual->pNext;
    }
    if(before_end_append == true)  //When u want to insert big value before some smaller px>0   insert(100) px>100>0
    {
        if(m_pHead->value < value)  //special if for first place insert(50) to: pr->40->32
        {
            help = new Element_t
            {
                .pNext = m_pHead,
                .value = value
            };
            m_pHead = help;
            return;
        }
        else
        {
            help = new Element_t
            {
                .pNext = actual,
                .value = value
            };
            while (help2->pNext->value != actual->value && help2->pNext != nullptr)
                help2 = help2->pNext;
            help2->pNext = help;
        }
    }
    else
    {
        actual = m_pHead->pNext;
        while (actual != nullptr)
        {
            if(actual->pNext == nullptr)
            {
                actual->pNext = new Element_t
                {
                    .pNext = nullptr,
                    .value = value
                };
                break;
            }
            actual = actual->pNext;
        }
    }
}

/*
Function for remoting given element. 
*/
bool PriorityQueue::Remove(int value)
{
    Element_t *actual = Find(value);
    Element_t *before = m_pHead;
    Element_t *help = m_pHead;

    if (actual == nullptr)
        return false;

    if(before != nullptr)
    {
        while(before != nullptr)
        {
            if(before->pNext != nullptr)
            {
                help = before->pNext;
                if(help->value == value)
                    break;
            }
            else if(before->pNext == nullptr)
                break;
            before = before->pNext;
        }
    }
    if(value == m_pHead->value)
    {
        help = m_pHead->pNext;
        m_pHead = actual->pNext;
        delete actual; 
        return true;
    }
    if (actual != nullptr)
    {
        help = actual->pNext;
        delete actual;
        before->pNext = help;
    }
    return true;
}


/* It returns pointer of node vith given value.*/
PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *actual = m_pHead;

    if(actual == nullptr)
        return nullptr;

    while (actual != nullptr)
    {
        if(actual->value == value)
        {
            return actual;
        }
        actual = actual->pNext;
    }
    return nullptr;
}


/* Returns list lenght.*/
size_t PriorityQueue::Length()
{
    Element_t *actual = GetHead();
    if(actual == nullptr)
        return 0;
    int i = 0;
    for(;actual != nullptr; i++)
    {
        actual = actual->pNext;
    } 
    return i;
}

/*
Function returns pointer to first node. 
It is always m_pHead becouse it is begining pointer.
*/
PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
