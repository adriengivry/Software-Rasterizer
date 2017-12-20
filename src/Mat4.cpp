#include "Mat4.h"

Mat4::Mat4(Vec4& vec4)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
            {
                if(i == 0)
                {
                    this->m_matrix[i][j] = vec4.m_x;
                }
                else if (i == 1)
                {
                    this->m_matrix[i][j] = vec4.m_y;
                }
                else if(i == 2)
                {
                    this->m_matrix[i][j] = vec4.m_z;
                }
                else if(i == 3)
                {
                    this->m_matrix[i][j] = vec4.m_w;
                }
            }
        }
    }
}

Mat4::Mat4()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                this->m_matrix[i][j] = 1;
            else
            {
                this->m_matrix[i][j] = 0;
            }
        }
    }
   
}

Mat4::~Mat4()
{
}

Mat4& Mat4::operator*(const Mat4& other)
{
    float Multsum = 0;
    Mat4 Multiply;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) 
        {
            for (int k = 0; k < 4; k++) 
            {
                Multsum = Multsum + this->m_matrix[i][k] * other.m_matrix[k][j];
            }
            Multiply.m_matrix[i][j] = Multsum;
        }
    }
    return Multiply;
}

Vec4& Mat4::operator*(const Vec4& other)
{
    float MultVec = 0;
    Vec4 Multiply;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            MultVec = MultVec + this->m_matrix[i][j] * other.m_x;
            MultVec = MultVec + this->m_matrix[i][j] * other.m_y;
            MultVec = MultVec + this->m_matrix[i][j] * other.m_z;
        }
        if (i == 0)
        {
            Multiply.m_x = MultVec;
        }
        else if(i == 1)
        {
            Multiply.m_y = MultVec;
        }
        else if(i == 2)
        {
            Multiply.m_z = MultVec;
        }
        MultVec = 0;
    }
    return Multiply;
}

Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    Mat4 Transform;
    //set Rotation First
    for(int i = 0; i < 3; i ++)
    {
        Transform.m_matrix[i][0] = rotation.m_x;
        Transform.m_matrix[i][1] = rotation.m_y;
        Transform.m_matrix[i][2] = rotation.m_z;
    }
    //set Translation
        Transform.m_matrix[0][3] = position.m_x;
        Transform.m_matrix[1][3] = position.m_y;
        Transform.m_matrix[2][3] = position.m_z;
    //set Scaling
        Transform.m_matrix[3][0] = scale.m_x;
        Transform.m_matrix[3][1] = scale.m_y;
        Transform.m_matrix[3][2] = scale.m_z;
        return Transform;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
{
    Mat4 Translate;
    Translate.m_matrix[0][0] = translation.m_x;
    Translate.m_matrix[1][1] = translation.m_y;
    Translate.m_matrix[2][2] = translation.m_z;
    return Translate;
}
Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
{
    Mat4 Scale;
    Scale.m_matrix[3][0] = scale.m_x;
    Scale.m_matrix[3][1] = scale.m_y;
    Scale.m_matrix[3][2] = scale.m_z;
    return Scale;
}
Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    angle = angle * M_PI / 180;
  
        Mat4 rotate;
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 4; j++) 
            {
                if (i == 1 && j == 1) 
                {
                    rotate.m_matrix[i][j] = cos(angle);
                }
                else if (i == 1 && j == 2) 
                {
                    rotate.m_matrix[i][j] = sin(angle);
                }
                else if (i == 2 && j == 1) 
                {
                    rotate.m_matrix[i][j] = -sin(angle);
                }
                else if (i == 2 && j == 2) 
                {
                    rotate.m_matrix[i][j] = cos(angle);
                }
            }
        }
        return rotate;
}
Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    angle = angle * M_PI / 180;
    Mat4 rotate;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) 
            {
                if (i == 0 && j == 0) 
                {
                    rotate.m_matrix[i][j] = cos(angle);
                }
                else if (i == 0 && j == 2) 
                {
                    rotate.m_matrix[i][j] = -sin(angle);
                }
                else if (i == 2 && j == 0) 
                {
                   rotate.m_matrix[i][j] = sin(angle);
                }
                else if (i == 2 && j == 2) 
                {
                    rotate.m_matrix[i][j] = cos(angle);
                }
            }
        }
        return rotate;
}
Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    angle = angle * M_PI / 180;
    Mat4 rotate;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 0 && j == 0) {
                rotate.m_matrix[i][j] = cos(angle);
            }
            else if (i == 0 && j == 1) {
                rotate.m_matrix[i][j] = sin(angle);
            }
            else if (i == 1 && j == 0) {
                rotate.m_matrix[i][j] = -sin(angle);
            }
            else if (i == 1 && j == 1) {
                rotate.m_matrix[i][j] = cos(angle);
            }
        }
    }
    return rotate;
}
