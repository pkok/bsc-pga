#ifndef INC_ConsoleLexer_hpp_
#define INC_ConsoleLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20060906): "ConsoleLexer.g" -> "ConsoleLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "ConsoleLexerTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
class CUSTOM_API ConsoleLexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public ConsoleLexerTokenTypes
{
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	ConsoleLexer(ANTLR_USE_NAMESPACE(std)istream& in);
	ConsoleLexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	ConsoleLexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mWS_(bool _createToken);
	public: void mOPERATOR(bool _createToken);
	public: void mML_COMMENT(bool _createToken);
	public: void mSL_COMMENT(bool _createToken);
	public: void mCOLON(bool _createToken);
	public: void mSEMICOLON(bool _createToken);
	public: void mCOMMA(bool _createToken);
	public: void mPAROPEN(bool _createToken);
	public: void mPARCLOSE(bool _createToken);
	public: void mSQUAREOPEN(bool _createToken);
	public: void mSQUARECLOSE(bool _createToken);
	public: void mCURLYOPEN(bool _createToken);
	public: void mCURLYCLOSE(bool _createToken);
	public: void mGLOBAL(bool _createToken);
	protected: void mQUOTED_STR_ESC(bool _createToken);
	public: void mID(bool _createToken);
	protected: void mINT(bool _createToken);
	public: void mCONSTANT(bool _createToken);
private:
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_5;
};

#endif /*INC_ConsoleLexer_hpp_*/
