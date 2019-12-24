extern "C" {
#include "clang-c/Index.h"
}

#include "llvm/Support/CommandLine.h"
#include <iostream>

using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Input file"), cl::Required);

int main(int argc, char** argv)
{
    cl::ParseCommandLineOptions(argc, argv, "Clang Diagnostics example");

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
    CXTranslationUnit translationUnit = clang_parseTranslationUnit(
                                        index, FileName.c_str(), args, 2, NULL, 0,
                                        CXTranslationUnit_None);

    unsigned int diagnosticsCount = clang_getNumDiagnostics(translationUnit);

    for (unsigned int idx = 0; idx < diagnosticsCount; idx++)
    {
        auto diagnostic     = clang_getDiagnostic(translationUnit, idx);
        auto diag_category  = clang_getDiagnosticCategoryText(diagnostic);
        auto diag_message   = clang_getDiagnosticSpelling(diagnostic);
        auto diag_serverity = clang_getDiagnosticSeverity(diagnostic);
        auto diag_loc       = clang_getDiagnosticLocation(diagnostic);

        CXString fileName; // = String::empty ?
        unsigned line = 0, col = 0;
        clang_getPresumedLocation(diag_loc, &fileName, &line, &col);

        std::cout   << "Severity: "     << diag_serverity
                    << " File: "        << clang_getCString(fileName)
                    << " Line: "        << line
                    << " Col: "         << col
                    << " Category: \""  << clang_getCString(diag_category)
                    << "\" Message: "   << clang_getCString(diag_message)
                    << std::endl;
        clang_disposeString(fileName);
        clang_disposeString(diag_message);
        clang_disposeString(diag_category);
        clang_disposeDiagnostic(diagnostic);
    }
    std::cout << "Total diagnostic messages: " << diagnosticsCount;

    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);
    return 0;
}