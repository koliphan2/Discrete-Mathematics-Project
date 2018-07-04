#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stack>
#include "node.h"
#include "Rule.h"

using namespace std;

class Graph{
private:
    map<int, node> graph;
    vector<int> typologicalSort;
    stack<int> DFS;

    map<int, string> ruleIndex;

public:

    Graph(){
     }
    void addNode(node x){
        int index = graph.size();
        graph[index] = x;

     }
    void addNode(node x, int i){
        graph[i] = x;
     }

    void makeGraph(vector<Rule> allRules){
        for(int i = 0;i<allRules.size();i++){
            ruleIndex[i] = allRules[i].getLeftSide().getScheme();
            }
        findNeighbors(allRules);
     }
    
    void findNeighbors(vector<Rule>& rules){
        //Loop through all rules
        for(int i = 0;i<rules.size();i++){
            node tempNode = node();
            //cout << "Current Rule: " << rules[i].print() << endl;

            //Loop through rule's right side
            for(int x = 0;x<rules[i].getRightSide().size();x++){
                //cout << "Right Side: " << rules[i].at(x).print() << endl;
                //Loop through map with rules to find match
                for(auto index : ruleIndex){
                    //cout << index.second << "<- index  rules.at() ->" << rules[i].at(x).getScheme() << endl;
                    if(rules[i].at(x).getScheme() == index.second){
                        tempNode.addNeighbor(index.first);
                    }
                }
                graph[i] = tempNode;
            }
        }
    }

    map<int, node> getMap(){
        return graph;
     }

    Graph invert(Graph original){
        Graph inverted = Graph();

        node tempNode = node();
        //For each node in graph
        for(auto n : graph){
            inverted.addNode(node());
        }
        for(auto n : graph){
            //For each neighbor in node
            for(int neighbor : n.second.getNeighbors()){
                node tnode = inverted.getMap()[neighbor];
                tnode.addNeighbor(n.first);
                inverted.addNode(tnode, neighbor);
            } 
        }
        return inverted;
     }

    int size(){
        return graph.size();
     }

    string print(){
        stringstream ss = stringstream();
        for(auto n : graph){
            ss << "R" << n.first << ":";
            ss << n.second.print() << endl;
        }
        return ss.str();
     }
    
    vector<int> getTypoSort(){
        for(auto n : graph){
            while(!n.second.hasVisited()){
                if(visitNeighbors(n.second, n.first)){
                    n.second.visit();
                }
            }
        }
        int fullSize = DFS.size();
        for(int i = 0;i<fullSize;i++){
            typologicalSort.push_back(DFS.top());
            DFS.pop();
        }
        return typologicalSort;
     }

    bool visitNeighbors(node n, int i){
        n.visit();
        graph[i] = n;
        for(int neighbor : n.getNeighbors()){
            if(!graph[neighbor].hasVisited()){
                visitNeighbors(graph[neighbor], neighbor);
            }
        }
        DFS.push(i);
        return true;
     }

    vector<vector<int>> getForest(vector<int>& order){
        while(!DFS.empty()){
            DFS.pop();
        }
        unvisitAllNodes();
        vector<vector<int>> forest;
        
        for(int i = 0;i<order.size();i++){
            vector<int> tempVector;
            node tempNode = graph[order[i]];
            while(!tempNode.hasVisited()){
                if(visitNeighbors(tempNode, order[i])){
                    tempNode.visit();
                }
            }
            int treeSize = DFS.size();
            for(int i = 0;i<treeSize;i++){
                tempVector.push_back(DFS.top());
                DFS.pop();
            }
            if(tempVector.size() > 0){
                sort(tempVector.begin(), tempVector.end());
                forest.push_back(tempVector);
            }
        }
        return forest;
     }
    
    vector<vector<int>> sortGraphCompletely(Graph& g){
        Graph invert = g.invert(g);

        vector<int> typoOrder = invert.getTypoSort();

        vector<vector<int>> forest = g.getForest(typoOrder);

        return forest;
     }

    void unvisitAllNodes(){
        for(int i = 0;i<graph.size();i++){
            graph[i].unVisit();
        }
     }
};