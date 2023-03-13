#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <algorithm>

class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T> class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex) noexcept;

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  // Private member variables here.
std:: unordered_map < std::string, std::list < std::string > > graph; // graph data structure


};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {





}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
  return {};
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
  return {};
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
  return 0;
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
  return 0;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) {

if (graph.count(v) == 0 || graph.count(w) == 0) // Check if both vertices exist
{
throw UnknownVertexException( "One or both of the vertices do not exist in the graph");
}


graph[v].push_back(w); // w is now a neighbor of v

graph[w].push_back(v); // v is now a neighbor of w


}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) {

auto * vPointer = std::find (graph[v].begin(), graph[v].end(), w); // check if value exists within each set

auto * wPointer = std::find (graph[w].begin(), graph[w].end(), v);


if ( graph.count(v) == 0 || graph.count(w) == 0) // Check if both vertices exist
{
  throw UnknownVertexException( "One or both of the vertices do not exist in the graph");
}


// find why its not working
/*
else if ( vPointer == graph[v].end() || wPointer == graph[w].end() ) // if the pointers point to their respective end(), edge does not exist
{
  throw UnknownEdgeException("Edge does not exist");
}
*/


// set what the pointers point to nothing

*(vPointer) = " " ; 

*(wPointer) = " ";


vPointer = nullptr; // set pointers to null
wPointer = nullptr;



}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept {

if (graph.count(vertex)) // Check if vertex is already within the graph
{
  return; 
}

graph[vertex] = std::list<std::string>(); // Creates an mapping between vertex and an empty list


}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
// Must remove all edges associated with it first
// then remove vertex


if (graph.count(vertex) == 0 ) // if vertex does not exist
{
throw UnknownVertexException ( "Vertex does not exist");

}

std:: string temp;


for ( int i = 0; i < graph[vertex].length(); i++ ) // is that valid syntax?
{

  


// loop thorugh the set
// at each position, go to that positions graph
// erase this vertex from it
// continue


}



}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const {
  return false;
}

template <typename T> unsigned InterferenceGraph<T>::degree(const T &v) const {
  return 0;
}

#endif
