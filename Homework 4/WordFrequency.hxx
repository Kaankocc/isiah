#ifndef WORD_FREQUENCY_HXX
#define WORD_FREQUENCY_HXX

///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
  #include <istream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <sstream> // Required for std::istringstream
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( std::string_view word )
  {
    constexpr char bad_char[] = " \t\r\n\b\v_-\"'(){}+/*,=.!?:;";                     // leading and trailing characters to be removed
    static std::locale locality{ "en_GB.UTF-8" };

    auto startIndex = word.find_first_not_of( bad_char );                             // start with the first non-bad character
    if( startIndex == std::string_view::npos ) startIndex = word.size();              // if the word contains only bad characters ...

    std::size_t count    = 0;                                                         // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );                         // end with the first non-bad character

    if( endIndex != std::string_view::npos ) count = endIndex - startIndex + 1;       // number of characters to use in results

    std::string result{ word.substr( startIndex, count ) };                           // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );                         // convert to lower case

    return result;                                                                    // result is moved optimized (copy elision) to the caller, std::move( result ) not required
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
template<typename Hasher>
WordFrequency<Hasher>::WordFrequency(std::istream & iStream)
{
   std::string word;

    while (iStream >> word)
    {
        if (word == "--")
        {
            ++wordFrequencyMap[word]; // Treat "--" as a valid word
            continue;
        }

        std::string sanitizedWord = sanitize(word); // Sanitize the word

        if (!sanitizedWord.empty())
        {
            ++wordFrequencyMap[sanitizedWord];
        }
        else
        {
            std::cerr << "Skipped word (sanitized to empty): \"" << word << "\"\n";
        }
    }
}

/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////

template<typename Hasher>
std::size_t WordFrequency<Hasher>::numberOfWords() const
{
    return wordFrequencyMap.size(); // Return the number of unique keys in the hash table
}

/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////

template<typename Hasher>
std::size_t WordFrequency<Hasher>::wordCount(const std::string_view word) const
{
    std::string sanitizedWord = sanitize(word); // Sanitize the input word

    auto it = wordFrequencyMap.find(sanitizedWord); // Search for the sanitized word in the hash table
    if (it != wordFrequencyMap.end())
    {
        return it->second; // Word found, return its frequency
    }
    return 0; // Word not found, return 0
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////

template<typename Hasher>
std::string WordFrequency<Hasher>::mostFrequentWord() const
{
    // Return an empty string if the hash table is empty
    if (wordFrequencyMap.empty()) 
    {
        return ""; 
    }

    // Iterate through the hash table to find the most frequent word
    auto maxElement = std::max_element(
        wordFrequencyMap.begin(), wordFrequencyMap.end(),
        [](const auto &a, const auto &b) {
            return a.second < b.second; // Compare word frequencies
        });

    return maxElement->first; // Return the word with the highest frequency
}

/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map

  template<typename Hasher>
std::size_t WordFrequency<Hasher>::maxBucketSize() const
{
    std::size_t maxSize = 0;

    // Iterate through all buckets in the hash table
    for (std::size_t i = 0; i < wordFrequencyMap.bucket_count(); ++i)
    {
        maxSize = std::max(maxSize, wordFrequencyMap.bucket_size(i)); // Get the size of each bucket
    }

    return maxSize; // Return the size of the largest bucket
}

/////////////////////// END-TO-DO (6) ////////////////////////////







// Implement WordFrequency::bucketSizeAverage() const - See requirements
///////////////////////// TO-DO (7) //////////////////////////////

template<typename Hasher>
double WordFrequency<Hasher>::bucketSizeAverage() const
{
    // If there are no buckets, the average is zero.
    if (wordFrequencyMap.bucket_count() == 0)
    {
        return 0.0;
    }

    // Calculate the average number of elements per bucket
    return static_cast<double>(wordFrequencyMap.size()) / static_cast<double>(wordFrequencyMap.bucket_count());

}
/////////////////////// END-TO-DO (7) ////////////////////////////




#endif    // WORD_FREQUENCY_HXX
