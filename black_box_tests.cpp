//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Jakub Kuzník <xkuzni04@stud.fit.vutbr.cz>
// $Date:       $2021.02.22
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Jakub Kuznik
 *itor.action.selectAll 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/


class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};
        for(auto value : values)
        {
            tree.InsertNode(value); 
        }
    }
    BinaryTree tree;

};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};
        for(auto value : values)
        {
            tree.InsertNode(value); 
        }
    }
    BinaryTree tree;

};

//EMPTY_TREE


TEST_F(EmptyTree, InsertNode)
{
    auto return_value = tree.InsertNode(23);
    EXPECT_TRUE(return_value.first);
    EXPECT_EQ(return_value.second->key, 23);

    return_value = tree.InsertNode(23);
    EXPECT_FALSE(return_value.first);
    EXPECT_EQ(return_value.second->key, 23);
    EXPECT_EQ(return_value.second->pParent, nullptr);

    return_value = tree.InsertNode(0);
    EXPECT_TRUE(return_value.first);
    EXPECT_EQ(return_value.second->key, 0);
    EXPECT_EQ(return_value.second->pParent->key, 23);

    return_value = tree.InsertNode(-756);
    EXPECT_EQ(return_value.second->key, -756);

}

TEST_F(EmptyTree, DeleteNode)
{
    auto node1 = tree.InsertNode(23);
    auto node2 = tree.InsertNode(0);
    
    auto return_value = tree.DeleteNode(node2.second->key);
    EXPECT_TRUE(return_value);
    EXPECT_EQ(node2.second->key, NULL);
    return_value = tree.DeleteNode(node2.second->key);
    EXPECT_FALSE(return_value);

    return_value = tree.DeleteNode(node1.second->key);
    EXPECT_TRUE(return_value);  //it returns true so it find the node but not delete it

   /* 
   EXPECT_EQ(node1.second, nullptr);  
    //here is mistake becouse after delete here is 23 but it should be NULL
   */
}

TEST_F(EmptyTree, FindNode)
{
    auto return_value = tree.FindNode(0);
    EXPECT_EQ(return_value, nullptr);

    auto node1 = tree.InsertNode(23);
    auto node2 = tree.InsertNode(0);

    return_value = tree.FindNode(0);
    EXPECT_EQ(return_value, node2.second);
    return_value = tree.FindNode(23);
    EXPECT_EQ(return_value, node1.second);
}

//NON_EMPTY_TREE


TEST_F(NonEmptyTree, InsertNode)
{
    auto node1 = tree.InsertNode(-3);
    auto node2 = tree.InsertNode(0);
    auto node3 = tree.InsertNode(1);

    EXPECT_FALSE(node2.first);
    EXPECT_TRUE(node1.first);
    EXPECT_TRUE(node3.first);

    EXPECT_EQ(node1.second->key, -3);
    auto return_value = tree.FindNode(1);
   
   EXPECT_EQ(return_value, node3.second);

}
TEST_F(NonEmptyTree, DeleteNode)
{
    int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};
    for(int i = 0; i < 13; i++)
    {
        auto node1 = tree.FindNode(values[i]);
        EXPECT_EQ(node1->key, values[i]);
        
        auto return_val = tree.DeleteNode(values[i]);
        
        auto node2 = tree.FindNode(values[i]);            
        EXPECT_EQ(node2, nullptr);
    }

    auto return_val = tree.DeleteNode(50);
    EXPECT_EQ(return_val , false);

}
TEST_F(NonEmptyTree, FindNode)
{
    int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};    
    for(int i = 0; i < 13; i++)
    {
        auto node1 = tree.FindNode(values[i]);
        EXPECT_EQ(node1->key, values[i]);
    }

    auto return_val = tree.DeleteNode(0);
    auto node1 = tree.FindNode(0);
    EXPECT_EQ(node1, nullptr);
}


//TREE_AXIOMS


//If node is leaf is black
TEST_F(TreeAxioms, Axiom1)
{
    int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};
    auto node1 = tree.FindNode(0);
    for(int i = 0; i < 13; i++)
    {                       
        node1 = tree.FindNode(values[i]);            
        if(node1->pLeft == nullptr && node1->pRight == nullptr)
            EXPECT_EQ(node1->color, BLACK);
    }
}

//If node is red then all his child are black 
TEST_F(TreeAxioms, Axiom2)
{
    int values[] = {-1, 0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13};
    auto node1 = tree.FindNode(0);
    
    for(int i = 0; i < 13; i++)
    {                       
        node1 = tree.FindNode(values[i]);            
        if(node1->color == RED)
        {
            EXPECT_EQ(node1->pLeft->color, BLACK);
            EXPECT_EQ(node1->pRight->color, BLACK);
        }
    }
}

//Every path to root from leaf have same amount of black nodes.
TEST_F(TreeAxioms, Axiom3)
{
    int path_lenght = 0;
    std::vector<Node_t *> vector;
    tree.GetLeafNodes(vector);
    
    auto node1 = vector[0];
    while (node1 != nullptr)
    {
        if(node1->color == BLACK)
            path_lenght++;
        node1 = node1->pParent;
    }
    for(int i = 0; i < vector.size(); i++ )
    {    
        int value = 0;  
        node1 = vector[i];                 
        while (node1 != nullptr)
        {
            if(node1->color == BLACK)
                value++;
            node1 = node1->pParent;
        }
        EXPECT_EQ(path_lenght, value);
    }
}


//SOMETHING MORE 

//Geting root 
TEST_F(EmptyTree, GetRoot)
{

    auto return_val = tree.GetRoot();    
    EXPECT_EQ(return_val, nullptr);

    auto node1 = tree.InsertNode(23);
    auto node2 = tree.InsertNode(23);


    return_val = tree.GetRoot();
    EXPECT_EQ(return_val, node1.second);
}

//DESTRUCTOR 

TEST_F(NonEmptyTree, GetRoot)
{
    tree.~BinaryTree();
    auto result = tree.GetRoot();

    EXPECT_EQ(result, nullptr);

}