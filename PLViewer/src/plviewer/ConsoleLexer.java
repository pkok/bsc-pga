// $ANTLR 3.4 src/plviewer/Console.g 2012-05-29 17:07:43

package plviewer;


import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked"})
public class ConsoleLexer extends Lexer {
    public static final int EOF=-1;
    public static final int APPLY=4;
    public static final int ASSIGN=5;
    public static final int CHARACTER=6;
    public static final int COMMA=7;
    public static final int CONST=8;
    public static final int CONSTANT=9;
    public static final int DIGIT=10;
    public static final int DISPLAY=11;
    public static final int DIV=12;
    public static final int DOT=13;
    public static final int EXPONENT=14;
    public static final int FUNC=15;
    public static final int LPAREN=16;
    public static final int MINUS=17;
    public static final int MULT=18;
    public static final int NAME=19;
    public static final int NEGATE=20;
    public static final int NEWLINE=21;
    public static final int NIL=22;
    public static final int NODISPLAY=23;
    public static final int NUMBER=24;
    public static final int PLUS=25;
    public static final int REVERSE=26;
    public static final int RPAREN=27;
    public static final int SEMICOLON=28;
    public static final int VAR=29;
    public static final int WEDGE=30;
    public static final int WHITESPACE=31;

    // delegates
    // delegators
    public Lexer[] getDelegates() {
        return new Lexer[] {};
    }

    public ConsoleLexer() {} 
    public ConsoleLexer(CharStream input) {
        this(input, new RecognizerSharedState());
    }
    public ConsoleLexer(CharStream input, RecognizerSharedState state) {
        super(input,state);
    }
    public String getGrammarFileName() { return "src/plviewer/Console.g"; }

