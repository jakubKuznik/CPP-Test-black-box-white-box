//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Jakub Kuzník <xkuzni04@stud.fit.vutbr.cz>
// $Date:       $2021-02-22
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Jakub Kuzník 
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/

class Matrix_1x1 : public ::testing::Test
{
protected:
    Matrix m{};
};


//matrix with values 3x3
class Matrix_3x3: public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        m.set({{3,2,2},{0, 4, 19},{-90, 60, 20}});
    }
    Matrix m{3, 3};
};


//matrix with values 2x3
class Matrix_2x3: public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        m.set({{3,2,2},{0, 4, 19}});
    }
    Matrix m{2, 3};
};


//Basic constructor test 
TEST(BasicTests, MatrixConstructor)
{
    Matrix m{};
    Matrix m2{3, 3};
    
    EXPECT_EQ(m.get(0, 0), 0);
    EXPECT_ANY_THROW(m.get(3,3));


    EXPECT_ANY_THROW(new Matrix(-5, 1));
    EXPECT_ANY_THROW(new Matrix(0,0));
}

//Test for set and get functions 
TEST(BasicTests, SetGet)
{
    Matrix m{2, 2};
    
    bool return_val = m.set(3, 3, 5);
    EXPECT_FALSE(return_val);

    return_val = m.set(1, 1, -5);
    EXPECT_TRUE(return_val);

    double result = m.get(1,1);
    EXPECT_EQ(result, -5);
    EXPECT_ANY_THROW(result = m.get(5,5));

    
    return_val = m.set({{2,2}, {2,2}});
    EXPECT_TRUE(return_val);
    EXPECT_EQ(m.get(1,1), 2);

    return_val = m.set({{2,2}, {2,2}, {2,2}});
    EXPECT_FALSE(return_val);


    return_val = m.set({{2}, {2,2}});
    EXPECT_FALSE(return_val);

}

//It 
TEST_F(Matrix_3x3, Operator_eq_eq)
{

    Matrix m1 = m; 
    m1.set(1,2,-399);

    Matrix m3{2, 3};
    m3.set({{3,2,2},{0, 4, 19}});

    Matrix m4{1,1};

    bool return_value = m.operator==(m1);
    EXPECT_FALSE(return_value);

    return_value = m.operator==(m);
    EXPECT_TRUE(return_value);

    EXPECT_ANY_THROW(return_value = m.operator==(m3));
    EXPECT_ANY_THROW(return_value = m.operator==(m4));
}

TEST_F(Matrix_2x3, Operator_plus)
{
    Matrix m1 = m;
    Matrix m2{2, 2};

    Matrix m_result = m.operator+(m1);
    double val = 0;
    
    for(int r = 0; r < 2; r++)
        for(int i = 0; i < 3; i++)
            EXPECT_EQ(m_result.get(r, i),(m.get(r,i) + m1.get(r,i)));

    EXPECT_ANY_THROW(m.operator+(m2));
}



TEST_F(Matrix_2x3, Operator_multiply)
{
    Matrix m1{3,3}, m2{2,1};
    Matrix m_result{3,3};
    m1.set({{3, 2, 2}, {0, 4, 19}, {-90, 60, 20}});
    m2.set({{1},{2}});

    EXPECT_ANY_THROW(m_result = m.operator*(m));
    m_result = m1*m1;


    EXPECT_EQ(m_result.get(0,0), -171);
    EXPECT_EQ(m_result.get(1,0), -1710);
    EXPECT_EQ(m_result.get(2,0), -2070);
}

TEST_F(Matrix_3x3, Operator_scalar)
{
    Matrix m1{3,3};
    m1.set({{3, 2, 2}, {0, 4, 19}, {-90, 60, 20}});

    m1 = m1*(-5);
    double result = m1.get(0,0);
    EXPECT_EQ(result, -15);

    m1 = m1.operator*(0);
    EXPECT_EQ(m1.get(0,0), 0);
}

//Cramer rule 
TEST_F(Matrix_3x3, Solve_equation)
{
    Matrix m2{2,1};
    Matrix m3_singular{2,2};
    Matrix m4{3,3};
    Matrix m5{1,1};
    Matrix m_quadra{4,4};
    

    m2.set({{1},{2}});
    m3_singular.set({{1,2},{1,2}});
    m4.set({{2,3,7},{3,8,1},{0,3,3}});
    m5.set({{1}});
    m_quadra.set({{1,2,-1,1},{-1,1,2,-1},{2,-1,2,2},{1,1,-1,2}});

    std::vector<double> vector = {1, 1};
    std::vector<double> vector2 = {47, 50, 27};
    std::vector<double> vector4 = {1};
    std::vector<double> vector3 = {1, 1, 1};
    std::vector<double> vector_quadra = {6,3,14,8};

    
    EXPECT_ANY_THROW(m2.solveEquation(vector));
    EXPECT_ANY_THROW(m.solveEquation(vector4));
    EXPECT_ANY_THROW(m3_singular.solveEquation(vector));


    std::vector<double> vector_result = {0,0,0};
    std::vector<double> vector_result1 = {0};
    std::vector<double> vector_result_quadra = {0,0,0,0};

    vector_result_quadra = m_quadra.solveEquation(vector_quadra);
    vector_result = m4.solveEquation(vector2);
    vector_result1 = m5.solveEquation(vector4);

    EXPECT_EQ(vector_result[0], 2);
    EXPECT_EQ(vector_result[1], 5);
    EXPECT_EQ(vector_result[2], 4);
    EXPECT_EQ(vector_result1[0], 1);

    //quadra
    EXPECT_EQ(vector_result_quadra[0],1);
    EXPECT_EQ(vector_result_quadra[1],2 );
    EXPECT_EQ(vector_result_quadra[2],3 );
    EXPECT_EQ(vector_result_quadra[3],4 );


}

TEST_F(Matrix_2x3, Transpose)
{
    Matrix m_t{3,2};
    m_t = m.transpose();
    for(int r =0; r <2; r++)
        for(int i = 0; i < 3; i++)
            EXPECT_EQ(m.get(r, i), m_t.get(i, r));
}

TEST(BasicTests, Inverse)
{
    Matrix m{2,2};
    Matrix m_res{2,2};
    Matrix m2{2,1};
    Matrix m3_singular{2,2};
    Matrix m3{3,3};


    m.set({{1,2},{3,4}});
    m2.set({{1},{2}});
    m3_singular.set({{1,2},{1,2}});
    m3.set({{1,1,1},{0,2,2},{0,0,2}});

    EXPECT_ANY_THROW(m2.inverse());
    EXPECT_ANY_THROW(m3_singular.inverse());    

    m_res = m.inverse();
    EXPECT_EQ(m_res.get(0,0), -2);
    EXPECT_EQ(m_res.get(0,1), 1);
    EXPECT_EQ(m_res.get(1,0), 1.5);
    EXPECT_EQ(m_res.get(1,1), -0.5);

    m3 = m3.inverse();
    EXPECT_EQ(m3.get(0,0), 1);
    EXPECT_EQ(m3.get(0,1), -0.5);
    EXPECT_EQ(m3.get(0,2), 0);

    EXPECT_EQ(m3.get(1,0), 0);
    EXPECT_EQ(m3.get(1,1), 0.5);
    EXPECT_EQ(m3.get(1,2), -0.5);
    
    EXPECT_EQ(m3.get(2,0), 0);
    EXPECT_EQ(m3.get(2,1), 0);
    EXPECT_EQ(m3.get(2,2), 0.5);
}

