// Homework 4
// Testing Sorting Algorithms
// Afnan Ebrahim

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, 
			  chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}



// Generates and returns random vector of size @size_of_vector.
/*creates vector filled with random variables*/
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  // Add code
  vector<int> random = {};
  for(size_t i = 0; i< size_of_vector; i++ )
  {
    random.push_back(rand());
  }
  return random;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
/*if smaller to larger then just pushback 1...size of vector*/
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  // Add code
  vector<int> vect = {};
  int i=1;
  if(smaller_to_larger)
  {
    while(vect.size()!= size_of_vector)
    {
      vect.push_back(i);
      i++;
    }
    return vect;
  }
  else
  {
    i=size_of_vector;
    while(vect.size() != size_of_vector)
    {
      vect.push_back(i);
      i--;
    }
    return vect;
  }

}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
/*just compare current element to the one before and make sure it is either
the same or whatever the comparator says it is. if it doesnt follow comparator return 0
else return 1*/
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  // Add code
  for(size_t i=1; i<input.size(); i++)
  {
    if(!less_than(input[i-1], input[i]) && input[i-1]!= input[i])
    {
      return 0;
    }
  }
  return 1;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }


  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    // Generate random vector @input_vector.
    input_vector = GenerateRandomVector(input_size);

  } else {
    // Generate sorted vector @input_vector.
    if(comparison_type == "less")
    {
       input_vector = GenerateSortedVector(input_size, true);
    }
    else
    {
       input_vector = GenerateSortedVector(input_size, false);
    }
  }
  if(comparison_type == "less")
  { 
    vector<int> restore = input_vector;
    //CALL HEAPSORT
    cout<<"Heapsort"<<endl;
    const auto begin_time = chrono::high_resolution_clock::now();
    HeapSort(input_vector, less<int>{} );
    const auto end_time = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time, end_time) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MERGESORT
    cout<<"MergeSort"<<endl;
    const auto begin_time2 = chrono::high_resolution_clock::now();
    MergeSort(input_vector, less<int>{});
    const auto end_time2 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time2, end_time2) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL QUICKSORT
    cout<<"QuickSort"<<endl;
    const auto begin_time3 = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    const auto end_time3 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time3, end_time3) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;
    cout<<'\n';
    // Pivot implementations
    cout << "Testing Quicksort Pivot Implementations"<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MEDIAN OF THREE
    cout<<"Median of Three"<<endl;
    const auto begin_time4 = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    const auto end_time4 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time4, end_time4) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MIDDLE OF THREE
    cout<<"Middle"<<endl;
    const auto begin_time5 = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, less<int>{});
    const auto end_time5 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time5, end_time5) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL FIRST OF THREE
    cout<<"First"<<endl;
    const auto begin_time6 = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, less<int>{});
    const auto end_time6 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time6, end_time6) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, less<int>{})<< endl;

  }
  else  
  { 
    vector<int> restore = input_vector;
    //CALL HEAPSORT
    cout<<"Heapsort"<<endl;
    const auto begin_time1 = chrono::high_resolution_clock::now();
    HeapSort(input_vector, greater<int>{} );
    const auto end_time1 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time1, end_time1) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MERGESORT
    cout<<"MergeSort"<<endl;
    const auto begin_time2 = chrono::high_resolution_clock::now();
    MergeSort(input_vector, greater<int>{});
    const auto end_time2 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time2, end_time2) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL QUICKSORT
    cout<<"QuickSort"<<endl;
    const auto begin_time3 = chrono::high_resolution_clock::now();
    QuickSort(input_vector, greater<int>{});
    const auto end_time3 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time3, end_time3) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
    cout<<'\n';

    // Pivot implementations
    cout << "Testing Quicksort Pivot Implementations"<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MEDIAN OF THREE
    cout<<"Median of Three"<<endl;
    const auto begin_time4= chrono::high_resolution_clock::now();
    QuickSort(input_vector, greater<int>{});
    const auto end_time4 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time4, end_time4) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL MIDDLE OF THREE
    cout<<"Middle"<<endl;
    const auto begin_time5 = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, greater<int>{});
    const auto end_time5 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time5, end_time5) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
    cout<<'\n';

    //Restore Vector
    input_vector = restore;
    //CALL FIRST OF THREE
    cout<<"First"<<endl;
    const auto begin_time6 = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, greater<int>{});
    const auto end_time6 = chrono::high_resolution_clock::now();  
    cout<<"Runtime: "<< ComputeDuration(begin_time6, end_time6) << " ns" << endl;
    cout<<"Verified: "<< VerifyOrder(input_vector, greater<int>{})<< endl;
  }

  // Call HeapSort / MergeSort / QuickSort  using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for HeapSort & QuickSort

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for QuickSort2 & QuickSort3

}

int main(int argc, char **argv) {
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
