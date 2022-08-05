

//`g++ std=c++11 main.cpp -o main && cat input/0.txt | ./main`
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef pair<int,int> node;

/*this is just a vanilla min-heap implementation with O(n) pop() 
time complexity. It can be improved to reach O(log n)*/
class min_heap{
public:
    //skip the constructor to keep it simple
    map<node,double> tab;
    double v_min=100000.0;
    node n_min=make_pair(0,0);
    //insert and update min
    void push(node n,double v){
        tab.insert(make_pair(n,v));
        if(v<v_min){
            v_min=v;
            n_min=n;
        }
    }
    void update_cost(node n,double v){
        tab[n]=v;
        update_min();
    }
    
    bool exist(node n){
        return tab.find(n)!=tab.end();
    }
    //retrieve min
    pair<node,double> top(){
        return make_pair(n_min,v_min);
    }

    void pop(){
        tab.erase(n_min);
        update_min();
    }
    
    void update_min(){
        //now update min
        v_min=100000.0;
        n_min=make_pair(0,0);
        for(auto& it:tab){
            if(it.second<v_min){
                v_min=it.second;
                n_min=it.first;
            }
        }
    }
    bool empty(){
        return tab.empty();
    }

    double operator[](node n){
        return tab[n];
    }
};


int main() {
    //initialization and input handling
    vector<string> grid;
    map<node,node> predec;
    string s;
    while(getline(cin, s)){
        s.erase(remove(s.begin(), s.end(), ' '), s.end());//remove spaces
        grid.push_back(s);//
    }
    int i{0};
    int j{0};
    while(i<grid.size()){
        cout<<grid[i]<<endl;
        i++;
    }
    //get grid dimensions
    long n_cols{(long)grid[0].size()};
    long n_rows{(long)grid.size()};
    cout<<"grid size: "<<n_rows<<" by "<<n_cols<<endl;
    //lets find where the robot is
    char cell;
    node home;
    for(int i{0};i<n_rows;i++){
        for(int j{0};j<n_cols;j++){
            cell=grid[i][j];
            if(cell=='&'){
                home=make_pair(i,j);
                break;
            }
        }
        if(cell=='&'){
            break;
        }
    }
    cout<<"home is at ("<<home.first<<","<<home.second<<")"<<endl;

    /* A* is ideal for a typical path finding, however here goals are neither unique nor known 
    and it is not trivial to find a single heuristic cost function. I will use Dijkstra instead.*/
    min_heap open;
    min_heap results;
    //now search for targets a corresponding paths and insert in a min heap
    //insert the home node in the open set
    open.push(home,0.0);
    set<node> closed;
    while(!open.empty()){
        pair<node,double> current=open.top();
        open.pop();
        // cout<<current.first.first<<","<<current.first.second<<" poped"<<endl;
        //check if a goal is reached
        if(grid[current.first.first][current.first.second]=='O'){
            results.push(current.first,current.second);
        }
        for(int i: {-1,0,1}){
            for(int j: {-1,0,1}){
                //confine to cardinal directions and grid boundaries
                if(((i!=0 && j==0) || (i==0 && j!=0)) && current.first.first+i<n_rows && current.first.first+i>-1 && current.first.second+j<n_cols && current.first.second+j>-1 && grid[current.first.first+i][current.first.second+j]!='X'){
                    node new_node=make_pair(current.first.first+i,current.first.second+j);
                    if(closed.find(new_node)==closed.end()){
                        // cout<<new_node.first<<","<<new_node.second<<" examining"<<endl;

                        double added_cost{0.0};
                        switch(grid[new_node.first][new_node.second]){
                            case '.':{
                                added_cost=1.0;
                                break;
                            }
                            case 'O':{
                                added_cost=1.0;
                                break;
                            }
                            case '~':{
                                added_cost=3.0;
                                break;
                            }
                        }
                        // cout<<"added cost:"<<added_cost<<endl;
                        if(open.exist(new_node)){
                            // cout<<"node existed in open"<<endl;
                            // cout<<"current cost:"<<open[new_node]<<", new cost:"<<current.second+added_cost<<endl;
                            if(open[new_node]>current.second+added_cost){
                                open.update_cost(new_node,current.second+added_cost);
                                cout<<"updating cost to:"<<current.second+added_cost<<endl;
                                predec[new_node]=current.first;
                            }

                        }
                        else{
                            open.push(new_node,current.second+added_cost);
                            predec[new_node]=current.first;
                        }
                    }

                }
            }
        }
        closed.insert(current.first);

    }
    cout<<"--------goals---------"<<endl;
    while(!results.empty()){
        cout<<results.n_min.second<<","<<results.n_min.first<<","<<results.v_min<<endl;
        results.pop();
    }

    return 0;
}