    // $ANTLR start "COMMA"
    public final void mCOMMA() throws RecognitionException {
        try {
            int _type = COMMA;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:140:11: ( ',' )
            // src/plviewer/Console.g:140:13: ','
            {
            match(','); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "COMMA"

    // $ANTLR start "SEMICOLON"
    public final void mSEMICOLON() throws RecognitionException {
        try {
            int _type = SEMICOLON;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:141:11: ( ';' )
            // src/plviewer/Console.g:141:13: ';'
            {
            match(';'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "SEMICOLON"

    // $ANTLR start "ASSIGN"
    public final void mASSIGN() throws RecognitionException {
        try {
            int _type = ASSIGN;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:142:11: ( '=' )
            // src/plviewer/Console.g:142:13: '='
            {
            match('='); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "ASSIGN"

    // $ANTLR start "PLUS"
    public final void mPLUS() throws RecognitionException {
        try {
            int _type = PLUS;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:143:11: ( '+' )
            // src/plviewer/Console.g:143:13: '+'
            {
            match('+'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "PLUS"

    // $ANTLR start "MINUS"
    public final void mMINUS() throws RecognitionException {
        try {
            int _type = MINUS;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:144:11: ( '-' )
            // src/plviewer/Console.g:144:13: '-'
            {
            match('-'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "MINUS"

    // $ANTLR start "MULT"
    public final void mMULT() throws RecognitionException {
        try {
            int _type = MULT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:145:11: ( '*' )
            // src/plviewer/Console.g:145:13: '*'
            {
            match('*'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "MULT"

    // $ANTLR start "DIV"
    public final void mDIV() throws RecognitionException {
        try {
            int _type = DIV;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:146:11: ( '/' )
            // src/plviewer/Console.g:146:13: '/'
            {
            match('/'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "DIV"

    // $ANTLR start "DOT"
    public final void mDOT() throws RecognitionException {
        try {
            int _type = DOT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:147:11: ( '.' )
            // src/plviewer/Console.g:147:13: '.'
            {
            match('.'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "DOT"

    // $ANTLR start "WEDGE"
    public final void mWEDGE() throws RecognitionException {
        try {
            int _type = WEDGE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:148:11: ( '^' )
            // src/plviewer/Console.g:148:13: '^'
            {
            match('^'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "WEDGE"

    // $ANTLR start "NEGATE"
    public final void mNEGATE() throws RecognitionException {
        try {
            int _type = NEGATE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:149:11: ( '!' )
            // src/plviewer/Console.g:149:13: '!'
            {
            match('!'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "NEGATE"

    // $ANTLR start "REVERSE"
    public final void mREVERSE() throws RecognitionException {
        try {
            int _type = REVERSE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:150:11: ( '~' )
            // src/plviewer/Console.g:150:13: '~'
            {
            match('~'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "REVERSE"

    // $ANTLR start "RPAREN"
    public final void mRPAREN() throws RecognitionException {
        try {
            int _type = RPAREN;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:151:11: ( ')' )
            // src/plviewer/Console.g:151:13: ')'
            {
            match(')'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "RPAREN"

    // $ANTLR start "LPAREN"
    public final void mLPAREN() throws RecognitionException {
        try {
            int _type = LPAREN;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:152:11: ( '(' )
            // src/plviewer/Console.g:152:13: '('
            {
            match('('); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "LPAREN"

    // $ANTLR start "NEWLINE"
    public final void mNEWLINE() throws RecognitionException {
        try {
            int _type = NEWLINE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:154:9: ( ( ( '\\r' )? '\\n' ) )
            // src/plviewer/Console.g:154:11: ( ( '\\r' )? '\\n' )
            {
            // src/plviewer/Console.g:154:11: ( ( '\\r' )? '\\n' )
            // src/plviewer/Console.g:154:12: ( '\\r' )? '\\n'
            {
            // src/plviewer/Console.g:154:12: ( '\\r' )?
            int alt1=2;
            int LA1_0 = input.LA(1);

            if ( (LA1_0=='\r') ) {
                alt1=1;
            }
            switch (alt1) {
                case 1 :
                    // src/plviewer/Console.g:154:12: '\\r'
                    {
                    match('\r'); 

                    }
                    break;

            }


            match('\n'); 

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "NEWLINE"

    // $ANTLR start "WHITESPACE"
    public final void mWHITESPACE() throws RecognitionException {
        try {
            int _type = WHITESPACE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:156:12: ( ( '\\t' | ' ' | '\\n' | '\\r' | '\\u000C' )+ )
            // src/plviewer/Console.g:156:14: ( '\\t' | ' ' | '\\n' | '\\r' | '\\u000C' )+
            {
            // src/plviewer/Console.g:156:14: ( '\\t' | ' ' | '\\n' | '\\r' | '\\u000C' )+
            int cnt2=0;
            loop2:
            do {
                int alt2=2;
                int LA2_0 = input.LA(1);

                if ( ((LA2_0 >= '\t' && LA2_0 <= '\n')||(LA2_0 >= '\f' && LA2_0 <= '\r')||LA2_0==' ') ) {
                    alt2=1;
                }


                switch (alt2) {
            	case 1 :
            	    // src/plviewer/Console.g:
            	    {
            	    if ( (input.LA(1) >= '\t' && input.LA(1) <= '\n')||(input.LA(1) >= '\f' && input.LA(1) <= '\r')||input.LA(1)==' ' ) {
            	        input.consume();
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;
            	    }


            	    }
            	    break;

            	default :
            	    if ( cnt2 >= 1 ) break loop2;
                        EarlyExitException eee =
                            new EarlyExitException(2, input);
                        throw eee;
                }
                cnt2++;
            } while (true);


             _channel = HIDDEN; 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "WHITESPACE"

    // $ANTLR start "CONSTANT"
    public final void mCONSTANT() throws RecognitionException {
        try {
            int _type = CONSTANT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:158:10: ( 'e01' | 'e02' | 'e03' | 'e12' | 'e23' | 'e31' )
            int alt3=6;
            int LA3_0 = input.LA(1);

            if ( (LA3_0=='e') ) {
                switch ( input.LA(2) ) {
                case '0':
                    {
                    switch ( input.LA(3) ) {
                    case '1':
                        {
                        alt3=1;
                        }
                        break;
                    case '2':
                        {
                        alt3=2;
                        }
                        break;
                    case '3':
                        {
                        alt3=3;
                        }
                        break;
                    default:
                        NoViableAltException nvae =
                            new NoViableAltException("", 3, 2, input);

                        throw nvae;

                    }

                    }
                    break;
                case '1':
                    {
                    alt3=4;
                    }
                    break;
                case '2':
                    {
                    alt3=5;
                    }
                    break;
                case '3':
                    {
                    alt3=6;
                    }
                    break;
                default:
                    NoViableAltException nvae =
                        new NoViableAltException("", 3, 1, input);

                    throw nvae;

                }

            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 3, 0, input);

                throw nvae;

            }
            switch (alt3) {
                case 1 :
                    // src/plviewer/Console.g:158:12: 'e01'
                    {
                    match("e01"); 



                    }
                    break;
                case 2 :
                    // src/plviewer/Console.g:158:20: 'e02'
                    {
                    match("e02"); 



                    }
                    break;
                case 3 :
                    // src/plviewer/Console.g:158:28: 'e03'
                    {
                    match("e03"); 



                    }
                    break;
                case 4 :
                    // src/plviewer/Console.g:158:36: 'e12'
                    {
                    match("e12"); 



                    }
                    break;
                case 5 :
                    // src/plviewer/Console.g:158:44: 'e23'
                    {
                    match("e23"); 



                    }
                    break;
                case 6 :
                    // src/plviewer/Console.g:158:52: 'e31'
                    {
                    match("e31"); 



                    }
                    break;

            }
            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "CONSTANT"

    // $ANTLR start "NAME"
    public final void mNAME() throws RecognitionException {
        try {
            int _type = NAME;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:160:6: ( CHARACTER ( CHARACTER | DIGIT )* )
            // src/plviewer/Console.g:160:8: CHARACTER ( CHARACTER | DIGIT )*
            {
            mCHARACTER(); 


            // src/plviewer/Console.g:160:18: ( CHARACTER | DIGIT )*
            loop4:
            do {
                int alt4=2;
                int LA4_0 = input.LA(1);

                if ( ((LA4_0 >= '0' && LA4_0 <= '9')||(LA4_0 >= 'A' && LA4_0 <= 'Z')||LA4_0=='_'||(LA4_0 >= 'a' && LA4_0 <= 'z')) ) {
                    alt4=1;
                }


                switch (alt4) {
            	case 1 :
            	    // src/plviewer/Console.g:
            	    {
            	    if ( (input.LA(1) >= '0' && input.LA(1) <= '9')||(input.LA(1) >= 'A' && input.LA(1) <= 'Z')||input.LA(1)=='_'||(input.LA(1) >= 'a' && input.LA(1) <= 'z') ) {
            	        input.consume();
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;
            	    }


            	    }
            	    break;

            	default :
            	    break loop4;
                }
            } while (true);


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "NAME"

    // $ANTLR start "NUMBER"
    public final void mNUMBER() throws RecognitionException {
        try {
            int _type = NUMBER;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // src/plviewer/Console.g:162:8: ( ( PLUS | MINUS )? ( DIGIT )+ ( '.' ( DIGIT )* )? ( EXPONENT )? )
            // src/plviewer/Console.g:162:10: ( PLUS | MINUS )? ( DIGIT )+ ( '.' ( DIGIT )* )? ( EXPONENT )?
            {
            // src/plviewer/Console.g:162:10: ( PLUS | MINUS )?
            int alt5=2;
            int LA5_0 = input.LA(1);

            if ( (LA5_0=='+'||LA5_0=='-') ) {
                alt5=1;
            }
            switch (alt5) {
                case 1 :
                    // src/plviewer/Console.g:
                    {
                    if ( input.LA(1)=='+'||input.LA(1)=='-' ) {
                        input.consume();
                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;
                    }


                    }
                    break;

            }


            // src/plviewer/Console.g:162:26: ( DIGIT )+
            int cnt6=0;
            loop6:
            do {
                int alt6=2;
                int LA6_0 = input.LA(1);

                if ( ((LA6_0 >= '0' && LA6_0 <= '9')) ) {
                    alt6=1;
                }


                switch (alt6) {
            	case 1 :
            	    // src/plviewer/Console.g:
            	    {
            	    if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
            	        input.consume();
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;
            	    }


            	    }
            	    break;

            	default :
            	    if ( cnt6 >= 1 ) break loop6;
                        EarlyExitException eee =
                            new EarlyExitException(6, input);
                        throw eee;
                }
                cnt6++;
            } while (true);


            // src/plviewer/Console.g:162:33: ( '.' ( DIGIT )* )?
            int alt8=2;
            int LA8_0 = input.LA(1);

            if ( (LA8_0=='.') ) {
                alt8=1;
            }
            switch (alt8) {
                case 1 :
                    // src/plviewer/Console.g:162:34: '.' ( DIGIT )*
                    {
                    match('.'); 

                    // src/plviewer/Console.g:162:38: ( DIGIT )*
                    loop7:
                    do {
                        int alt7=2;
                        int LA7_0 = input.LA(1);

                        if ( ((LA7_0 >= '0' && LA7_0 <= '9')) ) {
                            alt7=1;
                        }


                        switch (alt7) {
                    	case 1 :
                    	    // src/plviewer/Console.g:
                    	    {
                    	    if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
                    	        input.consume();
                    	    }
                    	    else {
                    	        MismatchedSetException mse = new MismatchedSetException(null,input);
                    	        recover(mse);
                    	        throw mse;
                    	    }


                    	    }
                    	    break;

                    	default :
                    	    break loop7;
                        }
                    } while (true);


                    }
                    break;

            }


            // src/plviewer/Console.g:162:47: ( EXPONENT )?
            int alt9=2;
            int LA9_0 = input.LA(1);

            if ( (LA9_0=='E'||LA9_0=='e') ) {
                alt9=1;
            }
            switch (alt9) {
                case 1 :
                    // src/plviewer/Console.g:162:47: EXPONENT
                    {
                    mEXPONENT(); 


                    }
                    break;

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "NUMBER"

    // $ANTLR start "EXPONENT"
    public final void mEXPONENT() throws RecognitionException {
        try {
            // src/plviewer/Console.g:164:19: ( ( 'e' | 'E' ) ( PLUS | MINUS )? ( DIGIT )+ )
            // src/plviewer/Console.g:164:21: ( 'e' | 'E' ) ( PLUS | MINUS )? ( DIGIT )+
            {
            if ( input.LA(1)=='E'||input.LA(1)=='e' ) {
                input.consume();
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;
            }


            // src/plviewer/Console.g:164:31: ( PLUS | MINUS )?
            int alt10=2;
            int LA10_0 = input.LA(1);

            if ( (LA10_0=='+'||LA10_0=='-') ) {
                alt10=1;
            }
            switch (alt10) {
                case 1 :
                    // src/plviewer/Console.g:
                    {
                    if ( input.LA(1)=='+'||input.LA(1)=='-' ) {
                        input.consume();
                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;
                    }


                    }
                    break;

            }


            // src/plviewer/Console.g:164:47: ( DIGIT )+
            int cnt11=0;
            loop11:
            do {
                int alt11=2;
                int LA11_0 = input.LA(1);

                if ( ((LA11_0 >= '0' && LA11_0 <= '9')) ) {
                    alt11=1;
                }


                switch (alt11) {
            	case 1 :
            	    // src/plviewer/Console.g:
            	    {
            	    if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
            	        input.consume();
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;
            	    }


            	    }
            	    break;

            	default :
            	    if ( cnt11 >= 1 ) break loop11;
                        EarlyExitException eee =
                            new EarlyExitException(11, input);
                        throw eee;
                }
                cnt11++;
            } while (true);


            }


        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "EXPONENT"

    // $ANTLR start "CHARACTER"
    public final void mCHARACTER() throws RecognitionException {
        try {
            // src/plviewer/Console.g:166:20: ( ( 'a' .. 'z' | 'A' .. 'Z' | '_' ) )
            // src/plviewer/Console.g:
            {
            if ( (input.LA(1) >= 'A' && input.LA(1) <= 'Z')||input.LA(1)=='_'||(input.LA(1) >= 'a' && input.LA(1) <= 'z') ) {
                input.consume();
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;
            }


            }


        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "CHARACTER"

    // $ANTLR start "DIGIT"
    public final void mDIGIT() throws RecognitionException {
        try {
            // src/plviewer/Console.g:168:16: ( '0' .. '9' )
            // src/plviewer/Console.g:
            {
            if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
                input.consume();
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;
            }


            }


        }
        finally {
        	// do for sure before leaving
        }
    }
    // $ANTLR end "DIGIT"

    public void mTokens() throws RecognitionException {
        // src/plviewer/Console.g:1:8: ( COMMA | SEMICOLON | ASSIGN | PLUS | MINUS | MULT | DIV | DOT | WEDGE | NEGATE | REVERSE | RPAREN | LPAREN | NEWLINE | WHITESPACE | CONSTANT | NAME | NUMBER )
        int alt12=18;
        switch ( input.LA(1) ) {
        case ',':
            {
            alt12=1;
            }
            break;
        case ';':
            {
            alt12=2;
            }
            break;
        case '=':
            {
            alt12=3;
            }
            break;
        case '+':
            {
            int LA12_4 = input.LA(2);

            if ( ((LA12_4 >= '0' && LA12_4 <= '9')) ) {
                alt12=18;
            }
            else {
                alt12=4;
            }
            }
            break;
        case '-':
            {
            int LA12_5 = input.LA(2);

            if ( ((LA12_5 >= '0' && LA12_5 <= '9')) ) {
                alt12=18;
            }
            else {
                alt12=5;
            }
            }
            break;
        case '*':
            {
            alt12=6;
            }
            break;
        case '/':
            {
            alt12=7;
            }
            break;
        case '.':
            {
            alt12=8;
            }
            break;
        case '^':
            {
            alt12=9;
            }
            break;
        case '!':
            {
            alt12=10;
            }
            break;
        case '~':
            {
            alt12=11;
            }
            break;
        case ')':
            {
            alt12=12;
            }
            break;
        case '(':
            {
            alt12=13;
            }
            break;
        case '\r':
            {
            int LA12_14 = input.LA(2);

            if ( (LA12_14=='\n') ) {
                int LA12_15 = input.LA(3);

                if ( ((LA12_15 >= '\t' && LA12_15 <= '\n')||(LA12_15 >= '\f' && LA12_15 <= '\r')||LA12_15==' ') ) {
                    alt12=15;
                }
                else {
                    alt12=14;
                }
            }
            else {
                alt12=15;
            }
            }
            break;
        case '\n':
            {
            int LA12_15 = input.LA(2);

            if ( ((LA12_15 >= '\t' && LA12_15 <= '\n')||(LA12_15 >= '\f' && LA12_15 <= '\r')||LA12_15==' ') ) {
                alt12=15;
            }
            else {
                alt12=14;
            }
            }
            break;
        case '\t':
        case '\f':
        case ' ':
            {
            alt12=15;
            }
            break;
        case 'e':
            {
            switch ( input.LA(2) ) {
            case '0':
                {
                switch ( input.LA(3) ) {
                case '1':
                    {
                    int LA12_27 = input.LA(4);

                    if ( ((LA12_27 >= '0' && LA12_27 <= '9')||(LA12_27 >= 'A' && LA12_27 <= 'Z')||LA12_27=='_'||(LA12_27 >= 'a' && LA12_27 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                    }
                    break;
                case '2':
                    {
                    int LA12_28 = input.LA(4);

                    if ( ((LA12_28 >= '0' && LA12_28 <= '9')||(LA12_28 >= 'A' && LA12_28 <= 'Z')||LA12_28=='_'||(LA12_28 >= 'a' && LA12_28 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                    }
                    break;
                case '3':
                    {
                    int LA12_29 = input.LA(4);

                    if ( ((LA12_29 >= '0' && LA12_29 <= '9')||(LA12_29 >= 'A' && LA12_29 <= 'Z')||LA12_29=='_'||(LA12_29 >= 'a' && LA12_29 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                    }
                    break;
                default:
                    alt12=17;
                }

                }
                break;
            case '1':
                {
                int LA12_24 = input.LA(3);

                if ( (LA12_24=='2') ) {
                    int LA12_30 = input.LA(4);

                    if ( ((LA12_30 >= '0' && LA12_30 <= '9')||(LA12_30 >= 'A' && LA12_30 <= 'Z')||LA12_30=='_'||(LA12_30 >= 'a' && LA12_30 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                }
                else {
                    alt12=17;
                }
                }
                break;
            case '2':
                {
                int LA12_25 = input.LA(3);

                if ( (LA12_25=='3') ) {
                    int LA12_31 = input.LA(4);

                    if ( ((LA12_31 >= '0' && LA12_31 <= '9')||(LA12_31 >= 'A' && LA12_31 <= 'Z')||LA12_31=='_'||(LA12_31 >= 'a' && LA12_31 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                }
                else {
                    alt12=17;
                }
                }
                break;
            case '3':
                {
                int LA12_26 = input.LA(3);

                if ( (LA12_26=='1') ) {
                    int LA12_32 = input.LA(4);

                    if ( ((LA12_32 >= '0' && LA12_32 <= '9')||(LA12_32 >= 'A' && LA12_32 <= 'Z')||LA12_32=='_'||(LA12_32 >= 'a' && LA12_32 <= 'z')) ) {
                        alt12=17;
                    }
                    else {
                        alt12=16;
                    }
                }
                else {
                    alt12=17;
                }
                }
                break;
            default:
                alt12=17;
            }

            }
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            {
            alt12=17;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            {
            alt12=18;
            }
            break;
        default:
            NoViableAltException nvae =
                new NoViableAltException("", 12, 0, input);

            throw nvae;

        }

        switch (alt12) {
            case 1 :
                // src/plviewer/Console.g:1:10: COMMA
                {
                mCOMMA(); 


                }
                break;
            case 2 :
                // src/plviewer/Console.g:1:16: SEMICOLON
                {
                mSEMICOLON(); 


                }
                break;
            case 3 :
                // src/plviewer/Console.g:1:26: ASSIGN
                {
                mASSIGN(); 


                }
                break;
            case 4 :
                // src/plviewer/Console.g:1:33: PLUS
                {
                mPLUS(); 


                }
                break;
            case 5 :
                // src/plviewer/Console.g:1:38: MINUS
                {
                mMINUS(); 


                }
                break;
            case 6 :
                // src/plviewer/Console.g:1:44: MULT
                {
                mMULT(); 


                }
                break;
            case 7 :
                // src/plviewer/Console.g:1:49: DIV
                {
                mDIV(); 


                }
                break;
            case 8 :
                // src/plviewer/Console.g:1:53: DOT
                {
                mDOT(); 


                }
                break;
            case 9 :
                // src/plviewer/Console.g:1:57: WEDGE
                {
                mWEDGE(); 


                }
                break;
            case 10 :
                // src/plviewer/Console.g:1:63: NEGATE
                {
                mNEGATE(); 


                }
                break;
            case 11 :
                // src/plviewer/Console.g:1:70: REVERSE
                {
                mREVERSE(); 


                }
                break;
            case 12 :
                // src/plviewer/Console.g:1:78: RPAREN
                {
                mRPAREN(); 


                }
                break;
            case 13 :
                // src/plviewer/Console.g:1:85: LPAREN
                {
                mLPAREN(); 


                }
                break;
            case 14 :
                // src/plviewer/Console.g:1:92: NEWLINE
                {
                mNEWLINE(); 


                }
                break;
            case 15 :
                // src/plviewer/Console.g:1:100: WHITESPACE
                {
                mWHITESPACE(); 


                }
                break;
            case 16 :
                // src/plviewer/Console.g:1:111: CONSTANT
                {
                mCONSTANT(); 


                }
                break;
            case 17 :
                // src/plviewer/Console.g:1:120: NAME
                {
                mNAME(); 


                }
                break;
            case 18 :
                // src/plviewer/Console.g:1:125: NUMBER
                {
                mNUMBER(); 


                }
                break;

        }

    }


 

}