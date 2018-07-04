/*#include <fstream>
#include <iomanip>
#include <vector>
#include "Graph.h"

int main(){
    Graph g1 = Graph();
    node n10 = node();
    n10.addNeighbor(1);
    n10.addNeighbor(3);

    node n11 = node();
    n11.addNeighbor(2);

    node n12 = node();
    n12.addNeighbor(3);
    n12.addNeighbor(4);

    node n13 = node();
    n13.addNeighbor(4);

    node n14 = node();

    node n15 = node();
    n15.addNeighbor(0);

    g1.addNode(n10);
    g1.addNode(n11);
    g1.addNode(n12);
    g1.addNode(n13);
    g1.addNode(n14);
    g1.addNode(n15);

    cout << endl << "Test 1: Invert non-recursive graph" << endl;

    cout << "Original:" << endl << g1.print() << endl;
    Graph invert1 = g1.invert(g1);
    cout << "Inverted:" << endl << invert1.print();
    string expected1 = "0 :- 5, \n1 :- 0, \n2 :- 1, \n3 :- 0, 2, \n4 :- 2, 3, \n5 :- \n";
    if(invert1.print() == expected1){
        cout << "PASS" << endl;
    }









    Graph g2 = Graph();
    node n20 = node();
    n20.addNeighbor(0);
    n20.addNeighbor(4);
    n20.addNeighbor(3);

    node n21 = node();
    n21.addNeighbor(5);
    n21.addNeighbor(0);
    n21.addNeighbor(3);

    node n22 = node();
    n22.addNeighbor(4);
    n22.addNeighbor(2);

    node n23 = node();
    n23.addNeighbor(4);
    n23.addNeighbor(1);
    n23.addNeighbor(5);

    node n24 = node();
    n24.addNeighbor(2);
    n24.addNeighbor(4);

    g2.addNode(n20);
    g2.addNode(n21);
    g2.addNode(n22);
    g2.addNode(n23);
    g2.addNode(n24);
    g2.addNode(node());

    cout << endl << "Test 2: Invert recursive graph" << endl;
    cout << "Original:" << endl << g2.print() << endl;
    Graph invert2 = g2.invert(g2);
    cout << "Inverted:" << endl << invert2.print();
    string expected2 = "0 :- 0, 1, \n1 :- 3, \n2 :- 2, 4, \n3 :- 0, 1, \n4 :- 0, 2, 3, 4, \n5 :- 1, 3, \n";
    if(invert2.print() == expected2){
        cout << "PASS" << endl;
    }









    cout << endl << "Test 3: Typological Sort Non-Recursive graph" << endl; 
    vector<int> typoOrder3 = invert1.getTypoSort();
    cout << "Inverted:" << endl << invert1.print();
    cout << endl << "Typological Sort: ";
    stringstream ss3 = stringstream();
    string expected3 = "4,3,2,1,0,5,";
    for(int x = 0;x<typoOrder3.size();x++){
        ss3 << typoOrder3[x] << ",";
    }
    cout << ss3.str() << endl;
    if(ss3.str() == expected3){
        cout << "PASS" << endl;
    }










    cout << endl << "Test 4: Typological Sort Recursive graph"; 
    vector<int> typoOrder4 = invert2.getTypoSort();
    cout << "Inverted:" << endl << invert2.print();
    cout << endl << "Typological Sort: ";
    stringstream ss4 = stringstream();
    string expected4 = "5,2,4,0,1,3,";
    for(int x = 0;x<typoOrder4.size();x++){
        ss4 << typoOrder4[x] << ",";
    }
    cout << ss4.str() << endl;
    if(ss4.str() == expected4){
        cout << "PASS" << endl;
    }




    




    cout << endl << "Test 5: Forest - no strongly connected componants:" << endl;
    cout << "Original Graph: " << endl;
    cout << g1.print() << endl;
    cout << "Typological Sorting Order: " << ss3.str() << endl;
    vector<vector<int>> forest = g1.getForest(typoOrder3);
    cout << "\nForest:\n";
    for(int x = 0;x<forest.size();x++){
        cout << "{";
        for(int i = 0;i<forest[x].size();i++){
        cout << forest[x][i] << ",";
        }
        cout << "}" << endl;
    }
    //Exptected Forest Vector
    vector<vector<int>> expected5;
    vector<vector<int>> forestE;
    vector<int> temp1;
    vector<int> temp2;
    vector<int> temp3;
    vector<int> temp4;
    vector<int> temp5;
    vector<int> temp6;

    temp1.push_back(4);
    temp2.push_back(3);
    temp3.push_back(2);
    temp4.push_back(1);
    temp5.push_back(0);
    temp6.push_back(5);
    expected5.push_back(temp1);
    expected5.push_back(temp2);
    expected5.push_back(temp3);
    expected5.push_back(temp4);
    expected5.push_back(temp5);
    expected5.push_back(temp6);

    if(forest == expected5){
        cout << "PASS" << endl;
    }










    cout << endl << "Test 6: Forest - Small strongly connected componants:" << endl;
    cout << "Original Graph: " << endl;
    cout << g2.print() << endl;
    cout << "Typological Sorting Order: " << ss4.str() << endl;
    vector<vector<int>> forest6 = g2.getForest(typoOrder4);
    cout << "\nForest:\n";
    for(int x = 0;x<forest6.size();x++){
        cout << "{";
        for(int i = 0;i<forest6[x].size();i++){
        cout << forest6[x][i] << ",";
        }
        cout << "}" << endl;
    }
    //Exptected Forest Vector
    vector<vector<int>> expected6;
    vector<int> temp61;
    vector<int> temp62;
    vector<int> temp63;
    temp61.push_back(5);
    temp62.push_back(2);
    temp62.push_back(4);
    temp63.push_back(0);
    temp63.push_back(3);
    temp63.push_back(1);
    expected6.push_back(temp61);
    expected6.push_back(temp62);
    expected6.push_back(temp63);

    if(forest6 == expected6){
        cout << "PASS" << endl;
    }










    cout << endl << "Test 7: Get result from original - no pauses or breaks or changes:" << endl;
    cout << "Original Graph: " << endl;
    cout << g2.print();
    vector<vector<int>> forest7 = g2.sortGraphCompletely(g2);
    cout << "\nForest:\n";
    for(int x = 0;x<forest7.size();x++){
        cout << "{";
        for(int i = 0;i<forest7[x].size();i++){
        cout << forest7[x][i] << ",";
        }
        cout << "}" << endl;
    }
    //zero recursion... something is up with that.

    vector<vector<int>> expected7;
    vector<int> temp71;
    vector<int> temp72;
    vector<int> temp73;
    temp71.push_back(5);
    temp72.push_back(2);
    temp72.push_back(4);
    temp73.push_back(0);
    temp73.push_back(3);
    temp73.push_back(1);
    expected7.push_back(temp71);
    expected7.push_back(temp72);
    expected7.push_back(temp73);

    if(forest7 == expected7){
        cout << "PASS" << endl;
    }











    Graph g8 = Graph();
    node n80 = node();
    n80.addNeighbor(3);
    n80.addNeighbor(2);

    node n81 = node();
    n81.addNeighbor(2);
    n81.addNeighbor(0);

    node n82 = node();
    n82.addNeighbor(5);
    n82.addNeighbor(0);

    node n83 = node();
    n83.addNeighbor(4);
    n83.addNeighbor(1);
    

    node n84 = node();
    n84.addNeighbor(5);

    node n85 = node();
    n85.addNeighbor(3);
    n85.addNeighbor(2);

    g8.addNode(n80);
    g8.addNode(n81);
    g8.addNode(n82);
    g8.addNode(n83);
    g8.addNode(n84);
    g8.addNode(n85);

    cout << endl << "Test 8: One Big strongly connected componant" << endl;
    cout << "Original Graph: " << endl;
    cout << g8.print();
    vector<vector<int>> forest8 = g8.sortGraphCompletely(g8);
    cout << "\nForest:\n";
    for(int x = 0;x<forest8.size();x++){
        cout << "{";
        for(int i = 0;i<forest8[x].size();i++){
        cout << forest8[x][i] << ",";
        }
        cout << "}" << endl;
    }

    vector<vector<int>> expected8;
    vector<int> temp81;
    

    temp81.push_back(0);
    temp81.push_back(2);
    temp81.push_back(5);
    temp81.push_back(3);
    temp81.push_back(4);
    temp81.push_back(1);
    expected8.push_back(temp81);

    if(forest8 == expected8){
        cout << "PASS" << endl;
    }









    cout << endl << "Test 9: Empty Graph?" << endl;
    Graph g9 = g1;
    for(int i = 0;i<g9.size();i++){
        g9.addNode(node(), i);
    }
    cout << g9.print();
    vector<vector<int>> forest9 = g9.sortGraphCompletely(g9);
    cout << "\nForest:\n";
    for(int x = 0;x<forest9.size();x++){
        cout << "{";
        for(int i = 0;i<forest9[x].size();i++){
        cout << forest9[x][i] << ",";
        }
        cout << "}" << endl;
    }
    vector<vector<int>> expected9;
    vector<int> temp91;
    vector<int> temp92;
    vector<int> temp93;
    vector<int> temp94;
    vector<int> temp95;
    vector<int> temp96;

    temp91.push_back(5);
    temp92.push_back(4);
    temp93.push_back(3);
    temp94.push_back(2);
    temp95.push_back(1);
    temp96.push_back(0);
    expected9.push_back(temp91);
    expected9.push_back(temp92);
    expected9.push_back(temp93);
    expected9.push_back(temp94);
    expected9.push_back(temp95);
    expected9.push_back(temp96);

    if(forest9 == expected9){
        cout << "PASS" << endl;
    }













    Graph g10 = Graph();
    node n100 = node();
    n100.addNeighbor(3);
    n100.addNeighbor(2);
    n100.addNeighbor(6);

    node n101 = node();
    n101.addNeighbor(6);

    node n102 = node();
    n102.addNeighbor(5);
    n102.addNeighbor(0);

    node n103 = node();
    n103.addNeighbor(2); 
    n103.addNeighbor(4);
    n103.addNeighbor(5);
    
    node n104 = node();
    n104.addNeighbor(5);

    node n105 = node();
    n105.addNeighbor(3);

    node n106 = node();
    n106.addNeighbor(1);

    node n107 = node();
    n107.addNeighbor(3);
    n107.addNeighbor(8);

    node n108 = node();
    n108.addNeighbor(0);

    g10.addNode(n100);
    g10.addNode(n101);
    g10.addNode(n102);
    g10.addNode(n103);
    g10.addNode(n104);
    g10.addNode(n105);
    g10.addNode(n106);
    g10.addNode(n107);
    g10.addNode(n108);
    

    cout << endl << "Test 10: Larger Graph" << endl;
    
    cout << g10.print();
    vector<vector<int>> forest10 = g10.sortGraphCompletely(g10);
    cout << "\nForest:\n";
    for(int x = 0;x<forest10.size();x++){
        cout << "{";
        for(int i = 0;i<forest10[x].size();i++){
        cout << forest10[x][i] << ",";
        }
        cout << "}" << endl;
    }


    vector<vector<int>> expected10;
    vector<int> temp101;
    vector<int> temp102;
    vector<int> temp103;
    vector<int> temp104;

    temp101.push_back(1);
    temp101.push_back(6);
    temp102.push_back(0);
    temp102.push_back(2);
    temp102.push_back(5);
    temp102.push_back(3);
    temp102.push_back(4);
    temp103.push_back(8);
    temp104.push_back(7);

    expected10.push_back(temp101);
    expected10.push_back(temp102);
    expected10.push_back(temp103);
    expected10.push_back(temp104);

    if(forest10 == expected10){
        cout << "PASS" << endl;
    }
}
*/