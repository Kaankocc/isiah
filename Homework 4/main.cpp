///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives

/////////////////////// END-TO-DO (1) ////////////////////////////


// unnamed, anonymous namespace providing non-member private working area
namespace
{
  struct ChangeEpsilon_RAII
  {
    ChangeEpsilon_RAII( Regression::CheckResults & checker, double newEpsilon ) : _epsilon( checker.EPSILON ), _checker( checker ) { _checker.EPSILON = newEpsilon; }
   ~ChangeEpsilon_RAII(                                                       )                                                    { _checker.EPSILON = _epsilon;   }

    const double               _epsilon;
    Regression::CheckResults & _checker;
  };






  struct MyCustomHasher
  {
    // Implement operator()( const std::string & ) const noexcept - See requirements
    std::size_t operator()( const std::string & key ) const noexcept
    {
      ///////////////////////// TO-DO (2) //////////////////////////////

      /////////////////////// END-TO-DO (2) ////////////////////////////
    }
  };
}






int main()
{
  Regression::CheckResults affirm( std::cout );
  affirm.policy = Regression::CheckResults::ReportingPolicy::ALL;
  std::cout << std::boolalpha;
  unsigned testNumber = 0;


  // Test set 1 - Frankenstein
  {
    std::cout << ++testNumber << ".  Test results for:  \"Frankenstein or The Modern Prometheus by Mary Shelley.txt\"\n\n";

    std::ifstream fin( "Frankenstein or The Modern Prometheus by Mary Shelley.txt" );
    affirm.is_true( "Find and open \"Frankenstein or The Modern Prometheus by Mary Shelley.txt\"", fin.is_open() );

    WordFrequency<> frankenstein( fin );
    affirm.is_equal( "numberOfWords           ",   7'195u, frankenstein.numberOfWords()                   );
    affirm.is_equal( "wordCount: Frankenstein ",      24u, frankenstein.wordCount( "Frankenstein"       ) );
    affirm.is_equal( "wordCount: feared       ",      13u, frankenstein.wordCount( "feared"             ) );
    affirm.is_equal( "wordCount: the          ",   4'187u, frankenstein.wordCount( "the"                ) );
    affirm.is_equal( "wordCount: life         ",     114u, frankenstein.wordCount( "life"               ) );
    affirm.is_equal( "wordCount: nonexistent  ",       0u, frankenstein.wordCount( "non-existent-!word" ) );
    affirm.is_equal( "mostFrequentWord        ",    "the", frankenstein.mostFrequentWord()                );

    // Temporarily widen the acceptable range allowing a little wiggle room for different library implementations
    {
      ChangeEpsilon_RAII changeEpsilon( affirm, 0.075 );
      affirm.is_equal( "average bucket size:    ", 0.63, frankenstein.bucketSizeAverage() );
    }

    std::size_t size = frankenstein.maxBucketSize();
    affirm.is_equal( "maxBucketSize:          ", (size - 5 <= 2 ? size : 6u ), size);           // expecting 5, 6, or 7 to allow a little wiggle room for different library implementations
                                                                                                // Programming note: intentionally using unsigned subtraction allowing negative number to wrap
                                                                                                // around to become very large positive numbers
  }

  std::cout << "\n\n";






  // Test set 2 - Frankenstein with custom hasher
  {
    std::cout << ++testNumber << ".  Test results for:  \"Frankenstein or The Modern Prometheus by Mary Shelley.txt\" using custom hasher\n\n";

    std::ifstream fin( "Frankenstein or The Modern Prometheus by Mary Shelley.txt" );
    affirm.is_true( "Find and open \"Frankenstein or The Modern Prometheus by Mary Shelley.txt\"", fin.is_open() );

    WordFrequency<MyCustomHasher> frankenstein( fin );
    affirm.is_equal       ( "numberOfWords           ",   7'195u, frankenstein.numberOfWords()                   );
    affirm.is_equal       ( "wordCount: Frankenstein ",      24u, frankenstein.wordCount( "Frankenstein"       ) );
    affirm.is_equal       ( "wordCount: feared       ",      13u, frankenstein.wordCount( "feared"             ) );
    affirm.is_equal       ( "wordCount: the          ",   4'187u, frankenstein.wordCount( "the"                ) );
    affirm.is_equal       ( "wordCount: life         ",     114u, frankenstein.wordCount( "life"               ) );
    affirm.is_equal       ( "wordCount: nonexistent  ",       0u, frankenstein.wordCount( "non-existent-!word" ) );
    affirm.is_equal       ( "mostFrequentWord        ",    "the", frankenstein.mostFrequentWord()                );
    affirm.is_greater_than( "average bucket size:    ",      1.0, frankenstein.bucketSizeAverage()               );
    affirm.is_greater_than( "maxBucketSize:          ",      10u, frankenstein.maxBucketSize()                   );
  }

  std::cout << "\n\n";






  // Test set 3 - Sleepy Hollow
  {
    std::cout << ++testNumber << ".  Test results for:  \"The Legend of Sleepy Hollow by Washington Irving.txt\"\n\n";

    WordFrequency<> sleepyHollow;
    affirm.is_equal( "numberOfWords           ",  3'231u, sleepyHollow.numberOfWords()                   );
    affirm.is_equal( "wordCount: Ichabod      ",     45u, sleepyHollow.wordCount( "Ichabod"            ) );
    affirm.is_equal( "wordCount: the          ",    917u, sleepyHollow.wordCount( "the"                ) );
    affirm.is_equal( "wordCount: nonexistent  ",      0u, sleepyHollow.wordCount( "non-existent-!word" ) );
    affirm.is_equal( "mostFrequentWord        ",   "the", sleepyHollow.mostFrequentWord()                );

    // Temporarily widen the acceptable range allowing a little wiggle room for different library implementations
    {
      ChangeEpsilon_RAII changeEpsilon( affirm, 0.067 );
      affirm.is_equal( "average bucket size     ", 0.57, sleepyHollow.bucketSizeAverage() );
    }

    std::size_t size = sleepyHollow.maxBucketSize();
    affirm.is_equal( "maxBucketSize           ", ( size - 4 <= 2 ? size : 5u ), size );         // expecting 4, 5, or 6 to allow a little wiggle room for different library implementations
                                                                                                // Programming note: intentionally using unsigned subtraction allowing negative number to wrap
                                                                                                // around to become very large positive numbers
  }

  std::cout << "\n\n";






  // Test set 4 - Hunger Games
  {
    std::cout << ++testNumber << ".  Test results for:  \"The Hunger Games by Suzanne Collins.txt\"\n\n";

    std::ifstream fin( "The Hunger Games by Suzanne Collins.txt" );
    affirm.is_true( "Find and open \"The Hunger Games by Suzanne Collins.txt\"", ! fin.is_open() );

    WordFrequency<> hungerGames;
    affirm.is_equal( "numberOfWords           ",   0u, hungerGames.numberOfWords()                   );
    affirm.is_equal( "wordCount: the          ",   0u, hungerGames.wordCount( "the"                ) );
    affirm.is_equal( "wordCount: nonexistent  ",   0u, hungerGames.wordCount( "non-existent-!word" ) );
    affirm.is_equal( "mostFrequentWord        ",   "", hungerGames.mostFrequentWord()                );
    affirm.is_equal( "average bucket size     ",  0.0, hungerGames.bucketSizeAverage()               );
    affirm.is_equal( "maxBucketSize           ",   0u, hungerGames.maxBucketSize()                   );
  }

  std::cout << "\n\n";






  // Test set 5 - Object Size
  std::cout << ++testNumber << ".  Test results for:  \"Word Frequency Object Size\"\n\n";
  affirm.is_equal( "Word Frequency Object Size", sizeof( std::unordered_map<std::string, std::size_t> ), sizeof( WordFrequency<> ) );






  std::cout << "\n\n\n"
            << affirm << '\n';
  return 0;
}
