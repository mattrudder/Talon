
#include "generated/TalonMaterialLexer.h"
#include "generated/TalonMaterialParser.h"

int main(int /*argc*/, char** /*argv*/)
{
	pANTLR3_UINT8 fileName = (pANTLR3_UINT8)"test.mat";

	pANTLR3_COMMON_TREE_NODE_STREAM treeNodes;
	pANTLR3_INPUT_STREAM input = antlr3FileStreamNew(fileName, ANTLR3_ENC_UTF8);
	if (input == nullptr)
	{
		ANTLR3_FPRINTF(stderr, "unable to open %s", (char *)fileName);
		return ANTLR3_ERR_NOFILE;
	}

	pTalonMaterialLexer lexer = TalonMaterialLexerNew(input);
	if (lexer == nullptr)
	{
		ANTLR3_FPRINTF(stderr, "unable to create lexer.");
		return ANTLR3_ERR_NOMEM;
	}

	pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	if (tokenStream == nullptr)
	{
		ANTLR3_FPRINTF(stderr, "unable to create tokenStream.");
		return ANTLR3_ERR_NOMEM;
	}

	pTalonMaterialParser parser = TalonMaterialParserNew(tokenStream);
	if (parser == nullptr)
	{
		ANTLR3_FPRINTF(stderr, "unable to create parser.");
		return ANTLR3_ERR_NOMEM;
	}

	auto module = parser->module(parser);
	auto errorCount = parser->pParser->rec->getNumberOfSyntaxErrors(parser->pParser->rec);
	if (errorCount > 0)
	{
		ANTLR3_FPRINTF(stderr, "The parser returned %d errors, tree walking aborted.\n", errorCount);
	}
	else
	{
		ANTLR3_FPRINTF(stdout, "Parser found no errors.");
	}

	return 0;
}