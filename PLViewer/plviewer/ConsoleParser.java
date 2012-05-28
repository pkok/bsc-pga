// $ANTLR 3.4 plviewer/Console.g 2012-05-29 01:17:04

package plviewer;

import java.util.Queue;
import java.util.LinkedList;

import pl3ga_pkg.mv;
import pl3ga_pkg.pl3ga;


import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

import org.antlr.runtime.tree.*;


@SuppressWarnings({"all", "warnings", "unchecked"})
public class ConsoleParser extends CustomParser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "APPLY", "ASSIGN", "CHARACTER", "COMMA", "CONST", "CONSTANT", "DIGIT", "DISPLAY", "DIV", "DOT", "EXPONENT", "FUNC", "LPAREN", "MINUS", "MULT", "NAME", "NEGATE", "NEWLINE", "NIL", "NODISPLAY", "NUMBER", "PLUS", "REVERSE", "RPAREN", "SEMICOLON", "VAR", "WEDGE", "WHITESPACE"
    };

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
    public CustomParser[] getDelegates() {
        return new CustomParser[] {};
    }

    // delegators


    public ConsoleParser(TokenStream input) {
        this(input, new RecognizerSharedState());
    }
    public ConsoleParser(TokenStream input, RecognizerSharedState state) {
        super(input, state);
    }

protected TreeAdaptor adaptor = new CommonTreeAdaptor();

