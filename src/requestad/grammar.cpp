/*
Copyright (c) Members of the EGEE Collaboration. 2004.
See http://www.eu-egee.org/partners/ for details on the
copyright holders.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

///////////////////////////////////////////////////////////////
// Author: Simone Pellegrini
// Mail: simone.pellegrini@cnaf.infn.it
///////////////////////////////////////////////////////////////
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <stack>
#include "grammar.h"

#define BOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE
//#define BOOST_SPIRIT_ASSERT_EXCEPTION 

//#define DEBUG
#ifdef DEBUG
	#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/scoped_ptr.hpp>
#ifdef NEWBOOSTSPIRIT
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/attribute.hpp>
#include <boost/spirit/home/classic/actor/push_back_actor.hpp>
#include <boost/spirit/home/classic/error_handling/exceptions.hpp>
#include <boost/spirit/home/classic/utility/confix.hpp>
#else
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/error_handling/exceptions.hpp>
#include <boost/spirit/utility/confix.hpp>
#endif

using namespace std;
using namespace boost::spirit;


namespace glite {
namespace jdl {

////////////////////////////////////////////////////////////////////////////
//
//  Parser errors
//
////////////////////////////////////////////////////////////////////////////
enum Errors{
	attribute_expected,
	expr_expected,
	attrname_expected,
	semicolon_expected,
	colon_expected,
	right_quad_par_expected,
	right_round_par_expected,
	right_graph_par_expected,
	question_mark_expected,
	left_round_par_expected
};
	    
assertion<Errors> expect_attribute(attribute_expected);
assertion<Errors> expect_expr(expr_expected);
assertion<Errors> expect_attrname(attrname_expected);
assertion<Errors> expect_semicolon(semicolon_expected);
assertion<Errors> expect_colon(colon_expected);
assertion<Errors> expect_right_quad_par(right_quad_par_expected);
assertion<Errors> expect_right_round_par(right_round_par_expected);
assertion<Errors> expect_right_graph_par(right_graph_par_expected);
assertion<Errors> expect_question_mark(question_mark_expected);
assertion<Errors> expect_left_round_par(left_round_par_expected);

class semantic_error: public logic_error{
	public:
		semantic_error(string message, char const *end): logic_error(message), where(end){};
		char const *where;
};

#ifdef DEBUG
void print_activation_record(vector<string> *v){
	cout << "[";
	vector<string>::iterator it = v->begin();
	while(it != v->end()){
		cout << *(it++);
		if(it != v->end())
			cout << ", ";
	}
	cout << "]" << endl;
}
#endif

struct add_attribute_name
{
    add_attribute_name(stack<vector<string> *>& _defs)
    :  defs(_defs) {}

    void operator()(char const* begin, char const* end) const
    {
    	string attr(begin, end);
	#ifdef DEBUG
		cout << "Adding attribute: " << attr << endl;
	#endif
		if(defs.empty())
			defs.push(new vector<string>());
			
		if(find(defs.top()->begin(), defs.top()->end(), attr) != defs.top()->end())
			throw semantic_error("Attribute '" + attr + "' already defined!", begin);
		defs.top()->push_back(attr);
	#ifdef DEBUG
		print_activation_record(defs.top());
	#endif
    }
    stack<vector<string>* >& defs;
};

struct push_activation_record
{
    push_activation_record(stack<vector<string> *>& _defs)
    :  defs(_defs) {}

    void operator()(char const c) const
    {
	#ifdef DEBUG
		cout << "Push Activation record" << endl;
	#endif
		defs.push(new vector<string>());
    }
    stack<vector<string> *>& defs;
};

void pop(stack<vector<string> *>& defs){
#ifdef DEBUG
	cout << "POP Activation record" << endl;
#endif
	vector<string> *v = defs.top();
	defs.pop();
	delete v;
}

struct pop_activation_record
{
    pop_activation_record(stack<vector<string> *>& _defs)
    :  defs(_defs) {}

    void operator()(char const c) const
    {
		pop(defs);
    }
    void operator()(char const* begin, char const* end) const
    {
    	pop(defs);
    }
    stack<vector<string> *>& defs;
};

////////////////////////////////////////////////////////////////////////////
//
//  JDL grammar
//
////////////////////////////////////////////////////////////////////////////
struct jdl_grammar : public grammar<jdl_grammar>
{	
	jdl_grammar(stack<vector<string>* >& stack): defs(stack){ }
		
    template <typename ScannerT>
    struct definition
    {
    
        definition(jdl_grammar const& self)
        {
        	/*
        	 * def_list := (attribute_definition ';' | comment)+
             * 			   | record_expression ';'?
             */
        	def_list =
        		// A record '[', ']' delimited attribute definition list.
            	record_expression >> !ch_p(';')
	            |
	            // Attribute definition list
	            ( +( comment
	        		| ( expect_attribute(attribute_definition) >>
	        	 		expect_semicolon(ch_p(';')) )[pop_activation_record(self.defs)]
	               )
	            )
            	;

            comment =
            	comment_p("//")
            	|	comment_p("#")
            	;

            /*
             * expression := simple_expression '?' expression ':' expression
             * 			   | simple_expression
             */
            expression =
            	(simple_expression >>
            			ch_p('?') >>
            			expect_expr(expression) >>
            			expect_colon(ch_p(':')) >>
            			expect_expr(expression))
            	|	simple_expression
                ;

            /*
             * simple_expression := factor ( binary_op factor )*
             */
			simple_expression =
				factor >> *( binary_op >> factor )
				;

			/*
			 * factor := ('+' | '-' | '~' | '!') suffix_expr
			 * 			 | suffix_expr
             */
			factor =
				unary_op >> suffix_expr
                | 	suffix_expr
                ;

            binary_op =
				lexeme_d[
					longest_d[chseq_p("||")
					| "&&" | '|' | '&' | '^'
					| "==" | "!=" | "is" | "isnt"
					| '<' | '>' | "<=" | ">="
	  	  		 	| "<<" | ">>" | ">>>"
				  	| '+' | '-'	| '*' | '/' | '%']
	  	  	 	]
               	;

            unary_op =
            	lexeme_d[ch_p('+') | '-' | '~' |  '!' ]
            	;

            /*
             * suffix_expr := atom ('.' attribute_name | '[' expression ']')*
             */
           	suffix_expr =
  	  	 		atom >>
  	  	 			*( ch_p('.') >> expect_attrname(attribute_name)
  	  	 			|
  	  	 			ch_p('[') >> expect_expr(expression) >> expect_right_quad_par(ch_p(']')) )
  	  	 		;

            /*
             * atom := '(' expression ')'
             * 		 |  list_expression
             * 	     |  record_expression
             *       |  function_call
             *       |  literal
             *       |  attribute_name
             *       |  keywords
             */
            atom =
	  	  	 		( '(' >> expect_expr(expression) >> expect_right_round_par(ch_p(')')) )
	  	  	 		| list_expression
	  	  	 		| record_expression
	  	  	 		| function_call
	  	  	 		| literal
	  	  	 		| attribute_name
	  	  	 		| keywords
  	  	 		;

			keywords =
				lexeme_d[(chseq_p("error") | "false" | "true" | "undefined" | "parent")]
				;

			/*
			 * list_expression := '{' ( '}' | list_expr_list )
             */
			list_expression =
				ch_p('{') >>
					( ch_p('}')
					| list_expr_list)
				;

			/*
			 * list_expr_list := expression ( (',' list_expr_list) | '}' )
             */
			list_expr_list =
				expect_expr(expression) >>
					( ch_p(',') >> list_expr_list
					| expect_right_graph_par(ch_p('}')) )
				;

			/*
			 * record_expression := '[' ( ']' | attribute_def_list )
             */
			record_expression =
				ch_p('[')[ push_activation_record(self.defs) ] >>
					( attribute_def_list | ch_p(']')[pop_activation_record(self.defs)] )
				;

			/*
			 * attribute_def_list := comment (']' | attribute_def_list )
			 * 					   | attribute_definition ( ( ';'? comment* ']' ) | ';' attribute_def_list )
             */
			attribute_def_list =
				(comment >> (ch_p(']')[pop_activation_record(self.defs)] | attribute_def_list))
				|	expect_attribute(attribute_definition) >>
					( !ch_p(';') >> *comment >> ch_p(']')[pop_activation_record(self.defs)]
					| expect_semicolon(ch_p(';')) >> attribute_def_list)
				;

			/*
			 * attribute_definition := attribute_name '=' expression
             */
			attribute_definition =
				(attribute_name[add_attribute_name(self.defs)] >> ch_p('=') >> expect_expr(expression))
				;

			/*
			 * function_call := unquoted_name '(' ( expression ( ',' expression )* )? ')'
             */
			function_call =
				unquoted_name >>
				(	ch_p('(') >>
					!( expect_expr(expression) >>
						*( ch_p(',') >> expect_expr(expression) )
					) >> expect_right_round_par(ch_p(')'))
				)
				;

            /*
             * attribute_name := unquoted_name | quoted_name
             */
            attribute_name =
				(unquoted_name
				|	quoted_name)
				;

			/*
			 * literal := integer_literal | floating_point_literal | string_literal+
             */
			literal =
				floating_point_literal
  	  	 		|	integer_literal
  	  	 		|	/*+(*/ string_literal /*)*/
  	  	 		;

			/*
  	  	 	 * floating_point_literal := uint_p+ '.' uint_p* exponent?
  	  	 	 * 						   | '.' uint_p+ exponent?
  	  	 	 * 						   | uint_p+ exponent
  	  	 	 */
        	floating_point_literal =
  	  	 		+uint_p >> '.' >> *uint_p >>  !exponent
  	  	 	   	| '.' >> +uint_p  >> !exponent
  	  	 		| +uint_p >> exponent
  	  	 		;

  	  	 	/*
  	  	 	 * exponent := ('e' | 'E') ('+' | '-')? uint_p+
  	  	 	 */
  	  	 	exponent =
 	  	 		lexeme_d[( ch_p('e') | 'E' ) >> !( ch_p('+') | '-' ) >> +uint_p ]
  	  	 		;

			nonzero_digit =
				range_p('1','9')
				;

        	integer_literal	=
				nonzero_digit >> *uint_p >> !(ch_p('K') | 'M' | 'G' | 'T')
				| lexeme_d[ ('0' >> *oct_p >> !(ch_p('K') | 'M' | 'G' | 'T')) ]
  	  	 		| lexeme_d[ ('0' >> ( ch_p('x') |  'X' ) >> +hex_p >> !(ch_p('K') | 'M' | 'G' | 'T')) ]
  	  	 		;

			string_literal =
  	  	 		ch_p('\"') >> ( *( non_quote | '\'' ) ) >> '\"'
  	  	 		;

        	escaped_char =
  	  	 		lexeme_d[ch_p('n') | 't' | 'b' | 'r' | 'f' | '\\'  | '\"' | '\'']
  	  	 		;

        	non_quote =
 	  	 		('\\' >> escaped_char
  	  	 		| 	lexeme_d['\\' >> oct_p >> !oct_p]
  	  	 		| 	lexeme_d['\\' >> range_p('0','3') >> oct_p >> oct_p]
  	  	 		| 	~ch_p('\"'))
  	  	 		;

        	quoted_name =
				ch_p('\'') >> (+( non_quote | '\"' )) >> '\''
				;

        	unquoted_name =
 	  	 		(lexeme_d[( alpha_p | '_' ) >> *(  alpha_p  | uint_p  | '_' )])
 	  	 		- "error" - "true" - "false" - "undefined" - "parent"
  	  	 		;

			BOOST_SPIRIT_DEBUG_NODE(attribute_definition);
			BOOST_SPIRIT_DEBUG_NODE(attribute_def_list);
			BOOST_SPIRIT_DEBUG_NODE(function_call);
			BOOST_SPIRIT_DEBUG_NODE(list_expression);
			BOOST_SPIRIT_DEBUG_NODE(atom);
			BOOST_SPIRIT_DEBUG_NODE(suffix_expr);
			BOOST_SPIRIT_DEBUG_NODE(unary_op);
            BOOST_SPIRIT_DEBUG_NODE(factor);
            BOOST_SPIRIT_DEBUG_NODE(binary_op);
            BOOST_SPIRIT_DEBUG_NODE(simple_expression);
            BOOST_SPIRIT_DEBUG_NODE(expression);
            BOOST_SPIRIT_DEBUG_NODE(record_expression);
            BOOST_SPIRIT_DEBUG_NODE(comment);
            BOOST_SPIRIT_DEBUG_NODE(def_list);
            BOOST_SPIRIT_DEBUG_NODE(escaped_char);
			BOOST_SPIRIT_DEBUG_NODE(string_literal);
			BOOST_SPIRIT_DEBUG_NODE(letter);
			BOOST_SPIRIT_DEBUG_NODE(exponent);
			BOOST_SPIRIT_DEBUG_NODE(floating_point_literal);
			BOOST_SPIRIT_DEBUG_NODE(integer_literal);
			BOOST_SPIRIT_DEBUG_NODE(non_quote);
			BOOST_SPIRIT_DEBUG_NODE(quoted_name);
			BOOST_SPIRIT_DEBUG_NODE(unquoted_name);
			BOOST_SPIRIT_DEBUG_NODE(literal);
            BOOST_SPIRIT_DEBUG_NODE(binary_op);
            BOOST_SPIRIT_DEBUG_NODE(attribute_name);
        }

        rule<ScannerT> def_list, expression, simple_expression, factor,
        	atom, unary_op, suffix_expr, list_expr_list, list_expression,
        	record_expression, attribute_definition, function_call,
        	attribute_def_list, comment, term, binary_op,
        	keywords;

        rule<ScannerT>  attribute_name, literal, unquoted_name,
        	quoted_name, integer_literal, floating_point_literal, exponent,
        	string_literal, letter, escaped_char, non_quote, nonzero_digit;

        rule<ScannerT> const&
        start() const { return def_list; }

    };

    stack<vector<string> *> &defs;
};

