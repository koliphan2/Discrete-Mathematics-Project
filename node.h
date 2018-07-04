#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class node{
private:
    bool visited;
    set<int> neighbors;


public:
    node(){
        visited = false;
    }
    void visit(){
        visited = true;
    }
    void unVisit(){
        visited = false;
    }
    bool hasVisited(){
        return visited;
    }

    set<int> getNeighbors(){
        return neighbors;
    }
    void addNeighbor(int i){
        neighbors.insert(i);
    }

    string print(){
        stringstream ss = stringstream();
        for(int x : neighbors){
            ss << "R" << x;
            ss << ",";
        }
        ss.seekp(-1, ss.end);
        ss << " ";
        return ss.str();
    }

};
