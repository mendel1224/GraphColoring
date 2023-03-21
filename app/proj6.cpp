#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace proj6;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.

int Partition(InterferenceGraph<Variable>& ig, std:: vector <std::string > &numbers, int lowIndex, int highIndex) {
  // Pick middle element as pivot
  int midpoint = lowIndex + (highIndex - lowIndex) / 2;
  std:: string pivot = numbers[midpoint] ; 

  bool done = false;
  while (!done) {
     while ( ig.degree( numbers[lowIndex] ) > ig.degree(pivot) ) 
     {
        lowIndex += 1 ;
     }
     while ( ig.degree( pivot ) > ig.degree( numbers[highIndex] )  ) 
     {
        highIndex -= 1 ;
     }

     // If zero or one elements remain, then all numbers are
     // partitioned. Return highIndex.
     if (lowIndex >= highIndex) {
        done = true ;
     }
     else {
        // Swap numbers[lowIndex] and numbers[highIndex]
        
        std:: string temp = numbers[lowIndex] ; 
        numbers[lowIndex] = numbers[highIndex] ;
        numbers[highIndex] = temp ;
   
        // Update lowIndex and highIndex
        lowIndex += 1 ;
        highIndex -= 1 ;
     }
  }
  return highIndex;
}

void Quicksort(InterferenceGraph<Variable>& ig, std:: vector <std::string > &numbers, int lowIndex, int highIndex) {
   if (lowIndex >= highIndex) 
   {
      return;
   }

   int lowEndIndex = Partition( ig,  numbers, lowIndex, highIndex);
   Quicksort(ig, numbers , lowIndex, lowEndIndex);
   Quicksort(ig, numbers, lowEndIndex + 1, highIndex);
}



RegisterAssignment proj6::assignRegisters(const std::string &path_to_graph,
                                          int num_registers) noexcept {
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);

  std::unordered_map < std::string , int > outputMap ; // output of the function that will contain mapping of variable to register

  
  // TODO: You implement this!

  // Step 1: Sort according to degree

  // 1) get a list of a set of all the vertices
  // 2) Find the degree of each of the vertcies thorugh degree()
  // 3) Sort in descending order in vector 


  std:: unordered_set <std:: string > verticesSet; 

  verticesSet = ig.vertices(); // set now contains all vertices


    std::vector<std::string> verticesVector(verticesSet.size());

   std::copy(verticesSet.begin(), verticesSet.end(), verticesVector.begin() ); // Copy set contents to vector

   Quicksort(ig, verticesVector, 0 , verticesVector.size()-1);

  


  // pass unordered set into vector 
  // access the degree by using ig.degree( string)
  // sort based on that






  

  return {};
}