pair<int, int> iter2RowCol(const string &str, const string &where){
	int rows = 1, cols = 1;
	string::const_iterator it = str.begin();
	string::const_iterator end = search(str.begin(), str.end(), where.begin(), where.end());
	while(it != end){
		if(*(it++) == '\n'){
			rows++;
			cols=0;
		}
		cols++;
	}
	return pair<int,int>(rows,cols);
}

jdl_parser::jdl_parser() {
	grammar.reset(new jdl_grammar(stack));
	#ifdef DEBUG
		BOOST_SPIRIT_DEBUG_NODE(grammar);
	#endif
}

jdl_parser::~jdl_parser(){ assert(stack.empty()); }

void jdl_parser::parseString(string jdl){
	try{
		boost::spirit::parse(jdl.c_str(),*grammar,space_p).full;
	}catch(parser_error<Errors, char const *> ex){
		cerr << "Syntax error occurred in your JDL file, please check the following row/column: " << endl;
		switch(ex.descriptor){
			case semicolon_expected:
				cerr << "';' expected at: ";
				break;
			case right_quad_par_expected:
				cerr << "']' expected at: ";
				break;
			case right_round_par_expected:
				cerr << "')' expected at: ";
				break;
			case right_graph_par_expected:
				cerr << "'}' expected at: ";
				break;
			case colon_expected:
				cerr << "':' expected at: ";
				break;
			case attribute_expected:
				cerr << "valid attribute expected at: ";
				break;
			default:
				cerr << "Error occured at: ";
		}
		pair<int,int> err_desc = iter2RowCol(jdl, ex.where);
		int charnum = err_desc.first + err_desc.second ;
		cerr << "Character number: " << charnum << endl ;
		cerr << "\" " << string(ex.where, ex.where+20) << " ... \"" << endl;
		exit(1);
	}catch(semantic_error e){
		cerr << e.what() << endl;
		pair<int,int> err_desc = iter2RowCol(jdl, e.where);
		int charnum = err_desc.first + err_desc.second ;
		cerr << "Character number: " << charnum << endl ;
		exit(1);
	}
}

