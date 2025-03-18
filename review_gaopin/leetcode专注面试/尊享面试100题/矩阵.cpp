#include <vector>

using namespace std;


/*c[i][j]=求和k从0到a[i].size()-1   a[i][k]*b[k][j]
遍历三个变量才能实现矩阵的乘法*/


vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
    int m1 = mat1.size();
    int m2 = mat1[0].size();
    int m4 = mat2[0].size();
    vector<vector<int>> ans(m1, vector<int>(m4));
    for(int i = 0; i < m1; i++){
        for(int j = 0; j < m4; j++){
            for(int k = 0; k < m2; k++){
                ans[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
//以i,k,j的方式遍历具有最优的空间局部性
    return ans;
}