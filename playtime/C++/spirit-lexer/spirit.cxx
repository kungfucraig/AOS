// Copyright (c) 2012 Craig Wright (kungfucraig@gmail.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>

//
// This example uses boost spirit to parse a simple
// colon-delimited grammar.
//
// The grammar we want to recognize is:
//    identifier := [a-z]+
//    separator  := ':'
//    path       := (identifier separator path) | identifier
//
// From the boost spirit perspective this example shows
// a few things I found hard to come by when building my
// first parser.
//    1. How to flag an incomplete token at the end of input
//       as an error. (use of boost::spirit::eoi)
//    2. How to bind an action on an instance of an object
//       that is taken as input to the parser.
//    3. Use of std::wstring.
//
// Some of what was mentioned above was provided as answers to
// a stackoverflow question I asked on the 12th of October, 2012.
// See:
// http://stackoverflow.com/questions/12864978/boost-spirit-signals-successful-parsing-despite-token-being-incomplete
//

// This using directive will cause issues with boost::bind
// when referencing placeholders such as _1.
// using namespace boost::spirit;

//! A class that tokenizes our input.
template<typename Lexer>
struct Tokens : boost::spirit::lex::lexer<Lexer>
{
      Tokens()
      {
         identifier = L"[a-z]+";
         separator = L":";
        
         this->self.add
            (identifier)
            (separator)
            ;
      }
      boost::spirit::lex::token_def<std::wstring, wchar_t> identifier, separator;
};

//! This class provides a callback that echoes strings to stderr.
struct Echo
{
      void echo(boost::fusion::vector<std::wstring> const& t) const
      {
         using namespace boost::fusion;
         std::wcerr << at_c<0>(t) << "\n";
      }
};


//! The definition of our grammar, as described above.
template <typename Iterator>
struct Grammar : boost::spirit::qi::grammar<Iterator> 
{
      template <typename TokenDef>
      Grammar(TokenDef const& tok, Echo const& e)
         : Grammar::base_type(path)
      {
         using boost::spirit::_val;
         path
            = 
            ((token >> tok.separator >> path)[boost::bind(&Echo::echo, e,::_1)]
             |
             (token)[boost::bind(&Echo::echo, &e, ::_1)]
             ) >> boost::spirit::eoi; // Look for end of input.

          token 
             = (tok.identifier) [_val=boost::spirit::qi::_1]
          ;
          
      }
      boost::spirit::qi::rule<Iterator> path;
      boost::spirit::qi::rule<Iterator, std::wstring()> token;
};
 

int main()
{
   // A set of typedefs to make things a little clearer. This stuff is
   // well described in the boost spirit documentation/examples.
   typedef std::wstring::iterator BaseIteratorType;
   typedef boost::spirit::lex::lexertl::token<BaseIteratorType, boost::mpl::vector<std::wstring> > TokenType;
   typedef boost::spirit::lex::lexertl::lexer<TokenType> LexerType;
   typedef Tokens<LexerType>::iterator_type TokensIterator;
   typedef LexerType::iterator_type LexerIterator;

   // Define some paths to parse.
   typedef std::vector<std::wstring> Tests;
   Tests paths;
   paths.push_back(L"abc");
   paths.push_back(L"abc:xyz");
   paths.push_back(L"abc:xyz:");
   paths.push_back(L":");

   // Parse 'em.
   for ( Tests::iterator iter = paths.begin(); iter != paths.end(); ++iter )
   {
      std::wstring str = *iter;
      std::wcerr << L"*****" << str << L"*****\n";

      Echo e;
      Tokens<LexerType> tokens;
      Grammar<TokensIterator> grammar(tokens, e);
   
      BaseIteratorType first = str.begin();
      BaseIteratorType last = str.end();

      // Have the lexer consume our string.
      LexerIterator lexFirst = tokens.begin(first, last);
      LexerIterator lexLast = tokens.end();
   
      // Have the parser consume the output of the lexer.
      bool r = boost::spirit::qi::parse(lexFirst, lexLast, grammar);

      // Print the status and whether or note all output of the lexer 
      // was processed.
      std::wcerr << r << L" " << (lexFirst==lexLast) << L"\n";
   }
}
