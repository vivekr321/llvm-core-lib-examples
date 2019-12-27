extern "C" {
#include "clang-c/Index.h"
}

#include "llvm/Support/CommandLine.h"
#include <iostream>

using namespace llvm;

static cl::opt<std::string>
FileName(cl::Positional, cl::desc("Input file"), cl::Required);

int main(int argc, char** argv)
{
    cl::ParseCommandLineOptions(argc, argv, "Tokenizer\n");
    CXIndex index = clang_createIndex(0, 0);

    const char *args[] =
    {
        //provide paths to dependent include folders if they are not in PATH env variable
        //windows
        "-IC:\\LLVM\\lib\\clang\\9.0.0\\include",
        "-IC:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Professional\\VC\\Tools\\MSVC\\14.16.27023\\include",
        "-IC:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\ucrt",
        "-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.17763.0\\shared",
        "-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.17763.0\\um",
        "-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.17763.0\\winrt"
    };

    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, FileName.c_str(), args, 2,
                                        NULL, 0, CXTranslationUnit_None);
    CXFile file = clang_getFile(translationUnit, FileName.c_str());

    CXSourceLocation loc_start  = clang_getLocationForOffset(translationUnit, file, 0);
    CXSourceLocation loc_end    = clang_getLocationForOffset(translationUnit, file, FileName.length());

    CXSourceRange range = clang_getRange(loc_start, loc_end);

    unsigned int numTokens = 0;
    CXToken *tokens = NULL;

    clang_tokenize(translationUnit, range, &tokens, &numTokens);

    std::cout << "Number of token: " << numTokens << std::endl;

    for (unsigned int idx = 0; idx < numTokens; idx++)
    {
        enum CXTokenKind tokenKind  = clang_getTokenKind(tokens[idx]);
        CXString tokenName          = clang_getTokenSpelling(translationUnit,
                                                            tokens[idx]);

        switch (tokenKind)
        {
        case CXToken_Punctuation:
            std::cout << "PUNCTUATION(" << clang_getCString(tokenName) << ") ";
            break;
        case CXToken_Keyword:
            std::cout << "KEYWORD(" << clang_getCString(tokenName) << ") ";
            break;
        case CXToken_Identifier:
            std::cout << "IDENTIFIER(" << clang_getCString(tokenName) << ") ";
            break;
        case CXToken_Literal:
            std::cout << "LITERAL(" << clang_getCString(tokenName) << ") ";
            break;
        case CXToken_Comment:
            std::cout << "COMMENT(" << clang_getCString(tokenName) << ") ";
            break;
        default:
            std::cout << "UNKNOWN(" << clang_getCString(tokenName) << ") ";
            break;
        }
        clang_disposeString(tokenName);
    }

    std::cout << std::endl;
    clang_disposeTokens(translationUnit, tokens, numTokens);
    clang_disposeTranslationUnit(translationUnit);

    return 0;
}