void jdl_parser::parseFile(string file_name){
	string jdl = "" ;
	try{
		jdl = open_file(file_name);
		boost::spirit::parse(jdl.c_str(),*grammar,space_p).full;
	}catch(parser_error<Errors, char const *> ex){
		cerr << "Syntax error occurred in the JDL file: "<<file_name
				<<"\nPlease check your JDL at the following row/column: " << endl;
		switch(ex.descriptor){
			case semicolon_expected:
				cerr << "';' expected at: ";
				break;
			case right_quad_par_expected:
				cerr << "']' expected at: ";
				break;
			case right_round_par_expected:
				cerr << "')' expected at: ";
				break;
			case right_graph_par_expected:
				cerr << "'}' expected at: ";
				break;
			case colon_expected:
				cerr << "':' expected at: ";
				break;
			case attribute_expected:
				cerr << "valid attribute expected at: ";
				break;
			default:
				cerr << "Error occured at: ";
		}
		pair<int,int> err_desc = iter2RowCol(jdl, ex.where);
		cerr << "Row: " << err_desc.first  << ", Col: " << err_desc.second << endl;
		cerr << "\" " << string(ex.where, ex.where+20) << " ... \"" << endl;
		exit(1);
	}catch(semantic_error e){
		cerr << e.what() << endl;
		pair<int,int> err_desc = iter2RowCol(jdl, e.where);
		cerr << "Row: " << err_desc.first  << ", Col: " << err_desc.second << endl;
		exit(1);
	}
}


string jdl_parser::open_file(const string &file_name){
	std::ifstream jdl_file(file_name.c_str());
	std::string s;
	std::string jdl_def = "";
	while (std::getline(jdl_file, s))
		jdl_def += s + "\n";
	return jdl_def;
}

} //glite namespace
} //jdl namespace