public void setTreeAdaptor(TreeAdaptor adaptor) {
    this.adaptor = adaptor;
}
public TreeAdaptor getTreeAdaptor() {
    return adaptor;
}
    public String[] getTokenNames() { return ConsoleParser.tokenNames; }
    public String getGrammarFileName() { return "plviewer/Console.g"; }


      protected mv applyOperator(int op, mv x) {
        switch (op) {
          case NEGATE: 
            return pl3ga.negate(x);
          case REVERSE: 
            return pl3ga.reverse(x);
          case MINUS:
            return pl3ga.subtract(new mv(), x);
          case PLUS:
          default:
            break;
        }
        return x;
      }

      protected mv applyOperator(int op, mv x, mv y) {
        switch (op) {
          case PLUS:
            return pl3ga.add(x, y);
          case MINUS:
            return pl3ga.subtract(x, y);
          case MULT:
            return pl3ga.gp(x, y);
          case DIV:
            return pl3ga.igp(x, y);
          case DOT:
            return pl3ga.lc(x, y);
          case WEDGE:
            return pl3ga.op(x, y);
          default:
            break;
        }
        return new mv();
      }


    public static class prog_return extends ParserRuleReturnScope {
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "prog"
    // plviewer/Console.g:71:1: prog : ( endstat )* EOF ;
    public final ConsoleParser.prog_return prog() throws RecognitionException {
        ConsoleParser.prog_return retval = new ConsoleParser.prog_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token EOF2=null;
        ConsoleParser.endstat_return endstat1 =null;


        Object EOF2_tree=null;

        try {
            // plviewer/Console.g:71:6: ( ( endstat )* EOF )
            // plviewer/Console.g:71:8: ( endstat )* EOF
            {
            root_0 = (Object)adaptor.nil();


            // plviewer/Console.g:71:8: ( endstat )*
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( (LA1_0==CONSTANT||(LA1_0 >= LPAREN && LA1_0 <= MINUS)||(LA1_0 >= NAME && LA1_0 <= NEGATE)||(LA1_0 >= NUMBER && LA1_0 <= REVERSE)) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // plviewer/Console.g:71:8: endstat
            	    {
            	    pushFollow(FOLLOW_endstat_in_prog87);
            	    endstat1=endstat();

            	    state._fsp--;

            	    adaptor.addChild(root_0, endstat1.getTree());

            	    }
            	    break;

            	default :
            	    break loop1;
                }
            } while (true);


            EOF2=(Token)match(input,EOF,FOLLOW_EOF_in_prog90); 
            EOF2_tree = 
            (Object)adaptor.create(EOF2)
            ;
            adaptor.addChild(root_0, EOF2_tree);


            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "prog"


    public static class endstat_return extends ParserRuleReturnScope {
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "endstat"
    // plviewer/Console.g:73:1: endstat : s= stat t= terminator ^;
    public final ConsoleParser.endstat_return endstat() throws RecognitionException {
        ConsoleParser.endstat_return retval = new ConsoleParser.endstat_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.stat_return s =null;

        ConsoleParser.terminator_return t =null;



        try {
            // plviewer/Console.g:73:9: (s= stat t= terminator ^)
            // plviewer/Console.g:73:11: s= stat t= terminator ^
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_stat_in_endstat100);
            s=stat();

            state._fsp--;

            adaptor.addChild(root_0, s.getTree());

            pushFollow(FOLLOW_terminator_in_endstat104);
            t=terminator();

            state._fsp--;

            root_0 = (Object)adaptor.becomeRoot(t.getTree(), root_0);

            completeExpr(s.r, t.display);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "endstat"


    public static class terminator_return extends ParserRuleReturnScope {
        public boolean display;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "terminator"
    // plviewer/Console.g:75:1: terminator returns [boolean display] : ( ( COMMA | NEWLINE | EOF ) -> DISPLAY | SEMICOLON -> NODISPLAY );
    public final ConsoleParser.terminator_return terminator() throws RecognitionException {
        ConsoleParser.terminator_return retval = new ConsoleParser.terminator_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token COMMA3=null;
        Token NEWLINE4=null;
        Token EOF5=null;
        Token SEMICOLON6=null;

        Object COMMA3_tree=null;
        Object NEWLINE4_tree=null;
        Object EOF5_tree=null;
        Object SEMICOLON6_tree=null;
        RewriteRuleTokenStream stream_SEMICOLON=new RewriteRuleTokenStream(adaptor,"token SEMICOLON");
        RewriteRuleTokenStream stream_NEWLINE=new RewriteRuleTokenStream(adaptor,"token NEWLINE");
        RewriteRuleTokenStream stream_COMMA=new RewriteRuleTokenStream(adaptor,"token COMMA");
        RewriteRuleTokenStream stream_EOF=new RewriteRuleTokenStream(adaptor,"token EOF");

        try {
            // plviewer/Console.g:76:8: ( ( COMMA | NEWLINE | EOF ) -> DISPLAY | SEMICOLON -> NODISPLAY )
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0==EOF||LA3_0==COMMA||LA3_0==NEWLINE) ) {
                alt3=1;
            }
            else if ( (LA3_0==SEMICOLON) ) {
                alt3=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 3, 0, input);

                throw nvae;

            }
            switch (alt3) {
                case 1 :
                    // plviewer/Console.g:76:10: ( COMMA | NEWLINE | EOF )
                    {
                    // plviewer/Console.g:76:10: ( COMMA | NEWLINE | EOF )
                    int alt2=3;
                    switch ( input.LA(1) ) {
                    case COMMA:
                        {
                        alt2=1;
                        }
                        break;
                    case NEWLINE:
                        {
                        alt2=2;
                        }
                        break;
                    case EOF:
                        {
                        alt2=3;
                        }
                        break;
                    default:
                        NoViableAltException nvae =
                            new NoViableAltException("", 2, 0, input);

                        throw nvae;

                    }

                    switch (alt2) {
                        case 1 :
                            // plviewer/Console.g:76:11: COMMA
                            {
                            COMMA3=(Token)match(input,COMMA,FOLLOW_COMMA_in_terminator128);  
                            stream_COMMA.add(COMMA3);


                            }
                            break;
                        case 2 :
                            // plviewer/Console.g:76:19: NEWLINE
                            {
                            NEWLINE4=(Token)match(input,NEWLINE,FOLLOW_NEWLINE_in_terminator132);  
                            stream_NEWLINE.add(NEWLINE4);


                            }
                            break;
                        case 3 :
                            // plviewer/Console.g:76:29: EOF
                            {
                            EOF5=(Token)match(input,EOF,FOLLOW_EOF_in_terminator136);  
                            stream_EOF.add(EOF5);


                            }
                            break;

                    }


                    retval.display = true;

                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (Object)adaptor.nil();
                    // 78:13: -> DISPLAY
                    {
                        adaptor.addChild(root_0, 
                        (Object)adaptor.create(DISPLAY, "DISPLAY")
                        );

                    }


                    retval.tree = root_0;

                    }
                    break;
                case 2 :
                    // plviewer/Console.g:79:10: SEMICOLON
                    {
                    SEMICOLON6=(Token)match(input,SEMICOLON,FOLLOW_SEMICOLON_in_terminator179);  
                    stream_SEMICOLON.add(SEMICOLON6);


                    retval.display = false;

                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (Object)adaptor.nil();
                    // 81:13: -> NODISPLAY
                    {
                        adaptor.addChild(root_0, 
                        (Object)adaptor.create(NODISPLAY, "NODISPLAY")
                        );

                    }


                    retval.tree = root_0;

                    }
                    break;

            }
            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "terminator"


    public static class stat_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "stat"
    // plviewer/Console.g:84:1: stat returns [mv r] : ( ( variable ASSIGN )+ expr -> ^( ASSIGN ( variable )* expr ) | expr );
    public final ConsoleParser.stat_return stat() throws RecognitionException {
        ConsoleParser.stat_return retval = new ConsoleParser.stat_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token ASSIGN8=null;
        ConsoleParser.variable_return variable7 =null;

        ConsoleParser.expr_return expr9 =null;

        ConsoleParser.expr_return expr10 =null;


        Object ASSIGN8_tree=null;
        RewriteRuleTokenStream stream_ASSIGN=new RewriteRuleTokenStream(adaptor,"token ASSIGN");
        RewriteRuleSubtreeStream stream_expr=new RewriteRuleSubtreeStream(adaptor,"rule expr");
        RewriteRuleSubtreeStream stream_variable=new RewriteRuleSubtreeStream(adaptor,"rule variable");
        try {
            // plviewer/Console.g:84:20: ( ( variable ASSIGN )+ expr -> ^( ASSIGN ( variable )* expr ) | expr )
            int alt5=2;
            int LA5_0 = input.LA(1);

            if ( (LA5_0==NAME) ) {
                int LA5_1 = input.LA(2);

                if ( (LA5_1==EOF||LA5_1==COMMA||(LA5_1 >= DIV && LA5_1 <= DOT)||(LA5_1 >= LPAREN && LA5_1 <= MULT)||LA5_1==NEWLINE||LA5_1==PLUS||LA5_1==SEMICOLON||LA5_1==WEDGE) ) {
                    alt5=2;
                }
                else if ( (LA5_1==ASSIGN) ) {
                    alt5=1;
                }
                else {
                    NoViableAltException nvae =
                        new NoViableAltException("", 5, 1, input);

                    throw nvae;

                }
            }
            else if ( (LA5_0==CONSTANT||(LA5_0 >= LPAREN && LA5_0 <= MINUS)||LA5_0==NEGATE||(LA5_0 >= NUMBER && LA5_0 <= REVERSE)) ) {
                alt5=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 5, 0, input);

                throw nvae;

            }
            switch (alt5) {
                case 1 :
                    // plviewer/Console.g:84:22: ( variable ASSIGN )+ expr
                    {
                    // plviewer/Console.g:84:22: ( variable ASSIGN )+
                    int cnt4=0;
                    loop4:
                    do {
                        int alt4=2;
                        int LA4_0 = input.LA(1);

                        if ( (LA4_0==NAME) ) {
                            int LA4_2 = input.LA(2);

                            if ( (LA4_2==ASSIGN) ) {
                                alt4=1;
                            }


                        }


                        switch (alt4) {
                    	case 1 :
                    	    // plviewer/Console.g:84:23: variable ASSIGN
                    	    {
                    	    pushFollow(FOLLOW_variable_in_stat230);
                    	    variable7=variable();

                    	    state._fsp--;

                    	    stream_variable.add(variable7.getTree());

                    	    ASSIGN8=(Token)match(input,ASSIGN,FOLLOW_ASSIGN_in_stat232);  
                    	    stream_ASSIGN.add(ASSIGN8);


                    	    }
                    	    break;

                    	default :
                    	    if ( cnt4 >= 1 ) break loop4;
                                EarlyExitException eee =
                                    new EarlyExitException(4, input);
                                throw eee;
                        }
                        cnt4++;
                    } while (true);


                    pushFollow(FOLLOW_expr_in_stat236);
                    expr9=expr();

                    state._fsp--;

                    stream_expr.add(expr9.getTree());

                    setVariable((variable7!=null?variable7.name:null), (expr9!=null?expr9.r:null)); retval.r = (expr9!=null?expr9.r:null);

                    // AST REWRITE
                    // elements: expr, ASSIGN, variable
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (Object)adaptor.nil();
                    // 84:99: -> ^( ASSIGN ( variable )* expr )
                    {
                        // plviewer/Console.g:84:102: ^( ASSIGN ( variable )* expr )
                        {
                        Object root_1 = (Object)adaptor.nil();
                        root_1 = (Object)adaptor.becomeRoot(
                        stream_ASSIGN.nextNode()
                        , root_1);

                        // plviewer/Console.g:84:111: ( variable )*
                        while ( stream_variable.hasNext() ) {
                            adaptor.addChild(root_1, stream_variable.nextTree());

                        }
                        stream_variable.reset();

                        adaptor.addChild(root_1, stream_expr.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }


                    retval.tree = root_0;

                    }
                    break;
                case 2 :
                    // plviewer/Console.g:85:8: expr
                    {
                    root_0 = (Object)adaptor.nil();


                    pushFollow(FOLLOW_expr_in_stat257);
                    expr10=expr();

                    state._fsp--;

                    adaptor.addChild(root_0, expr10.getTree());

                    retval.r = (expr10!=null?expr10.r:null);

                    }
                    break;

            }
            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "stat"


    public static class expr_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "expr"
    // plviewer/Console.g:87:1: expr returns [mv r] : x= multExpr (o= plusgrp ^y= multExpr )* ;
    public final ConsoleParser.expr_return expr() throws RecognitionException {
        ConsoleParser.expr_return retval = new ConsoleParser.expr_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.multExpr_return x =null;

        ConsoleParser.plusgrp_return o =null;

        ConsoleParser.multExpr_return y =null;



        try {
            // plviewer/Console.g:87:20: (x= multExpr (o= plusgrp ^y= multExpr )* )
            // plviewer/Console.g:87:22: x= multExpr (o= plusgrp ^y= multExpr )*
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_multExpr_in_expr272);
            x=multExpr();

            state._fsp--;

            adaptor.addChild(root_0, x.getTree());

            // plviewer/Console.g:87:33: (o= plusgrp ^y= multExpr )*
            loop6:
            do {
                int alt6=2;
                int LA6_0 = input.LA(1);

                if ( (LA6_0==MINUS||LA6_0==PLUS) ) {
                    alt6=1;
                }


                switch (alt6) {
            	case 1 :
            	    // plviewer/Console.g:87:34: o= plusgrp ^y= multExpr
            	    {
            	    pushFollow(FOLLOW_plusgrp_in_expr277);
            	    o=plusgrp();

            	    state._fsp--;

            	    root_0 = (Object)adaptor.becomeRoot(o.getTree(), root_0);

            	    pushFollow(FOLLOW_multExpr_in_expr282);
            	    y=multExpr();

            	    state._fsp--;

            	    adaptor.addChild(root_0, y.getTree());

            	    }
            	    break;

            	default :
            	    break loop6;
                }
            } while (true);


            retval.r = applyOperator(o.token, x.r, y.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "expr"


    public static class multExpr_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "multExpr"
    // plviewer/Console.g:89:1: multExpr returns [mv r] : x= dotExpr (o= multgrp ^y= dotExpr )* ;
    public final ConsoleParser.multExpr_return multExpr() throws RecognitionException {
        ConsoleParser.multExpr_return retval = new ConsoleParser.multExpr_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.dotExpr_return x =null;

        ConsoleParser.multgrp_return o =null;

        ConsoleParser.dotExpr_return y =null;



        try {
            // plviewer/Console.g:89:24: (x= dotExpr (o= multgrp ^y= dotExpr )* )
            // plviewer/Console.g:89:26: x= dotExpr (o= multgrp ^y= dotExpr )*
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_dotExpr_in_multExpr299);
            x=dotExpr();

            state._fsp--;

            adaptor.addChild(root_0, x.getTree());

            // plviewer/Console.g:89:36: (o= multgrp ^y= dotExpr )*
            loop7:
            do {
                int alt7=2;
                int LA7_0 = input.LA(1);

                if ( (LA7_0==DIV||LA7_0==MULT) ) {
                    alt7=1;
                }


                switch (alt7) {
            	case 1 :
            	    // plviewer/Console.g:89:37: o= multgrp ^y= dotExpr
            	    {
            	    pushFollow(FOLLOW_multgrp_in_multExpr304);
            	    o=multgrp();

            	    state._fsp--;

            	    root_0 = (Object)adaptor.becomeRoot(o.getTree(), root_0);

            	    pushFollow(FOLLOW_dotExpr_in_multExpr309);
            	    y=dotExpr();

            	    state._fsp--;

            	    adaptor.addChild(root_0, y.getTree());

            	    }
            	    break;

            	default :
            	    break loop7;
                }
            } while (true);


            retval.r = applyOperator(o.token, x.r, y.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "multExpr"


    public static class dotExpr_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "dotExpr"
    // plviewer/Console.g:91:1: dotExpr returns [mv r] : x= wedgeExpr (o= dotgrp ^y= wedgeExpr )* ;
    public final ConsoleParser.dotExpr_return dotExpr() throws RecognitionException {
        ConsoleParser.dotExpr_return retval = new ConsoleParser.dotExpr_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.wedgeExpr_return x =null;

        ConsoleParser.dotgrp_return o =null;

        ConsoleParser.wedgeExpr_return y =null;



        try {
            // plviewer/Console.g:91:23: (x= wedgeExpr (o= dotgrp ^y= wedgeExpr )* )
            // plviewer/Console.g:91:25: x= wedgeExpr (o= dotgrp ^y= wedgeExpr )*
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_wedgeExpr_in_dotExpr327);
            x=wedgeExpr();

            state._fsp--;

            adaptor.addChild(root_0, x.getTree());

            // plviewer/Console.g:91:37: (o= dotgrp ^y= wedgeExpr )*
            loop8:
            do {
                int alt8=2;
                int LA8_0 = input.LA(1);

                if ( (LA8_0==DOT) ) {
                    alt8=1;
                }


                switch (alt8) {
            	case 1 :
            	    // plviewer/Console.g:91:38: o= dotgrp ^y= wedgeExpr
            	    {
            	    pushFollow(FOLLOW_dotgrp_in_dotExpr332);
            	    o=dotgrp();

            	    state._fsp--;

            	    root_0 = (Object)adaptor.becomeRoot(o.getTree(), root_0);

            	    pushFollow(FOLLOW_wedgeExpr_in_dotExpr337);
            	    y=wedgeExpr();

            	    state._fsp--;

            	    adaptor.addChild(root_0, y.getTree());

            	    }
            	    break;

            	default :
            	    break loop8;
                }
            } while (true);


            retval.r = applyOperator(o.token, x.r, y.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "dotExpr"


    public static class wedgeExpr_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "wedgeExpr"
    // plviewer/Console.g:93:1: wedgeExpr returns [mv r] : x= prefixed (o= wedgegrp ^y= prefixed )* ;
    public final ConsoleParser.wedgeExpr_return wedgeExpr() throws RecognitionException {
        ConsoleParser.wedgeExpr_return retval = new ConsoleParser.wedgeExpr_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.prefixed_return x =null;

        ConsoleParser.wedgegrp_return o =null;

        ConsoleParser.prefixed_return y =null;



        try {
            // plviewer/Console.g:93:25: (x= prefixed (o= wedgegrp ^y= prefixed )* )
            // plviewer/Console.g:93:27: x= prefixed (o= wedgegrp ^y= prefixed )*
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_prefixed_in_wedgeExpr354);
            x=prefixed();

            state._fsp--;

            adaptor.addChild(root_0, x.getTree());

            // plviewer/Console.g:93:38: (o= wedgegrp ^y= prefixed )*
            loop9:
            do {
                int alt9=2;
                int LA9_0 = input.LA(1);

                if ( (LA9_0==WEDGE) ) {
                    alt9=1;
                }


                switch (alt9) {
            	case 1 :
            	    // plviewer/Console.g:93:39: o= wedgegrp ^y= prefixed
            	    {
            	    pushFollow(FOLLOW_wedgegrp_in_wedgeExpr359);
            	    o=wedgegrp();

            	    state._fsp--;

            	    root_0 = (Object)adaptor.becomeRoot(o.getTree(), root_0);

            	    pushFollow(FOLLOW_prefixed_in_wedgeExpr364);
            	    y=prefixed();

            	    state._fsp--;

            	    adaptor.addChild(root_0, y.getTree());

            	    }
            	    break;

            	default :
            	    break loop9;
                }
            } while (true);


            retval.r = applyOperator(o.token, x.r, y.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "wedgeExpr"


    public static class prefixed_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "prefixed"
    // plviewer/Console.g:95:1: prefixed returns [mv r] : (o= unarygrp )? x= atom ;
    public final ConsoleParser.prefixed_return prefixed() throws RecognitionException {
        ConsoleParser.prefixed_return retval = new ConsoleParser.prefixed_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        ConsoleParser.unarygrp_return o =null;

        ConsoleParser.atom_return x =null;



        try {
            // plviewer/Console.g:95:24: ( (o= unarygrp )? x= atom )
            // plviewer/Console.g:95:26: (o= unarygrp )? x= atom
            {
            root_0 = (Object)adaptor.nil();


            // plviewer/Console.g:95:27: (o= unarygrp )?
            int alt10=2;
            int LA10_0 = input.LA(1);

            if ( (LA10_0==MINUS||LA10_0==NEGATE||(LA10_0 >= PLUS && LA10_0 <= REVERSE)) ) {
                alt10=1;
            }
            switch (alt10) {
                case 1 :
                    // plviewer/Console.g:95:27: o= unarygrp
                    {
                    pushFollow(FOLLOW_unarygrp_in_prefixed381);
                    o=unarygrp();

                    state._fsp--;

                    adaptor.addChild(root_0, o.getTree());

                    }
                    break;

            }


            pushFollow(FOLLOW_atom_in_prefixed386);
            x=atom();

            state._fsp--;

            adaptor.addChild(root_0, x.getTree());

            retval.r = applyOperator(o.token, x.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "prefixed"


    public static class atom_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "atom"
    // plviewer/Console.g:97:1: atom returns [mv r] : (a= number |b= constant |c= variable |d= funccall | LPAREN !x= expr RPAREN !);
    public final ConsoleParser.atom_return atom() throws RecognitionException {
        ConsoleParser.atom_return retval = new ConsoleParser.atom_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token LPAREN11=null;
        Token RPAREN12=null;
        ConsoleParser.number_return a =null;

        ConsoleParser.constant_return b =null;

        ConsoleParser.variable_return c =null;

        ConsoleParser.funccall_return d =null;

        ConsoleParser.expr_return x =null;


        Object LPAREN11_tree=null;
        Object RPAREN12_tree=null;

        try {
            // plviewer/Console.g:97:20: (a= number |b= constant |c= variable |d= funccall | LPAREN !x= expr RPAREN !)
            int alt11=5;
            switch ( input.LA(1) ) {
            case NUMBER:
                {
                alt11=1;
                }
                break;
            case CONSTANT:
                {
                alt11=2;
                }
                break;
            case NAME:
                {
                int LA11_3 = input.LA(2);

                if ( (LA11_3==LPAREN) ) {
                    alt11=4;
                }
                else if ( (LA11_3==EOF||LA11_3==COMMA||(LA11_3 >= DIV && LA11_3 <= DOT)||(LA11_3 >= MINUS && LA11_3 <= MULT)||LA11_3==NEWLINE||LA11_3==PLUS||(LA11_3 >= RPAREN && LA11_3 <= SEMICOLON)||LA11_3==WEDGE) ) {
                    alt11=3;
                }
                else {
                    NoViableAltException nvae =
                        new NoViableAltException("", 11, 3, input);

                    throw nvae;

                }
                }
                break;
            case LPAREN:
                {
                alt11=5;
                }
                break;
            default:
                NoViableAltException nvae =
                    new NoViableAltException("", 11, 0, input);

                throw nvae;

            }

            switch (alt11) {
                case 1 :
                    // plviewer/Console.g:97:22: a= number
                    {
                    root_0 = (Object)adaptor.nil();


                    pushFollow(FOLLOW_number_in_atom401);
                    a=number();

                    state._fsp--;

                    adaptor.addChild(root_0, a.getTree());

                    retval.r = a.r;

                    }
                    break;
                case 2 :
                    // plviewer/Console.g:98:4: b= constant
                    {
                    root_0 = (Object)adaptor.nil();


                    pushFollow(FOLLOW_constant_in_atom410);
                    b=constant();

                    state._fsp--;

                    adaptor.addChild(root_0, b.getTree());

                    retval.r = b.r;

                    }
                    break;
                case 3 :
                    // plviewer/Console.g:99:4: c= variable
                    {
                    root_0 = (Object)adaptor.nil();


                    pushFollow(FOLLOW_variable_in_atom419);
                    c=variable();

                    state._fsp--;

                    adaptor.addChild(root_0, c.getTree());

                    retval.r = c.r;

                    }
                    break;
                case 4 :
                    // plviewer/Console.g:100:4: d= funccall
                    {
                    root_0 = (Object)adaptor.nil();


                    pushFollow(FOLLOW_funccall_in_atom428);
                    d=funccall();

                    state._fsp--;

                    adaptor.addChild(root_0, d.getTree());

                    retval.r = d.r;

                    }
                    break;
                case 5 :
                    // plviewer/Console.g:101:4: LPAREN !x= expr RPAREN !
                    {
                    root_0 = (Object)adaptor.nil();


                    LPAREN11=(Token)match(input,LPAREN,FOLLOW_LPAREN_in_atom435); 

                    pushFollow(FOLLOW_expr_in_atom440);
                    x=expr();

                    state._fsp--;

                    adaptor.addChild(root_0, x.getTree());

                    RPAREN12=(Token)match(input,RPAREN,FOLLOW_RPAREN_in_atom442); 

                    retval.r = x.r;

                    }
                    break;

            }
            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "atom"


    public static class plusgrp_return extends ParserRuleReturnScope {
        public int token;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "plusgrp"
    // plviewer/Console.g:103:1: plusgrp returns [int token] : x= ( PLUS | MINUS ) ;
    public final ConsoleParser.plusgrp_return plusgrp() throws RecognitionException {
        ConsoleParser.plusgrp_return retval = new ConsoleParser.plusgrp_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token x=null;

        Object x_tree=null;

        try {
            // plviewer/Console.g:103:29: (x= ( PLUS | MINUS ) )
            // plviewer/Console.g:103:31: x= ( PLUS | MINUS )
            {
            root_0 = (Object)adaptor.nil();


            x=(Token)input.LT(1);

            if ( input.LA(1)==MINUS||input.LA(1)==PLUS ) {
                input.consume();
                adaptor.addChild(root_0, 
                (Object)adaptor.create(x)
                );
                state.errorRecovery=false;
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            retval.token = x.getType();

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "plusgrp"


    public static class multgrp_return extends ParserRuleReturnScope {
        public int token;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "multgrp"
    // plviewer/Console.g:104:1: multgrp returns [int token] : x= ( MULT | DIV ) ;
    public final ConsoleParser.multgrp_return multgrp() throws RecognitionException {
        ConsoleParser.multgrp_return retval = new ConsoleParser.multgrp_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token x=null;

        Object x_tree=null;

        try {
            // plviewer/Console.g:104:29: (x= ( MULT | DIV ) )
            // plviewer/Console.g:104:31: x= ( MULT | DIV )
            {
            root_0 = (Object)adaptor.nil();


            x=(Token)input.LT(1);

            if ( input.LA(1)==DIV||input.LA(1)==MULT ) {
                input.consume();
                adaptor.addChild(root_0, 
                (Object)adaptor.create(x)
                );
                state.errorRecovery=false;
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            retval.token = x.getType();

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "multgrp"


    public static class dotgrp_return extends ParserRuleReturnScope {
        public int token;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "dotgrp"
    // plviewer/Console.g:105:1: dotgrp returns [int token] : x= DOT ;
    public final ConsoleParser.dotgrp_return dotgrp() throws RecognitionException {
        ConsoleParser.dotgrp_return retval = new ConsoleParser.dotgrp_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token x=null;

        Object x_tree=null;

        try {
            // plviewer/Console.g:105:29: (x= DOT )
            // plviewer/Console.g:105:31: x= DOT
            {
            root_0 = (Object)adaptor.nil();


            x=(Token)match(input,DOT,FOLLOW_DOT_in_dotgrp502); 
            x_tree = 
            (Object)adaptor.create(x)
            ;
            adaptor.addChild(root_0, x_tree);


            retval.token = x.getType();

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "dotgrp"


    public static class wedgegrp_return extends ParserRuleReturnScope {
        public int token;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "wedgegrp"
    // plviewer/Console.g:106:1: wedgegrp returns [int token] : x= WEDGE ;
    public final ConsoleParser.wedgegrp_return wedgegrp() throws RecognitionException {
        ConsoleParser.wedgegrp_return retval = new ConsoleParser.wedgegrp_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token x=null;

        Object x_tree=null;

        try {
            // plviewer/Console.g:106:29: (x= WEDGE )
            // plviewer/Console.g:106:31: x= WEDGE
            {
            root_0 = (Object)adaptor.nil();


            x=(Token)match(input,WEDGE,FOLLOW_WEDGE_in_wedgegrp516); 
            x_tree = 
            (Object)adaptor.create(x)
            ;
            adaptor.addChild(root_0, x_tree);


            retval.token = x.getType();

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "wedgegrp"


    public static class unarygrp_return extends ParserRuleReturnScope {
        public int token;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "unarygrp"
    // plviewer/Console.g:107:1: unarygrp returns [int token] : x= ( NEGATE | REVERSE | PLUS | MINUS ) ;
    public final ConsoleParser.unarygrp_return unarygrp() throws RecognitionException {
        ConsoleParser.unarygrp_return retval = new ConsoleParser.unarygrp_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token x=null;

        Object x_tree=null;

        try {
            // plviewer/Console.g:107:29: (x= ( NEGATE | REVERSE | PLUS | MINUS ) )
            // plviewer/Console.g:107:31: x= ( NEGATE | REVERSE | PLUS | MINUS )
            {
            root_0 = (Object)adaptor.nil();


            x=(Token)input.LT(1);

            if ( input.LA(1)==MINUS||input.LA(1)==NEGATE||(input.LA(1) >= PLUS && input.LA(1) <= REVERSE) ) {
                input.consume();
                adaptor.addChild(root_0, 
                (Object)adaptor.create(x)
                );
                state.errorRecovery=false;
            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            retval.token = x.getType();

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "unarygrp"


    public static class number_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "number"
    // plviewer/Console.g:109:1: number returns [mv r] : NUMBER ;
    public final ConsoleParser.number_return number() throws RecognitionException {
        ConsoleParser.number_return retval = new ConsoleParser.number_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token NUMBER13=null;

        Object NUMBER13_tree=null;

        try {
            // plviewer/Console.g:110:8: ( NUMBER )
            // plviewer/Console.g:110:10: NUMBER
            {
            root_0 = (Object)adaptor.nil();


            NUMBER13=(Token)match(input,NUMBER,FOLLOW_NUMBER_in_number565); 
            NUMBER13_tree = 
            (Object)adaptor.create(NUMBER13)
            ;
            adaptor.addChild(root_0, NUMBER13_tree);


            retval.r = toMV((NUMBER13!=null?NUMBER13.getText():null));

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "number"


    public static class constant_return extends ParserRuleReturnScope {
        public mv r;
        public String name;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "constant"
    // plviewer/Console.g:112:1: constant returns [mv r, String name] : CONSTANT ;
    public final ConsoleParser.constant_return constant() throws RecognitionException {
        ConsoleParser.constant_return retval = new ConsoleParser.constant_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token CONSTANT14=null;

        Object CONSTANT14_tree=null;

        try {
            // plviewer/Console.g:113:8: ( CONSTANT )
            // plviewer/Console.g:113:10: CONSTANT
            {
            root_0 = (Object)adaptor.nil();


            CONSTANT14=(Token)match(input,CONSTANT,FOLLOW_CONSTANT_in_constant586); 
            CONSTANT14_tree = 
            (Object)adaptor.create(CONSTANT14)
            ;
            adaptor.addChild(root_0, CONSTANT14_tree);


            retval.name = (CONSTANT14!=null?CONSTANT14.getText():null); retval.r = getConstant(retval.name); 

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "constant"


    public static class variable_return extends ParserRuleReturnScope {
        public mv r;
        public String name;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "variable"
    // plviewer/Console.g:115:1: variable returns [mv r, String name] : NAME ;
    public final ConsoleParser.variable_return variable() throws RecognitionException {
        ConsoleParser.variable_return retval = new ConsoleParser.variable_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token NAME15=null;

        Object NAME15_tree=null;

        try {
            // plviewer/Console.g:116:8: ( NAME )
            // plviewer/Console.g:116:11: NAME
            {
            root_0 = (Object)adaptor.nil();


            NAME15=(Token)match(input,NAME,FOLLOW_NAME_in_variable608); 
            NAME15_tree = 
            (Object)adaptor.create(NAME15)
            ;
            adaptor.addChild(root_0, NAME15_tree);


            retval.name = (NAME15!=null?NAME15.getText():null); retval.r = getVariable(retval.name); 

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "variable"


    public static class funccall_return extends ParserRuleReturnScope {
        public mv r;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "funccall"
    // plviewer/Console.g:118:1: funccall returns [mv r] : (fn= NAME LPAREN RPAREN -> ^( APPLY $fn NIL ) |fn= NAME LPAREN args= arguments RPAREN -> ^( APPLY $fn $args) );
    public final ConsoleParser.funccall_return funccall() throws RecognitionException {
        ConsoleParser.funccall_return retval = new ConsoleParser.funccall_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token fn=null;
        Token LPAREN16=null;
        Token RPAREN17=null;
        Token LPAREN18=null;
        Token RPAREN19=null;
        ConsoleParser.arguments_return args =null;


        Object fn_tree=null;
        Object LPAREN16_tree=null;
        Object RPAREN17_tree=null;
        Object LPAREN18_tree=null;
        Object RPAREN19_tree=null;
        RewriteRuleTokenStream stream_RPAREN=new RewriteRuleTokenStream(adaptor,"token RPAREN");
        RewriteRuleTokenStream stream_NAME=new RewriteRuleTokenStream(adaptor,"token NAME");
        RewriteRuleTokenStream stream_LPAREN=new RewriteRuleTokenStream(adaptor,"token LPAREN");
        RewriteRuleSubtreeStream stream_arguments=new RewriteRuleSubtreeStream(adaptor,"rule arguments");
        try {
            // plviewer/Console.g:119:8: (fn= NAME LPAREN RPAREN -> ^( APPLY $fn NIL ) |fn= NAME LPAREN args= arguments RPAREN -> ^( APPLY $fn $args) )
            int alt12=2;
            int LA12_0 = input.LA(1);

            if ( (LA12_0==NAME) ) {
                int LA12_1 = input.LA(2);

                if ( (LA12_1==LPAREN) ) {
                    int LA12_2 = input.LA(3);

                    if ( (LA12_2==RPAREN) ) {
                        alt12=1;
                    }
                    else if ( (LA12_2==CONSTANT||(LA12_2 >= LPAREN && LA12_2 <= MINUS)||(LA12_2 >= NAME && LA12_2 <= NEGATE)||(LA12_2 >= NUMBER && LA12_2 <= REVERSE)) ) {
                        alt12=2;
                    }
                    else {
                        NoViableAltException nvae =
                            new NoViableAltException("", 12, 2, input);

                        throw nvae;

                    }
                }
                else {
                    NoViableAltException nvae =
                        new NoViableAltException("", 12, 1, input);

                    throw nvae;

                }
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 12, 0, input);

                throw nvae;

            }
            switch (alt12) {
                case 1 :
                    // plviewer/Console.g:119:10: fn= NAME LPAREN RPAREN
                    {
                    fn=(Token)match(input,NAME,FOLLOW_NAME_in_funccall632);  
                    stream_NAME.add(fn);


                    LPAREN16=(Token)match(input,LPAREN,FOLLOW_LPAREN_in_funccall634);  
                    stream_LPAREN.add(LPAREN16);


                    RPAREN17=(Token)match(input,RPAREN,FOLLOW_RPAREN_in_funccall636);  
                    stream_RPAREN.add(RPAREN17);


                    retval.r = applyFunction((fn!=null?fn.getText():null), new LinkedList<mv>());

                    // AST REWRITE
                    // elements: fn
                    // token labels: fn
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleTokenStream stream_fn=new RewriteRuleTokenStream(adaptor,"token fn",fn);
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (Object)adaptor.nil();
                    // 121:13: -> ^( APPLY $fn NIL )
                    {
                        // plviewer/Console.g:121:16: ^( APPLY $fn NIL )
                        {
                        Object root_1 = (Object)adaptor.nil();
                        root_1 = (Object)adaptor.becomeRoot(
                        (Object)adaptor.create(APPLY, "APPLY")
                        , root_1);

                        adaptor.addChild(root_1, stream_fn.nextNode());

                        adaptor.addChild(root_1, 
                        (Object)adaptor.create(NIL, "NIL")
                        );

                        adaptor.addChild(root_0, root_1);
                        }

                    }


                    retval.tree = root_0;

                    }
                    break;
                case 2 :
                    // plviewer/Console.g:122:10: fn= NAME LPAREN args= arguments RPAREN
                    {
                    fn=(Token)match(input,NAME,FOLLOW_NAME_in_funccall688);  
                    stream_NAME.add(fn);


                    LPAREN18=(Token)match(input,LPAREN,FOLLOW_LPAREN_in_funccall690);  
                    stream_LPAREN.add(LPAREN18);


                    pushFollow(FOLLOW_arguments_in_funccall694);
                    args=arguments();

                    state._fsp--;

                    stream_arguments.add(args.getTree());

                    RPAREN19=(Token)match(input,RPAREN,FOLLOW_RPAREN_in_funccall696);  
                    stream_RPAREN.add(RPAREN19);


                    retval.r = applyFunction((fn!=null?fn.getText():null), args.args);

                    // AST REWRITE
                    // elements: fn, args
                    // token labels: fn
                    // rule labels: retval, args
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleTokenStream stream_fn=new RewriteRuleTokenStream(adaptor,"token fn",fn);
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);
                    RewriteRuleSubtreeStream stream_args=new RewriteRuleSubtreeStream(adaptor,"rule args",args!=null?args.tree:null);

                    root_0 = (Object)adaptor.nil();
                    // 124:13: -> ^( APPLY $fn $args)
                    {
                        // plviewer/Console.g:124:16: ^( APPLY $fn $args)
                        {
                        Object root_1 = (Object)adaptor.nil();
                        root_1 = (Object)adaptor.becomeRoot(
                        (Object)adaptor.create(APPLY, "APPLY")
                        , root_1);

                        adaptor.addChild(root_1, stream_fn.nextNode());

                        adaptor.addChild(root_1, stream_args.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }


                    retval.tree = root_0;

                    }
                    break;

            }
            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "funccall"


    public static class arguments_return extends ParserRuleReturnScope {
        public Queue<mv> args;
        Object tree;
        public Object getTree() { return tree; }
    };


    // $ANTLR start "arguments"
    // plviewer/Console.g:127:1: arguments returns [Queue<mv> args] : x1= expr ( COMMA !xn= expr )* ;
    public final ConsoleParser.arguments_return arguments() throws RecognitionException {
        ConsoleParser.arguments_return retval = new ConsoleParser.arguments_return();
        retval.start = input.LT(1);


        Object root_0 = null;

        Token COMMA20=null;
        ConsoleParser.expr_return x1 =null;

        ConsoleParser.expr_return xn =null;


        Object COMMA20_tree=null;

        retval.args = new LinkedList<mv>();
        try {
            // plviewer/Console.g:129:8: (x1= expr ( COMMA !xn= expr )* )
            // plviewer/Console.g:129:10: x1= expr ( COMMA !xn= expr )*
            {
            root_0 = (Object)adaptor.nil();


            pushFollow(FOLLOW_expr_in_arguments769);
            x1=expr();

            state._fsp--;

            adaptor.addChild(root_0, x1.getTree());

            // plviewer/Console.g:129:18: ( COMMA !xn= expr )*
            loop13:
            do {
                int alt13=2;
                int LA13_0 = input.LA(1);

                if ( (LA13_0==COMMA) ) {
                    alt13=1;
                }


                switch (alt13) {
            	case 1 :
            	    // plviewer/Console.g:129:19: COMMA !xn= expr
            	    {
            	    COMMA20=(Token)match(input,COMMA,FOLLOW_COMMA_in_arguments772); 

            	    pushFollow(FOLLOW_expr_in_arguments777);
            	    xn=expr();

            	    state._fsp--;

            	    adaptor.addChild(root_0, xn.getTree());

            	    }
            	    break;

            	default :
            	    break loop13;
                }
            } while (true);


            retval.args.offer(x1.r);

            }

            retval.stop = input.LT(-1);


            retval.tree = (Object)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (Object)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }

        finally {
        	// do for sure before leaving
        }
        return retval;
    }
    // $ANTLR end "arguments"

    // Delegated rules


 

    public static final BitSet FOLLOW_endstat_in_prog87 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_EOF_in_prog90 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_stat_in_endstat100 = new BitSet(new long[]{0x0000000010200080L});
    public static final BitSet FOLLOW_terminator_in_endstat104 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_COMMA_in_terminator128 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NEWLINE_in_terminator132 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_EOF_in_terminator136 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_SEMICOLON_in_terminator179 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_variable_in_stat230 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_ASSIGN_in_stat232 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_expr_in_stat236 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expr_in_stat257 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_multExpr_in_expr272 = new BitSet(new long[]{0x0000000002020002L});
    public static final BitSet FOLLOW_plusgrp_in_expr277 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_multExpr_in_expr282 = new BitSet(new long[]{0x0000000002020002L});
    public static final BitSet FOLLOW_dotExpr_in_multExpr299 = new BitSet(new long[]{0x0000000000041002L});
    public static final BitSet FOLLOW_multgrp_in_multExpr304 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_dotExpr_in_multExpr309 = new BitSet(new long[]{0x0000000000041002L});
    public static final BitSet FOLLOW_wedgeExpr_in_dotExpr327 = new BitSet(new long[]{0x0000000000002002L});
    public static final BitSet FOLLOW_dotgrp_in_dotExpr332 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_wedgeExpr_in_dotExpr337 = new BitSet(new long[]{0x0000000000002002L});
    public static final BitSet FOLLOW_prefixed_in_wedgeExpr354 = new BitSet(new long[]{0x0000000040000002L});
    public static final BitSet FOLLOW_wedgegrp_in_wedgeExpr359 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_prefixed_in_wedgeExpr364 = new BitSet(new long[]{0x0000000040000002L});
    public static final BitSet FOLLOW_unarygrp_in_prefixed381 = new BitSet(new long[]{0x0000000001090200L});
    public static final BitSet FOLLOW_atom_in_prefixed386 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_number_in_atom401 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_constant_in_atom410 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_variable_in_atom419 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_funccall_in_atom428 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_LPAREN_in_atom435 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_expr_in_atom440 = new BitSet(new long[]{0x0000000008000000L});
    public static final BitSet FOLLOW_RPAREN_in_atom442 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_plusgrp459 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_multgrp480 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_DOT_in_dotgrp502 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_WEDGE_in_wedgegrp516 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_unarygrp530 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NUMBER_in_number565 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_CONSTANT_in_constant586 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NAME_in_variable608 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NAME_in_funccall632 = new BitSet(new long[]{0x0000000000010000L});
    public static final BitSet FOLLOW_LPAREN_in_funccall634 = new BitSet(new long[]{0x0000000008000000L});
    public static final BitSet FOLLOW_RPAREN_in_funccall636 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NAME_in_funccall688 = new BitSet(new long[]{0x0000000000010000L});
    public static final BitSet FOLLOW_LPAREN_in_funccall690 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_arguments_in_funccall694 = new BitSet(new long[]{0x0000000008000000L});
    public static final BitSet FOLLOW_RPAREN_in_funccall696 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expr_in_arguments769 = new BitSet(new long[]{0x0000000000000082L});
    public static final BitSet FOLLOW_COMMA_in_arguments772 = new BitSet(new long[]{0x00000000071B0200L});
    public static final BitSet FOLLOW_expr_in_arguments777 = new BitSet(new long[]{0x0000000000000082L});

}