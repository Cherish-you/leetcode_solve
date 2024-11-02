#include <iostream>
#include <vector>


using namespace std;


void DFS(vector<vector<int>> &vec,int i,int j,vector<vector<int>> &result,vector<int> &path) {
    if(i==j) {
        result.push_back(path);
        return;
    }

    for(int k=0;k<vec[i].size();k++) {
        path.push_back(vec[i][k]);
        DFS(vec,vec[i][k],j,result,path);
        path.pop_back();
    }
} 

void bianli(vector<vector<int>> &vec) {
    vector<vector<int>> result;
    int size=vec.size();//节点个数
    vector<int> path(size,0);//记录节点是否被访问过
    path.push_back(0);
    DFS(vec,0,size-1,result,path);
} 








int main() {







    return 0;
}