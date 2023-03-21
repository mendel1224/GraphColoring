#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <set>

using namespace proj6;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.

int Partition(InterferenceGraph<Variable>& ig, std:: vector <std::string > &numbers, int lowIndex, int highIndex) // Using Zybooks code for Quick Sort
{
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

  // 1) get a list  of all the vertices
  // 2) copy to a vector
  // 3) Find the degree of each of the vertcies thorugh degree()
  // 4) Sort in descending order in vector 


  std:: unordered_set <std:: string > verticesSet; 

  verticesSet = ig.vertices(); // set now contains all vertices


    std::vector<std::string> verticesVector(verticesSet.size());

   std::copy(verticesSet.begin(), verticesSet.end(), verticesVector.begin() ); // Copy set contents to vector

   Quicksort(ig, verticesVector, 0 , verticesVector.size()-1); // Vector is sorted in descending order according to degree

  
  std::vector <int > registersList; // Create vector of registers

   // Testing if allocation is impossible and therefore, and empty map is to be returned

      std:: string highestDegree = verticesVector[0]; // Retrieve the first element in vector

      int degreeValue = ig.degree(highestDegree); // Get degree of first element in the vector. This element has the highest degree

      if ( degreeValue >= num_registers) // Case with no solution
         {
            return {};

         }

 
  
  for ( int i = 1; i <= num_registers; i++)
 {
   registersList.push_back(i);
   

 }

     

  while ( !verticesVector.empty())
  {

    // Assign highest value the first available register
    // assign any vertex that is not a neighbor the same register
    // repeat until vector is empty

    
      int registerNumber = registersList[0]; // retreieve first number in vector which is first available register


      
      outputMap.insert( { verticesVector[0],registerNumber}); // set first vertex to first available register

      std:: string temp = verticesVector[0]; // temp variable to hold the value of the first string so it can be removed from vector

      

       verticesVector.erase(verticesVector.begin()); // remove first value in vector

       std:: unordered_set < std::string > vertexNeighbors; // set that will hold neighbors of each vertex given a register. These neighbors cannot be assigned the register

       
       std:: unordered_set <std::string > tempSet1; // temp set to hold returned neighbors

        tempSet1 = ig.neighbors(temp); // neighbors of first element are returned to temp set

        vertexNeighbors.insert(tempSet1.begin(), tempSet1.end()); // temp set now added to vertexNeighbors

      for ( int i = 0; i < verticesVector.size(); i++)
      
      {

         // Retreive all neighbors
         // Check if any of the neighors have been colored yet 
         // if yes, skip, 
         // if no, map to register
        
        auto it = vertexNeighbors.find(verticesVector[i]);
        

         if ( it == vertexNeighbors.end())
         //if (vertexNeighbors.find(verticesVector[i]) != vertexNeighbors.end()) // check if element is neighbor to a vertex with same register
         {
        
         

          outputMap.insert( { verticesVector[i], registerNumber}); // Assign vertex to register 

         //std:: unordered_set <std::string > tempSet2; // temp set to hold returned neighbors

         tempSet1 = ig.neighbors(verticesVector[i]); // neighbors of first element are returned to temp set
        
         
         vertexNeighbors.insert(tempSet1.begin(), tempSet1.end()); // temp set2 in now stored in the neighbor tracker

         
         verticesVector.erase(verticesVector.begin()); // remove first value in vector
          

         }
      

         
      }

         if ( !registersList.empty()) // stops seg fault
          {

         registersList.erase(registersList.begin()); // Delete the first element in register set, next loop will now utilize next register 
         
       

          
          }




  }




  

  return outputMap;
}