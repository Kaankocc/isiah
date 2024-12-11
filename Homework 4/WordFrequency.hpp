#ifndef WORD_FREQUENCY_HPP
#define WORD_FREQUENCY_HPP

///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives

/////////////////////// END-TO-DO (1) ////////////////////////////




template<typename Hasher = std::hash<std::string>>
class WordFrequency
{
  public:
    // Construction and assignment
    WordFrequency( std::istream & iStream = std::cin );                 // (default) constructor, add words from file to hash table


    // Accessors, Queries, and Observers
    std::size_t numberOfWords    (                       ) const;       // returns the number of unique words
    std::size_t wordCount        ( std::string_view word ) const;       // returns the number of occurrences of the given word
    std::string mostFrequentWord (                       ) const;       // returns the most frequent word
    std::size_t maxBucketSize    (                       ) const;       // returns the size of the largest bucket in the hash table
    double      bucketSizeAverage(                       ) const;       // returns the average number of elements per bucket


  private:
    // Instance Attributes - See requirements
    ///////////////////////// TO-DO (2) //////////////////////////////
      /// The class should have a single instance attribute of type std::unordered_map, which is the C++ Standard Library's
      /// implementation of a hash table, to store the association of words (key) to the number of times a word occurs (value). Be
      /// sure to provide all three types when defining the std::unordered_map, including setting std::unordered_map's third
      /// argument to Hasher (WordFrequency's template parameter).

    /////////////////////// END-TO-DO (2) ////////////////////////////
};




#include "WordFrequency.hxx"



#endif    // WORD_FREQUENCY_HPP
